////////////////////////////////////////////////////////
//	Search DCI support function on the System.
//		Primary or YUV->RGB
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include "DOS.H"
#include "DCI.H"
#include "VCDAPI.H"

extern	int	DCIType;	//If now be 640x480 and had DCI Primary 64K/32K
extern	DWORD	lStride;	//Video Memory Line width.
extern	DWORD	LinearOffSurface;
extern	DWORD	LinearSelSurface;
DWORD		DCISupportFOURCC=0;
DWORD		DCIYUVFormat=0;
DCIENUMINPUT	DCIEnumInput;
DCISURFACEINFO	DCISurFace;
DCIOFFSCREEN	DCISurfaceScreen;	//Offscreen or primary
DCICREATEINPUT	DCISurfaceCreate;	//Create input
int		BeEnumCall=0;
static	void	PASCAL 	MemCpy(void far *Dest,void far *Source,WORD Size)
{
	_DI=_DI;
	_SI=_SI;
	asm	push	ds
	asm	cld
	asm	lds	si,dword ptr Source
	asm	les	di,dword ptr Dest
	asm	mov	cx,Size
	asm	shr	cx,1
	asm	rep	movsw
	asm	adc	cl,cl
	asm	rep	movsb
	asm	pop	ds
}
#pragma	warn -par
int PASCAL _huge EnumCallback(LPDCISURFACEINFO lpSurface,LPVOID lpContext)
{//Must load DS
	int	Number1,Number2;
	BeEnumCall=1;
	DCISupportFOURCC=lpSurface->dwCompression;
	if(DCISurFace.dwDCICaps!=0)
		{
		Number1=10;
		Number2=10;
		if(DCISurFace.dwCompression==0x32315659) Number1=0;//'YV12' first
		if(DCISurFace.dwCompression==0x32595559) Number1=1;//'YUY2' 2nd
		if(DCISurFace.dwCompression==0x55595659) Number1=2;//'YVYU' 3th
		if(DCISurFace.dwCompression==0x59565955) Number1=3;//'UYVY' 4th
		if(DCISurFace.dwCompression==0x39304649) Number1=4;//'IF09' 3th
		if(DCISurFace.dwCompression==0x39555659) Number1=5;//'YVU9' 4th
		if(DCISupportFOURCC==0x32315659) Number2=0;//'YV12' first
		if(DCISupportFOURCC==0x32595559) Number2=1;//'YUY2' 2nd
		if(DCISupportFOURCC==0x55595659) Number2=2;//'YVYU' 3th
		if(DCISupportFOURCC==0x59565955) Number2=3;//'UYVY' 4th
		if(DCISupportFOURCC==0x39304649) Number2=4;//'IF09' 3th
		if(DCISupportFOURCC==0x39555659) Number2=5;//'YVU9' 4th
		if(DCISupportFOURCC==0) return 0;// RGB had remember.
		if(Number2>=Number1) 	return 0;
		// Only this 4 formats support,but YV12 first.
		}
	DCISurFace.dwDCICaps	=lpSurface->dwDCICaps;
	DCISurFace.dwCompression=lpSurface->dwCompression;
	DCISurFace.dwMask[0]	=lpSurface->dwMask[0];
	DCISurFace.dwMask[1]	=lpSurface->dwMask[1];
	DCISurFace.dwMask[2]	=lpSurface->dwMask[2];
	DCISurFace.dwWidth	=lpSurface->dwWidth;
	DCISurFace.dwHeight	=lpSurface->dwHeight;
	DCISurFace.lStride	=lpSurface->lStride;
	DCISurFace.dwBitCount	=lpSurface->dwBitCount;
	return 0;
}
#pragma	warn .par
LPDCIOFFSCREEN		DCISurfaceScreenPtr;
HDC  	FAR PASCAL	(*DCIOpenProvider)(void);
void  	FAR PASCAL	(*DCICloseProvider)(HDC);
int     FAR PASCAL	(*DCICreatePrimary)(HDC,LPDCISURFACEINFO FAR*);
int     FAR PASCAL	(*DCICreateOffscreen)(HDC,DWORD,DWORD,DWORD,DWORD,
		DWORD,DWORD,DWORD,DWORD,LPDCISURFACEINFO FAR*);
int	FAR PASCAL	(*DCIEnum)(HDC,LPRECT,LPRECT,LPVOID,LPVOID);
extern	HINSTANCE	AcceleratorInst;
HDC	DCIhdc=0;
RECT	DCISrcRect;
RECT	DCIDstRect;
static	int	SearchDCIYUVSupportFunction(HWND hwnd)
{
	int	Ret;
	//////// Get DCI Call Address /////////
	if(AcceleratorInst==NULL) return 0;
	(FARPROC)DCIOpenProvider=GetProcAddress(AcceleratorInst,MAKELP(0,1));
	(FARPROC)DCICloseProvider=GetProcAddress(AcceleratorInst,MAKELP(0,2));
	(FARPROC)DCICreatePrimary=GetProcAddress(AcceleratorInst,MAKELP(0,3));
	(FARPROC)DCICreateOffscreen=GetProcAddress(AcceleratorInst,MAKELP(0,4));
	(FARPROC)DCIEnum=GetProcAddress(AcceleratorInst,MAKELP(0,6));
	///////////////////////////////////////
	DCIhdc=(*DCIOpenProvider)();
	if(DCIhdc==NULL)	return 0;
	//////////// DCI Support //////////////
	GetWindowRect(hwnd,&DCIDstRect);
	DCISrcRect.top=DCISrcRect.left=0;
	DCISrcRect.bottom=288;DCISrcRect.right=352;
	Ret=(*DCIEnum)(DCIhdc,&DCIDstRect,&DCISrcRect,EnumCallback,&DCIhdc);
	if(Ret!=0)
		{
		(*DCICloseProvider)(DCIhdc);
		DCIhdc=0;
		return 0;
		}
	//////////////////////////////////////
	if((DCISurFace.dwCompression&0xFFFF0000)!=0)	//YUV support
		{////////// Create YUV -> RGB \\\\\\\\\
		Ret=(*DCICreateOffscreen)(DCIhdc,DCISurFace.dwCompression,
			DCISurFace.dwMask[0],DCISurFace.dwMask[0],
			DCISurFace.dwMask[0],DCISurFace.dwWidth,
			DCISurFace.dwHeight,DCISurFace.dwDCICaps,
			DCISurFace.dwBitCount,
			(LPDCISURFACEINFO FAR*)&DCISurfaceScreenPtr);
		if(Ret!=0)
			{
			(*DCICloseProvider)(DCIhdc);
			DCIhdc=0;
			return 0;
			}
		MemCpy(&DCISurfaceScreen,DCISurfaceScreenPtr,DCISurfaceScreenPtr->dciInfo.dwSize);
		// Offscreen YUV->RGB support
		DCIType=2;
		LinearOffSurface=DCISurfaceScreen.dciInfo.dwOffSurface;
		LinearSelSurface=DCISurfaceScreen.dciInfo.dwSelSurface;
		DCIYUVFormat=DCISurfaceScreen.dciInfo.dwCompression;
		}
	else	{
		Ret=(*DCICreatePrimary)(DCIhdc,(LPDCISURFACEINFO FAR*)&DCISurfaceScreenPtr);
		if(Ret!=0)
			{
			(*DCICloseProvider)(DCIhdc);
			DCIhdc=0;
			return 0;
			}
		////// DCI Primary support ////////////
		MemCpy(&DCISurfaceScreen,DCISurfaceScreenPtr,DCISurfaceScreenPtr->dciInfo.dwSize);
		// Primary support
		DCIType=1;
		lStride=DCISurfaceScreen.dciInfo.lStride-1280;	//640x2
		LinearOffSurface=DCISurfaceScreen.dciInfo.dwOffSurface;
		LinearSelSurface=DCISurfaceScreen.dciInfo.dwSelSurface;
		}
	return 1;
}
static	int	CreatePrimary(void)
{
	int	Ret;
	//////// Get DCI Call Address /////////
	if(AcceleratorInst==NULL) return 0;
	(FARPROC)DCICreatePrimary=GetProcAddress(AcceleratorInst,MAKELP(0,3));
	///////////////////////////////////////
	Ret=(*DCICreatePrimary)(DCIhdc,(LPDCISURFACEINFO FAR*)&DCISurfaceScreenPtr);
	return	Ret;
}
HDC	Context=0;
int	YUVSupport=0;
int	PASCAL FAR	SearchDCISupportFunction(void)
{
	int	Ret;
	int	DCISupport;
	int	DCIFunc=0x0C03;
	int	ScreenMode;
	int	X,Y;
	HWND	hwnd;
	char	DCIDeviceName[128];

	Ret=GetPrivateProfileString("drivers","DCI","",DCIDeviceName,sizeof(DCIDeviceName),"system.ini");
	if(Ret==0)	return 0;
	DCIhdc=CreateDC(DCIDeviceName,NULL,NULL,NULL);
	if(DCIhdc==NULL) return 0;
	/////////// Search Driver support DCI ///////////
	DCISupport=Escape(DCIhdc,QUERYESCSUPPORT,sizeof(DCIFunc),(LPCSTR)&DCIFunc,NULL);
	if(DCISupport!=1)
		{//DCI function not support
		DeleteDC(DCIhdc);
		DCIhdc=0;
		return 0;
		}
	BeEnumCall=0;
	//////////// DCI Enum surface //////////////
	DCIEnumInput.dcicmd.dwCommand	=4;
	DCIEnumInput.dcicmd.dwVersion	=0x100;
	DCIEnumInput.rSrc.left		=0;
	DCIEnumInput.rSrc.top		=0;
	DCIEnumInput.rSrc.right		=352;
	DCIEnumInput.rSrc.bottom	=288;
	DCIEnumInput.rDest.left		=0;
	DCIEnumInput.rDest.top		=0;
	DCIEnumInput.rDest.right	=640;
	DCIEnumInput.rDest.bottom	=480;
	DCIEnumInput.EnumCallback	=(void CALLBACK *)EnumCallback;//PASCAL call
	DCIEnumInput.lpContext		=&Context;
	DCISupport=Escape(DCIhdc,DCIFunc,sizeof(DCIEnumInput),(LPCSTR)&DCIEnumInput,NULL);
	if(BeEnumCall==0 || DCISupport!=0)
		{//Offscreen create false.
		//DCI Support but not support Enum maybe support primary surface
		goto	TryCreatePrimary;
		}
	////////////////Which Surface be supported/////////////////
	if((DCISurFace.dwCompression&0xFFFF0000)!=0)	//YUV support
		{////////// Create YUV -> RGB \\\\\\\\\
		DeleteDC(DCIhdc);	//Release This DC
		hwnd=GetDesktopWindow();	//Full screen.
		Ret=SearchDCIYUVSupportFunction(hwnd);
		if(Ret==1)
			{// Success create YUV DCI.
			YUVSupport=1;
			return 1;
			}
		DCIhdc=CreateDC(DCIDeviceName,NULL,NULL,NULL);
		if(DCIhdc==NULL) return 0;	//YUV DCI False.
		goto	TryCreatePrimary;	//Try to create primary.
		}
	else	{//Primary surface only
		HDC	hdc;
		TryCreatePrimary:
		hwnd=GetDesktopWindow();
		hdc=GetDC(hwnd);
		ScreenMode=GetDeviceCaps(hdc,BITSPIXEL);
		ReleaseDC(hwnd,hdc);
		if(ScreenMode!=16 && ScreenMode!=15)
			{
			DeleteDC(DCIhdc);
			DCIhdc=0;
			return 0;
			}
		X=GetSystemMetrics(SM_CXSCREEN);
		Y=GetSystemMetrics(SM_CYSCREEN);
		if(X!=640 && Y!=480)
			{
			DeleteDC(DCIhdc);
			DCIhdc=0;
			return 0;
			}
		///////////// Create primary \\\\\\\\\\\\
		DCISupport=CreatePrimary();
		if(DCISupport!=0)
			{
			DeleteDC(DCIhdc);
			DCIhdc=0;
			return 0;
			}
		MemCpy(&DCISurfaceScreen,DCISurfaceScreenPtr,DCISurfaceScreenPtr->dciInfo.dwSize);
		// Primary support
		DCIType=1;
		lStride=DCISurfaceScreen.dciInfo.lStride-1280;	//640x2
		LinearOffSurface=DCISurfaceScreen.dciInfo.dwOffSurface;
		LinearSelSurface=DCISurfaceScreen.dciInfo.dwSelSurface;
		}
	return 1;
}
void  PASCAL FAR	DeleteDCISurface(void)
{
	void	(CALLBACK *DestroySurface)(LPVOID);	//DestroySurface Fn
	DestroySurface=DCISurfaceScreen.dciInfo.DestroySurface;
	(*DestroySurface)(DCISurfaceScreenPtr);	//Destroy the surface.
}
int PASCAL FAR	DCIPrimaryColorBits(int Color)
{
	int	color;
	if(DCIType!=1) return Color;
	color=DCISurfaceScreen.dciInfo.dwBitCount;
	if(color==16)
		{//16 bit RGB 5:6:5  64K Color
		if(	DCISurfaceScreen.dciInfo.dwMask[0]==0xF800 &&
			DCISurfaceScreen.dciInfo.dwMask[1]==0x07E0 &&
			DCISurfaceScreen.dciInfo.dwMask[2]==0x001F
			)	Color=64;
		else	Color=32;	//16 bit RGB 5:5:5 32K Color
		}
	if(color==15) 	Color=32;
	return Color;
}
void  PASCAL FAR	ReleaseDCIProvider(void)
{
	if(DCIhdc)
		{
		if(YUVSupport)	(*DCICloseProvider)(DCIhdc);
		else DeleteDC(DCIhdc);
		DCIhdc=0;
		}
}