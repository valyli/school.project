#include <conio.h>
#include <windows.h>
#include "intbasic.h"
#include "uart.h"

void interrupt FAR DeviceIsr( void )
{
   BYTE  ier, intid;
   LPBYTE buf;    
   DEVICECONTEXT *hDevice;

   hDevice = &Device1;

   while( TRUE )
   {
      intid = _inp( hDevice->usIoBase + UART_REG_IIR );
      if (intid == UART_IIR_NONE)
         break;

      if (intid == UART_IIR_RXRDY)
      {
         if ((hDevice->RxBuf.In+1==hDevice->RxBuf.Out)
         ||  ((hDevice->RxBuf.Out == 0) && 
              (hDevice->RxBuf.In == hDevice->RxBuf.Size-1)))
         {
            PostMessage( hDevice->hwnd, WM_USER, 0, NULL );
         }
         buf = hDevice->RxBuf.Start;
         buf[ hDevice->RxBuf.In++ ] = _inp( hDevice->usIoBase + UART_REG_RDR );
         if (hDevice->RxBuf.In >= hDevice->RxBuf.Size)
            hDevice->RxBuf.In = 0;
		  }

      else if (intid == UART_IIR_THRE)
      {
         if (hDevice->TxBuf.In==hDevice->TxBuf.Out)
         {
    	      ier = _inp( hDevice->usIoBase + UART_REG_IER );
	          _outp( hDevice->usIoBase + UART_REG_IER, ier & (~UART_IER_THRE) );
         }
         else
         {
            buf = hDevice->TxBuf.Start;
            _outp( hDevice->usIoBase+UART_REG_THR, buf[ hDevice->TxBuf.Out++ ] );
            if (hDevice->TxBuf.Out >= hDevice->TxBuf.Size)
               hDevice->TxBuf.Out = 0;
         }
      }
   }

   if (hDevice->bFlags & FLAGS_ON_SLAVE_PIC)
      _outp( SLAVE_PIC_CTRL, EOI );
   _outp( MASTER_PIC_CTRL, EOI );   
	
}

