#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"
#include <vxdwraps.h>
#include <wrappers.h>
#include <vwin32.h>
#include "postvxd.h"

#ifdef DEBUG
#define DPRINTF0(buf, fmt) _Sprintf(buf, fmt ); Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1) _Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#define DPRINTF2(buf, fmt, arg1, arg2) _Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf, fmt)
#define DPRINTF1(buf, fmt, arg1)
#define DPRINTF2(buf, fmt, arg1, arg2)
#endif

VOID _cdecl PostMessageHandler(DWORD dwPostMessageReturnCode, PVOID refdata);

// functions in asm module
void PriorityEventThunk( void );

BOOL bClientRegistered = FALSE;		// True when PM API called to register
WORD PostMsgOffset;
WORD PostMsgSelector;
HANDLE PostMsghWnd;
char dbgbuf[80];
BOOL  bWin3x;

typedef struct
{
	BOOL	 bVmCreated;
	VMHANDLE hVM;
} VMINFO;

BOOL OnSysDynamicDeviceInit()
{
	DPRINTF0(dbgbuf,"Loading\r\n");
	return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
	DPRINTF0(dbgbuf,"Unloading\r\n");
	return TRUE;
}

BOOL OnInitComplete(VMHANDLE hVM)
{
   DWORD ver;

	ver = Get_VMM_Version();

	if (HIWORD(ver) <= 3)
	{
		// Win3.x, not 95
		bWin3x = TRUE;
   }
}

BOOL OnVmInit(VMHANDLE hVM)
{
   VMINFO   *pInfo;
   
	if (bClientRegistered)
	{
      if (bWin3x)
      {
         pInfo = (VMINFO *)_HeapAllocate( sizeof( VMINFO ), 0 );
         if (pInfo)
         {	
            pInfo->hVM = hVM;
            pInfo->bVmCreated = TRUE;
            Call_Priority_VM_Event(LOW_PRI_DEVICE_BOOST, Get_Sys_VM_Handle(), 
                                   PEF_WAIT_FOR_STI+PEF_WAIT_NOT_CRIT, 
                                   pInfo, PriorityEventThunk, 0 );
         }
      }
      else
      {
   		_SHELL_PostMessage( PostMsghWnd, WM_USER_POSTVXD,
		  					1, (DWORD)hVM,  
		                   PostMessageHandler, NULL );
      }
	}
	return TRUE;
}

VOID OnVmTerminate(VMHANDLE hVM)
{
   VMINFO   *pInfo;

	if (bClientRegistered)
	{
      if (bWin3x)
      {
         pInfo = (VMINFO *)_HeapAllocate( sizeof( VMINFO ), 0 );
         if (pInfo)
         {	
            pInfo->hVM = hVM;
            pInfo->bVmCreated = TRUE;
            Call_Priority_VM_Event(LOW_PRI_DEVICE_BOOST, Get_Sys_VM_Handle(), 
                                   PEF_WAIT_FOR_STI+PEF_WAIT_NOT_CRIT, 
                                   pInfo, PriorityEventThunk, 0 );
         }
      }
      else
      {
   		_SHELL_PostMessage( PostMsghWnd, WM_USER_POSTVXD,
		  					0, hVM,  
		                   PostMessageHandler, NULL );
      }
	}
}

VOID __stdcall PriorityEventHandler(VMHANDLE hVM, PVOID Refdata, CRS *pRegs)
{
   CLIENT_STRUCT   saveRegs;
   VMINFO          *pInfo = Refdata;

   Save_Client_State(&saveRegs);
   Begin_Nest_Exec();
   Simulate_Push(PostMsghWnd);			// hwnd
   Simulate_Push(WM_USER_POSTVXD);			// message
   Simulate_Push(pInfo->bVmCreated);	     		// wParam
   Simulate_Push(((DWORD)pInfo->hVM >> 16) );		// lParam
   Simulate_Push(((DWORD)pInfo->hVM & 0xffff) );
   Simulate_Far_Call(PostMsgSelector, PostMsgOffset);
   Resume_Exec();
   End_Nest_Exec();
   Restore_Client_State(&saveRegs);
   _HeapFree( pInfo, 0 );
}

VOID _cdecl PostMessageHandler(DWORD dwPostMessageReturnCode, PVOID refdata)
{
	if (!dwPostMessageReturnCode)
		DPRINTF0(dbgbuf, "PostMessage failed!\r\n");
}

VOID __cdecl PM_Api_Handler(VMHANDLE hVM, CLIENT_STRUCT *pcrs)
{
	switch (pcrs->CWRS.Client_AX)
	{
	case POSTVXD_REGISTER:
      PostMsghWnd = (HANDLE)pcrs->CWRS.Client_BX;
      PostMsgSelector = pcrs->CWRS.Client_CX;
      PostMsgOffset = pcrs->CWRS.Client_DX;
		bClientRegistered = TRUE;
		pcrs->CWRS.Client_AX = 0;
		break;

	case POSTVXD_DEREGISTER:
		bClientRegistered = FALSE;
		pcrs->CWRS.Client_AX = 0;
		break;

	default:
		pcrs->CWRS.Client_AX = 0xffff;
	}
}

