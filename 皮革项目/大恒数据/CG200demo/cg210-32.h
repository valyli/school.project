/*
*-----------------------------------------------------------------------------
*       Name            CG210-32.H
*       Purpose         Device Driver Interface for Win32s, Windows95
*       Image karte		DH-VRT-CG210
*       Development Kit Microsoft Win32 SDK, Visual C++ 4.00 
*       Author          Zhang Ce
*       Date          	March/99
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
        
typedef DWORD HCG210;
                        
#define DISABLE	FALSE
#define ENABLE	TRUE

#define AD_SOURCE		0
#define AD_BRIGHTNESS	1
#define AD_CONTRAST		2
#define AD_HUE			3
#define AD_SATURATION	4 
#define AD_GAIN			5
#define	AD_AGCPED		6
#define AD_AGCRGBH		7
#define AD_AGCGN		8

#define	FIELD	1
#define FRAME	0         

#define YUV422	0
#define RGB888	1
#define RGB565	2
#define RGB555	3
#define RGB8888	4
#define All8Bit		5
#define Limited8Bit	6
                        
#define TopField	0
#define BottomField	1

#define LUMA_HYBWI	0
#define LUMA_HYBWR	1
#define LUMA_CTRAP	2
#define LUMA_HYPK	3
#define LUMA_HYLPF	4
#define LUMA_MNYCMB	5
#define LUMA_YCMBCO	6

#define CHROMA_CBWI		0
#define CHROMA_CBWR		1
#define CHROMA_CORE		2
#define CHROMA_MNCCMB	3
#define CHROMA_CCMBCO	4

#define COMB_ACMBRE		0
#define COMB_ACMBCO		1
#define COMB_VCTRL		2
#define COMB_ACMBEN		3

#define	HORSCL_HYDEC	0
#define VERSCL_VSCLEN	1
#define VERSCL_VRT2X	2

#define GAMMACORRCTRL	0

// Functions of CG210 device driver
HCG210 __stdcall BeginCG210(int iImageDevice);
int __stdcall EndCG210(HCG210 hcg210);
int __stdcall CG210Capture(HCG210 hcg210, BOOL Enable);
int __stdcall CG210CaptureToMem(HCG210 hcg210, DWORD MemAddr, DWORD MemSize, 
								WORD IntervVSyncs, BOOL bFrmMode, WORD Sum);
int __stdcall CG210EnableOverlay(HCG210 hcg210, BOOL Enable);
int __stdcall CG210GetSnappingStatus( HCG210 hcg210, BOOL *pbFlag);
int __stdcall CG210ReadFromMem(HCG210 hcg210, char *lpSourBuf, DWORD MemSize,
							   WORD Number, char *lpDestBuf);
int __stdcall CG210SetADParam(HCG210 hcg210, BYTE Param, BYTE Value);
int __stdcall CG210SetLumaCtrl(HCG210 hcg210, BYTE Param, BYTE Value);
int __stdcall CG210SetChromaCtrl(HCG210 hcg210, BYTE Param, BYTE Value);
int __stdcall CG210SetCombFilter(HCG210 hcg210, BYTE Param, BYTE Value);
int __stdcall CG210SetGammaCorrCtrl(HCG210 hcg210, BYTE Param, BYTE Value);
int __stdcall CG210SetGammaCorrCoef(HCG210 hcg210,
									WORD Start, WORD Entries,
									BYTE *lpGammaBuf);
int __stdcall CG210SetScaleCtrl(HCG210 hcg210, BYTE Param, BYTE Value);

int __stdcall CG210SetColorSpace(HCG210 hcg210, BYTE Space);
int __stdcall CG210SetDelay(HCG210 hcg210, WORD XDelay, WORD YDelay);
int __stdcall CG210SetDispMode(HCG210 hcg210, BOOL Mode);
int __stdcall CG210SetDispWindow(HCG210 hcg210,
							   int Left, int Top, int Width, int Height);
int __stdcall CG210SetInpVideoWindow(HCG210 hcg210,
								   int Left, int Top, int Width, int Height);
int __stdcall CG210SetMask(HCG210 hcg210, BYTE Param, DWORD Address);
int __stdcall CG210Snap(HCG210 hcg210);
int __stdcall CG210SnapOneToMem( HCG210 hcg210, DWORD MemAddr, DWORD MemSize,
								 BOOL bFrmMode );
int __stdcall CG210WaitOddVSync(HCG210 hcg210);
int __stdcall CG210WaitVSync(HCG210 hcg210);

int __stdcall ReadDispWindow(HDC hdc, 
						   int Left, int Top, int Width, int Height,
						   BYTE *lpDestBuf);

int __stdcall CG210DirectSetADParam(HCG210 hcg210, BYTE bySubAdr, BYTE byVal);

/* extren "C" { */
#ifdef __cplusplus
}
#endif

