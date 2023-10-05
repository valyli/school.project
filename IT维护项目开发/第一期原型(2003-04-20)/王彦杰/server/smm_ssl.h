///////////////////////////////////////////////////////////////////////////////
//�ļ����ݣ�
//���ߣ�	
//��д���ڣ�2003-04-01
//��Ҫ�ļ���
//�漰���ã�
///////////////////////////////////////////////////////////////////////////////
#if !defined(SMM_NO_SSL)               //ʹ��SSLͷ�ļ�

	#include "winsock2.h"
	#include "malloc.h"
	#include "stdio.h"
	#include "memory.h"
	#include "crypto.h"
	#include "x509.h"
	#include "ssl.h"
	#include "smm_type.h"
	
	/*custom  data type define */
	#define SD_NO           10       //shutdown on all direction
	#define SOCKET_MAX      256     //max socket connect number
	#define SC_ENCRYPT_YES  1       //use encrypt
	#define SC_ENCRYPT_NO   0       //no use encrypt
	#define SC_VERIFY_YES   1       //use SSL
	#define SC_VERIFY_NO    0       //no use SSL
	#define	SC_SERVER_YES   1       //server use
	#define	SC_CLIENT_YES   0       //client use
	#define SC_TCP_YES      0       //use tcp
	#define	SC_UDP_YES      1       //use udp
	#define SC_SSLV2        3       //SSLv2 protocol
	#define SC_TLSV1        2       //TLSv1 protocol
	#define SC_SSLV3        1       //SSLv3 protocol
	#define SC_SSLV23       4       //SSLv23 protocol
	#define SC_NOBLOCK_YES  1       //noblock mode
	#define SC_BLOCK_YES   0        //block mode
	#define SC_SELECTREAD_YES    0  //readset     
	#define SC_SELECTWRITE_YES   1  //writeset
	#define SC_SELECTEXP_YES     2  //exception
	
	#define SC_REPEAT      10       //�ط�����
	
	
	#define CIPHER_LIST_CLIENT "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH" //�����б�
	#define CAFILE_CLIENT "rootcert.pem"                           //��֤��
	#define CADIR_CLIENT NULL                                      //
	#define CERTFILE_CLIENT "client.pem"                    //�ͻ���֤��
	
	#define CIPHER_LIST_SERVER "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
	#define CAFILE_SERVER "rootcert.pem"
	#define CADIR_SERVER NULL
	#define CERTFILE_SERVER "server.pem"
	
	typedef  struct  tagSMM_socket
	{
	  SOCKET s;             //client,server
	  SOCKET sock_serv;     //server
	  SSL  *ssl;            //SSL structure   
	  SSL_CTX  *ctx;        //SSL_CTX structure
	  SMM_INT  flag ;       //socket flag
	}c;
	/////////////////////////////////
	/*SMM_ULONG  SC_init() ;
	SMM_INT SC_socket(SMM_ULONG ulAddressFamily,SMM_ULONG ulType
							,SMM_ULONG ulAuth,SMM_ULONG ulEncrypt
							,SMM_ULONG ulServer,SMM_ULONG ulVersion);
	SMM_INT SC_bind(SMM_INT iSocket,SMM_INT iPort);
	SMM_INT SC_listen(SMM_INT iSocket,SMM_INT iMaxnum);
	SMM_INT SC_accept(SMM_INT iSocket);
	SMM_INT SC_connect(SMM_INT iSocket,const SMM_CHAR FAR *pcIP,SMM_INT iPort );
	SMM_INT SC_send(SMM_INT iSocket, const char FAR *pcBuffer,SMM_INT iLen
					, SMM_INT iFlags,const struct sockaddr FAR *pTo,SMM_INT iTolen,SMM_INT iServer);
	SMM_INT SC_recv( SMM_INT iSocket, char FAR *pcBuffer,SMM_INT iLen
					,SMM_INT iFlags,struct sockaddr FAR *pFrom, SMM_INT FAR *pFromlen,SMM_INT iServer);
	SMM_VOID SC_selectinit(fd_set *pFd);
	SMM_INT SC_select(SMM_INT iNfds,SMM_INT iRwe,const struct timeval *pTimeout,fd_set *pFd);
	SMM_INT SC_close(SMM_INT iSocket,SMM_INT iHow,SMM_INT iMain);
	SMM_INT SC_isset(SMM_INT iSocket,fd_set FAR *pFd,SMM_INT iClient);
	SMM_VOID SC_fdset(SMM_INT iSocket,fd_set FAR *pFd,SMM_INT iClient);
	SMM_VOID SC_fdclear(SMM_INT iSock,fd_set FAR *fd,SMM_INT iClient);*/
	
	///////////////////////////////////////////////////////////////////////////////
	//��Ѷ���
	//�洢����ֵ�Ĺ�����
	/*union DataValueUnion
	{
		char Value_Char[256];
		int Value_Int;
	};
	
	
	//TLV��Type��Length��Value����ʽ�����е�Type��ʾValue��ʲô��
	//Length��ʾValue�ĳ��ȣ�Value����ʵ�ʵ����ݡ�
	//����Type����ΪCPU��ʵ�ʲɼ�����Ϣ�����ͣ�LengthΪ8;ValueΪPentium4��
	struct TLVStruct
	{
	    int Type;
	    long Length;
	    DataValueUnion Value;
	};*/
	
	
	///////////////////////////////////////////////////////////////////////////////
	 //���������/�ͻ���������Ϣ
        typedef struct tagSMM_setup
        {
        	SMM_INT   iVerifyMode ;    //��֤��ʽ:1��ʾʹ��֤����֤ 0:��ʾ��ʹ����֤
        	SMM_CHAR  cCipher[100] ;   //�����б�
        	SMM_INT   iSSL         ;   //1:��ʾʹ��SSL��ȫͨѶ 0:ʹ����ͨsocketͨѶ 
        	
         };

#endif