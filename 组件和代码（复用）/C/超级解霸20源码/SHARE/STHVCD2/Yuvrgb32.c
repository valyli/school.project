////////////////////////////////////////////////////////
//		YUV data write to Offscreen
//	     In Order fastest and optimization
//	       This code use 32 Bits' segment
//		    Southern.Liang
//		       1996.7.4
////////////////////////////////////////////////////////
// Remember fixed the retf to 0x66 retf,use 32,'code' etc
#pragma	inline
#pragma	option	-zCYUVRGB32_TEXT	//This Must in YUVRGB32_TEXT
#include "VCDAPI.H"
extern	long	VCDHigh;
extern	short	OffScrSel;
extern	unsigned long	LinearOffSurface;
extern	unsigned long	LinearSelSurface;

void	PASCAL	FAR	DrawYVU12(void)	//YVU12 Planar
{
	_EDI=_EDI;
	asm	xor	eax,eax
	asm	push	ds
//	_ES=LinearSelSurface;
//	_EDX=VCDHigh;
//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	asm	mov	ds,OffScrSel;
	asm	mov	esi,[eax+4]
	asm	mov	ebx,[eax+8]
	asm	mov	ds,[eax+0x10]	//GS-> Video data
	///////// Move Y Data //////////
	asm	push	edx
	MoveYData:
		_ECX=88;
		asm	rep	movsd//32 bits address
		_ESI+=800;
	asm	dec	edx
	asm	jnz	MoveYData
	////////// Move V Data //////////
	_ESI=_EBX;
	_ESI+=0x240;	//VPlane
	asm	pop	edx
	asm	shr	edx,1	//_EDX/=2;
	asm	push	edx
	MoveVData:
		_ECX=44;
		asm	rep	movsd//32 bits address
		_ESI+=976;
	asm	dec	edx
	asm	jnz	MoveVData
	////////// Move U Data //////////
	_ESI=_EBX;	//UPlane
	asm	pop	edx
	MoveUData:
		_ECX=44;
		asm	rep	movsd//32 bits address
		_ESI+=976;
	asm	dec	edx
	asm	jnz	MoveUData
	asm	pop	ds
}

void	PASCAL	FAR	DrawYVU9(void)	//YVU9 Planar
{
	_EDI=_EDI;
	asm	xor	eax,eax
	asm	push	ds
//	_EDX=VCDHigh;
//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
//	_ES=LinearSelSurface;
	asm	mov	ds,OffScrSel;
	asm 	mov 	esi,[eax+4]
	asm 	mov 	ebx,[eax+8]
	asm	mov 	ds,[eax+0x10]	//DS-> Video data
	///////// Move Y Data //////////
	asm	push	edx
	MoveYData:
		_ECX=88;
		asm	rep	movsd//32 bits address
		_ESI+=800;
	asm	dec	edx
	asm	jnz	MoveYData
	/////////////////////////////////
	asm	pop	edx
	////////// Move V Data //////////
	_ESI=_EBX;
	asm	shr	edx,2	//_EDX/=4;
	_ESI+=0x240;	//VPlane
	asm	push	edx
	MoveVData:
		_EBP=176/16;
		MoveVdata:
		asm	mov	al,[esi+4]
		asm	mov	cl,[esi+12]
		asm	mov	ah,[esi+6]
		asm	mov	ch,[esi+14]
		asm	shl	eax,16
		asm	shl	ecx,16
		asm	mov	al,[esi]
		asm	mov	cl,[esi+8]
		asm	mov	ah,[esi+2]
		asm	mov	es:[edi],eax
		asm	mov	ch,[esi+10]
		asm	mov	es:[edi+4],ecx
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	ebp
		asm	jnz	MoveVdata
		_ESI+=(976+0x480);
	asm	dec	edx
	asm	jnz	MoveVData
	////////// Move U Data //////////
	_ESI=_EBX;	//UPlane
	asm	pop	edx
	MoveUData:
		_EBP=176/16;
		MoveUdata:
		asm	mov	al,[esi+4]
		asm	mov	cl,[esi+12]
		asm	mov	ah,[esi+6]
		asm	mov	ch,[esi+14]
		asm	shl	eax,16
		asm	shl	ecx,16
		asm	mov	al,[esi]
		asm	mov	cl,[esi+8]
		asm	mov	ah,[esi+2]
		asm	mov	es:[edi],eax
		asm	mov	ch,[esi+10]
		asm	mov	es:[edi+4],ecx
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	ebp
		asm	jnz	MoveUdata
		_ESI+=(976+0x480);
	asm	dec	edx
	asm	jnz	MoveUData
	asm	pop	ds
}

void	PASCAL	FAR	DrawIF09(void)	//YVU9 Planar and pitch
{
	_EDI=_EDI;
	asm	xor	eax,eax
	asm	push	ds
	_EDX=288;
	asm	mov	ds,OffScrSel;
	asm 	mov 	esi,[eax+4]
	asm 	mov 	ebx,[eax+8]
	asm	mov 	ds,[eax+0x10]	//GS-> Video data
	///////// Move Y Data //////////
	MoveYData:
		_ECX=88;
		asm	rep	movsd//32 bits address
		_ESI+=800;
	asm	dec	edx
	asm	jnz	MoveYData
	/////////////////////////////////
	////////// Move V Data //////////
	_ESI=_EBX;
	_ESI+=0x240;	//VPlane
	_EDX=72;
	MoveVData:
		_EBP=176/16;
		MoveVdata:
		asm	mov	al,[esi+4]
		asm	mov	cl,[esi+12]
		asm	mov	ah,[esi+6]
		asm	mov	ch,[esi+14]
		asm	shl	eax,16
		asm	shl	ecx,16
		asm	mov	al,[esi]
		asm	mov	cl,[esi+8]
		asm	mov	ah,[esi+2]
		asm	mov	es:[edi],eax
		asm	mov	ch,[esi+10]
		asm	mov	es:[edi+4],ecx
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	ebp
		asm	jnz	MoveVdata
		_ESI+=(976+0x480);
	asm	dec	edx
	asm	jnz	MoveVData
	////////// Move U Data //////////
	_ESI=_EBX;	//UPlane
	_EDX=72;
	MoveUData:
		_EBP=176/16;
		MoveUdata:
		asm	mov	al,[esi+4]
		asm	mov	cl,[esi+12]
		asm	mov	ah,[esi+6]
		asm	mov	ch,[esi+14]
		asm	shl	eax,16
		asm	shl	ecx,16
		asm	mov	al,[esi]
		asm	mov	cl,[esi+8]
		asm	mov	ah,[esi+2]
		asm	mov	es:[edi],eax
		asm	mov	ch,[esi+10]
		asm	mov	es:[edi+4],ecx
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	ebp
		asm	jnz	MoveUdata
		_ESI+=(976+0x480);
	asm	dec	edx
	asm	jnz	MoveUData
	asm	pop	ds
}
void	PASCAL	FAR	DrawYUY2(void)	//YUYV 4:2:2 byte ordering
{
	asm	xor	eax,eax
	asm	push	ds
//	_EDX=VCDHigh;
//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
//	_ES=LinearSelSurface;
	asm	mov	ds,OffScrSel;
	asm 	mov 	esi,[eax+4]
	asm	mov 	ecx,[eax+8]	//ECX->V,U plane
	asm	mov 	ds,[eax+0x10]	//DS-> Video data
	///////// Move YUYV Data //////////
	asm	shr	edx,1//_EDX/=2;
	MoveYUY2Data:
		_EBP=176/2;
		asm	push	edx
		Move2LineData:
		asm	mov	ah,[ecx+0x240]
		asm	mov	bh,[ecx+0x241]
		asm	mov	al,[esi+1]
		asm	mov	bl,[esi+3]
		asm	shl	eax,16		//V0Y1
		asm	mov	dh,[ecx+0x240]
		asm	shl	ebx,16		//V1Y3
		asm	mov	al,[esi]
		asm	mov	ah,[ecx]	//U0Y0
		asm	mov	dl,[esi+0x480+1]
		asm	shl	edx,16		//V0Y1
		asm	mov	bh,[ecx+1]	//U1Y2
		asm	mov	es:[edi],eax		//Y1V0Y0U0
		asm	mov	bl,[esi+2]
		asm	mov	es:[edi+4],ebx		//Y3V1Y2U1
		asm	mov	dl,[esi+0x480]
		asm	mov	bh,[ecx+0x241]
		asm	mov	dh,[ecx]	//U0Y0
		asm	mov	es:[edi+704],edx
		asm	mov	bl,[esi+0x480+3]
		asm	shl	ebx,16		//V1Y3
		asm	mov	bl,[esi+0x480+2]
		asm	add	esi,4
		asm	mov	bh,[ecx+1]	//U1Y2
		asm	add	ecx,2
		asm	mov	es:[edi+704+4],ebx
		asm	add	edi,8
		asm	dec	ebp
		asm	jnz	Move2LineData
	_ECX+=976;
	asm	pop	edx
	_ESI+=(800+0x480);
	_EDI+=704;
	asm	dec	edx
	asm	jnz	MoveYUY2Data
	asm	pop	ds
}

void	PASCAL	FAR	DrawYVYU(void)	//YVYU 4:2:2 byte ordering
{
	asm	xor	eax,eax
	asm	push	ds
//	_EDX=VCDHigh;
//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
//	_ES=LinearSelSurface;
	asm	mov	ds,OffScrSel;
	asm 	mov 	esi,[eax+4]
	asm	mov 	ecx,[eax+8]
	asm	mov 	ds,[eax+0x10]	//DS-> Video data
	///////// Move YUYV Data //////////
	asm	shr	edx,1	//DX=_EBX/2;
	MoveYUY2Data:
		_EBP=176/2;
		asm	push	edx
		Move2LineData:
		asm	mov	ah,[ecx]	//U0
		asm	mov	bl,[esi+3]	//Y3
		asm	mov	al,[esi+1]	//Y1
		asm	mov	bh,[ecx+1]	//U1
		asm	shl	eax,16		//U0Y1
		asm	mov	dh,[ecx]	//U0
		asm	shl	ebx,16		//U1Y3
		asm	mov	dl,[esi+0x480+1]
		asm	mov	al,[esi]
		asm	mov	bh,[ecx+0x241]	//V1Y2
		asm	shl	edx,16		//U0Y1
		asm	mov	ah,[ecx+0x240]	//V0Y0
		asm	mov	bl,[esi+2]
		asm	mov	dl,[esi+0x480]
		asm	mov	es:[edi+4],ebx		//Y2V1Y3U1
		asm	mov	dh,[ecx+0x240]	//V0Y0
		asm	mov	es:[edi],eax		//Y0V0Y1U0
		//////////// Line 2 ////////////
		asm	mov	bh,[ecx+1]	//U1
		asm	mov	es:[edi+704],edx	//Y0V0Y1U0
		asm	mov	bl,[esi+0x480+3]
		asm	shl	ebx,16		//U1Y3
		asm	mov	bl,[esi+0x480+2]
		asm	add	esi,4
		asm	mov	bh,[ecx+0x241]	//V1Y2
		asm	add	ecx,2
		asm	mov	es:[edi+704+4],ebx	//Y2V1Y3U1
		asm	add	edi,8
		asm	dec	ebp
		asm	jnz	Move2LineData
	_ECX+=976;
	asm	pop	edx
	_ESI+=(800+0x480);
	_EDI+=704;
	asm	dec	edx
	asm	jnz	MoveYUY2Data
	asm	pop	ds
}
void	PASCAL	FAR	DrawUYVY(void)	//UYVY 4:2:2 byte ordering
{
	asm	xor	eax,eax
	asm	push	ds
//	_EDX=VCDHigh;
//	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
//	_ES=LinearSelSurface;
	asm	mov	ds,OffScrSel;
	asm 	mov 	esi,[eax+4]
	asm	mov 	ecx,[eax+8]
	asm	mov 	ds,[eax+0x10]	//DS-> Video data
	///////// Move YUYV Data //////////
	asm	shr	edx,1	//_EDX=_EBX/2;
	MoveYUY2Data:
		_EBP=176/2;
		asm	push	edx
		Move2LineData:
		asm	mov	al,[ecx+0x240]	//V0
		asm	mov	bl,[ecx+0x241]	//V1
		asm	mov	ah,[esi+1]
		asm	mov	bh,[esi+3]
		asm	shl	eax,16		//[Y1V0][0]
		asm	mov	dl,[ecx+0x240]	//V0
		asm	shl	ebx,16		//[Y3V1][0]
		asm	mov	dh,[esi+0x480+1]	//Y1
		asm	shl	edx,16		//[Y1V0][0]
		asm	mov	ah,[esi]
		asm	mov	bh,[esi+2]
		asm	mov	al,[ecx]	//[Y0U0]
		asm	mov	es:[edi],eax		//U0Y0V0Y1
		asm	mov	bl,[ecx+1]	//[Y2U1]
		asm	mov	es:[edi+4],ebx		//U1Y2V1Y3
		asm	mov	dh,[esi+0x480]
		asm	mov	dl,[ecx]		//[Y0U0]
		asm	mov	bl,[ecx+0x241]	//V1
		asm	mov	es:[edi+704],edx	//U0Y0V0Y1
		asm	mov	bh,[esi+0x480+3]	//Y3
		asm	shl	ebx,16		//[Y3V1][0]
		asm	mov	bh,[esi+0x480+2]
		asm	add	esi,4
		asm	mov	bl,[ecx+1]		//[Y2U1]
		asm	add	ecx,2
		asm	mov	es:[edi+704+4],ebx	//U1Y2V1Y3
		asm	add	edi,8
		asm	dec	ebp
		asm	jnz	Move2LineData
	_ECX+=976;
	asm	pop	edx
	_ESI+=(800+0x480);
	_EDI+=704;
	asm	dec	edx
	asm	jnz	MoveYUY2Data
	asm	pop	ds
}
