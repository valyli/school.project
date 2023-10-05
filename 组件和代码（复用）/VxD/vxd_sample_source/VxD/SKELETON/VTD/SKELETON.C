// SKELETON.c - main module for VxD SKELETON	   e

#define   DEVICE_MAIN
#include  "skeleton.h"
#undef    DEVICE_MAIN

DWORD va_arg_list[2];
DWORD filepos = 0;
HANDLE fh;
  
Declare_Virtual_Device(SKELETON)


DefineControlHandler(SYS_VM_INIT, OnSysVmInit);
DefineControlHandler(SYS_VM_TERMINATE, OnSysVmTerminate);
DefineControlHandler(CREATE_VM, OnCreateVm);
DefineControlHandler(DESTROY_VM, OnDestroyVm);
DefineControlHandler(CREATE_THREAD, OnCreateThread);
DefineControlHandler(DESTROY_THREAD, OnDestroyThread);

BOOL __cdecl ControlDispatcher(
	DWORD dwControlMessage,
	DWORD EBX,
	DWORD EDX,
	DWORD ESI,
	DWORD EDI,
	DWORD ECX)
{
	START_CONTROL_DISPATCH

		ON_SYS_VM_INIT(OnSysVmInit);
		ON_SYS_VM_TERMINATE(OnSysVmTerminate);
		ON_CREATE_VM(OnCreateVm);
		ON_DESTROY_VM(OnDestroyVm);
		ON_CREATE_THREAD(OnCreateThread);
		ON_DESTROY_THREAD(OnDestroyThread);

	END_CONTROL_DISPATCH

	return TRUE;
}


BOOL OnSysVmInit(VMHANDLE hVM)
{
	BYTE	action;
	WORD	err;
	int		count;
	char	buf[80];
	PTCB	tcb;

	tcb = Get_Initial_Thread_Handle(hVM);
    dprintf("SysVmInit: VM=%x, tcb=%x\r\n", hVM, tcb);	

 	fh = R0_OpenCreateFile(FALSE, "vxdskel.log", 0x0002, 0x0000, 0x12, 0x00, &err, &action);
	if (!fh)
		dprintf("Error %x opening file\n", err );
	else
	{
		count = sprintf(buf, "SysVmInit: VM=%x tcb=%x\r\n", hVM, tcb );
		if (count)
		{
			count = R0_WriteFile(FALSE, fh, buf, count, filepos, &err);
			filepos += count;
		}
	}
	return TRUE;
}

VOID OnSysVmTerminate(VMHANDLE hVM)
{
	WORD err;
	int		count;
	char	buf[80];
	PTCB	tcb;

	tcb = Get_Initial_Thread_Handle(hVM);
    dprintf("SysVmTerminate: VM=%x, tcb=%x\r\n", hVM, tcb);	
	count = sprintf(buf, "SysVmTerminate: VM=%x tcb=%x\r\n", hVM, tcb );
	if (count)
	{
		count = R0_WriteFile(FALSE, fh, buf, count, filepos, &err);
		filepos += count;
	}

	R0_CloseFile( fh, &err );
}

BOOL OnCreateVm(VMHANDLE hVM)
{
	WORD err;
	PTCB	tcb;
	int		count;
	char	buf[80];

	tcb = Get_Initial_Thread_Handle(hVM);
    dprintf("Create_VM: VM=%x, tcb=%x\r\n", hVM, tcb);	

	count = sprintf(buf, "Create_VM: VM=%x, tcb=%x\r\n", hVM, tcb );
	if (count)
	{
		count = R0_WriteFile(FALSE, fh, buf, count, filepos, &err);
		filepos += count;
	}
	return TRUE;
}

VOID OnDestroyVm(VMHANDLE hVM)
{
	char	buf[80];
	int		count;
	WORD err;

    dprintf("Destroy_VM: VM=%x tcb=%x\n", hVM );	
	count = sprintf(buf, "Destroy_VM: VM=%x\r\n", hVM );
	if (count)
	{
		count = R0_WriteFile(FALSE, fh, buf, count, filepos, &err);
		filepos += count;
	}
}

BOOL OnCreateThread(THREADHANDLE hThread)
{
	PTCB	tcb = (PTCB)hThread;
	char	buf[80];
	int		count;
	WORD err;

    dprintf("Create_Thread: VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb);	

	count = sprintf(buf, "Create_Thread: VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb );
	if (count)
	{
		count = R0_WriteFile(FALSE, fh, buf, count, filepos, &err);
		filepos += count;
	}
	return TRUE;
}

VOID OnDestroyThread(THREADHANDLE hThread)
{
	PTCB	tcb = (PTCB)hThread;
	char	buf[80];
	int		count;
	WORD err;

    dprintf("Destroy_Thread: VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb);	

	count = sprintf(buf, "Destroy_Thread: VM=%x, tcb=%x\r\n", tcb->TCB_VMHandle, tcb );
	if (count)
	{
		count = R0_WriteFile(FALSE, fh, buf, count, filepos, &err);
		filepos += count;
	}
}


