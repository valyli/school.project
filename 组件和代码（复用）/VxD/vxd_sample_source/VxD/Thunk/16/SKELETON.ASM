	page	,132

;Thunk Compiler Version 1.8  May 11 1995 13:16:19
;File Compiled Thu Aug 14 16:47:50 1997

;Command Line: C:\WIN32SDK\BIN\THUNK.EXE -t SKELETON -o skeleton.asm skeleton.thk 

	TITLE	$skeleton.asm

	.386
	OPTION READONLY
	OPTION OLDSTRUCTS

IFNDEF IS_16
IFNDEF IS_32
%out command line error: specify one of -DIS_16, -DIS_32
.err
ENDIF  ;IS_32
ENDIF  ;IS_16


IFDEF IS_32
IFDEF IS_16
%out command line error: you can't specify both -DIS_16 and -DIS_32
.err
ENDIF ;IS_16
;************************* START OF 32-BIT CODE *************************


	.model FLAT,STDCALL


;-- Import common flat thunk routines (in k32)

externDef MapHInstLS	:near32
externDef MapHInstLS_PN	:near32
externDef MapHInstSL	:near32
externDef MapHInstSL_PN	:near32
externDef FT_Prolog	:near32
externDef FT_Thunk	:near32
externDef QT_Thunk	:near32
externDef FT_Exit0	:near32
externDef FT_Exit4	:near32
externDef FT_Exit8	:near32
externDef FT_Exit12	:near32
externDef FT_Exit16	:near32
externDef FT_Exit20	:near32
externDef FT_Exit24	:near32
externDef FT_Exit28	:near32
externDef FT_Exit32	:near32
externDef FT_Exit36	:near32
externDef FT_Exit40	:near32
externDef FT_Exit44	:near32
externDef FT_Exit48	:near32
externDef FT_Exit52	:near32
externDef FT_Exit56	:near32
externDef SMapLS	:near32
externDef SUnMapLS	:near32
externDef SMapLS_IP_EBP_8	:near32
externDef SUnMapLS_IP_EBP_8	:near32
externDef SMapLS_IP_EBP_12	:near32
externDef SUnMapLS_IP_EBP_12	:near32
externDef SMapLS_IP_EBP_16	:near32
externDef SUnMapLS_IP_EBP_16	:near32
externDef SMapLS_IP_EBP_20	:near32
externDef SUnMapLS_IP_EBP_20	:near32
externDef SMapLS_IP_EBP_24	:near32
externDef SUnMapLS_IP_EBP_24	:near32
externDef SMapLS_IP_EBP_28	:near32
externDef SUnMapLS_IP_EBP_28	:near32
externDef SMapLS_IP_EBP_32	:near32
externDef SUnMapLS_IP_EBP_32	:near32
externDef SMapLS_IP_EBP_36	:near32
externDef SUnMapLS_IP_EBP_36	:near32
externDef SMapLS_IP_EBP_40	:near32
externDef SUnMapLS_IP_EBP_40	:near32

MapSL	PROTO NEAR STDCALL p32:DWORD



	.code 

;************************* COMMON PER-MODULE ROUTINES *************************

	.data

public SKELETON_ThunkData32	;This symbol must be exported.
SKELETON_ThunkData32 label dword
	dd	3130534ch	;Protocol 'LS01'
	dd	0c05ch	;Checksum
	dd	0	;Jump table address.
	dd	3130424ch	;'LB01'
	dd	0	;Flags
	dd	0	;Reserved (MUST BE 0)
	dd	0	;Reserved (MUST BE 0)
	dd	offset QT_Thunk_SKELETON - offset SKELETON_ThunkData32
	dd	offset FT_Prolog_SKELETON - offset SKELETON_ThunkData32



	.code 


externDef ThunkConnect32@24:near32

public SKELETON_ThunkConnect32@16
SKELETON_ThunkConnect32@16:
	pop	edx
	push	offset SKELETON_ThkData16
	push	offset SKELETON_ThunkData32
	push	edx
	jmp	ThunkConnect32@24
SKELETON_ThkData16 label byte
	db	"SKELETON_ThunkData16",0


		


pfnQT_Thunk_SKELETON	dd offset QT_Thunk_SKELETON
pfnFT_Prolog_SKELETON	dd offset FT_Prolog_SKELETON
	.data
QT_Thunk_SKELETON label byte
	db	32 dup(0cch)	;Patch space.

FT_Prolog_SKELETON label byte
	db	32 dup(0cch)	;Patch space.


	.code 





;************************ START OF THUNK BODIES************************




;
public DeviceOpen@0
DeviceOpen@0:
	mov	cl,8
; DeviceOpen(16) = DeviceOpen(32) {}
;
;
public IIDeviceOpen@0
IIDeviceOpen@0:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	call	dword ptr [pfnQT_Thunk_SKELETON]
	push	dx
	push	ax
	call	MapSL
	leave
	retn





;
public DeviceClose@4
DeviceClose@4:
	mov	cl,7
; DeviceClose(16) = DeviceClose(32) {}
;
; dword ptr [ebp+8]:  hDevice
;
public IIDeviceClose@4
IIDeviceClose@4:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	call	SMapLS_IP_EBP_8
	push	eax
	call	dword ptr [pfnQT_Thunk_SKELETON]
	cwde
	call	SUnMapLS_IP_EBP_8
	leave
	retn	4





;
public DeviceRead@12
DeviceRead@12:
	mov	cl,3
	jmp	IIDeviceRead@12
public DeviceWrite@12
DeviceWrite@12:
	mov	cl,4
; DeviceRead(16) = DeviceRead(32) {}
;
; dword ptr [ebp+8]:  hDevice
; dword ptr [ebp+12]:  lpData
; dword ptr [ebp+16]:  pcBytes
;
public IIDeviceRead@12
IIDeviceRead@12:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	call	SMapLS_IP_EBP_8
	push	eax
	call	SMapLS_IP_EBP_12
	push	eax
	call	SMapLS_IP_EBP_16
	push	eax
	call	dword ptr [pfnQT_Thunk_SKELETON]
	cwde
	call	SUnMapLS_IP_EBP_8
	call	SUnMapLS_IP_EBP_12
	call	SUnMapLS_IP_EBP_16
	leave
	retn	12





;
public DeviceGetDriverCapabilities@8
DeviceGetDriverCapabilities@8:
	mov	cl,0
	jmp	IIDeviceGetDriverCapabilities@8
public DeviceGetWriteStatus@8
DeviceGetWriteStatus@8:
	mov	cl,6
	jmp	IIDeviceGetDriverCapabilities@8
public DeviceGetReadStatus@8
DeviceGetReadStatus@8:
	mov	cl,5
	jmp	IIDeviceGetDriverCapabilities@8
public DeviceSetDriverParams@8
DeviceSetDriverParams@8:
	mov	cl,2
	jmp	IIDeviceGetDriverCapabilities@8
public DeviceGetDriverParams@8
DeviceGetDriverParams@8:
	mov	cl,1
; DeviceGetDriverCapabilities(16) = DeviceGetDriverCapabilities(32) {}
;
; dword ptr [ebp+8]:  hDevice
; dword ptr [ebp+12]:  ppDriverCaps
;
public IIDeviceGetDriverCapabilities@8
IIDeviceGetDriverCapabilities@8:
	push	ebp
	mov	ebp,esp
	push	ecx
	sub	esp,60
	call	SMapLS_IP_EBP_8
	push	eax
	call	SMapLS_IP_EBP_12
	push	eax
	call	dword ptr [pfnQT_Thunk_SKELETON]
	cwde
	call	SUnMapLS_IP_EBP_8
	call	SUnMapLS_IP_EBP_12
	leave
	retn	8




ELSE
;************************* START OF 16-BIT CODE *************************




	OPTION SEGMENT:USE16
	.model LARGE,PASCAL


	.code	



externDef DeviceGetDriverCapabilities:far16
externDef DeviceGetDriverParams:far16
externDef DeviceSetDriverParams:far16
externDef DeviceRead:far16
externDef DeviceWrite:far16
externDef DeviceGetReadStatus:far16
externDef DeviceGetWriteStatus:far16
externDef DeviceClose:far16
externDef DeviceOpen:far16


FT_SKELETONTargetTable label word
	dw	offset DeviceGetDriverCapabilities
	dw	   seg DeviceGetDriverCapabilities
	dw	offset DeviceGetDriverParams
	dw	   seg DeviceGetDriverParams
	dw	offset DeviceSetDriverParams
	dw	   seg DeviceSetDriverParams
	dw	offset DeviceRead
	dw	   seg DeviceRead
	dw	offset DeviceWrite
	dw	   seg DeviceWrite
	dw	offset DeviceGetReadStatus
	dw	   seg DeviceGetReadStatus
	dw	offset DeviceGetWriteStatus
	dw	   seg DeviceGetWriteStatus
	dw	offset DeviceClose
	dw	   seg DeviceClose
	dw	offset DeviceOpen
	dw	   seg DeviceOpen




	.data

public SKELETON_ThunkData16	;This symbol must be exported.
SKELETON_ThunkData16	dd	3130534ch	;Protocol 'LS01'
	dd	0c05ch	;Checksum
	dw	offset FT_SKELETONTargetTable
	dw	seg    FT_SKELETONTargetTable
	dd	0	;First-time flag.



	.code 


externDef ThunkConnect16:far16

public SKELETON_ThunkConnect16
SKELETON_ThunkConnect16:
	pop	ax
	pop	dx
	push	seg    SKELETON_ThunkData16
	push	offset SKELETON_ThunkData16
	push	seg    SKELETON_ThkData32
	push	offset SKELETON_ThkData32
	push	cs
	push	dx
	push	ax
	jmp	ThunkConnect16
SKELETON_ThkData32 label byte
	db	"SKELETON_ThunkData32",0





ENDIF
END
