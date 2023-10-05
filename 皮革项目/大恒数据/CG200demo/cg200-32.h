/*
*-----------------------------------------------------------------------------
*       Name            CG200-32.H
*       Purpose         Device Driver Interface for Win32s, Windows95
*       Image karte		DH-VRT-CG200
*       Development Kit Microsoft Win32 SDK, Visual C++ 4.00 
*       Author          Zhang Ce
*       Date          	Nov/97
*
*
*       Description
*
*       
*-----------------------------------------------------------------------------
*/

/* By C++ language compiler */
#ifdef __cplusplus
extern "C" {
#endif
        
typedef DWORD HCG200;
                        
#define DISABLE	FALSE
#define ENABLE	TRUE

#define AD_SOURCE		0
#define AD_BRIGHTNESS	1
#define AD_CONTRAST		2
#define AD_HUE			3
#define AD_SATURATION	4 
#define AD_CLAMPLEVEL	5
#define AD_BANDPASS		6

#define	FIELD	1
#define FRAME	0         

#define YUV422	0
#define RGB888	1
#define RGB565	2
#define RGB555	3
#define RGB8888	4
                        
#define TopField	0
#define BottomField	1

// Functions of CG200 device driver
                        
HCG200 __stdcall BeginCG200(int iImageDevice);
int __stdcall EndCG200(HCG200 hcg200);
int __stdcall CG200Capture(HCG200 hcg200, BOOL Enable);
int __stdcall CG200CaptureToMem(HCG200 hcg200, DWORD MemAddr, DWORD MemSize, 
								WORD IntervVSyncs, BOOL bFrmMode, WORD Sum);
int __stdcall CG200EnableOverlay(HCG200 hcg200, BOOL Enable);
int __stdcall CG200GetSnappingStatus( HCG200 hcg200, BOOL *pbFlag);
int __stdcall CG200ReadFromMem(HCG200 hcg200, char *lpSourBuf, DWORD MemSize,
							   WORD Number, char *lpDestBuf);
int __stdcall CG200SetADParam(HCG200 hcg200, BYTE Param, BYTE Value);
int __stdcall CG200SetColorSpace(HCG200 hcg200, BYTE Space);
int __stdcall CG200SetDelay(HCG200 hcg200, WORD XDelay, WORD YDelay);
int __stdcall CG200SetDispMode(HCG200 hcg200, BOOL Mode);
int __stdcall CG200SetDispWindow(HCG200 hcg200,
							   int Left, int Top, int Width, int Height);
int __stdcall CG200SetInpVideoWindow(HCG200 hcg200,
								   int Left, int Top, int Width, int Height);
int __stdcall CG200SetMask(HCG200 hcg200, BYTE Param, DWORD Address);
int __stdcall CG200Snap(HCG200 hcg200);
int __stdcall CG200SnapOneToMem( HCG200 hcg200, DWORD MemAddr, DWORD MemSize,
								 BOOL bFrmMode );
int __stdcall CG200WaitOddVSync(HCG200 hcg200);
int __stdcall CG200WaitVSync(HCG200 hcg200);

int __stdcall ReadDispWindow(HDC hdc, 
						   int Left, int Top, int Width, int Height,
						   BYTE *lpDestBuf);

int __stdcall SetSAA7110Param(HCG200 hcg200, BYTE bySubAdr, BYTE byVal);
int __stdcall Get32BitParam(HCG200 hcg200, WORD wOffset, DWORD *pValue);
int __stdcall Set32BitParam(HCG200 hcg200, WORD wOffset, DWORD dwVal);
int __stdcall SetVarData(HCG200 hcg200, BYTE byOffset, BYTE byVal);
int __stdcall GetVarData(HCG200 hcg200, BYTE byOffset, BYTE *pbyVal);

/* extren "C" { */
#ifdef __cplusplus
}
#endif

