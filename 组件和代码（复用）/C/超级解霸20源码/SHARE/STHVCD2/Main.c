//////////////////////////////////////////////////////////
//			Soft VCD Player
//	These code MUST Compiler by BC3.1,Not others.
//	SMALL Mode,386 Instructions,DOS Stack Code,
//		    FASTEST Optimizations.
//	  Main Program with Video Control & WndProc.
//			Southern.Liang
//			  1996.6.30
//////////////////////////////////////////////////////////
//#pragma	option	-zC_TEXT	//This Must in _TEXT segment because the library & Enter point in _TEXT
#include <windows.h>
#include <mmsystem.h>
#include <dos.h>	//Only this call C library
#include <dir.h>
#include <stdio.h>
#include <stdlib.h>
#include "DCI.H"
#include "VCDAPI.H"

extern	int	WindowsColorBits;	//Windows now Color bits
extern	int	Chinese;
extern	int	VESAColor;
extern	int	UseDCI;
extern	int	DCIPlay;
extern	int	VideoCardType;
extern	int	SubType;
extern	int	DCIType;	//If now be 640x480 and had DCI Primary 64K/32K
extern	RECT	VideoRc;
extern	RGNDATA	RgnData;
extern	int	M640x48064KC;
extern	int	M640x48032KC;
extern	HWND	MainWindow;	//Main Windows
extern	HWND 	ShowVideo;
extern	HANDLE 	hInst;
extern	HBITMAP	VCDFACE;
extern	HWND	AboutWindow;
extern	int	CurVideoType;
extern	HWND	VideoWindow;	//Video output Window.
extern	int	DrvNum;
extern	int	VideoNumber;
extern	int	CurFileNum;
extern	int	videoID;
extern	int	PlayType;
extern	LONG	CurrentPos;
extern	HPALETTE	PreviewhPal;	// ColorBits<=8 use palette
extern	int	TimeStart;
extern	int	OtherDecoder;		//Use internal MPEG decoder.
///////////////These Library functions in _TEXT segment
void	PASCAL FAR	GetCWD(char *buf, int buflen)
{
	getcwd(buf,buflen);
}
int	PASCAL FAR 	SetDisk(int drive)
{
	return	setdisk(drive);
}
int 	PASCAL FAR	ChangeDir(const char *path)
{
	return	chdir(path);
}
int 	PASCAL	FAR	FindFirst(const char *pathname,FFBLK 	*ffblk,int attrib)
{
	return findfirst(pathname,(struct ffblk *)ffblk,attrib);
}
int	PASCAL	FAR	FindNext(FFBLK 	*ffblk)
{
	return	findnext((struct ffblk *)ffblk);
}

int	PASCAL	FAR	_Dos_SetFileAttr(const char *path, unsigned attrib)
{
	return	_dos_setfileattr(path,attrib);
}
void 	PASCAL	FAR	GetFAT(unsigned char drive,char far *dtable)
{
	struct fatinfo FAT;
	struct fatinfo far * FATPtr;
	getfat(drive,&FAT);
	FATPtr=(struct fatinfo far *)dtable;
	FATPtr->fi_sclus=FAT.fi_sclus;
	FATPtr->fi_fatid=FAT.fi_fatid;
	FATPtr->fi_nclus=FAT.fi_nclus;
	FATPtr->fi_bysec=FAT.fi_bysec;
}
int	CurDisk;
char	CurPath[128];
void	GetHome(void)
{
	CurDisk=getdisk();
	getcwd(CurPath,sizeof(CurPath));
}
void	PASCAL	FAR	GoHome(void)
{	//Change Disk and Path to home
	setdisk(CurDisk);
	chdir(CurPath);
}
/////////////////// Make 32 Bits Segment /////////
typedef	struct	DESCtag
	{
	WORD	LimitLW;
	WORD	BaseLW;
	BYTE 	BaseHB;
	BYTE	Access;
	BYTE	ExtAccess;
	BYTE	BaseHH;
	}DESC;
WORD	YUVRGB32Selector=0;
void	Selector16To32(WORD Sel)
{
	DESC	Desc;
	_ES=FP_SEG(&Desc);
	_DI=FP_OFF(&Desc);
	_BX=Sel;
	_AX=0x0B;
	geninterrupt(0x31);	//Get Desc
	Desc.ExtAccess|=0x40;	//Set D bit
	_ES=FP_SEG(&Desc);
	_DI=FP_OFF(&Desc);
	_BX=Sel;
	_AX=0x0C;
	geninterrupt(0x31);	//Set Desc
}
void	Selector32To16(WORD Sel)
{
	DESC	Desc;
	_ES=FP_SEG(&Desc);
	_DI=FP_OFF(&Desc);
	_BX=Sel;
	_AX=0x0B;
	geninterrupt(0x31);	//Get Desc
	Desc.ExtAccess&=0xBF;	//Clear D  Bit
	_ES=FP_SEG(&Desc);
	_DI=FP_OFF(&Desc);
	_BX=Sel;
	_AX=0x0C;
	geninterrupt(0x31);	//Set Desc
}
void	MakeYUVRGB32Segment(void)
{
	YUVRGB32Selector=FP_SEG(DrawUYVY);
	Selector16To32(YUVRGB32Selector);
}
void	RestoreYUVRGB32Segment(void)
{
	Selector32To16(YUVRGB32Selector);
}
int	Run=0;
DWORD	RunStart=0;
DWORD	RunEnd=0;
extern	char	VideoName[][80];	// Video File Name.
static	int	ParaFile(void)
{
	int	Len;
	FILE	*fp;

	Len=lstrlen(VideoName[0]);
	if(VideoName[0][Len-3]|0x20=='t' &&
	   VideoName[0][Len-2]|0x20=='x' &&
	   VideoName[0][Len-1]|0x20=='t')
		{
		int	i;
		Len=0;
		fp=fopen(VideoName[0],"rt");
		if(fp==NULL) return 0;
		while(fgets(VideoName[Len],80,fp)!=NULL) Len++;
		fclose(fp);
		for(i=0;i<Len;i++)
			{
			int	l;
			l=lstrlen(VideoName[i]);
			if(VideoName[i][l-1]==0x0A) VideoName[i][l-1]=0;
			if(VideoName[i][l-1]==0x0D) VideoName[i][l-1]=0;
			}
		return Len;
		}
	else	return 1;
}
static	int	HandleCmdLine(LPSTR lpszCmdLine)
{
	int	i;
	int	j;
	int	Ret=0;
	char	Str[32];
	i=1;
	if(lpszCmdLine[i]==0) return Ret;
	while(lpszCmdLine[i]==' ')
		{
		if(lpszCmdLine[i]==0) return Ret;
		i++;
		}
	j=0;
	while(lpszCmdLine[i]!=' ')
		{
		VideoName[0][j]=lpszCmdLine[i];
		if(lpszCmdLine[i]==0) break;
		i++;
		j++;
		}
	VideoName[0][j]=0;
	Ret=ParaFile();
	if(Ret!=1) return Ret;
	if(lpszCmdLine[i]==0) return Ret;
	//////////// Start Time ////////////
	while(lpszCmdLine[i]==' ')
		{
		if(lpszCmdLine[i]==0) return Ret;
		i++;
		}
	j=0;
	while(lpszCmdLine[i]!=' ')
		{
		Str[j]=lpszCmdLine[i];
		if(lpszCmdLine[i]==0) break;
		i++;
		j++;
		}
	Str[j]=0;
	RunStart=atol(Str);
	if(lpszCmdLine[i]==0) return Ret;
	//////////// End Time   ////////////
	while(lpszCmdLine[i]==' ')
		{
		if(lpszCmdLine[i]==0) return Ret;
		i++;
		}
	j=0;
	while(lpszCmdLine[i]!=' ')
		{
		Str[j]=lpszCmdLine[i];
		if(lpszCmdLine[i]==0) break;
		i++;
		j++;
		}
	Str[j]=0;
	RunEnd=atol(Str);
	return Ret;
}
static	void	SeekVideoTo(int VideoID,HWND hwnd,DWORD Position)
{
	MCI_SEEK_PARMS	mciSeek;

	mciSeek.dwCallback=hwnd;
	mciSeek.dwTo=Position;
	mciSendCommand(VideoID,MCI_SEEK,MCI_TO,(DWORD)(LPVOID)&mciSeek);
}
int	TestMode=0;
static	void	DeleteSTHMPEGMCI(void)
{
	WritePrivateProfileString("mci","STHMPEG",NULL,"system.ini");
}
int PASCAL WinMain(HANDLE hInstance,HANDLE hPrevInstance,
			LPSTR lpszCmdLine,int nCmdShow)
{
	static char szAppName[]="Southern Soft VCD Player";
	WNDCLASS 	wndclass;
	MSG		msg;
	HWND		hWnd;
	RECT		Rc;
	BITMAP		bm;
	UINT		ErrorMode;
	HDC		hdc;
	int		LineW;

	if(hPrevInstance) return 0;	//Can't Run two times.
	DeleteSTHMPEGMCI();
	GetHome();	//Get Cur Disk and Path
	hdc=GetDC(NULL);
	WindowsColorBits=GetDeviceCaps(hdc,BITSPIXEL);
	ReleaseDC(NULL,hdc);
	//////////////////////////
	Chinese=GetSystemMetrics(SM_DBCSENABLED);//In Chinese Windows
	//////////Serial ID///////
	hWnd=CheckSerialInstall();
	if(hWnd==1)
		{// Not Install
		if(Chinese) MessageBox(NULL,"此软件没安装.\n请先安装 !","无法运行",MB_OK);
		else MessageBox(NULL,"This software had not installed.\nPlease Setup at first !","Can't RUN",MB_OK);
		return 0;
		}
	if(hWnd==2)
		{// Installed but be copy the next PC
		KillCopy();
		if(Chinese) MessageBox(NULL,"此乃受法律保护产品你不应复制到别的机器.","非法产品",MB_OK);
		else MessageBox(NULL,"You Can not copy this lawful software to another PC.","Not Lawful Product",MB_OK);
		return 0;
		}
	if(hWnd==3)
		{// Had been rename
		if(Chinese) MessageBox(NULL,"此软件已被破坏 !","无法运行",MB_OK);
		else MessageBox(NULL,"The Software be destroy !","Not RUN",MB_OK);
		return 0;
		}
	if(hWnd==4)
		{// Had been rename
		KillCopy();
		if(Chinese) MessageBox(NULL,"此软件关键数据被非法改动\n继续运行会死机 ! 请重装. ","无法运行",MB_OK);
		else MessageBox(NULL,"The Software's data be Modify \nif continue will be ERROR !\n Please reinstall .","Not RUN",MB_OK);
		return 0;
		}
	//////////////////////////
	if(GetAPIEntry(0x0543)==NULL)
		{
		if(Chinese) MessageBox(NULL,"没安装加速 VXD","错误",MB_OK);
		else MessageBox(NULL,"Not Install Accelerator VXD","Error",MB_OK);
		return 0;
		}
	ComputePalette();
	VESAColor=TestVESASupport();
	if(VESAColor==8)
		VESAColor=TestSupportCard();//Test S3 or GD542x
	if(VESAColor==0)
		{
		if(Chinese) MessageBox(NULL,"非 VGA 显示卡.\n请买一个吧.\n象这种显示卡你要放VCD ?!没趣 !","错误",MB_OK);
		else MessageBox(NULL,"Not any VGA.\nPlease Buy one.\nAs this Display Card You want to play VCD ?!Not fun !","Error",MB_OK);
		return 0;
		}
	///////////////////////////
	if(LoadDriverVideoAndAudio()==0)
		{//Load DCI Accelector
		FreeDriverVideoAndAudio();
		return 0;
		}
	CheckErrorDCICall();	//May be the VGA not support DCI,se call will error.
	UseDCI=SearchDCISupportFunction();
	//////// cmd line  ////////
	if((lpszCmdLine[0]|0x20)=='r') Run=1;	//Only Run the file.
	//////// Force mode ///////
	if((lpszCmdLine[0]|0x20)=='b')
		{//Focre Gray scale mode
		VESAColor=88;
		if(UseDCI==1)
			{
			DeleteDCISurface();
			ReleaseDCIProvider();
			}
		UseDCI=DCIType=0;
		}
	if((lpszCmdLine[0]|0x20)=='l')
		{//Focre 320x200 64K/32K mode
		if(VESAColor==16 || VESAColor==15 || VESAColor==163)
			{
			if(UseDCI==1)
				{
				if(UseDCI==1)
					{
					DeleteDCISurface();
					ReleaseDCIProvider();
					}
				UseDCI=DCIType=0;
				}
			}
		else	{
			}
		}
	if((lpszCmdLine[0]|0x20)=='h' && DCIType!=2)
		{//Focre 640x480 64KC high res mode
		VESAColor=864;
		if(DCIType)
			{
			DCIPlay=DCIPrimaryColorBits(VESAColor);
			if(DCIPlay!=8) //As VESAColor
				{
				DCIPlay=1;	//640x480 DCI Primary play
				}
			else	{//With BIOS 640x480 mode.
				DeleteDCISurface();
				ReleaseDCIProvider();
				UseDCI=DCIType=0;
				VideoCardType=SubType=0;//Not S3 and GD intra support
				}
			}
		else	{//With BIOS
			UseDCI=DCIType=0;
			VideoCardType=SubType=0;//Not S3 and GD intra support
			}
		}
	///////////////////////////
	if(UseDCI==1)
		{//Offscreen
		if(DCIType==2)
			{
			if(VESAColor==8)
				{
				}
			DCIPlay=1;
			VESAColor=128;//support YUV->RGB
			GetWindowRect(GetDesktopWindow(),&VideoRc);	//Get Windows size;
			////////// Set Cliplist //////////
			RgnData.rdh.dwSize=0x20;
			RgnData.rdh.rcBound.left=VideoRc.left;
			RgnData.rdh.rcBound.top=VideoRc.top;
			RgnData.rdh.rcBound.right=VideoRc.right;
			RgnData.rdh.rcBound.bottom=VideoRc.bottom;
			}
		else	{//Primary
			goto	SearchHowDisplay;
			}
		}
	else	{
		SearchHowDisplay:
		if(VESAColor==8)
			{//DCI primary.
			if(UseDCI==1)
				VESAColor=DCIPrimaryColorBits(VESAColor);
			if(VESAColor!=8)
				{
				DCIPlay=1;	//640x480 DCI Primary play
				}
			}
		if(VESAColor==8)
			{
			if(M640x48064KC) VESAColor=64;
			else if(M640x48032KC) VESAColor=32;
			if(VESAColor!=8)
				{
				}
			}
		if(VESAColor==8)
			{
			}
		}
	//////////////////////////
	switch(VESAColor)
		{
		case 88:VESAColor=8;	//Force Gray scale
		case 8:LineW=320;break;
		case 163:	//S3 86xx banking
		case 15:
		case 16:LineW=640;break;
		case 24:LineW=960;break;
		case 864://Force 640x480 64K mode
			if(M640x48064KC) VESAColor=64;
			else if(M640x48032KC) VESAColor=32;
			if(UseDCI) VESAColor=DCIPrimaryColorBits(VESAColor);
		case 32:
		case 64:LineW=1280;break;
		case 128:LineW=0;break;//YUV
		}
	if(SetDCI(320,200,LineW,VESAColor)==0)
		{
		if(Chinese) MessageBox(NULL,"没有足够内存分配视频影子缓冲区.","错误",MB_OK);
		else MessageBox(NULL,"Had no memory to allocate Video shadow buffer.","Error",MB_OK);
		return 0;
		}
	MakeYUVRGB32Segment();
	//////////////////////////
	AllocateVideoStateBuffer();	//Allocate Video State buffer
	SetAVITypeZoomBy2AndWindow();
	CreateINIFile();
	if((lpszCmdLine[0]|0x20)=='t' || (lpszCmdLine[1]|0x20)=='t')
			{//Run on Test mode.
			TestMode=1;
			SetProfileRate(0);
			}
	BuildSTHMPEGTypeMCI();
	//////////////////////////
	if(!hPrevInstance)
		{
		wndclass.style		=CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc	=(WNDPROC)WndProc;
		wndclass.cbClsExtra	=0;
		wndclass.cbWndExtra	=0;
		wndclass.hInstance	=hInstance;
		wndclass.hIcon		=LoadIcon(hInstance,"ACD");
		wndclass.hCursor	=LoadCursor(hInstance,"POSCUR");//LoadCursor(NULL,IDC_ARROW);
		wndclass.hbrBackground	=(HBRUSH)GetStockObject(BLACK_BRUSH);
		wndclass.lpszMenuName	=NULL;
		wndclass.lpszClassName	=szAppName;
		RegisterClass(&wndclass);
		}
	hInst=hInstance;
	////////// Control Window ////////
	GetWindowRect(GetDesktopWindow(),&Rc);	/* Get DeckTop size. */
	/////////////// LOGO Window ///////////
	VCDFACE=LoadBitmap(hInstance,"LOGO");
	GetObject(VCDFACE,sizeof(BITMAP),&bm);
	AboutWindow=CreateWindow(szAppName,szAppName,
			WS_POPUP|WS_BORDER,
			(Rc.right-Rc.left)/2-bm.bmWidth/2,
			(Rc.bottom-Rc.top)/2-bm.bmHeight/2,
			bm.bmWidth,
			bm.bmHeight,
			NULL,
			NULL,
			hInstance,
			NULL);
	SetWindowPos(AboutWindow,HWND_TOPMOST,
			(Rc.right-Rc.left)/2-bm.bmWidth/2,
			(Rc.bottom-Rc.top)/2-bm.bmHeight/2,
			bm.bmWidth,
			bm.bmHeight,
			SWP_SHOWWINDOW);
	hdc=GetDC(AboutWindow);
	DrawBitmap(hdc,VCDFACE,0,0);
	ReleaseDC(AboutWindow,hdc);
	DeleteObject(VCDFACE);
	////////////// Start Time counter /////////
	SetTimer(AboutWindow,3838,1000,(TIMERPROC)TimerProc);
	////////////////// Main Window ////////////
	VCDFACE=LoadBitmap(hInstance,"VCD");
	GetObject(VCDFACE,sizeof(BITMAP),&bm);
	DeleteObject(VCDFACE);
	MainWindow=hWnd=CreateWindow(szAppName,szAppName,
			WS_POPUP,
			(Rc.right-bm.bmWidth)/2,(Rc.bottom-Rc.top)/2,
			bm.bmWidth,bm.bmHeight,
			NULL,NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	ShowVideo=CreateWindow(szAppName,szAppName,
			WS_CHILD,
			47,24,
			64,56,
			hWnd,NULL,hInstance,NULL);
	ShowWindow(ShowVideo,SW_SHOW);
	UpdateWindow(ShowVideo);
	//////////// Create Video Windows //////////
	VideoWindow=CreateWindow(szAppName,"Video CD",
			WS_POPUP,
			0,0,
			Rc.right-Rc.left,
			Rc.bottom-Rc.top,	//Clear screen
			MainWindow,NULL,hInstance,NULL);
	ShowWindow(VideoWindow,SW_HIDE);
	UpdateWindow(VideoWindow);
	/////////// Create Audio Windows /////////////
	CreateAudioWindow(hInstance,MainWindow);
	//////////////////////////////////////////////
	LoadVideoDecoder();
	//////////////////////////////////////////////
	ErrorMode=SetErrorMode(SEM_NOOPENFILEERRORBOX|SEM_FAILCRITICALERRORS);
	//////////////////
	SetProfileRate(1);		// Normal Speed
	if(Run)	{//Only Run the file.
		VideoNumber=HandleCmdLine(lpszCmdLine);
		if(VideoNumber==0)	goto	SEARCHCDROM;
		}
	else	{///////// CDROM //////
		SEARCHCDROM:
		DrvNum=CheckCDROMEX();
		if(DrvNum>1) GetCDROMName(DrvNum);
		if(DrvNum)
			{// Search All VCD File.
			VideoNumber=SearchVideoFile();
			}
		}
	if(VideoNumber) InitVideoState();
	//////////////////
	CurFileNum=0;
	if(VideoNumber)	OpenVideo(MainWindow,CurFileNum);//Open VCD at start.
	//////////////////
	if(videoID!=-1)
		{
		if(CurVideoType)SetVideoWindow(videoID,ShowVideo,MainWindow);
		UpDateVideo(videoID,MainWindow);
		PlayType=0;	//VCD Type.
		}
	else	PlayType=1;	//MCI Type.
	if(Run && VideoNumber==1 && videoID!=-1)
		{//Seek to start
		if(RunStart) SeekVideoTo(videoID,MainWindow,RunStart);
		}
	//////////////////////////
	hdc=GetDC(MainWindow);
	DrawAllStatus(hdc);
	DrawPlayType(hdc);
	ReleaseDC(MainWindow,hdc);
	//////////////////////////
	if(VideoNumber)
		{
		CurrentPos=GetAllVideoPosition();
		if(CurrentPos<0)DisplayErrorMessage(LOWORD(CurrentPos),hWnd);
		}
	DisplayTime(CurrentPos);
	if(Run)	{//Start Run
		KillTimer(AboutWindow,3838);
		DestroyWindow(AboutWindow);//Delete in TimerProc
		TimeStart=-1;
		PostMessage(MainWindow,WM_KEYDOWN,VK_SPACE,0L);
		PostMessage(MainWindow,WM_KEYUP,VK_SPACE,0L);
		}
	/////////////////// Start up OK ///////////
	while(GetMessage(&msg,NULL,0,0))
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	SetErrorMode(ErrorMode);
	///////////////////////
	FreeVideoDecoder();
	///////////////////////
	RestoreAVIZoomBy2AndWindow();
	ReleaseDCI();		//No Hook DCI.
	if(UseDCI==1 && OtherDecoder==0 && DCIType==2)
		{
		DeleteDCISurface();
		ReleaseDCIProvider();
		}
	DeleteIniFile();		//Delete INI File Comment.
	FreeDriverVideoAndAudio();	//Free STHMPEG Files.
	FreeVideoStateBuffer();		//Free Video State buffer
	if(PreviewhPal) DeleteObject(PreviewhPal);
	RestoreYUVRGB32Segment();
	DeleteSTHMPEGMCI();
	////////////////////////
	return msg.wParam;
}
