// REFLECT.c - main module for VxD REFLECT
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
   IRQHANDLE	  	IrqHandle;
   VMHANDLE       VMOwner;
   char           DeviceName[8];
   BOOL           bVMIsServicing;
} DEVICE_CONTEXT;

// functions in asm module
void HwIntThunk( void );
void VirtIntThunk( void );
void EOIThunk( void );
void MaskChangeThunk( void );
void IRETThunk( void );

DEVICE_CONTEXT	device = { 0, 0, 
                           {'R','E','F','L','E','C','T'} };

VPICD_IRQ_DESCRIPTOR IrqDesc = { RTC_IRQ, VPICD_OPT_REF_DATA, 
                                 HwIntThunk, VirtIntThunk, EOIThunk, 
                                 MaskChangeThunk, IRETThunk, 500, 
                                 &device };


BOOL OnDeviceInit(VMHANDLE hVM);
void OnSystemExit(VMHANDLE hVM);
BOOL _stdcall HwIntHandler(VMHANDLE hVM, IRQHANDLE hIRQ);
void _stdcall EOIHandler(VMHANDLE hVM, IRQHANDLE hIRQ);
void _stdcall VirtIntHandler(VMHANDLE hVM, IRQHANDLE hIRQ);
void _stdcall IRETHandler(VMHANDLE hVM, IRQHANDLE hIRQ);
void _stdcall MaskChangeHandler(VMHANDLE hVM, IRQHANDLE hIRQ, BOOL bMasking);
void EatInt( void );
void CmosWriteReg( BYTE reg, BYTE val );
BYTE CmosReadReg( BYTE reg );


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
	if (!(device.IrqHandle = VPICD_Virtualize_IRQ(&IrqDesc)))
		return FALSE;		

	return TRUE;
}

VOID OnSystemExit(VMHANDLE hVM)
{
	VPICD_Force_Default_Behavior(device.IrqHandle);
}

BOOL _stdcall HwIntHandler(VMHANDLE hVM, IRQHANDLE hIRQ)
{
   if (device.VMOwner && !device.bVMIsServicing)
   {
      VPICD_Set_Int_Request( device.VMOwner, hIRQ );
   }
   else
   {
      EatInt();
   }
   return TRUE;
}

void EatInt( void )
{
   unsigned char temp;

   temp = CmosReadReg( RTC_STATUSC );
   VPICD_Phys_EOI( device.IrqHandle );   
}

void _stdcall EOIHandler(VMHANDLE hVM, IRQHANDLE hIRQ)
{
   VPICD_Phys_EOI( hIRQ );
   VPICD_Clear_Int_Request( device.VMOwner, hIRQ );
}

void _stdcall VirtIntHandler(VMHANDLE hVM, IRQHANDLE hIRQ)
{
   device.bVMIsServicing = TRUE;
}

void _stdcall IRETHandler(VMHANDLE hVM, IRQHANDLE hIRQ)
{
   device.bVMIsServicing = FALSE;
}

void _stdcall MaskChangeHandler(VMHANDLE hVM, IRQHANDLE hIRQ, BOOL bMasking)
{
   if (!bMasking)
   {
      if (!device.VMOwner)
      {
         device.VMOwner = hVM;
      }
      else 
      {
         if (device.VMOwner != hVM)
         {
            device.VMOwner = SHELL_Resolve_Contention(device.VMOwner, 
                                               hVM, device.DeviceName );
         }
      }
      VPICD_Physically_Unmask( hIRQ );         
   }
   else
   {
      device.VMOwner = 0;
      VPICD_Physically_Mask( hIRQ );
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