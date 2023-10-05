#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"
#include <vxdwraps.h>
#include <wrappers.h>
#include "intrinsi.h"


#ifdef DEBUG
#define DPRINTF(buf, fmt, arg1, arg2)  _Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF(buf, fmt, arg1, arg2)
#endif

typedef struct tcb_s *PTCB;

BOOL OnSysVmInit(VMHANDLE hVM);
VOID OnSysVmTerminate(VMHANDLE hVM);
BOOL OnCreateVm(VMHANDLE hVM);
VOID OnDestroyVm(VMHANDLE hVM);
BOOL OnCreateThread(PTCB hThread);
VOID OnDestroyThread(PTCB hThread);

#pragma VxD_LOCKED_DATA_SEG

DWORD filepos = 0;
HANDLE fh;
char  buf[80];

#pragma VxD_LOCKED_CODE_SEG


BOOL OnSysVmInit(VMHANDLE hVM)
{
   BYTE  action;
   WORD  err;
   int      count=0;
   PTCB  tcb;

   tcb = Get_Initial_Thread_Handle(hVM);
   DPRINTF(buf, "SysVMInit: VM=%x tcb=%x\r\n", hVM, tcb );

   fh = IFSMgr_Ring0_OpenCreateFile(FALSE, "vxdskel.log", 
                           0x0002, 0x0000, 0x12, 0x00, 
                           &err, &action);
   if (!fh)
   {
      DPRINTF(buf, "Error %x opening file %s\n", err, "vxdskel.log" );
   }
   else
   {
      _Sprintf(buf, "SysVMInit: VM=%x tcb=%x\r\n", hVM, tcb );
      count = IFSMgr_Ring0_WriteFile(FALSE, fh, buf, strlen(buf), filepos, &err);
      filepos += count;
   }
   return TRUE;
}

VOID OnSysVmTerminate(VMHANDLE hVM)
{
   WORD  err;
   int      count=0;
   PTCB  tcb;

   tcb = Get_Initial_Thread_Handle(hVM);
   DPRINTF( buf, "SysVmTerminate VM=%x tcb=%x\r\n", hVM, tcb );
      _Sprintf( buf, "SysVmTerminate VM=%x tcb=%x\r\n", hVM, tcb );
   count = IFSMgr_Ring0_WriteFile(FALSE, fh, buf, strlen(buf), filepos, &err);
   filepos += count;
   IFSMgr_Ring0_CloseFile( fh, &err );
}

BOOL OnCreateVm(VMHANDLE hVM)
{
   PTCB  tcb;
   WORD  err;
   int      count=0;

   tcb = Get_Initial_Thread_Handle(hVM);
    DPRINTF(buf, "Create_VM: VM=%x, tcb=%x\r\n", hVM, tcb); 
    _Sprintf(buf, "Create_VM: VM=%x, tcb=%x\r\n", hVM, tcb);   
   count = IFSMgr_Ring0_WriteFile(FALSE, fh, buf, strlen(buf), filepos, &err);
   filepos += count;
   return TRUE;
}

VOID OnDestroyVm(VMHANDLE hVM)
{
   WORD  err;
   int      count;
   PTCB  tcb;

   tcb = Get_Initial_Thread_Handle(hVM);
    DPRINTF(buf, "Destroy_VM: VM=%x tcb=%x\r\n", hVM, tcb );   
    _Sprintf(buf, "Destroy_VM: VM=%x tcb=%x\r\n", hVM, tcb );  
   count = IFSMgr_Ring0_WriteFile(FALSE, fh, buf, strlen(buf), filepos, &err);
   filepos += count;
}

BOOL OnCreateThread(PTCB tcb)
{
   WORD  err;
   int      count;

   DPRINTF(buf, "Create_Thread: VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb);  
   _Sprintf(buf, "Create_Thread: VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb); 
   count = IFSMgr_Ring0_WriteFile(FALSE, fh, buf, strlen(buf), filepos, &err);
   filepos += count;
   return TRUE;
}

VOID OnDestroyThread(PTCB tcb)
{
   WORD  err;
   int      count;

   DPRINTF( buf, "Destroy_Thread VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb );
   _Sprintf( buf, "Destroy_Thread VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb );
   count = IFSMgr_Ring0_WriteFile(FALSE, fh, buf, strlen(buf), filepos, &err);
   filepos += count;
}
