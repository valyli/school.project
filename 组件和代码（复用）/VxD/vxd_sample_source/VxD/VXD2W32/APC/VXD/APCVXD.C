#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"

#include <wrappers.h>
#include <vwin32.h>
#include "apcvxd.h"

#ifdef DEBUG
#define DPRINTF0(buf, fmt) _Sprintf(buf, fmt ); Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1) _Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#define DPRINTF2(buf, fmt, arg1, arg2) _Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf, fmt)
#define DPRINTF1(buf, fmt, arg1)
#define DPRINTF2(buf, fmt, arg1, arg2)
#endif

typedef struct tcb_s *PTCB;
char dbgbuf[80];

BOOL bClientRegistered = FALSE;	  
PVOID	    	VmEventApc = 0;	
PTCB 	appThread = 0;	  

BOOL OnVmInit(VMHANDLE hVM)
{
	VMINFO	*pVmInfo;

	if (bClientRegistered)
	{
		pVmInfo = _HeapAllocate( sizeof(VMINFO), 0 );
		if (pVmInfo)
		{
			pVmInfo->hVM = hVM;
			pVmInfo->bVmCreated = TRUE;
			_VWIN32_QueueUserApc(VmEventApc, (DWORD)pVmInfo, appThread);
		}
	}
	return TRUE;
}

VOID OnVmTerminate(VMHANDLE hVM)
{
	VMINFO	*pVmInfo;

	if (bClientRegistered)
	{
		pVmInfo = _HeapAllocate( sizeof(VMINFO), 0 );
		if (pVmInfo)
		{
			pVmInfo->hVM = hVM;
			pVmInfo->bVmCreated = FALSE;
			_VWIN32_QueueUserApc(VmEventApc, (DWORD)pVmInfo, appThread);
		}
	}
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

	case APCVXD_REGISTER:
		VmEventApc = p->lpvInBuffer;
		appThread = Get_Cur_Thread_Handle();
      bClientRegistered = TRUE;
		rc = 0;	// return OK
		break;

	case APCVXD_RELEASEMEM:
		_HeapFree(p->lpvInBuffer, 0);
		rc = 0;
		break;

	default:
		rc = 0xffffffff;
	}

	return rc;
}

