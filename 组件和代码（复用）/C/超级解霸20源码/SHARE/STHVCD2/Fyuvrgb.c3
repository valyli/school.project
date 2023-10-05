#pragma	inline
//////////////////////////////////////////////////////////
//	_EBX=0;		//No Delete pixel		//
//	FastYUV2RGB16Bits();	//Draw 3 pixel as movsd	//
//	_EBX=0x80000;	//May Delete first pixel	//
//	FastYUV2RGB16Bits();	//Draw 3 pixel as movsd	//
//	_EBX=0x10000;	//May Delete 4th pixel		//
//	FastYUV2RGB16Bits();	//Draw 3 pixel as movsd	//
//	_EBX=0x80000000	//Delete line (only one line)	//
//	FastYUV2RGB16Bits();	//Draw 3 pixel as movsd	//
//	_EBX=0x80020000	//Delete line (only one line)	//
//	FastYUV2RGB16Bits();	//Draw 3 pixel as movsd	//
//////////////////////////////////////////////////////////
////////////////////////// RGB16Bits 64K Colors ///////////////////
int	CrCb,Cg;
void	FastYUV2RGB16Bits(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+640],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+4+2],ax	;//Write AX=RGB16[5:6:5]
	add	edi,8		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB16BitsDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+640],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	shr	bl,1
	shr	bh,1
	add	bh,bl
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	shr	bl,1
	shr	bh,1
	add	bh,bl
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:6:5]
	add	edi,6		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
//////////// One line only ///////////
void	FastYUV2RGB16Bits1Line(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	shr	bl,1
	shr	bh,1
	shr	al,1
	shr	ah,1
	add	bl,al
	add	bh,ah
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	shr	bl,1
	shr	bh,1
	shr	al,1
	shr	ah,1
	add	bl,al
	add	bh,ah
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,8		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB16Bits1LineDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	mov	ax,gs:[esi+0x480]//Line 2 Y1 Y2
	shr	bl,1
	shr	bh,1
	shr	al,1
	shr	ah,1
	add	bl,al
	add	bh,ah
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	shr	bl,1
	shr	bh,1
	add	bh,bl
	mov	ax,gs:[esi+0x480+2]//Line 2 Y1 Y2
	shr	al,1
	shr	ah,1
	add	ah,al
	shr	bh,1
	shr	ah,1
	add	bh,ah
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,6		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
///////////////////////// 640x240 Double pixel ////////////////
extern	unsigned long	lStride;	//Video Memory Line width.
void	FastYUV2RGB16BitsDouble(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	add	edi,dword ptr lStride
	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+0x08],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+0x0C],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+0x0E],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	add	edi,dword ptr lStride
	mov	es:[edi+1280+0x08],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+1280+0x0C],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+0x0E],ax	;//Write AX=RGB16[5:6:5]
	sub	edi,dword ptr lStride
	add	edi,16		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB16BitsDoubleDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	add	edi,dword ptr lStride
	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	ebx,dword ptr lStride
	mov	es:[edi+ebx+1280+8],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+ebx+1280+10],ax	;//Write AX=RGB16[5:6:5]
	add	edi,12		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
//////////// One line only ///////////
void	FastYUV2RGB16BitsDouble1Line(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+8],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+10],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+12],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+14],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,16		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB16BitsDouble1LineDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2		;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,2            ;//G[6]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,12		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
///////////////////////////////////////////////////////////////////
//////////////////////// RGB15Bits 32K Colors /////////////////////
///////////////////////////////////////////////////////////////////
void	FastYUV2RGB15Bits(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+640],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+4+2],ax	;//Write AX=RGB16[5:6:5]
	add	edi,8		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB15BitsDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+640],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+640+4],ax	;//Write AX=RGB16[5:6:5]
	add	edi,6		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
//////////// One line only ///////////
void	FastYUV2RGB15Bits1Line(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,8		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB15Bits1LineDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,6		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB15BitsDouble(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	add	edi,dword ptr lStride
	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+0x08],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+0x0C],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+0x0E],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	add	edi,dword ptr lStride
	mov	es:[edi+1280+0x08],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+0x0A],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+1280+0x0C],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+0x0E],ax	;//Write AX=RGB16[5:6:5]
	sub	edi,dword ptr lStride
	add	edi,16		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB15BitsDoubleDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+0x480]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	add	edi,dword ptr lStride
	mov	es:[edi+1280],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+1280+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+1280+6],ax	;//Write AX=RGB16[5:6:5]
	sub	edi,dword ptr lStride
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+0x480+2]//Line 2 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	ebx,dword ptr lStride
	mov	es:[edi+ebx+1280+8],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+ebx+1280+10],ax	;//Write AX=RGB16[5:6:5]
	add	edi,12		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
//////////// One line only ///////////
void	FastYUV2RGB15BitsDouble1Line(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	/////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi+8],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+10],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+12],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+14],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,16		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
void	FastYUV2RGB15BitsDouble1LineDeletePixel(void)
{	//EAX,EBX,ECX,EDX,EDI,ESI,EBP changed
	//GS->Video data selector
	//ES->Video Buffer
	//Must compile with Fastest code optimization,the EBP will not save
	asm{
	mov	bx,gs:[ebp]		;//U1U2
	mov	cx,gs:[ebp+0x240]	;//V1V2
	xchg	cl,bh
	//CH=U2 CL=V2  BH=U1 BL=V1(Store in BX)
	////////////Use DX to compute U2V2////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	mov	Cg,dx  	//Store in high 16 bits
	mov	CrCb,cx
	//////////////////////////////////////////////////////
	mov 	cx,bx
	////////////Use DX to compute U1V1////////////////////
	////Compute U & V /////////			//////
	sub	cl,128		;//Cb=V-=128		//////
	sub	ch,128		;//Cr=U-=128		//////
	////////Compute U/2+V/5 //////////		//////
	mov	dl,ch					//////
	sar	dl,1		;//Cr/2			//////
	////////////// CH=Cr DL=Cg CL=Cb /////////////////////
	//////////////////////////////////////////////////////
	mov	bx,gs:[esi]	//Line 1 Y1 Y2
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bl					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bl
	sub	al,DL           ;//AL=G=Y-Cg		//////
	mov	dh,bl					//////
	add	dh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,dx,5		;//B[5]
	mov	es:[edi],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+2],ax	;//Write AX=RGB16[5:6:5]
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3            ;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3		;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+4],ax	;//Write AX=RGB16[5:6:5]
	mov	es:[edi+6],ax	;//Write AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
			///U2 V2\\\
	//////////////////////////////////////////////////////
	mov	cx,CrCb
	mov	dx,Cg
	//////////////////////////////////////////////////////
	mov	bh,gs:[esi+2]	//Line 1 Y3 Y4
	//////////////////////////////////////////////////////
	///////// R G B //////				//////
	mov	ah,bh					//////
	add	ah,ch		;//AH=R=Y+Cr		//////
	shr	ah,3		;//R[5]
	mov	al,bh					//////
	sub	al,DL           ;//AL=G=Y-Cg		//////
	add	bh,cl		;//DH=B=Y+Cb		//////
	//////////////////////////////////////////////////////
	shr	ax,3            ;//G[5]
	shld	ax,bx,5		;//B[5]
	mov	es:[edi+8],ax	;//Write 1 AX=RGB16[5:6:5]
	mov	es:[edi+10],ax	;//Write 1 AX=RGB16[5:6:5]
	//////////////////////////////////////////////////////
	add	edi,12		;//Y source 4 byte
	add	esi,4		;//Y source 4 byte
	add	ebp,2		;//UV source 2 byts
	}
	//	EDI had add when write pixel
}
/////////////////////////// YUV->RGB //////////////////////////
extern	short	VCDHigh;
extern	short	OffScrSel;
extern	unsigned long	LinearOffSurface;
extern	unsigned long	LinearSelSurface;
void	DrawYVU12(void)	//YVU12 Planar
{
	asm	push	ds
	_CX=VCDHigh;
	asm	push	cx
	asm	mov	es,OffScrSel;
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_DX=LinearSelSurface;
	__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
	__emit__(0x26,0x66,0x8B,0x5D,0x08);//asm mov ebx,es:[di+8]
	__emit__(0x26,0x8E,0x5D,0x10);	//asm	mov ds,es:[di+0x10]	//GS-> Video data
	asm	mov	es,dx
	///////// Move Y Data //////////
	_DX=_CX;
	MoveYData:
		_ECX=88;
		__emit__(0xF3,0x66,0x67,0xA5);//asm	rep	movsd//32 bits address
		_ESI+=800;
	asm	dec	dx
	asm	jnz	MoveYData
	////////// Move V Data //////////
	_ESI=_EBX;
	_ESI+=0x240;	//VPlane
	asm	pop	cx
	_DX=_CX/2;
	asm	push	dx
	MoveVData:
		_ECX=44;
		__emit__(0xF3,0x66,0x67,0xA5);//asm	rep	movsd//32 bits address
		_ESI+=976;
	asm	dec	dx
	asm	jnz	MoveVData
	////////// Move U Data //////////
	_ESI=_EBX;	//UPlane
	asm	pop	dx
	MoveUData:
		_ECX=44;
		__emit__(0xF3,0x66,0x67,0xA5);//asm	rep	movsd//32 bits address
		_ESI+=976;
	asm	dec	dx
	asm	jnz	MoveUData
	asm	pop	ds
}
void	DrawYVU9(void)	//YVU9 Planar
{
	_CX=VCDHigh;
	asm	push	ds
	asm	push	cx
	asm	mov	es,OffScrSel;
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_DX=LinearSelSurface;
	asm 	mov 	esi,es:[di+4]
	asm 	mov 	ebx,es:[di+8]
	asm	mov 	ds,es:[di+0x10]	//GS-> Video data
	asm	mov 	gs,es:[di+0x10]	//GS-> Video data
	asm	mov	es,dx
	///////// Move Y Data //////////
	_DX=_CX;
	MoveYData:
		_ECX=88;
		__emit__(0xF3,0x66,0x67,0xA5);//asm	rep	movsd//32 bits address
		_ESI+=800;
	asm	dec	dx
	asm	jnz	MoveYData
	/////////////////////////////////
	asm	pop	cx
	asm	pop	ds
	////////// Move V Data //////////
	_ESI=_EBX;
	_ESI+=0x240;	//VPlane
	_DX=_CX/4;
	asm	push	dx
	MoveVData:
		_CX=176/16;
		MoveVdata:
		asm	mov	al,gs:[esi]
		asm	mov	ah,gs:[esi+2]
		asm	mov	es:[edi],ax
		asm	mov	al,gs:[esi+4]
		asm	mov	ah,gs:[esi+6]
		asm	mov	es:[edi+2],ax
		asm	mov	al,gs:[esi+8]
		asm	mov	ah,gs:[esi+10]
		asm	mov	es:[edi+4],ax
		asm	mov	al,gs:[esi+12]
		asm	mov	ah,gs:[esi+14]
		asm	mov	es:[edi+6],ax
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	cx
		asm	jnz	MoveVdata
		_ESI+=(976+0x480);
	asm	dec	dx
	asm	jnz	MoveVData
	////////// Move U Data //////////
	_ESI=_EBX;	//UPlane
	asm	pop	dx
	MoveUData:
		_ECX=176/16;
		MoveUdata:
		asm	mov	al,gs:[esi]
		asm	mov	ah,gs:[esi+2]
		asm	mov	es:[edi],ax
		asm	mov	al,gs:[esi+4]
		asm	mov	ah,gs:[esi+6]
		asm	mov	es:[edi+2],ax
		asm	mov	al,gs:[esi+8]
		asm	mov	ah,gs:[esi+10]
		asm	mov	es:[edi+4],ax
		asm	mov	al,gs:[esi+12]
		asm	mov	ah,gs:[esi+14]
		asm	mov	es:[edi+6],ax
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	cx
		asm	jnz	MoveUdata
		_ESI+=(976+0x480);
	asm	dec	dx
	asm	jnz	MoveUData
}
void	DrawIF09(void)	//YVU9 Planar and pitch
{
	_CX=VCDHigh;
	asm	mov	es,OffScrSel;
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_EDI+=(101376L+6336);	//U position
	asm	push	edi
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_EDI+=101376L;	//V position
	asm	push	edi
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_DX=LinearSelSurface;
	asm	push	ds
	asm	push	cx
	asm 	mov 	esi,es:[di+4]
	asm 	mov 	ebx,es:[di+8]
	asm	mov 	ds,es:[di+0x10]	//GS-> Video data
	asm	mov 	gs,es:[di+0x10]	//GS-> Video data
	asm	mov	es,dx
	///////// Move Y Data //////////
	_DX=_CX;
	MoveYData:
		_ECX=88;
		__emit__(0xF3,0x66,0x67,0xA5);//asm	rep	movsd//32 bits address
		_ESI+=800;
	asm	dec	dx
	asm	jnz	MoveYData
	/////////////////////////////////
	asm	pop	cx
	asm	pop	ds
	////////// Move V Data //////////
	asm	pop	edi	//V Plane position
	_ESI=_EBX;
	_ESI+=0x240;	//VPlane
	_DX=_CX/4;
	asm	push	dx
	MoveVData:
		_CX=176/16;
		MoveVdata:
		asm	mov	al,gs:[esi]
		asm	mov	ah,gs:[esi+2]
		asm	mov	es:[edi],ax
		asm	mov	al,gs:[esi+4]
		asm	mov	ah,gs:[esi+6]
		asm	mov	es:[edi+2],ax
		asm	mov	al,gs:[esi+8]
		asm	mov	ah,gs:[esi+10]
		asm	mov	es:[edi+4],ax
		asm	mov	al,gs:[esi+12]
		asm	mov	ah,gs:[esi+14]
		asm	mov	es:[edi+6],ax
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	cx
		asm	jnz	MoveVdata
		_ESI+=(976+0x480);
	asm	dec	dx
	asm	jnz	MoveVData
	////////// Move U Data //////////
	asm	pop	dx
	asm	pop	edi	//U Plane position
	_ESI=_EBX;	//UPlane
	MoveUData:
		_CX=176/16;
		MoveUdata:
		asm	mov	al,gs:[esi]
		asm	mov	ah,gs:[esi+2]
		asm	mov	es:[edi],ax
		asm	mov	al,gs:[esi+4]
		asm	mov	ah,gs:[esi+6]
		asm	mov	es:[edi+2],ax
		asm	mov	al,gs:[esi+8]
		asm	mov	ah,gs:[esi+10]
		asm	mov	es:[edi+4],ax
		asm	mov	al,gs:[esi+12]
		asm	mov	ah,gs:[esi+14]
		asm	mov	es:[edi+6],ax
		asm	add	edi,8
		asm	add	esi,16
		asm	dec	cx
		asm	jnz	MoveUdata
		_ESI+=(976+0x480);
	asm	dec	dx
	asm	jnz	MoveUData
}
void	DrawYUY2(void)	//YUYV 4:2:2 byte ordering
{
//	asm	push	ebp
	asm	mov	es,OffScrSel;
	asm 	mov 	esi,es:[di+4]
	asm	mov 	ebp,es:[di+8]
	asm	mov 	gs,es:[di+0x10]	//GS-> Video data
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_ES=LinearSelSurface;
	///////// Move YUYV Data //////////
	_BX=VCDHigh;
	_DX=_BX/2;
	MoveYUY2Data:
		_CX=176/2;
		Move2LineData:
		asm	mov	ah,gs:[ebp+0x240]
		asm	mov	bh,gs:[ebp+0x241]
		asm	mov	al,gs:[esi+1]
		asm	mov	bl,gs:[esi+3]
		asm	shl	eax,16		//V0Y1
		asm	shl	ebx,16		//V1Y3
		asm	mov	al,gs:[esi]
		asm	mov	ah,gs:[ebp]	//U0Y0
		asm	mov	bl,gs:[esi+2]
		asm	mov	bh,gs:[ebp+1]	//U1Y2
		asm	mov	es:[edi],eax		//Y1V0Y0U0
		asm	mov	es:[edi+4],ebx		//Y3V1Y2U1
		//////////// Line 2 ////////////
		asm	mov	ah,gs:[ebp+0x240]
		asm	mov	bh,gs:[ebp+0x241]
		asm	mov	al,gs:[esi+0x480+1]
		asm	mov	bl,gs:[esi+0x480+3]
		asm	shl	eax,16		//V0Y1
		asm	shl	ebx,16		//V1Y3
		asm	mov	al,gs:[esi+0x480]
		asm	mov	ah,gs:[ebp]	//U0Y0
		asm	mov	bl,gs:[esi+0x480+2]
		asm	mov	bh,gs:[ebp+1]	//U1Y2
		asm	mov	es:[edi+704],eax
		asm	mov	es:[edi+704+4],ebx
		asm	add	edi,8
		asm	add	esi,4
		asm	add	ebp,2
		asm	dec	cx
		__emit__(0x0F,0x85,0x5B,0xFF);//asm	jnz	Move2LineData
	_EBP+=976;
	_ESI+=(800+0x480);
	_EDI+=704;
	asm	dec	dx
	__emit__(0x0F,0x85,0x3E,0xFF);//asm	jnz	MoveYUY2Data
//	asm	pop	ebp
}
void	DrawYVYU(void)	//YVYU 4:2:2 byte ordering
{
//	asm	push	ebp
	asm	mov	es,OffScrSel;
	asm 	mov 	esi,es:[di+4]
	asm	mov 	ebp,es:[di+8]
	asm	mov 	gs,es:[di+0x10]	//GS-> Video data
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_ES=LinearSelSurface;
	///////// Move YUYV Data //////////
	_BX=VCDHigh;
	_DX=_BX/2;
	MoveYUY2Data:
		_CX=176/2;
		Move2LineData:
		asm	mov	ah,gs:[ebp]	//U0
		asm	mov	bh,gs:[ebp+1]	//U1
		asm	mov	al,gs:[esi+1]	//Y1
		asm	mov	bl,gs:[esi+3]	//Y3
		asm	shl	eax,16		//U0Y1
		asm	shl	ebx,16		//U1Y3
		asm	mov	al,gs:[esi]
		asm	mov	ah,gs:[ebp+0x240]	//V0Y0
		asm	mov	bl,gs:[esi+2]
		asm	mov	bh,gs:[ebp+0x241]	//V1Y2
		asm	mov	es:[edi],eax		//Y0V0Y1U0
		asm	mov	es:[edi+4],ebx		//Y2V1Y3U1
		//////////// Line 2 ////////////
		asm	mov	ah,gs:[ebp]	//U0
		asm	mov	bh,gs:[ebp+1]	//U1
		asm	mov	al,gs:[esi+0x480+1]
		asm	mov	bl,gs:[esi+0x480+3]
		asm	shl	eax,16		//U0Y1
		asm	shl	ebx,16		//U1Y3
		asm	mov	al,gs:[esi+0x480]
		asm	mov	ah,gs:[ebp+0x240]	//V0Y0
		asm	mov	bl,gs:[esi+0x480+2]
		asm	mov	bh,gs:[ebp+0x241]	//V1Y2
		asm	mov	es:[edi+704],eax	//Y0V0Y1U0
		asm	mov	es:[edi+704+4],ebx	//Y2V1Y3U1
		asm	add	edi,8
		asm	add	esi,4
		asm	add	ebp,2
		asm	dec	cx
		__emit__(0x0F,0x85,0x5B,0xFF);//asm	jnz	Move2LineData
	_EBP+=976;
	_ESI+=(800+0x480);
	_EDI+=704;
	asm	dec	dx
	__emit__(0x0F,0x85,0x3E,0xFF);//asm	jnz	MoveYUY2Data
//	asm	pop	ebp
}
void	DrawUYVY(void)	//UYVY 4:2:2 byte ordering
{
//	asm	push	ebp
	asm	mov	es,OffScrSel;
	asm 	mov 	esi,es:[di+4]
	asm	mov 	ebp,es:[di+8]
	asm	mov 	gs,es:[di+0x10]	//GS-> Video data
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	_ES=LinearSelSurface;
	///////// Move YUYV Data //////////
	_BX=VCDHigh;
	_DX=_BX/2;
	MoveYUY2Data:
		_CX=176/2;
		Move2LineData:
		asm	mov	al,gs:[ebp+0x240]	//V0
		asm	mov	bl,gs:[ebp+0x241]	//V1
		asm	mov	ah,gs:[esi+1]
		asm	mov	bh,gs:[esi+3]
		asm	shl	eax,16		//[Y1V0][0]
		asm	shl	ebx,16		//[Y3V1][0]
		asm	mov	ah,gs:[esi]
		asm	mov	al,gs:[ebp]	//[Y0U0]
		asm	mov	bh,gs:[esi+2]
		asm	mov	bl,gs:[ebp+1]	//[Y2U1]
		asm	mov	es:[edi],eax		//U0Y0V0Y1
		asm	mov	es:[edi+4],ebx		//U1Y2V1Y3
		//////////// Line 2 ////////////
		asm	mov	al,gs:[ebp+0x240]	//V0
		asm	mov	bl,gs:[ebp+0x241]	//V1
		asm	mov	ah,gs:[esi+0x480+1]	//Y1
		asm	mov	bh,gs:[esi+0x480+3]	//Y3
		asm	shl	eax,16		//[Y1V0][0]
		asm	shl	ebx,16		//[Y3V1][0]
		asm	mov	ah,gs:[esi+0x480]
		asm	mov	al,gs:[ebp]		//[Y0U0]
		asm	mov	bh,gs:[esi+0x480+2]
		asm	mov	bl,gs:[ebp+1]		//[Y2U1]
		asm	mov	es:[edi+704],eax	//U0Y0V0Y1
		asm	mov	es:[edi+704+4],ebx	//U1Y2V1Y3
		asm	add	edi,8
		asm	add	esi,4
		asm	add	ebp,2
		asm	dec	cx
		__emit__(0x0F,0x85,0x5B,0xFF);//asm	jnz	Move2LineData
	_EBP+=976;
	_ESI+=(800+0x480);
	_EDI+=704;
	asm	dec	dx
	__emit__(0x0F,0x85,0x3E,0xFF);//asm	jnz	MoveYUY2Data
//	asm	pop	ebp
}
///////////////////////////////////////////////////////////////
