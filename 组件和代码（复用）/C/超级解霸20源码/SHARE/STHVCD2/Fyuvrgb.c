////////////////////////////////////////////////////////
//		YUV to RGB Fast decoder
//		and YUV display data trans
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
//#pragma	option	-zC_TEXT	//This Must in _TEXT segment because the library & Enter point in _TEXT
#pragma	inline
static	void	Align0(void){}
////////////////////////// RGB16Bits 64K Colors ///////////////////
int	CrCb,Cg;
void	FastYUV2RGB16Bits(void)
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
	////////////Use DX to compute U1V1////////////////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi+640],ax	;//Write AX=RGB16[5:6:5]
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
	asm	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	///////// R G B //////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL3
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL3
	Next1BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL3
	Next2BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL3
	asm	jmp	Next6BL3
	FixedR1BL3:
	asm	or	ch,ch
	asm	jnl	Next1BL3
	asm	xor	ah,ah
	asm	jmp	Next1BL3
	FixedG1BL3:
	asm	or	dl,dl
	asm	jl	Next2BL3
	asm	xor	al,al
	asm	jmp	Next2BL3
	FixedB1BL3:
	asm	or	cl,cl
	asm	jnl	Next3BL3
	asm	xor	dh,dh
	Next3BL3:
	asm 	jmp	Next6BL3
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL3
	Next4BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL3
	Next5BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL3
	asm	jmp	Next6BL3
	FixedR2BL3:
	asm	or	ch,ch
	asm	jl	Next4BL3
	asm	mov	ah,255
	asm	jmp	Next4BL3
	FixedG2BL3:
	asm	or	dl,dl
	asm	jnl	Next5BL3
	asm	mov	al,255
	asm	jmp	Next5BL3
	FixedB2BL3:
	asm	or	cl,cl
	asm	jl	Next6BL3
	asm	mov	dh,255
	Next6BL3:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	asm	shr	ax,2		;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL4
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL4
	Next1BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL4
	Next2BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL4
	asm	jmp	Next6BL4
	FixedR1BL4:
	asm	or	ch,ch
	asm	jnl	Next1BL4
	asm	xor	ah,ah
	asm	jmp	Next1BL4
	FixedG1BL4:
	asm	or	dl,dl
	asm	jl	Next2BL4
	asm	xor	al,al
	asm	jmp	Next2BL4
	FixedB1BL4:
	asm	or	cl,cl
	asm	jnl	Next3BL4
	asm	xor	dh,dh
	Next3BL4:
	asm 	jmp	Next6BL4
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL4
	Next4BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL4
	Next5BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL4
	asm	jmp	Next6BL4
	FixedR2BL4:
	asm	or	ch,ch
	asm	jl	Next4BL4
	asm	mov	ah,255
	asm	jmp	Next4BL4
	FixedG2BL4:
	asm	or	dl,dl
	asm	jnl	Next5BL4
	asm	mov	al,255
	asm	jmp	Next5BL4
	FixedB2BL4:
	asm	or	cl,cl
	asm	jl	Next6BL4
	asm	mov	dh,255
	Next6BL4:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,2		;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+640+4+2],ax	;//Write AX=RGB16[5:6:5]
	asm	add	edi,8		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align1(void){}
void	FastYUV2RGB16BitsDeletePixel(void)
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
	//////////////////////////////////////////////////////
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi+640],ax	;//Write AX=RGB16[5:6:5]
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
	asm	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:6:5]
	asm	add	edi,6		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
static	void	Align2(void)
{
	asm	nop
	asm	nop
}
//////////// One line only ///////////
void	FastYUV2RGB16Bits1Line(void)
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
	//////////////////////////////////////////////////////
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	asm	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	ax,gs:[esi+0x480+2]	//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	mov	dx,Cg
	asm	add	bx,ax
	asm	rcr	bx,1
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
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
	asm	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	add	edi,8		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align3(void){}
void	FastYUV2RGB16Bits1LineDeletePixel(void)
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
	//////////////////////////////////////////////////////
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	asm	mov	ax,gs:[esi+0x480]	//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax
	asm	rcr	bx,1
	///////// R G B //////
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	mov	dx,Cg
	asm	add	bx,ax		//4 Pixel mix with Alpha
	asm	rcr	bx,1
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
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
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	add	edi,6		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
///////////////////////////////////////////////////////////////////
//static	void	Align4(void){}
///////////////////////// 640x240 Double pixel ////////////////
extern	unsigned long	lStride;	//Video Memory Line width.
void	FastYUV2RGB16BitsDouble(void)
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
	////////////Use DX to compute U1V1////////////////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
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
	asm	add	edi,dword ptr lStride
	asm	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
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
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	dx,Cg
	asm	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL3
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL3
	Next1BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL3
	Next2BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL3
	asm	jmp	Next6BL3
	FixedR1BL3:
	asm	or	ch,ch
	asm	jnl	Next1BL3
	asm	xor	ah,ah
	asm	jmp	Next1BL3
	FixedG1BL3:
	asm	or	dl,dl
	asm	jl	Next2BL3
	asm	xor	al,al
	asm	jmp	Next2BL3
	FixedB1BL3:
	asm	or	cl,cl
	asm	jnl	Next3BL3
	asm	xor	dh,dh
	Next3BL3:
	asm 	jmp	Next6BL3
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL3
	Next4BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL3
	Next5BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL3
	asm	jmp	Next6BL3
	FixedR2BL3:
	asm	or	ch,ch
	asm	jl	Next4BL3
	asm	mov	ah,255
	asm	jmp	Next4BL3
	FixedG2BL3:
	asm	or	dl,dl
	asm	jnl	Next5BL3
	asm	mov	al,255
	asm	jmp	Next5BL3
	FixedB2BL3:
	asm	or	cl,cl
	asm	jl	Next6BL3
	asm	mov	dh,255
	Next6BL3:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+0x08],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	//////////////////////////////////////////////////////
	asm	shr	ax,2		;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+0x0C],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+0x0E],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL4
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL4
	Next1BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL4
	Next2BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL4
	asm	jmp	Next6BL4
	FixedR1BL4:
	asm	or	ch,ch
	asm	jnl	Next1BL4
	asm	xor	ah,ah
	asm	jmp	Next1BL4
	FixedG1BL4:
	asm	or	dl,dl
	asm	jl	Next2BL4
	asm	xor	al,al
	asm	jmp	Next2BL4
	FixedB1BL4:
	asm	or	cl,cl
	asm	jnl	Next3BL4
	asm	xor	dh,dh
	Next3BL4:
	asm 	jmp	Next6BL4
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL4
	Next4BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL4
	Next5BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL4
	asm	jmp	Next6BL4
	FixedR2BL4:
	asm	or	ch,ch
	asm	jl	Next4BL4
	asm	mov	ah,255
	asm	jmp	Next4BL4
	FixedG2BL4:
	asm	or	dl,dl
	asm	jnl	Next5BL4
	asm	mov	al,255
	asm	jmp	Next5BL4
	FixedB2BL4:
	asm	or	cl,cl
	asm	jl	Next6BL4
	asm	mov	dh,255
	Next6BL4:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,dx,5		;//B[5]
	asm	add	edi,dword ptr lStride
	asm	mov	es:[edi+1280+0x08],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,2		;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+1280+0x0C],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+0x0E],ax	;//Write AX=RGB16[5:6:5]
	asm	sub	edi,dword ptr lStride
	asm	add	edi,16		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align5(void){}
void	FastYUV2RGB16BitsDoubleDeletePixel(void)
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
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	jns	FixedR2BL1
	Next4BL1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	jns	FixedG2BL1
	Next5BL1:
	asm	add	dh,cl		;//DH=B=Y+Cb		//////
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
	///////// R G B //////				//////
	asm	mov	ah,bh					//////
	asm	mov	al,bh					//////
	asm	or	bh,bh
	asm	js	Granthen128BH1
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	js	FixedR1BH1
	Next1BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	js	FixedG1BH1
	Next2BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb		//////
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
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	jns	FixedR2BH1
	Next4BH1:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	jns	FixedG2BH1
	Next5BH1:
	asm	add	bh,cl		;//DH=B=Y+Cb		//////
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl					//////
	asm	mov	dh,bl					//////
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL2
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	js	FixedR1BL2
	Next1BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	js	FixedG1BL2
	Next2BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb		//////
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
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	jns	FixedR2BL2
	Next4BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	jns	FixedG2BL2
	Next5BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb		//////
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
	asm	add	edi,dword ptr lStride
	asm	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	asm	mov	ah,bh					//////
	asm	mov	al,bh					//////
	asm	or	bh,bh
	asm	js	Granthen128BH2
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	js	FixedR1BH2
	Next1BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	js	FixedG1BH2
	Next2BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb		//////
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
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	jns	FixedR2BH2
	Next4BH2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	jns	FixedG2BH2
	Next5BH2:
	asm	add	bh,cl		;//DH=B=Y+Cb		//////
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
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	dx,Cg
	asm	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	asm	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,2            ;//G[6]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	ebx,dword ptr lStride
	asm	mov	es:[edi+ebx+1280+8],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+ebx+1280+10],ax	;//Write AX=RGB16[5:6:5]
	asm	add	edi,12		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
static	void	Align6(void)
{
	asm	nop
	asm	nop
}
//////////// One line only ///////////
void	FastYUV2RGB16BitsDouble1Line(void)
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
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	asm	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax	//Two line mix with Alpha
	asm	rcr	bx,1
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
	asm	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101	//Two line mix with Alpha
	asm	add	bx,ax
	asm	rcr	bx,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bl					//////
	asm	mov	dh,bl					//////
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL2
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	js	FixedR1BL2
	Next1BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	js	FixedG1BL2
	Next2BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb		//////
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
	asm	add	ah,ch		;//AH=R=Y+Cr		//////
	asm	jns	FixedR2BL2
	Next4BL2:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	jns	FixedG2BL2
	Next5BL2:
	asm	add	dh,cl		;//DH=B=Y+Cb		//////
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
//static	void	Align7(void){}
void	FastYUV2RGB16BitsDouble1LineDeletePixel(void)
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
	asm	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
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
	///////// R G B //////				//////
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
	asm	mov	dx,Cg
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
	asm	add	bh,bl
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
static	void	Align8(void)
{
}
///////////////////////////////////////////////////////////////////
//////////////////////// RGB15Bits 32K Colors /////////////////////
///////////////////////////////////////////////////////////////////
void	FastYUV2RGB15Bits(void)
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
	////////Compute U/2+V/5 //////////		//////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:5:5]
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi+640],ax	;//Write AX=RGB16[5:5:5]
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
	asm	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:5:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	///////// R G B //////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL3
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL3
	Next1BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL3
	Next2BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL3
	asm	jmp	Next6BL3
	FixedR1BL3:
	asm	or	ch,ch
	asm	jnl	Next1BL3
	asm	xor	ah,ah
	asm	jmp	Next1BL3
	FixedG1BL3:
	asm	or	dl,dl
	asm	jl	Next2BL3
	asm	xor	al,al
	asm	jmp	Next2BL3
	FixedB1BL3:
	asm	or	cl,cl
	asm	jnl	Next3BL3
	asm	xor	dh,dh
	Next3BL3:
	asm 	jmp	Next6BL3
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL3
	Next4BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL3
	Next5BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL3
	asm	jmp	Next6BL3
	FixedR2BL3:
	asm	or	ch,ch
	asm	jl	Next4BL3
	asm	mov	ah,255
	asm	jmp	Next4BL3
	FixedG2BL3:
	asm	or	dl,dl
	asm	jnl	Next5BL3
	asm	mov	al,255
	asm	jmp	Next5BL3
	FixedB2BL3:
	asm	or	cl,cl
	asm	jl	Next6BL3
	asm	mov	dh,255
	Next6BL3:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:5:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	asm	shr	ax,3		;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL4
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL4
	Next1BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL4
	Next2BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL4
	asm	jmp	Next6BL4
	FixedR1BL4:
	asm	or	ch,ch
	asm	jnl	Next1BL4
	asm	xor	ah,ah
	asm	jmp	Next1BL4
	FixedG1BL4:
	asm	or	dl,dl
	asm	jl	Next2BL4
	asm	xor	al,al
	asm	jmp	Next2BL4
	FixedB1BL4:
	asm	or	cl,cl
	asm	jnl	Next3BL4
	asm	xor	dh,dh
	Next3BL4:
	asm 	jmp	Next6BL4
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL4
	Next4BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL4
	Next5BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL4
	asm	jmp	Next6BL4
	FixedR2BL4:
	asm	or	ch,ch
	asm	jl	Next4BL4
	asm	mov	ah,255
	asm	jmp	Next4BL4
	FixedG2BL4:
	asm	or	dl,dl
	asm	jnl	Next5BL4
	asm	mov	al,255
	asm	jmp	Next5BL4
	FixedB2BL4:
	asm	or	cl,cl
	asm	jl	Next6BL4
	asm	mov	dh,255
	Next6BL4:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:5:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,3		;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+640+4+2],ax	;//Write AX=RGB16[5:5:5]
	asm	add	edi,8		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align9(void){}
void	FastYUV2RGB15BitsDeletePixel(void)
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
	//////////////////////////////////////////////////////
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:5:5]
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi+640],ax	;//Write AX=RGB16[5:5:5]
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
	asm	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:5:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:5:5]
	asm	add	edi,6		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
static	void	Align10(void)
{
	asm	nop
	asm	nop
}
//////////// One line only ///////////
void	FastYUV2RGB15Bits1Line(void)
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
	//////////////////////////////////////////////////////
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	asm	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101	//Two line mix with Alpha
	asm	add	bx,ax
	asm	rcr	bx,1
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:5:5]
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:5:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	asm	mov	ax,gs:[esi+0x480+2]	//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax
	asm	rcr	bx,1
	//////////////////////////////////////////////////////
	///////// R G B //////
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
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:5:5]
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
	asm	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
	asm	add	edi,8		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align11(void){}
void	FastYUV2RGB15Bits1LineDeletePixel(void)
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
	//////////////////////////////////////////////////////
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////
	////////Compute U/2+V/5 //////////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	asm	mov	ax,gs:[esi+0x480]	//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax
	asm	rcr	bx,1
	///////// R G B //////
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
	asm	mov	es:[edi],ax	;//Write AX=RGB16[5:5:5]
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+2],ax	;//Write AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	cx,CrCb
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	dx,Cg
	asm	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax	//4 Pixel mix with Alpha
	asm	rcr	bx,1
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
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
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:5:5]
	//////////////////////////////////////////////////////
	asm	add	edi,6		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align12(void){}
///////////////////////////////////////////////////////////////////
///////////////////////// 640x240 Double pixel ////////////////
extern	unsigned long	lStride;	//Video Memory Line width.
void	FastYUV2RGB15BitsDouble(void)
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
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
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	add	edi,dword ptr lStride
	asm	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
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
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	dx,Cg
	asm	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	ah,bl					//////
	asm	mov	dh,bl					//////
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL3
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL3
	Next1BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL3
	Next2BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL3
	asm	jmp	Next6BL3
	FixedR1BL3:
	asm	or	ch,ch
	asm	jnl	Next1BL3
	asm	xor	ah,ah
	asm	jmp	Next1BL3
	FixedG1BL3:
	asm	or	dl,dl
	asm	jl	Next2BL3
	asm	xor	al,al
	asm	jmp	Next2BL3
	FixedB1BL3:
	asm	or	cl,cl
	asm	jnl	Next3BL3
	asm	xor	dh,dh
	Next3BL3:
	asm 	jmp	Next6BL3
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL3
	Next4BL3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL3
	Next5BL3:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL3
	asm	jmp	Next6BL3
	FixedR2BL3:
	asm	or	ch,ch
	asm	jl	Next4BL3
	asm	mov	ah,255
	asm	jmp	Next4BL3
	FixedG2BL3:
	asm	or	dl,dl
	asm	jnl	Next5BL3
	asm	mov	al,255
	asm	jmp	Next5BL3
	FixedB2BL3:
	asm	or	cl,cl
	asm	jl	Next6BL3
	asm	mov	dh,255
	Next6BL3:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	mov	es:[edi+0x08],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	//////////////////////////////////////////////////////
	asm	shr	ax,3		;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+0x0C],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+0x0E],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	asm	mov	ah,bl
	asm	mov	dh,bl
	asm	mov	al,bl
	asm	or	bl,bl
	asm	js	Granthen128BL4
	/////////////////////// Y < 128 /////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BL4
	Next1BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BL4
	Next2BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BL4
	asm	jmp	Next6BL4
	FixedR1BL4:
	asm	or	ch,ch
	asm	jnl	Next1BL4
	asm	xor	ah,ah
	asm	jmp	Next1BL4
	FixedG1BL4:
	asm	or	dl,dl
	asm	jl	Next2BL4
	asm	xor	al,al
	asm	jmp	Next2BL4
	FixedB1BL4:
	asm	or	cl,cl
	asm	jnl	Next3BL4
	asm	xor	dh,dh
	Next3BL4:
	asm 	jmp	Next6BL4
	///////////////////////// Y > 128 //////////////////////
	Granthen128BL4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BL4
	Next4BL4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BL4
	Next5BL4:
	asm	add	dh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BL4
	asm	jmp	Next6BL4
	FixedR2BL4:
	asm	or	ch,ch
	asm	jl	Next4BL4
	asm	mov	ah,255
	asm	jmp	Next4BL4
	FixedG2BL4:
	asm	or	dl,dl
	asm	jnl	Next5BL4
	asm	mov	al,255
	asm	jmp	Next5BL4
	FixedB2BL4:
	asm	or	cl,cl
	asm	jl	Next6BL4
	asm	mov	dh,255
	Next6BL4:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	add	edi,dword ptr lStride
	asm	mov	es:[edi+1280+0x08],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,3		;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+1280+0x0C],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+0x0E],ax	;//Write AX=RGB16[5:6:5]
	asm	sub	edi,dword ptr lStride
	asm	add	edi,16		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
//static	void	Align13(void){}
void	FastYUV2RGB15BitsDoubleDeletePixel(void)
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
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
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
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,dx,5		;//B[5]
	asm	add	edi,dword ptr lStride
	asm	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
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
	asm	mov	cx,CrCb
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	asm	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	or	bx,0x0101
	asm	mov	dx,Cg
	asm	add	bh,bl
	asm	rcr	bh,1
	asm	mov	ah,bh
	asm	mov	al,bh
	asm	or	bh,bh
	asm	js	Granthen128BH3
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH3
	Next1BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg		//////
	asm	js	FixedG1BH3
	Next2BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb		//////
	asm	js	FixedB1BH3
	asm	jmp	Next6BH3
	FixedR1BH3:
	asm	or	ch,ch
	asm	jnl	Next1BH3
	asm	xor	ah,ah
	asm	jmp	Next1BH3
	FixedG1BH3:
	asm	or	dl,dl
	asm	jl	Next2BH3
	asm	xor	al,al
	asm	jmp	Next2BH3
	FixedB1BH3:
	asm	or	cl,cl
	asm	jnl	Next3BH3
	asm	xor	bh,bh
	Next3BH3:
	asm	jmp	Next6BH3
	///////////////// Y > 128 ////////////////////
	Granthen128BH3:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH3
	Next4BH3:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH3
	Next5BH3:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH3
	asm	jmp	Next6BH3
	FixedR2BH3:
	asm	or	ch,ch
	asm	jl	Next4BH3
	asm	mov	ah,255
	asm	jmp	Next4BH3
	FixedG2BH3:
	asm	or	dl,dl
	asm	jnl	Next5BH3
	asm	mov	al,255
	asm	jmp	Next5BH3
	FixedB2BH3:
	asm	or	cl,cl
	asm	jl	Next6BH3
	asm	mov	bh,255
	Next6BH3:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	asm	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	add	bh,bl
	asm	rcr	bh,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bh
	asm	mov	al,bh					//////
	asm	or	bh,bh
	asm	js	Granthen128BH4
	///////////////////// Y < 128 ////////////////////
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	js	FixedR1BH4
	Next1BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	js	FixedG1BH4
	Next2BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	js	FixedB1BH4
	asm	jmp	Next6BH4
	FixedR1BH4:
	asm	or	ch,ch
	asm	jnl	Next1BH4
	asm	xor	ah,ah
	asm	jmp	Next1BH4
	FixedG1BH4:
	asm	or	dl,dl
	asm	jl	Next2BH4
	asm	xor	al,al
	asm	jmp	Next2BH4
	FixedB1BH4:
	asm	or	cl,cl
	asm	jnl	Next3BH4
	asm	xor	bh,bh
	Next3BH4:
	asm	jmp	Next6BH4
	///////////////// Y > 128 ////////////////////
	Granthen128BH4:
	asm	add	ah,ch		;//AH=R=Y+Cr
	asm	jns	FixedR2BH4
	Next4BH4:
	asm	shr	ah,3		;//R[5]
	asm	sub	al,DL           ;//AL=G=Y-Cg
	asm	jns	FixedG2BH4
	Next5BH4:
	asm	add	bh,cl		;//DH=B=Y+Cb
	asm	jns	FixedB2BH4
	asm	jmp	Next6BH4
	FixedR2BH4:
	asm	or	ch,ch
	asm	jl	Next4BH4
	asm	mov	ah,255
	asm	jmp	Next4BH4
	FixedG2BH4:
	asm	or	dl,dl
	asm	jnl	Next5BH4
	asm	mov	al,255
	asm	jmp	Next5BH4
	FixedB2BH4:
	asm	or	cl,cl
	asm	jl	Next6BH4
	asm	mov	bh,255
	Next6BH4:
	//////////////////////////////////////////////////////
	asm	shr	ax,3            ;//G[5]
	asm	shld	ax,bx,5		;//B[5]
	asm	mov	ebx,dword ptr lStride
	asm	mov	es:[edi+ebx+1280+8],ax	;//Write AX=RGB16[5:6:5]
	asm	mov	es:[edi+ebx+1280+10],ax	;//Write AX=RGB16[5:6:5]
	asm	add	edi,12		;//Y source 4 byte
	asm	add	esi,4		;//Y source 4 byte
	asm	add	ebp,2		;//UV source 2 byts
	//	EDI had add when write pixel
}
static	void	Align14(void)
{
	asm	nop
	asm	nop
}
//////////// One line only ///////////
void	FastYUV2RGB15BitsDouble1Line(void)
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
	////////Compute U/2+V/5 //////////		//////
	asm	mov	dl,bh
	asm	mov	cl,bl
	asm	sar	dl,1		;//Cr/2
	asm	mov	ch,bh
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	asm	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
	//////////////////////////////////
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
	asm	mov	al,bh					//////
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
	asm	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	mov	dx,Cg
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
	//////////////////////////////////////////////////////
	asm	mov	ah,bl					//////
	asm	mov	dh,bl					//////
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
//static	void	Align15(void){}
void	FastYUV2RGB15BitsDouble1LineDeletePixel(void)
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
	asm	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
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
	asm	mov	dx,Cg
	//////////////////////////////////////////////////////
	asm	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	asm	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	asm	or	bx,0x0101
	asm	or	ax,0x0101
	asm	add	bx,ax		//Two line mix with Alpha
	asm	rcr	bx,1
	asm	add	bh,bl
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
