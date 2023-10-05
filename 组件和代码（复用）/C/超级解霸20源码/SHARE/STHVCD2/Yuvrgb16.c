////////////////////////////////////////////////////////
//		  YUV to RGB Decoder.
//	Display on different mode use different ways.
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
//#pragma	option	-zC_TEXT	//This Must in _TEXT segment because the library & Enter point in _TEXT
#include <windows.h>
#include "DOS.H"
#include "DCI.H"
#include "VCDAPI.H"

extern	WORD	Linear;
extern	HGLOBAL	OffScrSel;
extern	int	DisplayVideo;
extern	long	VCDHigh;
extern	int	DeleteLine;
int	Line;
int	Pixels;
int	Counter;
int	TimesColor=0;
DWORD	LinearOffSurface;
DWORD	LinearSelSurface;
extern	LPDCIOFFSCREEN	DCISurfaceScreenPtr;
extern	DCIOFFSCREEN	DCISurfaceScreen;	//Offscreen or primary
RECT	VideoRc={0,0,640,240};
#pragma	warn	-par
///////////////// Draw YUV to RGB supported VGA ///////////////
extern	DWORD	DCIYUVFormat;
extern	int	DisplayPreView;
extern	int	CapturePictureFlags;
static	void	Align00(void){}
void	PASCAL _huge DrawYUVDCI(LPDCISURFACEINFO lpSurface)
{	//Only for DCI Supported YUV to RGB
	//BeginAccess
	if(!DisplayVideo)
		{
		if(DisplayPreView)	PreViewPicture();//Draw preview
		if(CapturePictureFlags)	DecodeCapturePicture();//Capture
		_AX=0;
		return;
		}
	if(DCISurfaceScreen.dciInfo.BeginAccess!=NULL)
		(*DCISurfaceScreen.dciInfo.BeginAccess)(DCISurfaceScreenPtr,&VideoRc);
	// Move Data to Offscreen with its format.
	_ES=LinearSelSurface;
	_EDX=VCDHigh;
	_EDI=LinearOffSurface;		//ES:EDI->Offscreen
	if(DCIYUVFormat==0x32595559) DrawYUY2();	//'YUY2'
	if(DCIYUVFormat==0x55595659) DrawYVYU();	//'YVYU'
	if(DCIYUVFormat==0x59565955) DrawUYVY();	//'UYVY'
	if(DCIYUVFormat==0x39304649) DrawYVU9();//DrawIF09();	//'IF09'
	if(DCIYUVFormat==0x39555659) DrawYVU9();	//'YVU9'
	if(DCIYUVFormat==0x32315659) DrawYVU12();	//'YV12'
	//Draw YUV data with standard format.
	(*DCISurfaceScreen.Draw)((LPDCISURFACEINFO)DCISurfaceScreenPtr);
	//EndAccess
	if(DCISurfaceScreen.dciInfo.EndAccess!=NULL)
		(*DCISurfaceScreen.dciInfo.EndAccess)(DCISurfaceScreenPtr);
	_AX=0;
}
#pragma	warn	.par
void	FastYUV2RGB16Bits(void);
void	FastYUV2RGB16BitsDeletePixel(void);
void	FastYUV2RGB16Bits1Line(void);
void	FastYUV2RGB16Bits1LineDeletePixel(void);//Delete one pixel
static	void	Align36(void)
{
	asm	nop
}
void	PASCAL near DrawYVU16Color(void)
{	//Only for 320x200 64K Color

	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=120;
		MoveVideoData240:
		asm	inc	Counter
		asm	cmp	Counter,3
		asm	je	DeleteLine240
		////// 352 bytes 32 times.
		Pixels=8;
		LoopLine240:
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		goto	RETURN;
		DeleteLine240:
		asm	mov	Counter,0
		Pixels=8;
		LoopLine240Delete:
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240Delete
		_EBP+=976;
		_ESI+=(800+0x480);//2 line had draw only one
		asm	dec	Line
		asm	jz	NextRet240
		asm	jmp	MoveVideoData240
		NextRet240:
		}
	else	{// 288 - > 200 36/25 delete 11 lines.
		TimesColor=0;
		/////////////352x288/////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	TimesColor
		if(TimesColor>18) TimesColor=1;
		asm	inc	Counter
		asm	cmp	Counter,1
		asm	je	NoDeleteLine288
		////// 352 bytes 32 times.
		if(TimesColor>12 || Counter>=3) Counter=0;
		Pixels=8;	//Draw 1 lines
		LoopLine288Delete:
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		NoDeleteLine288://Draw 2 lines
		Pixels=8;
		LoopLine288:
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;	//2 line had draw
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
/////////////////////// RGB 15 ///////////////////
static	void	Align1(void)
{
	asm	nop
}
void	FastYUV2RGB15Bits(void);
void	FastYUV2RGB15BitsDeletePixel(void);
void	FastYUV2RGB15Bits1Line(void);
void	FastYUV2RGB15Bits1LineDeletePixel(void);//Delete one pixel
void	PASCAL near DrawYVU15Color(void)
{	//Only for 320x200 32K Color

	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=120;
		MoveVideoData240:
		asm	inc	Counter
		asm	cmp	Counter,3
		asm	je	DeleteLine240
		////// 352 bytes 32 times.
		Pixels=8;
		LoopLine240:
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		goto	RETURN;
		DeleteLine240:
		asm	mov	Counter,0
		Pixels=8;
		LoopLine240Delete:
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jz	NextRet240
		asm	jmp	MoveVideoData240
		NextRet240:
		}
	else	{// 288 - > 200 36/25 delete 11 lines.
		TimesColor=0;
		/////////////352x288/////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	TimesColor
		if(TimesColor>18) TimesColor=1;
		asm	inc	Counter
		asm	cmp	Counter,1
		asm	je	NoDeleteLine288
		////// 352 bytes 32 times.
		if(TimesColor>12 || Counter>=3) Counter=0;
		Pixels=8;	//Draw 1 lines
		LoopLine288Delete:
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		NoDeleteLine288://Draw 2 lines
		Pixels=8;
		LoopLine288:
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;	//2 line had draw
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
////////////////// Draw Memory Buffer of Video ////////////////
int	DCIType=0;//If now be 640x480 and had DCI Primary 64K/32K set 1
		// If be offscreen YUV->RGB set 2;
extern	int	BankSize;	//K
extern	WORD	A000Buffer;//A0000 Base address selector
/*********************************************\
/////////////// 640x480 64K///////////////////
void	PASCAL near BuildYVURGB16Color(void)
{	//for 320x240 64K Color in memory
	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=120;
		MoveVideoData240:
		////// 352 bytes 32 times.
		Pixels=8;
		LoopLine240:
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		}
	else	{// 288 - > 240 6/5 delete 1 lines.
		/////////////352x288/////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	Counter
		asm	cmp	Counter,3
		asm	je	DeleteLine288
		////// 352 bytes 32 times.
		Pixels=8;	//Draw 2 lines
		LoopLine288Delete:
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;	//2 line had draw
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		DeleteLine288://Draw 1 lines
		Counter=0;
		Pixels=8;
		LoopLine288:
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
void	PASCAL near Draw640x240Banking64K(void)
{	//Only for VESA 640x480 -> 640x240 banking VGA
	int	BankCnt=4;
	int	BankingSize=BankSize;
	int	Banking=0;	//Select Bank 0
	//Build in memory 320x240 16Bits video data
	asm	push	bp
	BuildYVURGB16Color();	//Linear = Buffer for 320x240 16bits.
	asm	pop	bp
	//Set Bank and draw 64K data
	_ESI=0;
	_ES=A000Buffer;
	_DS=Linear;	//Video shadow buffer
	DrawPicture:
		_AX=0x4F05;
		_BX=0;
		_DX=Banking;
		geninterrupt(0x10);	//Some handbook VGA system will change DX
		_DI=0;
		asm	mov	cx,16384
		Draw64KMemory:
		__emit__(0x67,0xAD);		//asm	lodsw	//32Bit address
		asm	mov 	dx,ax
		__emit__(0x66,0xC1,0xE0,0x10);	//asm	shl	eax,16
		asm	mov	ax,dx
		__emit__(0x66,0xAB);		//asm	stosd
		asm	dec	cx//asm	loop	Draw64KMemory
		asm	jnz	Draw64KMemory
	asm	mov	dx,BankingSize
	asm	add	Banking,dx
	asm	dec	BankCnt
	asm	jne	DrawPicture
	//Select Bank 5
	_AX=0x4F05;
	_BX=0;
	_DX=Banking;
	geninterrupt(0x10);
	_DI=0;
	asm	mov	cx,11264	//lept data.
	Draw64KMemoryLess:
	__emit__(0x67,0xAD);		//asm	lodsw	//32Bit address
	asm	mov 	dx,ax
	__emit__(0x66,0xC1,0xE0,0x10);	//asm	shl	eax,16
	asm	mov	ax,dx
	__emit__(0x66,0xAB);		//asm	stosd
	asm	dec	cx//asm	loop	Draw64KMemoryLess
	asm	jnz	Draw64KMemoryLess
}
\***************************************************/
////////////////// 640x240 Banking mode /////////////
void	FastYUV2RGB16BitsDouble(void);
void	FastYUV2RGB16BitsDoubleDeletePixel(void);
void	FastYUV2RGB16BitsDouble1Line(void);
void	FastYUV2RGB16BitsDouble1LineDeletePixel(void);//Delete one pixel
void	FastYUV2RGB16BitsDouble1LineOnly(void);
void	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel(void);//Delete one pixel
static	void	Align2(void)
{
	asm	nop
}
void	PASCAL	near	DecodeTwoLine64KDouble(void)
{
	asm	mov	Pixels,8
	LoopLine:
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble();
	FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;
}
static	void	Align3(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	DecodeOneLine64KDouble(void)
{
	asm	mov	Pixels,8
	LoopLine:
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align4(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	DecodeOneLine64KMixDouble(void)
{
	asm	mov	Pixels,8
	LoopLine:
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align5(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	Draw40Pixel(void)
{
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
}
static	void	Align6(void)
{
	asm	nop
}
void	PASCAL	near	Over64K1(void)
{
	Draw40Pixel();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	asm	mov	Pixels,6
	LoopLine:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align7(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	Over64K2(void)
{
	asm	mov	Pixels,3
	LoopLine:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	add	dx,dx
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	asm	mov	Pixels,4
	LoopLine1:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine1
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align8(void)
{
}
void	PASCAL	near	Over64K3(void)
{
	asm	mov	Pixels,4
	LoopLine:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	add	dx,dx
	asm	add	dx,BankSize
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	asm	mov	Pixels,3
	LoopLine1:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine1
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align9(void)
{
}
void	PASCAL	near	Over64K4(void)
{
	asm	mov	Pixels,6
	LoopLine:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnly();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	shl	dx,2
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1LineOnly();
	FastYUV2RGB16BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	Draw40Pixel();
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
void	Decode5Lines(void)
{
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeOneLine64KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align10(void)
{
	asm	nop
	asm	nop
}
void	First64KOver(void)
{//Draw 5 Line
	DecodeOneLine64KDouble();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	_EBP-=0x480;
	Over64K1();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeOneLine64KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align11(void)
{
}
void	Second64KOver(void)
{//Draw 5 Line
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	Over64K2();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	_EBP-=0x480;
	DecodeOneLine64KDouble();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	DecodeOneLine64KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align12(void)
{
}
void	Third64KOver(void)
{//Draw 5 Line
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeOneLine64KDouble();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	_EBP-=0x480;
	Over64K3();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	DecodeOneLine64KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align13(void)
{
}
void	PASCAL	near	Over64K4Mix(void)
{
	asm	mov	Pixels,6
	LoopLine:
	Draw40Pixel();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1Line();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	shl	dx,2
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB16BitsDouble1Line();
	FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
	Draw40Pixel();
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
void	Fouth64KOver(void)
{//Draw 5 Line
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeTwoLine64KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	Over64K4Mix();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=(800);
}
DWORD	lStride;	//Video Memory Line width.
static	void	Align14(void)
{
	asm	nop
	asm	nop
}
void	PASCAL near Draw640x240Banking64K(void)
{	//Only for VESA 640x480 -> 640x240 banking VGA
	_AX=0x4F05;
	_BX=0;_DX=0;
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		////// First 50 Lines /////////
		Line=25;
		MoveVideoData2401:
			DecodeTwoLine64KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2401
		/////// Next Line ///////
		DecodeOneLine64KDouble();_ESI+=800;	//1 line had draw
		_EBP-=0x480;
		Over64K1(); _ESI+=800;// Full 64K
		////// 2nd 50 Lines /////////
		Line=25;
		MoveVideoData2402:
			DecodeTwoLine64KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2402
		/////// Next Line ///////
		Over64K2();_ESI+=800;// Full 64K
		_EBP-=0x480;
		DecodeOneLine64KDouble();_ESI+=800;
		////// 3rd 48 Lines /////////
		Line=24;
		MoveVideoData2403:
			DecodeTwoLine64KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2403
		/////// Next Line ///////
		DecodeOneLine64KDouble();_ESI+=800;
		_EBP-=0x480;
		Over64K3();	_ESI+=800;// Full 64K
		////// 4th 50 Lines /////////
		Line=25;
		MoveVideoData2404:
			DecodeTwoLine64KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2404
		/////// Next Line ///////
		Over64K4();_ESI+=800;// Full 64K
		_EBP-=0x480;
		DecodeOneLine64KDouble();_ESI+=800;
		////// First 34 Lines /////////
		Line=17;
		MoveVideoData240:
			DecodeTwoLine64KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData240
		}
	else	{// 288 - > 240 6/5 delete 1 lines.
		/////////////352x288/////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=10;
		Draw50Lines288:
			Decode5Lines();
			asm	dec	Line
			asm	jnz	near ptr Draw50Lines288
		First64KOver();	//First 64K
		Line=9;
		Draw45Lines2881:
			Decode5Lines();
			asm	dec	Line
			asm	jnz	near ptr Draw45Lines2881
		Second64KOver();	//2nd 64K
		Line=9;
		Draw45Lines2882:
			Decode5Lines();
			asm	dec	Line
			asm	jnz	near ptr Draw45Lines2882
		Third64KOver();
		Line=9;
		Draw45Lines2883:
			Decode5Lines();
			asm	dec	Line
			asm	jnz	near ptr Draw45Lines2883
		Fouth64KOver();
		Line=7;
		Draw35Lines288:
			Decode5Lines();
			asm	dec	Line
			asm	jnz	near ptr Draw35Lines288
		}
	_AX=0;	//return 0;
}
////////////////// 640x240 Linear mode /////////////
static	void	Align15(void)
{
	asm	nop
}
void	PASCAL near BuildYVURGB16DoubleColor(void)
{	//for 320x240 64K Color in memory
	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=LinearSelSurface;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=LinearOffSurface;
		Line=120;
		MoveVideoData240:
		////// 352 bytes 32 times.
		Pixels=8;
		LoopLine240:
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=lStride;
		_EDI+=1280;	//640*2
		_EDI+=lStride;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		}
	else	{// 288 - > 240 6/5 delete 1 lines.
		/////////////352x288/////////
		_DX=LinearSelSurface;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=LinearOffSurface;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	Counter
		asm	cmp	Counter,3
		asm	je	DeleteLine288
		////// 352 bytes 32 times.
		Pixels=8;	//Draw 2 lines
		LoopLine288Delete:
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble();
		FastYUV2RGB16BitsDoubleDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=lStride;
		_EDI+=1280;	//2 line had draw
		_EDI+=lStride;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		DeleteLine288://Draw 1 lines
		Counter=0;
		Pixels=8;
		LoopLine288:
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16BitsDouble1Line();
		FastYUV2RGB16BitsDouble1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		_EDI+=lStride;
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
static	void	Align16(void)
{
}
void	PASCAL near Draw640x240Banking64KLinear(void)
{	//Only for VESA 640x480 -> 640x240 Linear VGA Primary DCI
//	LPDCIOFFSCREEN	DCISurfaceScreenPtr;
	DCIRVAL	(CALLBACK *EndAccess)(LPVOID);		//EndAccess Fn

//	DCISurfaceScreenPtr=&DCISurfaceScreen;
	EndAccess=DCISurfaceScreen.dciInfo.EndAccess;
	if(DCISurfaceScreen.dciInfo.BeginAccess!=NULL)
		(*DCISurfaceScreen.dciInfo.BeginAccess)(DCISurfaceScreenPtr,&VideoRc);
	//Build in memory 320x240 16Bits video data
	asm	push	bp
	BuildYVURGB16DoubleColor();	//Linear = Buffer for 320x240 16bits.
	asm	pop	bp
	//Write video linear buffer
	if(EndAccess!=NULL)
		(*EndAccess)(DCISurfaceScreenPtr);
}
//////////////////// 640x480 32K /////////////////
/*************************************************\
void	PASCAL near BuildYVURGB15Color(void)
{	//for 320x240 64K Color in memory
	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=120;
		MoveVideoData240:
		////// 352 bytes 32 times.
		Pixels=8;
		LoopLine240:
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		}
	else	{// 288 - > 240 6/5 delete 1 lines.
		/////////////352x288/////////
		_DX=Linear;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	Counter
		asm	cmp	Counter,3
		asm	je	DeleteLine288
		////// 352 bytes 32 times.
		Pixels=8;	//Draw 2 lines
		LoopLine288Delete:
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;	//2 line had draw
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		DeleteLine288://Draw 1 lines
		Counter=0;
		Pixels=8;
		LoopLine288:
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
void	PASCAL near Draw640x240Banking32K(void)
{	//Only for VESA 640x480 -> 640x240 banking VGA
	int	BankCnt=4;
	int	BankingSize=BankSize;
	int	Banking=0;	//Select Bank 0
	//Build in memory 320x240 16Bits video data
	asm	push	bp
	BuildYVURGB15Color();	//Linear = Buffer for 320x240 16bits.
	asm	pop	bp
	//Set Bank and draw 64K data
	_ESI=0;
	_ES=A000Buffer;
	_DS=Linear;	//Video shadow buffer
	DrawPicture:
		_AX=0x4F05;
		_BX=0;
		_DX=Banking;
		geninterrupt(0x10);
		_DI=0;
		asm	mov	cx,16384
		Draw64KMemory:
		__emit__(0x67,0xAD);		//asm	lodsw	//32Bit address
		asm	mov 	dx,ax
		__emit__(0x66,0xC1,0xE0,0x10);	//asm	shl	eax,16
		asm	mov	ax,dx
		__emit__(0x66,0xAB);		//asm	stosd
		asm	dec	cx//asm	loop	Draw64KMemory
		asm	jnz	Draw64KMemory
	asm	mov	dx,BankingSize
	asm	add	Banking,dx
	asm	dec	BankCnt
	asm	jne	DrawPicture
	//Select Bank 5
	_AX=0x4F05;
	_BX=0;
	_DX=Banking;
	geninterrupt(0x10);
	_DI=0;
	asm	mov	cx,11264	//lept data.
	Draw64KMemoryLess:
	__emit__(0x67,0xAD);		//asm	lodsw	//32Bit address
	asm	mov 	dx,ax
	__emit__(0x66,0xC1,0xE0,0x10);	//asm	shl	eax,16
	asm	mov	ax,dx
	__emit__(0x66,0xAB);		//asm	stosd
	asm	dec	cx//asm	loop	Draw64KMemoryLess
	asm	jnz	Draw64KMemoryLess
}
\********************************************/
////////////////// 640x240 Banking mode /////////////
void	FastYUV2RGB15BitsDouble(void);
void	FastYUV2RGB15BitsDoubleDeletePixel(void);
void	FastYUV2RGB15BitsDouble1Line(void);
void	FastYUV2RGB15BitsDouble1LineDeletePixel(void);//Delete one pixel
void	FastYUV2RGB15BitsDouble1LineOnly(void);
void	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel(void);//Delete one pixel
static	void	Align17(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	DecodeTwoLine32KDouble(void)
{
	asm	mov	Pixels,8
	LoopLine:
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble();
	FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;
}
static	void	Align18(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	DecodeOneLine32KDouble(void)
{
	asm	mov	Pixels,8
	LoopLine:
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align19(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	DecodeOneLine32KMixDouble(void)
{
	asm	mov	Pixels,8
	LoopLine:
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align20(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	Draw40Pixel32K(void)
{
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
}
static	void	Align21(void)
{
	asm	nop
}
void	PASCAL	near	Over32K1(void)
{
	Draw40Pixel32K();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	asm	mov	Pixels,6
	LoopLine:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align22(void)
{
	asm	nop
	asm	nop
}
void	PASCAL	near	Over32K2(void)
{
	asm	mov	Pixels,3
	LoopLine:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	add	dx,dx
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	asm	mov	Pixels,4
	LoopLine1:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine1
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align23(void)
{
}
void	PASCAL	near	Over32K3(void)
{
	asm	mov	Pixels,4
	LoopLine:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	add	dx,dx
	asm	add	dx,BankSize
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	asm	mov	Pixels,3
	LoopLine1:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine1
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
static	void	Align24(void)
{
}
void	PASCAL	near	Over32K4(void)
{
	asm	mov	Pixels,6
	LoopLine:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnly();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	shl	dx,2
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1LineOnly();
	FastYUV2RGB15BitsDouble1LineOnlyDeletePixel();//Delete one pixel
	Draw40Pixel32K();
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
void	Decode5Lines32K(void)
{
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeOneLine32KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align25(void)
{
	asm	nop
	asm	nop
}
void	First32KOver(void)
{//Draw 5 Line
	DecodeOneLine32KDouble();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	_EBP-=0x480;
	Over32K1();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeOneLine32KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align26(void)
{
}
void	Second32KOver(void)
{//Draw 5 Line
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	Over32K2();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	_EBP-=0x480;
	DecodeOneLine32KDouble();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	DecodeOneLine32KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align27(void)
{
}
void	Third32KOver(void)
{//Draw 5 Line
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeOneLine32KDouble();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	_EBP-=0x480;
	Over32K3();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=800;	//1 line had draw
	DecodeOneLine32KMixDouble();	//Two lines mix to one line
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
}
static	void	Align28(void)
{
}
void	PASCAL	near	Over32K4Mix(void)
{
	asm	mov	Pixels,6
	LoopLine:
	Draw40Pixel32K();
	asm	dec	Pixels		//asm	loop	LoopLine240
	asm	jnz	LoopLine
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1Line();
	__emit__(0x66,0x33,0xFF);
	_AX=0x4F05;_BX=0;_DX=BankSize;
	asm	shl	dx,2
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	FastYUV2RGB15BitsDouble1Line();
	FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
	Draw40Pixel32K();
	_EBP+=976;		//All Y, U, V Line len=0x480;
}
void	Fouth32KOver(void)
{//Draw 5 Line
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	DecodeTwoLine32KDouble();
	__emit__(0x66,0x81,0xC6,0xA0,0x07,0x00,0x00);//_ESI+=(800+0x480);
	__emit__(0x66,0x81,0xC7,0x00,0x05,0x00,0x00);//_EDI+=1280;	//2 line had draw
	Over32K4Mix();
	__emit__(0x66,0x81,0xC6,0x20,0x03,0x00,0x00);//_ESI+=(800);
}
DWORD	lStride;	//Video Memory Line width.
static	void	Align29(void)
{
	asm	nop
	asm	nop
}
void	PASCAL near Draw640x240Banking32K(void)
{	//Only for VESA 640x480 -> 640x240 banking VGA
	_AX=0x4F05;
	_BX=0;_DX=0;
	geninterrupt(0x10);	//Some handbook VGA system will change DX
	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		////// First 50 Lines /////////
		Line=25;
		MoveVideoData2401:
			DecodeTwoLine32KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2401
		/////// Next Line ///////
		DecodeOneLine32KDouble();_ESI+=800;	//1 line had draw
		_EBP-=0x480;
		Over32K1(); _ESI+=800;// Full 64K
		////// 2nd 50 Lines /////////
		Line=25;
		MoveVideoData2402:
			DecodeTwoLine32KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2402
		/////// Next Line ///////
		Over32K2();_ESI+=800;// Full 64K
		_EBP-=0x480;
		DecodeOneLine32KDouble();_ESI+=800;
		////// 3rd 48 Lines /////////
		Line=24;
		MoveVideoData2403:
			DecodeTwoLine32KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2403
		/////// Next Line ///////
		DecodeOneLine32KDouble();_ESI+=800;
		_EBP-=0x480;
		Over32K3();	_ESI+=800;// Full 64K
		////// 4th 50 Lines /////////
		Line=25;
		MoveVideoData2404:
			DecodeTwoLine32KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData2404
		/////// Next Line ///////
		Over32K4();_ESI+=800;// Full 64K
		_EBP-=0x480;
		DecodeOneLine32KDouble();_ESI+=800;
		////// First 34 Lines /////////
		Line=17;
		MoveVideoData240:
			DecodeTwoLine32KDouble();
			_ESI+=(800+0x480);_EDI+=1280;	//2 line had draw
			asm	dec	Line
			asm	jnz	near ptr MoveVideoData240
		}
	else	{// 288 - > 240 6/5 delete 1 lines.
		/////////////352x288/////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=10;
		Draw50Lines288:
			Decode5Lines32K();
			asm	dec	Line
			asm	jnz	near ptr Draw50Lines288
		First32KOver();	//First 64K
		Line=9;
		Draw45Lines2881:
			Decode5Lines32K();
			asm	dec	Line
			asm	jnz	near ptr Draw45Lines2881
		Second32KOver();	//2nd 64K
		Line=9;
		Draw45Lines2882:
			Decode5Lines32K();
			asm	dec	Line
			asm	jnz	near ptr Draw45Lines2882
		Third32KOver();
		Line=9;
		Draw45Lines2883:
			Decode5Lines32K();
			asm	dec	Line
			asm	jnz	near ptr Draw45Lines2883
		Fouth32KOver();
		Line=7;
		Draw35Lines288:
			Decode5Lines32K();
			asm	dec	Line
			asm	jnz	near ptr Draw35Lines288
		}
	_AX=0;	//return 0;
}
static	void	Align30(void)
{
	asm	nop
}
void	PASCAL near BuildYVURGB15DoubleColor(void)
{	//for 320x240 32K Color in memory
	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=LinearSelSurface;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=LinearOffSurface;
		Line=120;
		MoveVideoData240:
		////// 352 bytes 32 times.
		Pixels=8;
		LoopLine240:
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=lStride;
		_EDI+=1280;	//640*2
		_EDI+=lStride;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		}
	else	{// 288 - > 240 6/5 delete 1 lines.
		/////////////352x288/////////
		_DX=LinearSelSurface;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=LinearOffSurface;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	Counter
		asm	cmp	Counter,3
		asm	je	DeleteLine288
		////// 352 bytes 32 times.
		Pixels=8;	//Draw 2 lines
		LoopLine288Delete:
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble();
		FastYUV2RGB15BitsDoubleDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=lStride;
		_EDI+=1280;	//2 line had draw
		_EDI+=lStride;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		DeleteLine288://Draw 1 lines
		Counter=0;
		Pixels=8;
		LoopLine288:
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15BitsDouble1Line();
		FastYUV2RGB15BitsDouble1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		_EDI+=lStride;
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
static	void	Align31(void)
{
}
void	PASCAL near Draw640x240Banking32KLinear(void)
{	//Only for VESA 640x480 -> 640x240 Linear VGA Primary DCI
//	LPDCIOFFSCREEN	DCISurfaceScreenPtr;
	DCIRVAL	(CALLBACK *EndAccess)(LPVOID);		//EndAccess Fn

//	DCISurfaceScreenPtr=&DCISurfaceScreen;
	EndAccess=DCISurfaceScreen.dciInfo.EndAccess;
	if(DCISurfaceScreen.dciInfo.BeginAccess!=NULL)
		(*DCISurfaceScreen.dciInfo.BeginAccess)(DCISurfaceScreenPtr,&VideoRc);
	//Build in memory 320x240 15Bits video data
	asm	push	bp
	BuildYVURGB15DoubleColor();	//Linear = Buffer for 320x240 15bits.
	asm	pop	bp
	//Draw Primary on linear video memory
	if(EndAccess!=NULL)
		(*EndAccess)(DCISurfaceScreenPtr);
}
////////////////////// 320 X 240 Banking //////////////////////
////////////////////// S3 86 banking //////////////////////////
static	void	Align32(void)
{
	asm	nop
	asm	nop
}
void	PASCAL near DrawYVU16S3BankingColor(void)
{	//Only for 320x200 64K Color S3 86

	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=120;
		MoveVideoData240:
		asm	inc	Counter
		asm	cmp	Counter,2
		asm	je	DeleteLine240
		////// 352 bytes 32 times.
		if(Counter==3) Counter=0;
		Pixels=8;
		LoopLine240:
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();//Full 64K data here
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		goto	RETURN;
		Banking1:
		/////////Select Bank 1 ///////////
		_AX=0x4F05;
		_BX=0;
		_DX=BankSize;//Select Bank 1
		geninterrupt(0x10);
		_EDI=0;
		goto	Banking1Next;
		//////////////////////////////////
		DeleteLine240:
		Pixels=8;
		LoopLine240Delete:
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		if(_EDI==65536) goto	Banking1;
		Banking1Next:
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240Delete
		_EBP+=976;
		_ESI+=(800+0x480);//2 line had draw only one
		asm	dec	Line
		asm	jz	NextRet240
		asm	jmp	MoveVideoData240
		asm	jmp	MoveVideoData240
		NextRet240:
		}
	else	{// 288 - > 200 36/25 delete 11 lines.
		TimesColor=0;
		/////////////352x288/////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	TimesColor
		if(TimesColor>18) TimesColor=1;
		asm	inc	Counter
		asm	cmp	Counter,1
		asm	je	NoDeleteLine288
		////// 352 bytes 32 times.
		if(TimesColor>12 || Counter>=3) Counter=0;
		Pixels=8;	//Draw 1 lines
		LoopLine288Delete:
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		if(_EDI==65536) goto	Banking1L288;
		Banking1Next288:
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits1Line();
		FastYUV2RGB16Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		Banking1L288:
		/////////Select Bank 1 ///////////
		_AX=0x4F05;
		_BX=0;
		_DX=BankSize;//Select Bank 1
		geninterrupt(0x10);
		_EDI=0;
		goto	Banking1Next288;
		NoDeleteLine288://Draw 2 lines
		Pixels=8;
		LoopLine288:
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		FastYUV2RGB16Bits();
		FastYUV2RGB16BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;	//2 line had draw
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
static	void	Align33(void)
{
	asm	nop
}
void	PASCAL near DrawS3BankColor(void)
{	//Only for S3 86 320x200 banking VGA
	/////// Set Bank 0 //////////////
	_AX=0x4F05;
	_BX=0;
	_DX=0;//Select Bank 0
	geninterrupt(0x10);
	DrawYVU16S3BankingColor();	//Linear = Buffer for 320x200 16bits.
}
static	void	Align34(void)
{
	asm	nop
	asm	nop
}
void	PASCAL near Draw32KColorBanking(void)
{	//Only for 320x200 32K Color banking

	asm	mov	es,OffScrSel;
	asm	xor	di,di
	Counter=0;
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=120;
		MoveVideoData240:
		asm	inc	Counter
		asm	cmp	Counter,2
		asm	je	DeleteLine240
		////// 352 bytes 32 times.
		if(Counter==3) Counter=0;
		Pixels=8;
		LoopLine240:
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();//Full 64K data here
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData240
		goto	RETURN;
		Banking1:
		/////////Select Bank 1 ///////////
		_AX=0x4F05;
		_BX=0;
		_DX=BankSize;//Select Bank 1
		geninterrupt(0x10);
		_EDI=0;
		goto	Banking1Next;
		//////////////////////////////////
		DeleteLine240:
		Pixels=8;
		LoopLine240Delete:
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		if(_EDI==65536) goto	Banking1;
		Banking1Next:
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels		//asm	loop	LoopLine240
		asm	jnz	LoopLine240Delete
		_EBP+=976;
		_ESI+=(800+0x480);//2 line had draw only one
		asm	dec	Line
		asm	jz	NextRet240
		asm	jmp	MoveVideoData240
		asm	jmp	MoveVideoData240
		NextRet240:
		}
	else	{// 288 - > 200 36/25 delete 11 lines.
		TimesColor=0;
		/////////////352x288/////////
		_DX=A000Buffer;
		__emit__(0x26,0x66,0x8B,0x75,0x04);//asm mov esi,es:[di+4]
		__emit__(0x26,0x66,0x8B,0x6D,0x08);//asm mov ebp,es:[di+8]
		__emit__(0x26,0x8E,0x6D,0x10);//asm	mov	gs,es:[di+0x10]	//GS-> Video data
		asm	mov	es,dx
		_EDI=0;
		Line=144;//=288/2
		MoveVideoData288:
		asm	inc	TimesColor
		if(TimesColor>18) TimesColor=1;
		asm	inc	Counter
		asm	cmp	Counter,1
		asm	je	NoDeleteLine288
		////// 352 bytes 32 times.
		if(TimesColor>12 || Counter>=3) Counter=0;
		Pixels=8;	//Draw 1 lines
		LoopLine288Delete:
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		if(_EDI==65536) goto	Banking1L288;
		Banking1Next288:
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits1Line();
		FastYUV2RGB15Bits1LineDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288Delete
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw only one
		asm	dec	Line
		asm	jnz	near ptr MoveVideoData288
		goto	RETURN;
		Banking1L288:
		/////////Select Bank 1 ///////////
		_AX=0x4F05;
		_BX=0;
		_DX=BankSize;//Select Bank 1
		geninterrupt(0x10);
		_EDI=0;
		goto	Banking1Next288;
		NoDeleteLine288://Draw 2 lines
		Pixels=8;
		LoopLine288:
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		FastYUV2RGB15Bits();
		FastYUV2RGB15BitsDeletePixel();//Delete one pixel
		asm	dec	Pixels
		asm	jnz	LoopLine288
		_EBP+=976;
		_ESI+=(800+0x480);	//2 line had draw
		_EDI+=640;	//2 line had draw
		asm	dec	Line
		asm	jz	RETURN
		asm	jmp	MoveVideoData288
		}
	RETURN:
	_AX=0;	//return 0;
}
static	void	Align35(void)
{
	asm	nop
}
void	PASCAL near Draw15BitsBanking(void)
{	//Only for 320x200 32K banking VGA
	/////// Set Bank 0 //////////////
	_AX=0x4F05;
	_BX=0;
	_DX=0;//Select Bank 0
	geninterrupt(0x10);
	Draw32KColorBanking();	//Linear = Buffer for 320x200 15bits.
}
