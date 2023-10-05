#include <stdlib.h>													   
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define RTC_IRQ	8

#define RTC_STATUSA	0xA
#define RTC_STATUSB	0xB
#define RTC_STATUSC	0xC

#define STATUSB_ENINT	0x40	

#define CMOS_ADDR    0x70
#define CMOS_DATA    0x71

#define DOS_GET_INT_VECTOR          0x35
#define DOS_SET_INT_VECTOR          0x25
#define SLAVE_PIC_MASK              0xA1
#define SLAVE_PIC_CTRL           0xA0
#define MASTER_PIC_CTRL          0x20
#define EOI                      0x20

typedef void (FAR interrupt *VOIDINTPROC)();

static char MsgBoxBuf[ 1024 ] = { 0 };
static VOIDINTPROC pfOldHandler = NULL;
BYTE StatusA, StatusB;

VOIDINTPROC DosGetIntVector( BYTE Irq );
void DosSetIntVector( BYTE Irq, VOIDINTPROC pHandler );
void interrupt FAR RtcIsr( void );

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

BYTE CmosReadReg( BYTE reg )
{
	BYTE	data;

	_asm 
	{
		; disable NMI then ints
		mov	al, reg
		or	al, 80h     
		cli		

		; first output reg to address port
		out	CMOS_ADDR, al
      jmp   _1
_1:
      jmp   _2
_2:   
		; then read data from data port
		in	al, CMOS_DATA
		mov	data, al
      jmp   _3
_3:
      jmp   _4
_4:
		; reenable NMI then ints 
		xor	al, al 
		out	CMOS_ADDR, al
		sti
	}

	return data;
}

void CmosWriteReg( BYTE reg, BYTE val )
{
	_asm 
	{
		; disable NMI then ints
		mov	al, reg
		or	al, 80h		
		cli		

		; first output reg to address port
		out	CMOS_ADDR, al
      jmp   __1
__1:
      jmp   __2
__2:

		; then output val to data port
      mov   al, val
		out 	CMOS_DATA, al
      jmp   __3
__3:
      jmp   __4
__4:

		; reenable NMI then ints 
		xor	al, al 
		out	CMOS_ADDR, al
		sti
	}
}

void interrupt FAR RtcIsr( void )
{
	CmosReadReg( RTC_STATUSC );
   _outp( SLAVE_PIC_CTRL, EOI );
   _outp( MASTER_PIC_CTRL, EOI );   
}

void InstallHandler()
{
   BYTE mask;
   
   // mask (disable) RTC IRQ
	MessageBox( NULL, "Masking IRQ", "RCTTEST", MB_OK );
   mask = _inp( SLAVE_PIC_MASK );
   mask |= 0x01;  // set bit 0 for IRQ 8
   _outp( SLAVE_PIC_MASK, mask );

   // install ISR
   pfOldHandler = DosGetIntVector( 0x70 );
   DosSetIntVector( 0x70, RtcIsr );

   // configure RTC to generate ints
	StatusA = CmosReadReg(RTC_STATUSA);
	StatusB = CmosReadReg(RTC_STATUSB);

	CmosWriteReg(RTC_STATUSA, StatusA | 0x0F );
	// enable clock interrupts
	CmosWriteReg(RTC_STATUSB, StatusB | STATUSB_ENINT);
	// clear flags 
	CmosReadReg(RTC_STATUSC);

   // unmask (enable) RTC IRQ
	MessageBox( NULL, "Unmasking IRQ", "RCTTEST", MB_OK );
   mask = _inp( SLAVE_PIC_MASK );
   mask &= ~0x01;  // clear bit 0 for IRQ 8
   _outp( SLAVE_PIC_MASK, mask );
}

void UnInstallHandler()
{
   BYTE mask;
   
	CmosWriteReg(RTC_STATUSA, StatusA );         
	CmosWriteReg(RTC_STATUSB, StatusB );

   // mask (disable) RTC IRQ
   mask = _inp( SLAVE_PIC_MASK );
   mask |= 0x01;  // set bit 0 for IRQ 8
   _outp( SLAVE_PIC_MASK, mask );

   // install ISR
   DosSetIntVector( 0x70, pfOldHandler );

}

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance, 
                    LPSTR lpCmdLine, int nCmdShow )
{
	char tmpbuf[ 128 ];

   InstallHandler();   
	MessageBox( NULL, "Installed ISR", "RCTTEST", MB_OK );

	MessageBox( NULL, "Dismiss to exit", "RCTTEST", MB_OK );

   UnInstallHandler();   
	MessageBox( NULL, "UnInstalled ISR", "RCTTEST", MB_OK );

	return 0;

}



