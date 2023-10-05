/*************************************************************
  Copyright (C)
  File name:  
  Author: 
  Version:  
  Date: 2003-3-28
  Description:    此文件是对多线程通信的测试程序
  Others:           
  Function List:  
  (1)ITDQ_int
  (2)IDDQ_CreateQueue
  (3)ITDQ_Read
  (4)ITDQ_Write
  (5)ITDQ_Delete
  History:          
    1. Date:   2003-04-01
       Author: xuhui
       Modification: First version
    2. ...
**************************************************************/
//#include "smm_ssl.h"   //ssl通讯头文件
#include "test.h"   //队列
#include "smm_api.cpp"    //ssl接口函数

#define   USE_SSL       0         //0:不使用SSL通讯 1:表示使用SSL                                

DWORD WINAPI ComProc(LPVOID lpParameter);						// 通信线程声明
DWORD WINAPI ComProc_Read(LPVOID lpParameter) ;                 //服务器阻塞于读共享内存



CRITICAL_SECTION cs;

//SMM_UCHAR *pSize;      //(暂时不用)
SMM_INT  iID[4];													//队列ID
//SMM_CHAR *pSize=(char*)malloc(sizeof(Data_Size));
//int test(void) ;
//SMM_CHAR pData[1][Data_Size];
HANDLE hShare;  
HANDLE hMapFile ;
LPVOID lpMapAddress;           //MapViewOfFile返回值
TLVStruct m_Data;  

int main(int argc, char* argv[])
{
	//pSize =(unsigned char*)malloc(sizeof(Data_Size)) ; (在队列上使用)

    char a =' ' ;

   //建立队列(暂时不用) 
	/*ITDQ_Init();
    iID[2]=ITDQ_Create(0,Data_Size);
	iID[3]=ITDQ_Create(0,Data_Size);*/

    //(1)建立共享内存(客户端到服务器)
	CreateFileMappingC2S() ;  //客户端到服务器
	CreateFileMappingS2C() ;  ////服务器到客户端


	InitializeCriticalSection(&cs);

    //(2)建立线程
	CreateThread(NULL,0,ComProc_Read,NULL,0,NULL);	
	CreateThread(NULL,0,ComProc,NULL,0,NULL);                   //创建通信线程
	//Sleep(INFINITE);
	//Sleep(1000);

//	test() ;
				//创建读共享内存线程
    
	//Sleep(INFINITE);
    

 
	while (a !='z') 
	{
		a = getchar() ;
	}


	DeleteCriticalSection(&cs);
	return 1;
}


////////////////////////////////////////////////////////////////////
//定义全局变量(王彦杰在多线程时使用)
SMM_INT iMaxClient[FD_SETSIZE] ;//保存客户端连接的数组
SMM_INT iMax = -1 ;                 //数组中的最大下标
fd_set fset,allset ;             //描述集

///////////////////////////////////////////////////////////////////
//通讯线程(客户端连接服务器:阻塞于写共享内存)
DWORD WINAPI ComProc(LPVOID lpParameter)
//int test(void)
{
	    int n = 0;
		SMM_INT iSocket ;               //服务器
		SMM_INT isock_cli ;             //客户端
		SMM_INT iReturn ;
		//SMM_INT iMaxClient[FD_SETSIZE] ;//保存客户端连接的数组 (已定义为全局变量)
		//SMM_INT iMax ;                 //数组中的最大下标
		//fd_set fset,allset ;             //描述集
		SMM_INT iNready ;				//符合条件的socket最大数目
		SMM_UCHAR	buf[1024] = {'\0'} ;		//发送接收包
		SMM_INT iLen;                  //等待socket地址族长度
		SMM_INT j;						//循环变量
        SMM_UCHAR cRecv[1024] ={'\0'};
        SMM_INT  iRecv = 0 ;
        SMM_ULONG ulArgpN = 1 ;
        SMM_INT i=1 ;
        SMM_INT iSet ;
        SMM_INT  ip ;
      
        //测试
        SMM_CHAR  pcBuffer[100000]={'\0'} ;
		SMM_CHAR  *pcIP  ;              //客户端发送到服务器ip
		SMM_USHORT  *piPort  ;          //端口
        SMM_INT iLoop =0 ;              //循环:用于控制socket数组
	
        SMM_CHAR   b =' ' ;
        //(0)定义
        //用于存储客户端返回服务端的数据
        tagSMM_c2s  *st_C2S;
		tagSMM_c2s  *st_C2S01;
        
       //用于存储要发送到客户端的数据
        tagSMM_s2c *st_S2C;

        //(1)初始化库
		SC_init();	
		st_C2S = (tagSMM_c2s *)malloc(sizeof(tagSMM_c2s)) ;
		st_C2S01 = (tagSMM_c2s *)malloc(sizeof(tagSMM_c2s)) ;
		st_S2C = (tagSMM_s2c *)malloc(sizeof(tagSMM_s2c)) ;
		pcIP =  (SMM_CHAR *)malloc(sizeof(SMM_CHAR)) ;
		piPort = (SMM_USHORT*)malloc(sizeof(SMM_USHORT)) ;
        
	
	    //(2)创建socket
	if (USE_SSL == 1)  //使用SSL通讯
		{
			iSocket = SC_socket(AF_INET,SOCK_STREAM,SC_VERIFY_YES,SC_ENCRYPT_NO
						,SC_SERVER_YES,SC_SSLV3) ;      //创建可靠验证的基于服务器端的socket描述字
		}
		else              //普通socket
		{

				iSocket = SC_socket(AF_INET,SOCK_STREAM,SC_VERIFY_NO,SC_ENCRYPT_NO
						,SC_SERVER_YES,SC_SSLV3) ;      //创建普通的服务器端的socket描述字
		}

       // printf("SC_socket=%d",iSocket) ;
      
		//(3)绑定
		if(SC_bind(iSocket,5000) != 0)
		{
			 printf("bind is error!\n") ;		//绑定错误
			 exit(1) ;
		}
        //(4)监听
		iReturn = SC_listen(iSocket,5) ;
		if (iReturn !=0)
		{
		  printf("listen error") ;
		  exit(1) ;
		}
	
		iLen=sizeof(sockaddr_in) ;

		
		//(5)设置socket属性为非阻塞模式
		if (USE_SSL == 1)   //使用非阻塞模式 (SSL)
		{
	        iReturn = SC_ioctl(iSocket,FIONBIO,ulArgpN) ;	//设置非阻塞方式(与SSL_accept有冲突)
			//printf("SC_ioctl01=%d\n",iReturn) ;
		}
		else    //普通socket
		{
			 iReturn = SC_ioctl(iSocket,FIONBIO,ulArgpN) ;
		}
		
		//(6)设置socket选项(关闭延时)
		int itry ;
		itry = SC_setsockopt(iSocket,1,1,4) ;  //关闭socket延时4秒
		printf("setsockopt=%d\n",itry) ;

		//(7)初始化文件集/socket保存数组
		iMax=-1 ;
		for(j=0;j<FD_SETSIZE;j++)						//循环判断最大连接数
		{
			iMaxClient[j]=-1 ;
		}
	
		

		SC_selectinit(&allset);  //清空fd_set

		SC_fdset(iSocket,&allset,0) ; //增加服务器socket到fd_set集中
		
       //(8)循环等待请求和处理客户端请求
		while(1)						
		{   
		    Sleep(10) ;
            fset = allset ;
			//(8-1)返回可读的socket数目,并已经有客户连接
			//iNready=SC_select(0,SC_SELECTREAD_YES,-1,&fset) ;  //阻塞模式:阻塞1秒
			iNready=SC_select(0,SC_SELECTREAD_YES,0,&fset) ;    //非阻塞模式
			printf("iNready=%d\n",iNready) ;

			//测试
			printf("server-isset=%d\n",SC_isset(iSocket,&fset,0)) ;
			//(8-2)判断socket是否在文件集中(服务器)
			if (SC_isset(iSocket,&fset,0)>0)       //接收客户端请求
			{       SC_fdset(iSocket,&fset,0) ; //增加服务器socket到fd_set集中
					iLen=sizeof(SOCKADDR_IN);
					isock_cli  = SC_accept(iSocket) ;  //等待客户连接

					//(8-3)向java服务器提交刚连接上的客户端ip地址(暂时不用)
                    //(8-3-1)取出ip
				   /*ip= SC_getip(isock_cli,pcIP,piPort) ;
				   if (ip == 0)  //取出ip成功
				   {
                        printf("ip=%s\n",pcIP) ;
					    printf("port=%d",*piPort) ; //测试
                        strcpy(st_C2S->cIp,pcIP) ;
                        st_C2S->uiPort = *piPort ;
						st_C2S->iFlag  = 0 ;  //0:客户端刚连接上服务器
						//写入共享内存
                        SetTransfer_C2S_StructtoMapFileC2S(st_C2S) ;
				   }
				   else
				   {
					   printf("不能向服务器提交客户端ip地址\n") ;
				   }
					
				   */

					printf("accept_iLoop=%d\n",iLoop) ;

					if (isock_cli <0)  //接收不对
					{
                        //printf("server can not accept client request ");
						continue ;
					}

					printf("accept=%d\n",isock_cli) ;

                   	/*while (b !='a')   //测试SC_accept函数(在此等待用户响应)
						{
							b = getchar() ;
						}*/

					for(j=0;j<FD_SETSIZE;j++)          //遍历数组,并存储socket值 
					{
						if(iMaxClient[j]<0)
						{
							iMaxClient[j] = isock_cli ; //保存socket
							break;
						}
						
					}

					if(j>=FD_SETSIZE)				    //超过记录集中socket最大数
					{
						printf("连接客户端太多!\n") ;
					}
                     
					if (isock_cli >= 0)
					{
					     SC_fdset(isock_cli,&allset,1) ;  //增加客户端socket值到文件集中
					}

					if(j>=iMax)                       //更新最大用户数
					{
						iMax=j ;
					}

            }
            
			printf("iMax=%d\n",iMax) ;
			
			//(8-4)检查所有用户连接,并处理接收客户端数据
			for(iLoop=0;iLoop<=iMax;iLoop++)    //处理没有必要(在select方式已经得到) 原j=0							
			{   
				//向所有用户发送数据
				isock_cli = iMaxClient[iLoop] ;
				printf("Client=%d,iLoop=%d\n",iMaxClient[iLoop],iLoop) ;
				
			
                if (isock_cli < 0)          //遍历数组,判断是否有客户端等待
				{
					continue ;
				}
                
				//(8-4)若有要处理的socket进行处理
                iSet = SC_isset(isock_cli,&allset,1) ;  //
				printf("client-iset=%d\n",iSet) ;
				if (iSet>0)  
				{     
                    printf("sock_cli=%d\n",isock_cli) ;
					/*iReturn = SC_queryarray(iSocket) ;   //测试客户端真实的socket
	                printf("socketserver=%d",stSSLSocket[iReturn].sock_serv) ;*/
					//goto lable1 ;
                    //(8-5)接收数据

                    iReturn = SC_recv(isock_cli,cRecv,sizeof(cRecv),SC_TCP_YES,NULL,&iRecv,SC_SERVER_YES) ;

					printf("recv=%s\n",cRecv) ;
					/*switch (WSAGetLastError()) 
					{
					    case WSAEWOULDBLOCK:  //没有数据
							SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_NO",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ;
							//Sleep(10) ;
							//goto lable02 ;
                            break ;
						default :
							//关闭
							break ;
					}*/
					printf("recv_num=%d",iReturn) ;
					//printf("SC_recv01=%l\n",((Transfer_C2S_Struct *)cRecv)->Value.Value.Value_long) ; 
					//printf("SC_recv00=%s\n",((Transfer_C2S_Struct *)cRecv)->Value.Value.Value_char) ; 
				
					//printf("sock=%d\n",isock_cli) ;
					//(8-6)接收数据成功
                        if (iReturn >0 )   //接收数据成功,写入到共享内存
						{          //(8-7)客户端要关闭连接
								   if (strcmp((char*)cRecv,"CLIENT_END") == 0) //客户端主动关闭(客户端发送ip)
								   {
									   SC_fdclear(isock_cli,&allset,1) ; 
									   //移动数据
									   for (int k=j;k<=iMax;k++)
									   {
                                           iMaxClient[k] = iMaxClient[k+1]  ;
									   }

									   //iMaxClient[j] = -1 ; //屏蔽
									   //int wy ;
									   SC_close(isock_cli,SD_NO,1) ;
									   //printf("wy=%d\n",wy) ;
									   iMax-- ;
									   printf("client end\n") ;
									   memset(cRecv,'\0',sizeof(cRecv)) ;
									   //向java服务器提交客户端关闭报告
									    /*ip = SC_getip(isock_cli,pcIP,piPort) ;
										strcpy(st_C2S->cIp,pcIP) ;
										st_C2S->uiPort = *piPort ;
										st_C2S->iFlag  = 2 ;  //2:客户端关闭与服务器的连接
										//写入共享内存
										SetTransfer_C2S_StructtoMapFileC2S(st_C2S) ;*/
									   continue ;
								   }
							
						   //(8-8)若接收到客户端返回代码,交给另一个线程处理
						   if (strcmp((char *)cRecv,"CLIENT_WRITE_GOOD") == 0 ||
							   strcmp((char *)cRecv,"CLIENT_WRITE_ERR") == 0)
						   {
							  //printf("hand in client\n") ;
							   continue;
							   //continue ; //(继续哪个循环?)
						   }

						   //(8-9)接收到数据为空
						   /*if (SC_isnull((char *)cRecv,sizeof(cRecv)) == 1)
						   {
							   continue ;
						   }*/
                           //(8-10)将接收的数据写入到结构中(以后补充)
						   //(8-11)取出ip地址
							ip = SC_getip(isock_cli,pcIP,piPort) ;
							printf("ip=%s\n",pcIP) ;
							//printf("port=%d",*piPort) ; //测试
							strcpy(st_C2S->cIp,pcIP) ;
							st_C2S->uiPort = *piPort ;
							//st_C2S->iFlag  = 1 ;  //1:表示客户端正常发送数据(暂时屏蔽)
                           memcpy(&(st_C2S->m_Data_Transfer_C2S_Struct),cRecv,sizeof(Transfer_C2S_Struct)) ;
						   memset(cRecv,'\0',sizeof(cRecv));  //清空当前接收的数据
						   //(8-12)写入到共享内存(方式1)
						   if (SetTransfer_C2S_StructtoMapFileC2S(st_C2S) == 1)
						   {  
							  //(8-12-1)写入共享内存成功,返回"SERVER_WRITE_GOOD" 
							   SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_GOOD",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ;
                               
							   //(8-12-2)从共享内存读出(自测使用:当李俊使用时,就屏蔽)
                              //printf("get=%d\n",GetTransfer_C2S_StructfromMapFileC2S(st_C2S01)) ;
							  //printf("value=%s\n",(st_C2S01->m_Data_Transfer_C2S_Struct).Value.Value.Value_char) ;
							  
							   //printf("port=%ud\n",st_C2S01->uiPort) ;
						   }
						   else //写入共享内存不成功,返回"SERVER_WRITE_ERR"
						   {
                               SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_ERR",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ; //RECV_ERR:要求客户端重发
						   }
                           ///////////////////////////////////////////////////////////////////
						   //以下是写入队列(目前不用)
					       //memcpy(lpMapAddress, cRecv,sizeof(TLVStruct)) ;
                           //printf("SC_recv=%s\n",((TLVStruct*)lpMapAddress)->Value.Value_Char) ; 
						   //(6-3-0-2)写入到队列(方式2:暂时不用)
						   	//(6-3-2)写入到队列
							//测试写入队列
							/*iWrite1=ITDQ_Write(iID[2],cRecv); //stTcp
							printf("write=%d",iWrite1 ) ;
							if (iWrite1 == -3) //-3:表示队列已满
							{
							    SC_send(iSocket,(unsigned char *)"RECV_ERR",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ; //RECV_ERR:要求客户端重发
							}
							else
							{
							     SC_send(iSocket,(unsigned char *)"RECV_GOOD",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ;
							}
							printf("server_Write=%d\n",iWrite1);
							memset(pSize,'\0',sizeof(pSize));
							//测试读出队列
							//ITDQ_Read(iID[2],pSize);
						    //printf("server_Read=%s\n",((TLVStruct*)pSize)->Value.Value_Char);*/
                           ///////////////////////////////////////////////////////////////////////
						}
						    //处理接收不成功的情况
						
							//SC_fdclear(isock_cli,&allset,1) ; 
                            //iMaxClient[j] = -1 ;
							//SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_NO",1024,SC_TCP_YES,NULL
								//,NULL,SC_SERVER_YES) ;
                            //(8-13)客户端网络中断,关闭socket
							if (iReturn == 0)  //客户端网络中断,要么会话重连,要么关闭socket(默认关闭socket)
							{   
								printf("client close:%s\n",pcIP) ;
								//(7-8-1)关闭客户socket
								//SC_fdclear(isock_cli,&allset,1) ; 
								//iMaxClient[j] = -1 ;
							//	SC_close(isock_cli,SD_NO,1) ;
							
								//goto lable1 ;  //跳转到结束程序
								//(7-8-2)进行会话重连(以后补充)
								
							}
							else //返回-1:返回客户端"SERVER-NO";启动定时器,服务器主动关闭客户端(以后补充)
							{
							    //(7-9)返回"SERVER-NO":客户端可以继续发送数据
								 //SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_NO",1024,SC_TCP_YES,NULL
								//,NULL,SC_SERVER_YES) ;
							}
						    
							if (iReturn == -1)
							{
								continue ;
								//SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_NO",1024,SC_TCP_YES,NULL
								//,NULL,SC_SERVER_YES) ;
							}

				

				  
				
                  if (--iNready <= 0) break;
				}
			
			}   //结束 for循环
           
		}   //结束while循环  
        
		//(9)关闭服务器套接字
//lable1:
		printf("abc\n") ;
		//关闭共享内存
		//UnmapViewOfFile(lpMapAddress);
		SC_close(iSocket,SD_NO,0) ;

		free(st_C2S);
		free(st_S2C);
		free(pcIP) ;
		free(piPort);
        
	    return 1;
}


//通讯线程(服务器:阻塞于读共享内存) (2003-04-10)
DWORD WINAPI ComProc_Read(LPVOID lpParameter)
{
   SMM_INT  isock_cli ;
   tagSMM_s2c *st_S2C; //用于存储要发送到客户端的数据
   SMM_CHAR  *pcIP  ;              //客户端发送到服务器ip
   SMM_UCHAR	buf[1024] = {'\0'} ;		//发送接收包
   SMM_UCHAR    ucRepeat[1024] = {'\0'} ;
   SMM_INT iReturn ;
   SMM_USHORT *piPort;                  //端口
   SMM_INT    j ;
   SMM_INT    iSet ;                    //>0:表示当前socket有效
   SMM_INT   i=0 ; 
   SMM_INT   iConnectFlag = 0 ;         //0表示没有该客户端连接
   //(1)初始化指针
   st_S2C = (tagSMM_s2c *)malloc(sizeof(tagSMM_s2c)) ;
   pcIP =  (SMM_CHAR *)malloc(sizeof(SMM_USHORT)) ;
   piPort = (SMM_USHORT*)malloc(sizeof(SMM_USHORT)) ;

   //(2)服务器向客户端发送指令 (以后补充)
   while (1)
   {        
	        //测试:该线程是否在运行
	       /* i++ ;
            itoa(i,(char *)buf,10) ;
		    strcat((char *)buf,"A-") ;
			printf("client=%s\n",buf) ;
            memset(buf,'\0',sizeof(buf)) ;*/

		  Sleep(10) ;    //交出控制权

           //(3)循环处理socket数组(为接收客户端发送的返回代码) 
		  /*for(i=0;i<=iMax;i++)    //处理没有必要(在select方式已经得到)							
		  {
				isock_cli = iMaxClient[i] ; //取出socket值
				if (isock_cli < 0)          //遍历数组,判断是否有客户端等待
				{
					continue ;
				}

			   iSet = SC_isset(isock_cli,&allset,1) ;  //
               if (iSet)
			   {
			   */
				   //(3-1)接收数据
				   /*iReturn = SC_recv(isock_cli,buf,sizeof(buf),SC_TCP_YES,NULL,&iRecv,SC_SERVER_YES) ;
				   if (iReturn <=0)   //接收错误
				   {
					   continue ;
				   }
                   
				   if (strcmp((char *)buf,"") == 0 )
				   {
					   continue ;
				   }
				   printf("client_recv=%s\n",(char *)buf);
           
				   //(3-2)若接收到客户端发来错误代码,要求服务器重发
				   if (strcmp((char *)buf,"CLIENT_WRITE_ERR") == 0)  
				   {
					   //重发数据
					   iReturn = SC_send(isock_cli,ucRepeat,sizeof(ucRepeat),SC_TCP_YES,NULL
													,NULL,SC_SERVER_YES) ;
				   }
				   else    //CLIENT_WRITE_GOOD:客户端接收成功:服务器继续发送数据
				   {        
							memset(ucRepeat,'\0',sizeof(ucRepeat)) ;
							//(3-2-0)客户端主动关闭
                            if (strcmp((char*)buf,"CLIENT_END") == 0) 
						   {
                               SC_fdclear(isock_cli,&allset,1) ; 
                               iMaxClient[j] = -1 ;
						       SC_close(isock_cli,SD_NO,1) ;
							   iMax-- ;
							   continue;
						   }
                           //(3-2-1)判断是否为客户端发来的具体配制信息
                           if (strcmp((char *)buf,"CLIENT_WRITE_GOOD") !=0 
							   && strcmp((char *)buf,"") !=0)
						   {
							   continue ;
						   }*/
							//(3-2-1)测试写共享内存(若加上李俊的程序,就屏蔽)
							//strcpy(st_S2C->cIp,"127.0.0.1") ;
                           // SetTransfer_S2C_StructtoMapFileS2C(st_S2C) ;
							//(3-3)从共享内存中读出数据
			   				if (GetTransfer_S2C_StructfromMapFileS2C(st_S2C) == 1) 
							{     
								 //////////////////////////////////////////////////////
								 //不用李俊的程序,服务器直接发送指令给客户端
								 // printf("clientport=%d",st_S2C->uiPort) ;
								  //printf("clientip=%s",st_S2C->cIp) ;
								  //printf("window=%d\n",st_S2C->m_Data_Transfer_S2C_Struct.InfoBaseID.InfomationElementTableID) ;

								 //strcpy(st_S2C->cIp,"192.168.1.150") ; //测试使用
								 ////////////////////////////////////////////////////////
								 //(3-4)取出结构体
								  memcpy(buf,&(st_S2C->m_Data_Transfer_S2C_Struct),sizeof(Transfer_S2C_Struct)) ;
								  memcpy(ucRepeat,buf,sizeof(buf)) ;
								  //(3-5)循环处理socket
								  for(j=0;j<=iMax;j++)    //处理没有必要(在select方式已经得到)							
								  { 
										isock_cli = iMaxClient[j] ;
										if (isock_cli < 0)          //遍历数组,判断是否有客户端等待
										{
											continue ;
										}

										iSet = SC_isset(isock_cli,&allset,1) ;  //
										printf("client-iset=%d\n",iSet) ;
										if (iSet > 0)
										{   
											//(3-6)通过socket取出客户端ip地址
											SC_getip(isock_cli,pcIP,piPort) ;
											printf("read_ip=%s\n",pcIP);

											//(3-7)取出数据的头(主要是ip地址)/socket的ip
											if (strcmp(st_S2C->cIp,pcIP) == 0) //找到客户端
											{   
												//printf("find\n") ;
												//((Transfer_S2C_Struct *)buf)->InfoBaseID.InfomationElementTableID= 1 ;
												 printf("windowtry=%d\n",((Transfer_S2C_Struct *)buf)->InfoBaseID.InfomationElementTableID) ;
                                                iConnectFlag = 1 ;
												//(3-8)向客户端发送数据
												iReturn = SC_send(isock_cli,buf,sizeof(buf),SC_TCP_YES,NULL
														,NULL,SC_SERVER_YES) ;
												printf("other_send=%d\n",iReturn) ;
												memcpy(ucRepeat,buf,sizeof(buf)) ;
												memset(buf,'\0',sizeof(buf)) ;
												printf("send=%d\n",iReturn) ;
											}
										}  //结束iSet > 0
								  }        //结束for

                                  //(3-9)判断该ip地址并没有连接上服务器
								  /*if (iConnectFlag == 0)
								  {
                                      printf("client can not connect server\n") ;
									  continue ;
								  }*/

							}              //共享内存
				  // }
			  // }   //结束最外层iSet>0
           
		 // }  //结束最外层for
		
   }

   free(pcIP);
   free(piPort) ;
   return 1 ;
}
