////////////////////////////////////////////////////////////
//		SoftVCD Common API header
//		   Southern.1996.6.29
////////////////////////////////////////////////////////////
#ifndef __WINDOWS_H     /* prevent multiple includes */
#include <windows.h>
#endif

typedef	struct FFBLKtag
	{
	char ff_reserved[21]; /* reserved by DOS */
	char ff_attrib;       /* attribute found */
	WORD ff_ftime;        /* file time */
	WORD ff_fdate;        /* file date */
	long ff_fsize;        /* file size */
	char ff_name[13];     /* found file name */
	}  FFBLK;
////////////////// On OTHER_TEXT Segment ////////////////
/////////////////// Capture.C ///////////	OTHER_TEXT
void	PASCAL FAR	CapturePicture(void);	//API
void	PASCAL FAR	DecodeCapturePicture(void);	//API
/////////////////// CDROM.C /////////////	OTHER_TEXT
void 	PASCAL FAR	OpenCDROMDoor(void);
void 	PASCAL FAR	CloseCDROMDoor(void);
int 	PASCAL FAR	CDROMDoorClosed(void);
int   	PASCAL FAR	CDROMMediaChanged(void);//This function must on door closed.
void 	PASCAL FAR	LockCDROM(int Code);//0-UnLock,1-Lock
//////////////////// PreView.C ////////////	OTHER_TEXT
void	PASCAL FAR	PreViewPicture(void);
void	PASCAL FAR	PreViewReDraw(void);
/////////////////// Feature.C ////////////// 	OTHER_TEXT
int	PASCAL FAR	GetCPUType(void);
int	PASCAL FAR	CheckSerialInstall(void);
/////////////////// USEDCI.H ///////////////	OTHER_TEXT
void  	PASCAL FAR	ReleaseDCIProvider(void);
int 	PASCAL FAR	DCIPrimaryColorBits(int Color);
void	PASCAL FAR	DeleteDCISurface(void);
int	PASCAL FAR	SearchDCISupportFunction(void);
/////////////////// SPECMODE.C /////////////	OTHER_TEXT
void	PASCAL FAR	SetVideoMode(void);
int 	PASCAL FAR	TestSupportCard(void);
void  	PASCAL FAR	SearchVESAType(char far *OEMPtr);
/////////////////// S3TRIO.C  //////////////	OTHER_TEXT
void  	PASCAL FAR	InitS3Trio10E(void);
/////////////////// SNDCTRL.C //////////////	OTHER_TEXT
void	PASCAL FAR	SetVolumeAndMute(void);
long 	PASCAL FAR 	AudioWndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
int 	PASCAL FAR 	CreateAudioWindow(HANDLE hInstance,HWND ParenthWnd);
/////////////////// VESAVCD.C //////////////	OTHER_TEXT
long 	FAR PASCAL 	WndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
long 	FAR PASCAL 	WndBmpProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
void 	PASCAL 	FAR	DisplayTime(DWORD Time);
void 	PASCAL 	FAR	DrawBitmap(HDC hdc,HBITMAP hBitmap,int x,int y);
void 	_huge PASCAL 	TimerProc(HWND hwnd,UINT message,UINT idTimer,DWORD dwTime);
void  	PASCAL FAR	CheckErrorDCICall(void);	//May be the VGA not support DCI,se call will error.
void 	PASCAL 	FAR	FreeVideoDecoder(void);
void 	PASCAL 	FAR	LoadVideoDecoder(void);
void 	PASCAL 	FAR	KillCopy(void);
void 	PASCAL 	FAR	DeleteIniFile(void);
void 	PASCAL 	FAR	CreateINIFile(void);
void 	PASCAL 	FAR	FreeDriverVideoAndAudio(void);
int 	PASCAL 	FAR	LoadDriverVideoAndAudio(void);
void 	PASCAL 	FAR	RestoreAVIZoomBy2AndWindow(void);
void 	PASCAL 	FAR	SetAVITypeZoomBy2AndWindow(void);
void 	PASCAL 	FAR	SetProfileRate(int V);
DWORD 	PASCAL 	FAR	GetAllVideoPosition(void);
void 	PASCAL 	FAR	InitVideoState(void);
int 	PASCAL 	FAR	OpenVideo(HWND hwnd,int VideoNumber);
int  	PASCAL 	FAR	SearchVideoFile(void);
void 	PASCAL 	FAR	DisplayErrorMessage(int Ret,HWND hwnd);
void  	PASCAL 	FAR	GetCDROMName(int DrvNum);
int  	PASCAL 	FAR	CheckCDROMEX(void);
DWORD 	PASCAL 	FAR	UpDateVideo(int VideoID,HWND MainWindow);
DWORD 	PASCAL 	FAR	SetVideoWindow(int VideoID,HWND VideoWindow,HWND CallBackhWnd);
void 	PASCAL 	FAR	BuildSTHMPEGTypeMCI(void);
int	PASCAL 	FAR	TestVESASupport(void);
void 	PASCAL 	FAR	FreeVideoStateBuffer(void);
void 	PASCAL 	FAR	AllocateVideoStateBuffer(void);
void 	PASCAL 	FAR	ComputePalette(void);
void 	PASCAL 	FAR	DrawAllStatus(HDC hdc);
void 	PASCAL 	FAR	DrawPlayType(HDC hdc);
////////////////// On _TEXT Segment ////////////////
//////////////////// VESADCI.C /////////////	_TEXT
void far *GetAPIEntry(int VxD_ID);
int 	SetDCI(int ScrW,int ScrH,int LineW,int ColorBits);
void	ReleaseDCI(void);
//////////////////// MAIN.C ////////////////	_TEXT
void	PASCAL 	FAR	GetCWD(char *buf, int buflen);
int	PASCAL 	FAR 	SetDisk(int drive);
int 	PASCAL 	FAR	ChangeDir(const char *path);
int 	PASCAL	FAR	FindFirst(const char *pathname,FFBLK 	*ffblk,int attrib);
int	PASCAL	FAR	FindNext(FFBLK 	*ffblk);
int	PASCAL	FAR	_Dos_SetFileAttr(const char *path, unsigned attrib);
void 	PASCAL	FAR	GetFAT(unsigned char drive,char far *dtable);
void	PASCAL	FAR	GoHome(void);
/////////////////// YUVRGB32.C //////////////	YUVRGB32_TEXT
void	PASCAL	FAR	DrawYVU12(void);	//YVU12 Planar
void	PASCAL	FAR	DrawYUY2(void);	//YUYV 4:2:2 byte ordering
void	PASCAL	FAR	DrawYVYU(void);	//YVYU 4:2:2 byte ordering
void	PASCAL	FAR	DrawUYVY(void);	//UYVY 4:2:2 byte ordering
void	PASCAL	FAR	DrawIF09(void);	//YUV9 planer
void	PASCAL	FAR	DrawYVU9(void);	//YUV9 planer
