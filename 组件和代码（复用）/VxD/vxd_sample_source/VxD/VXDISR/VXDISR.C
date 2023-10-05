#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vxdwraps.h>
#include <vpicd.h>

#include <vxdcall.h>
#include <wrappers.h>
#include <intrinsi.h>

#define RTC_IRQ	8

#define RTC_STATUSA	0xA
#define RTC_STATUSB	0xB
#define RTC_STATUSC	0xC

#define STATUSB_ENINT	0x40	

#define CMOS_ADDR    0x70
#define CMOS_DATA    0x71

typedef struct
{

   VPICD_IRQ_DESCRIPTOR	descIrq;	
   IRQHANDLE	  	hndIrq;
   EVENTHANDLE 		hEvent;			
   DWORD       EventCounter;
   BYTE			StatusA;
   BYTE			StatusB;
} DEVICE_CONTEXT;

DEVICE_CONTEXT	rtc;


BOOL OnDeviceInit(VMHANDLE hVM);
void OnSystemExit(VMHANDLE hVM);
BOOL _stdcall HwIntProcHandler(VMHANDLE hVM, IRQHANDLE hIRQ, void *Refdata);
VOID _stdcall EventHandler(VMHANDLE hVM, PVOID Refdata, CRS *pRegs);
void CmosWriteReg( BYTE reg, BYTE val );
BYTE CmosReadReg( BYTE reg );

// functions in asm module
void EventThunk( void );
void HwIntProcThunk( void );

BOOL OnSysDynamicDeviceInit(VMHANDLE hVM)
{
   OnDeviceInit( hVM );
   return TRUE;
}

BOOL OnSysDynamicDeviceExit(void)
{
   OnSystemExit(Get_Cur_VM_Handle() );
   return TRUE;
}

BOOL OnDeviceInit(VMHANDLE hVM)
{
	rtc.descIrq.VID_IRQ_Number = RTC_IRQ;	
	rtc.descIrq.VID_Options = VPICD_OPT_REF_DATA;		
	rtc.descIrq.VID_Hw_Int_Ref = &rtc;
	rtc.descIrq.VID_Hw_Int_Proc = (ULONG)HwIntProcThunk;
	rtc.descIrq.VID_EOI_Proc = 
	rtc.descIrq.VID_Virt_Int_Proc = 
	rtc.descIrq.VID_Mask_Change_Proc = 
	rtc.descIrq.VID_IRET_Proc = 0;

	rtc.descIrq.VID_IRET_Time_Out = 500;

	if (!(rtc.hndIrq = VPICD_Virtualize_IRQ(&rtc.descIrq)))
		return FALSE;		

	rtc.StatusA = CmosReadReg(RTC_STATUSA);
	rtc.StatusB = CmosReadReg(RTC_STATUSB);

	// set interrupt frequency to only 2 times a sec
	CmosWriteReg(RTC_STATUSA, rtc.StatusA | 0x0F );
	// enable clock interrupts
	CmosWriteReg(RTC_STATUSB, rtc.StatusB | STATUSB_ENINT);
	// clear flags 
	CmosReadReg(RTC_STATUSC);

	rtc.EventCounter = 0;

	VPICD_Physically_Unmask(rtc.hndIrq);

	return TRUE;
}

VOID OnSystemExit(VMHANDLE hVM)
{

	CmosWriteReg(RTC_STATUSA, rtc.StatusA );         
	CmosWriteReg(RTC_STATUSB, rtc.StatusB );

   Cancel_Global_Event(rtc.hEvent);
	VPICD_Physically_Mask(rtc.hndIrq);
	VPICD_Force_Default_Behavior(rtc.hndIrq);
}

BOOL __stdcall HwIntProcHandler(VMHANDLE hVM, IRQHANDLE hIRQ, void *Refdata)
{
   DEVICE_CONTEXT *pRtc = (DEVICE_CONTEXT *)Refdata;

Out_Debug_String("ISR\r\n");
	CmosReadReg( RTC_STATUSC );

	VPICD_Phys_EOI(hIRQ);		// tell VPICD to clear the interrupt

	pRtc->hEvent = Schedule_Global_Event(EventThunk, (ULONG)pRtc );

	return TRUE;	    		// thunk will clear carry
}

VOID __stdcall EventHandler(VMHANDLE hVM, PVOID Refdata, CRS* pRegs)
{
   DEVICE_CONTEXT *rtc = (DEVICE_CONTEXT *)Refdata;

	rtc->hEvent = 0;
   rtc->EventCounter++;
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