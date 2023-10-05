#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vxdwraps.h>

#include <vxdcall.h>
#include <wrappers.h>
#include <intrinsi.h>

#ifdef DEBUG
#define DPRINTF0(buf)  Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1)  _Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf)
#define DPRINTF1(buf, fmt, arg1 )
#endif


#define IO_BASE			0x300
#define NUM_IO_PORTS	8
#define FLAGS_CONTENDED	0x0001
typedef struct
{
	WORD		numIoPorts;
	WORD		IoBase;
	VMHANDLE	VMOwner;
	DWORD		cbOffset;
	char		DeviceName[8];
} DEVICE_CONTEXT;

typedef struct
{
	WORD		flags;
} DEVICE_CB;

DEVICE_CONTEXT device = { NUM_IO_PORTS, IO_BASE, NULL, 0, 
 						{'P','O','R','T','T','R','A','P'} };

char buf[80];

BOOL OnDeviceInit(VMHANDLE hVM);
void OnSystemExit(VMHANDLE hVM);
void OnVmTerminate(VMHANDLE hVM);
void SetOwner( VMHANDLE newVMOwner, DEVICE_CONTEXT *dev );
DWORD _stdcall PortTrapHandler(VMHANDLE hVM, DWORD IOType, DWORD Port, 
                               CLIENT_STRUCT *pcrs, DWORD Data);

// functions in asm module
void PortTrapThunk( void );

BOOL OnDeviceInit(VMHANDLE hVM)
{
   int i;
   
   for (i=0; i < device.numIoPorts; i++)
   {
      if (!Install_IO_Handler(device.IoBase+i, PortTrapThunk ))
      {
         DPRINTF1(buf, "Error installing handler for io %x\r\n", IO_BASE+i );
         return FALSE;
      }	
   }
   if (!(device.cbOffset = _Allocate_Device_CB_Area(sizeof(DEVICE_CB), 0)))
   {
      DPRINTF0("Error alloc'ing control block\r\n" );
      return FALSE;
   }	
				
   return TRUE;
}

VOID OnSystemExit(VMHANDLE hVM)
{
   int i;
 
   for (i=0; i < device.numIoPorts; i++)
   {
     if (!Remove_IO_Handler(device.IoBase+i))
     {
        DPRINTF1( buf, "Error removing handler for io %x\r\n", device.IoBase+i);
        break;
     }
   }
   if (device.cbOffset)
      _Deallocate_Device_CB_Area( device.cbOffset, 0 );
}

VOID OnVmTerminate(VMHANDLE hVM)
{
   if (hVM == device.VMOwner)
   {
      device.VMOwner = 0;
   }
}

DWORD _stdcall PortTrapHandler(VMHANDLE hVM, DWORD IOType, DWORD Port, 
                               CLIENT_STRUCT *pcrs, DWORD Data)
{
   DEVICE_CB *pCB;
   BOOL      bThisVMIsOwner;
   VMHANDLE  newVMOwner;

   bThisVMIsOwner = TRUE;

   if (!device.VMOwner)
   {
      // device doesn't have an owner, assign this VM as owner
      SetOwner(hVM, &device);
   }

   else if (device.VMOwner && (device.VMOwner != hVM))
   {
      // device has an owner, but it's not this VM
      pCB = (DEVICE_CB *)((char *)hVM + device.cbOffset);
      if (pCB->flags & FLAGS_CONTENDED)
      {
         // this VM has already attempted to grab the device
         bThisVMIsOwner = FALSE;
      }
      else
      {
         newVMOwner = SHELL_Resolve_Contention(device.VMOwner, hVM, device.DeviceName );
         if (newVMOwner != device.VMOwner)
         {
            bThisVMIsOwner = FALSE;
            Data = 0xFFFFFFFF;
         }
      }
   }

   if (bThisVMIsOwner)
   {
      if (IOType & BYTE_INPUT)
      {
         Data = _inp( Port );
      }
      else if (IOType & BYTE_OUTPUT)	
      {
         _outp( Port, Data );
      }
   }
   else
   {
      Data = 0xFFFFFFFFl;
   }

   return Data;
}


void SetOwner( VMHANDLE newVMOwner, DEVICE_CONTEXT *dev )
{
   int i;

   for (i=0; i < dev->numIoPorts; i++)
   {
      Disable_Local_Trapping( newVMOwner, dev->IoBase+i );
      Enable_Local_Trapping( dev->VMOwner, dev->IoBase+i);
   }
   dev->VMOwner = newVMOwner;
}