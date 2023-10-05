////////////////////////////////////////////////////////
//		Capture picture handle
//	      Decode Picture to 24bit BMP file
//		    Southern.Liang
//		       1996.6.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include <mmsystem.h>
#include <commdlg.h>
#include "DOS.H"
#include "VCDAPI.H"

#define	BEPLAY		8

OPENFILENAME	ofn;
char	DefaultBmpName[]="";
char	DirName[256];
char	FileName[256];
char	FileTitle[256];
char	Filter[]="24Bit RGB Bitmap\0*.BMP\0Double Size 24Bit BMP\0*.BMP\0\
Gray Scale Bitmap\0*.BMP\0NoDither 256Color Bitmap\0*.BMP\0NoDither 256Color \
PCX\0*.PCX\0";
char	BmpTitle[]="Save as Bitmap File";
extern	int	videoID;
extern	HWND	MainWindow;	//Main Windows
extern	HWND	AudioMainWindow;
extern	long	VCDHigh;
extern	HGLOBAL	OffScrSel;
extern	HANDLE 	hInst;
extern	int	Chinese;
BITMAPFILEHEADER	BmpFileHeader=
	{
	0x4D42,		//'BM'
	0,		//Size = SizeImage + 0x36
	0,
	0,
	0x36,		//Offset
	};
BITMAPINFOHEADER	BmpInfoHeader=
	{
	40,	//This struct size
	352,
	240,	//or 288
	1,
	24,	//24bits
	BI_RGB,	//No compress
	0,	//SizeImage = 352 X 240 (or 288) X 3
	0,
	0,
	0,	//Colors used
	0,	//Color Important
	};

static	void	PASCAL	Write24BitBMPHeader(HFILE hFile)
{
	BmpInfoHeader.biSizeImage=352L*VCDHigh*3;
	BmpFileHeader.bfSize=BmpInfoHeader.biSizeImage+0x36;
	BmpInfoHeader.biHeight=VCDHigh;
	BmpInfoHeader.biBitCount=24;
	BmpInfoHeader.biClrUsed=0;
	BmpInfoHeader.biClrImportant=0;
	BmpFileHeader.bfOffBits=0x36;
	/////////////////Write BMP file header /////////////
	_lwrite(hFile,&BmpFileHeader,sizeof(BmpFileHeader));
	_lwrite(hFile,&BmpInfoHeader,sizeof(BmpInfoHeader));
}
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

static	DWORD	PASCAL	DecodeYUVToRGB24Bits(WORD Selector,DWORD YPlane,
				DWORD UPlane,DWORD VPlane)
{
	int	Y,U,V;
	int	R,G,B;
	//////////// Get Y U V/////////////
	_ES=Selector;
	_EBX=YPlane;
	__emit__(0x26,0x67,0x8A,0x03);//asm	mov	al,es:[ebx]
	Y=_AL;
	_EBX=UPlane;
	__emit__(0x26,0x67,0x8A,0x03);//asm	mov	al,es:[ebx]
	U=_AL;
	_EBX=VPlane;
	__emit__(0x26,0x67,0x8A,0x03);//asm	mov	al,es:[ebx]
	V=_AL;
	//////////// Compute /////////////
	U-=128;V-=128;
	U=359L*U/256;
	V=454L*V/256;
	R=Y+U;
	B=Y+V;
	G=Y-U/2-V/5;
	if(R>255) R=255;
	if(G>255) G=255;
	if(B>255) B=255;
	if(R<0) R=0;
	if(G<0) G=0;
	if(B<0) B=0;
	_DL=B;
	_AH=G;_AL=R;
	return (DWORD)MK_FP(_DX,_AX);
}
HGLOBAL		FilehMem=0;
BYTE far *	FilehMemPtr;
static	void	PASCAL	DecodeCapture24BitPicture(void)
{	//Decode the picture and write to file.
	int		x,y;
	LPVIDEODATA	VideoDataPtr;
	DWORD		Offset=0;

	VideoDataPtr=MK_FP(OffScrSel,0);
	if(VideoDataPtr->SelfFlags!=0x21485453) return;
	if(FilehMem==0) return;
	for(y=0;y<VCDHigh;y++)
		{
		WORD	Selector=VideoDataPtr->Selector;
		DWORD	YPlane=VideoDataPtr->YPlane+0x480L*(VCDHigh-y-1);
		DWORD	UPlane=VideoDataPtr->UPlane+0x480L*(VCDHigh/2-y/2-1);
		DWORD	VPlane=VideoDataPtr->VPlane+0x480L*(VCDHigh/2-y/2-1);
		for(x=0;x<352;x++)
			{
			DecodeYUVToRGB24Bits(Selector,YPlane,UPlane,VPlane);
			_ES=FilehMem;
			_EBX=Offset; 	//DX:AX=RGB 32 bits
			__emit__(0x26,0x67,0x89,0x03);//asm es:[ebx],ax
			__emit__(0x26,0x67,0x88,0x53,0x02);//asm es:[ebx+2],dl
			Offset+=3;
			YPlane++;
			UPlane+=(x&1);
			VPlane+=(x&1);
			}
		}
}
static	void	PASCAL	DecodeCaptureGrayScalePicture(void)
{	//Decode the Gray Scale picture and write to file.
	int		x,y;
	LPVIDEODATA	VideoDataPtr;
	DWORD		Offset=0;

	VideoDataPtr=MK_FP(OffScrSel,0);
	if(VideoDataPtr->SelfFlags!=0x21485453) return;
	if(FilehMem==0) return;
	for(y=0;y<VCDHigh;y++)
		{
		WORD	Selector=VideoDataPtr->Selector;
		DWORD	YPlane=VideoDataPtr->YPlane+0x480L*(VCDHigh-y-1);
		for(x=0;x<352;x++)
			{
			_ES=Selector;
			_EAX=YPlane; 	//AL=Y
			__emit__(0x26,0x67,0x8A,0x00);//asm al,es:[eax]
			_ES=FilehMem;
			_EBX=Offset; 	//AL=Y
			__emit__(0x26,0x67,0x88,0x03);//asm es:[ebx],al
			Offset++;
			YPlane++;
			}
		}
}
int	PictureType=1;
void	PASCAL FAR	DecodeCapturePicture(void)	//API
{	//Decode the picture and write to file.
	switch(PictureType)
		{
		case 1: //24 Bit RGB
		case 2:	//Double Size 24 Bit RGB
		case 4:	//256 Color BMP
		case 5:	//256 Color PCX
			DecodeCapture24BitPicture();
			break;
		case 3:	// Gray Scale
			DecodeCaptureGrayScalePicture();
			break;
		}
}
extern	int	CapturePictureFlags;
static	DWORD	CaptureUpDateVideo(int VideoID,HWND MainWindow)
{
	DWORD	Ret;
	MCI_ANIM_UPDATE_PARMS	mciUpdate;
	HDC	hdc;

	mciUpdate.dwCallback=MainWindow;
	mciUpdate.hDC=0;
	mciUpdate.rc.left=mciUpdate.rc.top=0;
	mciUpdate.rc.right=64;mciUpdate.rc.bottom=56;
	Ret=mciSendCommand(VideoID,MCI_UPDATE,MCI_WAIT|
		MCI_ANIM_RECT,(DWORD)(LPVOID)&mciUpdate);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;	//Current Position
}
static	void	PASCAL	Decode24BitsToFile(HFILE hFile)
{
	DWORD	Size=352L*VCDHigh*3;
	FilehMem=GlobalAlloc(GMEM_MOVEABLE,Size);
	if(FilehMem==NULL)
		{
		MessageBox(NULL,"Can't Allocate Error !","Not Enough Memory",MB_ICONSTOP);
		return;
		}
	FilehMemPtr=GlobalLock(FilehMem);
	///////////Start Capture ///////
	CapturePictureFlags=1;
	/////////// Caputre ////////////
	CaptureUpDateVideo(videoID,MainWindow);
	///////////Capture End /////////
	CapturePictureFlags=0;
	////////////// Write /////////////
	_hwrite(hFile,FilehMemPtr,Size);
	//////////////////////////////////
	GlobalUnlock(FilehMem);
	GlobalFree(FilehMem);
}
///////////////////Double Size 24Bit/////////////////////
static	void	PASCAL	WriteD24BitBMPHeader(HFILE hFile)
{
	BmpInfoHeader.biSizeImage=352L*VCDHigh*3*4;
	BmpFileHeader.bfSize=BmpInfoHeader.biSizeImage+0x36;
	BmpInfoHeader.biHeight=VCDHigh*2L;
	BmpInfoHeader.biBitCount=24;
	BmpInfoHeader.biClrUsed=0;
	BmpInfoHeader.biClrImportant=0;
	BmpFileHeader.bfOffBits=0x36;
	BmpInfoHeader.biWidth=352L*2;
	/////////////////Write BMP file header /////////////
	_lwrite(hFile,&BmpFileHeader,sizeof(BmpFileHeader));
	_lwrite(hFile,&BmpInfoHeader,sizeof(BmpInfoHeader));
	BmpInfoHeader.biWidth=352L;
}
static	void	PASCAL	WriteDouble(HFILE hFile,BYTE far * FilehMemPtr)
{
	int		i,j;
	HGLOBAL		hMem;
	BYTE	far	*LocalPtr;
	BYTE	far	*Ptr;
	DWORD		Offset;

	hMem=GlobalAlloc(GMEM_MOVEABLE,4224L);//352L*3*2*2
	LocalPtr=GlobalLock(hMem);
	for(i=0;i<VCDHigh;i++)
		{
		Ptr=LocalPtr;
		Offset=352L*i*3+FP_OFF(FilehMemPtr);
		for(j=0;j<352;j++)
			{
			_ES=FP_SEG(FilehMemPtr);
			_ESI=Offset;
			__emit__(0x26,0x67,0x8B,0x06);//asm 	mov	ax,es:[esi]
			__emit__(0x26,0x67,0x8A,0x56,0x02);//asm     mov	dl,es:[esi+2]
			Offset+=3;
			*(WORD far *)Ptr=_AX;
			*(Ptr+2)=_DL;
			Ptr+=3;
			*(WORD far *)Ptr=_AX;
			*(Ptr+2)=_DL;
			Ptr+=3;
			}
		Offset-=1056L;
		for(j=0;j<352;j++)
			{
			_ES=FP_SEG(FilehMemPtr);
			_ESI=Offset;
			__emit__(0x26,0x67,0x8B,0x06);//asm 	mov	ax,es:[esi]
			__emit__(0x26,0x67,0x8A,0x56,0x02);//asm     mov	dl,es:[esi+2]
			Offset+=3;
			*(WORD far *)Ptr=_AX;
			*(Ptr+2)=_DL;
			Ptr+=3;
			*(WORD far *)Ptr=_AX;
			*(Ptr+2)=_DL;
			Ptr+=3;
			}
		_lwrite(hFile,LocalPtr,4224L);//write 2 lines
		}
	GlobalUnlock(hMem);
	GlobalFree(hMem);
}
static	void	PASCAL	DecodeD24BitsToFile(HFILE hFile)
{
	DWORD	Size=352L*VCDHigh*3;
	FilehMem=GlobalAlloc(GMEM_MOVEABLE,Size);
	if(FilehMem==NULL)
		{
		MessageBox(NULL,"Can't Allocate Error !","Not Enough Memory",MB_ICONSTOP);
		return;
		}
	FilehMemPtr=GlobalLock(FilehMem);
	///////////Start Capture ///////
	CapturePictureFlags=1;
	/////////// Caputre ////////////
	CaptureUpDateVideo(videoID,MainWindow);
	///////////Capture End /////////
	CapturePictureFlags=0;
	////////////// Write /////////////
	WriteDouble(hFile,FilehMemPtr);
	//////////////////////////////////
	GlobalUnlock(FilehMem);
	GlobalFree(FilehMem);
}

///////////////////Gray Scale ///////////////////////////
static	void	PASCAL	Write8BitBMPHeader(HFILE hFile)
{
	BmpInfoHeader.biSizeImage=352L*VCDHigh;
	BmpFileHeader.bfSize=BmpInfoHeader.biSizeImage+0x436;
	BmpInfoHeader.biHeight=VCDHigh;
	BmpInfoHeader.biBitCount=8;
	BmpInfoHeader.biClrUsed=256;
	BmpInfoHeader.biClrImportant=256;
	BmpFileHeader.bfOffBits=0x436;		//BMP Data Offset
	/////////////////Write BMP file header /////////////
	_lwrite(hFile,&BmpFileHeader,sizeof(BmpFileHeader));
	_lwrite(hFile,&BmpInfoHeader,sizeof(BmpInfoHeader));
}
static	int	PASCAL	WriteGrayScalePalette(HFILE hFile)
{
	int	i;
	FilehMem=GlobalAlloc(GMEM_MOVEABLE,0x400);//256 * 4
	if(FilehMem==NULL) return 0;
	FilehMemPtr=GlobalLock(FilehMem);
	for(i=0;i<256;i++)
		{
		*(FilehMemPtr+i*4)  =
		*(FilehMemPtr+i*4+1)=
		*(FilehMemPtr+i*4+2)=i;
		*(FilehMemPtr+i*4+3)=0;
		}
	_lwrite(hFile,FilehMemPtr,0x400);
	GlobalUnlock(FilehMem);
	GlobalFree(FilehMem);
	return 1;
}
static	void	PASCAL	Decode8BitsGrayScaleToFile(HFILE hFile)
{
	DWORD	Size=352L*VCDHigh;

	if(WriteGrayScalePalette(hFile)==0)	//Write Palette
		{
		MessageBox(NULL,"Can't Allocate Error !","Not Enough Memory",MB_ICONSTOP);
		return;
		}
	//////////// Decode a Y picture ////////
	FilehMem=GlobalAlloc(GMEM_MOVEABLE,Size);
	if(FilehMem==NULL)
		{
		MessageBox(NULL,"Can't Allocate Error !","Not Enough Memory",MB_ICONSTOP);
		return;
		}
	FilehMemPtr=GlobalLock(FilehMem);
	///////////Start Capture ///////
	CapturePictureFlags=1;
	/////////// Caputre ////////////
	CaptureUpDateVideo(videoID,MainWindow);
	///////////Capture End /////////
	CapturePictureFlags=0;
	////////////// Write /////////////
	_hwrite(hFile,FilehMemPtr,Size);
	//////////////////////////////////
	GlobalUnlock(FilehMem);
	GlobalFree(FilehMem);
}
static	void	PASCAL	Decode24BitsToMemory(void)
{
	DWORD	Size=352L*VCDHigh*3;
	FilehMem=GlobalAlloc(GMEM_MOVEABLE,Size);
	if(FilehMem==NULL)
		{
		MessageBox(NULL,"Can't Allocate Error !","Not Enough Memory",MB_ICONSTOP);
		return;
		}
	FilehMemPtr=GlobalLock(FilehMem);
	///////////Start Capture ///////
	CapturePictureFlags=1;
	/////////// Caputre ////////////
	CaptureUpDateVideo(videoID,MainWindow);
	///////////Capture End /////////
	CapturePictureFlags=0;
	GlobalUnlock(FilehMem);
}
HGLOBAL	Bmp256CMem;
HGLOBAL	Bmp256CPalMem;
static	int	Allocate256ColorMemory(void)
{
	Bmp256CMem=GlobalAlloc(GMEM_MOVEABLE,352L*VCDHigh);
	if(Bmp256CMem==NULL)	return 0;
	Bmp256CPalMem=GlobalAlloc(GMEM_MOVEABLE,0x400+sizeof(BITMAPINFOHEADER));//256 * 4 + sizeof(BITMAPINFOHEADER)
	if(Bmp256CPalMem==NULL)
		{
		GlobalFree(Bmp256CMem);
		return 0;
		}
	return 1;
}
static	void	FreeAllMemory(void)
{	//Free all memory when complete.
	GlobalFree(Bmp256CMem);
	GlobalFree(Bmp256CPalMem);
	GlobalFree(FilehMem);
}
LPRGBQUAD	PalPtr;
int	PalCount=0;
int	Default=6;
/***************************\
int	SearchLong(BYTE R,BYTE G,BYTE B)
{
	int	i;
	int	Long=256;
	int	Length;
	int	Pal=0;
	int	r,g,b;

	for(i=0;i<PalCount;i++)
		{//Search The short disance
		b=PalPtr[i].rgbBlue-R;
		g=PalPtr[i].rgbGreen-G;
		r=PalPtr[i].rgbRed-B;
		Length=abs(r)+abs(g)+abs(b);
		if(Length<Long)
			{
			Long=Length;
			Pal=i;	//Remember the short Palette
			}
		}
	if(Long>Default && PalCount<256)//New a Palette
		{
		PalPtr[PalCount].rgbReserved	=0;
		PalPtr[PalCount].rgbBlue	=B;
		PalPtr[PalCount].rgbGreen	=G;
		PalPtr[PalCount].rgbRed		=R;
		Pal=PalCount;
		PalCount++;
		}
	return Pal;
}
\***********************************/
static	int	SearchLong(void)
{	//DX:AX=RGB
	int	i;
	int	Long=256;
	int	Length;
	int	Pal=0;
	DWORD	RGB;
	DWORD	rgb;
	DWORD far *	Ptr;

	asm	xor	dh,dh
	asm	mov 	word ptr RGB,ax	//remember RGB
	asm	mov	word ptr RGB+2,dx
	Ptr=(DWORD far *)PalPtr;
	for(i=0;i<PalCount;i++)
		{//Search The short disance
		rgb=*Ptr++;
		asm	mov  	ax,word ptr rgb
		asm	mov	dx,word ptr rgb+2
		asm	sub	al,byte ptr RGB
		asm	sub	ah,byte ptr RGB+1
		asm	sub	dl,byte ptr RGB+2
		if(_AL>=0x3F) asm 	neg	al;
		if(_AH>=0x3F) asm	neg	ah;
		if(_DL>=0x3F) asm	neg	dl;
		asm	add	al,ah
		asm	mov	ah,dh
		asm	add	ax,dx
		if(_AX<Long)
			{
			if(_AX<=Default) return i;
			Long=_AX;
			Pal=i;	//Remember the short Palette
			}
		}
	if(Long>Default && PalCount<256)//New a Palette
		{
		*Ptr=RGB;
		Pal=PalCount;
		PalCount++;
		}
	return Pal;
}
static	void	PaletteNormal(void)
{
	int	i;
	for(i=0;i<256;i++)
		{
		PalPtr[i].rgbBlue 	*=4;
		PalPtr[i].rgbGreen	*=4;
		PalPtr[i].rgbRed 	*=4;
		}
}
static	void	PaletteChange(char R,char G,char B)
{
	int	i;
	PalPtr=(LPRGBQUAD)(GlobalLock(Bmp256CPalMem)+sizeof(BITMAPINFOHEADER));
	for(i=0;i<256;i++)
		{
		PalPtr[i].rgbBlue +=B;
		PalPtr[i].rgbGreen+=G;
		PalPtr[i].rgbRed  +=R;
		}
	GlobalUnlock(Bmp256CPalMem);
}
BYTE far * 	IndexPtr;
static	void	TranslateTo256Colors(void)
{
	int	i,j;
	int	Pal;
	BYTE	R,G,B;
	DWORD	IndexOffset=0;
	DWORD	RGBOffset=0;
	HCURSOR	hWaitCursor,hOldCursor;

	hWaitCursor=LoadCursor(NULL,IDC_WAIT);
	hOldCursor=SetCursor(hWaitCursor);
	PalPtr=(LPRGBQUAD)(GlobalLock(Bmp256CPalMem)+sizeof(BITMAPINFOHEADER));
	IndexPtr=GlobalLock(Bmp256CMem);
	FilehMemPtr=GlobalLock(FilehMem);
	for(i=0;i<VCDHigh;i++)
		for(j=0;j<352;j++)
			{
			_ES=FilehMem;	//RGB memory
			_EBX=RGBOffset;
			__emit__(0x26,0x67,0x8B,0x03);//asm ax,es:[ebx]
			__emit__(0x26,0x67,0x8A,0x53,0x02);//asm dl,es:[ebx+2]
			asm	shr	al,2	//B
			asm	shr	ah,2	//G
			asm	shr	dl,2	//R
			Pal=SearchLong();//RGB is 64 level,It is 6:6:6
			_ES=Bmp256CMem;	//Index memory
			_EBX=IndexOffset;
			_AL=Pal;
			__emit__(0x26,0x67,0x88,0x03);//asm mov es:[ebx],al
			RGBOffset+=3;
			IndexOffset++;
			}
	PaletteNormal();
	GlobalUnlock(Bmp256CPalMem);
	GlobalUnlock(Bmp256CMem);
	GlobalUnlock(FilehMem);
	SetCursor(hOldCursor);
}
static	HPALETTE	CreateCapturePalette(void)
{
	HPALETTE	CapturehPal;	//The 256 Color Capture hPalette
	LOGPALETTE FAR* lpPal;

	lpPal=(LOGPALETTE FAR*)(GlobalLock(Bmp256CPalMem)+sizeof(BITMAPINFOHEADER)-4);
	lpPal->palNumEntries 	= 256;
	lpPal->palVersion 	= 0x300;
	CapturehPal=CreatePalette(lpPal);
	GlobalUnlock(Bmp256CPalMem);
	return	CapturehPal;
}
static	void	CreateBitmapInfoHeader(void)
{
	BITMAPINFOHEADER far *	BmpInfoPtr;

	BmpInfoPtr=(BITMAPINFOHEADER far *)GlobalLock(Bmp256CPalMem);
	BmpInfoPtr->biSize		=sizeof(BITMAPINFOHEADER);
	BmpInfoPtr->biWidth		=352;
	BmpInfoPtr->biHeight		=VCDHigh;
	BmpInfoPtr->biPlanes		=1;
	BmpInfoPtr->biBitCount		=8;
	BmpInfoPtr->biCompression	=0;
	BmpInfoPtr->biSizeImage		=352L*VCDHigh;
	BmpInfoPtr->biXPelsPerMeter	=0;
	BmpInfoPtr->biYPelsPerMeter	=0;
	BmpInfoPtr->biClrUsed		=256;
	BmpInfoPtr->biClrImportant	=256;
}
static	void	PASCAL	SavePalette(HFILE hFile)
{
	PalPtr=(LPRGBQUAD)(GlobalLock(Bmp256CPalMem)+sizeof(BITMAPINFOHEADER));
	_lwrite(hFile,PalPtr,0x400);
	GlobalUnlock(Bmp256CPalMem);
}
static	void	PASCAL	SaveImage256(HFILE hFile)
{
	IndexPtr=GlobalLock(Bmp256CMem);
	_hwrite(hFile,IndexPtr,352L*VCDHigh);
	GlobalUnlock(Bmp256CMem);
}
////////////////////// PCX ///////////////////////
typedef struct PCXHEADERtag
	{
	BYTE 	ManuFacturer;	// 0A
	BYTE 	Version;
	BYTE 	Encoding;   	// 1
	BYTE 	Bits;
	WORD	XMin,YMin;
	WORD	XMax,YMax;
	WORD	Width;
	WORD	High;
	BYTE	Palette[16][3];	// 16 Colors
	BYTE	Reserved;
	BYTE	Planes;
	WORD	BytesOfLine;
	WORD	PaletteType;
	BYTE	Filler[58];
	} PCXHEADER;		// 128 Bytes
PCXHEADER	PCXHeader=
	{
	10,
	5,
	1,
	8,
	0,0,
	351,239,	//XMax,YMax
	640,480,	//Width,High
	{
	{0x00,0x00,0x00},{0x10,0x10,0x10},{0x20,0x20,0x20},{0x30,0x30,0x30},
	{0x40,0x40,0x40},{0x50,0x50,0x50},{0x60,0x60,0x60},{0x70,0x70,0x70},
	{0x80,0x80,0x80},{0x90,0x90,0x90},{0xA0,0xA0,0xA0},{0xB0,0xB0,0xB0},
	{0xC0,0xC0,0xC0},{0xD0,0xD0,0xD0},{0xE0,0xE0,0xE0},{0xF0,0xF0,0xF0}
	},
	0,
	1,
	352,
	1,
	0
	};
static	void	WritePCXHeader(HFILE hFile)
{
	PCXHeader.High=VCDHigh;
	PCXHeader.YMax=VCDHigh-1;
	_lwrite(hFile,&PCXHeader,sizeof(PCXHeader));
}
DWORD	PCXSize=0;
static	void	WriteToMemory(BYTE Pixel)
{
	_ES=FilehMem;
	_EBX=PCXSize;
	asm	mov	al,Pixel
	__emit__(0x26,0x67,0x88,0x03);//asm es:[ebx],al
	PCXSize++;
}
static	void	SavePCXImage256(HFILE hFile)
{
	BYTE	Pixel,OldPixel,Count;
	int	i,j;
	DWORD	Offset;

	PCXSize=0;
	IndexPtr=GlobalLock(Bmp256CMem);
	FilehMemPtr=GlobalLock(FilehMem);
	for(j=0;j<VCDHigh;j++)
		{
		Offset=352L*(VCDHigh-j-1);
		Count=0;
		for(i=0;i<352;i++)
			{
			_ES=Bmp256CMem;
			_EBX=Offset;
			__emit__(0x26,0x67,0x8A,0x03);//asm mov	al,es:[ebx]
			Pixel=_AL;
			if(i==0){
				OldPixel=Pixel;
				Count++;
				}
			else	{
				if(OldPixel!=Pixel || Count>=0x3F)
					{
					if(Count==1)
						{
						if((OldPixel&0xC0)==0xC0)
							{//the Pixel >=0xC0
							Count=0xC1;
							WriteToMemory(Count);
							WriteToMemory(OldPixel);
							}
						else	{
							WriteToMemory(OldPixel);
							}
						}
					else	{//Count != 0
						Count|=0xC0;
						WriteToMemory(Count);
						WriteToMemory(OldPixel);
						}
					OldPixel=Pixel;
					Count=0;
					}
				Count++;
				}
			Offset++;
			}
		if(Count>1)//Save left
			{
			Count|=0xC0;
			WriteToMemory(Count);
			WriteToMemory(OldPixel);
			}
		else	{
			if(Count==1)
				{
				if((OldPixel&0xC0)==0xC0)
					{//the Pixel >=0xC0
					Count=0xC1;
					WriteToMemory(Count);
					WriteToMemory(OldPixel);
					}
				else	{
					WriteToMemory(OldPixel);
					}
				}
			}
		}
	GlobalUnlock(Bmp256CMem);
	_hwrite(hFile,FilehMemPtr,PCXSize);
	GlobalUnlock(FilehMem);
}
static	void	SavePCXPalette(HFILE hFile)
{
	int		i;
	BYTE far *	Ptr;

	PalPtr=(LPRGBQUAD)(GlobalLock(Bmp256CPalMem)+sizeof(BITMAPINFOHEADER));
	Ptr=FilehMemPtr=GlobalLock(FilehMem);
	*Ptr++=0x0C;
	for(i=0;i<256;i++)
		{
		*Ptr++=PalPtr[i].rgbRed;
		*Ptr++=PalPtr[i].rgbGreen;
		*Ptr++=PalPtr[i].rgbBlue;
		}
	_lwrite(hFile,FilehMemPtr,769);
	GlobalUnlock(Bmp256CPalMem);
	GlobalUnlock(FilehMem);
}
DWORD	huge	PASCAL	Modify256ColorProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
static	void	BuildFile(HFILE hFile,int Index)
{
	PictureType=Index;
	switch(Index)
		{
		case 1:	Write24BitBMPHeader(hFile);//Write the bmp file header
			Decode24BitsToFile(hFile);	//Decode the Picture to file
			break;
		case 2: //Double Size 24 bit bitmap
			WriteD24BitBMPHeader(hFile);//Write the bmp file header
			DecodeD24BitsToFile(hFile);	//Decode the Picture to file
			break;
		case 3:	Write8BitBMPHeader(hFile);//Write the bmp file header
			Decode8BitsGrayScaleToFile(hFile);//Decode the Picture to file
			break;
		case 4: Write8BitBMPHeader(hFile);//256 Color BMP header
			Decode24BitsToMemory();//Decode to 24 bit ture colors
			Allocate256ColorMemory();
			///////////// To 256 Colors //////////////
			PalCount=0;Default=6;
			TranslateTo256Colors();//Decode to 256 Colors
			if(Chinese) DialogBox(hInst,"Modify256CC",NULL,(DLGPROC)Modify256ColorProc);
			else DialogBox(hInst,"Modify256C",NULL,(DLGPROC)Modify256ColorProc);
			//////////////////////////////////////////
			SavePalette(hFile);
			SaveImage256(hFile);
			FreeAllMemory();
			break;
		case 5: WritePCXHeader(hFile);
			Decode24BitsToMemory();//Decode to 24 bit ture colors
			Allocate256ColorMemory();
			///////////// To 256 Colors //////////////
			PalCount=0;Default=6;
			TranslateTo256Colors();//Decode to 256 Colors
			if(Chinese)	DialogBox(hInst,"Modify256CC",NULL,(DLGPROC)Modify256ColorProc);
			else	DialogBox(hInst,"Modify256C",NULL,(DLGPROC)Modify256ColorProc);
			//////////////////////////////////////////
			SavePCXImage256(hFile);
			SavePCXPalette(hFile);
			FreeAllMemory();
			break;
		}
}
extern	char	Buffer[80];
static	void	GetDirPath(void)
{
	int	Ret;
	char	tmpBuffer[128];

	GetCWD(Buffer,sizeof(Buffer));
	lstrcpy(tmpBuffer,Buffer);
	lstrcat(tmpBuffer,"\\STHMPEG.INI");
	Ret=GetPrivateProfileString("SthAV","SavePicturePath","",DirName,sizeof(DirName),tmpBuffer);
	if(Ret==0)//Read from INI file.
		{
		GetCWD(DirName,sizeof(DirName));
		}
}
static	void	SavePath(void)
{
	GetCWD(DirName,sizeof(DirName));
	GoHome();		//Change to Locate Dir.
	lstrcat(Buffer,"\\STHMPEG.INI");	//The Buffer got prev
	WritePrivateProfileString("SthAV","SavePicturePath",DirName,Buffer);
}
static	void	PASCAL	SaveVideoPicture(void)
{
	lstrcpy(FileName,DefaultBmpName);
	///////////////////////////////////////
	GetDirPath();
	///////////////////////////////////////
	ofn.lStructSize	 	= sizeof(OPENFILENAME);
	ofn.hwndOwner 		= AudioMainWindow;
	ofn.lpstrFilter 	= Filter;
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= FileName;
	ofn.nMaxFile 		= sizeof(FileName);
	ofn.lpstrInitialDir 	= DirName;
	ofn.lpstrTitle		= BmpTitle;
	ofn.lpstrFileTitle 	= FileTitle;
	ofn.nMaxFileTitle 	= sizeof(FileTitle);
	ofn.lpstrCustomFilter 	= NULL;
	ofn.nMaxCustFilter 	= 0L;
	ofn.nFileOffset 	= 0;
	ofn.nFileExtension 	= 0;
	ofn.lpstrDefExt 	= NULL;
	ofn.lCustData 		= 0L;
	ofn.lpfnHook 		= NULL;
	ofn.lpTemplateName 	= NULL;
	ofn.Flags 		= OFN_OVERWRITEPROMPT //| OFN_SHOWHELP
				| OFN_HIDEREADONLY | OFN_PATHMUSTEXIST;;
	if(GetSaveFileName(&ofn))
		{
		// Perform file operations. Decode Video to BMP File.
		HFILE	hFile;
		hFile=_lcreat(FileName,0);
		if(hFile==HFILE_ERROR)
			{
			MessageBox(NULL,"Create File Error !","ERROR",MB_ICONSTOP);
			return;
			}
		BuildFile(hFile,ofn.nFilterIndex);
		_lclose(hFile);
		}
	SavePath();
}
///////////////////////////////////////////////////////////////
extern	int	Playing;
extern	int	DisplayPreView;
extern	HWND 	ShowVideo;
int	Caputuring=0;
void	PASCAL FAR	CapturePicture(void)	//API
{
	int	CurPlayState;
	MSG	msg;

	if(Caputuring)	return;
	Caputuring=1;
	CurPlayState=Playing;
	DisplayPreView=0;
	//////////////if playing stop it ///////////
	if(Playing)
		{//Stop playing
		SendMessage(MainWindow,WM_KEYDOWN,VK_SPACE,0L);
		SendMessage(MainWindow,WM_KEYUP,VK_SPACE,0L);
		}
	////////// Wait when not playing.
	while(Playing)
		{//Wait Stop playing.
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			}
		}
	/////////////// Dialog Box input file name ////////////
	SaveVideoPicture();
	//////////////if stop playing restart it //////////////
	if(CurPlayState)
		{//Restart playing
		SendMessage(MainWindow,WM_KEYDOWN,VK_SPACE,0L);
		SendMessage(MainWindow,WM_KEYUP,VK_SPACE,0L);
		}
	Caputuring=0;	//End Capture Video
	DisplayPreView=1;
	if(CurPlayState==0)//On stop state repaint the preview.
		InvalidateRect(ShowVideo,NULL,TRUE);//Update the preview area
}
//////////////////////// Dialog Box Proc ///////////////////
static	void	DisplayThePicture(HDC hdc)
{
	HPALETTE	CapturehPal;	//The 256 Color Capture hPalette
	HPALETTE	hOldPal;
	BITMAPINFOHEADER far *	BmpInfoPtr;

	CapturehPal=CreateCapturePalette();//Create Palette
	CreateBitmapInfoHeader();//Create Bitmap info
	IndexPtr=GlobalLock(Bmp256CMem);
	BmpInfoPtr=(BITMAPINFOHEADER far *)GlobalLock(Bmp256CPalMem);
	hOldPal=SelectPalette(hdc,CapturehPal,FALSE);
	RealizePalette(hdc);
	SetDIBitsToDevice(hdc,0,0,352,VCDHigh,0,0,0,VCDHigh,IndexPtr,
				(BITMAPINFO FAR*)BmpInfoPtr,DIB_RGB_COLORS);
	SelectPalette(hdc,hOldPal,FALSE);
	GlobalUnlock(Bmp256CMem);
	GlobalUnlock(Bmp256CPalMem);
	DeleteObject(CapturehPal);
}
#pragma	warn -par
DWORD	huge	PASCAL	Modify256ColorProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{
	PAINTSTRUCT 	ps;
	HDC		hdc;
	char		Buffer[16];

	switch(message)
		{
		case 	WM_INITDIALOG:
			return TRUE;
		case	WM_PAINT:
			hdc=BeginPaint(hwnd,&ps);
			DisplayThePicture(hdc);
			EndPaint(hwnd,&ps);
			break;
		case	WM_COMMAND:
			switch(wParam)
				{
				case 1://OK
				EndDialog(hwnd,wParam);
				return TRUE;
				// R
				case 100://--
				case 101://++
					if(wParam==100) PaletteChange(-4,0,0);
					else PaletteChange(4,0,0);
					hdc=GetDC(hwnd);
					DisplayThePicture(hdc);
					ReleaseDC(hwnd,hdc);
					break;
				// G
				case 102://--
				case 103://++
					if(wParam==102) PaletteChange(0,-4,0);
					else PaletteChange(0,4,0);
					hdc=GetDC(hwnd);
					DisplayThePicture(hdc);
					ReleaseDC(hwnd,hdc);
					break;
				// B
				case 104://--
				case 105://++
					if(wParam==104) PaletteChange(0,0,-4);
					else PaletteChange(0,0,4);
					hdc=GetDC(hwnd);
					DisplayThePicture(hdc);
					ReleaseDC(hwnd,hdc);
					break;
				// Level
				case 106:Default-=2;	//--
				case 107:Default++;	//++
					if(Default<0)
						{
						Default=0;
						break;
						}
					if(Default>99)
						{
						Default=99;
						break;
						}
					PalCount=0;
					wsprintf(Buffer,"%d",Default);
					SetDlgItemText(hwnd,200,Buffer);
					TranslateTo256Colors();
					hdc=GetDC(hwnd);
					DisplayThePicture(hdc);
					ReleaseDC(hwnd,hdc);
					break;
				}
			break;
		case	WM_CLOSE:
			EndDialog(hwnd,wParam);
			return TRUE;
		}
	return FALSE;
}
#pragma	warn .par
