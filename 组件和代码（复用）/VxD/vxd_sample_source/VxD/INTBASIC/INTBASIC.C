#include <dos.h>
#include <conio.h>
#include <windows.h>
#include <windowsx.h>
#include "intbasic.h"
#include "uart.h"
#include "isr.h"
#include "malloc.h"

#define DOS_GET_INT_VECTOR          0x35
#define DOS_SET_INT_VECTOR          0x25

DEVICECONTEXT Device1 = { 0, 0x3F8, 4, 0, NULL };
DRIVERPARAMS DefaultParams = { 1024 };
DRIVERCAPS DriverCaps = { 0x0101 };

BOOL ValidHandle( HDEVICE hDevice );
VOIDINTPROC DosGetIntVector( BYTE Irq );
void DosSetIntVector( BYTE Irq, VOIDINTPROC pHandler );
void interrupt FAR DeviceIsr( void );
UINT SafePageLock( HGLOBAL sel );

HDEVICE FAR PASCAL _export DeviceOpen( HWND hwnd )
{
	HDEVICE	hDevice;
 	BYTE		bVector, mask;
  WORD    mycs, myds;

	OutputDebugString( "DeviceOpen\n");

	hDevice = &Device1;

	if (hDevice->bFlags & FLAGS_OPEN)
  {
  	OutputDebugString( "ERROR already open\n");
		return (HDEVICE)-1;
  }

	hDevice->params = DefaultParams;
   hDevice->hwnd = hwnd;

   hDevice->RxBuf.Size = hDevice->params.usReadBufSize;
	 hDevice->RxBuf.Start = GlobalAllocPtr( GMEM_SHARE | 
                                          GMEM_MOVEABLE | 
                                          GMEM_NODISCARD, 
                                          hDevice->RxBuf.Size  );
   if (!hDevice->RxBuf.Start)
   {
      OutputDebugString( "ERROR GlobalAlloc Rx\n");
	  	return (HDEVICE)-1;
   }
   SafePageLock( (HGLOBAL)SELECTOROF( hDevice->RxBuf.Start ));
   hDevice->RxBuf.In = hDevice->RxBuf.Out = 0;

   hDevice->TxBuf.Size = hDevice->params.usReadBufSize;
	 hDevice->TxBuf.Start = GlobalAllocPtr( GMEM_SHARE | 
                                          GMEM_MOVEABLE | 
                                          GMEM_NODISCARD, 
                                          hDevice->TxBuf.Size  );
   if (!hDevice->TxBuf.Start)
   {
      OutputDebugString( "ERROR GlobalAlloc Tx\n");
	  	return (HDEVICE)-1;
   }
   SafePageLock( (HGLOBAL)SELECTOROF( hDevice->TxBuf.Start ));
   hDevice->TxBuf.In = hDevice->TxBuf.Out = 0;
 
   _asm mov myds, ds
   _asm mov mycs, cs
   SafePageLock( myds );
   SafePageLock( mycs );

   if (hDevice->bIrq < 8)
   {
      mask = _inp( MASTER_PIC_MASK );
      SET( mask, 1 << hDevice->bIrq );
      _outp( MASTER_PIC_MASK, mask );
   }
   else
   {
      SET( hDevice->bFlags, FLAGS_ON_SLAVE_PIC );
      mask = _inp( SLAVE_PIC_MASK );
      SET( mask, 1 << (hDevice->bIrq-8) );
      _outp( SLAVE_PIC_MASK, mask );
   }

   if (hDevice->bIrq < 8)
      bVector = hDevice->bIrq + 0x08;
   else
      bVector = hDevice->bIrq - 8 + 0x70;
   hDevice->pfOldHandler = DosGetIntVector( bVector );
   DosSetIntVector( bVector, DeviceIsr );

   // Configure UART.
   _outp( hDevice->usIoBase+UART_REG_IER, 0 );
   _outp( hDevice->usIoBase+UART_REG_LCR, UART_LCR_DLAB );
   _outp( hDevice->usIoBase+UART_REG_BAUDLO, BAUD_1200 );
   _outp( hDevice->usIoBase+UART_REG_BAUDHI, 0 );
   _outp( hDevice->usIoBase+UART_REG_LCR, UART_LCR_8N1 );
   _outp( hDevice->usIoBase+UART_REG_IER, UART_IER_RXRDY );
   _outp( hDevice->usIoBase+UART_REG_MCR, UART_MCR_OUT2 );

   // Unmask interrupt at PIC.
   if (hDevice->bIrq < 8)
   {
      mask = _inp( MASTER_PIC_MASK );
      CLR( mask, (1 << hDevice->bIrq) );
      _outp( MASTER_PIC_MASK, mask );
   }
   else
   {
      mask = _inp( SLAVE_PIC_MASK );
      CLR( mask, (1 << (hDevice->bIrq-8)) );
      _outp( SLAVE_PIC_MASK, mask );
   }

   SET( hDevice->bFlags, FLAGS_OPEN );

	 return hDevice;
}

int FAR PASCAL _export DeviceClose( HDEVICE hDevice )
{
	BYTE	mask, bVector;

	OutputDebugString( "DeviceClose\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return FALSE;

	CLR( hDevice->bFlags, FLAGS_OPEN );

   // Disable UART interrupts.
   _outp( hDevice->usIoBase + UART_REG_IER, 0 );
   _outp( hDevice->usIoBase + UART_REG_MCR, 0 );

   if (hDevice->bIrq < 8)
   {
      mask = _inp( MASTER_PIC_MASK );
      SET( mask, 1 << hDevice->bIrq );
      _outp( MASTER_PIC_MASK, mask );
   }
   else
   {
      SET( hDevice->bFlags, FLAGS_ON_SLAVE_PIC );
      mask = _inp( SLAVE_PIC_MASK );
      SET( mask, 1 << (hDevice->bIrq-8) );
      _outp( SLAVE_PIC_MASK, mask );
   }

   if (hDevice->bIrq < 8)
      bVector = hDevice->bIrq + 0x08;
   else
      bVector = hDevice->bIrq - 8 + 0x70;
   DosSetIntVector( bVector, hDevice->pfOldHandler );

	GlobalFreePtr( hDevice->RxBuf.Start  );
	GlobalFreePtr( hDevice->TxBuf.Start  );

	return 0;
}

int FAR PASCAL _export DeviceGetWriteStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	OutputDebugString( "DeviceGetWriteStatus\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

   if (_inp( hDevice->usIoBase + UART_REG_LSR ) & UART_LSR_THRE)
	{
		*pusStatus = 1;		// ready to transmit
	}
	else
	{
		*pusStatus = 0;		// not ready to transmit
	}

	return 0;
}

int FAR PASCAL _export DeviceGetReadStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	OutputDebugString( "DeviceGetReadStatus\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	if (hDevice->RxBuf.In != hDevice->RxBuf.Out)
	{
		*pusStatus = 1;		// data ready
	}
	else
	{
		*pusStatus = 0;		// no data ready
	}

	return 0;
}

int FAR PASCAL _export DeviceWrite( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	WORD	i;
  char  ier;

	OutputDebugString( "DeviceWrite\n");

	if (!lpData)
  {
  	OutputDebugString( "ERROR\n");
		return -1;
  }

	if (!ValidHandle( hDevice ))
  {
  	OutputDebugString( "ERROR\n");
		return -1;
  }

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
  {
  	OutputDebugString( "ERROR\n");
		return -1;
  }

	for (i=0; i < *pcBytes; i++)
	{
    hDevice->TxBuf.Start[ hDevice->TxBuf.In++ ] = lpData[ i ];           
    if (hDevice->TxBuf.In >= hDevice->TxBuf.Size)
       hDevice->TxBuf.In = 0;
	}

  if (UART_LSR_THRE & _inp( hDevice->usIoBase+UART_REG_LSR ))
  {
     ier = _inp( hDevice->usIoBase+UART_REG_IER );
     if ((UART_IER_THRE & ier) == 0)
     {
        _outp( hDevice->usIoBase+UART_REG_IER, 
     	  ier | UART_IER_THRE );
     }
  }

	return 0;
}

int FAR PASCAL _export DeviceRead( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	WORD	cBytes, i;

	OutputDebugString( "DeviceRead\n");

	if (!lpData)
  {
  	OutputDebugString( "ERROR\n");
		return -1;
  }

	if (!ValidHandle( hDevice ))
  {
  	OutputDebugString( "ERROR\n");
		return -1;
  }

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
  {
  	OutputDebugString( "ERROR\n");
		return -1;
  }

	cBytes = *pcBytes;

	for (i=0; i < cBytes; i++)
	{
		if (hDevice->RxBuf.In == hDevice->RxBuf.Out)
			break;
		lpData[i] = hDevice->RxBuf.Start[ hDevice->RxBuf.Out++ ];
    if (hDevice->RxBuf.Out >= hDevice->RxBuf.Size)
       hDevice->RxBuf.Out = 0;
		*pcBytes--;
	}

	return 0;
}

int FAR PASCAL _export DeviceSetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParams )
{
	OutputDebugString( "DeviceSetDriverParams\n");

	if (!pParams)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	hDevice->params = *pParams;
  
	return 0;
}

int FAR PASCAL _export DeviceGetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParams )
{
	OutputDebugString( "DeviceGetDriverParams\n");

	if (!pParams)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	*pParams = hDevice->params;

	return 0;
}

int FAR PASCAL _export DeviceGetDriverCapabilities( HDEVICE hDevice, PPDRIVERCAPS ppDriverCaps )
{
	OutputDebugString( "DeviceGetDriverCapabilities\n");

	if (!ppDriverCaps)
		return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	*ppDriverCaps = &DriverCaps;

	return 0;
}

BOOL ValidHandle( HDEVICE hDevice )
{
	return (hDevice == &Device1);
}

VOIDINTPROC DosGetIntVector( BYTE vector )
{
   WORD  selHandler, offHandler;

   _asm
   {
      mov  al, vector
      mov  ah, DOS_GET_INT_VECTOR
      push es
      int  21h
      mov  offHandler,bx
      mov  selHandler,es
      pop  es
   }
   return( MAKELP( selHandler, offHandler ) );
}

void DosSetIntVector( BYTE vector, VOIDINTPROC pHandler )
{
   WORD  offHandler, selHandler;

   selHandler = SELECTOROF( pHandler );
   offHandler = OFFSETOF( pHandler );

  _asm
   {
      mov  al, vector
      mov  ah, DOS_SET_INT_VECTOR
      mov  dx, offHandler
      mov  bx, selHandler
      push ds
      mov  ds, bx
      int  21h
      pop  ds
   }
}

UINT SafePageLock( HGLOBAL sel )
{
   WORD i, rc;
static WORD SelArray[ 1024 ];

   memset( SelArray, 1024 * sizeof(WORD), 0 );
   for (i=0; i < 1024; i++)
   {
      SelArray[i] = LOWORD( GlobalDosAlloc( 1024 ) );
      if (!SelArray[i])
         break;
   }

   rc = GlobalPageLock( sel );

   for (i=0; i < 1024; i++)
   {
      if (!SelArray[i])
         break;
      GlobalFree( SelArray[i] );
   }

   return rc;
}




