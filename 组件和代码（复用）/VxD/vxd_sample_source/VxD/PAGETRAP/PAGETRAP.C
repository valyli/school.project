// PAGETRAP.c - main module for VxD PAGETRAP

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include <vxdwraps.h>

#include <vxdcall.h>
#include <wrappers.h>
#include <intrinsi.h>

#ifdef DEBUG
#define DPRINTF0(buf)  Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1)  _Sprintf(buf, fmt, arg1); Out_Debug_String( buf )
#else
#define DPRINTF0(buf)  
#define DPRINTF1(buf, fmt, arg1)
#endif

#define DEVICE_PHYS_ADDR	0xB0000L
#define DEVICE_REGION_SIZE  4096

typedef struct
{
	DWORD		RegionSize;
	DWORD		RegionPhysAddr;
	VMHANDLE	VMOwner;
	DWORD		linAddr;
} DEVICE_CONTEXT;


DEVICE_CONTEXT device = { DEVICE_REGION_SIZE, DEVICE_PHYS_ADDR };

char buf[80];

BOOL OnDeviceInit(VMHANDLE hVM);
void OnSystemExit(VMHANDLE hVM);
BOOL OnCreateVm(VMHANDLE hVM);
void OnVmTerminate(VMHANDLE hVM);
DWORD _stdcall PageTrapHandler(VMHANDLE hVM,DWORD PageNumber);

// functions in asm module
void PageFaultThunk( void );

BOOL OnSysDynamicDeviceInit(VMHANDLE hVM)
{
   OnDeviceInit(hVM);
   return TRUE;
}

BOOL OnSysDynamicDeviceExit(void)
{
   OnSystemExit(Get_Cur_VM_Handle());
   return TRUE;
}


BOOL OnDeviceInit(VMHANDLE hVM)
{
	DWORD	PageNum = device.RegionPhysAddr >> 12;
	DWORD   nPages = device.RegionSize / 4096;

	if (!_Assign_Device_V86_Pages(PageNum, nPages, hVM, 0 ))
	{
		DPRINTF0("Assign_Device_V86_Pages failed\r\n");
		return FALSE;
	}

   if (!Hook_V86_Page(PageNum, PageFaultThunk )) 
	{
		DPRINTF0("Hook_V86_Page failed\r\n");
		return FALSE;
	}
    
   if (!_ModifyPageBits(hVM, PageNum, nPages, ~P_AVAIL, 0, PG_HOOKED, 0 ))
	{
		DPRINTF0("ModifyPageBits failed\r\n");
		return FALSE;
	}

   return TRUE;
}

VOID OnSystemExit(VMHANDLE hVM)
{
	DWORD	PageNum = device.RegionPhysAddr >> 12;
	DWORD   nPages = device.RegionSize / 4096;

   if (!Unhook_V86_Page(PageNum, PageFaultThunk ))
   {
      DPRINTF0("Unhook_V86_Page failed\r\n");
   }
   if (!_DeAssign_Device_V86_Pages( PageNum, nPages, hVM, 0))
   {
      DPRINTF0("DeAssign_Device_V86_Pages failed\r\n");
   }
}

BOOL OnCreateVm(VMHANDLE hVM)
{
    if (!_ModifyPageBits(hVM, device.RegionPhysAddr >> 12, device.RegionSize / 4096, 
                        ~P_AVAIL, 0, PG_HOOKED, 0 ))
	{
		DPRINTF0( "ModifyPageBits failed\r\n");
		return FALSE;
	}

	return TRUE;
}


VOID OnVmTerminate(VMHANDLE hVM)
{
   if (hVM == device.VMOwner)
   {
      device.VMOwner = 0;
   }
}


VOID __stdcall PageFaultHandler(VMHANDLE hVM, DWORD PageNumber)
{
	if (device.VMOwner)
	{
		// device already has an owner, owner wouldn't cause a page fault 
		// therefore this VM is not owner
		if (!_MapIntoV86( _GetNulPageHandle(), PageNumber, hVM, 
		                 PageNumber, device.RegionSize / 4096, 0, 0 ))
		{
			DPRINTF0("MapIntoV86 failed\r\n");
		}
	}
	else
	{
		device.VMOwner = hVM;
		_PhysIntoV86( PageNumber, hVM, PageNumber, device.RegionSize / 4096, 0 );
	}
}

