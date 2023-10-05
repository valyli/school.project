////////////////////////////////////////////////////////
//	Visual DCI Supportd for decoder,and pass
//	     data to myself display handler.
//   Can display on gray,10E/10D,111/110 or YUV mode
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
//#pragma	option	-zC_TEXT	//This Must in _TEXT segment because the library & Enter point in _TEXT
#include <windows.h>
#include "DOS.H"
#include "DCI.H"
#include "VCDAPI.H"

/////////////////////////////////////
unsigned pascal far __A000H(void);
WORD	Linear;
int	PixelBits=8;
DWORD	ScrWidth=640;
DWORD	ScrHigh=480;
DWORD	LineWidth=0x400;
/////////////////////////////////////
extern	LPDCIOFFSCREEN		DCISurfaceScreenPtr;
HGLOBAL	OffScrSel=0;
#pragma	warn -par
static	void	Align1(void)
{
	asm	nop
	asm	nop
}
DCIRVAL	CALLBACK _loadds BeginAccess(LPVOID lpSurface,LPRECT lpRdst)
{
	return 0;
}
DCIRVAL	CALLBACK _loadds EndAccess(LPVOID lpSurface)
{
	return 0;
}
void	CALLBACK _loadds DestroySurface(LPVOID lpSurface)
{	//may free the lpSurface->dciInfo.dwSelSurface
	if(OffScrSel!=0)//Free the Offscreen.
		{
		GlobalFree(OffScrSel);
		OffScrSel=0;
		}
}
int	DisplayVideo=0;
long	VCDHigh=240;
int	DeleteLine=3;
typedef	struct	VIDEODATAtag
	{
	DWORD	SelfFlags;	//'STH!'
	DWORD	YPlane;		//Video offset
	DWORD	UPlane;
	DWORD	VPlane;
	DWORD	Selector;	//Video Selector
	DWORD	DataStride;
	DWORD	LineWidth;	//352
	DWORD	LineNumber;	//240 or 288
	}VIDEODATA,FAR *LPVIDEODATA;
extern	int	VESAColor;	//Color bits
extern	int	DCIType;	//If now be 640x480 and had DCI Primary 64K/32K
//////////////////////////////////////////////////////////
void	PASCAL near DrawYVU16Color(void);
void	PASCAL near DrawYVU15Color(void);
void	PASCAL near DrawS3BankColor(void);
void	PASCAL near Draw15BitsBanking(void);
void	PASCAL near Draw640x240Banking64K(void);
void	PASCAL near Draw640x240Banking64KLinear(void);
void	PASCAL near Draw640x240Banking32K(void);
void	PASCAL near Draw640x240Banking32KLinear(void);
void	PASCAL _huge DrawYUVDCI(LPDCISURFACEINFO lpSurface);
//////////////////////////////////////////////////////////
extern	int	BankingFlags;	//No 128K Buffer use banking.
////// This function Complied with Fastest mode BP no saved
void	PASCAL	DrawGrayScale(void)
{	//Gray scale
	int	Count=0;
	int	Line=0;

	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Count=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		asm	mov	ds,es:[di+0x10]
		asm	mov	es,dx
		_EDI=0;
		_DX=200;
		MoveVideoData240:
		////// 352 bytes 32 times.
		asm	inc	Count
		asm	cmp	Count,5
		asm	je	DrawMix2Lines240
		////// 352 bytes 32 times.
		asm	mov	cx,32
		LoopLine240:
		__emit__(0x66,0x67,0xA5);	//asm	movsd//32bit addr
		__emit__(0x66,0x67,0xA5);	//asm	movsd//32bit addr
		__emit__(0x67,0x8B,0x06);	//asm	mov	ax,[esi]
		asm	or	ax,0x0101
		asm	add	al,ah
		asm	rcr	al,1
		__emit__(0x67,0x8A,0x66,0x02);	//asm	mov	ah,[esi+2]
		asm	mov	es:[di],ax	//asm	stosw
		asm	add	di,2
		_ESI+=3;
		asm	dec	cx		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		////////////Delete line/////////
		_ESI+=800;
		asm	dec	dx
		asm	jnz	MoveVideoData240
		goto	RETURN;
		DrawMix2Lines240:
		Count=0;
		Line=32;
		LoopDeleteLine240:
		asm	mov	cx,4
		Mix2Pixel240:
			__emit__(0x67,0x8B,0x06);//asm	mov	ax,[esi]
			__emit__(0x67,0x8B,0x9E,0x80,0x04,0x00,0x00);//asm mov	bx,[esi+0x480]
			asm	or	ax,0x0101
			asm	or	bx,0x0101
			asm	add	ax,bx
			asm	rcr	ax,1
			asm	mov	es:[di],ax	//asm	stosw
			asm	add	di,2
			_ESI+=2;
			asm	dec	cx
			asm	jnz	Mix2Pixel240
		////////////////////
		__emit__(0x67,0x8B,0x06);//asm	mov	ax,[esi]
		__emit__(0x67,0x8B,0x9E,0x80,0x04,0x00,0x00);//asm mov	bx,[esi+0x480]
		asm	or	ax,0x0101
		asm	or	bx,0x0101
		asm	add	ax,bx
		asm	rcr	ax,1
		asm	add	al,ah
		asm	rcr	al,1
		__emit__(0x67,0x8B,0x5E,0x02);//asm	mov	bl,[esi+2]
		__emit__(0x67,0x8A,0xA6,0x82,0x04,0x00,0x00);//asm mov	ah,[esi+0x480+2]
		asm	or	bl,1
		asm	or	ah,1
		asm	add	ah,bl
		asm	rcr	ah,1
		asm	mov	es:[di],ax	//asm	stosw
		asm	add	di,2
		_ESI+=3;
		asm	dec	Line		//asm	loop	LoopLine240
		asm	jnz	LoopDeleteLine240
		////////////Delete line/////////
		_ESI+=(800+0x480);
		asm	dec	dx
		asm	jz	NextRet240
		asm	jmp	MoveVideoData240
		NextRet240:
		}
	else	{
		int	Times=0;
		/////////////352x288/////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		asm	mov	ds,es:[di+0x10]
		asm	mov	es,dx
		_EDI=0;
		_DX=200;//for(i=0;i<200;i++)
		MoveVideoData288:
		////// 352 bytes 32 times.
		asm	inc	Count
		asm	cmp	Count,2
		asm	ja	DrawMix2Lines288
		////// 352 bytes 32 times.
		asm	mov	cx,32
		LoopLine288:
		__emit__(0x66,0x67,0xA5);	//asm	movsd//32bit addr
		__emit__(0x66,0x67,0xA5);	//asm	movsd//32bit addr
		__emit__(0x67,0x8B,0x06);	//asm	mov	ax,[esi]
		asm	or	ax,0x0101
		asm	add	al,ah
		asm	rcr	al,1
		__emit__(0x67,0x8A,0x66,0x02);	//asm	mov	ah,[esi+2]
		asm	mov	es:[di],ax	//asm	stosw
		asm	add	di,2
		_ESI+=3;
		asm	dec	cx		//asm	loop	LoopLine288
		asm	jnz	LoopLine288
		////////////Delete line/////////
		_ESI+=800;
		asm	dec	dx
		asm	jnz	MoveVideoData288
		goto	RETURN;
		DrawMix2Lines288:
		Times++;
		if(Times<8)
			{
			if(Count==4)
				Count=0;
			}
		else	{
			Count=0;
			}
		if(Times==11) Times=0;
		Line=32;
		LoopDeleteLine288:
		asm	mov	cx,4
		Mix2Pixel288:
			__emit__(0x67,0x8B,0x06);//asm	mov	ax,[esi]
			__emit__(0x67,0x8B,0x9E,0x80,0x04,0x00,0x00);//asm mov	bx,[esi+0x480]
			asm	or	ax,0x0101
			asm	or	bx,0x0101
			asm	add	ax,bx
			asm	rcr	ax,1
			asm	mov	es:[di],ax	//asm	stosw
			asm	add	di,2
			_ESI+=2;
			asm	dec	cx
			asm	jnz	Mix2Pixel288
		__emit__(0x67,0x8B,0x06);//asm	mov	ax,[esi]
		__emit__(0x67,0x8B,0x9E,0x80,0x04,0x00,0x00);//asm mov	bx,[esi+0x480]
		asm	or	ax,0x0101
		asm	or	bx,0x0101
		asm	add	ax,bx
		asm	rcr	ax,1
		asm	add	al,ah
		asm	rcr	al,1
		__emit__(0x67,0x8B,0x5E,0x02);//asm	mov	bl,[esi+2]
		__emit__(0x67,0x8A,0xA6,0x82,0x04,0x00,0x00);//asm mov	ah,[esi+0x480+2]
		asm	or	bl,1
		asm	or	ah,1
		asm	add	ah,bl
		asm	rcr	ah,1
		asm	mov	es:[di],ax	//asm	stosw
		asm	add	di,2
		_ESI+=3;
		asm	dec	Line		//asm	loop	LoopLine288
		asm	jnz	LoopDeleteLine288
		////////////Delete line/////////
		_ESI+=(800+0x480);
		asm	dec	dx
		asm	jz	NextRet288
		asm	jmp	MoveVideoData288
		NextRet288:
		}
	RETURN:
	_AX=0;	//return 0;
}
int	DisplayPreView=1;
int	CapturePictureFlags=0;
void	PASCAL _huge DrawYVURGB(LPDCISURFACEINFO lpSurface)
{
	if(!DisplayVideo)
		{
		if(DisplayPreView) PreViewPicture();
		if(CapturePictureFlags) DecodeCapturePicture();
		_AX=0;
		return;
		}
	if(VESAColor==8)
		{//Draw Gray Scale
		DrawGrayScale();
		_AX=0;
		return;
		}
	if(VESAColor==16)
		{//Draw  VESA 64K 320x200
		if(BankingFlags)
			{//S3 no 128K Video Buffer
			DrawS3BankColor();
			_AX=0;
			return;
			}
		else 	{//Normal 128K Video Buffer
			DrawYVU16Color();
			_AX=0;
			return;
			}
		}
	if(VESAColor==15)
		{//Draw  VESA 32K 320x200
		if(BankingFlags)
			{//S3 no 128K Video Buffer
			Draw15BitsBanking();
			_AX=0;
			return;
			}
		else 	{//Normal 128K Video Buffer
			DrawYVU15Color();
			_AX=0;
			return;
			}
		}
	if(VESAColor==163)
		{//Draw S3 86xx 320x200 Banking
		DrawS3BankColor();
		_AX=0;
		return;
		}
	if(VESAColor==64)
		{//640 x 240 VESA 111 640x480 64KC modify
		if(DCIType==1) Draw640x240Banking64KLinear();
		else Draw640x240Banking64K();
		_AX=0;
		return;
		}
	if(VESAColor==32)
		{//640 x 240 VESA 110 640x480 32KC modify
		if(DCIType==1) Draw640x240Banking32KLinear();
		else Draw640x240Banking32K();
		_AX=0;
		return;
		}
}
extern	RECT	SrcRect;
extern	RECT	VideoRc;
extern	DCIOFFSCREEN	DCISurfaceScreen;	//Offscreen or primary
extern	int	Caputuring;
DCIRVAL	CALLBACK _loadds SetDestination(LPVOID lpSurface,LPRECT lprDst,LPRECT lprSrc)
{
	if(Caputuring) return 0;
	VCDHigh=lprSrc->bottom-lprSrc->top;
	if(VCDHigh<0) VCDHigh=240;
	if(VCDHigh==240) DeleteLine=5;//240
	else DeleteLine=3;	//288
	SrcRect.top=lprSrc->top;
	SrcRect.left=lprSrc->left;
	SrcRect.bottom=lprSrc->bottom;
	SrcRect.right=lprSrc->right;
	//////// Set Destination /////////
//	DCISurfaceScreen.dciInfo.dwHeight=lprSrc->bottom-lprSrc->top;
	if(DCISurfaceScreenPtr!=NULL)
		{//The Pointer not be NULL
		DCISurfaceScreenPtr->dciInfo.dwHeight=lprSrc->bottom-lprSrc->top;
		if(DCIType==2)	(*DCISurfaceScreenPtr->SetDestination)(DCISurfaceScreenPtr,lprDst,lprSrc);
		}
	return 0;
}
extern	RGNDATA	RgnData;
static	void	Align4(void)
{
}
DCIRVAL	CALLBACK _loadds SetClipList(LPVOID lpSurface,LPRGNDATA lpClipList)
{
	if(Caputuring) 	return 0;
	if(DCISurfaceScreenPtr!=NULL)
		{//The Pointer not be NULL
		if(DCIType==2)	(*DCISurfaceScreenPtr->SetCliplist)(DCISurfaceScreenPtr,lpClipList);
		}
	return 0;
}
#pragma	warn .par

DCIPRIMARY	Primary;
DCIOFFSCREEN	OffScreen;
DCISURFACEINFO	SurFace;
int	DCISupport(LPDCIENUMINPUT lpInput,DWORD far *lpvOutData)
{
	if(lpInput->dcicmd.dwVersion!=0x100) return -4;
	if(lpInput->dcicmd.dwCommand==4)//DCI ENUM
		{
		void PASCAL far (*CallBackDCI)(LPVOID lpContext,LPDCISURFACEINFO lpSurface);
		CallBackDCI=(void PASCAL far (*)())lpInput->EnumCallback;
		SurFace.dwSize=sizeof(SurFace);
		/////////// YV12 /////////
		SurFace.dwDCICaps=0x3401;
		SurFace.dwCompression=0x32315659;	//'YV12'
		SurFace.dwMask[0]=0;
		SurFace.dwMask[1]=0;
		SurFace.dwMask[2]=0;
		SurFace.dwWidth=ScrWidth;		// Window Width
		SurFace.dwHeight=ScrHigh;		// High
		SurFace.lStride=LineWidth;		// Line Width
		SurFace.dwBitCount=12;			// Color Deep.
		(*CallBackDCI)(&SurFace,lpInput->lpContext);
		/////////// RGB //////////////
		SurFace.dwDCICaps=0x3041;
		if(PixelBits==16)//64K Color
			{
			SurFace.dwCompression=3;
			SurFace.dwMask[0]=0xF800;
			SurFace.dwMask[1]=0x7E0;
			SurFace.dwMask[2]=0x1F;
			}
		else	{//Not RGB 16 bits.
			SurFace.dwCompression=0;
			SurFace.dwMask[0]=0;
			SurFace.dwMask[1]=0;
			SurFace.dwMask[2]=0;
			}
		SurFace.dwWidth=ScrWidth;		// Window Width
		SurFace.dwHeight=ScrHigh;		// High
		SurFace.lStride=LineWidth;		// Line Width
		SurFace.dwBitCount=PixelBits;		// Color Deep.
		(*CallBackDCI)(&SurFace,lpInput->lpContext);
		return 0;
		}
	if(lpInput->dcicmd.dwCommand==1)//DCI Create Primary
		{
		if(lpvOutData==NULL) return -4;
		*lpvOutData=(DWORD)(LPSTR)&Primary;
		Primary.dwSize	=sizeof(Primary);
		Primary.dwDCICaps=0x50;
		if(PixelBits==16)//64K Color
			{
			Primary.dwCompression=3;
			Primary.dwMask[0]=0xF800;
			Primary.dwMask[1]=0x7E0;
			Primary.dwMask[2]=0x1F;
			}
		else	{//Not RGB 16 bits.
			Primary.dwCompression=0;
			Primary.dwMask[0]=0;
			Primary.dwMask[1]=0;
			Primary.dwMask[2]=0;
			}
		Primary.dwWidth		=ScrWidth;	//Width
		Primary.dwHeight	=ScrHigh;	//High
		Primary.lStride		=LineWidth;	//Line byte width
		Primary.dwBitCount	=PixelBits;	//Color deep 16 Bits
		Primary.dwOffSurface	=0;
		Primary.dwSelSurface	=Linear;	//Linear Buffer;
		Primary.dwReserved1	=0;
		Primary.dwReserved2	=0;
		Primary.dwReserved3	=0;
		Primary.BeginAccess	=BeginAccess;
		Primary.EndAccess	=EndAccess;
		Primary.DestroySurface	=DestroySurface;
		return 0;
		}
	if(lpInput->dcicmd.dwCommand==2)//DCI Create OffSurface
		{
		LPDCICREATEINPUT lpCreateOffscreen;
		if(lpvOutData==NULL) return -4;
		OffScrSel=GlobalAlloc(GMEM_MOVEABLE,sizeof(VIDEODATA));
		if(OffScrSel==NULL) return -4;
		lpCreateOffscreen=(LPDCICREATEINPUT)lpvOutData;
		*lpvOutData=(DWORD)(LPSTR)&OffScreen;
		OffScreen.dciInfo.dwSize=sizeof(OffScreen);
		OffScreen.dciInfo.dwDCICaps=0x50;
		OffScreen.dciInfo.dwCompression=0;
		OffScreen.dciInfo.dwMask[0]=0;
		OffScreen.dciInfo.dwMask[1]=0;
		OffScreen.dciInfo.dwMask[2]=0;
		OffScreen.dciInfo.dwWidth	=lpCreateOffscreen->dwWidth;	//Width
		OffScreen.dciInfo.dwHeight	=lpCreateOffscreen->dwHeight;	//High
		OffScreen.dciInfo.lStride	=lpCreateOffscreen->dwWidth;	//Line byte width
		OffScreen.dciInfo.dwBitCount	=12;	//Color deep 16 Bits
		OffScreen.dciInfo.dwOffSurface	=0;
		OffScreen.dciInfo.dwSelSurface	=OffScrSel;//Offscreen Buffer;
		OffScreen.dciInfo.dwReserved1	=0;
		OffScreen.dciInfo.dwReserved2	=0;
		OffScreen.dciInfo.dwReserved3	=0;
		OffScreen.dciInfo.BeginAccess	=0;//BeginAccess;
		OffScreen.dciInfo.EndAccess	=0;//EndAccess;
		OffScreen.dciInfo.DestroySurface=DestroySurface;
		if(DCIType==2)	OffScreen.Draw	=DrawYUVDCI;// DCI YUV->RGB
		else 	OffScreen.Draw	=DrawYVURGB;	//My YUV->RGB
		OffScreen.SetCliplist	=SetClipList;
		OffScreen.SetDestination=SetDestination;
		return 0;
		}
	return -4;
}
void huge TurnOffEscape(void);
void huge TurnOnEscape(void);
int  _huge _pascal MyEscape(HDC hdc,int nEscape,int cbInput,
			LPCSTR	lpszInData,void FAR * lpvOutData)
{
	int	Ret;
	if(nEscape==QUERYESCSUPPORT && cbInput==2)
		{	//Support DCI
		if(*(int far *)lpszInData==0x0C03)
			return	1;
		}
	if(nEscape==0x0C03)
		{
		return 	DCISupport((LPDCIENUMINPUT)lpszInData,(DWORD far *)lpvOutData);
		}
	TurnOnEscape();
	Ret=Escape(hdc,nEscape,cbInput,lpszInData,lpvOutData);
	TurnOffEscape();
	return Ret;
}
#pragma warn .par
unsigned char   Code[10];
void huge TurnOffEscape(void)
{
	unsigned char far       *CallAdr;
	unsigned char far       *PtrAdr;
	unsigned long           Here;
	int     Sel;

	if(*(unsigned long *)Code==0L)
		{
		CallAdr=(unsigned char far *)Escape;// Read Old ernter Point
		PtrAdr=Code;
		*PtrAdr++=*CallAdr++;
		*((unsigned long far *)PtrAdr)=*(unsigned long far *)CallAdr;
		}

	PtrAdr=(unsigned char far *)Escape;
	Sel=FP_SEG(PtrAdr);
	PrestoChangoSelector(Sel,Sel);
	Here=(unsigned long)MyEscape;
	*PtrAdr++=0xEA;
	*((unsigned long far *)PtrAdr)=Here;
	PrestoChangoSelector(Sel,Sel);
}

void huge TurnOnEscape(void)
{
	unsigned char far       *PtrAdr;
	unsigned char far       *CallAdr;
	int     Sel;

	if(*(unsigned long *)Code==0L)
		{
		return;
		}
	PtrAdr=(unsigned char far *)Escape;// Restore Old enter point
	CallAdr=Code;
	Sel=FP_SEG(PtrAdr);
	PrestoChangoSelector(Sel,Sel);
	*PtrAdr++=*CallAdr++;
	*((unsigned long far *)PtrAdr)=*(unsigned long far *)CallAdr;
	PrestoChangoSelector(Sel,Sel);
}
/////////////////////////////////////////
void far (*TrapIO)(void);
void far *GetAPIEntry(int VxD_ID)
{       //if Not support return NULL
	void far *APIPtr;

	_ES=_DI=0;
	_BX=VxD_ID;
	_AX=0x1684;
	geninterrupt(0x2F);
	APIPtr=MK_FP(_ES,_DI);
	return  APIPtr;
}
DWORD	GetBasePage(DWORD Base,DWORD Limit)
{
	_EDX=Limit;
	_EBX=Base;
	_AX=0x00;
	(*TrapIO)();
	return	(DWORD)MK_FP(_DX,_AX);
}
void	VxDSet128KBuffer(void)
{
	_AX=0x01;
	(*TrapIO)();
}
void	VxDSet64KBuffer(void)
{
	_AX=0x01;
	(*TrapIO)();
}
/////////////////////////////////////////
DWORD	VideoBase;
DWORD	VideoPhysBase;
void	SetVideoBufferBase(DWORD Base)
{
	VideoPhysBase=Base;
	VideoBase=GetBasePage(VideoPhysBase,0x20000L);
	SetSelectorBase(Linear,VideoBase);//Base A0000-BFFFF or linear addressing
}
HGLOBAL	VideoShadow;
WORD	A000Buffer;
extern	int	VideoCardType;
extern	int	LinearFlags;
int 	SetDCI(int ScrW,int ScrH,int LineW,int ColorBits)
{
	if(DCIType==2)	return 1;	//YUV->RGB support
	A000Buffer=FP_OFF(__A000H);		//Screen Buffer as A000 Segment.
	if(VESAColor!=8)
		if(VESAColor==64 || VESAColor==32)
		{//S3 86 Banking or 640x240 banking
		ScrWidth=ScrW;
		ScrHigh=ScrH;
		LineWidth=LineW;	//Line Byte Width.
		PixelBits=ColorBits;
//		VideoShadow=GlobalAlloc(GMEM_MOVEABLE,153600L);//320*240*2
//		if(VideoShadow==NULL)	return 0;//false
		Linear=A000Buffer;//VideoShadow;
		return 1;
		}
	TrapIO=GetAPIEntry(0x0543);	// TrapIO_ID = 0x678
	if((long)TrapIO==0)
		{
		MessageBox(NULL,"No Base Support Vxd","Error",MB_OK);
		return 0;
		}
	Linear=A000Buffer;
	Linear=AllocSelector(Linear);	//Allocate a Selector.
	SetSelectorLimit(Linear,0x1FFFF);//12K;
	SetVideoBufferBase(0xA0000);	//Set Video buffer base.
	LinearFlags=1;	//Can write to 128K
	//////////////////////
	ScrWidth=ScrW;
	ScrHigh=ScrH;
	LineWidth=LineW;	//Line Byte Width.
	PixelBits=ColorBits;
	//////////////////////
	return 1;
}

void	ReleaseDCI(void)
{
	WORD	ScrSel;
	if(DCIType==2)	return;	//YUV->RGB support
	if(VESAColor==64 || VESAColor==32)
		{//free video shadow buffer
//		GlobalFree(VideoShadow);
		return;
		}
	ScrSel=FP_OFF(__A000H);
	SetSelectorLimit(Linear,GetSelectorLimit(ScrSel));
	SetSelectorBase(Linear,GetSelectorBase(ScrSel));
	FreeSelector(Linear);//Free it.
}
