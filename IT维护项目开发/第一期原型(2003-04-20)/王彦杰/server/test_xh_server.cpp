/*************************************************************
  Copyright (C)
  File name:  
  Author: 
  Version:  
  Date: 2003-3-28
  Description:    ���ļ��ǶԶ��߳�ͨ�ŵĲ��Գ���
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
//#include "smm_ssl.h"   //sslͨѶͷ�ļ�
#include "test.h"   //����
#include "smm_api.cpp"    //ssl�ӿں���

#define   USE_SSL       0         //0:��ʹ��SSLͨѶ 1:��ʾʹ��SSL                                

DWORD WINAPI ComProc(LPVOID lpParameter);						// ͨ���߳�����
DWORD WINAPI ComProc_Read(LPVOID lpParameter) ;                 //�����������ڶ������ڴ�



CRITICAL_SECTION cs;

//SMM_UCHAR *pSize;      //(��ʱ����)
SMM_INT  iID[4];													//����ID
//SMM_CHAR *pSize=(char*)malloc(sizeof(Data_Size));
//int test(void) ;
//SMM_CHAR pData[1][Data_Size];
HANDLE hShare;  
HANDLE hMapFile ;
LPVOID lpMapAddress;           //MapViewOfFile����ֵ
TLVStruct m_Data;  

int main(int argc, char* argv[])
{
	//pSize =(unsigned char*)malloc(sizeof(Data_Size)) ; (�ڶ�����ʹ��)

    char a =' ' ;

   //��������(��ʱ����) 
	/*ITDQ_Init();
    iID[2]=ITDQ_Create(0,Data_Size);
	iID[3]=ITDQ_Create(0,Data_Size);*/

    //(1)���������ڴ�(�ͻ��˵�������)
	CreateFileMappingC2S() ;  //�ͻ��˵�������
	CreateFileMappingS2C() ;  ////���������ͻ���


	InitializeCriticalSection(&cs);

    //(2)�����߳�
	CreateThread(NULL,0,ComProc_Read,NULL,0,NULL);	
	CreateThread(NULL,0,ComProc,NULL,0,NULL);                   //����ͨ���߳�
	//Sleep(INFINITE);
	//Sleep(1000);

//	test() ;
				//�����������ڴ��߳�
    
	//Sleep(INFINITE);
    

 
	while (a !='z') 
	{
		a = getchar() ;
	}


	DeleteCriticalSection(&cs);
	return 1;
}


////////////////////////////////////////////////////////////////////
//����ȫ�ֱ���(������ڶ��߳�ʱʹ��)
SMM_INT iMaxClient[FD_SETSIZE] ;//����ͻ������ӵ�����
SMM_INT iMax = -1 ;                 //�����е�����±�
fd_set fset,allset ;             //������

///////////////////////////////////////////////////////////////////
//ͨѶ�߳�(�ͻ������ӷ�����:������д�����ڴ�)
DWORD WINAPI ComProc(LPVOID lpParameter)
//int test(void)
{
	    int n = 0;
		SMM_INT iSocket ;               //������
		SMM_INT isock_cli ;             //�ͻ���
		SMM_INT iReturn ;
		//SMM_INT iMaxClient[FD_SETSIZE] ;//����ͻ������ӵ����� (�Ѷ���Ϊȫ�ֱ���)
		//SMM_INT iMax ;                 //�����е�����±�
		//fd_set fset,allset ;             //������
		SMM_INT iNready ;				//����������socket�����Ŀ
		SMM_UCHAR	buf[1024] = {'\0'} ;		//���ͽ��հ�
		SMM_INT iLen;                  //�ȴ�socket��ַ�峤��
		SMM_INT j;						//ѭ������
        SMM_UCHAR cRecv[1024] ={'\0'};
        SMM_INT  iRecv = 0 ;
        SMM_ULONG ulArgpN = 1 ;
        SMM_INT i=1 ;
        SMM_INT iSet ;
        SMM_INT  ip ;
      
        //����
        SMM_CHAR  pcBuffer[100000]={'\0'} ;
		SMM_CHAR  *pcIP  ;              //�ͻ��˷��͵�������ip
		SMM_USHORT  *piPort  ;          //�˿�
        SMM_INT iLoop =0 ;              //ѭ��:���ڿ���socket����
	
        SMM_CHAR   b =' ' ;
        //(0)����
        //���ڴ洢�ͻ��˷��ط���˵�����
        tagSMM_c2s  *st_C2S;
		tagSMM_c2s  *st_C2S01;
        
       //���ڴ洢Ҫ���͵��ͻ��˵�����
        tagSMM_s2c *st_S2C;

        //(1)��ʼ����
		SC_init();	
		st_C2S = (tagSMM_c2s *)malloc(sizeof(tagSMM_c2s)) ;
		st_C2S01 = (tagSMM_c2s *)malloc(sizeof(tagSMM_c2s)) ;
		st_S2C = (tagSMM_s2c *)malloc(sizeof(tagSMM_s2c)) ;
		pcIP =  (SMM_CHAR *)malloc(sizeof(SMM_CHAR)) ;
		piPort = (SMM_USHORT*)malloc(sizeof(SMM_USHORT)) ;
        
	
	    //(2)����socket
	if (USE_SSL == 1)  //ʹ��SSLͨѶ
		{
			iSocket = SC_socket(AF_INET,SOCK_STREAM,SC_VERIFY_YES,SC_ENCRYPT_NO
						,SC_SERVER_YES,SC_SSLV3) ;      //�����ɿ���֤�Ļ��ڷ������˵�socket������
		}
		else              //��ͨsocket
		{

				iSocket = SC_socket(AF_INET,SOCK_STREAM,SC_VERIFY_NO,SC_ENCRYPT_NO
						,SC_SERVER_YES,SC_SSLV3) ;      //������ͨ�ķ������˵�socket������
		}

       // printf("SC_socket=%d",iSocket) ;
      
		//(3)��
		if(SC_bind(iSocket,5000) != 0)
		{
			 printf("bind is error!\n") ;		//�󶨴���
			 exit(1) ;
		}
        //(4)����
		iReturn = SC_listen(iSocket,5) ;
		if (iReturn !=0)
		{
		  printf("listen error") ;
		  exit(1) ;
		}
	
		iLen=sizeof(sockaddr_in) ;

		
		//(5)����socket����Ϊ������ģʽ
		if (USE_SSL == 1)   //ʹ�÷�����ģʽ (SSL)
		{
	        iReturn = SC_ioctl(iSocket,FIONBIO,ulArgpN) ;	//���÷�������ʽ(��SSL_accept�г�ͻ)
			//printf("SC_ioctl01=%d\n",iReturn) ;
		}
		else    //��ͨsocket
		{
			 iReturn = SC_ioctl(iSocket,FIONBIO,ulArgpN) ;
		}
		
		//(6)����socketѡ��(�ر���ʱ)
		int itry ;
		itry = SC_setsockopt(iSocket,1,1,4) ;  //�ر�socket��ʱ4��
		printf("setsockopt=%d\n",itry) ;

		//(7)��ʼ���ļ���/socket��������
		iMax=-1 ;
		for(j=0;j<FD_SETSIZE;j++)						//ѭ���ж����������
		{
			iMaxClient[j]=-1 ;
		}
	
		

		SC_selectinit(&allset);  //���fd_set

		SC_fdset(iSocket,&allset,0) ; //���ӷ�����socket��fd_set����
		
       //(8)ѭ���ȴ�����ʹ���ͻ�������
		while(1)						
		{   
		    Sleep(10) ;
            fset = allset ;
			//(8-1)���ؿɶ���socket��Ŀ,���Ѿ��пͻ�����
			//iNready=SC_select(0,SC_SELECTREAD_YES,-1,&fset) ;  //����ģʽ:����1��
			iNready=SC_select(0,SC_SELECTREAD_YES,0,&fset) ;    //������ģʽ
			printf("iNready=%d\n",iNready) ;

			//����
			printf("server-isset=%d\n",SC_isset(iSocket,&fset,0)) ;
			//(8-2)�ж�socket�Ƿ����ļ�����(������)
			if (SC_isset(iSocket,&fset,0)>0)       //���տͻ�������
			{       SC_fdset(iSocket,&fset,0) ; //���ӷ�����socket��fd_set����
					iLen=sizeof(SOCKADDR_IN);
					isock_cli  = SC_accept(iSocket) ;  //�ȴ��ͻ�����

					//(8-3)��java�������ύ�������ϵĿͻ���ip��ַ(��ʱ����)
                    //(8-3-1)ȡ��ip
				   /*ip= SC_getip(isock_cli,pcIP,piPort) ;
				   if (ip == 0)  //ȡ��ip�ɹ�
				   {
                        printf("ip=%s\n",pcIP) ;
					    printf("port=%d",*piPort) ; //����
                        strcpy(st_C2S->cIp,pcIP) ;
                        st_C2S->uiPort = *piPort ;
						st_C2S->iFlag  = 0 ;  //0:�ͻ��˸������Ϸ�����
						//д�빲���ڴ�
                        SetTransfer_C2S_StructtoMapFileC2S(st_C2S) ;
				   }
				   else
				   {
					   printf("������������ύ�ͻ���ip��ַ\n") ;
				   }
					
				   */

					printf("accept_iLoop=%d\n",iLoop) ;

					if (isock_cli <0)  //���ղ���
					{
                        //printf("server can not accept client request ");
						continue ;
					}

					printf("accept=%d\n",isock_cli) ;

                   	/*while (b !='a')   //����SC_accept����(�ڴ˵ȴ��û���Ӧ)
						{
							b = getchar() ;
						}*/

					for(j=0;j<FD_SETSIZE;j++)          //��������,���洢socketֵ 
					{
						if(iMaxClient[j]<0)
						{
							iMaxClient[j] = isock_cli ; //����socket
							break;
						}
						
					}

					if(j>=FD_SETSIZE)				    //������¼����socket�����
					{
						printf("���ӿͻ���̫��!\n") ;
					}
                     
					if (isock_cli >= 0)
					{
					     SC_fdset(isock_cli,&allset,1) ;  //���ӿͻ���socketֵ���ļ�����
					}

					if(j>=iMax)                       //��������û���
					{
						iMax=j ;
					}

            }
            
			printf("iMax=%d\n",iMax) ;
			
			//(8-4)��������û�����,��������տͻ�������
			for(iLoop=0;iLoop<=iMax;iLoop++)    //����û�б�Ҫ(��select��ʽ�Ѿ��õ�) ԭj=0							
			{   
				//�������û���������
				isock_cli = iMaxClient[iLoop] ;
				printf("Client=%d,iLoop=%d\n",iMaxClient[iLoop],iLoop) ;
				
			
                if (isock_cli < 0)          //��������,�ж��Ƿ��пͻ��˵ȴ�
				{
					continue ;
				}
                
				//(8-4)����Ҫ�����socket���д���
                iSet = SC_isset(isock_cli,&allset,1) ;  //
				printf("client-iset=%d\n",iSet) ;
				if (iSet>0)  
				{     
                    printf("sock_cli=%d\n",isock_cli) ;
					/*iReturn = SC_queryarray(iSocket) ;   //���Կͻ�����ʵ��socket
	                printf("socketserver=%d",stSSLSocket[iReturn].sock_serv) ;*/
					//goto lable1 ;
                    //(8-5)��������

                    iReturn = SC_recv(isock_cli,cRecv,sizeof(cRecv),SC_TCP_YES,NULL,&iRecv,SC_SERVER_YES) ;

					printf("recv=%s\n",cRecv) ;
					/*switch (WSAGetLastError()) 
					{
					    case WSAEWOULDBLOCK:  //û������
							SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_NO",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ;
							//Sleep(10) ;
							//goto lable02 ;
                            break ;
						default :
							//�ر�
							break ;
					}*/
					printf("recv_num=%d",iReturn) ;
					//printf("SC_recv01=%l\n",((Transfer_C2S_Struct *)cRecv)->Value.Value.Value_long) ; 
					//printf("SC_recv00=%s\n",((Transfer_C2S_Struct *)cRecv)->Value.Value.Value_char) ; 
				
					//printf("sock=%d\n",isock_cli) ;
					//(8-6)�������ݳɹ�
                        if (iReturn >0 )   //�������ݳɹ�,д�뵽�����ڴ�
						{          //(8-7)�ͻ���Ҫ�ر�����
								   if (strcmp((char*)cRecv,"CLIENT_END") == 0) //�ͻ��������ر�(�ͻ��˷���ip)
								   {
									   SC_fdclear(isock_cli,&allset,1) ; 
									   //�ƶ�����
									   for (int k=j;k<=iMax;k++)
									   {
                                           iMaxClient[k] = iMaxClient[k+1]  ;
									   }

									   //iMaxClient[j] = -1 ; //����
									   //int wy ;
									   SC_close(isock_cli,SD_NO,1) ;
									   //printf("wy=%d\n",wy) ;
									   iMax-- ;
									   printf("client end\n") ;
									   memset(cRecv,'\0',sizeof(cRecv)) ;
									   //��java�������ύ�ͻ��˹رձ���
									    /*ip = SC_getip(isock_cli,pcIP,piPort) ;
										strcpy(st_C2S->cIp,pcIP) ;
										st_C2S->uiPort = *piPort ;
										st_C2S->iFlag  = 2 ;  //2:�ͻ��˹ر��������������
										//д�빲���ڴ�
										SetTransfer_C2S_StructtoMapFileC2S(st_C2S) ;*/
									   continue ;
								   }
							
						   //(8-8)�����յ��ͻ��˷��ش���,������һ���̴߳���
						   if (strcmp((char *)cRecv,"CLIENT_WRITE_GOOD") == 0 ||
							   strcmp((char *)cRecv,"CLIENT_WRITE_ERR") == 0)
						   {
							  //printf("hand in client\n") ;
							   continue;
							   //continue ; //(�����ĸ�ѭ��?)
						   }

						   //(8-9)���յ�����Ϊ��
						   /*if (SC_isnull((char *)cRecv,sizeof(cRecv)) == 1)
						   {
							   continue ;
						   }*/
                           //(8-10)�����յ�����д�뵽�ṹ��(�Ժ󲹳�)
						   //(8-11)ȡ��ip��ַ
							ip = SC_getip(isock_cli,pcIP,piPort) ;
							printf("ip=%s\n",pcIP) ;
							//printf("port=%d",*piPort) ; //����
							strcpy(st_C2S->cIp,pcIP) ;
							st_C2S->uiPort = *piPort ;
							//st_C2S->iFlag  = 1 ;  //1:��ʾ�ͻ���������������(��ʱ����)
                           memcpy(&(st_C2S->m_Data_Transfer_C2S_Struct),cRecv,sizeof(Transfer_C2S_Struct)) ;
						   memset(cRecv,'\0',sizeof(cRecv));  //��յ�ǰ���յ�����
						   //(8-12)д�뵽�����ڴ�(��ʽ1)
						   if (SetTransfer_C2S_StructtoMapFileC2S(st_C2S) == 1)
						   {  
							  //(8-12-1)д�빲���ڴ�ɹ�,����"SERVER_WRITE_GOOD" 
							   SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_GOOD",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ;
                               
							   //(8-12-2)�ӹ����ڴ����(�Բ�ʹ��:���ʹ��ʱ,������)
                              //printf("get=%d\n",GetTransfer_C2S_StructfromMapFileC2S(st_C2S01)) ;
							  //printf("value=%s\n",(st_C2S01->m_Data_Transfer_C2S_Struct).Value.Value.Value_char) ;
							  
							   //printf("port=%ud\n",st_C2S01->uiPort) ;
						   }
						   else //д�빲���ڴ治�ɹ�,����"SERVER_WRITE_ERR"
						   {
                               SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_ERR",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ; //RECV_ERR:Ҫ��ͻ����ط�
						   }
                           ///////////////////////////////////////////////////////////////////
						   //������д�����(Ŀǰ����)
					       //memcpy(lpMapAddress, cRecv,sizeof(TLVStruct)) ;
                           //printf("SC_recv=%s\n",((TLVStruct*)lpMapAddress)->Value.Value_Char) ; 
						   //(6-3-0-2)д�뵽����(��ʽ2:��ʱ����)
						   	//(6-3-2)д�뵽����
							//����д�����
							/*iWrite1=ITDQ_Write(iID[2],cRecv); //stTcp
							printf("write=%d",iWrite1 ) ;
							if (iWrite1 == -3) //-3:��ʾ��������
							{
							    SC_send(iSocket,(unsigned char *)"RECV_ERR",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ; //RECV_ERR:Ҫ��ͻ����ط�
							}
							else
							{
							     SC_send(iSocket,(unsigned char *)"RECV_GOOD",1024,SC_TCP_YES,NULL
								,NULL,SC_SERVER_YES) ;
							}
							printf("server_Write=%d\n",iWrite1);
							memset(pSize,'\0',sizeof(pSize));
							//���Զ�������
							//ITDQ_Read(iID[2],pSize);
						    //printf("server_Read=%s\n",((TLVStruct*)pSize)->Value.Value_Char);*/
                           ///////////////////////////////////////////////////////////////////////
						}
						    //������ղ��ɹ������
						
							//SC_fdclear(isock_cli,&allset,1) ; 
                            //iMaxClient[j] = -1 ;
							//SC_send(isock_cli,(unsigned char *)"SERVER_WRITE_NO",1024,SC_TCP_YES,NULL
								//,NULL,SC_SERVER_YES) ;
                            //(8-13)�ͻ��������ж�,�ر�socket
							if (iReturn == 0)  //�ͻ��������ж�,Ҫô�Ự����,Ҫô�ر�socket(Ĭ�Ϲر�socket)
							{   
								printf("client close:%s\n",pcIP) ;
								//(7-8-1)�رտͻ�socket
								//SC_fdclear(isock_cli,&allset,1) ; 
								//iMaxClient[j] = -1 ;
							//	SC_close(isock_cli,SD_NO,1) ;
							
								//goto lable1 ;  //��ת����������
								//(7-8-2)���лỰ����(�Ժ󲹳�)
								
							}
							else //����-1:���ؿͻ���"SERVER-NO";������ʱ��,�����������رտͻ���(�Ժ󲹳�)
							{
							    //(7-9)����"SERVER-NO":�ͻ��˿��Լ�����������
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
			
			}   //���� forѭ��
           
		}   //����whileѭ��  
        
		//(9)�رշ������׽���
//lable1:
		printf("abc\n") ;
		//�رչ����ڴ�
		//UnmapViewOfFile(lpMapAddress);
		SC_close(iSocket,SD_NO,0) ;

		free(st_C2S);
		free(st_S2C);
		free(pcIP) ;
		free(piPort);
        
	    return 1;
}


//ͨѶ�߳�(������:�����ڶ������ڴ�) (2003-04-10)
DWORD WINAPI ComProc_Read(LPVOID lpParameter)
{
   SMM_INT  isock_cli ;
   tagSMM_s2c *st_S2C; //���ڴ洢Ҫ���͵��ͻ��˵�����
   SMM_CHAR  *pcIP  ;              //�ͻ��˷��͵�������ip
   SMM_UCHAR	buf[1024] = {'\0'} ;		//���ͽ��հ�
   SMM_UCHAR    ucRepeat[1024] = {'\0'} ;
   SMM_INT iReturn ;
   SMM_USHORT *piPort;                  //�˿�
   SMM_INT    j ;
   SMM_INT    iSet ;                    //>0:��ʾ��ǰsocket��Ч
   SMM_INT   i=0 ; 
   SMM_INT   iConnectFlag = 0 ;         //0��ʾû�иÿͻ�������
   //(1)��ʼ��ָ��
   st_S2C = (tagSMM_s2c *)malloc(sizeof(tagSMM_s2c)) ;
   pcIP =  (SMM_CHAR *)malloc(sizeof(SMM_USHORT)) ;
   piPort = (SMM_USHORT*)malloc(sizeof(SMM_USHORT)) ;

   //(2)��������ͻ��˷���ָ�� (�Ժ󲹳�)
   while (1)
   {        
	        //����:���߳��Ƿ�������
	       /* i++ ;
            itoa(i,(char *)buf,10) ;
		    strcat((char *)buf,"A-") ;
			printf("client=%s\n",buf) ;
            memset(buf,'\0',sizeof(buf)) ;*/

		  Sleep(10) ;    //��������Ȩ

           //(3)ѭ������socket����(Ϊ���տͻ��˷��͵ķ��ش���) 
		  /*for(i=0;i<=iMax;i++)    //����û�б�Ҫ(��select��ʽ�Ѿ��õ�)							
		  {
				isock_cli = iMaxClient[i] ; //ȡ��socketֵ
				if (isock_cli < 0)          //��������,�ж��Ƿ��пͻ��˵ȴ�
				{
					continue ;
				}

			   iSet = SC_isset(isock_cli,&allset,1) ;  //
               if (iSet)
			   {
			   */
				   //(3-1)��������
				   /*iReturn = SC_recv(isock_cli,buf,sizeof(buf),SC_TCP_YES,NULL,&iRecv,SC_SERVER_YES) ;
				   if (iReturn <=0)   //���մ���
				   {
					   continue ;
				   }
                   
				   if (strcmp((char *)buf,"") == 0 )
				   {
					   continue ;
				   }
				   printf("client_recv=%s\n",(char *)buf);
           
				   //(3-2)�����յ��ͻ��˷����������,Ҫ��������ط�
				   if (strcmp((char *)buf,"CLIENT_WRITE_ERR") == 0)  
				   {
					   //�ط�����
					   iReturn = SC_send(isock_cli,ucRepeat,sizeof(ucRepeat),SC_TCP_YES,NULL
													,NULL,SC_SERVER_YES) ;
				   }
				   else    //CLIENT_WRITE_GOOD:�ͻ��˽��ճɹ�:������������������
				   {        
							memset(ucRepeat,'\0',sizeof(ucRepeat)) ;
							//(3-2-0)�ͻ��������ر�
                            if (strcmp((char*)buf,"CLIENT_END") == 0) 
						   {
                               SC_fdclear(isock_cli,&allset,1) ; 
                               iMaxClient[j] = -1 ;
						       SC_close(isock_cli,SD_NO,1) ;
							   iMax-- ;
							   continue;
						   }
                           //(3-2-1)�ж��Ƿ�Ϊ�ͻ��˷����ľ���������Ϣ
                           if (strcmp((char *)buf,"CLIENT_WRITE_GOOD") !=0 
							   && strcmp((char *)buf,"") !=0)
						   {
							   continue ;
						   }*/
							//(3-2-1)����д�����ڴ�(��������ĳ���,������)
							//strcpy(st_S2C->cIp,"127.0.0.1") ;
                           // SetTransfer_S2C_StructtoMapFileS2C(st_S2C) ;
							//(3-3)�ӹ����ڴ��ж�������
			   				if (GetTransfer_S2C_StructfromMapFileS2C(st_S2C) == 1) 
							{     
								 //////////////////////////////////////////////////////
								 //������ĳ���,������ֱ�ӷ���ָ����ͻ���
								 // printf("clientport=%d",st_S2C->uiPort) ;
								  //printf("clientip=%s",st_S2C->cIp) ;
								  //printf("window=%d\n",st_S2C->m_Data_Transfer_S2C_Struct.InfoBaseID.InfomationElementTableID) ;

								 //strcpy(st_S2C->cIp,"192.168.1.150") ; //����ʹ��
								 ////////////////////////////////////////////////////////
								 //(3-4)ȡ���ṹ��
								  memcpy(buf,&(st_S2C->m_Data_Transfer_S2C_Struct),sizeof(Transfer_S2C_Struct)) ;
								  memcpy(ucRepeat,buf,sizeof(buf)) ;
								  //(3-5)ѭ������socket
								  for(j=0;j<=iMax;j++)    //����û�б�Ҫ(��select��ʽ�Ѿ��õ�)							
								  { 
										isock_cli = iMaxClient[j] ;
										if (isock_cli < 0)          //��������,�ж��Ƿ��пͻ��˵ȴ�
										{
											continue ;
										}

										iSet = SC_isset(isock_cli,&allset,1) ;  //
										printf("client-iset=%d\n",iSet) ;
										if (iSet > 0)
										{   
											//(3-6)ͨ��socketȡ���ͻ���ip��ַ
											SC_getip(isock_cli,pcIP,piPort) ;
											printf("read_ip=%s\n",pcIP);

											//(3-7)ȡ�����ݵ�ͷ(��Ҫ��ip��ַ)/socket��ip
											if (strcmp(st_S2C->cIp,pcIP) == 0) //�ҵ��ͻ���
											{   
												//printf("find\n") ;
												//((Transfer_S2C_Struct *)buf)->InfoBaseID.InfomationElementTableID= 1 ;
												 printf("windowtry=%d\n",((Transfer_S2C_Struct *)buf)->InfoBaseID.InfomationElementTableID) ;
                                                iConnectFlag = 1 ;
												//(3-8)��ͻ��˷�������
												iReturn = SC_send(isock_cli,buf,sizeof(buf),SC_TCP_YES,NULL
														,NULL,SC_SERVER_YES) ;
												printf("other_send=%d\n",iReturn) ;
												memcpy(ucRepeat,buf,sizeof(buf)) ;
												memset(buf,'\0',sizeof(buf)) ;
												printf("send=%d\n",iReturn) ;
											}
										}  //����iSet > 0
								  }        //����for

                                  //(3-9)�жϸ�ip��ַ��û�������Ϸ�����
								  /*if (iConnectFlag == 0)
								  {
                                      printf("client can not connect server\n") ;
									  continue ;
								  }*/

							}              //�����ڴ�
				  // }
			  // }   //���������iSet>0
           
		 // }  //���������for
		
   }

   free(pcIP);
   free(piPort) ;
   return 1 ;
}
