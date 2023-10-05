/*************************************************************
  Copyright (C)
  File name:      test.cpp
  Author:         王彦杰
  Version:  
  Date:           2003-3-19
  Description:    此文件对SOCKET以及SSL基本通信函数的封装
  Others:           
  Function List:  
  接口函数:
  (1)SMM_ULONG  SC_init()   
  (2)SMM_INT SC_socket(SMM_ULONG ulAddressFamily,SMM_ULONG ulType
						,SMM_ULONG ulAuth,SMM_ULONG ulEncrypt
						,SMM_ULONG ulServer,SMM_ULONG ulVersion)

  (3)SMM_INT SC_bind(SMM_INT iSocket,SMM_INT iPort)
  (4)SMM_INT SC_listen(SMM_INT iSocket,SMM_INT iMaxnum)
  (5)SMM_INT SC_connect(SMM_INT iSocket,const SMM_CHAR FAR *pcIP,SMM_INT iPort )
  (6)SMM_INT SC_send(SMM_INT iSocket, const char FAR *pcBuffer,SMM_INT iLen
				, SMM_INT iFlags,const struct sockaddr FAR *pTo,SMM_INT iTolen,SMM_INT iServer)
  (7)SMM_INT SC_recv( SMM_INT iSocket, char FAR *pcBuffer,SMM_INT iLen
				,SMM_INT iFlags,struct sockaddr FAR *pFrom, SMM_INT FAR *pFromlen,SMM_INT iServer)
  (8)SMM_INT SC_select(SMM_INT iNfds,SMM_INT iRwe,const struct timeval *pTimeout,fd_set *pFd)
  (9)SMM_INT SC_close(SMM_INT iSocket,SMM_INT iHow)
 
  内部函数:
  (1)SMM_INT SC_mallocarray(SMM_VOID)
  (2)SMM_VOID SC_freearray(SMM_INT iSocket)
  (3)SMM_INT SC_queryarray(SMM_INT iSocket)
  History:          
    1. Date:
       Author:王彦杰
       Modification:
    2. ...
**************************************************************/
//头文件区
#include "smm_ssl.h"
#include "tcp_data.h"

//全局变量
struct tagSMM_socket stSSLSocket[SOCKET_MAX] ;

DH *dh512 = NULL;
DH *dh1024 = NULL;
//共享数据区的句柄(客户端向服务器)
HANDLE hShareC2S;
//共享数据区内存映射的句柄(客户端向服务器)
HANDLE hMapFileC2S;

//共享数据区的句柄(服务器向客户端)
HANDLE hShareS2C;
//共享数据区内存映射的句柄(服务器向客户端)
HANDLE hMapFileS2C;


/////////////////////////////////////////////////////////////////
void init_dhparams(void)
{
    BIO *bio;

    bio = BIO_new_file("dh512.pem", "r");
    if (!bio)
        printf("Error opening file dh512.pem");
    dh512 = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    if (!dh512)
        printf("Error reading DH parameters from dh512.pem");
    BIO_free(bio);

    bio = BIO_new_file("dh1024.pem", "r");
    if (!bio)
       printf("Error opening file dh1024.pem");
    dh1024 = PEM_read_bio_DHparams(bio, NULL, NULL, NULL);
    if (!dh1024)
        printf("Error reading DH parameters from dh1024.pem");
    BIO_free(bio);
}
/********************************************************
 Function:        verify_callback
  Description:    证书验证回调
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				  

  Output:         
  Return:         
				  
  Others: 内部使用    
***********************************************************/
int verify_callback(int ok, X509_STORE_CTX *store)
{
    char data[256];
 
    if (!ok)
    {
        X509 *cert = X509_STORE_CTX_get_current_cert(store);
        int  depth = X509_STORE_CTX_get_error_depth(store);
        int  err = X509_STORE_CTX_get_error(store);
 
        fprintf(stderr, "-Error with certificate at depth: %i\n", depth);
        X509_NAME_oneline(X509_get_issuer_name(cert), data, 256);
        fprintf(stderr, "  issuer   = %s\n", data);
        X509_NAME_oneline(X509_get_subject_name(cert), data, 256);
        fprintf(stderr, "  subject  = %s\n", data);
        fprintf(stderr, "  err %i:%s\n", err, X509_verify_cert_error_string(err));
    }
 
    return ok;
}

/********************************************************
 Function:        tmp_dh_callback
  Description:    dh回调函数(指针函数)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				  

  Output:         
  Return:         
				  
  Others: 内部使用    
***********************************************************/
DH *tmp_dh_callback(SSL *ssl, int is_export, int keylength)
{
    DH *ret;

    if (!dh512 || !dh1024)
        init_dhparams(  );

    switch (keylength)
    {
        case 512:
            ret = dh512;
            break;
        case 1024:
        default: /* generating DH params is too costly to do on the fly */
            ret = dh1024;
            break;
    }
    return ret;
}

/********************************************************
 Function:        tmp_rsa_callback
  Description:    rsa回调函数(指针函数)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				  

  Output:         
  Return:         
				  
  Others: 内部使用(以后补充)    
***********************************************************/
DH *tmp_rsa_callback(SSL *ssl, int is_export, int keylength)
{
    DH *ret;

    if (!dh512 || !dh1024)
        init_dhparams(  );

    switch (keylength)
    {
        case 512:
            ret = dh512;
            break;
        case 1024:
        default: /* generating DH params is too costly to do on the fly */
            ret = dh1024;
            break;
    }
    return ret;
}

/********************************************************
  Function:       SC_setup_server_ctx
  Description:    设置服务器端SSL_CTX结构(证书验证/加密算法)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   ctx  : SSL_CTX
				   

  Output:         
  Return:         1:加载CA证书文件/目录失败
                  2:加载默认CA证书文件/目录失败
				  3:加载证书链失败
                  4:加载私钥文件失败
				 
				  
  Others: 内部使用     
***********************************************************/
SMM_INT SC_setup_server_ctx(SSL_CTX *ctx)
{   
	//(1)加载CA证书文件/目录
    if (SSL_CTX_load_verify_locations(ctx, CAFILE_SERVER, CADIR_SERVER) != 1)
	{   
		return 1 ;
	}
	//(2)加载默认CA证书文件/目录
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
	{
        return 2;
	}

	//(3)加载证书链
    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE_SERVER) != 1)
	{
        return 3;
	}
	//(4)加载私钥文件
    if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE_SERVER, SSL_FILETYPE_PEM) != 1)
	{
        return 4 ; 
	}
	//(5)设置证书验证方式(服务器端设置对客户端有效)
    //SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
                     //  verify_callback);
	//(6)设置证书验证深度(服务器端设置对客户端有效)
    //SSL_CTX_set_verify_depth(ctx, 4);
	//(7)设置
    SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2 |
                             SSL_OP_SINGLE_DH_USE);
	//(8)设置dh回调
    SSL_CTX_set_tmp_dh_callback(ctx, tmp_dh_callback);
	//(9)设置加密算法列表
    
   return 0 ; //设置成功
}

/********************************************************
  Function:       SC_setup_client_ctx
  Description:    设置服务器端SSL_CTX结构(证书验证/加密算法)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   ctx  : SSL_CTX
				   

  Output:         
  Return:         1:加载CA证书文件/目录失败
                  2:加载默认CA证书文件/目录失败
				  3:加载证书链失败
                  4:加载私钥文件失败
				  5:设置加密算法列表失败
				  
  Others: 内部使用     
***********************************************************/
SMM_INT SC_setup_client_ctx(SSL_CTX *ctx)
{
    //(1)加载CA证书文件/目录
    /*if (SSL_CTX_load_verify_locations(ctx, CAFILE_CLIENT, CADIR_CLIENT) != 1)
	{
	    return 1 ;
	}
	//(2)加载默认CA证书文件/目录
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
	{
        return 2;
	}
	//(3)加载证书链
    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE_CLIENT) != 1)
    {
		return 3 ;
	}
	//(4)加载私钥文件
    if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE_CLIENT, SSL_FILETYPE_PEM) != 1)
	{
        return 4 ;
	}
	//(5)设置证书验证方式
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	//(6)设置证书验证深度
    SSL_CTX_set_verify_depth(ctx, 4);*/
	//(7)设置
    SSL_CTX_set_options(ctx, SSL_OP_ALL|SSL_OP_NO_SSLv2);
 
   
	return 0 ;  //设置成功
}



/********************************************************
  Function:       SC_setup_cipher_ctx
  Description:    设置服务器端SSL_CTX结构(证书验证/加密算法)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   ctx  : SSL_CTX
				   

  Output:         
  Return:         0:设置加密算法列表成功
		  1:设置加密算法列表失败
				  
  Others: 内部使用     
***********************************************************/
SMM_INT SC_setup_cipher_ctx(SSL_CTX *ctx)
{
   //(8)设置加密算法列表
    if (SSL_CTX_set_cipher_list(ctx, CIPHER_LIST_CLIENT) != 1)
	{
            return 1 ;
	}
	
    return 0 ;

}


/********************************************************
  Function:       SC_mallocarray
  Description:    分配数组内存空间
  Calls:          malloc
  Called By:      SC_socket
                  SC_accept
  Table Accessed: 
  Table Updated:  
  Input:          无      
                   


  Output:         
  Return:        成功返回数组下标
                 无可分配的内存返回－1
				 客户端连接的数目超出上限:-2
  Others:        内部使用
***********************************************************/
SMM_INT SC_mallocarray(SMM_VOID)
{   
	SMM_INT i ;
	SMM_INT iReturn = -1 ;  // -1:表示无可分配的内存
	//(1)分配数组内存空间(主要是SSL,SSL_CTX结构)
    for (i=0 ;i<SOCKET_MAX;i++) 
	{
		//printf("malloc=%d\n",stSSLSocket[i].flag) ;
        if (stSSLSocket[i].flag != -1 ) //flag=-1:表示数组没有分配内存空间
		{
			continue ;
		}
		else   //分配内存
		{   
			stSSLSocket[i].ssl = (SSL *)malloc(sizeof(SSL)) ;
			if (stSSLSocket[i].ssl == NULL)
			{
                                return  -1 ;
				break ;
			}

            stSSLSocket[i].ctx = (SSL_CTX *)malloc(sizeof(SSL_CTX)) ;
			if (stSSLSocket[i].ctx == NULL)
			{
				return -1 ;
				break ;
			}
                        
			stSSLSocket[i].flag = -1 ;
			break ;
		}
	}
    
    //(2)若i>SOCKET_MAX,则说明连接的客户已经超过上限
	if (i >= SOCKET_MAX)
	{
		return  -2 ;
	}
	
	return i  ;
}

/********************************************************
  Function:       SC_queryarray
  Description:    遍历数组(返回数组的下标)
  Calls:          
  Called By:      SC_socket
                  SC_bind
				  SC_listen
				  SC_connect
				  SC_accept
				  SC_send
				  SC_recv
  Table Accessed: 
  Table Updated:  
  Input:          无      
                   


  Output:         
  Return:        成功返回数组下标，否则返回－1
  Others:        内部使用
***********************************************************/
SMM_INT SC_queryarray(SMM_INT iSocket)
{
	SMM_INT iReturn = -1 ;
    SMM_INT i ;
	//(1)遍历数组,查找socket对应的数组下标
	for (i=0 ;i<SOCKET_MAX;i++)
	{
		if (stSSLSocket[i].flag != iSocket)
		{
			continue ;
		}
		else
		{
			iReturn = i ;
			break ;
		}
	}
    //(2)返回下标(-1:表示错误)
	return iReturn ;
}
/********************************************************
  Function:       SC_freearray
  Description:    释放空闲的数组(SSL,SSL_CTX结构)
  Calls:          free
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          SMM_INT iSocket:套接字      
                   


  Output:         
  Return:        无
  Others:        内部使用
***********************************************************/
SMM_VOID SC_freearray(SMM_INT iSocket)
{
	//SMM_INT i  ;
	SMM_INT j  ;
    for (SMM_INT i=0 ;i<SOCKET_MAX;i++)  //遍历数组
	{
        if (stSSLSocket[i].flag != iSocket )
		{
			continue ;
		}
		else
		{
			stSSLSocket[i].ssl = NULL  ;
            stSSLSocket[i].ctx = NULL  ;
			stSSLSocket[i].s         = -1 ;
			stSSLSocket[i].sock_serv = -1 ;
			stSSLSocket[i].flag = -1 ;
			break ;
		}
	}

    //(1)清空当前元素
	/*stSSLSocket[iSocket].ssl = NULL  ; //因为在使用SC_freearray函数的地方已经得到了数组下标
    stSSLSocket[iSocket].ctx = NULL  ;
	stSSLSocket[iSocket].s         = -1 ;
	stSSLSocket[iSocket].sock_serv = -1 ;
	stSSLSocket[iSocket].flag = -1 ;*/
	//(2)后续元素前移
        /*j = SC_queryarray(iSocket) ;
        if (j == -1 )
        {
        	return ;
        }
        
	for (;j<SOCKET_MAX,j+1<SOCKET_MAX;j++)  //遍历数组
	{   
		if (stSSLSocket[j].flag != -1)
		{       //printf("free=%d\n",stSSLSocket[j].flag) ;
			stSSLSocket[j].ssl =  stSSLSocket[j+1].ssl  ; 
			stSSLSocket[j].ctx  = stSSLSocket[j+1].ctx  ;
			stSSLSocket[j].s   =  stSSLSocket[j+1].s;
			stSSLSocket[j].sock_serv = stSSLSocket[j+1].sock_serv ;
			stSSLSocket[j].flag = stSSLSocket[j+1].flag ; 
		}
		else   //-1:表示已经到数组结尾
		{
			break ;
		}
	}*/
}


/********************************************************
  Function:       SC_init
  Description:    初始化库
  Calls:          WSAStartup
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           无  
                  
  Output:         
  Return:          1表示初始化成功
				   2表示初始化socket失败
				   

  Others:        
***********************************************************/
SMM_ULONG  SC_init()   
{
	WSADATA wsaData;
	SMM_INT iReturn = 2 ;
    SMM_INT i ;
	//(1)初始化数组
	for (i=0 ;i<SOCKET_MAX;i++)
	{
           stSSLSocket[i].flag      = -1 ; 
	   stSSLSocket[i].s         = -1 ;
	   stSSLSocket[i].sock_serv = -1 ; //-1:没有使用,-2:表示该项没有使用,但s已经使用
	}
    
	//(2)初始化socket
	if (WSAStartup(MAKEWORD(2,1),&wsaData) ==0)
	{
		iReturn = 1 ;
	}
	else
	{
	    iReturn = 2 ;
	}
   
	return iReturn ;
}

/********************************************************
  Function:       SC_socket
  Description:    创建套接字
  Calls:          SC_mallocarray
                  SSLeay_add_ssl_algorithms
                  SSLv3_server_method
				  SSL_CTX_new
				  SSL_CTX_use_certificate_file
				  SSL_CTX_use_PrivateKey_file
				  SSL_CTX_check_private_key
				  socket
				  SSL_new

  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
              SMM_ULONG ulAddressFamily:地址族
			  MM_ULONG ulType:socket类型
			  SMM_ULONG ulAuth:1:表示认证模式;非1:表示不使用认证模式
              SMM_ULONG ulEncrypt 1:表示加密模式;非1:表示不使用加密模式
			  bool isssl:表示是否使用SSL安全通讯 true:表示使用
              SMM_ULONG ulServer:1:表示服务器端使用;非1:表示客户端使用
			  SMM_ULONG ulversion:使用协议 1:SSLV3;2:TLSV1
  Output:      
  				   
  Return:    成功:返回套接字    
             2 不支持该协议
			 3 协议设置失败
			 4 初始化SSL_CTX结构失败
			 5 分配内存失败
			 6 连接的用户超过上限
			 7 加载证书失败
			 8 加载私钥文件失败
			 9 创建socket失败
			 10 创建SSL失败
  Others: 在返回SOCKET或SSL有问题  
          SSLv3=5,TLS1=6; (不知道具体版本号对应的数值)
		  
 修改记录:2003/04/02(为使用udp做准备)
          将socket函数的第三个参数由0改为stppe->p_proto 
***********************************************************/
SMM_INT SC_socket(SMM_ULONG ulAddressFamily,SMM_ULONG ulType
						,SMM_ULONG ulAuth,SMM_ULONG ulEncrypt
						,SMM_ULONG ulServer,SMM_ULONG ulVersion)
{
    SSL_METHOD *pMethod ;
    X509       *x509 = NULL ;
	SMM_INT    iSocket ;
   
    
	//(0)取出协议类型
	struct protoent *stppe;
    stppe = getprotobyname("tcp");   //目前默认使用tcp
       
    //(1)为数组分配内存空间
    iSocket = SC_mallocarray() ;
	switch (iSocket)
	{
		case -1:      //分配内存失败
			 return 5 ;
			 break ;
		case -2:      //连接的用户超过上限
			 return 6 ;
			 break ;
	}
        

	//(3)处理认证模式/协议版本
	if (ulAuth == SC_VERIFY_YES)                      //采用认证模式
	{
		//(2)加载SSL库
	    SSLeay_add_ssl_algorithms() ;

        if (ulServer == SC_SERVER_YES)                //服务器使用
		{
            switch(ulVersion)             //协议版本
			{
				case SC_SSLV3:
					pMethod = SSLv3_server_method();//设置服务器使用SSLV3协议
					break;
				case SC_TLSV1:
					pMethod = TLSv1_server_method();//设置服务器使用TLSV1协议
					break;
				case SC_SSLV2:
                    pMethod = SSLv2_server_method();//设置服务器使用SSLV2协议
					break;
				case SC_SSLV23:
                    pMethod = SSLv23_server_method();//设置服务器使用SSLV23协议
					break;
				default:
					return 2 ;
					break;
			}
			
		}
		else                              //客户端使用
		{
			switch(ulVersion)             //协议版本
			{
				case SC_SSLV3:
					pMethod = SSLv3_client_method() ;//设置客户端使用SSLV3协议
					break ;
				case SC_TLSV1:
					pMethod = TLSv1_client_method() ;//设置客户端使用TLSV1协议
					break ;
				case SC_SSLV2:
					pMethod = SSLv2_client_method() ;//设置客户端使用SSLV2协议
					break ;
				case SC_SSLV23:
					pMethod = SSLv23_client_method() ;//设置客户端使用SSLV23协议
					break ;
				default:
					return 2 ;
					break ;
			}
		}

		//(4)判断设置协议版本是否正确(暂时屏蔽)
		/*
        if(pMethod->version != 5 && pMethod->version != 6)
		{
			return 3;
		}
		*/

        //(5)创建SSL上下文环境
        stSSLSocket[iSocket].ctx            = SSL_CTX_new(pMethod) ;
		if (stSSLSocket[iSocket].ctx == NULL) 
		{
			return 4 ;
		}
		
	   //(6)取出握手协议参数(取出本地证书)
	   //(6-1)加载服务器证书/私钥文件
	   if (ulServer == SC_SERVER_YES && ulAuth == SC_VERIFY_YES)
	   {
		    //SSL_CTX_set_verify(stSSLSocket[iSocket].ctx,SSL_VERIFY_NONE,NULL);
		    //SSL_CTX_set_options(stSSLSocket[iSocket].ctx,SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION) ;  //设置会话重连
		    SC_setup_server_ctx(stSSLSocket[iSocket].ctx) ;
		    /*if (SSL_CTX_use_certificate_file(stSSLSocket[iSocket].ctx,"cert.pem"
				, SSL_FILETYPE_PEM) <= 0) 	//加载证书文件
			{
				return 6 ;
                //exit(3);
            }

		   if (SSL_CTX_use_PrivateKey_file(stSSLSocket[iSocket].ctx, "key.pem"
			 , SSL_FILETYPE_PEM) <= 0)      //加载私钥文件
		   {
			    return 7 ;
		        //exit(4);
		   }

		   if (!SSL_CTX_check_private_key(stSSLSocket[iSocket].ctx)) //校验证书公钥是否与私钥配对
		   {
			   return 8 ;
		      //exit(5);
		   }*/
	   }
       //(6-2)加载客户端证书/私钥文件
       if (ulServer == SC_CLIENT_YES && ulAuth == SC_VERIFY_YES)
	   {
		    SC_setup_client_ctx(stSSLSocket[iSocket].ctx) ;
		    //SSL_CTX_set_verify(stSSLSocket[iSocket].ctx,SSL_VERIFY_PEER,NULL);  //客户端验证服务器证书
		    /*if (SSL_CTX_use_certificate_file(stSSLSocket[iSocket].ctx,"cert.pem"
				, SSL_FILETYPE_PEM) <= 0) 	//加载证书文件
			{
			    return 6 ;
                //exit(3);
            }

		   if (SSL_CTX_use_PrivateKey_file(stSSLSocket[iSocket].ctx, "key.pem"
			 , SSL_FILETYPE_PEM) <= 0)      //加载私钥文件
		   {
		        return 7 ;
		        //exit(4);
		   }

		   if (!SSL_CTX_check_private_key(stSSLSocket[iSocket].ctx)) //校验证书公钥是否与私钥配对
		   {
		      return 8 ;
		      //exit(5);
		   }*/
	   }

	   //(7)设置握手协议参数(加密算法)
	   if (ulEncrypt == SC_ENCRYPT_YES) //采用加密
	   {    
		    
                //SSL_CTX_set_options(stSSLSocket[iSocket].ctx,SSL_OP_ALL) ;
	        SC_setup_cipher_ctx(stSSLSocket[iSocket].ctx) ;
	   }
	   else
	   {

	   }
	   //(8)创建socket套接字
        stSSLSocket[iSocket].s   = socket(ulAddressFamily,ulType,stppe->p_proto) ; 
        if (stSSLSocket[iSocket].s == SOCKET_ERROR)
		{
			return 9 ;
		}

        //printf("socket=%d",stSSLSocket[iSocket].s) ; //测试:显示socket值
        stSSLSocket[iSocket].sock_serv = -2 ; //-2:表示该项没有使用,但s已经使用
		//(9)创建SSL通道
        stSSLSocket[iSocket].ssl = SSL_new(stSSLSocket[iSocket].ctx) ; //创建SSL套接字
		if (stSSLSocket[iSocket].ssl == NULL)
		{
			return 10 ;
		}

        if (ulServer == SC_CLIENT_YES)
		{
		    //SSL_set_verify(stSSLSocket[iSocket].ssl,SSL_VERIFY_PEER,NULL); //设置客户端验证方式
		}
	}
	else  //不采用SSL通讯
	{
		stSSLSocket[iSocket].s   = socket(ulAddressFamily,ulType,stppe->p_proto) ;  //socket第三个参数由0改为
		//printf("SC_socket=%d\n",stSSLSocket[iSocket].s) ;  //测试
		if (stSSLSocket[iSocket].s == SOCKET_ERROR)
		{
			return 9 ;
		}
		stSSLSocket[iSocket].sock_serv = -2 ; //-2:表示该项没有使用,但s已经使用
		stSSLSocket[iSocket].ssl = NULL ; 
		stSSLSocket[iSocket].ctx = NULL ;
		
	} 
	
	//(9)返回socket套接字
	stSSLSocket[iSocket].flag = iSocket ;
	return iSocket ;

}


/********************************************************
  Function:       SC_bind
  Description:    绑定ip和端口
  Calls:          bind
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket:套接字
                  SMM_INT iPort  :端口号
  Output:         
  Return:         
                  0:绑定成功
				  -1:表示没有给定socket
				  非零:错误代码
  Others:      
***********************************************************/

SMM_INT SC_bind(SMM_INT iSocket,SMM_INT iPort)
{
    struct sockaddr_in stServer;
	SMM_INT iError ;
    SMM_INT iSSL ;
    
	//(1)在数组中查找套接字对应的下标
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}
	//(2)绑定端口
	stServer.sin_family      = AF_INET ;
	stServer.sin_addr.s_addr = htonl(INADDR_ANY) ;
	stServer.sin_port        = htons(iPort) ;
	
	//printf("SC_bind=%d\n",stSSLSocket[iSSL].s) ; //测试
    iError = bind(stSSLSocket[iSSL].s,(struct sockaddr*)&stServer,sizeof(stServer));
	
	return iError ;
}

/********************************************************
  Function:       SC_listen
  Description:    服务器监听请求客户端连接请求
  Calls:          listen
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket:套接字
				  SMM_INT iMaxnum:缓冲区最大等待连接数
  Output:         
  Return:         
                  0:正确
				  -1:表示没有给定socket
				  非零:返回错误代码
  Others:      
***********************************************************/
SMM_INT SC_listen(SMM_INT iSocket,SMM_INT iMaxnum)
{
	 SMM_INT iError ;
	 SMM_INT iSSL ;
     
	 //(1)在数组中查找套接字对应的下标
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}
	 //(2)监听
	 
	// printf("SC_listen=%d\n",stSSLSocket[iSSL].s) ; //测试
	 
	 iError = listen(stSSLSocket[iSSL].s,iMaxnum);
	 return iError ;
}

/********************************************************
  Function:       SC_accept
  Description:    服务器等待连接请求
  Calls:          accept
                  SC_queryarray
				  SC_mallocarray
				  SSL_accept
				  SSL_set_fd
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket:套接字
				 
  Output:         
  Return:         
                  >=0:socket套接字(客户端)
				  -1:返回其他错误代码
				  -2:分配内存失败
				  -3:连接的用户超过上限
				  -4:调用accept函数失败
				  -5:调用SSL_set_fd绑定函数失败
				  -6:调用SSL_accept函数失败
				  -7:没有给定的socket
  Others:      
***********************************************************/
SMM_INT SC_accept(SMM_INT iSocket)
{
	struct sockaddr_in stClient_S ;
    SMM_INT iError = 0 ; 
    SMM_INT iServer_socket ;
    SMM_INT iClient_Socket ;
    SMM_INT iClient ;
	
	//(1)在数组中查找套接字对应的下标
	iServer_socket = SC_queryarray(iSocket) ; 
	//printf("server_socket=%d",iServer_socket) ;//测试
	if (iServer_socket == -1)
	{
		return -7 ;
	}
	
	//(2)sock_serv:-2:表示该数组结构中该子项没有使用,但s已经使用
	
        iClient_Socket  = SC_mallocarray() ;
       // printf("client_socket=%d",iClient_Socket ) ; //测试
        switch (iClient_Socket)
	{
		case -1:      //分配内存失败
			 return -2 ;
			 break ;
		case -2:      //连接的用户超过上限
			 return -3 ;
			 break ;
	}
	
	
	//(3)服务器等待连接请求
	iClient = sizeof(stClient_S) ;
    if (stSSLSocket[iServer_socket].ssl != NULL)       //使用SSL安全通讯(使用服务器的SSL项)
	{   
		//(3-1)等待客户端socket连接请求
		stSSLSocket[iClient_Socket].sock_serv = accept(stSSLSocket[iServer_socket].s
			,(struct sockaddr *) &stClient_S,&iClient) ;
		if (stSSLSocket[iClient_Socket].sock_serv == SOCKET_ERROR)
		{
			return -4 ;
		}
		printf("sock_serv=%d",stSSLSocket[iClient_Socket].sock_serv) ; //测试accept返回值
        //(3-2)绑定socket和ssl
        iError = SSL_set_fd(stSSLSocket[iServer_socket].ssl,stSSLSocket[iClient_Socket].sock_serv);
		if (iError<0)
		{
			return -5 ;
		}
        //(3-3)等待客户端ssl连接请求
		iError = SSL_accept(stSSLSocket[iServer_socket].ssl) ;
		printf("ssl_accept=%d",iError) ; //测试SSL_accept返回值
		if (iError <0 )
		{   
			SSL_shutdown(stSSLSocket[iServer_socket].ssl) ; 
			return -6 ;
		}
		
		stSSLSocket[iClient_Socket].flag = iClient_Socket ;   //补充
	}
	else   //不使用SSL通讯
	{
        stSSLSocket[iClient_Socket].sock_serv = accept(stSSLSocket[iServer_socket].s
			,(struct sockaddr *) &stClient_S,&iClient) ;
	stSSLSocket[iClient_Socket].flag = iClient_Socket ;   //补充		
	printf("SC_accept=%d\n",stSSLSocket[iClient_Socket].sock_serv) ;
	//test 
	/*printf("input enter\n") ;
	char a=' ' ;
	while (a !='\n')
	{
		a=getchar() ;
	}*/
		if (stSSLSocket[iClient_Socket].sock_serv == SOCKET_ERROR)
		{
			return -4 ;
		}
	}
    
	//(4)返回值套接字
	return iClient_Socket ;

}

/********************************************************
  Function:       SC_connect
  Description:    客户端连接服务器
  Calls:          connect
                  SSL_connect
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket          :套接字
				  const SMM_CHAR FAR *pcIP :IP地址
				  SMM_INT iPort            :端口
  Output:         
  Return:         
                  0:正确
				  -1:表示没有给定的socket
				  -2:表示调用SSL_set_fd失败
				  -3:表示调用SSL_connect失败
				  非零:返回错误代码
  Others:      
***********************************************************/
SMM_INT SC_connect(SMM_INT iSocket,const SMM_CHAR FAR *pcIP,SMM_INT iPort )
{
	SMM_INT  iError = 0 ;
    struct sockaddr_in stClient_S ;
	SMM_INT iSSL ;
    
	//(1)在数组中查找套接字对应的下标
	iSSL = SC_queryarray(iSocket) ;
	
	if (iSSL == -1)
	{
		return -1 ;
	}
    //(2)连接服务器    
    stClient_S.sin_family      = AF_INET ;
	stClient_S.sin_addr.s_addr = inet_addr(pcIP) ;
	stClient_S.sin_port        = htons(iPort) ;
	if (stSSLSocket[iSSL].ssl != NULL)     //使用SSL安全通讯
	{   
		//(2-1)连接socket服务器
        iError = connect(stSSLSocket[iSSL].s,(struct sockaddr *)&stClient_S,sizeof(struct sockaddr)) ;
		if (iError != 0)
		{
			return SOCKET_ERROR ;
		}
        //printf("iError=%d",iError) ; //测试connect函数
		//(2-2)绑定socket和ssl
		iError = SSL_set_fd(stSSLSocket[iSSL].ssl,stSSLSocket[iSSL].s) ;
        if (iError != 1)
		{
			return -2 ;
		}
		//(2-3)连接ssl
		iError = SSL_connect(stSSLSocket[iSSL].ssl) ;
		if (iError != 1)
		{
			return -3 ;
		}
	}
	else                                  //不使用SSL安全通讯
	{
		iError = connect(stSSLSocket[iSSL].s,(struct sockaddr *)&stClient_S,sizeof(stClient_S)) ;
		if (iError != 0)
		{
			return SOCKET_ERROR ;
		}
	}

	return iError ;
}

/********************************************************
  Function:       SC_send
  Description:    发送数据
  Calls:          send
                  SC_write
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket            :套接字
				  const char FAR *pcBuffer   :数据缓冲区
				  SMM_INT iLen               :数据长度
				  SMM_INT iFlags             :0表示tcp
				  const struct sockaddr FAR *pTo 仅对udp有效
				  SMM_INT iTolen             仅对udp有效
				  SMM_INT iServer            SC_SERVER_YES:服务器使用
				                             SC_CLIENT_YES:客户端使用
  Output:         
  Return:         
                  成功返回发送数据的长度
				  -1:没有给定的socket

				  不成功返回错误代码
  Others:      
***********************************************************/
SMM_INT SC_send(SMM_INT iSocket, const SMM_UCHAR FAR *pcBuffer,SMM_INT iLen
				, SMM_INT iFlags,const struct sockaddr FAR *pTo,SMM_INT iTolen,SMM_INT iServer)
{
     SMM_INT iLength ;
     SMM_INT iSSL ;
     
	//(1)在数组中查找套接字对应的下标
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}

     if (stSSLSocket[0].ssl != NULL)  //使用SSL安全通讯
	 {  
         iLength = SSL_write(stSSLSocket[iSSL].ssl,pcBuffer,iLen) ;
	 }
	 else                               //不使用SSL安全通讯
	 {
		if (iServer == SC_SERVER_YES)   //服务器向客户端发送数据
		{
			 iLength = send(stSSLSocket[iSSL].sock_serv,(char *)pcBuffer,iLen,iFlags) ;
		}
		else                            //客户端使用
		{
		   iLength = send(stSSLSocket[iSSL].s,(char *)pcBuffer,iLen,iFlags) ;
		}
	 }
    
	 //(2)>=0返回发送数据的长度;其他为发送错误
	 return iLength ;
}

/********************************************************
  Function:       SC_recv
  Description:    接收数据
  Calls:          recv
                  SSL_read
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket            :套接字
				  const char FAR *pcBuffer   :数据
				  SMM_INT iLen               :数据长度
				  SMM_INT iFlags             :0表示tcp
				  struct sockaddr FAR *pFrom :仅对udp有效
				  SMM_INT FAR *pFromlen      :仅对udp有效
				  iServer                    :SC_SERVER_YES:服务器使用
				                              SC_CLIENT_YES:客户端使用
  Output:         
  Return:         
                  >0 成功返回接收数据的长度
				  =0 网络中断(已经断开了连接)
				  -1:没有给定的socket
				  不成功返回错误代码
  Others:      
***********************************************************/
SMM_INT SC_recv( SMM_INT iSocket, SMM_UCHAR FAR *pcBuffer,SMM_INT iLen
				,SMM_INT iFlags,struct sockaddr FAR *pFrom, SMM_INT FAR *pFromlen,SMM_INT iServer)
{
	SMM_INT iLength = -2;
	SMM_INT iSSL ;
    
	//(1)在数组中查找套接字对应的下标
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}

	if (stSSLSocket[0].ssl != NULL)       //使用SSL安全通讯
	{
		iLength = SSL_read(stSSLSocket[iSSL].ssl,pcBuffer,iLen) ;
	}
	else                                    //不使用SSL安全通讯
	{
		if (iServer == SC_SERVER_YES)  //服务器发送到各客户端
		{
			//printf("SC_recv=%d\n",stSSLSocket[iSSL].sock_serv) ;
            iLength = recv(stSSLSocket[iSSL].sock_serv,(char *)pcBuffer,iLen,iFlags) ;
		}
		else                           //客户端使用
		{
			 iLength = recv(stSSLSocket[iSSL].s,(char *)pcBuffer,iLen,iFlags) ;
		}
		  
	}
    //(2)iLength>0返回接收数据的长度;其他为接收错误
	return iLength ;
}

/********************************************************
  Function:       SC_ioctl
  Description:    设定socket模式
  Calls:          ioctlsocket 
  Called By:      
  Table Accessed: 
  Table Updated: 
  Input:           
                   SMM_INT   iSocket:socket描述字 
				   SMM_LONG  cmd    :获取或设定 Socket 的运作参数的指令 
                   SMM_ULONG argp   :指令参数指针 非零:表示非阻塞
				                                  0 :表示阻塞
                   

  Output:         
  Return:         
                  0: 设置成功
				  -1:设置错误
  Others:      与SSL_accept函数使用有冲突(不用也可以/暂时没用)
***********************************************************/
/////////////////////////////////////////////////////////////////////////
SMM_INT SC_ioctl(SMM_INT iSocket,SMM_LONG lCmd,SMM_ULONG pArgp)
	{
		SMM_INT iErr = -1;	
		SMM_INT iSSL ;	
                SMM_ULONG ulBlock ;  //定义设置是否阻塞标志变量
                
                //(1)        
		if (pArgp == 0)
		{   
			ulBlock = 0 ;
		}
		else
		{
			ulBlock = 1 ;
		}
            
  
	    iSSL = SC_queryarray(iSocket) ;

		switch(lCmd)			//根据用户输入的命令参数进行定义，只考虑阻塞/非阻塞
		{
			case FIONBIO:      //设置阻塞/非阻塞模式
				iErr = ioctlsocket(stSSLSocket[iSSL].s,FIONBIO,&ulBlock);
				break;
			default:          //其他模式暂时不处理
				break;
		}
    
	  
     
	   if (iErr == 0)
	   {
		   return 0 ;
	   }
	   else
       {
	      return -1;
	   }

	}
/********************************************************
  Function:       SC_selectinit
  Description:    初始化select函数中fd_set记录集
  Calls:          FD_ZERO
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           

				   pFd       fd_set记录集



  Output:         
  Return:         
                  
  Others:  
***********************************************************/
SMM_VOID SC_selectinit(fd_set *pFd)
{
	FD_ZERO(pFd);
		
}
/********************************************************
  Function:       SC_select
  Description:    返回未处理socket的数目
  Calls:          select
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                   SMM_INT iNfds:可以忽略，兼容Berkeley socket所用
				   SMM_INT iRwe : SC_SELECTREAD_YES等待可读的socket组的指针
				                  SC_SELECTWRITE_YES等待可写的socket组的指针
				                  SC_SELECTEXP_YES:异常
				   timeout      :指定等待时间
				   fd_set *pFd  :文件描述集


  Output:         
  Return:         
                  返回未处理socket最大描述字数目
				  -1:调用失败
  Others:      
***********************************************************/
SMM_INT SC_select(SMM_INT iNfds,SMM_INT iRwe,const struct timeval *pTimeout,fd_set *pFd)
	{
		SMM_INT  iNready = -1 ;

		switch(iRwe)
		{
			case 0:    //可读
				iNready=select(0,pFd,NULL,NULL,NULL);
				//printf("select=%d",iNready) ;
				 break ;
			case 1:   //可写
				iNready=select(0,NULL,pFd,NULL,NULL);
				break;
			case 2:  //异常
					iNready=select(0,NULL,NULL,pFd,NULL);
					break;

		}
       
		return iNready ;
	}
/********************************************************
  Function:       SC_close
  Description:    释放通讯环境,具有单项关闭的功能
  Calls:          closesocket
                  shutdown
                  SSL_shutdown
                  SSL_free
				  SSL_CTX_free
  Called By:     
  Table Accessed: 
  Table Updated:  
  Input:           
                   stSocket_S         socket描述字
                   iHow               SD_SEND:关闭send,SD_RECEIVE:关闭recv
				                      SD_NO:双向关闭
                   iMain              1:服务器上accecpt返回的客户socket
                                      0:其他socket

  Output:         
  Return:        0  :成功返回   
                 1  :无此socket 
				 2  :调用shutdown/closesocket函数失败
				 3  :调用WSACleanup函数失败
				 4  :调用SSL_shutdown函数失败
				 5  :其他原因

  Others:      
***********************************************************/
SMM_INT SC_close(SMM_INT iSocket,SMM_INT iHow,SMM_INT iMain)
	{
		SMM_INT iErr   = 0 ;
		SMM_INT iSSL = 5 ;

        //(1)在数组中查找套接字对应的下标
	    iSSL = SC_queryarray(iSocket) ;
        if (iSSL == -1)
		{
			return 1 ;
		}

        //(2)关闭socket/ssl
		if(stSSLSocket[0].ctx == NULL) //不使用SSL通讯
		{   
			switch (iHow)
			{
				 case SD_SEND:
					 iErr = shutdown(stSSLSocket[iSSL].s,SD_SEND) ;
					 break;
				 case SD_RECEIVE:
					 iErr = shutdown(stSSLSocket[iSSL].s,SD_RECEIVE) ;
					 break ;
				 default:
					 if (iMain == 1) //用于服务器上accecpt返回的客户socket
					{      
						//printf("sock=%d\n",stSSLSocket[iSSL].sock_serv) ;
						iErr = closesocket(stSSLSocket[iSSL].sock_serv);
					}
					else            //其他socket
					{
					     iErr = closesocket(stSSLSocket[iSSL].s);	
					     iErr = WSACleanup();
						if (iErr == SOCKET_ERROR) //判断调用WSACleanup是否成功
						{
							return 3 ;
						}
					}
					break ;
			}

			if (iErr == SOCKET_ERROR) //判断调用shutdown是否成功
			{
				return 2 ;
			}

			
		}
		else                             //使用SSL通讯
		{
			 switch (iHow)
			 {
				 case SD_SEND:
					 iErr = shutdown(stSSLSocket[iSSL].s,SD_SEND) ;
					 break;
				 case SD_RECEIVE:
					iErr = shutdown(stSSLSocket[iSSL].s,SD_RECEIVE) ;
					break ;
				 default:
					
					if (iMain == 1) //用于服务器上accecpt返回的客户socket
					{
						iErr = closesocket(stSSLSocket[iSSL].sock_serv);
					}
					else            //其他socket
					{
					     iErr = closesocket(stSSLSocket[iSSL].s);
					     iErr = WSACleanup();
						if (iErr == SOCKET_ERROR) //判断调用WSACleanup是否成功
						{
							return 3 ;
						}	
					}
					break ;
			 }

			if (iErr == SOCKET_ERROR) //判断调用shutdown/closesocket是否成功
			{
				return 2 ;
			}

			

			iErr = SSL_shutdown(stSSLSocket[iSSL].ssl);
		
            if (iErr == -1)
			{
				return 4 ;
			}

			SSL_free(stSSLSocket[iSSL].ssl);
			SSL_CTX_free(stSSLSocket[iSSL].ctx);
		}

		//(3)释放该套接字占用的数组资源
		//printf("sc_freearray=%d",iSSL) ;
		SC_freearray(iSSL) ;

		return iErr ;
		
	}


/***********************************************************/
//连接重协商函数(需要补充)



/********************************************************
  Function:       SC_isset
  Description:    判断指定的socket是否在文件描述集中
  Calls:          FD_ISSET 
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : 套接字
				   *pFd     : fd_set集
				   iClient  : 1:服务器处理多客户端
				              0:服务器本身
			       


  Output:         
  Return:         
                  iSocket在fd_set集中返回 1
				  -1:表示没有给定的socket
				  0 :其他失败
  Others:      
***********************************************************/
SMM_INT SC_isset(SMM_INT iSocket,fd_set FAR *pFd,SMM_INT iClient)
	{
	    SMM_INT iNready ;
		SMM_INT iSSL ;

	    iSSL = SC_queryarray(iSocket) ;
        if (iSSL == -1)
		{
			return -1 ;
		}

		if (iClient == 1 )  //服务器处理多客户端
		{
          iNready = FD_ISSET(stSSLSocket[iSSL].sock_serv,pFd) ;
		}
		else   //服务器本身/客户端
		{
		   iNready = FD_ISSET(stSSLSocket[iSSL].s,pFd) ;
		}

		return iNready ;


	}


/********************************************************
  Function:       SC_fdset
  Description:    将指定的socket增加到文件描述集中
  Calls:          FD_SET
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : 套接字
				   iClient  : 1:服务器处理多客户端
				              0:服务器本身
                   pFd      :fd_set集

  Output:         
  Return:          无   
                  
  Others:      
***********************************************************/
SMM_VOID SC_fdset(SMM_INT iSocket,fd_set FAR *pFd,SMM_INT iClient)
	{
	    
		SMM_INT iSSL ;

	    iSSL = SC_queryarray(iSocket) ;
		if (iSSL == -1)
		{
			return ;
		}

		if (iClient == 1 )  //服务器处理多客户端
		{
            FD_SET(stSSLSocket[iSSL].sock_serv,pFd) ;
		}
		else
		{
		    FD_SET(stSSLSocket[iSSL].s,pFd) ;
		}

	}
	

/********************************************************
  Function:       SC_fdclear
  Description:    清除文件描述集中指定的socket
  Calls:          FD_CLR
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : 套接字
				   iClient  : 1:服务器处理多客户端
				              0:服务器本身
                   pFd      : fd_set集

  Output:         
  Return:         无
                  
				  
  Others:      
***********************************************************/
SMM_VOID SC_fdclear(SMM_INT iSock,fd_set FAR *fd,SMM_INT iClient)
{
	SMM_INT iBound ;
	
	iBound = SC_queryarray(iSock) ;
	if (iBound == -1)
	{
		return ;
	}

	if (iClient == 1)  //客户端socket
	{
	   FD_CLR(stSSLSocket[iBound].sock_serv,fd);
	}
	else
	{
	   FD_CLR(stSSLSocket[iBound].s,fd);
	}
}

/********************************************************
  Function:       SC_getip
  Description:    得到ip地址
  Calls:          getpeername
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : 套接字
				  

  Output:         
  Return:         无
                  
				  
  Others: 内部使用     
***********************************************************/
unsigned long SC_getip(SMM_INT  iSocket,char *ipaddr,SMM_USHORT *port)
    {
     struct sockaddr_in name;
     //size_t namelen = sizeof(name);
     int      namelen = sizeof(name) ;
     unsigned long ip = 0;
	 SMM_INT iSSL ;
	 SMM_INT iReturn ;
	 SMM_CHAR cip[19] ; //存储ip
	 //SMM_INT iPort; //存储端口

     //assert(fd >= 0);
     //assert(ipaddr != NULL);
    
    // *ipaddr = '\0';

     iSSL = SC_queryarray(iSocket) ;
     if (iSSL == -1)
	 {
		return -1 ;
	 }

     //printf("ss=%d",stSSLSocket[iSSL].sock_serv) ;
   
        iReturn = getpeername(stSSLSocket[iSSL].sock_serv, (struct sockaddr *) &name, &namelen) ;
    
     
     //printf("return=%d",iReturn) ;

     if ( iReturn!= 0) 
	 {
         strerror(errno);
     }
     else 
     {
       strcpy(ipaddr,
       inet_ntoa(*(struct in_addr *) &name.sin_addr.s_addr));
       //printf("ipaddr=%s",ipaddr) ; //测试ip
       port = &name.sin_port ;
   
       //printf("port=%d",*port) ;
       //ip = inet_addr(ipaddr);
     }

    
     return 0;  //正确
    }

//////////////////////////////////////////////////////////
//封装对共享内存的封装  
/********************************************************
  Function:       CreateFileMappingC2S
  Description:    创建共享数据区(客户端向服务器)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:表示创建共享内存成功
		  -1:表示创建共享内存失败

  Others:      
***********************************************************/
int  CreateFileMappingC2S()
{
	hShareC2S = CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//共享数据区大小
		"ServerJNITLVModuleC2S"	//命名空间：ServerJNITLVModule
		);
	//创建失败
	if(hShareC2S == NULL)
	{
		printf("Could not create file-mapping S2C object");
		return -1;
	}
	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleC2S_Write");
	CreateSemaphore(NULL, 0, 1, "ServerJNITLVModuleC2S_Read");
	
	return 1;
}


/********************************************************
  Function:       CreateFileMappingS2C
  Description:    创建共享数据区(服务器向客户端)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:表示创建共享内存成功
		  -1:表示创建共享内存失败

  Others:      
***********************************************************/
int CreateFileMappingS2C()
{
	hShareC2S = CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//共享数据区大小
		"ServerJNITLVModuleS2C"	//命名空间：ServerJNITLVModule
		);
	//创建失败
	if(hShareC2S == NULL)
	{
		printf("Could not create file-mapping S2C object");
		return -1;
	}
	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleS2C_Write");
	CreateSemaphore(NULL, 0, 1, "ServerJNITLVModuleS2C_Read");
	return 1;
}

/********************************************************
  Function:       SetTransfer_C2S_StructtoMapFileC2S
  Description:    写共享数据区:C2S(客户端到服务器)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:表示写共享内存成功
		  -1:表示写共享内存失败

  Others:      
***********************************************************/
//从全局变量m_Data_Transfer_C2S_Struct向共享数据区设置Transfer_C2S_Struct
int SetTransfer_C2S_StructtoMapFileC2S(tagSMM_c2s *m_Data_Transfer_C2S_Struct)
{
	//获取共享数据区
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//获取共享数据区中内存窗口句柄
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileC2S, // Handle to mapping object. 
		FILE_MAP_WRITE,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		0);                                // Map entire file. 
	if (lpMapAddress == NULL)
	{ 
		printf("Could not map view of file.");
		return -1;
	} 

	//获取信号量
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	//写入数据
	//for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    //{
    	memcpy((unsigned char*)lpMapAddress,(unsigned char*)m_Data_Transfer_C2S_Struct,sizeof(tagSMM_c2s));
       //((unsigned char*)lpMapAddress)[i] = ((unsigned char*)m_Data_Transfer_C2S_Struct)[i];
    //}

	//释放信号量
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return 1;
}

/********************************************************
  Function:       SetTransfer_C2S_StructtoMapFileS2C
  Description:    写共享数据区:C2S(客户端到服务器)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:表示写共享内存成功
		  -1:表示写共享内存失败

  Others:      //S2C(暂时不用)
***********************************************************/

//从全局变量m_Data_Transfer_S2C_Struct向共享数据区设置Transfer_S2C_Struct
int SetTransfer_S2C_StructtoMapFileS2C(tagSMM_s2c *m_Data_Transfer_S2C_Struct)
{
	//获取共享数据区
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//获取共享数据区中内存窗口句柄
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileS2C, // Handle to mapping object. 
		FILE_MAP_WRITE,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		0);                                // Map entire file. 
	if (lpMapAddress == NULL)
	{ 
		printf("Could not map view of file.");
		return -1;
	} 

	//获取信号量
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	//写入数据
	//for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
    //{
        memcpy((unsigned char*)lpMapAddress,(unsigned char*)&m_Data_Transfer_S2C_Struct,sizeof(tagSMM_s2c)) ;
       //((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_Data_Transfer_S2C_Struct)[i];
    //}

	//释放信号量
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return 1;
}


/********************************************************
  Function:       GetTransfer_C2S_StructfromMapFileC2S
  Description:    从共享数据区获取数据TLVStruct:C2S(客户端到服务器)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:表示读共享内存成功
		  -1:表示读共享内存失败

  Others:      //C2S(客户端到服务器:暂时不用:调试成功)
***********************************************************/
int GetTransfer_C2S_StructfromMapFileC2S( tagSMM_c2s *m_Data_Transfer_C2S_Struct)
{
	//获取共享数据区
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//获取共享数据区中内存窗口句柄
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileC2S, // Handle to mapping object. 
		FILE_MAP_WRITE,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		0);                                // Map entire file. 
	if (lpMapAddress == NULL)
	{ 
		printf("Could not map view of file.");
		return -1;
	}

	//获取信号量
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	//读入数据
	//for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    //{
    	memcpy((unsigned char*)m_Data_Transfer_C2S_Struct,(unsigned char*)lpMapAddress,sizeof(tagSMM_c2s)) ;
       //((unsigned char*)&m_Data_Transfer_C2S_Struct)[i] = ((unsigned char*)lpMapAddress)[i];
    //}

	//释放信号量
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return 1;
}


/********************************************************
  Function:       GetTransfer_S2C_StructfromMapFileS2C
  Description:    从共享数据区获取数据TLVStruct:C2S(服务器到客户端)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:表示读共享内存成功
		  -1:表示读共享内存失败

  Others:      //S2C(服务器到客户端:未调试)
***********************************************************/
int GetTransfer_S2C_StructfromMapFileS2C(tagSMM_s2c *m_Data_Transfer_S2C_Struct)
{
	//获取共享数据区
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//获取共享数据区中内存窗口句柄
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileS2C, // Handle to mapping object. 
		FILE_MAP_WRITE,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		0);                                // Map entire file. 
	if (lpMapAddress == NULL)
	{ 
		printf("Could not map view of file.");
		return -1;
	} 

	//获取信号量
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	//读入数据
	//for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
   //{
    	memcpy((unsigned char*)m_Data_Transfer_S2C_Struct,(unsigned char*)lpMapAddress,sizeof(tagSMM_s2c)) ;
       //((unsigned char*)&m_Data_Transfer_S2C_Struct)-> = ((unsigned char*)lpMapAddress)[i];
    //}

	//释放信号量
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return 1;
}


/********************************************************
  Function:       SC_isnull
  Description:    判断字符数组是否为空
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           char *cData:要比较的数据指针
                   int iLen   :数据长度
                  
				   
			       


  Output:         
  Return:         
                  1:为空
		  0:不为空

  Others:      //S2C(服务器到客户端:未调试)
***********************************************************/
int SC_isnull(char *cData,int iLen)
{
	for (int i=0 ;i<iLen;i++)
	{
        if (*(cData+i) != '\0')
		{
			break ;
		
		}
	}

    if (i<iLen)
	{
		return 0;
	}
	else
	{ 
		return 1 ;
	}
}



