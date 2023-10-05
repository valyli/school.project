    .386p

;******************************************************************************
;                I N C L U D E S
;******************************************************************************

    include vmm.inc
    include debug.inc

;============================================================================
;        V I R T U A L   D E V I C E   D E C L A R A T I O N
;============================================================================
POSTVXD_ID   EQU     0BADDh   

DECLARE_VIRTUAL_DEVICE    POSTVXD, 1, 0, ControlProc, POSTVXD_ID, \
                        UNDEFINED_INIT_ORDER, 0, PM_API


VxD_LOCKED_CODE_SEG

;===========================================================================
;
;   PROCEDURE: ControlProc
;
;   DESCRIPTION:
;    Device control procedure for the SKELETON VxD
;
;   ENTRY:
;    EAX = Control call ID
;
;   EXIT:
;    If carry clear then
;        Successful
;    else
;        Control call failed
;
;   USES:
;    EAX, EBX, ECX, EDX, ESI, EDI, Flags
;
;============================================================================

BeginProc ControlProc
    Control_Dispatch SYS_DYNAMIC_DEVICE_INIT, _OnSysDynamicDeviceInit, cCall, <ebx>
    Control_Dispatch SYS_DYNAMIC_DEVICE_EXIT, _OnSysDynamicDeviceExit, cCall, <ebx>
    Control_Dispatch INIT_COMPLETE, _OnInitComplete, cCall, <ebx>
    Control_Dispatch VM_INIT, _OnVmInit, cCall, <ebx>
    Control_Dispatch VM_TERMINATE, _OnVmTerminate, cCall, <ebx>
    clc
    ret

EndProc ControlProc

BeginProc PM_API

   cCall _PM_Api_Handler, <ebx, ebp>
   ret

EndProc PM_API

VxD_LOCKED_CODE_ENDS

VxD_CODE_SEG

BeginProc _PriorityEventThunk

   sCall PriorityEventHandler, <ebx,edx,ebp>
	ret

EndProc _PriorityEventThunk

VxD_CODE_ENDS

    END
