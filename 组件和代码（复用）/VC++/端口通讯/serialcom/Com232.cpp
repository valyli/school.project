#include "stdafx.h"
#include "com232.h"

BYTE XwCom=0x40;
BYTE  sCom1[5],sCom2[MAXBLOCKLENGTH+12],sCom3[MAXBLOCKLENGTH+12];
BYTE opation;
short ComNum;
//COMSTAT ComStat;


CComStatus::CComStatus()
{
	m_hCom = NULL;
	m_bComId = (char)ComNum;//COM1

	m_bByteSize=8;
	m_bStopBits=ONESTOPBIT;
	m_bParity=NOPARITY;
	m_dwBaudRate=9600;
//	m_fChEvt=1;
	m_bEvtChar=EVENTCHAR;
	m_fBinary=1;

	m_bConnected = FALSE;
	m_bFlowCtrl = FC_XONXOFF ;
	m_fXonXoff = FALSE;
}
CComStatus::CComStatus(BYTE bComId,BYTE bByteSize,BYTE bStopBits,BYTE bParity,
		DWORD dwBaudRate,/*WORD fChEvt,*/char bEvtChar,DWORD fBinary)
{
	m_hCom = NULL;
	m_bComId = bComId;

	m_bByteSize=bByteSize;
	m_bStopBits=bStopBits;
	m_bParity=bParity;
	m_dwBaudRate=dwBaudRate;
//	m_fChEvt=1;
	m_bEvtChar=bEvtChar;
	m_fBinary=fBinary;

	m_bConnected = FALSE;

	m_bFlowCtrl = FC_XONXOFF ;
	m_fXonXoff = FALSE;

}
BOOL CComStatus::OpenConnection()
{
	char csCom[10];
    COMMTIMEOUTS  CommTimeOuts ;

    if((m_bComId < 0) || (m_bComId > 4))
		return FALSE;//从COM1到COM4
	if(m_hCom)//if already open
		return FALSE;
    //OVERLAPPED包含异步I/O信息
	m_rdos.Offset = 0;
	m_rdos.OffsetHigh = 0;
	m_rdos.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(m_rdos.hEvent == NULL)
		return FALSE;
	m_wtos.Offset = 0;
	m_wtos.OffsetHigh = 0;
	m_wtos.hEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	if(m_wtos.hEvent == NULL)
	{
		CloseHandle(m_rdos.hEvent);
		return FALSE;
	}
	

	wsprintf(csCom,"COM%d",m_bComId);
	m_hCom = CreateFile(csCom,GENERIC_READ | GENERIC_WRITE,
    0,
    NULL,
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
    NULL
	);

	if(m_hCom == INVALID_HANDLE_VALUE) {
		//dwError = GetLastError();
	    // handle error 
		return FALSE;
	}
	else
	{
      // get any early notifications

      SetCommMask( m_hCom, EV_RXCHAR ) ;

      // setup device buffers

      SetupComm( m_hCom, 4096, 4096 ) ;

      // purge any information in the buffer

      PurgeComm( m_hCom, PURGE_TXABORT | PURGE_RXABORT |
                                      PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

      // set up for overlapped I/O
	  DWORD dwTemp = 1000 / (this->m_dwBaudRate / 8);
      CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
      CommTimeOuts.ReadTotalTimeoutMultiplier = 0;//((dwTemp > 0) ? dwTemp : 1);
      CommTimeOuts.ReadTotalTimeoutConstant = 1000 ;
      // CBR_9600 is approximately 1byte/ms. For our purposes, allow
      // double the expected time per character for a fudge factor.
      
      CommTimeOuts.WriteTotalTimeoutMultiplier = 2*CBR_9600/this->m_dwBaudRate;//( npTTYInfo ) ;
      CommTimeOuts.WriteTotalTimeoutConstant = 0;//1000 ;
      SetCommTimeouts( m_hCom, &CommTimeOuts ) ;
	}
	if(!SetupConnection())
	{
		CloseConnection();
		return FALSE;
	}
	EscapeCommFunction( m_hCom, SETDTR );
	m_bConnected = TRUE;
	return TRUE;
}
BOOL CComStatus::CloseConnection()
{
   if (NULL == m_hCom)
      return ( TRUE ) ;

   // set connected flag to FALSE

	m_bConnected = FALSE;
   // disable event notification and wait for thread
   // to halt

   SetCommMask( m_hCom, 0 ) ;

   // block until thread has been halted

   //while(THREADID(npTTYInfo) != 0);

   // kill the focus

   //KillTTYFocus( hWnd ) ;

   // drop DTR

   EscapeCommFunction( m_hCom, CLRDTR ) ;

   // purge any outstanding reads/writes and close device handle

   PurgeComm( m_hCom, PURGE_TXABORT | PURGE_RXABORT |
                                   PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
   CloseHandle( m_hCom ) ;
	m_hCom = NULL;
   // change the selectable items in the menu
	CloseHandle(m_rdos.hEvent);
	CloseHandle(m_wtos.hEvent);

   return ( TRUE ) ;
}
BOOL CComStatus::SetupConnection()
{
   BOOL       fRetVal ;
   BYTE       bSet ;
   DCB        dcb ;
	if(m_hCom == NULL)
		return FALSE; 
   dcb.DCBlength = sizeof( DCB ) ;

   GetCommState( m_hCom, &dcb ) ;

   dcb.BaudRate = this->m_dwBaudRate;
   dcb.ByteSize = this->m_bByteSize;
   dcb.Parity =  this->m_bParity;
   dcb.StopBits = this->m_bStopBits ;
	dcb.EvtChar = this->m_bEvtChar ;
   // setup hardware flow control

   bSet = (BYTE) ((m_bFlowCtrl & FC_DTRDSR) != 0) ;
   dcb.fOutxDsrFlow = bSet ;
   if (bSet)
      dcb.fDtrControl = DTR_CONTROL_HANDSHAKE ;
   else
      dcb.fDtrControl = DTR_CONTROL_ENABLE ;

   bSet = (BYTE) ((m_bFlowCtrl & FC_RTSCTS) != 0) ;
	dcb.fOutxCtsFlow = bSet ;
   if (bSet)
      dcb.fRtsControl = RTS_CONTROL_HANDSHAKE ;
   else
      dcb.fRtsControl = RTS_CONTROL_ENABLE ;

   // setup software flow control

   bSet = (BYTE) ((m_bFlowCtrl & FC_XONXOFF) != 0) ;

   dcb.fInX = dcb.fOutX = bSet ;
   dcb.XonChar = ASCII_XON ;
   char xon = ASCII_XON ;
   dcb.XoffChar = ASCII_XOFF ;
    char xoff = ASCII_XOFF ;
    dcb.XonLim = 100 ;
   dcb.XoffLim = 100 ;

   // other various settings

   dcb.fBinary = TRUE ;
   dcb.fParity = TRUE ;

   fRetVal = SetCommState( m_hCom, &dcb ) ;

   return ( fRetVal ) ;

} // end of SetupConnection()
BOOL CComStatus::IsConnected()
{
	return m_bConnected;
}
/******************************************************************
*
*			global functions
*
*******************************************************************/
/*******************************************************
function:
	CommWatchProc
describ:
	监视串口数据
********************************************************/
UINT CommWatchProc( LPVOID lpData )
{
   DWORD       dwEvtMask ;
   //NPTTYINFO   npTTYInfo = (NPTTYINFO) lpData ;
   OVERLAPPED  os ;
	int        nLength ;
   //BYTE       abIn[ MAXBLOCK + 1] ;
	CComStatus * pCom = (CComStatus *)lpData;

   memset( &os, 0, sizeof( OVERLAPPED ) ) ;

   // create I/O event used for overlapped read

   os.hEvent = CreateEvent( NULL,    // no security
                            TRUE,    // explicit reset req
                            FALSE,   // initial event reset
                            NULL ) ; // no name
   if (os.hEvent == NULL)
   {
      MessageBox( NULL, "Failed to create event for thread!", "TTY Error!",
                  MB_ICONEXCLAMATION | MB_OK ) ;
      return ( FALSE ) ;
   }

   if (!SetCommMask( pCom->m_hCom, EV_RXCHAR ))
      return ( FALSE ) ;
	char buf[256];
   while ( pCom->m_bConnected )
   {
      dwEvtMask = 0 ;

      WaitCommEvent( pCom->m_hCom, &dwEvtMask, NULL );

      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      {
/*         do
         {*/
		  if ((nLength = ReadCommBlock( *pCom, (LPSTR) buf, 255 )))
            {
               //WriteTTYBlock( hTTYWnd, (LPSTR) abIn, nLength ) ;
			  buf[nLength]='\0';
			  AfxMessageBox(buf);
               // force a paint

               //UpdateWindow( hTTYWnd ) ;
            }
//         }
//         while ( nLength > 0 ) ;
      }
   }

   // get rid of event handle

   CloseHandle( os.hEvent ) ;

   // clear information in structure (kind of a "we're done flag")

//   THREADID( npTTYInfo ) = 0 ;
//   HTHREAD( npTTYInfo ) = NULL ;

   return( TRUE ) ;
} // end of CommWatchProc()
//---------------------------------------------------------------------------
//  int NEAR ReadCommBlock( HWND hWnd, LPSTR lpszBlock, int nMaxLength )
//
//  Description:
//     Reads a block from the COM port and stuffs it into
//     the provided buffer.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     LPSTR lpszBlock
//        block used for storage
//
//     int nMaxLength
//        max length of block to read
//
//  Win-32 Porting Issues:
//     - ReadComm() has been replaced by ReadFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------
int ReadCommBlock(CComStatus& comDev,LPSTR lpszBlock, int nMaxLength )
{
   BOOL       fReadStat ;

   COMSTAT    ComStat ;
   DWORD      dwErrorFlags;
   DWORD      dwLength;
   DWORD      dwError;
   char       szError[ 10 ] ;
   /*NPTTYINFO  npTTYInfo ;

   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;
*/
   // only try to read number of bytes in queue
   ClearCommError( comDev.m_hCom, &dwErrorFlags, &ComStat ) ;
   dwLength = min( (DWORD) nMaxLength, ComStat.cbInQue ) ;

   if (dwLength > 0)
   {
      fReadStat = ReadFile( comDev.m_hCom, lpszBlock,
		                    dwLength, &dwLength, &(comDev.m_rdos) ) ;
/*	  if(WaitForSingleObject(comDev.m_rdos.hEvent,5000) == WAIT_OBJECT_0)
	  {
		GetOverlappedResult( comDev.m_hCom ,
               &(comDev.m_rdos), &dwLength, TRUE );
		//lpszBlo[255] = '0';
		//AfxMessageBox(buf);
	  }*/
      if (!fReadStat)
      {
         if (GetLastError() == ERROR_IO_PENDING)
         {
            OutputDebugString("\n\rIO Pending");
            // We have to wait for read to complete.
            // This function will timeout according to the
            // CommTimeOuts.ReadTotalTimeoutConstant variable
            // Every time it times out, check for port errors
            while(!GetOverlappedResult( comDev.m_hCom ,
               &(comDev.m_rdos), &dwLength, TRUE ))
            {
               dwError = GetLastError();
               if(dwError == ERROR_IO_INCOMPLETE)
                  // normal result if not finished
                  continue;
               else
               {
                  // an error occurred, try to recover
                  wsprintf( szError, "<CE-%u>", dwError ) ;
                  //WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
                  ClearCommError( comDev.m_hCom , &dwErrorFlags, &ComStat ) ;
                  /*if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
                  {
	                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
	                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
                  }*/
                  break;
               }

            }

	      }
         else
         {
            // some other error occurred
            dwLength = 0 ;
            ClearCommError( comDev.m_hCom , &dwErrorFlags, &ComStat ) ;
            /*if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
            {
	            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
	            WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
            }*/
         }
      }
   }

   return ( dwLength ) ;

} // end of ReadCommBlock()
//-------------------------------------------------------
//
//ReadCommBlockEx(CComStatus& comDev,LPSTR lpszBlock, int nMaxLength,DWORD dwTimeOut)
//
//---------------------------------------------------------
//---------------------------------------------------------------------------
int ReadCommBlockEx(CComStatus& comDev,LPSTR lpszBlock, int nMaxLength,DWORD dwTimeOut)
{
	LPSTR lpOffset=lpszBlock;
	int nReadCount = 0;
	char chBuf;
	//time_t beginTime,endTime;
	if(!comDev.m_hCom)
		return 0;
	if(dwTimeOut <= 0)
		return 0;
	MSG msg;
	//time(&beginTime);
	DWORD dwLastTick,dwNowTick,dwGoneTime;
	dwGoneTime = 0;
	dwLastTick = GetTickCount();
	dwNowTick = dwLastTick;
//	double diftime;
	do
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		if(ReadCommBlock(comDev,&chBuf,1) > 0)
		{
			//TRACE("----get a char----\n");
			*lpOffset = chBuf;
			lpOffset ++;
			nReadCount ++;
		}
		/*time(&endTime);
		diftime = difftime(endTime,beginTime);*/
		dwNowTick = GetTickCount();
		if(dwNowTick < dwLastTick)
		{
			dwLastTick = dwNowTick;
		}
		dwGoneTime = dwNowTick - dwLastTick;
		//TRACE("gon time = %lu\n",dwGoneTime);
	}while((nReadCount < nMaxLength) && (dwGoneTime < dwTimeOut));//((diftime * 1000.0) < dwTimeOut));
	return (nReadCount);
}//end ReadCommBlockEx
//  BOOL NEAR WriteCommBlock( HWND hWnd, BYTE *pByte )
//
//  Description:
//     Writes a block of data to the COM port specified in the associated
//     TTY info structure.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     BYTE *pByte
//        pointer to data to write to port
//
//  Win-32 Porting Issues:
//     - WriteComm() has been replaced by WriteFile() in Win-32.
//     - Overlapped I/O has been implemented.
//
//---------------------------------------------------------------------------

BOOL WriteCommBlock( CComStatus& comDev, LPSTR lpByte , DWORD dwBytesToWrite)
{

   BOOL        fWriteStat ;
   DWORD       dwBytesWritten ;
//   NPTTYINFO   npTTYInfo ;
   DWORD       dwErrorFlags;
   DWORD   	dwError;
   DWORD       dwBytesSent=0;
   COMSTAT     ComStat;
   char        szError[ 128 ] ;

/*
   if (NULL == (npTTYInfo = GETNPTTYINFO( hWnd )))
      return ( FALSE ) ;
*/
   fWriteStat = WriteFile( comDev.m_hCom , lpByte, dwBytesToWrite,
                           &dwBytesWritten, &( comDev.m_wtos) ) ;

   // Note that normally the code will not execute the following
   // because the driver caches write operations. Small I/O requests
   // (up to several thousand bytes) will normally be accepted
   // immediately and WriteFile will return true even though an
   // overlapped operation was specified

   if (!fWriteStat)
   {
      if(GetLastError() == ERROR_IO_PENDING)
      {
         // We should wait for the completion of the write operation
         // so we know if it worked or not

         // This is only one way to do this. It might be beneficial to
         // place the write operation in a separate thread
         // so that blocking on completion will not negatively
         // affect the responsiveness of the UI

         // If the write takes too long to complete, this
         // function will timeout according to the
         // CommTimeOuts.WriteTotalTimeoutMultiplier variable.
         // This code logs the timeout but does not retry
         // the write.

         while(!GetOverlappedResult( comDev.m_hCom,
            &(comDev.m_wtos), &dwBytesWritten, TRUE ))
         {
            dwError = GetLastError();
            if(dwError == ERROR_IO_INCOMPLETE)
            {
               // normal result if not finished
               dwBytesSent += dwBytesWritten;
               continue;
            }
            else
            {
               // an error occurred, try to recover
               wsprintf( szError, "<CE-%u>", dwError ) ;
               //WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
               ClearCommError( comDev.m_hCom, &dwErrorFlags, &ComStat ) ;
               /*if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
               {
                  wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
                  WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
               }*/
               break;
            }
         }

         dwBytesSent += dwBytesWritten;

         if( dwBytesSent != dwBytesToWrite )
             wsprintf(szError,"\nProbable Write Timeout: Total of %ld bytes sent", dwBytesSent);
         else
             wsprintf(szError,"\n%ld bytes written", dwBytesSent);

         OutputDebugString(szError);

      }
      else
      {
         // some other error occurred
         ClearCommError( comDev.m_hCom, &dwErrorFlags, &ComStat ) ;
         /*if ((dwErrorFlags > 0) && DISPLAYERRORS( npTTYInfo ))
         {
            wsprintf( szError, "<CE-%u>", dwErrorFlags ) ;
            WriteTTYBlock( hWnd, szError, lstrlen( szError ) ) ;
         }*/
         return ( FALSE );
      }
   }
   return ( TRUE ) ;

} // end of WriteCommBlock()

/*
extern int    fileflash[100];
BOOL FAR InitComDev(HWND hWnd)
{
DCB             dcb;
int x;

if(XwCom&0x10)
    CommStatus.idComDev=OpenComm("COM1\0",1024,1128);
if(XwCom&0x20)
    CommStatus.idComDev=OpenComm("COM2\0",1024,1128);
if(XwCom&0x40)
    CommStatus.idComDev=OpenComm("COM3\0",1024,1128);
if(XwCom&0x80)
    CommStatus.idComDev=OpenComm("COM4\0",1024,1128);

//if ((CommStatus.idComDev=OpenComm(InitCommParam.bPort,1024,1128))<0)
if (CommStatus.idComDev<0)
 {
  MessageBox (hWnd,"打开串行口错误!","错误",MB_ICONSTOP);
  return (FALSE);
 }

GetCommState(CommStatus.idComDev,&dcb);
dcb.BaudRate=InitCommParam.wBaudRate;
dcb.ByteSize=InitCommParam.bByteSize;
dcb.Parity=InitCommParam.bParity;
dcb.StopBits=InitCommParam.bStopBits;
dcb.fChEvt=InitCommParam.fChEvt;
dcb.EvtChar=InitCommParam.bEvtChar;
dcb.fBinary=InitCommParam.fBinary;

x=SetCommState(&dcb);

if (CommStatus.fConnected=!(x<0))
 {
  SetCommEventMask(CommStatus.idComDev,EV_RXFLAG);
  EnableCommNotification(CommStatus.idComDev,hWnd,58,4) ;
  //MAXBLOCKLENGTH,5);
  ClearCommBreak(CommStatus.idComDev);
 }
 else
 {
  MessageBox (hWnd,"串行口设置错误!","错误",MB_ICONSTOP);
  CloseComm(CommStatus.idComDev);
 }
return(CommStatus.fConnected);
}


BOOL FAR ProcessCOMMNotification(HWND hWnd,LPARAM lParam)
{
int    nError=0,x;
unsigned int nLength=0;
BYTE    ch0;
COMSTAT ComStat;

x=0;

while (nError=GetCommError(CommStatus.idComDev,&ComStat));

if (ComStat.cbInQue<1)
       return TRUE;

if((CN_EVENT&LOWORD(lParam))||(CN_RECEIVE&LOWORD(lParam)));
  {

   fileflash[11]++;
   GetCommEventMask(CommStatus.idComDev,EV_RXFLAG);

   if(opation==1)
     { nLength=ReadComm(CommStatus.idComDev,(LPSTR)&sCom2[0],MAXBLOCKLENGTH);
       opation++;
     }
   else if(opation==3)
     { nLength=ReadComm(CommStatus.idComDev,(LPSTR)&sCom3[0],MAXBLOCKLENGTH);
       opation=0;
     }
   else if(opation<0||opation>=4)
     opation=0;
         
   return(TRUE);    
  
  }


}


void SendData(BYTE option)
{
  BYTE sCom1[5];

	if(option==0)
	  strcpy(sCom1,"1100\xd");    
    else if(option==2)
      strcpy(sCom1,"1200\xd");
    else
      return;  
	
    
    FlushComm(CommStatus.idComDev,0);
    FlushComm(CommStatus.idComDev,1);

    WriteComm(CommStatus.idComDev,(LPSTR)sCom1,strlen(sCom1));
    
}


BOOL FAR CloseConnection(HWND hWnd)
{
EnableCommNotification (CommStatus.idComDev,NULL,-1,-1);
CloseComm(CommStatus.idComDev);
CommStatus.fConnected=FALSE;
return (TRUE);
}

void tron(float *buf)
{
  char b[5];
  int i,j,k;
  long ll;
  float *netdata;
     

  netdata=(float *)GlobalLock(downstationdata[6][3].rdata);

  b[4]=0;
  for(k=0;k<100;k++)
    if(sCom2[k]=='A')break;
  if(k==100)
    {
      GlobalUnlock(downstationdata[6][3].rdata);
      return;
    }
  for(i=0;i<13;i++)
   {
    if(i==0||i==1)
      continue;
    for(j=0;j<4;j++)
      b[j]=sCom2[i*4+j+1+k]; 
    ll=0;  
    if(!strcmp("5555",b))
      ll=0;
    else
      sscanf(b,"%x",&ll);
    *(netdata+i-2)=(float)ll;  
   }

  for(k=0;k<100;k++)
    if(sCom3[k]=='B')break;
  if(k==100)
    {
      GlobalUnlock(downstationdata[6][3].rdata);
      return;
    }
  for(i=0;i<14;i++)
   {
    if(i==0||i==1)
      continue; 
      
    for(j=0;j<4;j++)
      b[j]=sCom3[i*4+j+1+k];
    sscanf(b,"%f",netdata+i+11-2);
    *(netdata+i+11-2)/=10;
   }         
  GlobalUnlock(downstationdata[6][3].rdata);
}

*/