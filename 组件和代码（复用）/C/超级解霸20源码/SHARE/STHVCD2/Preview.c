////////////////////////////////////////////////////////
//		PreView picture handle
//	      Decode a stamp just 64 X 56
//	   And Display it in Preview position
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include "DOS.H"
#include "VCDAPI.H"

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

extern	int	Pixels;
extern	int	Line;
extern	HGLOBAL	OffScrSel;
extern	int	DeleteLine;
extern	int	Start;
BITMAPINFO	BitmapInfo=
{
	{
	sizeof(BITMAPINFOHEADER),
	64,
	56,
	1,
	24,
	BI_RGB,
	0,
	0,//	biXPelsPerMeter;
	0,//	biYPelsPerMeter;
	0,
	0
	},
	0
};
BYTE	far	PreViewBuffer[56][64][3];	//64*56*4 RGB 24
static	DWORD	PASCAL	PreviewComputRGB(void)
{
	int	Y,Cb,Cr,Cg;
	int	R,G,B;
	DWORD	RGB;
	__emit__(0x65,0x67,0x8A,0x07);//mov al,gs:[edi] Y
	__emit__(0x65,0x67,0x8A,0x1E);//mov bl,gs:[esi] U
	__emit__(0x65,0x67,0x8A,0x96,0x40,0x02,0x00,0x00);//mov dl,gs:[esi+0x240] V
	Y=_AL;
	Cb=_BL;
	Cr=_DL;
	Cb-=128;
	Cr-=128;
	Cg=Cr/2;
	R=Y+Cr;
	G=Y-Cg;
	B=Y+Cb;
	if(R>255) R=255;
	if(G>255) G=255;
	if(B>255) B=255;
	if(R<0) R=0;
	if(G<0) G=0;
	if(B<0) B=0;
	*((BYTE *)&RGB)=R;
	*((BYTE *)&RGB+1)=G;
	*((BYTE *)&RGB+2)=B;
	*((BYTE *)&RGB+3)=0;
	return	RGB;
}
extern	HWND	MainWindow;	//Main Windows
static	void	PASCAL	PreView24BitPicture(void)
{	//Preview little picture
	int	i,line,Count;
	int	UVLine;
	HDC	hdc;
	LPVIDEODATA	VideoDataPtr;
	BYTE 	far *	Ptr;

	if(Start)	return;	//Had off screen not draw the preview picture
	if(OffScrSel==NULL) return;
	VideoDataPtr=MK_FP(OffScrSel,0);
	if(VideoDataPtr->SelfFlags!=0x21485453) return;
	_AX=VideoDataPtr->Selector;
	__emit__(0x8E,0xE8);//mov gs,ax
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		UVLine=Count=0;
		for(line=0;line<56;line++)
			{
			Count++;
			for(i=0;i<16;i++)
				{
				Ptr=&PreViewBuffer[55-line][i*4][0];
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=6;
				VideoDataPtr->UPlane+=3;
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=5;
				VideoDataPtr->UPlane+=2;
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=6;
				VideoDataPtr->UPlane+=3;
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=5;
				VideoDataPtr->UPlane+=3;
				}
			VideoDataPtr->YPlane+=800;
			if(Count<3)
				{
				VideoDataPtr->YPlane+=4*0x480;
				UVLine+=4;
				}
			else	{
				VideoDataPtr->YPlane+=3*0x480;
				UVLine+=3;
				if(Count>=7) Count=0;
				}
			UVLine++;
			VideoDataPtr->UPlane=VideoDataPtr->VPlane+(UVLine/2)*0x480L;
			}
		}
	else	{
		/////////////352x288/////////////
		UVLine=Count=0;
		for(line=0;line<56;line++)
			{
			Count++;
			for(i=0;i<16;i++)
				{
				Ptr=&PreViewBuffer[55-line][i*4][0];
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=6;
				VideoDataPtr->UPlane+=3;
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=5;
				VideoDataPtr->UPlane+=2;
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=6;
				VideoDataPtr->UPlane+=3;
				_EDI=VideoDataPtr->YPlane;
				_ESI=VideoDataPtr->UPlane;
				PreviewComputRGB();
				*(short far *)Ptr=_AX;Ptr+=2;
				*Ptr++=_DL;
				VideoDataPtr->YPlane+=5;
				VideoDataPtr->UPlane+=3;
				}
			VideoDataPtr->YPlane+=800;
			if(Count<7)
				{
				VideoDataPtr->YPlane+=4*0x480;
				UVLine+=4;
				}
			else	{
				VideoDataPtr->YPlane+=5*0x480;
				UVLine+=5;
				Count=0;
				}
			UVLine++;
			VideoDataPtr->UPlane=VideoDataPtr->VPlane+(UVLine/2)*0x480L;
			}
		}
	///////////// Display this sample ///////////
	hdc=GetDC(MainWindow);
	SetDIBitsToDevice(hdc,47,24,64,56,0,0,0,56,&PreViewBuffer[0][0][0],&BitmapInfo,DIB_RGB_COLORS);
	ReleaseDC(MainWindow,hdc);
}
static	void	PASCAL	PreView24BitReDraw(void)
{
	HDC	hdc;
	LPVIDEODATA	VideoDataPtr;

	if(Start)	return;	//Had off screen not draw the preview picture
	if(OffScrSel==NULL) return;
	VideoDataPtr=MK_FP(OffScrSel,0);
	if(VideoDataPtr->SelfFlags!=0x21485453) return;
	hdc=GetDC(MainWindow);
	SetDIBitsToDevice(hdc,47,24,64,56,0,0,0,56,&PreViewBuffer[0][0][0],&BitmapInfo,DIB_RGB_COLORS);
	ReleaseDC(MainWindow,hdc);
}
///////////////////// Gray Preview picture /////////////////
typedef struct BMPINFOtag
	{
	BITMAPINFOHEADER    BmpInfoHeader;
	RGBQUAD             DAC[256];
	} BMPINFO;
BMPINFO	far *	BmpInfoPtr=NULL;
/*
BMPINFO	BmpInfo=
{
	{
	sizeof(BITMAPINFOHEADER),
	64,
	56,
	1,
	8,
	BI_RGB,
	64*56,
	0,//	biXPelsPerMeter;
	0,//	biYPelsPerMeter;
	256,
	256
	},
	0
};
*/
HPALETTE	PreviewhPal=0;
static	void	Build256CBmpInfo(void)
{
	BYTE far *	Ptr;
	int		i;

	Ptr=&PreViewBuffer[0][0][0];
	(BYTE far *)BmpInfoPtr=(Ptr+0xF00);
	///////////// Build Bmp header ////////////////
	BmpInfoPtr->BmpInfoHeader.biSize	=sizeof(BITMAPINFOHEADER);
	BmpInfoPtr->BmpInfoHeader.biWidth	=64;
	BmpInfoPtr->BmpInfoHeader.biHeight	=56;
	BmpInfoPtr->BmpInfoHeader.biPlanes	=1;
	BmpInfoPtr->BmpInfoHeader.biBitCount	=8;
	BmpInfoPtr->BmpInfoHeader.biCompression=BI_RGB;
	BmpInfoPtr->BmpInfoHeader.biSizeImage	=64*56;
	BmpInfoPtr->BmpInfoHeader.biXPelsPerMeter=0;
	BmpInfoPtr->BmpInfoHeader.biYPelsPerMeter=0;
	BmpInfoPtr->BmpInfoHeader.biClrUsed	=256;
	BmpInfoPtr->BmpInfoHeader.biClrImportant=256;
	///////////////// DAC Palette ////////////
	for(i=0;i<256;i++)
		{
		BmpInfoPtr->DAC[i].rgbRed	=i;
		BmpInfoPtr->DAC[i].rgbGreen	=i;
		BmpInfoPtr->DAC[i].rgbBlue	=i;
		BmpInfoPtr->DAC[i].rgbReserved	=0;
		}
}

static	void	CreatePreviewPalette(void)
{
	HGLOBAL		PalMem;
	LOGPALETTE FAR* lpPal;
	int		i;
	HDC		hdc;

	PalMem=GlobalAlloc(GMEM_MOVEABLE,sizeof(LOGPALETTE)+
		BmpInfoPtr->BmpInfoHeader.biClrUsed*sizeof(PALETTEENTRY));
	if(PalMem==NULL) return;
	lpPal=(LOGPALETTE FAR*)GlobalLock(PalMem);
	lpPal->palNumEntries 	= 256;
	lpPal->palVersion 	= 0x300;
	for(i=0;i<256;i++)
		{
		lpPal->palPalEntry[i].peRed	=i;
		lpPal->palPalEntry[i].peGreen	=i;
		lpPal->palPalEntry[i].peBlue	=i;
		lpPal->palPalEntry[i].peFlags	=0;
		}
	PreviewhPal=CreatePalette(lpPal);
	GlobalUnlock(PalMem);
	GlobalFree(PalMem);
}
/************************************\
void	PASCAL	PreviewGetYData(void)
{
	__emit__(0x65,0x67,0x8A,0x07);//mov al,gs:[edi]
}
\************************************/
#define	PreviewGetYData()	__emit__(0x65,0x67,0x8A,0x07)
static	void	PASCAL	PreViewGrayPicture(void)
{	//Preview little picture
	int	i,line,Count;
	HDC	hdc;
	LPVIDEODATA	VideoDataPtr;
	BYTE 	far *	VideoPtr;
	BYTE 	far *	Ptr;
	HPALETTE	hOldPal;

	if(Start)	return;	//Had off screen not draw the preview picture
	if(OffScrSel==NULL) return;
	VideoPtr=&PreViewBuffer[0][0][0];
	VideoDataPtr=MK_FP(OffScrSel,0);
	if(VideoDataPtr->SelfFlags!=0x21485453) return;
	_AX=VideoDataPtr->Selector;
	__emit__(0x8E,0xE8);//mov gs,ax
	if(DeleteLine==5)
		{
		/////////////352x240/////////////
		Count=0;
		for(line=0;line<56;line++)
			{
			Count++;
			Ptr=VideoPtr+(55-line)*64;
			for(i=0;i<16;i++)
				{
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=6;
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=5;
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=6;
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=5;
				}
			VideoDataPtr->YPlane+=800;
			if(Count<3)
				{
				VideoDataPtr->YPlane+=4*0x480;
				}
			else	{
				VideoDataPtr->YPlane+=3*0x480;
				if(Count>=7) Count=0;
				}
			}
		}
	else	{
		/////////////352x288/////////////
		Count=0;
		for(line=0;line<56;line++)
			{
			Count++;
			Ptr=VideoPtr+(55-line)*64;
			for(i=0;i<16;i++)
				{
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=6;
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=5;
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=6;
				_EDI=VideoDataPtr->YPlane;
				PreviewGetYData();
				*Ptr++=_AL;
				VideoDataPtr->YPlane+=5;
				}
			VideoDataPtr->YPlane+=800;
			if(Count<7)
				{
				VideoDataPtr->YPlane+=4*0x480;
				}
			else	{
				VideoDataPtr->YPlane+=5*0x480;
				Count=0;
				}
			}
		}
	///////////// Display this sample ///////////
	if(BmpInfoPtr==NULL) Build256CBmpInfo();
	hdc=GetDC(MainWindow);
	if(PreviewhPal==0) CreatePreviewPalette();
	if(PreviewhPal==0) PreView24BitPicture();	//Can create PAL use 24 Bit format
	hOldPal = SelectPalette (hdc,PreviewhPal,FALSE);
	RealizePalette(hdc);
	SetDIBitsToDevice(hdc,47,24,64,56,0,0,0,56,&PreViewBuffer[0][0][0],
				(BITMAPINFO FAR*)BmpInfoPtr,DIB_RGB_COLORS);
	SelectPalette (hdc,hOldPal,FALSE);
	ReleaseDC(MainWindow,hdc);
}
static	void	PASCAL	PreViewGrayReDraw(void)
{
	HDC	hdc;
	LPVIDEODATA	VideoDataPtr;
	HPALETTE	hOldPal;

	if(Start)	return;	//Had off screen not draw the preview picture
	if(OffScrSel==NULL) return;
	VideoDataPtr=MK_FP(OffScrSel,0);
	if(VideoDataPtr->SelfFlags!=0x21485453) return;
	if(BmpInfoPtr==NULL) Build256CBmpInfo();
	hdc=GetDC(MainWindow);
	if(PreviewhPal==0) CreatePreviewPalette();
	if(PreviewhPal==0) PreView24BitPicture();	//Can create PAL use 24 Bit format
	hOldPal = SelectPalette (hdc,PreviewhPal,FALSE);
	RealizePalette(hdc);
	SetDIBitsToDevice(hdc,47,24,64,56,0,0,0,56,&PreViewBuffer[0][0][0],
				(BITMAPINFO FAR*)BmpInfoPtr,DIB_RGB_COLORS);
	SelectPalette (hdc,hOldPal,FALSE);
	ReleaseDC(MainWindow,hdc);
}
///////////////////////////////////////
extern	int	WindowsColorBits;	//Windows now Color bits
void	PASCAL FAR	PreViewPicture(void)
{	//Preview little picture
	if(WindowsColorBits>8)	PreView24BitPicture();
	else	PreViewGrayPicture();
}
void	PASCAL FAR	PreViewReDraw(void)
{
	if(WindowsColorBits>8)	PreView24BitReDraw();
	else	PreViewGrayReDraw();
}
