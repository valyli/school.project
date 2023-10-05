////////////////////////////////////////////////////////
//		YUV to RGB Fast decoder
//		and YUV display data trans
//		    Southern.Liang
//		       1996.6.29
////////////////////////////////////////////////////////
//#pragma	option	-zC_TEXT	//This Must in _TEXT segment because the library & Enter point in _TEXT
#pragma	inline
/////////////////////////// YUV->RGB //////////////////////////
extern	long	VCDHigh;
extern	short	OffScrSel;
extern	unsigned long	LinearOffSurface;
extern	unsigned long	LinearSelSurface;
static	void	Align0(void){}
////////////////////////// RGB16Bits 64K Colors ///////////////////
extern	int	CrCb,Cg;
void	FastYUV2RGB16BitsDouble1LineOnly(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm	mov	cx,gs:[ebp+0x240]	;//V1V2
	asm	mov	bx,gs:[ebp]		;//U1U2
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////
	asm	sub	ch,128		;//Cr=U-=128
	asm	mov     al,cl
	asm	mov	cl,bh
	asm	mov	bh,al
	////////Compute U/2+V/5 //////////
	asm	mov	dl,ch
	asm	sar	dl,1		;//Cr/2
	asm	sub	cl,128		;//Cb=V-=128
	asm	sub	bh,128		;//Cr=U-=128
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	Cg,dx  	//Store in high 16 bits
	asm	sub	bl,128		;//Cb=V-=128
	asm	mov	CrCb,cx
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL1
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL1
	Next1BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL1
	Next2BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL1
	asm	jmp	Next6BL1
	FixedR1BL1:
	asm	or	ch,ch
	asm	jnl	Next1BL1
	asm	xor	ah,ah
	asm	jmp	Next1BL1
	FixedG1BL1:
	asm	or	dl,dl
	asm	jl	Next2BL1
	asm	xor	al,al
	asm	jmp	Next2BL1
	FixedB1BL1:
	asm	or	cl,cl
	asm	jnl	Next3BL1
	asm	xor	dh,dh
	Next3BL1:
	asm 	jmp	Next6BL1
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL1
	Next4BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL1
	Next5BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL1
	asm	jmp	Next6BL1
	FixedR2BL1:
	asm	or	ch,ch
	asm	jl	Next4BL1
	asm	mov	ah,255
	asm	jmp	Next4BL1
	FixedG2BL1:
	asm	or	dl,dl
	asm	jnl	Next5BL1
	asm	mov	al,255
	asm	jmp	Next5BL1
	FixedB2BL1:
	asm	or	cl,cl
	asm	jl	Next6BL1
	asm	mov	dh,255
	Next6BL1:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH1
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH1
	Next1BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH1
	Next2BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH1
	asm	jmp	Next6BH1
	FixedR1BH1:
	asm	or	ch,ch
	asm	jnl	Next1BH1
	asm	xor	ah,ah
	asm	jmp	Next1BH1
	FixedG1BH1:
	asm	or	dl,dl
	asm	jl	Next2BH1
	asm	xor	al,al
	asm	jmp	Next2BH1
	FixedB1BH1:
	asm	or	cl,cl
	asm	jnl	Next3BH1
	asm	xor	bh,bh
	Next3BH1:
	asm	jmp	Next6BH1
	///////////////// Y > 128 ////////////////////
	Granthen128BH1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH1
	Next4BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH1
	Next5BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH1
	asm	jmp	Next6BH1
	FixedR2BH1:
	asm	or	ch,ch
	asm	jl	Next4BH1
	asm	mov	ah,255
	asm	jmp	Next4BH1
	FixedG2BH1:
	asm	or	dl,dl
	asm	jnl	Next5BH1
	asm	mov	al,255
	asm	jmp	Next5BH1
	FixedB2BH1:
	asm	or	cl,cl
	asm	jl	Next6BH1
	asm	mov	bh,255
	Next6BH1:
	//////////////////////////////////////////////////////
	asm	shr	ax,2		;//G[6]
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	dx,Cg
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL2
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL2
	Next1BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL2
	Next2BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL2
	asm	jmp	Next6BL2
	FixedR1BL2:
	asm	or	ch,ch
	asm	jnl	Next1BL2
	asm	xor	ah,ah
	asm	jmp	Next1BL2
	FixedG1BL2:
	asm	or	dl,dl
	asm	jl	Next2BL2
	asm	xor	al,al
	asm	jmp	Next2BL2
	FixedB1BL2:
	asm	or	cl,cl
	asm	jnl	Next3BL2
	asm	xor	dh,dh
	Next3BL2:
	asm 	jmp	Next6BL2
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL2:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL2
	Next4BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL2
	Next5BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL2
	asm	jmp	Next6BL2
	FixedR2BL2:
	asm	or	ch,ch
	asm	jl	Next4BL2
	asm	mov	ah,255
	asm	jmp	Next4BL2
	FixedG2BL2:
	asm	or	dl,dl
	asm	jnl	Next5BL2
	asm	mov	al,255
	asm	jmp	Next5BL2
	FixedB2BL2:
	asm	or	cl,cl
	asm	jl	Next6BL2
	asm	mov	dh,255
	Next6BL2:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+8],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+10],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH2
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH2
	Next1BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH2
	Next2BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH2
	asm	jmp	Next6BH2
	FixedR1BH2:
	asm	or	ch,ch
	asm	jnl	Next1BH2
	asm	xor	ah,ah
	asm	jmp	Next1BH2
	FixedG1BH2:
	asm	or	dl,dl
	asm	jl	Next2BH2
	asm	xor	al,al
	asm	jmp	Next2BH2
	FixedB1BH2:
	asm	or	cl,cl
	asm	jnl	Next3BH2
	asm	xor	bh,bh
	Next3BH2:
	asm	jmp	Next6BH2
	///////////////// Y > 128 ////////////////////
	Granthen128BH2:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH2
	Next4BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH2
	Next5BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH2
	asm	jmp	Next6BH2
	FixedR2BH2:
	asm	or	ch,ch
	asm	jl	Next4BH2
	asm	mov	ah,255
	asm	jmp	Next4BH2
	FixedG2BH2:
	asm	or	dl,dl
	asm	jnl	Next5BH2
	asm	mov	al,255
	asm	jmp	Next5BH2
	FixedB2BH2:
	asm	or	cl,cl
	asm	jl	Next6BH2
	asm	mov	bh,255
	Next6BH2:
	//////////////////////////////////////////////////////
	asm	shr	ax,2		;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+12],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+14],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	add	edi,16		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align18(void){}
void	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm	mov	cx,gs:[ebp+0x240]	;//V1V2
	asm	mov	bx,gs:[ebp]		;//U1U2
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////
	asm	sub	ch,128		;//Cr=U-=128
	asm	mov     al,cl
	asm	mov	cl,bh
	asm	mov	bh,al
	////////Compute U/2+V/5 //////////
	asm	mov	dl,ch
	asm	sar	dl,1		;//Cr/2
	asm	sub	cl,128		;//Cb=V-=128
	asm	sub	bh,128		;//Cr=U-=128
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	Cg,dx  	//Store in high 16 bits
	asm	sub	bl,128		;//Cb=V-=128
	asm	mov	CrCb,cx
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL1
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL1
	Next1BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL1
	Next2BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL1
	asm	jmp	Next6BL1
	FixedR1BL1:
	asm	or	ch,ch
	asm	jnl	Next1BL1
	asm	xor	ah,ah
	asm	jmp	Next1BL1
	FixedG1BL1:
	asm	or	dl,dl
	asm	jl	Next2BL1
	asm	xor	al,al
	asm	jmp	Next2BL1
	FixedB1BL1:
	asm	or	cl,cl
	asm	jnl	Next3BL1
	asm	xor	dh,dh
	Next3BL1:
	asm 	jmp	Next6BL1
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL1
	Next4BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL1
	Next5BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL1
	asm	jmp	Next6BL1
	FixedR2BL1:
	asm	or	ch,ch
	asm	jl	Next4BL1
	asm	mov	ah,255
	asm	jmp	Next4BL1
	FixedG2BL1:
	asm	or	dl,dl
	asm	jnl	Next5BL1
	asm	mov	al,255
	asm	jmp	Next5BL1
	FixedB2BL1:
	asm	or	cl,cl
	asm	jl	Next6BL1
	asm	mov	dh,255
	Next6BL1:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH1
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH1
	Next1BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH1
	Next2BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH1
	asm	jmp	Next6BH1
	FixedR1BH1:
	asm	or	ch,ch
	asm	jnl	Next1BH1
	asm	xor	ah,ah
	asm	jmp	Next1BH1
	FixedG1BH1:
	asm	or	dl,dl
	asm	jl	Next2BH1
	asm	xor	al,al
	asm	jmp	Next2BH1
	FixedB1BH1:
	asm	or	cl,cl
	asm	jnl	Next3BH1
	asm	xor	bh,bh
	Next3BH1:
	asm	jmp	Next6BH1
	///////////////// Y > 128 ////////////////////
	Granthen128BH1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH1
	Next4BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH1
	Next5BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH1
	asm	jmp	Next6BH1
	FixedR2BH1:
	asm	or	ch,ch
	asm	jl	Next4BH1
	asm	mov	ah,255
	asm	jmp	Next4BH1
	FixedG2BH1:
	asm	or	dl,dl
	asm	jnl	Next5BH1
	asm	mov	al,255
	asm	jmp	Next5BH1
	FixedB2BH1:
	asm	or	cl,cl
	asm	jl	Next6BH1
	asm	mov	bh,255
	Next6BH1:
	//////////////////////////////////////////////////////
	asm	shr	ax,2		;//G[6]
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	asm	or	bx,0x0101
	asm	add	bh,bl	//Two line mix with Alpha
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH2
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH2
	Next1BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH2
	Next2BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH2
	asm	jmp	Next6BH2
	FixedR1BH2:
	asm	or	ch,ch
	asm	jnl	Next1BH2
	asm	xor	ah,ah
	asm	jmp	Next1BH2
	FixedG1BH2:
	asm	or	dl,dl
	asm	jl	Next2BH2
	asm	xor	al,al
	asm	jmp	Next2BH2
	FixedB1BH2:
	asm	or	cl,cl
	asm	jnl	Next3BH2
	asm	xor	bh,bh
	Next3BH2:
	asm	jmp	Next6BH2
	///////////////// Y > 128 ////////////////////
	Granthen128BH2:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH2
	Next4BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH2
	Next5BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH2
	asm	jmp	Next6BH2
	FixedR2BH2:
	asm	or	ch,ch
	asm	jl	Next4BH2
	asm	mov	ah,255
	asm	jmp	Next4BH2
	FixedG2BH2:
	asm	or	dl,dl
	asm	jnl	Next5BH2
	asm	mov	al,255
	asm	jmp	Next5BH2
	FixedB2BH2:
	asm	or	cl,cl
	asm	jl	Next6BH2
	asm	mov	bh,255
	Next6BH2:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	asm	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	add	edi,12		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
static	void	Align19(void){}
void	FastYUV2RGB15BitsDouble1LineOnly(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm	mov	cx,gs:[ebp+0x240]	;//V1V2
	asm	mov	bx,gs:[ebp]		;//U1U2
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////
	asm	sub	ch,128		;//Cr=U-=128
	asm	mov     al,cl
	asm	mov	cl,bh
	asm	mov	bh,al
	////////Compute U/2+V/5 //////////
	asm	mov	dl,ch
	asm	sar	dl,1		;//Cr/2
	asm	sub	cl,128		;//Cb=V-=128
	asm	sub	bh,128		;//Cr=U-=128
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	Cg,dx  	//Store in high 16 bits
	asm	sub	bl,128		;//Cb=V-=128
	asm	mov	CrCb,cx
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL1
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL1
	Next1BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL1
	Next2BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL1
	asm	jmp	Next6BL1
	FixedR1BL1:
	asm	or	ch,ch
	asm	jnl	Next1BL1
	asm	xor	ah,ah
	asm	jmp	Next1BL1
	FixedG1BL1:
	asm	or	dl,dl
	asm	jl	Next2BL1
	asm	xor	al,al
	asm	jmp	Next2BL1
	FixedB1BL1:
	asm	or	cl,cl
	asm	jnl	Next3BL1
	asm	xor	dh,dh
	Next3BL1:
	asm 	jmp	Next6BL1
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL1
	Next4BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL1
	Next5BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL1
	asm	jmp	Next6BL1
	FixedR2BL1:
	asm	or	ch,ch
	asm	jl	Next4BL1
	asm	mov	ah,255
	asm	jmp	Next4BL1
	FixedG2BL1:
	asm	or	dl,dl
	asm	jnl	Next5BL1
	asm	mov	al,255
	asm	jmp	Next5BL1
	FixedB2BL1:
	asm	or	cl,cl
	asm	jl	Next6BL1
	asm	mov	dh,255
	Next6BL1:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH1
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH1
	Next1BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH1
	Next2BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH1
	asm	jmp	Next6BH1
	FixedR1BH1:
	asm	or	ch,ch
	asm	jnl	Next1BH1
	asm	xor	ah,ah
	asm	jmp	Next1BH1
	FixedG1BH1:
	asm	or	dl,dl
	asm	jl	Next2BH1
	asm	xor	al,al
	asm	jmp	Next2BH1
	FixedB1BH1:
	asm	or	cl,cl
	asm	jnl	Next3BH1
	asm	xor	bh,bh
	Next3BH1:
	asm	jmp	Next6BH1
	///////////////// Y > 128 ////////////////////
	Granthen128BH1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH1
	Next4BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH1
	Next5BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH1
	asm	jmp	Next6BH1
	FixedR2BH1:
	asm	or	ch,ch
	asm	jl	Next4BH1
	asm	mov	ah,255
	asm	jmp	Next4BH1
	FixedG2BH1:
	asm	or	dl,dl
	asm	jnl	Next5BH1
	asm	mov	al,255
	asm	jmp	Next5BH1
	FixedB2BH1:
	asm	or	cl,cl
	asm	jl	Next6BH1
	asm	mov	bh,255
	Next6BH1:
	//////////////////////////////////////////////////////
	asm	shr	ax,3		;//G[5]
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	asm	mov	dx,Cg
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL2
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL2
	Next1BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL2
	Next2BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL2
	asm	jmp	Next6BL2
	FixedR1BL2:
	asm	or	ch,ch
	asm	jnl	Next1BL2
	asm	xor	ah,ah
	asm	jmp	Next1BL2
	FixedG1BL2:
	asm	or	dl,dl
	asm	jl	Next2BL2
	asm	xor	al,al
	asm	jmp	Next2BL2
	FixedB1BL2:
	asm	or	cl,cl
	asm	jnl	Next3BL2
	asm	xor	dh,dh
	Next3BL2:
	asm 	jmp	Next6BL2
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL2:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL2
	Next4BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL2
	Next5BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL2
	asm	jmp	Next6BL2
	FixedR2BL2:
	asm	or	ch,ch
	asm	jl	Next4BL2
	asm	mov	ah,255
	asm	jmp	Next4BL2
	FixedG2BL2:
	asm	or	dl,dl
	asm	jnl	Next5BL2
	asm	mov	al,255
	asm	jmp	Next5BL2
	FixedB2BL2:
	asm	or	cl,cl
	asm	jl	Next6BL2
	asm	mov	dh,255
	Next6BL2:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+8],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+10],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH2
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH2
	Next1BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH2
	Next2BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH2
	asm	jmp	Next6BH2
	FixedR1BH2:
	asm	or	ch,ch
	asm	jnl	Next1BH2
	asm	xor	ah,ah
	asm	jmp	Next1BH2
	FixedG1BH2:
	asm	or	dl,dl
	asm	jl	Next2BH2
	asm	xor	al,al
	asm	jmp	Next2BH2
	FixedB1BH2:
	asm	or	cl,cl
	asm	jnl	Next3BH2
	asm	xor	bh,bh
	Next3BH2:
	asm	jmp	Next6BH2
	///////////////// Y > 128 ////////////////////
	Granthen128BH2:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH2
	Next4BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH2
	Next5BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH2
	asm	jmp	Next6BH2
	FixedR2BH2:
	asm	or	ch,ch
	asm	jl	Next4BH2
	asm	mov	ah,255
	asm	jmp	Next4BH2
	FixedG2BH2:
	asm	or	dl,dl
	asm	jnl	Next5BH2
	asm	mov	al,255
	asm	jmp	Next5BH2
	FixedB2BH2:
	asm	or	cl,cl
	asm	jl	Next6BH2
	asm	mov	bh,255
	Next6BH2:
	//////////////////////////////////////////////////////
	asm	shr	ax,3		;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+12],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+14],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	add	edi,16		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align20(void){}
void	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm	mov	cx,gs:[ebp+0x240]	;//V1V2
	asm	mov	bx,gs:[ebp]		;//U1U2
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////
	asm	sub	ch,128		;//Cr=U-=128
	asm	mov     al,cl
	asm	mov	cl,bh
	asm	mov	bh,al
	////////Compute U/2+V/5 //////////
	asm	mov	dl,ch
	asm	sar	dl,1		;//Cr/2
	asm	sub	cl,128		;//Cb=V-=128
	asm	sub	bh,128		;//Cr=U-=128
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	Cg,dx  	//Store in high 16 bits
	asm	sub	bl,128		;//Cb=V-=128
	asm	mov	CrCb,cx
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL1
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL1
	Next1BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL1
	Next2BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL1
	asm	jmp	Next6BL1
	FixedR1BL1:
	asm	or	ch,ch
	asm	jnl	Next1BL1
	asm	xor	ah,ah
	asm	jmp	Next1BL1
	FixedG1BL1:
	asm	or	dl,dl
	asm	jl	Next2BL1
	asm	xor	al,al
	asm	jmp	Next2BL1
	FixedB1BL1:
	asm	or	cl,cl
	asm	jnl	Next3BL1
	asm	xor	dh,dh
	Next3BL1:
	asm 	jmp	Next6BL1
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL1
	Next4BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL1
	Next5BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL1
	asm	jmp	Next6BL1
	FixedR2BL1:
	asm	or	ch,ch
	asm	jl	Next4BL1
	asm	mov	ah,255
	asm	jmp	Next4BL1
	FixedG2BL1:
	asm	or	dl,dl
	asm	jnl	Next5BL1
	asm	mov	al,255
	asm	jmp	Next5BL1
	FixedB2BL1:
	asm	or	cl,cl
	asm	jl	Next6BL1
	asm	mov	dh,255
	Next6BL1:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH1
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH1
	Next1BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH1
	Next2BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH1
	asm	jmp	Next6BH1
	FixedR1BH1:
	asm	or	ch,ch
	asm	jnl	Next1BH1
	asm	xor	ah,ah
	asm	jmp	Next1BH1
	FixedG1BH1:
	asm	or	dl,dl
	asm	jl	Next2BH1
	asm	xor	al,al
	asm	jmp	Next2BH1
	FixedB1BH1:
	asm	or	cl,cl
	asm	jnl	Next3BH1
	asm	xor	bh,bh
	Next3BH1:
	asm	jmp	Next6BH1
	///////////////// Y > 128 ////////////////////
	Granthen128BH1:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH1
	Next4BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH1
	Next5BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH1
	asm	jmp	Next6BH1
	FixedR2BH1:
	asm	or	ch,ch
	asm	jl	Next4BH1
	asm	mov	ah,255
	asm	jmp	Next4BH1
	FixedG2BH1:
	asm	or	dl,dl
	asm	jnl	Next5BH1
	asm	mov	al,255
	asm	jmp	Next5BH1
	FixedB2BH1:
	asm	or	cl,cl
	asm	jl	Next6BH1
	asm	mov	bh,255
	Next6BH1:
	//////////////////////////////////////////////////////
	asm	shr	ax,3		;//G[5]
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	asm	or	bx,0x0101
	asm	add	bh,bl		//Two line mix with Alpha
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH2
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH2
	Next1BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH2
	Next2BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH2
	asm	jmp	Next6BH2
	FixedR1BH2:
	asm	or	ch,ch
	asm	jnl	Next1BH2
	asm	xor	ah,ah
	asm	jmp	Next1BH2
	FixedG1BH2:
	asm	or	dl,dl
	asm	jl	Next2BH2
	asm	xor	al,al
	asm	jmp	Next2BH2
	FixedB1BH2:
	asm	or	cl,cl
	asm	jnl	Next3BH2
	asm	xor	bh,bh
	Next3BH2:
	asm	jmp	Next6BH2
	///////////////// Y > 128 ////////////////////
	Granthen128BH2:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH2
	Next4BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH2
	Next5BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH2
	asm	jmp	Next6BH2
	FixedR2BH2:
	asm	or	ch,ch
	asm	jl	Next4BH2
	asm	mov	ah,255
	asm	jmp	Next4BH2
	FixedG2BH2:
	asm	or	dl,dl
	asm	jnl	Next5BH2
	asm	mov	al,255
	asm	jmp	Next5BH2
	FixedB2BH2:
	asm	or	cl,cl
	asm	jl	Next6BH2
	asm	mov	bh,255
	Next6BH2:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	asm	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	add	edi,12		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
