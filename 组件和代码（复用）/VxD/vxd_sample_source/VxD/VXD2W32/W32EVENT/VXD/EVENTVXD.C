#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"

#include <wrappers.h>
#include <vwin32.h>
#include "eventvxd.h"

#ifdef DEBUG
#define DPRINTF0(buf, fmt) _Sprintf(buf, fmt ); Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1) _Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#define DPRINTF2(buf, fmt, arg1, arg2) _Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf, fmt)
#define DPRINTF1(buf, fmt, arg1)
#define DPRINTF2(buf, fmt, arg1, arg2)
#endif

// functions in asm module
void PriorityEventThunk( void );

typedef VMINFO *PVMINFO;

VOID __stdcall PriorityEventHandler(VMHANDLE hVM, PVOID Refdata, CRS *pRegs);

BOOL     bClientRegistered = FALSE;		
VMINFO	GlobalVMInfo;
HANDLE	hWin32Event;
char     dbgbuf[80];

BOOL OnVmInit(VMHANDLE hVM)
{
	if (bClientRegistered)
	{
		GlobalVMInfo.hVM = hVM;
		GlobalVMInfo.bVmCreated = TRUE;
		Call_Priority_VM_Event(LOW_PRI_DEVICE_BOOST, Get_Sys_VM_Handle(), 
								PEF_WAIT_FOR_STI+PEF_WAIT_NOT_CRIT, 
								hWin32Event, PriorityEventThunk, 0 );
	}
	return TRUE;
}

VOID OnVmTerminate(VMHANDLE hVM)
{
	if (bClientRegistered)
	{
		GlobalVMInfo.hVM = hVM;
		GlobalVMInfo.bVmCreated = FALSE;
		Call_Priority_VM_Event(LOW_PRI_DEVICE_BOOST, Get_Sys_VM_Handle(), 
								PEF_WAIT_FOR_STI+PEF_WAIT_NOT_CRIT, 
								hWin32Event, PriorityEventThunk, 0 );
	}
}

VOID __stdcall PriorityEventHandler(VMHANDLE hVM, PVOID Refdata, CRS *pRegs)
{
	HANDLE hWin32Event = Refdata;

	_VWIN32_SetWin32Event( hWin32Event );
}

BOOL OnSysDynamicDeviceInit()
{
	DPRINTF0( dbgbuf, "Loading\r\n");
	return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
	DPRINTF0( dbgbuf, "Unloading\r\n");
	return TRUE;
}

DWORD OnW32Deviceiocontrol(PDIOCPARAMETERS p)
{
	DWORD rc;

	switch (p->dwIoControlCode)
	{
	case DIOC_OPEN:	  
		rc = 0; 
		break;

	case DIOC_CLOSEHANDLE:
      bClientRegistered = FALSE;
		rc = 0; 
		break;

	case EVENTVXD_REGISTER:
		hWin32Event = p->lpvInBuffer;
		*((DWORD *)(p->lpvOutBuffer)) = (DWORD)&GlobalVMInfo;
      *((DWORD *)(p->lpcbBytesReturned)) = sizeof(DWORD);
      bClientRegistered = TRUE;
		rc = 0;	
		break;

	default:
		rc = 0xffffffff;
	}

	return rc;
}

