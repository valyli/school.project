/*************************************************************
  Copyright (C)
  File name:      test.cpp
  Author:         �����
  Version:  
  Date:           2003-3-19
  Description:    ���ļ���SOCKET�Լ�SSL����ͨ�ź����ķ�װ
  Others:           
  Function List:  
  �ӿں���:
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
 
  �ڲ�����:
  (1)SMM_INT SC_mallocarray(SMM_VOID)
  (2)SMM_VOID SC_freearray(SMM_INT iSocket)
  (3)SMM_INT SC_queryarray(SMM_INT iSocket)
  History:          
    1. Date:
       Author:�����
       Modification:
    2. ...
**************************************************************/
//ͷ�ļ���
#include "smm_ssl.h"
#include "tcp_data.h"

//ȫ�ֱ���
struct tagSMM_socket stSSLSocket[SOCKET_MAX] ;

DH *dh512 = NULL;
DH *dh1024 = NULL;
//�����������ľ��(�ͻ����������)
HANDLE hShareC2S;
//�����������ڴ�ӳ��ľ��(�ͻ����������)
HANDLE hMapFileC2S;

//�����������ľ��(��������ͻ���)
HANDLE hShareS2C;
//�����������ڴ�ӳ��ľ��(��������ͻ���)
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
  Description:    ֤����֤�ص�
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				  

  Output:         
  Return:         
				  
  Others: �ڲ�ʹ��    
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
  Description:    dh�ص�����(ָ�뺯��)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				  

  Output:         
  Return:         
				  
  Others: �ڲ�ʹ��    
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
  Description:    rsa�ص�����(ָ�뺯��)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				  

  Output:         
  Return:         
				  
  Others: �ڲ�ʹ��(�Ժ󲹳�)    
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
  Description:    ���÷�������SSL_CTX�ṹ(֤����֤/�����㷨)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   ctx  : SSL_CTX
				   

  Output:         
  Return:         1:����CA֤���ļ�/Ŀ¼ʧ��
                  2:����Ĭ��CA֤���ļ�/Ŀ¼ʧ��
				  3:����֤����ʧ��
                  4:����˽Կ�ļ�ʧ��
				 
				  
  Others: �ڲ�ʹ��     
***********************************************************/
SMM_INT SC_setup_server_ctx(SSL_CTX *ctx)
{   
	//(1)����CA֤���ļ�/Ŀ¼
    if (SSL_CTX_load_verify_locations(ctx, CAFILE_SERVER, CADIR_SERVER) != 1)
	{   
		return 1 ;
	}
	//(2)����Ĭ��CA֤���ļ�/Ŀ¼
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
	{
        return 2;
	}

	//(3)����֤����
    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE_SERVER) != 1)
	{
        return 3;
	}
	//(4)����˽Կ�ļ�
    if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE_SERVER, SSL_FILETYPE_PEM) != 1)
	{
        return 4 ; 
	}
	//(5)����֤����֤��ʽ(�����������öԿͻ�����Ч)
    //SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,
                     //  verify_callback);
	//(6)����֤����֤���(�����������öԿͻ�����Ч)
    //SSL_CTX_set_verify_depth(ctx, 4);
	//(7)����
    SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2 |
                             SSL_OP_SINGLE_DH_USE);
	//(8)����dh�ص�
    SSL_CTX_set_tmp_dh_callback(ctx, tmp_dh_callback);
	//(9)���ü����㷨�б�
    
   return 0 ; //���óɹ�
}

/********************************************************
  Function:       SC_setup_client_ctx
  Description:    ���÷�������SSL_CTX�ṹ(֤����֤/�����㷨)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   ctx  : SSL_CTX
				   

  Output:         
  Return:         1:����CA֤���ļ�/Ŀ¼ʧ��
                  2:����Ĭ��CA֤���ļ�/Ŀ¼ʧ��
				  3:����֤����ʧ��
                  4:����˽Կ�ļ�ʧ��
				  5:���ü����㷨�б�ʧ��
				  
  Others: �ڲ�ʹ��     
***********************************************************/
SMM_INT SC_setup_client_ctx(SSL_CTX *ctx)
{
    //(1)����CA֤���ļ�/Ŀ¼
    /*if (SSL_CTX_load_verify_locations(ctx, CAFILE_CLIENT, CADIR_CLIENT) != 1)
	{
	    return 1 ;
	}
	//(2)����Ĭ��CA֤���ļ�/Ŀ¼
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
	{
        return 2;
	}
	//(3)����֤����
    if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE_CLIENT) != 1)
    {
		return 3 ;
	}
	//(4)����˽Կ�ļ�
    if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE_CLIENT, SSL_FILETYPE_PEM) != 1)
	{
        return 4 ;
	}
	//(5)����֤����֤��ʽ
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	//(6)����֤����֤���
    SSL_CTX_set_verify_depth(ctx, 4);*/
	//(7)����
    SSL_CTX_set_options(ctx, SSL_OP_ALL|SSL_OP_NO_SSLv2);
 
   
	return 0 ;  //���óɹ�
}



/********************************************************
  Function:       SC_setup_cipher_ctx
  Description:    ���÷�������SSL_CTX�ṹ(֤����֤/�����㷨)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   ctx  : SSL_CTX
				   

  Output:         
  Return:         0:���ü����㷨�б�ɹ�
		  1:���ü����㷨�б�ʧ��
				  
  Others: �ڲ�ʹ��     
***********************************************************/
SMM_INT SC_setup_cipher_ctx(SSL_CTX *ctx)
{
   //(8)���ü����㷨�б�
    if (SSL_CTX_set_cipher_list(ctx, CIPHER_LIST_CLIENT) != 1)
	{
            return 1 ;
	}
	
    return 0 ;

}


/********************************************************
  Function:       SC_mallocarray
  Description:    ���������ڴ�ռ�
  Calls:          malloc
  Called By:      SC_socket
                  SC_accept
  Table Accessed: 
  Table Updated:  
  Input:          ��      
                   


  Output:         
  Return:        �ɹ����������±�
                 �޿ɷ�����ڴ淵�أ�1
				 �ͻ������ӵ���Ŀ��������:-2
  Others:        �ڲ�ʹ��
***********************************************************/
SMM_INT SC_mallocarray(SMM_VOID)
{   
	SMM_INT i ;
	SMM_INT iReturn = -1 ;  // -1:��ʾ�޿ɷ�����ڴ�
	//(1)���������ڴ�ռ�(��Ҫ��SSL,SSL_CTX�ṹ)
    for (i=0 ;i<SOCKET_MAX;i++) 
	{
		//printf("malloc=%d\n",stSSLSocket[i].flag) ;
        if (stSSLSocket[i].flag != -1 ) //flag=-1:��ʾ����û�з����ڴ�ռ�
		{
			continue ;
		}
		else   //�����ڴ�
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
    
    //(2)��i>SOCKET_MAX,��˵�����ӵĿͻ��Ѿ���������
	if (i >= SOCKET_MAX)
	{
		return  -2 ;
	}
	
	return i  ;
}

/********************************************************
  Function:       SC_queryarray
  Description:    ��������(����������±�)
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
  Input:          ��      
                   


  Output:         
  Return:        �ɹ����������±꣬���򷵻أ�1
  Others:        �ڲ�ʹ��
***********************************************************/
SMM_INT SC_queryarray(SMM_INT iSocket)
{
	SMM_INT iReturn = -1 ;
    SMM_INT i ;
	//(1)��������,����socket��Ӧ�������±�
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
    //(2)�����±�(-1:��ʾ����)
	return iReturn ;
}
/********************************************************
  Function:       SC_freearray
  Description:    �ͷſ��е�����(SSL,SSL_CTX�ṹ)
  Calls:          free
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:          SMM_INT iSocket:�׽���      
                   


  Output:         
  Return:        ��
  Others:        �ڲ�ʹ��
***********************************************************/
SMM_VOID SC_freearray(SMM_INT iSocket)
{
	//SMM_INT i  ;
	SMM_INT j  ;
    for (SMM_INT i=0 ;i<SOCKET_MAX;i++)  //��������
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

    //(1)��յ�ǰԪ��
	/*stSSLSocket[iSocket].ssl = NULL  ; //��Ϊ��ʹ��SC_freearray�����ĵط��Ѿ��õ��������±�
    stSSLSocket[iSocket].ctx = NULL  ;
	stSSLSocket[iSocket].s         = -1 ;
	stSSLSocket[iSocket].sock_serv = -1 ;
	stSSLSocket[iSocket].flag = -1 ;*/
	//(2)����Ԫ��ǰ��
        /*j = SC_queryarray(iSocket) ;
        if (j == -1 )
        {
        	return ;
        }
        
	for (;j<SOCKET_MAX,j+1<SOCKET_MAX;j++)  //��������
	{   
		if (stSSLSocket[j].flag != -1)
		{       //printf("free=%d\n",stSSLSocket[j].flag) ;
			stSSLSocket[j].ssl =  stSSLSocket[j+1].ssl  ; 
			stSSLSocket[j].ctx  = stSSLSocket[j+1].ctx  ;
			stSSLSocket[j].s   =  stSSLSocket[j+1].s;
			stSSLSocket[j].sock_serv = stSSLSocket[j+1].sock_serv ;
			stSSLSocket[j].flag = stSSLSocket[j+1].flag ; 
		}
		else   //-1:��ʾ�Ѿ��������β
		{
			break ;
		}
	}*/
}


/********************************************************
  Function:       SC_init
  Description:    ��ʼ����
  Calls:          WSAStartup
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           ��  
                  
  Output:         
  Return:          1��ʾ��ʼ���ɹ�
				   2��ʾ��ʼ��socketʧ��
				   

  Others:        
***********************************************************/
SMM_ULONG  SC_init()   
{
	WSADATA wsaData;
	SMM_INT iReturn = 2 ;
    SMM_INT i ;
	//(1)��ʼ������
	for (i=0 ;i<SOCKET_MAX;i++)
	{
           stSSLSocket[i].flag      = -1 ; 
	   stSSLSocket[i].s         = -1 ;
	   stSSLSocket[i].sock_serv = -1 ; //-1:û��ʹ��,-2:��ʾ����û��ʹ��,��s�Ѿ�ʹ��
	}
    
	//(2)��ʼ��socket
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
  Description:    �����׽���
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
              SMM_ULONG ulAddressFamily:��ַ��
			  MM_ULONG ulType:socket����
			  SMM_ULONG ulAuth:1:��ʾ��֤ģʽ;��1:��ʾ��ʹ����֤ģʽ
              SMM_ULONG ulEncrypt 1:��ʾ����ģʽ;��1:��ʾ��ʹ�ü���ģʽ
			  bool isssl:��ʾ�Ƿ�ʹ��SSL��ȫͨѶ true:��ʾʹ��
              SMM_ULONG ulServer:1:��ʾ��������ʹ��;��1:��ʾ�ͻ���ʹ��
			  SMM_ULONG ulversion:ʹ��Э�� 1:SSLV3;2:TLSV1
  Output:      
  				   
  Return:    �ɹ�:�����׽���    
             2 ��֧�ָ�Э��
			 3 Э������ʧ��
			 4 ��ʼ��SSL_CTX�ṹʧ��
			 5 �����ڴ�ʧ��
			 6 ���ӵ��û���������
			 7 ����֤��ʧ��
			 8 ����˽Կ�ļ�ʧ��
			 9 ����socketʧ��
			 10 ����SSLʧ��
  Others: �ڷ���SOCKET��SSL������  
          SSLv3=5,TLS1=6; (��֪������汾�Ŷ�Ӧ����ֵ)
		  
 �޸ļ�¼:2003/04/02(Ϊʹ��udp��׼��)
          ��socket�����ĵ�����������0��Ϊstppe->p_proto 
***********************************************************/
SMM_INT SC_socket(SMM_ULONG ulAddressFamily,SMM_ULONG ulType
						,SMM_ULONG ulAuth,SMM_ULONG ulEncrypt
						,SMM_ULONG ulServer,SMM_ULONG ulVersion)
{
    SSL_METHOD *pMethod ;
    X509       *x509 = NULL ;
	SMM_INT    iSocket ;
   
    
	//(0)ȡ��Э������
	struct protoent *stppe;
    stppe = getprotobyname("tcp");   //ĿǰĬ��ʹ��tcp
       
    //(1)Ϊ��������ڴ�ռ�
    iSocket = SC_mallocarray() ;
	switch (iSocket)
	{
		case -1:      //�����ڴ�ʧ��
			 return 5 ;
			 break ;
		case -2:      //���ӵ��û���������
			 return 6 ;
			 break ;
	}
        

	//(3)������֤ģʽ/Э��汾
	if (ulAuth == SC_VERIFY_YES)                      //������֤ģʽ
	{
		//(2)����SSL��
	    SSLeay_add_ssl_algorithms() ;

        if (ulServer == SC_SERVER_YES)                //������ʹ��
		{
            switch(ulVersion)             //Э��汾
			{
				case SC_SSLV3:
					pMethod = SSLv3_server_method();//���÷�����ʹ��SSLV3Э��
					break;
				case SC_TLSV1:
					pMethod = TLSv1_server_method();//���÷�����ʹ��TLSV1Э��
					break;
				case SC_SSLV2:
                    pMethod = SSLv2_server_method();//���÷�����ʹ��SSLV2Э��
					break;
				case SC_SSLV23:
                    pMethod = SSLv23_server_method();//���÷�����ʹ��SSLV23Э��
					break;
				default:
					return 2 ;
					break;
			}
			
		}
		else                              //�ͻ���ʹ��
		{
			switch(ulVersion)             //Э��汾
			{
				case SC_SSLV3:
					pMethod = SSLv3_client_method() ;//���ÿͻ���ʹ��SSLV3Э��
					break ;
				case SC_TLSV1:
					pMethod = TLSv1_client_method() ;//���ÿͻ���ʹ��TLSV1Э��
					break ;
				case SC_SSLV2:
					pMethod = SSLv2_client_method() ;//���ÿͻ���ʹ��SSLV2Э��
					break ;
				case SC_SSLV23:
					pMethod = SSLv23_client_method() ;//���ÿͻ���ʹ��SSLV23Э��
					break ;
				default:
					return 2 ;
					break ;
			}
		}

		//(4)�ж�����Э��汾�Ƿ���ȷ(��ʱ����)
		/*
        if(pMethod->version != 5 && pMethod->version != 6)
		{
			return 3;
		}
		*/

        //(5)����SSL�����Ļ���
        stSSLSocket[iSocket].ctx            = SSL_CTX_new(pMethod) ;
		if (stSSLSocket[iSocket].ctx == NULL) 
		{
			return 4 ;
		}
		
	   //(6)ȡ������Э�����(ȡ������֤��)
	   //(6-1)���ط�����֤��/˽Կ�ļ�
	   if (ulServer == SC_SERVER_YES && ulAuth == SC_VERIFY_YES)
	   {
		    //SSL_CTX_set_verify(stSSLSocket[iSocket].ctx,SSL_VERIFY_NONE,NULL);
		    //SSL_CTX_set_options(stSSLSocket[iSocket].ctx,SSL_OP_NO_SESSION_RESUMPTION_ON_RENEGOTIATION) ;  //���ûỰ����
		    SC_setup_server_ctx(stSSLSocket[iSocket].ctx) ;
		    /*if (SSL_CTX_use_certificate_file(stSSLSocket[iSocket].ctx,"cert.pem"
				, SSL_FILETYPE_PEM) <= 0) 	//����֤���ļ�
			{
				return 6 ;
                //exit(3);
            }

		   if (SSL_CTX_use_PrivateKey_file(stSSLSocket[iSocket].ctx, "key.pem"
			 , SSL_FILETYPE_PEM) <= 0)      //����˽Կ�ļ�
		   {
			    return 7 ;
		        //exit(4);
		   }

		   if (!SSL_CTX_check_private_key(stSSLSocket[iSocket].ctx)) //У��֤�鹫Կ�Ƿ���˽Կ���
		   {
			   return 8 ;
		      //exit(5);
		   }*/
	   }
       //(6-2)���ؿͻ���֤��/˽Կ�ļ�
       if (ulServer == SC_CLIENT_YES && ulAuth == SC_VERIFY_YES)
	   {
		    SC_setup_client_ctx(stSSLSocket[iSocket].ctx) ;
		    //SSL_CTX_set_verify(stSSLSocket[iSocket].ctx,SSL_VERIFY_PEER,NULL);  //�ͻ�����֤������֤��
		    /*if (SSL_CTX_use_certificate_file(stSSLSocket[iSocket].ctx,"cert.pem"
				, SSL_FILETYPE_PEM) <= 0) 	//����֤���ļ�
			{
			    return 6 ;
                //exit(3);
            }

		   if (SSL_CTX_use_PrivateKey_file(stSSLSocket[iSocket].ctx, "key.pem"
			 , SSL_FILETYPE_PEM) <= 0)      //����˽Կ�ļ�
		   {
		        return 7 ;
		        //exit(4);
		   }

		   if (!SSL_CTX_check_private_key(stSSLSocket[iSocket].ctx)) //У��֤�鹫Կ�Ƿ���˽Կ���
		   {
		      return 8 ;
		      //exit(5);
		   }*/
	   }

	   //(7)��������Э�����(�����㷨)
	   if (ulEncrypt == SC_ENCRYPT_YES) //���ü���
	   {    
		    
                //SSL_CTX_set_options(stSSLSocket[iSocket].ctx,SSL_OP_ALL) ;
	        SC_setup_cipher_ctx(stSSLSocket[iSocket].ctx) ;
	   }
	   else
	   {

	   }
	   //(8)����socket�׽���
        stSSLSocket[iSocket].s   = socket(ulAddressFamily,ulType,stppe->p_proto) ; 
        if (stSSLSocket[iSocket].s == SOCKET_ERROR)
		{
			return 9 ;
		}

        //printf("socket=%d",stSSLSocket[iSocket].s) ; //����:��ʾsocketֵ
        stSSLSocket[iSocket].sock_serv = -2 ; //-2:��ʾ����û��ʹ��,��s�Ѿ�ʹ��
		//(9)����SSLͨ��
        stSSLSocket[iSocket].ssl = SSL_new(stSSLSocket[iSocket].ctx) ; //����SSL�׽���
		if (stSSLSocket[iSocket].ssl == NULL)
		{
			return 10 ;
		}

        if (ulServer == SC_CLIENT_YES)
		{
		    //SSL_set_verify(stSSLSocket[iSocket].ssl,SSL_VERIFY_PEER,NULL); //���ÿͻ�����֤��ʽ
		}
	}
	else  //������SSLͨѶ
	{
		stSSLSocket[iSocket].s   = socket(ulAddressFamily,ulType,stppe->p_proto) ;  //socket������������0��Ϊ
		//printf("SC_socket=%d\n",stSSLSocket[iSocket].s) ;  //����
		if (stSSLSocket[iSocket].s == SOCKET_ERROR)
		{
			return 9 ;
		}
		stSSLSocket[iSocket].sock_serv = -2 ; //-2:��ʾ����û��ʹ��,��s�Ѿ�ʹ��
		stSSLSocket[iSocket].ssl = NULL ; 
		stSSLSocket[iSocket].ctx = NULL ;
		
	} 
	
	//(9)����socket�׽���
	stSSLSocket[iSocket].flag = iSocket ;
	return iSocket ;

}


/********************************************************
  Function:       SC_bind
  Description:    ��ip�Ͷ˿�
  Calls:          bind
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket:�׽���
                  SMM_INT iPort  :�˿ں�
  Output:         
  Return:         
                  0:�󶨳ɹ�
				  -1:��ʾû�и���socket
				  ����:�������
  Others:      
***********************************************************/

SMM_INT SC_bind(SMM_INT iSocket,SMM_INT iPort)
{
    struct sockaddr_in stServer;
	SMM_INT iError ;
    SMM_INT iSSL ;
    
	//(1)�������в����׽��ֶ�Ӧ���±�
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}
	//(2)�󶨶˿�
	stServer.sin_family      = AF_INET ;
	stServer.sin_addr.s_addr = htonl(INADDR_ANY) ;
	stServer.sin_port        = htons(iPort) ;
	
	//printf("SC_bind=%d\n",stSSLSocket[iSSL].s) ; //����
    iError = bind(stSSLSocket[iSSL].s,(struct sockaddr*)&stServer,sizeof(stServer));
	
	return iError ;
}

/********************************************************
  Function:       SC_listen
  Description:    ��������������ͻ�����������
  Calls:          listen
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket:�׽���
				  SMM_INT iMaxnum:���������ȴ�������
  Output:         
  Return:         
                  0:��ȷ
				  -1:��ʾû�и���socket
				  ����:���ش������
  Others:      
***********************************************************/
SMM_INT SC_listen(SMM_INT iSocket,SMM_INT iMaxnum)
{
	 SMM_INT iError ;
	 SMM_INT iSSL ;
     
	 //(1)�������в����׽��ֶ�Ӧ���±�
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}
	 //(2)����
	 
	// printf("SC_listen=%d\n",stSSLSocket[iSSL].s) ; //����
	 
	 iError = listen(stSSLSocket[iSSL].s,iMaxnum);
	 return iError ;
}

/********************************************************
  Function:       SC_accept
  Description:    �������ȴ���������
  Calls:          accept
                  SC_queryarray
				  SC_mallocarray
				  SSL_accept
				  SSL_set_fd
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket:�׽���
				 
  Output:         
  Return:         
                  >=0:socket�׽���(�ͻ���)
				  -1:���������������
				  -2:�����ڴ�ʧ��
				  -3:���ӵ��û���������
				  -4:����accept����ʧ��
				  -5:����SSL_set_fd�󶨺���ʧ��
				  -6:����SSL_accept����ʧ��
				  -7:û�и�����socket
  Others:      
***********************************************************/
SMM_INT SC_accept(SMM_INT iSocket)
{
	struct sockaddr_in stClient_S ;
    SMM_INT iError = 0 ; 
    SMM_INT iServer_socket ;
    SMM_INT iClient_Socket ;
    SMM_INT iClient ;
	
	//(1)�������в����׽��ֶ�Ӧ���±�
	iServer_socket = SC_queryarray(iSocket) ; 
	//printf("server_socket=%d",iServer_socket) ;//����
	if (iServer_socket == -1)
	{
		return -7 ;
	}
	
	//(2)sock_serv:-2:��ʾ������ṹ�и�����û��ʹ��,��s�Ѿ�ʹ��
	
        iClient_Socket  = SC_mallocarray() ;
       // printf("client_socket=%d",iClient_Socket ) ; //����
        switch (iClient_Socket)
	{
		case -1:      //�����ڴ�ʧ��
			 return -2 ;
			 break ;
		case -2:      //���ӵ��û���������
			 return -3 ;
			 break ;
	}
	
	
	//(3)�������ȴ���������
	iClient = sizeof(stClient_S) ;
    if (stSSLSocket[iServer_socket].ssl != NULL)       //ʹ��SSL��ȫͨѶ(ʹ�÷�������SSL��)
	{   
		//(3-1)�ȴ��ͻ���socket��������
		stSSLSocket[iClient_Socket].sock_serv = accept(stSSLSocket[iServer_socket].s
			,(struct sockaddr *) &stClient_S,&iClient) ;
		if (stSSLSocket[iClient_Socket].sock_serv == SOCKET_ERROR)
		{
			return -4 ;
		}
		printf("sock_serv=%d",stSSLSocket[iClient_Socket].sock_serv) ; //����accept����ֵ
        //(3-2)��socket��ssl
        iError = SSL_set_fd(stSSLSocket[iServer_socket].ssl,stSSLSocket[iClient_Socket].sock_serv);
		if (iError<0)
		{
			return -5 ;
		}
        //(3-3)�ȴ��ͻ���ssl��������
		iError = SSL_accept(stSSLSocket[iServer_socket].ssl) ;
		printf("ssl_accept=%d",iError) ; //����SSL_accept����ֵ
		if (iError <0 )
		{   
			SSL_shutdown(stSSLSocket[iServer_socket].ssl) ; 
			return -6 ;
		}
		
		stSSLSocket[iClient_Socket].flag = iClient_Socket ;   //����
	}
	else   //��ʹ��SSLͨѶ
	{
        stSSLSocket[iClient_Socket].sock_serv = accept(stSSLSocket[iServer_socket].s
			,(struct sockaddr *) &stClient_S,&iClient) ;
	stSSLSocket[iClient_Socket].flag = iClient_Socket ;   //����		
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
    
	//(4)����ֵ�׽���
	return iClient_Socket ;

}

/********************************************************
  Function:       SC_connect
  Description:    �ͻ������ӷ�����
  Calls:          connect
                  SSL_connect
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket          :�׽���
				  const SMM_CHAR FAR *pcIP :IP��ַ
				  SMM_INT iPort            :�˿�
  Output:         
  Return:         
                  0:��ȷ
				  -1:��ʾû�и�����socket
				  -2:��ʾ����SSL_set_fdʧ��
				  -3:��ʾ����SSL_connectʧ��
				  ����:���ش������
  Others:      
***********************************************************/
SMM_INT SC_connect(SMM_INT iSocket,const SMM_CHAR FAR *pcIP,SMM_INT iPort )
{
	SMM_INT  iError = 0 ;
    struct sockaddr_in stClient_S ;
	SMM_INT iSSL ;
    
	//(1)�������в����׽��ֶ�Ӧ���±�
	iSSL = SC_queryarray(iSocket) ;
	
	if (iSSL == -1)
	{
		return -1 ;
	}
    //(2)���ӷ�����    
    stClient_S.sin_family      = AF_INET ;
	stClient_S.sin_addr.s_addr = inet_addr(pcIP) ;
	stClient_S.sin_port        = htons(iPort) ;
	if (stSSLSocket[iSSL].ssl != NULL)     //ʹ��SSL��ȫͨѶ
	{   
		//(2-1)����socket������
        iError = connect(stSSLSocket[iSSL].s,(struct sockaddr *)&stClient_S,sizeof(struct sockaddr)) ;
		if (iError != 0)
		{
			return SOCKET_ERROR ;
		}
        //printf("iError=%d",iError) ; //����connect����
		//(2-2)��socket��ssl
		iError = SSL_set_fd(stSSLSocket[iSSL].ssl,stSSLSocket[iSSL].s) ;
        if (iError != 1)
		{
			return -2 ;
		}
		//(2-3)����ssl
		iError = SSL_connect(stSSLSocket[iSSL].ssl) ;
		if (iError != 1)
		{
			return -3 ;
		}
	}
	else                                  //��ʹ��SSL��ȫͨѶ
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
  Description:    ��������
  Calls:          send
                  SC_write
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket            :�׽���
				  const char FAR *pcBuffer   :���ݻ�����
				  SMM_INT iLen               :���ݳ���
				  SMM_INT iFlags             :0��ʾtcp
				  const struct sockaddr FAR *pTo ����udp��Ч
				  SMM_INT iTolen             ����udp��Ч
				  SMM_INT iServer            SC_SERVER_YES:������ʹ��
				                             SC_CLIENT_YES:�ͻ���ʹ��
  Output:         
  Return:         
                  �ɹ����ط������ݵĳ���
				  -1:û�и�����socket

				  ���ɹ����ش������
  Others:      
***********************************************************/
SMM_INT SC_send(SMM_INT iSocket, const SMM_UCHAR FAR *pcBuffer,SMM_INT iLen
				, SMM_INT iFlags,const struct sockaddr FAR *pTo,SMM_INT iTolen,SMM_INT iServer)
{
     SMM_INT iLength ;
     SMM_INT iSSL ;
     
	//(1)�������в����׽��ֶ�Ӧ���±�
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}

     if (stSSLSocket[0].ssl != NULL)  //ʹ��SSL��ȫͨѶ
	 {  
         iLength = SSL_write(stSSLSocket[iSSL].ssl,pcBuffer,iLen) ;
	 }
	 else                               //��ʹ��SSL��ȫͨѶ
	 {
		if (iServer == SC_SERVER_YES)   //��������ͻ��˷�������
		{
			 iLength = send(stSSLSocket[iSSL].sock_serv,(char *)pcBuffer,iLen,iFlags) ;
		}
		else                            //�ͻ���ʹ��
		{
		   iLength = send(stSSLSocket[iSSL].s,(char *)pcBuffer,iLen,iFlags) ;
		}
	 }
    
	 //(2)>=0���ط������ݵĳ���;����Ϊ���ʹ���
	 return iLength ;
}

/********************************************************
  Function:       SC_recv
  Description:    ��������
  Calls:          recv
                  SSL_read
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  SMM_INT iSocket            :�׽���
				  const char FAR *pcBuffer   :����
				  SMM_INT iLen               :���ݳ���
				  SMM_INT iFlags             :0��ʾtcp
				  struct sockaddr FAR *pFrom :����udp��Ч
				  SMM_INT FAR *pFromlen      :����udp��Ч
				  iServer                    :SC_SERVER_YES:������ʹ��
				                              SC_CLIENT_YES:�ͻ���ʹ��
  Output:         
  Return:         
                  >0 �ɹ����ؽ������ݵĳ���
				  =0 �����ж�(�Ѿ��Ͽ�������)
				  -1:û�и�����socket
				  ���ɹ����ش������
  Others:      
***********************************************************/
SMM_INT SC_recv( SMM_INT iSocket, SMM_UCHAR FAR *pcBuffer,SMM_INT iLen
				,SMM_INT iFlags,struct sockaddr FAR *pFrom, SMM_INT FAR *pFromlen,SMM_INT iServer)
{
	SMM_INT iLength = -2;
	SMM_INT iSSL ;
    
	//(1)�������в����׽��ֶ�Ӧ���±�
	iSSL = SC_queryarray(iSocket) ;
	if (iSSL == -1)
	{
		return -1 ;
	}

	if (stSSLSocket[0].ssl != NULL)       //ʹ��SSL��ȫͨѶ
	{
		iLength = SSL_read(stSSLSocket[iSSL].ssl,pcBuffer,iLen) ;
	}
	else                                    //��ʹ��SSL��ȫͨѶ
	{
		if (iServer == SC_SERVER_YES)  //���������͵����ͻ���
		{
			//printf("SC_recv=%d\n",stSSLSocket[iSSL].sock_serv) ;
            iLength = recv(stSSLSocket[iSSL].sock_serv,(char *)pcBuffer,iLen,iFlags) ;
		}
		else                           //�ͻ���ʹ��
		{
			 iLength = recv(stSSLSocket[iSSL].s,(char *)pcBuffer,iLen,iFlags) ;
		}
		  
	}
    //(2)iLength>0���ؽ������ݵĳ���;����Ϊ���մ���
	return iLength ;
}

/********************************************************
  Function:       SC_ioctl
  Description:    �趨socketģʽ
  Calls:          ioctlsocket 
  Called By:      
  Table Accessed: 
  Table Updated: 
  Input:           
                   SMM_INT   iSocket:socket������ 
				   SMM_LONG  cmd    :��ȡ���趨 Socket ������������ָ�� 
                   SMM_ULONG argp   :ָ�����ָ�� ����:��ʾ������
				                                  0 :��ʾ����
                   

  Output:         
  Return:         
                  0: ���óɹ�
				  -1:���ô���
  Others:      ��SSL_accept����ʹ���г�ͻ(����Ҳ����/��ʱû��)
***********************************************************/
/////////////////////////////////////////////////////////////////////////
SMM_INT SC_ioctl(SMM_INT iSocket,SMM_LONG lCmd,SMM_ULONG pArgp)
	{
		SMM_INT iErr = -1;	
		SMM_INT iSSL ;	
                SMM_ULONG ulBlock ;  //���������Ƿ�������־����
                
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

		switch(lCmd)			//�����û����������������ж��壬ֻ��������/������
		{
			case FIONBIO:      //��������/������ģʽ
				iErr = ioctlsocket(stSSLSocket[iSSL].s,FIONBIO,&ulBlock);
				break;
			default:          //����ģʽ��ʱ������
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
  Description:    ��ʼ��select������fd_set��¼��
  Calls:          FD_ZERO
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           

				   pFd       fd_set��¼��



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
  Description:    ����δ����socket����Ŀ
  Calls:          select
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                   SMM_INT iNfds:���Ժ��ԣ�����Berkeley socket����
				   SMM_INT iRwe : SC_SELECTREAD_YES�ȴ��ɶ���socket���ָ��
				                  SC_SELECTWRITE_YES�ȴ���д��socket���ָ��
				                  SC_SELECTEXP_YES:�쳣
				   timeout      :ָ���ȴ�ʱ��
				   fd_set *pFd  :�ļ�������


  Output:         
  Return:         
                  ����δ����socket�����������Ŀ
				  -1:����ʧ��
  Others:      
***********************************************************/
SMM_INT SC_select(SMM_INT iNfds,SMM_INT iRwe,const struct timeval *pTimeout,fd_set *pFd)
	{
		SMM_INT  iNready = -1 ;

		switch(iRwe)
		{
			case 0:    //�ɶ�
				iNready=select(0,pFd,NULL,NULL,NULL);
				//printf("select=%d",iNready) ;
				 break ;
			case 1:   //��д
				iNready=select(0,NULL,pFd,NULL,NULL);
				break;
			case 2:  //�쳣
					iNready=select(0,NULL,NULL,pFd,NULL);
					break;

		}
       
		return iNready ;
	}
/********************************************************
  Function:       SC_close
  Description:    �ͷ�ͨѶ����,���е���رյĹ���
  Calls:          closesocket
                  shutdown
                  SSL_shutdown
                  SSL_free
				  SSL_CTX_free
  Called By:     
  Table Accessed: 
  Table Updated:  
  Input:           
                   stSocket_S         socket������
                   iHow               SD_SEND:�ر�send,SD_RECEIVE:�ر�recv
				                      SD_NO:˫��ر�
                   iMain              1:��������accecpt���صĿͻ�socket
                                      0:����socket

  Output:         
  Return:        0  :�ɹ�����   
                 1  :�޴�socket 
				 2  :����shutdown/closesocket����ʧ��
				 3  :����WSACleanup����ʧ��
				 4  :����SSL_shutdown����ʧ��
				 5  :����ԭ��

  Others:      
***********************************************************/
SMM_INT SC_close(SMM_INT iSocket,SMM_INT iHow,SMM_INT iMain)
	{
		SMM_INT iErr   = 0 ;
		SMM_INT iSSL = 5 ;

        //(1)�������в����׽��ֶ�Ӧ���±�
	    iSSL = SC_queryarray(iSocket) ;
        if (iSSL == -1)
		{
			return 1 ;
		}

        //(2)�ر�socket/ssl
		if(stSSLSocket[0].ctx == NULL) //��ʹ��SSLͨѶ
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
					 if (iMain == 1) //���ڷ�������accecpt���صĿͻ�socket
					{      
						//printf("sock=%d\n",stSSLSocket[iSSL].sock_serv) ;
						iErr = closesocket(stSSLSocket[iSSL].sock_serv);
					}
					else            //����socket
					{
					     iErr = closesocket(stSSLSocket[iSSL].s);	
					     iErr = WSACleanup();
						if (iErr == SOCKET_ERROR) //�жϵ���WSACleanup�Ƿ�ɹ�
						{
							return 3 ;
						}
					}
					break ;
			}

			if (iErr == SOCKET_ERROR) //�жϵ���shutdown�Ƿ�ɹ�
			{
				return 2 ;
			}

			
		}
		else                             //ʹ��SSLͨѶ
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
					
					if (iMain == 1) //���ڷ�������accecpt���صĿͻ�socket
					{
						iErr = closesocket(stSSLSocket[iSSL].sock_serv);
					}
					else            //����socket
					{
					     iErr = closesocket(stSSLSocket[iSSL].s);
					     iErr = WSACleanup();
						if (iErr == SOCKET_ERROR) //�жϵ���WSACleanup�Ƿ�ɹ�
						{
							return 3 ;
						}	
					}
					break ;
			 }

			if (iErr == SOCKET_ERROR) //�жϵ���shutdown/closesocket�Ƿ�ɹ�
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

		//(3)�ͷŸ��׽���ռ�õ�������Դ
		//printf("sc_freearray=%d",iSSL) ;
		SC_freearray(iSSL) ;

		return iErr ;
		
	}


/***********************************************************/
//������Э�̺���(��Ҫ����)



/********************************************************
  Function:       SC_isset
  Description:    �ж�ָ����socket�Ƿ����ļ���������
  Calls:          FD_ISSET 
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : �׽���
				   *pFd     : fd_set��
				   iClient  : 1:�����������ͻ���
				              0:����������
			       


  Output:         
  Return:         
                  iSocket��fd_set���з��� 1
				  -1:��ʾû�и�����socket
				  0 :����ʧ��
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

		if (iClient == 1 )  //�����������ͻ���
		{
          iNready = FD_ISSET(stSSLSocket[iSSL].sock_serv,pFd) ;
		}
		else   //����������/�ͻ���
		{
		   iNready = FD_ISSET(stSSLSocket[iSSL].s,pFd) ;
		}

		return iNready ;


	}


/********************************************************
  Function:       SC_fdset
  Description:    ��ָ����socket���ӵ��ļ���������
  Calls:          FD_SET
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : �׽���
				   iClient  : 1:�����������ͻ���
				              0:����������
                   pFd      :fd_set��

  Output:         
  Return:          ��   
                  
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

		if (iClient == 1 )  //�����������ͻ���
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
  Description:    ����ļ���������ָ����socket
  Calls:          FD_CLR
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : �׽���
				   iClient  : 1:�����������ͻ���
				              0:����������
                   pFd      : fd_set��

  Output:         
  Return:         ��
                  
				  
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

	if (iClient == 1)  //�ͻ���socket
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
  Description:    �õ�ip��ַ
  Calls:          getpeername
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   iSocket  : �׽���
				  

  Output:         
  Return:         ��
                  
				  
  Others: �ڲ�ʹ��     
***********************************************************/
unsigned long SC_getip(SMM_INT  iSocket,char *ipaddr,SMM_USHORT *port)
    {
     struct sockaddr_in name;
     //size_t namelen = sizeof(name);
     int      namelen = sizeof(name) ;
     unsigned long ip = 0;
	 SMM_INT iSSL ;
	 SMM_INT iReturn ;
	 SMM_CHAR cip[19] ; //�洢ip
	 //SMM_INT iPort; //�洢�˿�

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
       //printf("ipaddr=%s",ipaddr) ; //����ip
       port = &name.sin_port ;
   
       //printf("port=%d",*port) ;
       //ip = inet_addr(ipaddr);
     }

    
     return 0;  //��ȷ
    }

//////////////////////////////////////////////////////////
//��װ�Թ����ڴ�ķ�װ  
/********************************************************
  Function:       CreateFileMappingC2S
  Description:    ��������������(�ͻ����������)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:��ʾ���������ڴ�ɹ�
		  -1:��ʾ���������ڴ�ʧ��

  Others:      
***********************************************************/
int  CreateFileMappingC2S()
{
	hShareC2S = CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//������������С
		"ServerJNITLVModuleC2S"	//�����ռ䣺ServerJNITLVModule
		);
	//����ʧ��
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
  Description:    ��������������(��������ͻ���)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:��ʾ���������ڴ�ɹ�
		  -1:��ʾ���������ڴ�ʧ��

  Others:      
***********************************************************/
int CreateFileMappingS2C()
{
	hShareC2S = CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//������������С
		"ServerJNITLVModuleS2C"	//�����ռ䣺ServerJNITLVModule
		);
	//����ʧ��
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
  Description:    д����������:C2S(�ͻ��˵�������)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:��ʾд�����ڴ�ɹ�
		  -1:��ʾд�����ڴ�ʧ��

  Others:      
***********************************************************/
//��ȫ�ֱ���m_Data_Transfer_C2S_Struct��������������Transfer_C2S_Struct
int SetTransfer_C2S_StructtoMapFileC2S(tagSMM_c2s *m_Data_Transfer_C2S_Struct)
{
	//��ȡ����������
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//��ȡ�������������ڴ洰�ھ��
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

	//��ȡ�ź���
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	//д������
	//for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    //{
    	memcpy((unsigned char*)lpMapAddress,(unsigned char*)m_Data_Transfer_C2S_Struct,sizeof(tagSMM_c2s));
       //((unsigned char*)lpMapAddress)[i] = ((unsigned char*)m_Data_Transfer_C2S_Struct)[i];
    //}

	//�ͷ��ź���
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return 1;
}

/********************************************************
  Function:       SetTransfer_C2S_StructtoMapFileS2C
  Description:    д����������:C2S(�ͻ��˵�������)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:��ʾд�����ڴ�ɹ�
		  -1:��ʾд�����ڴ�ʧ��

  Others:      //S2C(��ʱ����)
***********************************************************/

//��ȫ�ֱ���m_Data_Transfer_S2C_Struct��������������Transfer_S2C_Struct
int SetTransfer_S2C_StructtoMapFileS2C(tagSMM_s2c *m_Data_Transfer_S2C_Struct)
{
	//��ȡ����������
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//��ȡ�������������ڴ洰�ھ��
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

	//��ȡ�ź���
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	//д������
	//for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
    //{
        memcpy((unsigned char*)lpMapAddress,(unsigned char*)&m_Data_Transfer_S2C_Struct,sizeof(tagSMM_s2c)) ;
       //((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_Data_Transfer_S2C_Struct)[i];
    //}

	//�ͷ��ź���
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return 1;
}


/********************************************************
  Function:       GetTransfer_C2S_StructfromMapFileC2S
  Description:    �ӹ�����������ȡ����TLVStruct:C2S(�ͻ��˵�������)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:��ʾ�������ڴ�ɹ�
		  -1:��ʾ�������ڴ�ʧ��

  Others:      //C2S(�ͻ��˵�������:��ʱ����:���Գɹ�)
***********************************************************/
int GetTransfer_C2S_StructfromMapFileC2S( tagSMM_c2s *m_Data_Transfer_C2S_Struct)
{
	//��ȡ����������
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//��ȡ�������������ڴ洰�ھ��
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

	//��ȡ�ź���
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	//��������
	//for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    //{
    	memcpy((unsigned char*)m_Data_Transfer_C2S_Struct,(unsigned char*)lpMapAddress,sizeof(tagSMM_c2s)) ;
       //((unsigned char*)&m_Data_Transfer_C2S_Struct)[i] = ((unsigned char*)lpMapAddress)[i];
    //}

	//�ͷ��ź���
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return 1;
}


/********************************************************
  Function:       GetTransfer_S2C_StructfromMapFileS2C
  Description:    �ӹ�����������ȡ����TLVStruct:C2S(���������ͻ���)
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           
                  
				   
			       


  Output:         
  Return:         
                  1:��ʾ�������ڴ�ɹ�
		  -1:��ʾ�������ڴ�ʧ��

  Others:      //S2C(���������ͻ���:δ����)
***********************************************************/
int GetTransfer_S2C_StructfromMapFileS2C(tagSMM_s2c *m_Data_Transfer_S2C_Struct)
{
	//��ȡ����������
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		printf("Could not Open file-mapping object.");
		return -1;
	}
	//��ȡ�������������ڴ洰�ھ��
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

	//��ȡ�ź���
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	//��������
	//for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
   //{
    	memcpy((unsigned char*)m_Data_Transfer_S2C_Struct,(unsigned char*)lpMapAddress,sizeof(tagSMM_s2c)) ;
       //((unsigned char*)&m_Data_Transfer_S2C_Struct)-> = ((unsigned char*)lpMapAddress)[i];
    //}

	//�ͷ��ź���
	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return 1;
}


/********************************************************
  Function:       SC_isnull
  Description:    �ж��ַ������Ƿ�Ϊ��
  Calls:          
  Called By:      
  Table Accessed: 
  Table Updated:  
  Input:           char *cData:Ҫ�Ƚϵ�����ָ��
                   int iLen   :���ݳ���
                  
				   
			       


  Output:         
  Return:         
                  1:Ϊ��
		  0:��Ϊ��

  Others:      //S2C(���������ͻ���:δ����)
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



