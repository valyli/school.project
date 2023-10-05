////////////////////////////////////////////////////////
//	Sound Control face handle include SndWndProc
//	Sound can mute and control volume,mono etc.
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include <mmsystem.h>
#include "VCDAPI.H"

#define	BEAUDIOPOWER	1
#define	BELEFT		2
#define	BEDOWN		3
#define	BEUP		4
#define	BERIGHT		5
#define	BEMONO		6
#define	BEVOLUME	7
#define	BEMUTE		8
#define	BEAM		9
#define	BEFM		10
#define	BECD		11
#define	BEFLOAT		12
#define	BEINT		13
#define	BEQUICK		14
#define	ALLBUTTON	14
////////////////////////////////
extern	int	Playing;
extern	int 	videoID;
extern	int	StopFlags;
extern	int	StepFlags;
void	MemSet(LPSTR MemPtr,BYTE C,WORD Size);
HWND	AudioMainWindow;
//The Audio Decoder support 8 bits and 16 bits.
//And auto used them.
HINSTANCE	AudiohInst;
void  	FAR PASCAL	(*SetDecode)(int Channel,int Bits,int Rate);
DWORD	FAR PASCAL	(*GethWaveOuthDeviceID)(void);//[hWaveOut|DevID]
static	int	LoadAudioDecoder(void)
{
	AudiohInst=LoadLibrary("STHMPEG.ADO");
	return	(AudiohInst>HINSTANCE_ERROR);
}
static	void	GetAudioDecoderAddress(void)
{
	(FARPROC)SetDecode=GetProcAddress(AudiohInst,MAKELP(0,18));
	(FARPROC)GethWaveOuthDeviceID=GetProcAddress(AudiohInst,MAKELP(0,27));
	(WORD)GethWaveOuthDeviceID+=4;
}
HWAVEOUT PASCAL	GethWaveOut(void)
{
	DWORD	Val;
	if(GethWaveOuthDeviceID==NULL) return 0;
	Val=(*GethWaveOuthDeviceID)();
	return	HIWORD(Val);
}
UINT 	PASCAL	GetDeviceID(void)
{
	DWORD	Val;
	if(GethWaveOuthDeviceID==NULL) return 0;
	Val=(*GethWaveOuthDeviceID)();
	return	LOWORD(Val);
}
static	void	FreeAudioDecoder(void)
{
	if(AudiohInst>HINSTANCE_ERROR)
		{
		FreeLibrary(AudiohInst);
		AudiohInst=0;
		}
}
static	void	SetDecoder(int Rate,int Bits,int Channel)
{	//Rate 0=44.1K 1=22.05K 2=11.025K
	//Precision	0=Integer 1=Floating 2=Mixed 3=Quick
	//		when Rate=1 or 2 This=3 ,when Rate=0 This=1
	//Channel 	=0 Stereo with 2 speaker
	//		=1 Mixed Stereo to Mono with 2 speaker
	//		=2 Left  Channel Mono with 2 speaker
	//		=3 Right Channel Mono with 2 speaker
	if(SetDecode==NULL)	return;
	(*SetDecode)(Channel,Bits,Rate);
}
int	CurDevID=0;
UINT	Devs=0;
DWORD	DevVolume[10];
WAVEOUTCAPS	AudioCaps[10];
static	void	ReadVolume(void)
{	// return the Old Volume.
	unsigned long	Vol;
	int		i;

	Devs=waveOutGetNumDevs();
	if(Devs>10) Devs=10;
	for(i=0;i<Devs;i++)
		{
		waveOutGetDevCaps(i,&AudioCaps[i],sizeof(WAVEOUTCAPS));
		waveOutGetVolume(i,&DevVolume[i]);
		}
}
static	void	RestoreVolume(void)
{
	int	i;
	for(i=0;i<Devs;i++)
		{
		waveOutSetVolume(i,DevVolume[i]);
		}
}
static	unsigned long	SetAudioVolume(unsigned long Volume)
{
	DWORD	Vol;
	CurDevID=GetDeviceID();
	waveOutGetVolume(CurDevID,&Vol);
	waveOutSetVolume(CurDevID,Volume);
	return	Vol;
}
#define	VIDEONUMBER	30
char	AudioButtonState[ALLBUTTON]={0};
extern 	char	VideoName[VIDEONUMBER][80];	// Video File Name.
extern	int	CurFileNum;
static	void	BuildCommandStr(char *Com,char *Op)
{
	lstrcpy(Com,"setaudio ");
	lstrcat(Com,VideoName[CurFileNum]);
	lstrcat(Com," ");
	lstrcat(Com,Op);
}
static	void	SetAudioOff(void)
{
	char	Com[128];
	char	Str[10];
	BuildCommandStr(Com,"off");
	mciSendString(Com,Str,sizeof(Str),AudioMainWindow);
}
static	void	SetAudioOn(void)
{
	char	Com[128];
	char	Str[10];
	BuildCommandStr(Com,"on");
	mciSendString(Com,Str,sizeof(Str),AudioMainWindow);
}
int	MixSound=0;
int	SampleRate=2;	//Rate 0=44.1K 1=22.05K 2=11.025K
int	DecodeMode=1;	//above 486-66 all had FPU,So use Float
static	void	SetLeftRightSelect(int LeftRight)
{
	int	Mute;

	Mute=AudioButtonState[BEMUTE-1];
	// Set Mute off
	if(Mute==1 || AudioButtonState[BEAUDIOPOWER-1]==1)
		{
		SetAudioOff();
		return;
		}
	/////////////// Sound On /////////////
	SetAudioOn();
	//////////// Set Channel //////////
	if(LeftRight==0 && MixSound) LeftRight=3;
	switch(LeftRight)
		{
		case 0:	SetDecoder(SampleRate,DecodeMode,0); break;
		case 1:	SetDecoder(SampleRate,DecodeMode,2); break;
		case 2:	SetDecoder(SampleRate,DecodeMode,3); break;
		case 3:	SetDecoder(SampleRate,DecodeMode,1); break;
		}
}
//int	OldLR=0;
//int	OldMute=1;
static	void	SetChannelMute(int LeftRight)
{
	int	Mute;
	char	Com[128];
	char	Str[10];

	Mute=AudioButtonState[BEMUTE-1];
	// Set Mute off
	if(Mute==1 || AudioButtonState[BEAUDIOPOWER-1]==1)
		{
//		if(Mute==OldMute) return;
		BuildCommandStr(Com,"off");
		mciSendString(Com,Str,sizeof(Str),AudioMainWindow);
//		OldMute=0;
		return;
		}
//	if(OldLR==LeftRight && Mute==OldMute) return;
//	OldMute=1;
	//Set Audio On.
	BuildCommandStr(Com,"on");
	mciSendString(Com,Str,sizeof(Str),AudioMainWindow);
	//Set Audio Off.
	if(LeftRight!=0)
		{
		if(LeftRight==1)
			{
			BuildCommandStr(Com,"right off");
			mciSendString(Com,Str,sizeof(Str),AudioMainWindow);
			}
		if(LeftRight==2)
			{
			BuildCommandStr(Com,"left off");
			mciSendString(Com,Str,sizeof(Str),AudioMainWindow);
			}
		}
//	OldLR=LeftRight;
}
DWORD		SndPos=0;
MMTIME		MmTime;
HWAVEOUT	hWaveOut;
static	void	GethWaveOutAndID(void)	//when start play read these.
{
	CurDevID=GetDeviceID();
	hWaveOut=GethWaveOut();
}
static	DWORD	SetVideoAudeo(int LeftRight,LONG LVolume,LONG RVolume)
{
	if(videoID==-1) goto SetVolume;
	GethWaveOutAndID();	//Get hWaveOut & DeviceID when start play
	if(SetDecode==NULL)    	SetChannelMute(LeftRight);
	else	SetLeftRightSelect(LeftRight);
	//Set Volume ..
	SetVolume:
	if(LVolume>65535) LVolume=65535;
	if(RVolume>65535) RVolume=65535;
	if(LeftRight==1)  RVolume=LVolume;
	if(LeftRight==2)  LVolume=RVolume;
	return	SetAudioVolume(RVolume<<16|LVolume);
}
#pragma	warn -par
void _huge PASCAL SndTimerProc(HWND hwnd,UINT message,UINT idTimer,DWORD dwTime)
{
	DWORD	CurPos;
	if(!Playing) return;
	if(StopFlags) return;
	if(StepFlags) return;
	if(AudioButtonState[BEMUTE-1]==1) return; //Mute
	if(Devs==0) return;
	if(hWaveOut==0) hWaveOut=GethWaveOut();
	if(hWaveOut==0)	return;	//No Audio Device
	if(waveOutGetPosition(hWaveOut,&MmTime,sizeof(MMTIME))!=0)
		{//HWAVEOUT HANDLE ERROR
		GethWaveOutAndID();
		return;
		}
	CurPos=MmTime.u.ms;
	if(CurPos==SndPos)
		{//Audio Stop now.
		SetAudioOff();
		SetAudioOn();
		}
	SndPos=CurPos;
}
#pragma	warn .par
////////////////////////////////
HBITMAP	AUDIOFACE;
char	VolumeState=1;
char	MuteState=1;
char	MonoState=1;
DWORD	OldVolume;
LONG	LVolume=50411;
LONG	RVolume=50411;
int	CheckTime=1000;
void	PASCAL	FAR	BuildCheckTimer(void)
{
	if(CheckTime!=-1)
		{//If CheckTime =-1 mean not check Audio Time.
		if(CheckTime<300) CheckTime=300;
		if(CheckTime>8000) CheckTime=8000;
		SetTimer(AudioMainWindow,4545,CheckTime,(TIMERPROC)SndTimerProc);
		}
}
#pragma	warn -par
extern	HANDLE 	hInst;
long FAR PASCAL AudioWndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
int PASCAL FAR CreateAudioWindow(HANDLE hInstance,HWND ParenthWnd)
{
	static char szAppName[]="Southern Soft VCD Player";
	HWND		hWnd;
	RECT		Rc;
	BITMAP		bm;

	AudioButtonState[BEMUTE-1]=0;
	AudioButtonState[BEVOLUME-1]=1;
	if(SampleRate==2)	AudioButtonState[BEAM-1]=1;
	if(SampleRate==1)	AudioButtonState[BEFM-1]=1;
	if(SampleRate==0)	AudioButtonState[BECD-1]=1;
	if(DecodeMode==0)	AudioButtonState[BEINT-1]=1;
	if(DecodeMode==1)	AudioButtonState[BEFLOAT-1]=1;
	if(DecodeMode==3)	AudioButtonState[BEQUICK-1]=1;
	//////////////////////////
	hInst=hInstance;
	//////////////////////////////////
	ReadVolume();
	OldVolume=DevVolume[CurDevID];
	RVolume=OldVolume>>16;
	LVolume=(LONG)(unsigned short)OldVolume;
	////////// Control Window ////////
	AUDIOFACE=LoadBitmap(hInstance,"AUDIOFACE");
	GetObject(AUDIOFACE,sizeof(BITMAP),&bm);
	DeleteObject(AUDIOFACE);
	GetWindowRect(GetDesktopWindow(),&Rc);	/* Get DeckTop size. */
	AudioMainWindow=hWnd=CreateWindow(szAppName,"STH Soft VCD Audio Control",
			WS_POPUP,
			(Rc.right-bm.bmWidth)/2,
			(Rc.bottom-Rc.top)/2-bm.bmHeight,
			bm.bmWidth,bm.bmHeight,
			ParenthWnd,NULL,hInstance,NULL);
	ShowWindow(hWnd,SW_SHOW);
	UpdateWindow(hWnd);
	BuildCheckTimer();
	if(LoadAudioDecoder())
		GetAudioDecoderAddress();
	return	AudioMainWindow;
}
#pragma	warn .par
static	void	AudioDrawBitmap(HDC hdc,HBITMAP hBitmap,int x,int y)
{
	HDC	hdcMem;
	BITMAP	bm;

	hdcMem=CreateCompatibleDC(hdc);
	SelectObject(hdcMem,hBitmap);
	GetObject(hBitmap,sizeof(BITMAP),&bm);
	BitBlt(hdc,x,y,bm.bmWidth,bm.bmHeight,
		hdcMem,0,0,SRCCOPY);
	DeleteDC(hdcMem);
}
static	int	AudioInButton(HWND hwnd)
{
	RECT	Rc;
	POINT	Pos;
	int	X,Y;

	GetWindowRect(hwnd,&Rc);
	GetCursorPos(&Pos);
	X=Pos.x-Rc.left;
	Y=Pos.y-Rc.top;
	X+=2;
	if((X>=12 && X<=56) && (Y>=109 && Y<=138)) return BEAUDIOPOWER;
	if(X>=332 && X<=396)
		{
		if(Y>=41  && Y<61 ) return BEAM;
		if(Y>=61  && Y<81 ) return BEFM;
		if(Y>=81  && Y<101) return BECD;
		}
	if(X>=396 && X<=460)
		{
		if(Y>=41  && Y<61 ) return BEFLOAT;
		if(Y>=61  && Y<81 ) return BEINT;
		if(Y>=81  && Y<101) return BEQUICK;
		}
	if(Y>=114 && Y<=134)
		{
		if(X>=65  && X<96 ) return BELEFT;
		if(X>=96  && X<160) return BEDOWN;
		if(X>=160 && X<224) return BEUP;
		if(X>=224 && X<255) return BERIGHT;
		//////////////////////////
		if(X>=268 && X<332) return BEMONO;
		if(X>=332 && X<396) return BEVOLUME;
		if(X>=396 && X<460) return BEMUTE;
		}
	return 0;
}
static	void	AudioDrawPower(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1100+State));
	AudioDrawBitmap(hdc,hBmp,12,109);
	DeleteObject(hBmp);
}
static	void	DrawLeft(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1110+State));
	AudioDrawBitmap(hdc,hBmp,65,114);
	DeleteObject(hBmp);
}
static	void	DrawDown(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1120+State));
	AudioDrawBitmap(hdc,hBmp,96,114);
	DeleteObject(hBmp);
}
static	void	DrawUp(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1130+State));
	AudioDrawBitmap(hdc,hBmp,160,114);
	DeleteObject(hBmp);
}
static	void	DrawRight(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1140+State));
	AudioDrawBitmap(hdc,hBmp,224,114);
	DeleteObject(hBmp);
}
static	void	DrawMono(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1150+State));
	AudioDrawBitmap(hdc,hBmp,268,114);
	DeleteObject(hBmp);
}
static	void	DrawVolume(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1160+State));
	AudioDrawBitmap(hdc,hBmp,332,114);
	DeleteObject(hBmp);
}
static	void	DrawMute(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1170+State));
	AudioDrawBitmap(hdc,hBmp,396,114);
	DeleteObject(hBmp);
}
static	void	DrawAM(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1180+State));
	AudioDrawBitmap(hdc,hBmp,332,41);
	DeleteObject(hBmp);
}
static	void	DrawFM(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1190+State));
	AudioDrawBitmap(hdc,hBmp,332,61);
	DeleteObject(hBmp);
}
static	void	DrawCD(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1200+State));
	AudioDrawBitmap(hdc,hBmp,332,81);
	DeleteObject(hBmp);
}
static	void	DrawFloat(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1210+State));
	AudioDrawBitmap(hdc,hBmp,396,41);
	DeleteObject(hBmp);
}
static	void	DrawInt(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1220+State));
	AudioDrawBitmap(hdc,hBmp,396,61);
	DeleteObject(hBmp);
}
static	void	DrawQuick(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(1230+State));
	AudioDrawBitmap(hdc,hBmp,396,81);
	DeleteObject(hBmp);
}

static	void	AudioDrawAllStatus(HDC hdc)
{
	AudioDrawPower(hdc,AudioButtonState[BEAUDIOPOWER-1]);
	DrawLeft(hdc,AudioButtonState[BELEFT-1]);
	DrawDown(hdc,AudioButtonState[BEDOWN-1]);
	DrawUp(hdc,AudioButtonState[BEUP-1]);
	DrawRight(hdc,AudioButtonState[BERIGHT-1]);
	DrawMono(hdc,AudioButtonState[BEMONO-1]);
	DrawVolume(hdc,AudioButtonState[BEVOLUME-1]);
	DrawMute(hdc,AudioButtonState[BEMUTE-1]);
	DrawAM(hdc,AudioButtonState[BEAM-1]);
	DrawFM(hdc,AudioButtonState[BEFM-1]);
	DrawCD(hdc,AudioButtonState[BECD-1]);
	DrawFloat(hdc,AudioButtonState[BEFLOAT-1]);
	DrawInt(hdc,AudioButtonState[BEINT-1]);
	DrawQuick(hdc,AudioButtonState[BEQUICK-1]);
}
static	void	AudioDrawButtonState(HWND hwnd,int Button,int Status)
{
	HDC	hdc;

	if(Playing) return;
	hdc=GetDC(hwnd);
	switch(Button)
		{
		case	BEAUDIOPOWER: 	AudioDrawPower(hdc,Status);break;
		case	BELEFT:		DrawLeft(hdc,Status);break;
		case	BEDOWN:		DrawDown(hdc,Status);break;
		case	BEUP:		DrawUp(hdc,Status);break;
		case	BERIGHT:    	DrawRight(hdc,Status);break;
		case	BEMONO:   	DrawMono(hdc,Status);break;
		case	BEVOLUME:   	DrawVolume(hdc,Status);break;
		case	BEMUTE:   	DrawMute(hdc,Status);break;
		case	BEAM:   	DrawAM(hdc,Status);break;
		case	BEFM:   	DrawFM(hdc,Status);break;
		case	BECD:   	DrawCD(hdc,Status);break;
		case	BEFLOAT:  	DrawFloat(hdc,Status);break;
		case	BEINT:   	DrawInt(hdc,Status);break;
		case	BEQUICK:  	DrawQuick(hdc,Status);break;
		}
	ReleaseDC(hwnd,hdc);
}
static	void	DisplayVolume(LONG LVolume,LONG RVolume)
{
	HDC	hdc;
	HBITMAP	hBmp1,hBmp2;
	int	i;
	long	V;

	if(Playing) return;
	hdc=GetDC(AudioMainWindow);
	hBmp1=LoadBitmap(hInst,"LED1");
	hBmp2=LoadBitmap(hInst,"LED2");
	for(i=0;i<13;i++)
		{
		V=LVolume-(i*5041L);
		AudioDrawBitmap(hdc,V>0?hBmp1:hBmp2,65,87-i*4);
		}
	for(i=0;i<13;i++)
		{
		V=RVolume-(i*5041L);
		AudioDrawBitmap(hdc,V>0?hBmp1:hBmp2,199,87-i*4);
		}
	DeleteObject(hBmp1);
	DeleteObject(hBmp2);
	ReleaseDC(AudioMainWindow,hdc);
}
int	AudioButtonPress=0;
LONG	OldLVolume,OldRVolume;
int	LeftRight=0;
static	void	AudioDoUpHandle(HWND hwnd,int Mouse)
{
	if(AudioButtonPress!=BEAUDIOPOWER && AudioButtonState[BEAUDIOPOWER-1]!=0) return;
	switch(AudioButtonPress)
		{
		case BEMONO:
		case BEVOLUME:
		case BEMUTE:
		case BEAUDIOPOWER:
			AudioButtonState[AudioButtonPress-1]^=1;
			break;
		case BELEFT:
			if(AudioButtonState[BEVOLUME-1]==0) break;
			if(LeftRight!=0)
				{
				if(LeftRight==1) break;
				OldRVolume=RVolume;
				LVolume=OldLVolume;
				RVolume=0;
				LeftRight=1;
				DisplayVolume(LVolume,RVolume);
				break;
				}
			if(Mouse)//Be mouse do it.
				{
				LVolume+=5041;
				if(LVolume>65536) LVolume=65536;
				RVolume-=5041;
				if(RVolume<0) RVolume=0;
				}
			DisplayVolume(LVolume,RVolume);
			break;
		case BEDOWN:
			if(AudioButtonState[BEVOLUME-1]==0) break;
			if(Mouse)//Be mouse do it
				{
				if(LeftRight!=2)
					{
					LVolume-=5041;
					if(LVolume<0) LVolume=0;
					}
				if(LeftRight!=1)
					{
					RVolume-=5041;
					if(RVolume<0) RVolume=0;
					}
				}
			DisplayVolume(LVolume,RVolume);
			break;
		case BEUP:
			if(AudioButtonState[BEVOLUME-1]==0) break;
			if(Mouse)//Be mouse do it
				{
				if(LeftRight!=2)
					{
					LVolume+=5041;
					if(LVolume>65536) LVolume=65536;
					}
				if(LeftRight!=1)
					{
					RVolume+=5041;
					if(RVolume>65536) RVolume=65536;
					}
				}
			DisplayVolume(LVolume,RVolume);
			break;
		case BERIGHT:
			if(AudioButtonState[BEVOLUME-1]==0) break;
			if(LeftRight!=0)
				{
				if(LeftRight==2) break;
				OldLVolume=LVolume;
				RVolume=OldRVolume;
				LVolume=0;
				LeftRight=2;
				DisplayVolume(LVolume,RVolume);
				break;
				}
			if(Mouse)//Be mouse do it
				{
				LVolume-=5041;
				if(LVolume<0) LVolume=0;
				RVolume+=5041;
				if(RVolume>65536) RVolume=65536;
				}
			DisplayVolume(LVolume,RVolume);
			break;
		/////////////////// AM,FM,CD //////////////
		case	BEAM:
		case 	BEFM:
		case	BECD:
			AudioButtonState[AudioButtonPress-1]=1;
			if(AudioButtonPress==BEAM)
				{
				AudioButtonState[BEFM-1]=
				AudioButtonState[BECD-1]=0;
				AudioDrawButtonState(hwnd,BEFM,0);
				AudioDrawButtonState(hwnd,BECD,0);
				}
			if(AudioButtonPress==BEFM)
				{
				AudioButtonState[BEAM-1]=
				AudioButtonState[BECD-1]=0;
				AudioDrawButtonState(hwnd,BEAM,0);
				AudioDrawButtonState(hwnd,BECD,0);
				}
			if(AudioButtonPress==BECD)
				{
				AudioButtonState[BEAM-1]=
				AudioButtonState[BEFM-1]=0;
				AudioDrawButtonState(hwnd,BEAM,0);
				AudioDrawButtonState(hwnd,BEFM,0);
				}
			break;
		///////// Decoder //////////////
		case	BEFLOAT:
		case 	BEINT:
		case	BEQUICK:
			AudioButtonState[AudioButtonPress-1]=1;
			if(AudioButtonPress==BEFLOAT)
				{
				AudioButtonState[BEINT-1]=
				AudioButtonState[BEQUICK-1]=0;
				AudioDrawButtonState(hwnd,BEINT,0);
				AudioDrawButtonState(hwnd,BEQUICK,0);
				}
			if(AudioButtonPress==BEINT)
				{
				AudioButtonState[BEFLOAT-1]=
				AudioButtonState[BEQUICK-1]=0;
				AudioDrawButtonState(hwnd,BEFLOAT,0);
				AudioDrawButtonState(hwnd,BEQUICK,0);
				}
			if(AudioButtonPress==BEQUICK)
				{
				AudioButtonState[BEFLOAT-1]=
				AudioButtonState[BEINT-1]=0;
				AudioDrawButtonState(hwnd,BEFLOAT,0);
				AudioDrawButtonState(hwnd,BEINT,0);
				}
			break;
		}
	AudioDrawButtonState(hwnd,AudioButtonPress,AudioButtonState[AudioButtonPress-1]);
	// Post Message to handle.
	PostMessage(hwnd,WM_COMMAND,AudioButtonPress,0L);
}
int	AudioHadDown=0;
int	AudioMoveOut=0;
extern	HWND	MainWindow;// Video Control Window
void PASCAL FAR	ClearhInt(void);
HWND PASCAL FAR	CreatehInt(HWND hwnd,int x,int y,char *Str);
extern	HWND	hIntwnd;
extern	int	hIntBtn;
extern	int	ButtonPress;
extern	int	DisplayhIntCount;
extern	int	tmpCurPos;
extern	int	Chinese;
static	void	DrawhInt(HWND hwnd,int CurPos)
{
	POINT ptCurrent;

	if(AudioButtonPress!=0)
		{
		ClearhInt();
		return;
		}
	///////////// Create a TrackPopupMenu ////////
	if(hIntBtn!=CurPos && hIntBtn!=0) ClearhInt();
	if(hIntBtn==CurPos) return;
	if(tmpCurPos==CurPos)
		{
		DisplayhIntCount++;
		if(DisplayhIntCount<10) return;
		}
	else	{//Cureent Position
		tmpCurPos=CurPos;
		DisplayhIntCount=0;
		return;
		}
	switch(CurPos)
		{
		case BEAUDIOPOWER:
			if(Chinese) hIntwnd=CreatehInt(hwnd,12,109,"声音电源");
			else hIntwnd=CreatehInt(hwnd,12,109,"Audio power");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BELEFT:
			if(Chinese) hIntwnd=CreatehInt(hwnd,65,114,"左声道/左均衡");
			else hIntwnd=CreatehInt(hwnd,65,114,"Left/Balance");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEUP:
			if(Chinese)  hIntwnd=CreatehInt(hwnd,160,114,"音量增大");
			else hIntwnd=CreatehInt(hwnd,160,114,"Volume up");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEDOWN:
			if(Chinese) hIntwnd=CreatehInt(hwnd,96,114,"音量减小");
			else hIntwnd=CreatehInt(hwnd,96,114,"Volume down");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BERIGHT:
			if(Chinese) hIntwnd=CreatehInt(hwnd,224,114,"右声道/右均衡");
			else hIntwnd=CreatehInt(hwnd,224,114,"Right/Balance");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEMONO:
			if(Chinese) hIntwnd=CreatehInt(hwnd,268,114,"使用单声");
			else hIntwnd=CreatehInt(hwnd,268,114,"Mono");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEVOLUME:
			if(Chinese) hIntwnd=CreatehInt(hwnd,312,114,"允许改变音量");
			else hIntwnd=CreatehInt(hwnd,312,114,"Enable modify volume");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEMUTE:
			if(Chinese) hIntwnd=CreatehInt(hwnd,396,114,"无声");
			else hIntwnd=CreatehInt(hwnd,396,114,"Mute");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		///////////////////////////
		case	BEAM:
			if(Chinese) hIntwnd=CreatehInt(hwnd,332,41,"11千赫 486可用");
			else hIntwnd=CreatehInt(hwnd,332,41,"11KHz 486 Use");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEFM:
			if(Chinese) hIntwnd=CreatehInt(hwnd,332,61,"22千赫 奔腾可用");
			else hIntwnd=CreatehInt(hwnd,332,61,"22KHz Pentium Use");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case 	BECD:
			if(Chinese) hIntwnd=CreatehInt(hwnd,331,81,"44千赫 P7/P8可用");
			else hIntwnd=CreatehInt(hwnd,331,81,"44KHz P7/P8 Use");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEFLOAT:
			if(Chinese) hIntwnd=CreatehInt(hwnd,376,41,"声音浮点解码");
			else hIntwnd=CreatehInt(hwnd,386,41,"Float decode");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case 	BEINT:
			if(Chinese) hIntwnd=CreatehInt(hwnd,376,61,"声音整数解码");
			else hIntwnd=CreatehInt(hwnd,376,61,"Integer decode");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEQUICK:
			if(Chinese) hIntwnd=CreatehInt(hwnd,376,81,"声音快速解码");
			else hIntwnd=CreatehInt(hwnd,386,81,"Quick decode");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		}
}
long 	PASCAL FAR	AudioWndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{
	HDC 		hdc;
	PAINTSTRUCT 	ps;
	RECT 		rect;
	DWORD		Ret;
	int		CurPos;

	switch(message)
	{
	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
		if(!Playing)
			{
			AUDIOFACE=LoadBitmap(hInst,"AUDIOFACE");
			AudioDrawBitmap(hdc,AUDIOFACE,0,0);
			DeleteObject(AUDIOFACE);
			AudioDrawAllStatus(hdc);
			}
		EndPaint(hwnd,&ps);
		DisplayVolume(LVolume,RVolume);
		return 0;
	case WM_NCHITTEST:
		if(AudioInButton(hwnd)) break;
		lParam=DefWindowProc(hwnd,message,wParam,lParam);
		if(lParam==1)	return 2;
		return	lParam;
	case WM_LBUTTONDOWN:
		AudioButtonPress=AudioInButton(hwnd);
		ClearhInt();	//Clear Hint
		if(AudioButtonPress!=BEAUDIOPOWER && AudioButtonState[BEAUDIOPOWER-1]!=0) break;
		if(AudioButtonPress)
			{
			SetCapture(hwnd);
			AudioDrawButtonState(hwnd,AudioButtonPress,AudioButtonState[AudioButtonPress-1]^1);
			}
		break;
	case WM_LBUTTONUP:
		if(AudioButtonPress)
			{
			int	CurPos;
			CurPos=AudioInButton(hwnd);
			if(CurPos==AudioButtonPress)
				{
				AudioDoUpHandle(hwnd,1);
				}
			AudioButtonPress=AudioMoveOut=0;
			ReleaseCapture();
			}
	case WM_NCMOUSEMOVE:
		CurPos=AudioInButton(hwnd);
		//////////// Draw hint ///////////
		if(CurPos) DrawhInt(hwnd,CurPos);
		else	ClearhInt();
		break;
	case WM_MOUSEMOVE:
		CurPos=AudioInButton(hwnd);
		//////////// Draw hint ///////////
		if(CurPos) DrawhInt(hwnd,CurPos);
		else	ClearhInt();
		if(AudioButtonPress)
			{
			if(CurPos!=AudioButtonPress)
				{
				AudioDrawButtonState(hwnd,AudioButtonPress,AudioButtonState[AudioButtonPress-1]);
				AudioMoveOut=1;
				}
			else	if(AudioMoveOut)
				{
				AudioDrawButtonState(hwnd,AudioButtonPress,AudioButtonState[AudioButtonPress-1]^1);
				AudioMoveOut=0;
				}
			}
		break;
	case WM_COMMAND:	// Audio Command
		switch(wParam)
			{
			case BEAUDIOPOWER:
				if(AudioButtonState[BEAUDIOPOWER-1]==0)
					{
					AudioButtonState[BEMUTE-1]=MuteState;
					AudioButtonState[BEVOLUME-1]=VolumeState;
					AudioButtonState[BEMONO-1]=MonoState;
					if(SampleRate==2)	AudioButtonState[BEAM-1]=1;
					if(SampleRate==1)	AudioButtonState[BEFM-1]=1;
					if(SampleRate==0)	AudioButtonState[BECD-1]=1;
					if(DecodeMode==0)	AudioButtonState[BEINT-1]=1;
					if(DecodeMode==1)	AudioButtonState[BEFLOAT-1]=1;
					if(DecodeMode==3)	AudioButtonState[BEQUICK-1]=1;
					hdc=GetDC(hwnd);
					AudioDrawAllStatus(hdc);
					ReleaseDC(hwnd,hdc);
					LVolume=OldLVolume;
					RVolume=OldRVolume;
					DisplayVolume(LVolume,RVolume);
					}
				else	{//Power DOWN
					int i;
					MuteState=AudioButtonState[BEMUTE-1];
					VolumeState=AudioButtonState[BEVOLUME-1];
					MonoState=AudioButtonState[BEMONO-1];
					AudioButtonState[BEMUTE-1]=0;
					AudioButtonState[BEVOLUME-1]=0;
					AudioButtonState[BEMONO-1]=0;
					AudioButtonState[BEAM-1]=
					AudioButtonState[BEFM-1]=
					AudioButtonState[BECD-1]=
					AudioButtonState[BEFLOAT-1]=
					AudioButtonState[BEINT-1]=
					AudioButtonState[BEQUICK-1]=0;
					hdc=GetDC(hwnd);
					AudioDrawAllStatus(hdc);
					ReleaseDC(hwnd,hdc);
					OldLVolume=LVolume;
					OldRVolume=RVolume;
					LVolume=RVolume=0;
					DisplayVolume(LVolume,RVolume);
					}
				break;
			case BEMONO:
				if(AudioButtonState[BEMONO-1]==0)
					{
					LVolume=OldLVolume;
					RVolume=OldRVolume;
					LeftRight=0;
					}
				else	{
					OldLVolume=LVolume;
					OldRVolume=RVolume;
					RVolume=0;
					LeftRight=1;
					}
				DisplayVolume(LVolume,RVolume);
				SetVideoAudeo(LeftRight,LVolume,RVolume);
				break;
			case BELEFT:
			case BEDOWN:
			case BEUP:
			case BERIGHT:
			case BEVOLUME:
			case BEMUTE:
				SetVideoAudeo(LeftRight,LVolume,RVolume);
				break;
			/////////// AM,FM,CD //////////
			case BEAM:
			case BEFM:
			case BECD:
				if(AudioButtonState[BEAM-1]==1) SampleRate=2;
				if(AudioButtonState[BEFM-1]==1) SampleRate=1;
				if(AudioButtonState[BECD-1]==1) SampleRate=0;
			/////////// Decodee ///////////
			case BEFLOAT:
			case BEINT:
			case BEQUICK:
				if(AudioButtonState[BEINT-1]==1)   DecodeMode=0;
				if(AudioButtonState[BEFLOAT-1]==1) DecodeMode=1;
				if(AudioButtonState[BEQUICK-1]==1) DecodeMode=3;
				SetVideoAudeo(LeftRight,LVolume,RVolume);
				break;
			}
		break;
	////////// Key Board Control. //////////
	case WM_KEYDOWN:
		switch(wParam)
			{
			case VK_DELETE:// Mute
				AudioButtonPress=BEMUTE;
				break;
			case VK_ADD: //Volume ++
				AudioButtonPress=BEUP;
				break;
			case VK_SUBTRACT://Volume --
				AudioButtonPress=BEDOWN;
				break;
			}
		if(!AudioHadDown) AudioDrawButtonState(hwnd,AudioButtonPress,AudioButtonState[AudioButtonPress-1]^1);
		AudioHadDown=1;
		switch(wParam)
			{
			case VK_ADD: //Volume ++
				if(AudioButtonState[BEVOLUME-1]==0) break;
				if(LeftRight==0)
					{//Two channel +
					LVolume+=1000;
					if(LVolume>65536) LVolume=65536;
					RVolume+=1000;
					if(RVolume>65536) RVolume=65536;
					}
				else	{//Single channel
					if(LeftRight==1)
						{//Left
						LVolume+=1000;
						if(LVolume>65536) LVolume=65536;
						}
					if(LeftRight==2)
						{//Right
						RVolume+=1000;
						if(RVolume>65536) RVolume=65536;
						}
					}
				DisplayVolume(LVolume,RVolume);
				break;
			case VK_SUBTRACT://Volume --
				if(AudioButtonState[BEVOLUME-1]==0) break;
				if(LeftRight==0)
					{//Two channel -
					LVolume-=1000;
					if(LVolume<0) LVolume=0;
					RVolume-=1000;
					if(RVolume<0) RVolume=0;
					}
				else	{//Single channel
					if(LeftRight==1)
						{//Left
						LVolume-=1000;
						if(LVolume<0) LVolume=0;
						}
					if(LeftRight==2)
						{//Right
						RVolume-=1000;
						if(RVolume<0) RVolume=0;
						}
					}
				DisplayVolume(LVolume,RVolume);
				break;
			}
		//////// Video Control /////////
		switch(wParam)
			{
			case VK_RETURN:
			case VK_SPACE://PLAY or STOP
			case VK_ESCAPE://POWER down
			case VK_HOME://START
			case VK_END:// END
			case VK_PRIOR://Page UP,Back one Min
			case VK_LEFT:// Back Search one Sec
			case VK_NEXT:// Page Down,Forward one Min
			case VK_RIGHT:// Forward search one Sec
			case VK_INSERT:// Open Select,DISC Insert now.
			case VK_TAB:	//When Play End,loop play from start.
				SendMessage(MainWindow,WM_KEYDOWN,wParam,lParam);
				break;
			}
		return 0;
	case WM_KEYUP:
		AudioDoUpHandle(hwnd,0);
		AudioHadDown=0;
		AudioButtonPress=0;
		//////// Video Control /////////
		switch(wParam)
			{
			case VK_RETURN:
			case VK_SPACE://PLAY or STOP
			case VK_ESCAPE://POWER down
			case VK_HOME://START
			case VK_END:// END
			case VK_PRIOR://Page UP,Back one Min
			case VK_LEFT:// Back Search one Sec
			case VK_NEXT:// Page Down,Forward one Min
			case VK_RIGHT:// Forward search one Sec
			case VK_INSERT:// Open Select,DISC Insert now.
			case VK_TAB:	//When Play End,loop play from start.
				SendMessage(MainWindow,WM_KEYUP,wParam,lParam);
				break;
			}
		return 0;
	/////////////////////////
	case WM_DESTROY:
		if(CheckTime!=-1) KillTimer(hwnd,4545);
		RestoreVolume();
		FreeAudioDecoder();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
////////////////// When Play start Call ///////////////
void	PASCAL FAR	SetVolumeAndMute(void)
{
	SetVideoAudeo(LeftRight,LVolume,RVolume);
}