    .386p

;******************************************************************************
;                I N C L U D E S
;******************************************************************************

    include vmm.inc
    include debug.inc

;============================================================================
;        V I R T U A L   D E V I C E   D E C L A R A T I O N
;============================================================================

DECLARE_VIRTUAL_DEVICE    TRICORD, 1, 0, ControlProc, UNDEFINED_DEVICE_ID, \
                        UNDEFINED_INIT_ORDER

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
    Control_Dispatch PNP_NEW_DEVNODE, _OnPNPNewDevnode, cCall, <ebx, edx>

    clc
    ret

EndProc ControlProc

PUBLIC _HwIntProcThunk
_HwIntProcThunk PROC NEAR ; called from C, needs underscore

   sCall HwIntProcHandler, <eax, ebx, edx>
	or    ax, ax
	jnz    clearc
   stc
	ret

clearc:
   clc
	ret

 _HwIntProcThunk ENDP

VxD_LOCKED_CODE_ENDS

    END
