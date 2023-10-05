    .386p

;******************************************************************************
;                I N C L U D E S
;******************************************************************************

	include vmm.inc
	include debug.inc

;============================================================================
;        V I R T U A L   D E V I C E   D E C L A R A T I O N
;============================================================================

DECLARE_VIRTUAL_DEVICE   REFLECT, 1, 0, ControlProc, UNDEFINED_DEVICE_ID, \
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
    Control_Dispatch DEVICE_INIT, _OnDeviceInit, cCall, <ebx>
    Control_Dispatch SYSTEM_EXIT, _OnSystemExit, cCall, <ebx>
Control_Dispatch SYS_DYNAMIC_DEVICE_INIT, _OnSysDynamicDeviceInit, cCall, <ebx>
Control_Dispatch SYS_DYNAMIC_DEVICE_EXIT, _OnSysDynamicDeviceExit, cCall
    clc
    ret

EndProc ControlProc


PUBLIC _HwIntThunk
_HwIntThunk PROC NEAR ; called from C, needs underscore

    sCall HwIntHandler, <ebx, eax>
	or	  ax, ax
	jz    clearc
    stc
	ret

clearc:
    clc
	ret

 _HwIntThunk ENDP

VxD_LOCKED_CODE_ENDS

VxD_CODE_SEG

PUBLIC _VirtIntThunk
_VirtIntThunk PROC NEAR ; called from C, needs underscore

    sCall VirtIntHandler, <ebx, eax>
    ret

 _VirtIntThunk ENDP


PUBLIC _EOIThunk
_EOIThunk PROC NEAR ; called from C, needs underscore

    sCall EOIHandler, <ebx, eax>
    ret

 _EOIThunk ENDP


PUBLIC _IRETThunk
_IRETThunk PROC NEAR ; called from C, needs underscore

    sCall IRETHandler, <ebx, eax>
    ret

 _IRETThunk ENDP


PUBLIC _MaskChangeThunk
_MaskChangeThunk PROC NEAR ; called from C, needs underscore

    sCall MaskChangeHandler, <ebx, eax, ecx>
    ret

 _MaskChangeThunk ENDP



VXD_CODE_ENDS

    END
