//////////////////////////////////////////////////////////
//			Soft VCD Player
//	These code MUST Compiler by BC3.1,Not others.
//	SMALL Mode,386 Instructions,DOS Stack Code,
//		    FASTEST Optimizations.
//	  Main Program with Video Control & WndProc.
//			Southern.Liang
//			  1996.5.25
//////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include <mmsystem.h>
#include "DOS.H"
#include "DCI.H"
#include "VCDAPI.H"

#define	WM_DEBUG	WM_USER+800
#define	WM_CDROMOPEN	WM_USER+890
#define	VIDEONUMBER	30
//////////////// New feature Message ///////////////
#define	WM_RESUME	WM_USER+900
#define	WM_STEPVIDEO	WM_USER+901
#define	WM_STOPVIDEO	WM_USER+902
#define	WM_CUTPICTURE	WM_USER+903
#define	WM_STATEDISPLAY	WM_USER+904
#define	WM_PLAYNEXTFILE	WM_USER+905
#define	WM_PLAYPREVFILE	WM_USER+906

////////////////////////////////////
void huge TurnOffEscape(void);
void huge TurnOnEscape(void);
////////////////////Screen/////////////////
#define DAC_WRITE_ADDR  0x3C8   // VGA DAC Write Addr Register
#define DAC_READ_ADDR   0x3C7   // VGA DAC Read Addr Register
#define PEL_DATA_REG    0x3C9   // VGA DAC/PEL data Register R/W
static	void    ReadDAC(void far *DAC,WORD Start,WORD Number)
{
	// Determine register #'s, size to copy, etc
	asm     les     DI, dword ptr DAC       // ES:DI -> Palette Buffer
	asm     mov     DX, DAC_READ_ADDR       // DAC register # selector
	asm     mov     AX, Start       // Get Start Register
	asm     mov     BX, Number      // BX = # of DAC registers
	asm     mov     CX, BX          // CX = # of DAC registers
	asm     add     CX, BX          // CX =  "   " * 2
	asm     add     CX, BX          // CX =  "   " * 3
	asm     cld                     // Block INs forward
	// Read a block of DAC Registers
	asm     out     DX, AL          // set up correct register #
	asm     mov     DX, PEL_DATA_REG// Dac Data Register
	asm     rep     insb            // block read DAC registers
}
static	void    LoadDAC(void far *DAC,WORD Start,WORD Number)
{
	asm     push    ds
	Wait:
	asm	mov	dx,0x3DA
	asm	in	al,dx
	asm	test	al,8
	asm	jz	short	Wait
	asm	mov	dx,0x3C6
	asm	mov	al,0xFF
	asm	out	dx,al
	asm     lds     SI,dword ptr DAC	// DS:SI -> Palette Data
	asm     mov     DX, DAC_WRITE_ADDR	// DAC register # selector
	asm     mov     BX, Number		// Get Number Register
	asm	mov	cx, Start
	asm     cld			// Block OUTs forward
	LOOPOUT:
	asm	mov	al,cl
	asm     out     DX,AL		// set up correct register #
	asm	inc	dx
	asm     outsb			// block set DAC registers
	asm	outsb
	asm	outsb
	asm	dec	dx
	asm	inc	cx
	asm	cmp	cx,bx
	asm	jbe	short	LOOPOUT
	asm     pop     ds
}
BYTE    Palette[256*3];
void PASCAL FAR	ComputePalette(void)
{
	int	i;
	for(i=0;i<256;i++)
		Palette[i*3+2]=Palette[i*3+1]=Palette[i*3]=i/4;
}
static	void	ReadAllDAC(void)
{
	ReadDAC(Palette,0,256);
}
static	void	SetAllDAC(void)
{	int	i;
	//LoadDAC(Palette,0,256);//This Load too fast on some fast machine error.
	outportb(0x3C6,0xFF);
	outportb(0x3C8,0);
	for(i=0;i<256*3;i++)	//Load Slowly make on fast machine success.
		outportb(0x3C9,Palette[i]);
	outport(0x3C4,0x0003);
}
///////////////////////////////////////////
void FAR PASCAL Death(HDC hdc);
void FAR PASCAL Resurrection(HDC hdc,WORD,WORD,WORD,WORD,WORD,WORD);
int	VESASupportFlags=0;
int	VESAColor=0;
HDC	DeathhDC;
int	Old3CF6;
void	RestoreVideoState(void);
static	void	NormalWindow(void)
{
	int 	Port;
	//////// Restore Old ////////
	outportb(0x3CE,0x06);
	outportb(0x3CF,Old3CF6);	//128K Screen Buffer
	//////////////////
	_AX=3;
	geninterrupt(0x10);		//This is very importion
	RestoreVideoState();
	//////////////////
	_AX=3;
	geninterrupt(0x10);		//This is very importion
	//////////////////////////////////
	Resurrection(DeathhDC,0,0,0,0,0,0);
	ReleaseDC(NULL,DeathhDC);
	ShowCursor(1);
	InvalidateRect(NULL,NULL,0);
}
extern	int	VideoCardType;
extern	int	SubType;
extern	DWORD	VideoPhysBase;
int	BankingFlags=0;		//No 128K Buffer use banking.
int	OtherDecoder=0;		//Use internal MPEG decoder.
char	OtherDecoderName[24];
void	SetVideoBufferBase(DWORD Base);
int	LinearFlags=0;
extern	WORD	Linear;
static	int	TestNo128KVideo(void)
{
	int	Ret;
	WORD	Selector;
	DWORD	Limit;
	DWORD 	far *Ptr;
	DWORD	Data,tmp;
	if(LinearFlags==0) return 1;	//No 128K
	//Screen Buffer as B800 Segment.
	asm	mov	es,Linear
	_EDI=0x18000;
	__emit__(0x26,0x67,0x66,0x8B,0x07);//asm  mov	eax,es:[edi]
	__emit__(0x66,0x26,0x67,0x83,0x37,0xFF);//asm 	xor es:[edi],0xFFFFFFFF
	__emit__(0x26,0x67,0x66,0x3B,0x07);//asm  cmp	eax,es:[edi]
	__emit__(0x26,0x67,0x66,0x89,0x07);//asm  mov	es:[edi],eax
	asm	je	ROM
	return 	0;
	ROM:
	return  1;
}
int	GetBankSize(int Mode);
int	BankSize=1;	//K
int	BankGranUnit=64;
void	SaveVideoState(void);
void	PASCAL	FAR	GetBankingWay(void)
{
	outportb(0x3CE,0x06);outportb(0x3CF,Old3CF6);//64K Screen Buffer
	if(VideoCardType==0)
		BankGranUnit=GetBankSize(VESAColor==16 ? 0x10E:0x10D);
	else BankGranUnit=GetBankSize(0x101);
	if(BankGranUnit==0) BankGranUnit=64;
	BankSize=64/BankGranUnit;
	if(BankSize==0) BankSize=1;
}
static	void	Set320x20064KC(void)
{
	ShowCursor(0);
	DeathhDC=GetDC(NULL);
	Death(DeathhDC);
	////////////////
	SaveVideoState();
	////////////////
	_AX=0x13;	//Some VGA card must call this first.
	geninterrupt(0x10);	//In Graphics mode first.
	///////////////////////////
	if(VideoCardType==0)
		{//VESA Support
		if(VESAColor==64)
			{//640x480 64KC
			_BX=0x111;
			_AX=0x4F02;
			geninterrupt(0x10);
			}
		if(VESAColor==32)
			{//640x480 32KC
			_BX=0x110;
			_AX=0x4F02;
			geninterrupt(0x10);
			}
		if(VESAColor==16)//64K Color
			{
			_BX=0x10E;
			_AX=0x4F02;
			geninterrupt(0x10);
			}
		if(VESAColor==15)//32K Color
			{
			_BX=0x10D;
			_AX=0x4F02;
			geninterrupt(0x10);
			}
		if(VESAColor==8)//256 Color
			{
			_AX=0x13;
			geninterrupt(0x10);
			}
		}
	else	{//S3 or GD542x,myself support
		if(VESAColor==8)
			{
			_AX=0x13;
			geninterrupt(0x10);
			}
		else	SetVideoMode();
		}
	if(VESASupportFlags)//Set Video Memory Bank & Display start
		{
		_AX=0x4F05;
		_BX=0;_DX=0;//Select Bank 0
		geninterrupt(0x10);
		_AX=0x4F07;
		_BX=0;_CX=0;_DX=0;//Start display at (0,0)
		geninterrupt(0x10);
		}
	if(VESAColor==64 || VESAColor==32)
		{//Set 640x240 mode
		int	Port;
		outportb(0x3D4,9);
		Port=inportb(0x3D5);
		if((Port&1)) Port|=0x80;
		else	Port|=1;
		outportb(0x3D5,Port);
		if(VESAColor==64) BankGranUnit=GetBankSize(0x111);
		else	BankGranUnit=GetBankSize(0x110);
		if(BankGranUnit==0) BankGranUnit=64;
		BankSize=64/BankGranUnit;
		if(BankSize==0) BankSize=1;
		}
	else	{
		if(VESAColor==16||VESAColor==15)
			{
			//////// Set 128K Buffer ////////
			outportb(0x3CE,0x06);Old3CF6=inportb(0x3CF);
			outportb(0x3CE,0x06);outportb(0x3CF,Old3CF6&0xF3);//128K Screen Buffer
			if(BankingFlags==0)	//Force use banking
				BankingFlags=TestNo128KVideo();
			if(BankingFlags)
				{//Normal VGA,use banking.
				GetBankingWay();
				}
			}
		}
}
///////////////////// VESA //////////////////////
typedef	struct	VESAtag
	{
	DWORD	VESAFlags;
	WORD	Version;
	char far * OEMPtr;
	DWORD	Size;
	int far *  ModePtr;
	}VESA;
VESA far *VESAPtr;
WORD	DOSSel;
WORD	DOSSeg;
typedef	struct	Stacktag
	{
	DWORD	DI;
	DWORD	SI;
	DWORD	BP;
	DWORD	Resever;//
	DWORD	BX;
	DWORD	DX;
	DWORD	CX;
	DWORD	AX;
	WORD	FLAGS;//
	WORD	ES;
	WORD	DS;
	WORD	FS;
	WORD	GS;
	WORD	IP;//
	WORD	CS;//
	WORD	SP;
	WORD	SS;
	}STACK;
STACK	Stack;
////////////////////////////////////////////
WORD	VideoStateSel=0;
WORD	VideoStateSeg=0;
void PASCAL FAR	AllocateVideoStateBuffer(void)
{
	DWORD	Size;

	if(VESASupportFlags==0) return;//VESA Call not support.
//	_AX=0x4F04;
//	_DL=0;
//	_CX=0xFF;
//	geninterrupt(0x10);	//This call in Win95 & S3 Trio32/64 driver
//	if(_AX!=0x004F)	return;	//will make GDI error.
//	Size=_BX;		//Always the size = 1024 bytes
//	Size*=64;
	Size=4096;		//Now set 4096 bytes buffer for all Video card
	GlobalDosAlloc(Size);
	VideoStateSel=_AX;
	VideoStateSeg=_DX;
}
void PASCAL FAR	FreeVideoStateBuffer(void)
{
	if(VideoStateSel==NULL) return;
	GlobalDosFree(VideoStateSel);
}
int	SupperVESAState=0;
static	void	SaveVideoState(void)
{
	if(VideoStateSel==NULL) return;
	Stack.ES=VideoStateSeg;
	Stack.AX=0x4F04;
	Stack.DX=1;	//The Supper VGA state on Windows95 VIEWTOP 64V+ error
	Stack.CX=0x7;	//VESA Restore Video hardware,BIOS data,DAC state
	Stack.CX|=SupperVESAState;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x10;
	_AX=0x300;
	geninterrupt(0x31);
}
static	void	RestoreVideoState(void)
{
	if(VideoStateSel==NULL) return;
	Stack.ES=VideoStateSeg;
	Stack.AX=0x4F04;
	Stack.DX=2;	//The Supper VGA state on Windows95 VIEWTOP 64V+ error
	Stack.CX=0x7;	//VESA Restore Video hardware,BIOS data,DAC state
	Stack.CX|=SupperVESAState;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x10;
	_AX=0x300;
	geninterrupt(0x31);
}
int  far *  ModePtr;
static	int	VESAModeTest(int Mode)
{
	////////// Stack Registers ////////
	Stack.DI=0;
	Stack.ES=0xC000;	//BIOS ROM area C000:0
	Stack.AX=0x4F01;
	Stack.CX=Mode;		//VESA Mode;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x10;
	_AX=0x300;
	geninterrupt(0x31);
	asm	jnc	short	NEXT2;
	return 0;
	NEXT2:			//VESA Support 64K Color
	if((Stack.AX&0xFF)!=0x4F) return 0;//Not Support VESA
	if((Stack.AX&0xFF00)!=0 ) return 0;//Not Success
	return 1;
}
int	VESACanUse=0;
int	M640x48064KC=0;
int	M640x48032KC=0;
int	PASCAL FAR	TestVESASupport(void)
{
	int	Mode;
	/////////// Must be VGA //////////
	if((inportb(0x3CC)&1)==0) return 0;
	/////////// Allocate DOS Memory //////////
	GlobalDosAlloc(256);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		{
		if(VESAModeTest(0x111)==1) M640x48064KC=1;
		if(VESAModeTest(0x110)==1) M640x48032KC=1;
		if(VESAModeTest(0x10E)==1) return 16;
		if(VESAModeTest(0x10D)==1) return 15;
		return 8;
		}
	////////////////VESA Info////////////////
	Stack.DI=0;
	Stack.ES=DOSSeg;
	Stack.AX=0x4F00;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x10;
	_AX=0x300;
	geninterrupt(0x31);
	asm	jnc	short	NEXT2;
	// DPMI or VESA Call Error,Directly test mode.
	DIRTESTMODE:
	GlobalDosFree(DOSSel);
	if(VESAModeTest(0x10E)==1) return 16;
	if(VESAModeTest(0x10D)==1) return 15;
	return 8;
	NEXT2:			//VESA Support 64K Color
	if((Stack.AX&0xFF)!=0x4F) goto DIRTESTMODE;//Not Support VESA
	if((Stack.AX&0xFF00)!=0 ) goto DIRTESTMODE;//Not Success
	VESASupportFlags=VESACanUse=1;
	///////////////Read VESA info/////////////
	VESAPtr=MK_FP(DOSSel,0);
	if(VESAPtr->VESAFlags!=0x41534556) goto DIRTESTMODE;//'VESA'
	ModePtr=VESAPtr->ModePtr;
	////////// Segment -> Selector ///////////
	_BX=FP_SEG(ModePtr);
	_AX=2;
	geninterrupt(0x31);	//DOS Segment to Selector.
	asm	jnc	short	NEXT3;
	goto	DIRTESTMODE;
	NEXT3:
	*((WORD *)&ModePtr+1)=_AX;	//High WORD = Selector.
	/////////// Mode Info ////////////
	Mode=8;
	while(*ModePtr!=-1)
		{
		if(*ModePtr==0x111) M640x48064KC=1;
		if(*ModePtr==0x110) M640x48032KC=1;
		if(*ModePtr==0x10E)
			{
			if(Mode==8||Mode==15)
				Mode=16;	//64 K Colors
			}
		if(*ModePtr==0x10D)
			{
			if(Mode==8) Mode=15;	//32 K Colors
			}
		ModePtr++;	//Next VESA mode.
		if(*ModePtr==0) break;
		}
	if(Mode==8)	SearchVESAType(VESAPtr->OEMPtr);
	///////////////Free DOS Memory ///////////
	GlobalDosFree(DOSSel);
	//////////////////////////////////////////
	return Mode;
}
typedef	struct	VESAINFOtag
	{
	WORD	ModeAttrib;
	BYTE	WindowAAttrib;
	BYTE	WindowBAttrib;
	WORD	GranUnit;
	WORD	WinSize;
	WORD	WindowASegment;
	WORD	WindowBSegment;
	void far *BankSwitchProc;
	WORD	LineBytes;
	WORD	WidthBytes;
	WORD	HeightBytes;
	}VESAINFO;
static	HadGetBankSize=0;
static	int	GetBankSize(int Mode)
{
	VESAINFO far *Ptr;
	if(HadGetBankSize==1) return BankGranUnit;
	HadGetBankSize=1;
	GlobalDosAlloc(256);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		return	64;
	////////////////VESA Info////////////////
	Stack.DI=0;
	Stack.ES=DOSSeg;
	Stack.AX=0x4F01;
	Stack.CX=Mode;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x10;
	_AX=0x300;
	geninterrupt(0x31);
	asm	jnc	short	NEXT2;
	// DPMI or VESA Call Error,Directly test mode.
	GlobalDosFree(DOSSel);
	return 64;
	NEXT2:			//VESA Support 64K Color
	Ptr=MK_FP(DOSSel,0);
	BankGranUnit=Ptr->GranUnit;
	///////////////Free DOS Memory ///////////
	GlobalDosFree(DOSSel);
	//////////////////////////////////////////
	if(BankGranUnit==0) BankGranUnit=64;
	return BankGranUnit;
}
////////////////////////////////////////////////
int	Start=0;
////////////////////////////////////////////
char	SthMPEG[40];
void PASCAL FAR	BuildSTHMPEGTypeMCI(void)
{
	GetCWD(SthMPEG,sizeof(SthMPEG));
	lstrcat(SthMPEG,"\\STHMPEG.SYS");
}
static	void	AddSTHMPEGTypeMCI(void)
{
	WritePrivateProfileString("mci","STHMPEG",SthMPEG,"system.ini");
}
static	void	DeleteSTHMPEGTypeMCI(void)
{
	WritePrivateProfileString("mci","STHMPEG",NULL,"system.ini");
}
//////////////////// Video Play ////////////////
static	void	MemSet(LPSTR MemPtr,BYTE C,WORD Size)
{
	asm	les	di,MemPtr
	asm	mov	cx,Size;
	asm	mov	al,C
	asm	cld
	asm	shr	cx,1
	asm	mov	ah,al
	asm	rep	stosw
	asm	adc	cl,cl
	asm	rep	stosb
}
static	DWORD	VideoOpen(LPSTR Path,LPSTR MCIDriver)
{
	DWORD	Ret;
	MCI_ANIM_OPEN_PARMS	mciopen;

	MemSet((LPSTR)&mciopen,0,sizeof(mciopen));
	mciopen.lpstrDeviceType=MCIDriver;
	mciopen.lpstrElementName=Path;
	Ret=mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,(DWORD)(LPVOID)&mciopen);
	if(Ret!=0)
		{
		return (Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return	mciopen.wDeviceID;	//TRUE;
}
DWORD PASCAL FAR	SetVideoWindow(int VideoID,HWND VideoWindow,HWND CallBackhWnd)
{
	DWORD	Ret;
	MCI_ANIM_WINDOW_PARMS	mciWindow;

	MemSet((LPSTR)&mciWindow,0,sizeof(mciWindow));
	///////////// Set Video in my Window /////////
	mciWindow.hWnd=VideoWindow;
	mciWindow.dwCallback=(DWORD)CallBackhWnd;
	mciWindow.lpstrText="Southern MPEG";
	Ret=mciSendCommand(VideoID,MCI_WINDOW,//MCI_NOTIFY|
		MCI_ANIM_WINDOW_HWND|MCI_ANIM_WINDOW_ENABLE_STRETCH,
		(DWORD)(LPVOID)&mciWindow);
	if(Ret!=0)
		{
		return (Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return	1;	//TRUE;
}
static	void	SetVideoTimeFormat(int VideoID,HWND hwnd,int Format)
{	//Format is MCI_FORMAT_MILLISECONDS or MCI_FORMAT_FRAMES
	MCI_SET_PARMS	mciTime;

	MemSet((LPSTR)&mciTime,0,sizeof(mciTime));
	mciTime.dwCallback=hwnd;
	mciTime.dwTimeFormat=Format;
	mciSendCommand(VideoID,MCI_SET,//MCI_NOTIFY|
		MCI_SET_TIME_FORMAT,(DWORD)(LPVOID)&mciTime);
}
void	ResetPalette(void);
int	Loop=0;
int	LoopCount=0;
int	LoopStart=-1;
int	CursorPos;
int	FromPos;	//Current file loop start position
int	ToPos;		//Current file loop end position
int	LoopEnd=-1;
DWORD	LoopStartBase;
DWORD	EndTo;
DWORD	From=0;
DWORD	To=0;
LONG	CurrentPos=0;
extern	int	DisplayVideo;
extern	int	Run;
extern	DWORD	RunStart;
extern	DWORD	RunEnd;
extern	int	DCIType;	//If now be 640x480 and had DCI Primary 64K/32K
static	DWORD	PlayVideo(int VideoID,HWND CallBackhWnd)
{
	DWORD	Ret;
	MCI_ANIM_PLAY_PARMS	mciplay;

	MemSet((LPSTR)&mciplay,0,sizeof(mciplay));
	mciplay.dwCallback=(DWORD)CallBackhWnd;
	if(Run)	{//CmdLine Run
		if(RunEnd!=0 && RunStart<RunEnd)
			{//Run To
			mciplay.dwTo	=RunEnd;
			Ret=mciSendCommand(VideoID,MCI_PLAY,MCI_NOTIFY|MCI_TO,(DWORD)(LPVOID)&mciplay);
			}
		else	Ret=mciSendCommand(VideoID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciplay);
		}
	else	{//Normal play
		if(Loop && LoopStart<LoopEnd && LoopStart!=-1 && LoopEnd!=-1)
			{//Enable Loop area
			LONG	CurPos;
			mciplay.dwFrom	=From;
			mciplay.dwTo	=To;
			CurPos=CurrentPos;
			CurPos-=LoopStartBase;
			if(CurPos<From)	Ret=mciSendCommand(VideoID,MCI_PLAY,MCI_NOTIFY|MCI_FROM|MCI_TO,(DWORD)(LPVOID)&mciplay);
			else	Ret=mciSendCommand(VideoID,MCI_PLAY,MCI_NOTIFY|MCI_TO,(DWORD)(LPVOID)&mciplay);
			}
		else Ret=mciSendCommand(VideoID,MCI_PLAY,MCI_NOTIFY,(DWORD)(LPVOID)&mciplay);
		}
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	if(VESAColor==8)  ResetPalette();
	DisplayVideo=1;
	return 1;
}
static	void	StopVideo(int VideoID,HWND hwnd)
{
	MCI_GENERIC_PARMS	mcigen;
	mcigen.dwCallback=hwnd;
	mciSendCommand(VideoID,MCI_STOP,0,//MCI_NOTIFY,
		(DWORD)(LPVOID)&mcigen);
}
static	void	StopVideoWait(int VideoID,HWND hwnd)
{
	MCI_GENERIC_PARMS	mcigen;
	mcigen.dwCallback=hwnd;
	mciSendCommand(VideoID,MCI_STOP,MCI_WAIT,
		(DWORD)(LPVOID)&mcigen);
}
static	DWORD	PauseVideo(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_GENERIC_PARMS	mcigen;
	mcigen.dwCallback=hwnd;
	Ret=mciSendCommand(VideoID,MCI_PAUSE,0,//MCI_NOTIFY,
		(DWORD)(LPVOID)&mcigen);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;
}
static	void	ResumeVideo(int VideoID,HWND hwnd)
{
	MCI_GENERIC_PARMS	mcigen;
	mcigen.dwCallback=hwnd;
	mciSendCommand(VideoID,MCI_RESUME,MCI_NOTIFY,
		(DWORD)(LPVOID)&mcigen);
}
#pragma	warn -par
static	void	CloseVideo(int VideoID,HWND hwnd)
{
	mciSendCommand(VideoID,MCI_CLOSE,0,NULL);
}
#pragma	warn .par
static	DWORD	GetVideoLength(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_STATUS_PARMS	mciStatus;

	MemSet((LPSTR)&mciStatus,0,sizeof(mciStatus));
	mciStatus.dwCallback=hwnd;
	mciStatus.dwItem=MCI_STATUS_LENGTH;
	Ret=mciSendCommand(VideoID,MCI_STATUS,//MCI_NOTIFY|
		MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return mciStatus.dwReturn;	//Length
}
static	DWORD	GetVideoCurrentPosition(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_STATUS_PARMS	mciStatus;

	MemSet((LPSTR)&mciStatus,0,sizeof(mciStatus));
	mciStatus.dwCallback=hwnd;
	mciStatus.dwItem=MCI_STATUS_POSITION;
	Ret=mciSendCommand(VideoID,MCI_STATUS,//MCI_NOTIFY|
		MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return mciStatus.dwReturn;	//Current Position
}
static	DWORD	SeekVideoTo(int VideoID,HWND hwnd,DWORD Position)
{
	DWORD	Ret;
	MCI_SEEK_PARMS	mciSeek;

	mciSeek.dwCallback=hwnd;
	mciSeek.dwTo=Position;
	Ret=mciSendCommand(VideoID,MCI_SEEK,//MCI_NOTIFY|
		MCI_TO,(DWORD)(LPVOID)&mciSeek);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;	//Current Position
}
static	DWORD	SeekVideoToStart(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_SEEK_PARMS	mciSeek;

	mciSeek.dwCallback=hwnd;
	mciSeek.dwTo=0;
	Ret=mciSendCommand(VideoID,MCI_SEEK,//MCI_NOTIFY|
		MCI_SEEK_TO_START,(DWORD)(LPVOID)&mciSeek);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;	//Current Position
}
static	DWORD	SeekVideoToEnd(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_SEEK_PARMS	mciSeek;

	mciSeek.dwCallback=hwnd;
	mciSeek.dwTo=0;
	Ret=mciSendCommand(VideoID,MCI_SEEK,//MCI_NOTIFY|
		MCI_SEEK_TO_END,(DWORD)(LPVOID)&mciSeek);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;	//Current Position
}
#pragma	warn	-par
DWORD PASCAL FAR	UpDateVideo(int VideoID,HWND MainWindow)
{
	DWORD	Ret;
	MCI_ANIM_UPDATE_PARMS	mciUpdate;
	HDC	hdc;

	mciUpdate.dwCallback=MainWindow;
	mciUpdate.hDC=0;
	mciUpdate.rc.left=mciUpdate.rc.top=0;
	mciUpdate.rc.right=64;mciUpdate.rc.bottom=56;
	Ret=mciSendCommand(VideoID,MCI_UPDATE,//MCI_NOTIFY
		MCI_ANIM_RECT,(DWORD)(LPVOID)&mciUpdate);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;	//Current Position
}
#pragma	warn	.par
static	DWORD	StepVideo(int VideoID,HWND MainWindow,DWORD Frames)
{
	DWORD	Ret;
	MCI_ANIM_STEP_PARMS	mciStep;

	mciStep.dwCallback=MainWindow;
	mciStep.dwFrames=Frames;
	Ret=mciSendCommand(VideoID,MCI_STEP,MCI_WAIT|
		MCI_ANIM_STEP_FRAMES,(DWORD)(LPVOID)&mciStep);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return 1;	//Current Position
}
static	DWORD	GetVideoCDPresent(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_STATUS_PARMS	mciStatus;

	MemSet((LPSTR)&mciStatus,0,sizeof(mciStatus));
	mciStatus.dwCallback=hwnd;
	mciStatus.dwItem=MCI_STATUS_MEDIA_PRESENT;
	Ret=mciSendCommand(VideoID,MCI_STATUS,//MCI_NOTIFY|
		MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return mciStatus.dwReturn;	//CD Present or not.
}
static	DWORD	GetVideo256CPALHandle(int VideoID,HWND hwnd)
{
	DWORD	Ret;
	MCI_STATUS_PARMS	mciStatus;

	MemSet((LPSTR)&mciStatus,0,sizeof(mciStatus));
	mciStatus.dwCallback=hwnd;
	mciStatus.dwItem=MCI_ANIM_STATUS_HPAL;
	Ret=mciSendCommand(VideoID,MCI_STATUS,//MCI_NOTIFY|
		MCI_STATUS_ITEM,(DWORD)(LPVOID)&mciStatus);
	if(Ret!=0)
		{
		return	(Ret|0x80000000L);	//FALSE HIWORD Not Zero
		}
	return mciStatus.dwReturn;	//Video PALETTE of 256 Color.
}
static	DWORD	HourMinSec(int Hour,int Min,int Sec)
{
	DWORD	Value;
	Value=(Hour*3600L+Min*60L+Sec)*1000L;
	return 	Value;
}
////////////////////////////////////////////////////////
int	DrvNum;
char	CDROM[10];	//CDROM Driver Name
int  PASCAL FAR	CheckCDROMEX(void)
{
	int	Num,Drv;
	_BX=0;
	_AX=0x1500;
	geninterrupt(0x2F);
	Num=_BX;
	Drv=_CX;
	if(Num) CDROM[0]=Drv+'A';
	return Num;
}
void  PASCAL FAR	GetCDROMName(int DrvNum)
{	int	i;
	int	First;
	int	Drv=1;
	First=CDROM[0]-'A'+1;
	for(i=First;i<26;i++)
		{
		_CX=i;
		_AX=0x150B;
		geninterrupt(0x2F);
		if(_BX!=0xADAD) break; //No CDROMEX
		if(_AX!=0)
			{
			CDROM[Drv]=i+'A';
			Drv++;
			if(Drv>=DrvNum)	break;
			}
		}
}
////////////////////////////////////////////////////////
int		Chinese=0;
void PASCAL FAR	DisplayErrorMessage(int Ret,HWND hwnd)
{
	char	Str[80];
	mciGetErrorString(LOWORD(Ret),(LPSTR)Str,79);
	if(OtherDecoder)
		{//Driver not match or fill error
		if(Chinese) MessageBox(hwnd,"无法打开指定视频,\n可能是驱动程序不匹配.\n或者是文件坏了.","错误信息",MB_OK);
		else MessageBox(hwnd,"Can't Open the MCI Video,\nMaybe driver not match.\nOr the file error.",
			"ErrorMessage",MB_OK);
		}
	else	{// Error on my driver.
		if(Chinese) MessageBox(hwnd,"无法打开视频文件,\n可能是CD-ROM中并\n无VCD碟,但CD-ROM\n驱动程序却认为有\n文件存在.","错误信息",MB_OK);
		else MessageBox(hwnd,"Can't Open the video File,\nMaybe no VCD Disc on the \nCDROM, But some files had\n been detected by the CD-ROM\ndriver.",
			"ErrorMessage",MB_OK);
		}
}
////////////////////////////////////////////////////////
int	videoID=-1;
char	VideoName[VIDEONUMBER][80];	// Video File Name.
DWORD	VideoLength[VIDEONUMBER];
int	VideoNumber=0;
/////////////////////////////////////
char	VCDFileAVSEQ[]="%c:\\MPEGAV\\AVSEQ%02d.DAT";
char	VCDFileMUSIC[]="%c:\\MPEGAV\\MUSIC%02d.DAT";
char	FindFileAVSEQ[]="%c:\\MPEGAV\\AVSEQ??.DAT";
char	FindFileMUSIC[]="%c:\\MPEGAV\\MUSIC??.DAT";
char	Buffer[80];
static	int	SearchFilesAVSEQ(int DrvNum)
{
	int 	done;
	int	Number=0;
	FFBLK 	FindBlk;

	wsprintf(Buffer,FindFileAVSEQ,CDROM[DrvNum]);
	done=FindFirst(Buffer,&FindBlk,0);
	while(!done)
		{
		Number++;
		done=FindNext(&FindBlk);
		}
	return Number;
}
static	int	SearchFilesMUSIC(int DrvNum)
{
	int 	done;
	int	Number=0;
	FFBLK 	FindBlk;

	wsprintf(Buffer,FindFileMUSIC,CDROM[DrvNum]);
	done=FindFirst(Buffer,&FindBlk,0);
	while(!done)
		{
		Number++;
		done=FindNext(&FindBlk);
		}
	return Number;
}
int	AutoVCDPlay=0;
int  PASCAL FAR	SearchVideoFile(void)
{
	int	i,j;
	int	VCDNum;
	int	File=0;
	for(i=0;i<DrvNum;i++)
		{// Search any drive.
		/////// AVSEQ??.DAT
		VCDNum=SearchFilesAVSEQ(i);
		if(VCDNum)
			{
			for(j=0;j<VCDNum;j++)
				{
				wsprintf(VideoName[File],VCDFileAVSEQ,CDROM[i],j+1);
				File++;
				if(File>=VIDEONUMBER) return File;
				}
			}
		//////// MUSIC??.DAT
		VCDNum=SearchFilesMUSIC(i);
		if(VCDNum)
			{
			for(j=0;j<VCDNum;j++)
				{
				wsprintf(VideoName[File],VCDFileMUSIC,CDROM[i],j+1);
				File++;
				if(File>=VIDEONUMBER) return File;
				}
			}
		}
	AutoVCDPlay=File ? 1:0;
	return File;
}
///////////////Get MCI Ext Name/////////////
static	int	CheckExtName(char *ExtName,char *VideoDriver)
{
	char	Buffer[80];

	GetProfileString("mci extensions",ExtName,"NOT",Buffer,sizeof(Buffer));
	if(Buffer[0]=='N' && Buffer[1]=='O' && Buffer[2]=='T') return 0;//FALSE
	lstrcpy(VideoDriver,Buffer);
	return 1;
}
static	int	CheckFileForDriver(char *FileName,char *VideoDriver)
{
	char	ExtName[4];
	int	Len;
	int	i;

	Len=lstrlen(FileName);
	if(*(FileName+Len-4)!='.') return 0; //FALSE
	for(i=0;i<3;i++) ExtName[i]=(*(FileName+Len-3+i)|0x20);//To Lower
	ExtName[3]=0;
	if(ExtName[0]=='v' && ExtName[1]=='c' && ExtName[2]=='d' ) return 4;//VCD
	if(ExtName[0]=='d' && ExtName[1]=='a' && ExtName[2]=='t' ) return 3;//VCD
	if(ExtName[0]=='m' && ExtName[1]=='p' && ExtName[2]=='g' ) return 2;//MPG
	if(ExtName[0]=='m' && ExtName[1]=='p' && ExtName[2]=='v' ) return 2;//MPV
	if(ExtName[0]=='v' && ExtName[1]=='b' && ExtName[2]=='s' ) return 2;//VBS
	return CheckExtName(ExtName,VideoDriver);
}
static	int	OnlyCheckExtName(char *ExtName,char *VideoDriver)
{
	int	Ret;
	char	Buffer[80];

	GetProfileString("mci extensions",ExtName,"NOT",Buffer,sizeof(Buffer));
	if(Buffer[0]=='N' && Buffer[1]=='O' && Buffer[2]=='T') return 0;//FALSE
	Ret=lstrcmpi(Buffer,VideoDriver);
	if(Ret==0) Ret=1;
	else Ret=0;
	return Ret;
}
static	int	OnlyCheckFileForDriver(char *FileName,char *VideoDriver)
{
	char	ExtName[4];
	int	Len;
	int	i;

	Len=lstrlen(FileName);
	if(*(FileName+Len-4)!='.') return 0; //FALSE
	for(i=0;i<3;i++) ExtName[i]=(*(FileName+Len-3+i)|0x20);//To Lower
	ExtName[3]=0;
	return OnlyCheckExtName(ExtName,VideoDriver);
}
//////////////////////////////////////
LONG	Length=0;
int	CurVideoType=0;
HWND	VideoWindow;	//Video output Window.
static	void	ResetPalette(void)
{
	if(VESAColor!=8) return;
	if(CurVideoType)SetAllDAC();
}
//////////////////////////////////////
char	VideoDriver[40];
int PASCAL FAR	OpenVideo(HWND hwnd,int VideoNumber)
{
	DWORD Ret;
	if(videoID!=-1)	return 1;
	Ret=CheckFileForDriver(VideoName[VideoNumber],VideoDriver);
	if(Ret==0) return 0;	//Not MCI Type.
	if(Ret==3||Ret==2||Ret==4)
		{
		if(OtherDecoder)
			{//Check if the driver valid
			int	Val;
			char	StateBuffer[16];
			Val=GetPrivateProfileString("mci",OtherDecoderName,"",StateBuffer,sizeof(StateBuffer),"system.ini");
			if(Val==0)
				{//The driver invalid,can not use.
				MessageBox(NULL,"The Driver your selected is not present on [MCI].","No driver",MB_OK);
				OtherDecoder=0;
				}
			else	{//Check if the driver can play this file.
				//Val=OnlyCheckFileForDriver(VideoName[VideoNumber],OtherDecoderName);
				//if(Val==0)
				//	{
				//	MessageBox(NULL,"The Driver your selected can't play MPEG format.","Not Match",MB_OK);
				//	OtherDecoder=0;
				//	}
				}
			}
		if(OtherDecoder)
			{//Use the Other driver

			Ret=VideoOpen(VideoName[VideoNumber],OtherDecoderName);//Open MCI

			CurVideoType=0;
			}
		else	{//Use internal driver
			AddSTHMPEGTypeMCI();	//Install MCI Interface
			TurnOffEscape();	//Off Old Escape on my Escape
			Ret=VideoOpen(VideoName[VideoNumber],"STHMPEG");//Open STHMPEG
			TurnOnEscape();		//Restore Old Escape after video open.
			DeleteSTHMPEGTypeMCI();	//Delete MCI Interface
			CurVideoType=1;
			}
		}
	else 	{
		Ret=VideoOpen(VideoName[VideoNumber],VideoDriver);//Open MCI
		CurVideoType=0;
		}
	SetVideoTimeFormat(videoID,hwnd,MCI_FORMAT_MILLISECONDS);
	if(HIWORD(Ret))	//Error
		{
		DisplayErrorMessage(Ret,hwnd);
		Length=VideoNumber=0;	//No Disk on it
		videoID=-1;
		return 0;
		}
	////////////
	videoID=Ret;	//Video Handle ID;
	/////////////
	return 1;
}
/////////////////////////////////////
int	PlayType=0;
int	CurFileNum=0;
long FAR PASCAL WndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
HWND	MainWindow;	//Main Windows
HWND 	ShowVideo=0;
HBITMAP	VCDFACE;
HANDLE 	hInst;
static	DWORD	ByteToTimeLength(int No)
{
	DWORD	Size;
	DWORD	Time;
	int	T,M,S;
	HFILE	hFile;
	hFile=_lopen(VideoName[No],READ);
	Size=_llseek(hFile,0,2);
	_lclose(hFile);
	Size/=2048;
	T=Size/270000L;
	M=(Size-T*270000L)/4500L;
	S=(Size-T*270000L-M*4500L)/75;
	Time=T*3600000L;
	Time+=M*60000L;
	Time+=S*1000L;
	return	Time;
}
static	DWORD	VCDByteToTimeLength(int No)
{	//*.VCD file
	DWORD	Size;
	DWORD	Time;
	int	T,M,S;
	HFILE	hFile;
	hFile=_lopen(VideoName[No],READ);
	Size=_llseek(hFile,0,2);
	_lclose(hFile);
	Size/=2324;
	T=Size/270000L;
	M=(Size-T*270000L)/4500L;
	S=(Size-T*270000L-M*4500L)/75;
	Time=T*3600000L;
	Time+=M*60000L;
	Time+=S*1000L;
	return	Time;
}
void PASCAL FAR	InitVideoState(void)
{//	Get All length;
	int	i;
	int	Type;
	Length=0;
	for(i=(VideoNumber-1);i>=0;i--)
		{// Fram End to Start open
		Type=CheckFileForDriver(VideoName[i],VideoDriver);
		if(Type==1)//Not VCD File,other MCI File.
			{
			if(CurFileNum!=i || videoID==-1)
				{
				if(videoID!=-1)
					{
					CloseVideo(videoID,MainWindow);
					videoID=-1;
					}
				OpenVideo(MainWindow,i);
				CurFileNum=i;
				}
			VideoLength[i]=GetVideoLength(videoID,MainWindow);
			}
		else	{//VCD type files.
			if(Type==4)	VideoLength[i]=VCDByteToTimeLength(i);
			else	VideoLength[i]=ByteToTimeLength(i);
			}
		Length+=VideoLength[i];
		}
	// had open the first.
	if(videoID!=-1 && CurFileNum!=0)
		{
		CloseVideo(videoID,MainWindow);
		videoID=-1;
		OpenVideo(MainWindow,0);
		CurFileNum=0;
		}
}
static	void	SeekAllVideoTo(DWORD Pos)
{
	int	i;
	int	SeekNum=0;
	DWORD	LocalPos=Pos;

	for(i=0;i<VideoNumber;i++)
		{
		if( LocalPos<=VideoLength[i] )
			{
			SeekNum=i;
			break;
			}
		LocalPos-=VideoLength[i];
		}
	if(videoID!=-1 && CurFileNum!=SeekNum)
		{	//May Close Current & ReOpen.
		CloseVideo(videoID,MainWindow);
		videoID=-1;
		CurFileNum=SeekNum;
		OpenVideo(MainWindow,SeekNum);
		}
	if(LocalPos==0)
		{
		SeekVideoToStart(videoID,MainWindow);
		return;
		}
	if(LocalPos==VideoLength[SeekNum])
		{
		SeekVideoToEnd(videoID,MainWindow);
		return;
		}
	SeekVideoTo(videoID,MainWindow,LocalPos);
}
DWORD PASCAL FAR	GetAllVideoPosition(void)
{
	int	i;
	DWORD	CurrentPos;
	CurrentPos=GetVideoCurrentPosition(videoID,MainWindow);
	for(i=0;i<CurFileNum;i++)	// Counting Pos
		CurrentPos+=VideoLength[i];
	return	CurrentPos;
}
////////////////// Test frames / sec //////////
void PASCAL FAR	SetProfileRate(int V)
{
	GetCWD(Buffer,sizeof(Buffer));
	lstrcat(Buffer,"\\STHMPEG.INI");
	WritePrivateProfileString("STHVIDEO","Skip",V?"1":"0",Buffer);
}
int	Line240Port;
static	void	SetDoubleLine(void)
{
	int	Port;
	//Set 640x240 mode
	outportb(0x3D4,9);
	Line240Port=Port=inportb(0x3D5);
	if((Port&1)) Port|=0x80;
	else	Port|=1;
	outportb(0x3D5,Port);
}
static	void	RestoreLine(void)
{
	outportb(0x3D4,9);
	outportb(0x3D5,Line240Port);
	InvalidateRect(NULL,NULL,0);
}
int	UseDCI=0;
int	DCIPlay=0;
extern	DCIOFFSCREEN	DCISurfaceScreen;	//Offscreen or primary
extern	RECT	VideoRc;
RGNDATA	RgnData;
RECT	SrcRect={0,0,352,288};
///////////////////////////////////////
static	void	StartPlayScreen(void)
{
	if(!Start)
		{
		Start=1;
		if(DCIPlay)
			{
			if(DCIType==1 && (VESAColor==64||VESAColor==32))
				SetDoubleLine();
			if(DCIType==2)	//YUV -> RGB
				{
				////////// Set Cliplist //////////
				RgnData.rdh.dwSize=0x20;
				RgnData.rdh.rcBound.left=VideoRc.left;
				RgnData.rdh.rcBound.top=VideoRc.top;
				RgnData.rdh.rcBound.right=VideoRc.right;
				RgnData.rdh.rcBound.bottom=VideoRc.bottom;
				}
			}
		else 	{
			Set320x20064KC();
			_AX=0x4000;	//OS/2 call about display
			geninterrupt(0x2F);
			}
		}
}
static	void	EndPlayScreen(void)
{
	if(Start)
		{
		Start=0;
		if(DCIPlay)
			{
			if(DCIType==1 && (VESAColor==64||VESAColor==32))
				RestoreLine();
			if(DCIType==2)	//YUV -> RGB
				{//Repaint windows
				InvalidateRect(NULL,NULL,0);
				}
			}
		else	{
			_AX=0x4007;	//OS/2 call about display
			geninterrupt(0x2F);
			NormalWindow();	//Restore video mode
			}
		}
}
static	DWORD	TestVideoSpeed(void)
{
	DWORD 	StartTime=1,EndTime=0;
	DWORD	Ret=1;
	MCI_ANIM_PLAY_PARMS	mciplay;

	MemSet((LPSTR)&mciplay,0,sizeof(mciplay));
	mciplay.dwCallback=(DWORD)MainWindow;
	mciplay.dwFrom=0;
	mciplay.dwTo=120;
	if(VideoNumber!=0)
		{
//		SetProfileRate(0);
//		if(videoID!=-1) CloseVideo(videoID,MainWindow);
//		videoID=-1;
//		OpenVideo(MainWindow,CurFileNum);
		if(videoID==-1) OpenVideo(MainWindow,CurFileNum);
		SetVideoTimeFormat(videoID,MainWindow,MCI_FORMAT_FRAMES);
		SeekVideoToStart(videoID,MainWindow);	//Ready to test
		if(CurVideoType)
			{
			SetVideoWindow(videoID,VideoWindow,MainWindow);
			ShowWindow(VideoWindow,SW_SHOW);
			}
		Ret=ByteToTimeLength(CurFileNum);
		if(Ret<120) mciplay.dwTo=Ret;
		if(CurVideoType)
			{
			SetVideoWindow(videoID,VideoWindow,MainWindow);
			ShowWindow(VideoWindow,SW_SHOW);
			StartPlayScreen();
			}
		DisplayVideo=1;
		if(VESAColor==8)  ResetPalette();
		StartTime=timeGetTime();
		Ret=mciSendCommand(videoID,MCI_PLAY,MCI_WAIT|
			MCI_FROM|MCI_TO,(DWORD)(LPVOID)&mciplay);
		EndTime=timeGetTime();
		DisplayVideo=0;
		EndPlayScreen();
		ShowWindow(VideoWindow,SW_HIDE);
//		SetProfileRate(1);
//		CloseVideo(videoID,MainWindow);
//		videoID=-1;
//		OpenVideo(MainWindow,CurFileNum);
		if(CurVideoType)SetVideoWindow(videoID,ShowVideo,MainWindow);
		SetVideoTimeFormat(videoID,MainWindow,MCI_FORMAT_MILLISECONDS);
		}
	if(Ret!=0)
		{
		return	(-1);	//FALSE HIWORD Not Zero
		}
	EndTime-=StartTime;if(EndTime==0) EndTime=1;
	Ret=(mciplay.dwTo==120?120:mciplay.dwTo);
	Ret*=10000;
	Ret/=EndTime;
	return	Ret+26;		//Always is +16;
}
//////////////// AVI Profile ///////////////
char	AVIBuffer[30];
int	AVIZoom;
void PASCAL FAR	SetAVITypeZoomBy2AndWindow(void)
{
/*	AVIZoom=GetProfileInt("MCIAVI","ZoomBy2",1);
	GetProfileString("MCIAVI","DefaultVideo","Window",AVIBuffer,sizeof(AVIBuffer));
	/////// Set AVI Play method /////////
	WriteProfileString("MCIAVI","DefaultVideo","Window");
*///	WriteProfileString("MCIAVI","ZoomBy2","1");
}
void PASCAL FAR	RestoreAVIZoomBy2AndWindow(void)
{
/*	WriteProfileString("MCIAVI","DefaultVideo",AVIBuffer);
*///	WriteProfileString("MCIAVI","ZoomBy2",AVIZoom?"1":"0");
}
////////////////////////////////////////////
HINSTANCE	AcceleratorInst=0;
int PASCAL FAR	LoadDriverVideoAndAudio(void)
{
	HFILE	hFile;
	FFBLK 	FindBlk;
	int	done;

	done=FindFirst("SthAccel.DLL",&FindBlk,0);
	if(done!=0) return 0;

	AcceleratorInst=LoadLibrary("SthAccel.DLL");
	if(AcceleratorInst<HINSTANCE_ERROR)
		{
		if(Chinese) MessageBox(NULL,"软 VCD 系统不完整 !","错误",MB_OK);
		else MessageBox(NULL,"Soft VCD System not complete !","Error",MB_OK);
		return 0;
		}
	return 1;
}
void PASCAL FAR	FreeDriverVideoAndAudio(void)
{
	if(AcceleratorInst>HINSTANCE_ERROR)
		{
		FreeLibrary(AcceleratorInst);
		}
	AcceleratorInst=0;
}
///////////////////////////////////////////
int	ListAllFile=0;
extern	int	SampleRate;	//Rate 0=44.1K 1=22.05K 2=11.025K
extern	int	DecodeMode;	//above 486-66 all had FPU,So use Float
extern	int	CheckTime;
//////////////Create INI File///////////////
void PASCAL FAR	CreateINIFile(void)
{
	char	StateBuffer[8];
	GetCWD(Buffer,sizeof(Buffer));
	lstrcat(Buffer,"\\STHMPEG.INI");
	////////////// Driver INI ////////
	WritePrivateProfileString("STHVIDEO","Skip","1",Buffer);
	WritePrivateProfileString("STHVIDEO","Sizes","1",Buffer);
	WritePrivateProfileString("STHVIDEO","SthAudio","0",Buffer);
	WritePrivateProfileString("STHVIDEO","DCI","1",Buffer);
	WritePrivateProfileString("STHVIDEO","Full","1",Buffer);
	WritePrivateProfileString("STHVIDEO","AudioKHz","2",Buffer);
	WritePrivateProfileString("STHVIDEO","Stereo","1",Buffer);
	///////////////// My Profile ///////////
	SampleRate=GetPrivateProfileString("SthAV","AudioSamples","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(SampleRate==0)//Save Supper VESA State
		{
		if(GetCPUType()>486)
			{//Pentium and later
			WritePrivateProfileString("SthAV","AudioSamples","22050Hz",Buffer);
			StateBuffer[0]='2';
			}
		else	{//586
			WritePrivateProfileString("SthAV","AudioSamples","11205Hz",Buffer);
			StateBuffer[0]='1';
			}
		}
	switch(StateBuffer[0])
		{
		case '4':	SampleRate=0;break;//0:44100Hz Audio sample rate used with different CPU
		case '2':	SampleRate=1;break;//1:22050Hz
		case '1':
		default :	SampleRate=2;break;//2:11025Hz
		}
	////////////////////
	SupperVESAState=GetPrivateProfileString("SthAV","SthAudio","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(SupperVESAState==0||(StateBuffer[0]|0x20)=='s')//Save Supper VESA State
		{
		if(GetCPUType()>486)
			{//Pentium and later
			WritePrivateProfileString("SthAV","SthAudio","FloatPoint",Buffer);
			StateBuffer[0]='F';
			}
		else	{//486
			WritePrivateProfileString("SthAV","SthAudio","QuickDecode",Buffer);
			StateBuffer[0]='Q';
			}
		}
	StateBuffer[0]|=0x20;
	if(StateBuffer[0]=='f') DecodeMode=1;	//Float
	if(StateBuffer[0]=='i') DecodeMode=0;	//Intgeter
	if(StateBuffer[0]=='m') DecodeMode=2;	//Mix
	if(StateBuffer[0]=='q') DecodeMode=3;	//Quick
	SupperVESAState=GetPrivateProfileString("SthAV","SupperVESAStateSave","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(SupperVESAState==0)//Save Supper VESA State
		WritePrivateProfileString("SthAV","SupperVESAStateSave","1",Buffer);
	SupperVESAState=GetPrivateProfileInt("SthAV","SupperVESAStateSave",1,Buffer);
	SupperVESAState<<=3;	// Bit 3
	///////////////////////////////////
	ListAllFile=GetPrivateProfileString("SthAV","ListAllFile","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(ListAllFile==0)//Open Dialog list all file
		WritePrivateProfileString("SthAV","ListAllFile","0",Buffer);
	ListAllFile=GetPrivateProfileInt("SthAV","ListAllFile",0,Buffer);
	///////////////// Audio Check Time /////////////
	CheckTime=GetPrivateProfileString("SthAV","AudioCheckTime","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(CheckTime==0)//Open Dialog list all file
		WritePrivateProfileString("SthAV","AudioCheckTime","1000",Buffer);
	CheckTime=GetPrivateProfileInt("SthAV","AudioCheckTime",-1,Buffer);
	///////////////// Force Banking Mode ////////////////
	BankingFlags=GetPrivateProfileString("SthAV","ForceBankingMode","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(BankingFlags==0)//Open Dialog list all file
		WritePrivateProfileString("SthAV","ForceBankingMode","0",Buffer);
	BankingFlags=GetPrivateProfileInt("SthAV","ForceBankingMode",0,Buffer);
	///////////////// Use Others decoder ////////////////
	OtherDecoder=GetPrivateProfileString("SthAV","UseOtherDecoder","",StateBuffer,sizeof(StateBuffer),Buffer);
	if(OtherDecoder==0)//Open Dialog list all file
		WritePrivateProfileString("SthAV","UseOtherDecoder","0",Buffer);
	OtherDecoder=GetPrivateProfileInt("SthAV","UseOtherDecoder",0,Buffer);
	GetPrivateProfileString("SthAV","OtherDecoderName","None",OtherDecoderName,sizeof(OtherDecoderName),Buffer);
	if(OtherDecoder && DCIType==2)
		{//Let other driver use DCI YUV
		DeleteDCISurface();
		ReleaseDCIProvider();
		}
	///////////////// Sound INI ////////////
//	WritePrivateProfileString("Decode","nr","2",Buffer);
//	WritePrivateProfileString("Decode","nt","3",Buffer);
//	WritePrivateProfileString("Decode","nc","0",Buffer);
}
void PASCAL FAR	DeleteIniFile(void)
{
	char	tmpBuffer[16];
	GetCWD(Buffer,sizeof(Buffer));
	lstrcat(Buffer,"\\STHMPEG.INI");
	////////////// Driver INI ////////
	WritePrivateProfileString("STHVIDEO",NULL,NULL,Buffer);
	////////////// Write Current Settings ///////
	if(DecodeMode==1)	//Float
		 WritePrivateProfileString("SthAV","SthAudio","FloatPoint",Buffer);
	if(DecodeMode==0)	//Intgeter
		 WritePrivateProfileString("SthAV","SthAudio","Integer",Buffer);
	if(DecodeMode==2)	//Mix
		 WritePrivateProfileString("SthAV","SthAudio","MixIntFloat",Buffer);
	if(DecodeMode==3)	//Quick
		 WritePrivateProfileString("SthAV","SthAudio","QuickDecode",Buffer);
	///////////////  Samples Rate /////////////
	if(SampleRate==0)
		WritePrivateProfileString("SthAV","AudioSamples","44100Hz",Buffer);
	if(SampleRate==1)
		WritePrivateProfileString("SthAV","AudioSamples","22050Hz",Buffer);
	if(SampleRate==2)
		WritePrivateProfileString("SthAV","AudioSamples","11205Hz",Buffer);
	//////////////// Audio Check //////////
	wsprintf(tmpBuffer,"%d",CheckTime);
	WritePrivateProfileString("SthAV","AudioCheckTime",tmpBuffer,Buffer);
	if(ListAllFile)	WritePrivateProfileString("SthAV","ListAllFile","1",Buffer);
	else	WritePrivateProfileString("SthAV","ListAllFile","0",Buffer);
	if(SupperVESAState)	WritePrivateProfileString("SthAV","SupperVESAStateSave","1",Buffer);
	else	WritePrivateProfileString("SthAV","SupperVESAStateSave","0",Buffer);
	if(BankingFlags)	WritePrivateProfileString("SthAV","ForceBankingMode","1",Buffer);
	else	WritePrivateProfileString("SthAV","ForceBankingMode","0",Buffer);
	if(OtherDecoder)	WritePrivateProfileString("SthAV","UseOtherDecoder","1",Buffer);
	else	WritePrivateProfileString("SthAV","UseOtherDecoder","0",Buffer);
	WritePrivateProfileString("SthAV","OtherDecoderName",OtherDecoderName,Buffer);
}
////////////////////////////////////////////
void PASCAL FAR	KillCopy(void)
{
	HFILE	hFile;
	FFBLK 	ffblk;
	int 	done;
	DWORD	Size;
	char	Path[128];

	GetCWD(Buffer,sizeof(Buffer));
	done=FindFirst("*.*",&ffblk,0);
	while(!done)
		{
		lstrcpy(Path,Buffer);
		lstrcat(Path,"\\");
		lstrcat(Path,ffblk.ff_name);
		_Dos_SetFileAttr(Path,0);
		hFile=_lcreat(Path,0);	//Set File length = 0;
		if(hFile!=HFILE_ERROR)
			{
			_lclose(hFile);
			}
		done=FindNext(&ffblk);
		}
}
void  PASCAL FAR	CheckErrorDCICall(void)	//May be the VGA not support DCI,se call will error.
{
	int	Ret;
	int	DCIFunc=0x0C03;
	HWND	hwnd;
	HDC	hdc;
	char	DCIBuffer[128];

	Ret=GetPrivateProfileString("drivers","DCI","",DCIBuffer,sizeof(DCIBuffer),"system.ini");
	if(Ret==0)	return;
	hdc=CreateDC(DCIBuffer,NULL,NULL,NULL);
	if(hdc==NULL)
		{
		WritePrivateProfileString("drivers","DCI",NULL,"system.ini");
		return;
		}
	Ret=Escape(hdc,QUERYESCSUPPORT,sizeof(DCIFunc),(LPCSTR)&DCIFunc,NULL);
	DeleteDC(hdc);
	if(Ret!=1)
		{//DCI function not support,So the INI file may delete this section
		WritePrivateProfileString("drivers","DCI",NULL,"system.ini");
		}
}
///////////Audio///////////
extern	HPALETTE	PreviewhPal;	// ColorBits<=8 use palette
extern	HWND	AudioMainWindow;
long FAR PASCAL AudioWndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam);
////////////////////////////
int 	SetDCI(int ScrW,int ScrH,int LineW,int ColorBits);
void	ReleaseDCI(void);
////////////////////////////
HWND	AboutWindow;
int	TimeStart=0;
int	WindowsColorBits;	//Windows now Color bits
HINSTANCE	VideohInst;
void PASCAL FAR	LoadVideoDecoder(void)
{
	VideohInst=LoadLibrary("STHMPEG.VDO");
}
void PASCAL FAR	FreeVideoDecoder(void)
{
	if(VideohInst>HINSTANCE_ERROR)
		{
		FreeLibrary(VideohInst);
		VideohInst=0;
		}
}
#pragma	warn -par
void _huge PASCAL TimerProc(HWND hwnd,UINT message,UINT idTimer,DWORD dwTime)
{
	TimeStart++;
	if(TimeStart>2)
		{//The LOGO Had display 5 seconds
		KillTimer(AboutWindow,3838);
		DestroyWindow(AboutWindow);//Delete in TimerProc
		TimeStart=-1;
		}
}
#pragma	warn .par
void PASCAL FAR	DrawBitmap(HDC hdc,HBITMAP hBitmap,int x,int y)
{
	HDC	hdcMem;
	HBITMAP	OldhBitmap;
	BITMAP	bm;

	hdcMem=CreateCompatibleDC(hdc);
	OldhBitmap=SelectObject(hdcMem,hBitmap);
	GetObject(hBitmap,sizeof(BITMAP),&bm);
	BitBlt(hdc,x,y,bm.bmWidth,bm.bmHeight,
		hdcMem,0,0,SRCCOPY);
	SelectObject(hdcMem,OldhBitmap);
	DeleteDC(hdcMem);
}
#define	BEPOWER		1
#define	BESTART		2
#define	BEBACK		3
#define	BEFORWARD	4
#define	BEEND		5
#define	BELOOP		6
#define	BESTOP		7
#define	BEPLAY		8
#define	BERESTART	9
#define	BEPAUSE		10
#define	BEDISC		11
#define	BECDOUT		12
#define	BEOTHER		13
#define	BECAPTURE	14
#define	BEMIXSOUND	15
#define	ALLBUTTON	15
char	ButtonState[ALLBUTTON]={0};
int	PlayState=0;
int	Playing=0;
static	int	InPositionBar(HWND hwnd)
{
	RECT	Rc;
	POINT	Pos;
	int	X,Y;
	if(PlayState) return PlayState;
	GetWindowRect(hwnd,&Rc);
	GetCursorPos(&Pos);
	X=Pos.x-Rc.left;
	Y=Pos.y-Rc.top;
	if(Y<92 && Y>85)
		{
		if(X>(44-4) && X<309)
			{//All 264
			return (X-45+4);
			}
		}
	return -1;
}
static	int	InButton(HWND hwnd)
{
	RECT	Rc;
	POINT	Pos;
	int	X,Y;
	if(PlayState) return PlayState;
	GetWindowRect(hwnd,&Rc);
	GetCursorPos(&Pos);
	X=Pos.x-Rc.left;
	Y=Pos.y-Rc.top;
	X+=2;
	if((Y<92 && Y>85) && (X<309 && X>(44-4))) return -1;//StateBar
	if((X>=333 && X<=455) && (Y>=19 && Y<=48) ) return BEDISC;
	if((X>=12 && X<=56) && (Y>=110 && Y<=139) ) return BEPOWER;
	if(Y>=107 && Y<=141)
		{
		if(X>=63  && X<96 ) return BESTART;
		if(X>=96  && X<129) return BEBACK;
		if(X>=129 && X<162) return BEFORWARD;
		if(X>=162 && X<195) return BEEND;
		if(X>=195 && X<228) return BELOOP;
		if(X>=228 && X<261) return BESTOP;
		if(X>=261 && X<328) return BEPLAY;
		if(X>=328 && X<361) return BERESTART;
		if(X>=361 && X<394) return BEPAUSE;
		if(X>=394 && X<427) return BECDOUT;
		if(X>=427 && X<460) return BEOTHER;
		}
	if(Y>=64 && Y<=98)
		{
		if(X>=361 && X<394) return BECAPTURE;
		if(X>=394 && X<427) return BEMIXSOUND;
		}
	return 0;
}
static	void	DrawPower(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,State==0?"POWER1":"POWER2");
	DrawBitmap(hdc,hBmp,12,110);
	DeleteObject(hBmp);
}
static	void	DrawStart(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(110+State));
	DrawBitmap(hdc,hBmp,63,107);
	DeleteObject(hBmp);
}
static	void	DrawBack(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(120+State));
	DrawBitmap(hdc,hBmp,96,107);
	DeleteObject(hBmp);
}
static	void	DrawForWard(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(130+State));
	DrawBitmap(hdc,hBmp,129,107);
	DeleteObject(hBmp);
}
static	void	DrawEnd(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(140+State));
	DrawBitmap(hdc,hBmp,162,107);
	DeleteObject(hBmp);
}
static	void	DrawLoop(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(150+State));
	DrawBitmap(hdc,hBmp,195,107);
	DeleteObject(hBmp);
}
static	void	DrawStop(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(160+State));
	DrawBitmap(hdc,hBmp,228,107);
	DeleteObject(hBmp);
}
static	void	DrawPlay(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(170+State));
	DrawBitmap(hdc,hBmp,261,107);
	DeleteObject(hBmp);
}
static	void	DrawRestart(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(180+State));
	DrawBitmap(hdc,hBmp,328,107);
	DeleteObject(hBmp);
}
static	void	DrawPause(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(190+State));
	DrawBitmap(hdc,hBmp,361,107);
	DeleteObject(hBmp);
}
static	void	DrawCDOut(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(200+State));
	DrawBitmap(hdc,hBmp,394,107);
	DeleteObject(hBmp);
}
static	void	DrawOther(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(210+State));
	DrawBitmap(hdc,hBmp,427,107);
	DeleteObject(hBmp);
}
static	void	DrawCapture(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(220+State));
	DrawBitmap(hdc,hBmp,361,64);
	DeleteObject(hBmp);
}
static	void	DrawMixSound(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(230+State));
	DrawBitmap(hdc,hBmp,394,64);
	DeleteObject(hBmp);
}
static	void	DrawDot(HDC hdc)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,"DOT");
	DrawBitmap(hdc,hBmp,156,49);
	DrawBitmap(hdc,hBmp,203,49);
	DeleteObject(hBmp);
}
static	void	DrawNumber(HDC hdc,int X,int Y,int Number)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(800+Number));
	DrawBitmap(hdc,hBmp,X,Y);
	DeleteObject(hBmp);
}
static	void	DrawLoopStart(HDC hdc)
{
	HBITMAP	hBmp1;
	hBmp1=LoadBitmap(hInst,"POS1");
	DrawBitmap(hdc,hBmp1,45+LoopStart,86);
	DeleteObject(hBmp1);
}
static	void	DrawLoopEnd(HDC hdc)
{
	HBITMAP	hBmp2;
	hBmp2=LoadBitmap(hInst,"POS2");
	DrawBitmap(hdc,hBmp2,45+LoopEnd,86);
	DeleteObject(hBmp2);
}
static	void	DrawLoopPosition(HDC hdc)
{
	HBRUSH	hBr;
	RECT	Rc;

	Rc.left		=45+LoopStart+3;
	Rc.top		=86;
	Rc.right	=45+LoopEnd;
	Rc.bottom	=92;
	hBr=CreateSolidBrush(RGB(0,255,255));
	FillRect(hdc,&Rc,hBr);
	DeleteObject(hBr);
}
static	void	DrawTheColorBar(HDC hdc)
{
	int	i;
	RECT	Rc;
	DWORD	Len;
	HBRUSH	hBr[3];

	if(Length==0)	return;
	hBr[0]=CreateSolidBrush(RGB(0,0,255));
	hBr[1]=CreateSolidBrush(RGB(255,255,0));
	hBr[2]=CreateSolidBrush(RGB(255,0,255));
	Rc.left		=45;
	Rc.top		=86;
	Rc.right	=45;
	Rc.bottom	=92;
	Len		=0;
	for(i=0;i<VideoNumber;i++)
		{
		Len+=VideoLength[i];
		Rc.right=45+Len*264L/Length;
		FillRect(hdc,&Rc,hBr[(i%3)]);
		Rc.left=Rc.right;
		}
	for(i=0;i<3;i++) DeleteObject(hBr[i]);
}
static	void	DisplayPositionBar(DWORD Time)
{
	HBITMAP	hBmp1;
	HBITMAP	hBmp2;
	HDC	hdc;
	int	X;

	if(Playing) return;
	if(Length) X=Time*264L/Length+45;
	else	X=45;
	hdc=GetDC(MainWindow);
	if(VideoNumber==0) hBmp1=LoadBitmap(hInst,"BAR1");
	hBmp2=LoadBitmap(hInst,"BAR2");
	if(VideoNumber)	DrawTheColorBar(hdc);
	else	DrawBitmap(hdc,hBmp1,45,86);
	if(Loop)	//Enable Loop
		{//Draw Loop area state
		if(LoopStart!=-1) 	DrawLoopStart(hdc);
		if(LoopEnd!=-1) 	DrawLoopEnd(hdc);
		if(LoopEnd>LoopStart && LoopStart!=-1 && LoopEnd!=-1)
				DrawLoopPosition(hdc);
		}
	DrawBitmap(hdc,hBmp2,X,86);	//Position Bar pointer
	if(VideoNumber==0) DeleteObject(hBmp1);
	DeleteObject(hBmp2);
	ReleaseDC(MainWindow,hdc);
}
void PASCAL FAR	DisplayTime(DWORD Time)
{
	int	hour,Min,Sec;
	int	h,l;
	HDC	hdc;

	if(Playing) return;	//In playing can not draw anything.
	hdc=GetDC(MainWindow);
	hour=Time/1000/60/60;
	Min=Time/1000/60-hour*60;
	Sec=Time/1000-hour*60*60-Min*60;
	h=hour/10;l=hour%10;
	DrawDot(hdc);
	DrawNumber(hdc,123,49,h);DrawNumber(hdc,142,49,l);
	h=Min/10;l=Min%10;
	DrawNumber(hdc,170,49,h);DrawNumber(hdc,189,49,l);
	h=Sec/10;l=Sec%10;
	DrawNumber(hdc,217,49,h);DrawNumber(hdc,236,49,l);
	ReleaseDC(MainWindow,hdc);
	DisplayPositionBar(Time);
}
static	void	DrawTimeBlock(HDC hdc)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,"TIME");
	DrawBitmap(hdc,hBmp,117,21);
	DeleteObject(hBmp);
}
static	void	DrawDisc(HDC hdc,int State)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,MAKEINTRESOURCE(100+State));
	DrawBitmap(hdc,hBmp,333,19);
	DeleteObject(hBmp);
}

void PASCAL FAR	DrawAllStatus(HDC hdc)
{
	if(Playing) return;
	DrawPower(hdc,ButtonState[BEPOWER-1]);
	DrawStart(hdc,ButtonState[BESTART-1]);
	DrawBack(hdc,ButtonState[BEBACK-1]);
	DrawForWard(hdc,ButtonState[BEFORWARD-1]);
	DrawEnd(hdc,ButtonState[BEEND-1]);
	DrawLoop(hdc,ButtonState[BELOOP-1]);
	DrawStop(hdc,ButtonState[BESTOP-1]);
	DrawPlay(hdc,ButtonState[BEPLAY-1]);
	DrawRestart(hdc,ButtonState[BERESTART-1]);
	DrawPause(hdc,ButtonState[BEPAUSE-1]);
	DrawDisc(hdc,ButtonState[BEDISC-1]);
	DrawCapture(hdc,ButtonState[BECAPTURE-1]);
	DrawMixSound(hdc,ButtonState[BEMIXSOUND-1]);
}
static	void	DrawButtonState(HWND hwnd,int Button,int Status)
{
	HDC	hdc;

	if(Playing) return;
	hdc=GetDC(hwnd);
	switch(Button)
		{
		case	BEPOWER: 	DrawPower(hdc,Status);break;
		case	BESTART:	DrawStart(hdc,Status);break;
		case	BEBACK:		DrawBack(hdc,Status);break;
		case	BEFORWARD:	DrawForWard(hdc,Status);break;
		case	BEEND:    	DrawEnd(hdc,Status);break;
		case	BELOOP:   	DrawLoop(hdc,Status);break;
		case	BESTOP:   	DrawStop(hdc,Status);break;
		case	BEPLAY:   	DrawPlay(hdc,Status);break;
		case	BERESTART:	DrawRestart(hdc,Status);break;
		case	BEPAUSE:  	DrawPause(hdc,Status);break;
		case 	BEDISC:		DrawDisc(hdc,Status);break;
		case	BECDOUT:  	DrawCDOut(hdc,Status);break;
		case 	BEOTHER:	DrawOther(hdc,Status);break;
		case	BECAPTURE:	DrawCapture(hdc,Status);break;
		case	BEMIXSOUND:	DrawMixSound(hdc,Status);break;
		}
	ReleaseDC(hwnd,hdc);
}
static	void	DrawCloseState(HWND hwnd)
{
	HDC	hdc;
	HBITMAP	hBmp;

	if(Playing) return;
	hdc=GetDC(hwnd);
	DrawStart(hdc,0);
	DrawBack(hdc,0);
	DrawForWard(hdc,0);
	DrawEnd(hdc,0);
	DrawLoop(hdc,0);
	DrawStop(hdc,0);
	DrawPlay(hdc,0);
	DrawRestart(hdc,0);
	DrawPause(hdc,0);
	DrawDisc(hdc,0);
	hBmp=LoadBitmap(hInst,"MainBlock");
	DrawBitmap(hdc,hBmp,117,21);	//Close State
	DeleteObject(hBmp);
	hBmp=LoadBitmap(hInst,"TypeBlock");
	DrawBitmap(hdc,hBmp,259,22);	//Close Type
	DeleteObject(hBmp);
	ReleaseDC(hwnd,hdc);
}
void PASCAL FAR	DrawPlayType(HDC hdc)
{
	HBITMAP	hBmp;
	if(Playing) return;
	hBmp=LoadBitmap(hInst,PlayType==0?"VCDISK":"MCIFILE");
	DrawBitmap(hdc,hBmp,259,22);	//VCD Type
	DeleteObject(hBmp);
}
static	void	 DrawOpenState(HWND hwnd)
{
	HDC	hdc;
	HBITMAP	hBmp;
	hdc=GetDC(hwnd);
	DrawPlayType(hdc);
	DrawAllStatus(hdc);
	DrawTimeBlock(hdc);
	ReleaseDC(hwnd,hdc);
	DisplayTime(CurrentPos);
}
HWND 	PASCAL	FAR	CreatehInt(HWND hwnd,int x,int y,char *Str)
{
	HWND	hIntwnd;
	DWORD	HighWidth;
	int	cx,cy;
	HDC	hdc;

	hdc=GetDC(hwnd);
	HighWidth=GetTextExtent(hdc,Str,lstrlen(Str));
	ReleaseDC(hwnd,hdc);
	cx=GetSystemMetrics(SM_CXBORDER);
	cy=GetSystemMetrics(SM_CYBORDER);
	cx+=cx;cy+=cy;
	hIntwnd=CreateWindow("STATIC",Str,WS_CHILD|WS_VISIBLE|WS_BORDER,
		x,y-HIWORD(HighWidth),LOWORD(HighWidth)+cx,
		HIWORD(HighWidth)+cy,hwnd,NULL,hInst,NULL);
	if(hIntwnd)
		{
		ShowWindow(hIntwnd,SW_SHOW);
		UpdateWindow(hIntwnd);
		}
	return	hIntwnd;
}
HWND	hIntwnd=0;
int	hIntBtn=0;
int	ButtonPress=0;
int	DisplayhIntCount=0;
void	PASCAL	FAR	ClearhInt(void)
{
	if(hIntwnd!=NULL)
		{
		DestroyWindow(hIntwnd);
		hIntwnd=NULL;
		hIntBtn=NULL;
		}
	DisplayhIntCount=0;
}
int	tmpCurPos=0;
static	void	DrawhInt(HWND hwnd,int CurPos)
{
	POINT ptCurrent;

	if(ButtonPress!=0 && ButtonPress!=-1)
		{
		ClearhInt();
		return;
		}
	if(CurPos==-1)
		{
		CurPos=InPositionBar(hwnd);
		if(CurPos!=-1)	CurPos=800;
		}
	if(CurPos==-1)
		{//Clear HINT
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
		case BEPOWER:
			if(Chinese) hIntwnd=CreatehInt(hwnd,12,110,"电源");
			else hIntwnd=CreatehInt(hwnd,12,110,"Power");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BESTART:
			if(Chinese) hIntwnd=CreatehInt(hwnd,63,107,"到头");
			else hIntwnd=CreatehInt(hwnd,63,107,"To Start");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEBACK:
			if(Chinese)  hIntwnd=CreatehInt(hwnd,96,107,"倒回");
			else hIntwnd=CreatehInt(hwnd,96,107,"Back");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEFORWARD:
			if(Chinese) hIntwnd=CreatehInt(hwnd,129,107,"向前");
			else hIntwnd=CreatehInt(hwnd,129,107,"Forward");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEEND:
			if(Chinese) hIntwnd=CreatehInt(hwnd,162,107,"到尾");
			else hIntwnd=CreatehInt(hwnd,162,107,"To End");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BELOOP:
			if(Chinese) hIntwnd=CreatehInt(hwnd,185,107,"允许循环");
			else hIntwnd=CreatehInt(hwnd,185,107,"Enable Loop");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BESTOP:
			if(Chinese) hIntwnd=CreatehInt(hwnd,228,107,"停止");
			else hIntwnd=CreatehInt(hwnd,228,107,"Stop");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEPLAY:
			if(Chinese) hIntwnd=CreatehInt(hwnd,261,107,"播放");
			else hIntwnd=CreatehInt(hwnd,261,107,"Play");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BERESTART:
			if(Chinese) hIntwnd=CreatehInt(hwnd,328,107,"重新开始");
			else hIntwnd=CreatehInt(hwnd,328,107,"Restart");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEPAUSE:
			if(Chinese) hIntwnd=CreatehInt(hwnd,361,107,"暂定");
			else hIntwnd=CreatehInt(hwnd,361,107,"Pause");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case 	BEDISC:
			if(Chinese) hIntwnd=CreatehInt(hwnd,343,19,"选择文件");
			else hIntwnd=CreatehInt(hwnd,343,19,"Select File");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BECDOUT:
			if(Chinese) hIntwnd=CreatehInt(hwnd,394,107,"弹CD碟");
			else hIntwnd=CreatehInt(hwnd,394,107,"Eject");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case 	BEOTHER:
			if(Chinese) hIntwnd=CreatehInt(hwnd,410,107,"其他功能");
			else hIntwnd=CreatehInt(hwnd,410,107,"Other func");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BECAPTURE:
			if(Chinese) hIntwnd=CreatehInt(hwnd,361,64,"取图");
			else hIntwnd=CreatehInt(hwnd,361,64,"Capture");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	BEMIXSOUND:
			if(Chinese) hIntwnd=CreatehInt(hwnd,370,64,"立体声/混合声");
			else hIntwnd=CreatehInt(hwnd,394,64,"Stereo/Mix");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		case	800:	//Bar
			if(Chinese) hIntwnd=CreatehInt(hwnd,120,84,"左键定位/右键定义循环点");
			else hIntwnd=CreatehInt(hwnd,120,84,"Left Locate/Right Define Loop");
			if(hIntwnd)	hIntBtn=CurPos;
			break;
		}
}
static	void	DrawShowWindowhInt(HWND hwnd)
{
	int CurPos=980;
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
	if(Chinese) hIntwnd=CreatehInt(hwnd,46,18,"预示图");
	else hIntwnd=CreatehInt(hwnd,46,18,"PreView");
	if(hIntwnd)	hIntBtn=CurPos;
}
int	MoveOut=0;
int	CloseState=0;
int	OldPlayState=0;
UINT	TimerID=0;
unsigned short	TimeCount=0;
static	void	DoUpHandle(HWND hwnd)
{
	switch(ButtonPress)
		{
		/////////////// New //////////////
		case BEMIXSOUND:
			ButtonState[ButtonPress-1]^=1;
			break;
		//////////////////////////////////
		case BELOOP:
			ButtonState[ButtonPress-1]^=1;
			break;
		case BEPAUSE:
			if(ButtonState[BESTOP-1]) break;
			if(OldPlayState)
				{
				ButtonState[ButtonPress-1]^=1;
				if(ButtonState[BEPAUSE-1]==1)
					{
					OldPlayState=ButtonState[BEPLAY-1];
					ButtonState[BEPLAY-1]=0;
					}
				else	ButtonState[BEPLAY-1]=OldPlayState;
				DrawButtonState(hwnd,BEPLAY,ButtonState[BEPLAY-1]);
				if(ButtonState[BEPLAY-1]==1)
					{
					ButtonState[BESTOP-1]=0;
					DrawButtonState(hwnd,BESTOP,0);
					}
				}
			break;
		case BERESTART:
			if(ButtonState[BEPAUSE-1]==1)
				{
				ButtonState[BEPLAY-1]=OldPlayState;
				DrawButtonState(hwnd,BEPLAY,OldPlayState);
				ButtonState[BEPAUSE-1]=0;
				DrawButtonState(hwnd,BEPAUSE,0);
				ButtonState[BESTOP-1]=0;
				DrawButtonState(hwnd,BESTOP,0);
				}
			break;
		case BEPLAY:
			ButtonState[ButtonPress-1]^=1;
			OldPlayState=ButtonState[BEPLAY-1];
			if(ButtonState[BEPLAY-1]==1)
				{
				ButtonState[BEPAUSE-1]=0;
				DrawButtonState(hwnd,BEPAUSE,0);
				ButtonState[BESTOP-1]=0;
				DrawButtonState(hwnd,BESTOP,0);
				}
			break;
		case BESTOP:
			if(ButtonState[BEPAUSE-1]) break;
			if(OldPlayState)
				{
				ButtonState[ButtonPress-1]^=1;
				if(ButtonState[BESTOP-1]==1)
					{
					OldPlayState=ButtonState[BEPLAY-1];
					ButtonState[BEPLAY-1]=0;
					}
				else	ButtonState[BEPLAY-1]=OldPlayState;
				DrawButtonState(hwnd,BEPLAY,ButtonState[BEPLAY-1]);
				if(ButtonState[BEPLAY-1]==1)
					{
					ButtonState[BEPAUSE-1]=0;
					DrawButtonState(hwnd,BEPAUSE,0);
					}
				}
			break;
		}
	DrawButtonState(hwnd,ButtonPress,ButtonState[ButtonPress-1]);
	// Post Message to handle.
	PostMessage(hwnd,WM_COMMAND,ButtonPress,0L);
}
long FAR PASCAL WndBmpProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{
	HDC             hdc;
	PAINTSTRUCT     ps;

	if(message==WM_PAINT)
		{
		HBITMAP	hAbout;
		hdc=BeginPaint(hwnd,&ps);
		hAbout=LoadBitmap(hInst,"LOGO");
		DrawBitmap(hdc,hAbout,0,0);
		DeleteObject(hAbout);
		EndPaint(hwnd,&ps);
		return  0;
		}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
DWORD	huge	PASCAL	SelectProc(HWND hwnd,WORD message,WORD wParam,LONG LParam);
DWORD	huge	PASCAL	OtherFunctionProc(HWND hwnd,WORD message,WORD wParam,LONG LParam);
LONG huge pascal KeyboardFunc (int nCode, WORD wParam, DWORD lParam);
FARPROC	 	HookProc;
HHOOK   	HookHandle;
int		VideoAbort=0;
int		HadDown=0;
int		HadSetCapture=0;
extern	int	TestMode;
extern	long	VCDHigh;
extern	int	DisplayPreView;
extern	UINT	Devs;
extern	int	CurDevID;
extern	int	MixSound;
extern	WAVEOUTCAPS	AudioCaps[10];
/////////////////// New Feature /////////////////
int	StopFlags=0;
int	StepFlags=0;
int	MouseStop=0;
static	int	pascal	TryToYield(void)
{
	MSG	msg;

	if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
		if(msg.message==WM_STOPVIDEO)
			{//STOP
			StopFlags^=1;
			}
		else	{
			if(msg.message==WM_KEYDOWN &&
				(msg.wParam==VK_SPACE||
				 msg.wParam==VK_RETURN))
				{//Not play
				StopFlags=StepFlags=0;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				return 0;
				}
			else	{//another message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				}
			}
		}
	if(MouseStop)
		{
		StopFlags=StepFlags=0;
		return 0;
		}
	return 1;
}
void	PASCAL	FAR	DisplaySystemMessage(HWND hwnd)
{
	char	TmpBuffer[50];
	char	InfoBuffer[640];
	char	WhichYUV[5];

	*(DWORD *)WhichYUV=DCISurfaceScreen.dciInfo.dwCompression;
	WhichYUV[4]=0;
	InfoBuffer[0]=TmpBuffer[0]=0;
	if(VCDHigh==288)
		{//PAL
		if(UseDCI)
			{
			if(DCIType==2)
				{
				lstrcpy(InfoBuffer,"========PAL Video======\n");
				lstrcpy(TmpBuffer,"Use (");
				lstrcat(TmpBuffer,WhichYUV);
				lstrcat(TmpBuffer,") DCI Display\n");
				lstrcat(InfoBuffer,TmpBuffer);
				}
			else if(DCIType==1 && DCIPlay) lstrcpy(InfoBuffer,"PAL Video,Use Primary surface DCI Display\n");
			     else	goto	PALNotUseDCI;
			}
		else	{
			PALNotUseDCI:
			if(VESAColor==16 || VESAColor==163) lstrcpy(InfoBuffer,"PAL Video,Use 10E mode Display\n");
			if(VESAColor==15) lstrcpy(InfoBuffer,"PAL Video,Use 10D mode Display\n");
			if(VESAColor==64) lstrcpy(InfoBuffer,"PAL Video,Use 111 mode Display\n");
			if(VESAColor==32) lstrcpy(InfoBuffer,"PAL Video,Use 110 mode Display\n");
			if(VESAColor==8)  lstrcpy(InfoBuffer,"PAL Video,Use 13  mode Display\n");
			}
		}
	else	{//NTSC
		if(UseDCI)
			{
			if(DCIType==2)
				{
				lstrcpy(InfoBuffer,"========NTSC Video======\n");
				lstrcpy(TmpBuffer,"Use (");
				lstrcat(TmpBuffer,WhichYUV);
				lstrcat(TmpBuffer,") DCI Display\n");
				lstrcat(InfoBuffer,TmpBuffer);
				}
			else if(DCIType==1 && DCIPlay) lstrcpy(InfoBuffer,"NTSC Video,Use Primary surface DCI Display\n");
			     else goto	NTSCNotUseDCI;
			}
		else	{
			NTSCNotUseDCI:
			if(VESAColor==16 || VESAColor==163) lstrcpy(InfoBuffer,"NTSC Video,Use 10E mode Display\n");
			if(VESAColor==15) lstrcpy(InfoBuffer,"NTSC Video,Use 10D mode Display\n");
			if(VESAColor==64) lstrcpy(InfoBuffer,"NTSC Video,Use 111 mode Display\n");
			if(VESAColor==32) lstrcpy(InfoBuffer,"NTSC Video,Use 110 mode Display\n");
			if(VESAColor==8)  lstrcpy(InfoBuffer,"NTSC Video,Use 13  mode Display\n");
			}
		}
	////////////////// Sound Card Info ///////////////////
	if(Devs==0) lstrcat(InfoBuffer,"No any Audio Device.\n");
	else	{
		wsprintf(TmpBuffer,"There are %d Audio Devices\n",Devs);
		lstrcat(InfoBuffer,TmpBuffer);
		wsprintf(TmpBuffer,"Support %d Audio Channels\n",AudioCaps[CurDevID].wChannels);
		lstrcat(InfoBuffer,TmpBuffer);
		if(AudioCaps[CurDevID].dwSupport & WAVECAPS_VOLUME)
			lstrcat(InfoBuffer,"This Device Support Volume Control\n");
		else	lstrcat(InfoBuffer,"This Device Not Support Volume Control\n");
		if(AudioCaps[CurDevID].dwSupport & WAVECAPS_LRVOLUME)
			lstrcat(InfoBuffer,"Support Left & Right Volume Control\n");
		else	lstrcat(InfoBuffer,"Not Support Left & Right Volume Control\n");
		if(AudioCaps[CurDevID].dwFormats & 1)
			lstrcat(InfoBuffer,"Support 11025Hz Mono    8Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 2)
			lstrcat(InfoBuffer,"Support 11025Hz Stereo  8Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 4)
			lstrcat(InfoBuffer,"Support 11025Hz Mono   16Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 8)
			lstrcat(InfoBuffer,"Support 11025Hz Stereo 16Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x10)
			lstrcat(InfoBuffer,"Support 22050Hz Mono    8Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x20)
			lstrcat(InfoBuffer,"Support 22050Hz Stereo  8Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x40)
			lstrcat(InfoBuffer,"Support 22050Hz Mono   16Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x80)
			lstrcat(InfoBuffer,"Support 22050Hz Stereo 16Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x100)
			lstrcat(InfoBuffer,"Support 44100Hz Mono    8Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x200)
			lstrcat(InfoBuffer,"Support 44100Hz Stereo  8Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x400)
			lstrcat(InfoBuffer,"Support 44100Hz Mono   16Bits\n");
		if(AudioCaps[CurDevID].dwFormats & 0x800)
			lstrcat(InfoBuffer,"Support 44100Hz Stereo 16Bits\n");
		}
	//////////////////////////////////////////////////////
	lstrcat(InfoBuffer,"========Version II========");
	MessageBox(hwnd,InfoBuffer,"System Infomation",MB_OK);
}
static	void	MessageInfo(int wParam)
{
	DWORD	Ret;
	HWND	hwnd;

	hwnd=MainWindow;
	if(TimeStart!=-1) return;
	if(wParam=='t'||wParam=='T')
		{
		int	FullFrame;
		if(!TestMode)	return;
		Ret=TestVideoSpeed();
		FullFrame=(VCDHigh==288) ? 25:30;
		if(VCDHigh==288)
			{//PAL
			if(Chinese) wsprintf(Buffer,"播放 PAL 制\n速度=%ld.%ld 帧每秒\n满帧=%d\n速度率=%d%%",Ret/10,Ret%10,FullFrame,Ret*10/FullFrame);
			else wsprintf(Buffer,"Play PAL Video\nSpeed=%ld.%ld Frames Per Second\nFull Frames=%d\nSpeed rate=%d%%",Ret/10,Ret%10,FullFrame,Ret*10/FullFrame);
			}
		else	{//NTSC
			if(Chinese) wsprintf(Buffer,"播放 NTSC 制\n速度=%ld.%ld 帧每秒\n满帧=%d\n速度率=%d%%",Ret/10,Ret%10,FullFrame,Ret*10/FullFrame);
			else wsprintf(Buffer,"Play NTSC Video\nSpeed=%ld.%ld Frames Per Second\nFull Frames=%d\nSpeed rate=%d%%",Ret/10,Ret%10,FullFrame,Ret*10/FullFrame);
			}
		if(Chinese) MessageBox(hwnd,Buffer,"速度",MB_OK);
		else MessageBox(hwnd,Buffer,"Speed",MB_OK);
		}
	if(wParam=='m'||wParam=='M')
		{
		DisplaySystemMessage(hwnd);
		}
}
long _huge PASCAL WndProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{//Load DS
	HDC 		hdc;
	PAINTSTRUCT 	ps;
	RECT 		rect;
	DWORD		Ret;
	int		CurPos;

	if(message==WM_KEYUP && wParam==VK_F12)
		{//Capture Video
		DisplayPreView=0;//Disable the preview
		PostMessage(MainWindow,WM_CUTPICTURE,0,0L);
		return 0;
		}
	if(message==WM_SYSCHAR)
		{//TEST or Message
		MessageInfo(wParam);
		return 0;
		}
	if(message==WM_KEYDOWN && wParam==VK_F1 && Playing==0)
		{//Help
		WinHelp(hwnd,"README.HLP",HELP_CONTENTS,0L);
		return 0;
		}
	/////////////////////////////////////////////////////
	if(hwnd==AudioMainWindow) /// Audio Control
		return AudioWndProc(hwnd,message,wParam,lParam);
	if(hwnd==AboutWindow)	//Starting About Logo picture.
		return	WndBmpProc(hwnd,message,wParam,lParam);
	if(hwnd==ShowVideo&&(message>=WM_MOUSEFIRST && message<=WM_MOUSELAST))
		{// Display hInt
		DrawShowWindowhInt(MainWindow);
		}
	if(hwnd!=MainWindow)
		{// Video Window Message.
		if(message==WM_PAINT)
			{
			BeginPaint(hwnd,&ps);
			if(hwnd==ShowVideo) PreViewReDraw();
			EndPaint(hwnd,&ps);
			return 0;
			}
		if(Playing)
		    switch(message)
			{
			case WM_LBUTTONDOWN:	//STOP
				PlayState=BESTOP;
				SendMessage(MainWindow,WM_LBUTTONDOWN,0,0L);
				return 0;
			case WM_LBUTTONUP:
				MouseStop=1;
				PlayState=BESTOP;
				SendMessage(MainWindow,WM_LBUTTONUP,0,0L);
				PlayState=0;
				HadSetCapture=0;
				ReleaseCapture();
				return 0;
			case WM_RBUTTONDOWN:	//PAUSE
				PlayState=BEPAUSE;
				SendMessage(MainWindow,WM_LBUTTONDOWN,0,0L);
				return 0;
			case WM_RBUTTONUP:
				MouseStop=1;
				PlayState=BEPAUSE;
				SendMessage(MainWindow,WM_LBUTTONUP,0,0L);
				PlayState=0;
				HadSetCapture=0;
				ReleaseCapture();
				return 0;
			}
		return DefWindowProc(hwnd,message,wParam,lParam);
		}
	// Main Window Message.
	switch(message)
	{
	case MM_MCINOTIFY:
		if(wParam==MCI_NOTIFY_SUCCESSFUL && Loop)//Loop this video
			{//In Loop Mode.
			LONG	Pos;
			Pos=GetVideoCurrentPosition(videoID,hwnd);
			if(Pos<To && Playing) goto PAUSEVCD;//Looping stop
			if(From==0)	SeekVideoToStart(videoID,MainWindow);
			else	SeekVideoTo(videoID,MainWindow,From);
			if(!Playing) return 0;
			CurrentPos=From+LoopStartBase;
			if(CurVideoType)SetVideoWindow(videoID,VideoWindow,hwnd);
			if(CurVideoType && !Start) StartPlayScreen();
			PlayVideo(videoID,hwnd);
			SetVolumeAndMute();	//Set Volume.
			return 0;
			}
		if(wParam==MCI_NOTIFY_SUCCESSFUL)
			{// Can't play continue
			LONG	Pos;
			DisplayVideo=0;
			Pos=GetVideoCurrentPosition(videoID,hwnd);
			if(Pos<0) DisplayErrorMessage(LOWORD(Pos),hwnd);
			Pos+=3000;	//in one second.
			if(Pos<VideoLength[CurFileNum] && Playing)
				{
				PAUSEVCD:
				Loop=ButtonState[BELOOP-1]=0;
				LoopStart=LoopEnd=-1;	//Stop loop state.
				OldPlayState=ButtonState[BEPLAY-1]=0;//Not Play again.
				DrawButtonState(hwnd,BEPLAY,ButtonState[BEPLAY-1]);
				EndPlayScreen();//Restore Normal Screen.
				////// Not Close this Video if CDROM still there.
				VideoAbort=1;
				if(Run && VideoNumber==1)goto	RUNEXIT;
				else PostMessage(hwnd,WM_COMMAND,BEPLAY,0L);
				return 0;
				}
			}
		if(wParam==MCI_NOTIFY_SUCCESSFUL)//Had Played.
			{// Can Play Next here.
			if(Loop){//Loop this video
				//SeekAllVideoTo(0);
				SeekVideoToStart(videoID,MainWindow);
				if(!Playing) return 0;
				if(CurVideoType)SetVideoWindow(videoID,VideoWindow,hwnd);
				if(CurVideoType && !Start)StartPlayScreen();
				PlayVideo(videoID,hwnd);
				SetVolumeAndMute();	//Set Volume.
				return 0;
				}
			///////// try to play next /////////
			CurFileNum++;
			if(CurFileNum<VideoNumber)
				{
				HBITMAP	hBmp;
				PLAYOTHERFILE:

				if(!Playing) return 0;
				EndPlayScreen();//Restore Normal Screen.
				////////////
				hdc=GetDC(VideoWindow);
				GetClientRect(VideoWindow,&rect);
				hBmp=LoadBitmap(hInst,"WAIT");
				rect.right/=2;
				rect.bottom/=2;
				rect.right-=100;
				if(DCIPlay &&
					(DCIType==1 &&
					(VESAColor==64||VESAColor==32))
					)//DCI Primary play.
					rect.bottom+=0;
				else	rect.bottom-=32;//Not DCI Primary
				DrawBitmap(hdc,hBmp,rect.right,rect.bottom);
				DeleteObject(hBmp);
				ReleaseDC(VideoWindow,hdc);
				////////////
				CloseVideo(videoID,hwnd);// End the video
				videoID=-1;
				OpenVideo(hwnd,CurFileNum);//New Video
				if(CurVideoType)SetVideoWindow(videoID,VideoWindow,hwnd);
				if(CurVideoType && !Start) StartPlayScreen();
				PlayVideo(videoID,hwnd);
				SetVolumeAndMute();	//Set Volume.
				return 0;
				}
			else	{//End and Close.
				OldPlayState=ButtonState[BEPLAY-1]=0;//Not Play again.
				DrawButtonState(hwnd,BEPLAY,ButtonState[BEPLAY-1]);
				EndPlayScreen();//Restore Normal Screen.
				RUNEXIT:
				VideoNumber=0;	//Had Played end all file.
				CurFileNum=0;
				CloseVideo(videoID,hwnd);
				videoID=-1;
				if(Run)	{//Exit
					PostMessage(hwnd,WM_KEYDOWN,VK_ESCAPE,0L);
					PostMessage(hwnd,WM_KEYUP,VK_ESCAPE,0L);
					return 0;
					}
				PostMessage(hwnd,WM_COMMAND,BEPLAY,0L);
				if(AutoVCDPlay)	PostMessage(hwnd,WM_CDROMOPEN,0,0L);
				}
			return 0;	//Success.
			}
		break;
	case WM_CDROMOPEN:
		if(DrvNum) OpenCDROMDoor();// Must had CDROM driver device.
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hwnd,&ps);
		if(!Playing)
			{
			VCDFACE=LoadBitmap(hInst,"VCD");
			DrawBitmap(hdc,VCDFACE,0,0);
			DeleteObject(VCDFACE);
			DrawAllStatus(hdc);
			DrawPlayType(hdc);
			PreViewReDraw();
			if(ShowVideo)ValidateRect(ShowVideo,NULL);//Not update the preview area
			}
		EndPaint(hwnd,&ps);
		DisplayTime(CurrentPos);
		if(!Playing&&videoID!=-1) UpDateVideo(videoID,MainWindow);
		return 0;
	case WM_NCHITTEST:
		if(InButton(hwnd)) break;
		lParam=DefWindowProc(hwnd,message,wParam,lParam);
		if(lParam==1)	return 2;
		return	lParam;
	///////////////// new /////////////////
	case WM_RBUTTONDOWN:
		CurPos=InPositionBar(hwnd);
		if(CurPos==-1) return 0;
		LoopCount^=1;
		if(LoopCount)	LoopStart=CurPos;
		else	LoopEnd=CurPos;
		if(LoopStart<FromPos) 	LoopStart=FromPos;
		if(LoopEnd>ToPos) 	LoopEnd=ToPos;
		if(LoopEnd<FromPos) 	LoopEnd=FromPos;
		if(LoopStart>ToPos) 	LoopStart=ToPos;
		if(LoopStart==FromPos) From=0;
		else	{
			From=Length*LoopStart/264L;
			if(From>LoopStartBase)	From-=LoopStartBase;
			else	From=0;
			}
		if(LoopEnd==ToPos) To=EndTo;
		else	{
			To=Length*LoopEnd/264L;
			if(To<LoopStartBase) To=0;
			else	To-=LoopStartBase;
			if(To>EndTo) To=EndTo;
			}
		DisplayTime(CurrentPos);	//Display the loop
		return 0;
	///////////////////////////////////////
	case WM_LBUTTONDOWN:
		ButtonPress=InButton(hwnd);
		ClearhInt();	//Clear Hint
		if(ButtonPress)
			{
			if(!PlayState)
				{
				HadSetCapture=1;
				SetCapture(hwnd);
				}
			DrawButtonState(hwnd,ButtonPress,ButtonState[ButtonPress-1]^1);
			}
		if(ButtonPress==BEPOWER)
			{
			CloseState=1;
			DrawCloseState(hwnd);
			}
		switch(ButtonPress)
			{
			case	BEBACK:
			case	BEFORWARD:
				TimeCount=0;
				TimerID=SetTimer(hwnd,0x888,40,NULL);
				break;
			}
		/////////Position//////
		if(videoID!=-1)
			{
			int	Ret;
			Ret=InPositionBar(hwnd);
			if(Ret!=-1 && Playing==0) //Only when not playing
				{//Seek to
				int	CurFile=CurFileNum;
				CurrentPos=Ret;
				CurrentPos*=Length;
				CurrentPos/=264;
				DisplayTime(CurrentPos);
				SeekAllVideoTo(CurrentPos);
				UpDateVideo(videoID,hwnd);
				if(CurFile!=CurFileNum)
					{//Seek to another file the loop state clear.
					Loop=ButtonState[BELOOP-1]=0;
					LoopStart=LoopEnd=-1;
					DrawButtonState(hwnd,BELOOP,ButtonState[BELOOP-1]);
					DisplayTime(CurrentPos);
					}
				}
			}
		///////////////////////
		break;
	case WM_LBUTTONUP:
		if(TimerID)
			{
			KillTimer(hwnd,0x888);
			TimerID=0;
			}
		if(ButtonPress)
			{
			int	CurPos;
			CurPos=InButton(hwnd);
			if(CurPos==ButtonPress)
				{
				DoUpHandle(hwnd);
				}
			CloseState=ButtonPress=MoveOut=0;
			if(!PlayState)
				{
				HadSetCapture=0;
				ReleaseCapture();
				}
			}
		break;
	case WM_NCMOUSEMOVE:
		CurPos=InButton(hwnd);
		//////////// Draw hint ///////////
		if(CurPos) DrawhInt(hwnd,CurPos);
		else	ClearhInt();
		break;
	case WM_MOUSEMOVE:
		CurPos=InButton(hwnd);
		//////////// Draw hint ///////////
		if(CurPos) DrawhInt(hwnd,CurPos);
		else	ClearhInt();
		if(ButtonPress)
			{
			//////////////////////////////////
			if(ButtonPress==BEPOWER &&
			  ((CurPos!=BEPOWER && CloseState) ||
			  (CurPos==BEPOWER && CloseState==0)))
				{
				if(CloseState==0)
					{
					DrawCloseState(hwnd);
					CloseState=1;
					}
				else	{
					DrawOpenState(hwnd);
					CloseState=0;
					}
				}
			if(CurPos!=ButtonPress)
				{
				DrawButtonState(hwnd,ButtonPress,ButtonState[ButtonPress-1]);
				MoveOut=1;
				}
			else	if(MoveOut)
				{
				DrawButtonState(hwnd,ButtonPress,ButtonState[ButtonPress-1]^1);
				MoveOut=0;
				}
			}
		break;
	case WM_COMMAND:	// Video Command
		switch(wParam)
			{
			////////////////// New functions /////////
			case BEOTHER:
				if(Chinese) DialogBox(hInst,"FUNCTIONC",hwnd,(DLGPROC)OtherFunctionProc);
				else DialogBox(hInst,"FUNCTION",hwnd,(DLGPROC)OtherFunctionProc);
				return 0;
			case BECDOUT:
				if(CDROMDoorClosed())//CDROM Closed,Open it
					{
					if(videoID!=-1)
						{//Close the video
						CurrentPos=0;
						Playing=0;
						VideoNumber=0;
						CurFileNum=0;
						CloseVideo(videoID,hwnd);
						videoID=-1;
						OldPlayState=ButtonState[BEPLAY-1]=0;//Not Play again.
						DrawButtonState(hwnd,BEPLAY,ButtonState[BEPLAY-1]);
						ButtonState[BEPAUSE-1]=0;//Not Play again.
						DrawButtonState(hwnd,BEPAUSE,ButtonState[BEPAUSE-1]);
						ButtonState[BESTOP-1]=0;//Not Play again.
						DrawButtonState(hwnd,BESTOP,ButtonState[BESTOP-1]);
						Loop=ButtonState[BELOOP-1]=0;
						DrawButtonState(hwnd,BELOOP,ButtonState[BELOOP-1]);
						LoopStart=LoopEnd=-1;
						DisplayTime(CurrentPos);
						}
					OpenCDROMDoor();
					}
				else	{//CDROM Opened,then Close it.
					CloseCDROMDoor();
					}
				return 0;
			case BECAPTURE:
				if(videoID!=-1 && CurVideoType)//Video had Open then caputure picture
					CapturePicture();
				return 0;
			case BEMIXSOUND:
				MixSound=ButtonState[BEMIXSOUND-1];
				return 0;
			//////////////////////////////////////////
			case BEPOWER:
				if(videoID!=-1) CloseVideo(videoID,hwnd);
				if(DrvNum)//Close the CDROM that be open after play end..
					if(!CDROMDoorClosed())
						CloseCDROMDoor();
				DestroyWindow(AudioMainWindow);
				DestroyWindow(VideoWindow);
				DestroyWindow(hwnd);
				return 0;
			case BELOOP:
				Loop=ButtonState[BELOOP-1];
				if(VideoNumber==0 || Length==0)
					{//Can Press this buttom when no video open
					Loop=ButtonState[BELOOP-1]=0;
					LoopStart=LoopEnd=-1;
					DrawButtonState(hwnd,BELOOP,ButtonState[BELOOP-1]);
					}
				if(Loop){//Set Loop start & end
					int	i;
					DWORD	Len;
					Len=0;
					for(i=0;i<CurFileNum;i++)
						Len+=VideoLength[i];
					LoopStart=Len*264L/Length;//Make sure Length!=0
					LoopStartBase=Len;
					Len	+=VideoLength[i];
					LoopEnd	=Len*264L/Length;
					LoopEnd-=3;
					FromPos=LoopStart;
					ToPos=LoopEnd;
					From=0;
					EndTo=To=VideoLength[i];
					}
				else	LoopStart=LoopEnd=-1;
				DisplayTime(CurrentPos);// Display the loop state
				return 0;
			case BEDISC:	//The Disc is Opened,Close all Plaing.
				CurrentPos=0;
				if(videoID!=-1)
					{//There is one opened Video
					CloseVideo(videoID,hwnd);
					videoID=-1;
					}
				Playing=0;
				if(AutoVCDPlay)
					{//Auto Play State Clear them.
					VideoNumber=0;
					CurFileNum=0;
					}
				AutoVCDPlay=0;//Select state.
				OldPlayState=ButtonState[BEPLAY-1]=0;//Not Play again.
				DrawButtonState(hwnd,BEPLAY,ButtonState[BEPLAY-1]);
				ButtonState[BEPAUSE-1]=0;//Not Play again.
				DrawButtonState(hwnd,BEPAUSE,ButtonState[BEPAUSE-1]);
				ButtonState[BESTOP-1]=0;//Not Play again.
				DrawButtonState(hwnd,BESTOP,ButtonState[BESTOP-1]);
				break;
			case BEBACK:
			case BEFORWARD:
				if(videoID!=-1)
					{
					SeekAllVideoTo(CurrentPos);
					UpDateVideo(videoID,hwnd);
					}
				break;
			case BESTART:
				if(videoID!=-1)
					{
					CurrentPos=0;
					DisplayTime(CurrentPos);
					SeekAllVideoTo(CurrentPos);
					UpDateVideo(videoID,hwnd);
					}
				break;
			case BEEND:
				if(videoID!=-1)
					{
					CurrentPos=Length;
					DisplayTime(CurrentPos);
					SeekAllVideoTo(CurrentPos);
					UpDateVideo(videoID,hwnd);
					}
				break;
			}
		if(wParam>=BESTOP && wParam<=BEPAUSE)
		{
		if(ButtonState[BEPLAY-1])
			{// Play
			if(TimeStart!=-1)
				{//Can not Start.
				OldPlayState=ButtonState[BEPLAY-1]=0;
				DrawButtonState(hwnd,BEPLAY,0);
				return 0;
				}
			if(VideoAbort)
				{// Video auto stop maybe data error or open.
				if(!CDROMDoorClosed())
					{
					CloseCDROMDoor();//CDROM Must close.
					VideoNumber=CurFileNum=0;
					CloseVideo(videoID,hwnd);
					videoID=-1;
					VideoAbort=0;//Video Close
					CDROMMediaChanged();//Let MSCDEX know media changed.
					}
				if(VideoAbort)////Video not Close.
				    if(CDROMMediaChanged())//Media changed.
					{// The Video stop because the disk open by hand.
					VideoNumber=CurFileNum=0;
					CloseVideo(videoID,hwnd);
					videoID=-1;
					}
				VideoAbort=0;
				}
			if(VideoNumber==0)
				{//No selector video file,search CDROM
				if(DrvNum)//There are CDROMs,Try to Close them.
					{
					if(!CDROMDoorClosed())	CloseCDROMDoor();//CDROM Must close.
					if(!CDROMDoorClosed())	//Make sure the door close
						{
						MessageBox(hwnd,"Your CDROM's door can't close !\n","CDROM Error",MB_OK);
						OldPlayState=ButtonState[BEPLAY-1]=0;
						DrawButtonState(hwnd,BEPLAY,0);
						return 0;
						}
					}
				}
			if(!Playing)
				{
				if(VideoNumber==0)
					{// No selected Video file,Search them.
					VideoNumber=SearchVideoFile();
					if(VideoNumber) InitVideoState();
					}
				if(VideoNumber)	Playing=1;
				if(videoID==-1 && VideoNumber)
					{
					Playing=OpenVideo(hwnd,CurFileNum);
					}
				if(Playing)// Can Play.
					{
					if(CurVideoType)
						{
						SetVideoWindow(videoID,VideoWindow,hwnd);
						ShowWindow(VideoWindow,SW_SHOW);
						}
					////////// Hook Keyboard ///////////
					HookProc = MakeProcInstance((FARPROC)KeyboardFunc, hInst);
					HookHandle=SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)HookProc,hInst,NULL);
					if(CurVideoType)StartPlayScreen();
					PlayVideo(videoID,hwnd);
					if(CurVideoType) SetCapture(VideoWindow);//Play MCI type not capture mouse.
					SetVolumeAndMute();	//Set Volume.
					HadSetCapture=1;
					}
				if(!Playing)//Can not play.
					{
					OldPlayState=ButtonState[BEPLAY-1]=0;
					DrawButtonState(hwnd,BEPLAY,0);
					}
				}
			}
		else	{// Not Play
			CurrentPos=GetAllVideoPosition();
			if(CurrentPos<0)DisplayErrorMessage(LOWORD(CurrentPos),hwnd);
			DisplayTime(CurrentPos);
			if(Playing)
				{
				Playing=0;
				DisplayVideo=0;
				StepFlags=StopFlags=0;	//Clear Stop & Step falgs
				EndPlayScreen();//Restore Normal Screen.
				UnhookWindowsHook(WH_KEYBOARD,(HOOKPROC)HookProc);
				if(HookProc!=NULL) FreeProcInstance(HookProc);
				HookProc=NULL;
				if(CurVideoType)SetVideoWindow(videoID,ShowVideo,hwnd);
				StopVideo(videoID,hwnd);
				ShowWindow(VideoWindow,SW_HIDE);
				UpDateVideo(videoID,hwnd);
				if(HadSetCapture==1) 	//Maybe the Play had STOP by KEYBOARD
					{	//Release MOVSE Capture
					HadSetCapture=0;	//No Capture the Mouse to STOP or PAUSE
					ReleaseCapture();
					}
				if(CurVideoType==0)//RePaint the windows
					{
					InvalidateRgn(hwnd,NULL,FALSE);
					InvalidateRgn(AudioMainWindow,NULL,FALSE);
					}
				}
			}
		}
		if(wParam==BEDISC)
			{
			Loop=ButtonState[BELOOP-1]=0;
			DrawButtonState(hwnd,BELOOP,ButtonState[BELOOP-1]);
			LoopStart=LoopEnd=-1;
			if(Chinese) DialogBox(hInst,"OPENDISK",hwnd,(DLGPROC)SelectProc);
			else DialogBox(hInst,"OPENDISC",hwnd,(DLGPROC)SelectProc);
			}
		break;
	case WM_TIMER:
		if(videoID==-1) return 0;
		if(ButtonPress==BEBACK && !MoveOut)
			{
			if(TimeCount<60)
				{
				CurrentPos-=1000;
				TimeCount++;
				}
			else	CurrentPos-=15000;//60000;
			if(CurrentPos<0) CurrentPos=0;
			}
		if(ButtonPress==BEFORWARD && !MoveOut)
			{
			if(TimeCount<60)
				{
				CurrentPos+=1000;	//If Search one Min
				TimeCount++;
				}
			else	CurrentPos+=15000;//60000;	// Search Min level.
			if(CurrentPos>Length) CurrentPos=Length;
			}
		DisplayTime(CurrentPos);	//Display the Time.
		return 0;
	////////// Key Board Control. //////////
	case WM_KEYDOWN:
		switch(wParam)
			{
			case VK_RETURN:
			case VK_SPACE://PLAY or STOP
				ButtonPress=BEPLAY;
				break;
			case VK_ESCAPE://POWER down
				ButtonPress=BEPOWER;
				break;
			case VK_HOME://START
				ButtonPress=BESTART;
				break;
			case VK_END:// END
				ButtonPress=BEEND;
				break;
			case VK_PRIOR://Page UP,Back one Min
			case VK_LEFT:// Back Search one Sec
				ButtonPress=BEBACK;
				break;
			case VK_NEXT:// Page Down,Forward one Min
			case VK_RIGHT:// Forward search one Sec
				ButtonPress=BEFORWARD;
				break;
			case VK_INSERT:// Open Select,DISC Insert now.
				ButtonPress=BEDISC;
				break;
			case VK_TAB:	//When Play End,loop play from start.
				ButtonPress=BELOOP;
				break;
			//////// To Audio Coltrol ///////
			case VK_DELETE:// Mute
			case VK_ADD: //Volume ++
			case VK_SUBTRACT://Volume --
				SendMessage(AudioMainWindow,WM_KEYDOWN,wParam,lParam);
				break;
			}
		if(!HadDown) DrawButtonState(hwnd,ButtonPress,ButtonState[ButtonPress-1]^1);
		HadDown=1;
		if(ButtonPress==BEPOWER)
			{
			CloseState=1;
			DrawCloseState(hwnd);
			}
		if(videoID!=-1)	//Only when the video be open.
		switch(wParam)
			{// Seek to
			case VK_PRIOR://Page UP,Back one Min
				CurrentPos-=59000;
			case VK_LEFT:// Back Search one Sec
				CurrentPos-=1000;
				if(CurrentPos<0) CurrentPos=0;
				DisplayTime(CurrentPos); //Display the Time.
				break;
			case VK_NEXT:// Page Down,Forward one Min
				CurrentPos+=59000;
			case VK_RIGHT:// Forward search one Sec
				CurrentPos+=1000;
				if(CurrentPos>Length) CurrentPos=Length;
				ButtonPress=BEFORWARD;
				DisplayTime(CurrentPos); //Display the Time.
				break;
			}
		return 0;
	case WM_KEYUP:
		DoUpHandle(hwnd);
		HadDown=0;
		CloseState=ButtonPress=MoveOut=0;
		//////////Audio Control ////////
		switch(wParam)
			{
			case VK_DELETE:// Mute
			case VK_ADD: //Volume ++
			case VK_SUBTRACT://Volume --
				SendMessage(AudioMainWindow,WM_KEYUP,wParam,lParam);
				break;
			}
		return 0;
	/////////////////////////
	case WM_DEBUG:
		ButtonPress=BESTOP;
		DoUpHandle(hwnd);
		HadDown=0;
		CloseState=ButtonPress=MoveOut=0;
		/////////////////////
		ButtonPress=BEPOWER;	//Close
		DoUpHandle(hwnd);
		HadDown=0;
		CloseState=ButtonPress=MoveOut=0;
		break;
	case WM_DESTROY:
		if(Start) EndPlayScreen();//Restore Normal Screen.
		if(videoID!=-1) CloseVideo(videoID,hwnd);
		videoID=-1;
		PostQuitMessage(0);
		return 0;
	//////////////////// New Feature //////////////////
	case WM_STOPVIDEO:
		StopFlags^=1;
		if(StopFlags)
			{//On PAUSE state the CDROM's door can't open
			LockCDROM(1);//Lock
			PauseVideo(videoID,hwnd);
			}
		else	{
			ResumeVideo(videoID,hwnd);
			LockCDROM(0);//UnLockk
			}
		return 0;
	case WM_STEPVIDEO:
		if(StopFlags)	return 0;
		StepFlags^=1;
		if(StepFlags==0) return 0;
		LockCDROM(1);//Lock
		MouseStop=0;
		PauseVideo(videoID,hwnd);
		Ret=timeGetTime();
		Ret+=100;
		while(StepFlags)
			{
			while(timeGetTime()<Ret)
				{//Wait
				if(TryToYield()==0)
					return 0;
				}
			Ret=timeGetTime();
			Ret+=100;
			if(StopFlags==0)
				{
				DWORD	Pos;
				if(MouseStop) return 0;	//use mouse stop playing
				StepVideo(videoID,hwnd,1);
				Pos=GetVideoCurrentPosition(videoID,hwnd);
				if(Loop){//Loop mode
					if(Pos>=To)
						{//Loop on step mode,seek to the From position
						if(From==0)	SeekVideoToStart(videoID,hwnd);
						else	SeekVideoTo(videoID,hwnd,From);
						}
					}
				else	{//If to End
					Pos+=100;
					if(Pos>=VideoLength[CurFileNum])
						{
						StopFlags=StepFlags=0;//End
						PostMessage(hwnd,WM_KEYDOWN,VK_SPACE,0L);
						PostMessage(hwnd,WM_KEYUP,VK_SPACE,0L);
						}
					}
				}
			if(TryToYield()==0)
				return 0;
			}
		if(Playing)	ResumeVideo(videoID,hwnd);
		LockCDROM(0);//UnLockk
		return 0;
	case	WM_CUTPICTURE:
		if(videoID!=-1 && CurVideoType)//Video had Open then caputure picture
			CapturePicture();//Must MPEG and use internal driver.
		return 0;
	case	WM_PLAYNEXTFILE:
		if(Loop)	return 0;
		if(Playing==0)	return 0;
		if((CurFileNum+1)<VideoNumber)
			{
			CurFileNum++;
			DisplayVideo=0;
			StopVideoWait(videoID,hwnd);
			goto	PLAYOTHERFILE;
			}
		return 0;
	case	WM_PLAYPREVFILE:
		if(Loop)	return 0;
		if(Playing==0)	return 0;
		if((CurFileNum-1)>=0)
			{
			CurFileNum--;
			DisplayVideo=0;
			StopVideoWait(videoID,hwnd);
			goto	PLAYOTHERFILE;
			}
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}
////////////////////////// Dialog Box //////////////////////////
static	void	MakeFileName(int Num,LPSTR Str)
{
	int	NameStart=0;
	int	i;
	for(i=0;i<80;i++)
		{
		if(*(Str+i)=='\\') NameStart=i;
		if(*(Str+i)==0) break;
		}
	wsprintf(Buffer,"%d:",Num);
	lstrcat(Buffer,(Str+NameStart+1));
}
static	void	FillPathInBuffer(int Num)
{
	int	NameStart=0;
	int	i;
	for(i=0;i<80;i++)
		{
		if(VideoName[Num][i]=='\\') NameStart=i;
		if(VideoName[Num][i]==0) break;
		}
	for(i=0;i<NameStart;i++) Buffer[i]=VideoName[Num][i];
	Buffer[i]=0;
}
static	void	SelectNumber(HWND hwnd,int Num)
{
	FillPathInBuffer(Num);
	SendDlgItemMessage(hwnd,104,WM_SETTEXT,0,(LPARAM)(LPSTR)Buffer);
	SendDlgItemMessage(hwnd,102,LB_SETCURSEL,Num,0L);
}
static	void	DeleteFromPlayList(int Num)
{
	int	i;
	VideoNumber--;
	if(VideoNumber<0) VideoNumber=0;
	for(i=Num;i<VideoNumber;i++)
		{
		lstrcpy(VideoName[i],VideoName[i+1]);
		}
	VideoName[VideoNumber][0]=0;	//Delete the End String.
}
static	int	AddToPlayList(void)
{
	int 	Ret;
	GetCWD(VideoName[VideoNumber-1],sizeof(VideoName[VideoNumber-1]));
	if(VideoName[VideoNumber-1][3]) lstrcat(VideoName[VideoNumber-1],"\\");
	lstrcat(VideoName[VideoNumber-1],Buffer);
	//////////// Check if OK MCI Driver ///////
	Ret=CheckFileForDriver(VideoName[VideoNumber-1],VideoDriver);
	if(Ret==0) return 0;
	if(Ret!=3) PlayType=1; // MCI Type.
	return 1;
}
static	void	CheckAllFileType(void)
{
	int	i;
	int	Ret;
	PlayType=0;
	for(i=0;i<VideoNumber;i++)
		{
		Ret=CheckFileForDriver(VideoName[VideoNumber-1],VideoDriver);
		if(Ret==0)
			{//Error Type Delete it from play list.
			i--;if(i<0)i=0;
			DeleteFromPlayList(i);
			}
		if(Ret!=3) PlayType|=1; // MCI Type.
		}
}
static	void	ChDir(char *Path)
{
	if(*(Path+1)==':') SetDisk((*Path|0x20)-'a');
	ChangeDir(Path);
}
static	void	ResetSelectorList(HWND hwnd,unsigned listbox,unsigned PathItem)
{
	HWND	dlgH;
	////////////////////////////////
	dlgH=GetDlgItem(hwnd,listbox);
	SendDlgItemMessage(hwnd,listbox,LB_RESETCONTENT,0,0L);
	SetDlgItemText(hwnd,PathItem,Buffer);
	ChDir(Buffer);
	SendMessage(dlgH,WM_SETREDRAW,FALSE,0L);
	if(ListAllFile)
		{//List all files
		lstrcpy(Buffer,"*.*");
		SendDlgItemMessage(hwnd,listbox,LB_DIR,0X0000,(LONG)Buffer);
		}
	else	{//Only list video files.
		lstrcpy(Buffer,"*.dat");
		SendDlgItemMessage(hwnd,listbox,LB_DIR,0X0000,(LONG)Buffer);
		lstrcpy(Buffer,"*.vcd");
		SendDlgItemMessage(hwnd,listbox,LB_DIR,0X0000,(LONG)Buffer);
		lstrcpy(Buffer,"*.mpg");
		SendDlgItemMessage(hwnd,listbox,LB_DIR,0X0000,(LONG)Buffer);
		lstrcpy(Buffer,"*.mpv");
		SendDlgItemMessage(hwnd,listbox,LB_DIR,0X0000,(LONG)Buffer);
		lstrcpy(Buffer,"*.vbs");
		SendDlgItemMessage(hwnd,listbox,LB_DIR,0X0000,(LONG)Buffer);
		}
	lstrcpy(Buffer,"*.*");
	SendDlgItemMessage(hwnd,listbox,LB_DIR,0XC010,(LONG)Buffer);
	SendDlgItemMessage(hwnd,listbox,LB_SETCURSEL,0,0L);
	SendMessage(dlgH,WM_SETREDRAW,TRUE,0L);
}
#pragma warn -par
int	Modify=0;
char	WorkPath[80];
static	void	ChangeReturnWorkPath(void)
{
	SetDisk((WorkPath[0]|0x20)-'a');
	ChangeDir(WorkPath);
}
DWORD	huge	PASCAL	SelectProc(HWND hwnd,WORD message,WORD wParam,LONG lParam)
{
	int	i;
	HDC	hdc;
	switch(message)
		{
		case 	WM_INITDIALOG:
			GetCWD(WorkPath,sizeof(WorkPath));
			PlayType=0; // VCD Type.
			for(i=0;i<VideoNumber;i++)
				{
				MakeFileName(i,VideoName[i]);
				SendDlgItemMessage(hwnd,102,LB_ADDSTRING,0,(LPARAM)(LPSTR)Buffer);
				}
			SelectNumber(hwnd,0);
			if(VideoNumber==0)
				{
				GetCWD(Buffer,sizeof(Buffer));
				}
			else	{
				FillPathInBuffer(0);
				}
			ResetSelectorList(hwnd,101,103);
			Modify=0;
			return TRUE;
		case	WM_COMMAND:
			switch(wParam)
				{
				case 	300:
					goto	RETURN;
				case	200:	//Add
					if(DlgDirSelect(hwnd,Buffer,101))
						{
						i=lstrlen(Buffer);
						if(Buffer[i-1]=='\\')
							{
							Buffer[i-1]=0;
							ChangeDir(Buffer);
							}
						else	{
							SetDisk((Buffer[0]|0x20)-'a');
							}
						GetCWD(Buffer,sizeof(Buffer));
						ResetSelectorList(hwnd,101,103);
						}
					else	{/////////// Add ////////////
						i=SendDlgItemMessage(hwnd,101,LB_GETCURSEL,0,0L);
						if(i!=LB_ERR)
							{
							VideoNumber++;
							SendDlgItemMessage(hwnd,101,LB_GETTEXT,i,(LPARAM)(LPSTR)Buffer);
							if(VideoNumber<VIDEONUMBER)
								{
								if(AddToPlayList()==0)
									{// Can't Add
									VideoNumber--;
									if(VideoNumber<0) VideoNumber=0;
									}
								else	{// Add Success
									Modify=1;
									MakeFileName(VideoNumber-1,VideoName[VideoNumber-1]);
									SendDlgItemMessage(hwnd,102,LB_ADDSTRING,VideoNumber-1,(LPARAM)(LPSTR)Buffer);
									SelectNumber(hwnd,0);
									}
								}
							}
						}
					break;
				case	201:	//Add All
					i=SendDlgItemMessage(hwnd,101,LB_GETCOUNT,0,0L);
					if(i!=LB_ERR)
						{
						int	j;
						for(j=0;j<i;j++)
							{//Add one by one.
							VideoNumber++;
							SendDlgItemMessage(hwnd,101,LB_GETTEXT,j,(LPARAM)(LPSTR)Buffer);
							if(VideoNumber<VIDEONUMBER)
								{
								if(AddToPlayList()==0)
									{// Can't Add
									VideoNumber--;
									if(VideoNumber<0) VideoNumber=0;
									}
								else	{// Add Success
									Modify=1;
									MakeFileName(VideoNumber-1,VideoName[VideoNumber-1]);
									SendDlgItemMessage(hwnd,102,LB_ADDSTRING,VideoNumber-1,(LPARAM)(LPSTR)Buffer);
									SelectNumber(hwnd,0);
									}
								}
							else	VideoNumber--; //Video Number not changed
							}
						}
					break;
				case	202:	//Del
					Modify=1;
					if(VideoNumber==0) return TRUE;
					i=SendDlgItemMessage(hwnd,102,LB_GETCURSEL,0,0L);
					DeleteFromPlayList(i);
					////// Delete All
					SendDlgItemMessage(hwnd,102,LB_RESETCONTENT,0,0L);
					////// ReInit list box
					for(i=0;i<VideoNumber;i++)
						{
						MakeFileName(i,VideoName[i]);
						SendDlgItemMessage(hwnd,102,LB_ADDSTRING,0,(LPARAM)(LPSTR)Buffer);
						}
					SelectNumber(hwnd,0);
					return	TRUE;
				case	101://Select in Select List Box
					switch(HIWORD(lParam))
						{
						case	LBN_DBLCLK:
							if(DlgDirSelect(hwnd,Buffer,101))
								{
								i=lstrlen(Buffer);
								if(Buffer[i-1]=='\\')
									{
									Buffer[i-1]=0;
									ChangeDir(Buffer);
									}
								else	{
									SetDisk((Buffer[0]|0x20)-'a');
									}
								GetCWD(Buffer,sizeof(Buffer));
								ResetSelectorList(hwnd,101,103);
								}
							else	SendMessage(hwnd,WM_COMMAND,200,88888888L); //Add
							break;
						}
					return TRUE;
				}
			if(HIWORD(lParam)==LBN_SELCHANGE)
				{
				if(wParam==102)
					SelectNumber(hwnd,SendDlgItemMessage(hwnd,102,LB_GETCURSEL,0,0L));
				}
			break;
		case	WM_CLOSE:
			RETURN:
			ChangeReturnWorkPath();
			if(VideoNumber<=0) VideoNumber=CurFileNum=0;
			if(VideoNumber) CheckAllFileType();
			if(Modify && VideoNumber!=0)
				{//Had Modify
				CurFileNum=0;//Start from first.
				InitVideoState();
				}
			/////////////////////////
			CurrentPos=0;
			hdc=GetDC(MainWindow);
			DrawAllStatus(hdc);
			DrawPlayType(hdc);
			ReleaseDC(MainWindow,hdc);
			/////////////////////////
			EndDialog(hwnd,wParam);
			return TRUE;
		}
	return FALSE;
}
#pragma warn .par
//////////////////////////////////////////////
int	FAR PASCAL SouthernAudioVideo(void);	//From DLL
int	FAR PASCAL SouthernAudio(void);
int	FAR PASCAL SouthernVideo(void);
////////////////// Key Board Hook ////////////////
#pragma option -2       //Use 286 instructions
LONG huge pascal KeyboardFunc (int nCode, WORD wParam, DWORD lParam)
{	//When Playing Hook Keyboard for any key,execpt SPACE or ENTER
	int	CTRL,ALT;
	if(nCode<0)     return(CallNextHookEx(HookHandle,nCode,wParam,lParam));
	if(SouthernAudioVideo()) PostMessage(MainWindow,WM_DEBUG,0,0L);
	CTRL=GetKeyState(VK_CONTROL);
	ALT=GetKeyState(VK_MENU);
	if(CTRL<0 || ALT<0)
		{       //Press Crtl or Alt
		if(ALT<0)	return 1;
		if(CTRL<0)
			{//Press CTRL+-> or CTRL+<-
			if(wParam==VK_LEFT)
				{
				if((long)lParam>0) //Down
					{
					PostMessage(MainWindow,WM_PLAYPREVFILE,0,0L);
					return 1;
					}
				}
			if(wParam==VK_RIGHT) //->
				{
				if((long)lParam>0) //Down
					{
					PostMessage(MainWindow,WM_PLAYNEXTFILE,0,0L);
					return 1;
					}
				}
			}
		return 1;
		}
	switch(wParam)
		{
		case VK_RETURN:
		case VK_SPACE:	//PLAY or STOP
			if(StopFlags && StepFlags==0) StopFlags=0;
			if(SouthernAudio()) PostMessage(MainWindow,WM_DEBUG,0,0L);
			if((long)lParam<0) PostMessage(MainWindow,WM_KEYUP,wParam,lParam);
			else PostMessage(MainWindow,WM_KEYDOWN,wParam,lParam);
			break;
		case VK_TAB:	//LOOP or not
			if(SouthernAudio()) PostMessage(MainWindow,WM_DEBUG,0,0L);
			if((long)lParam<0) PostMessage(MainWindow,WM_KEYUP,wParam,lParam);
			else PostMessage(MainWindow,WM_KEYDOWN,wParam,lParam);
			break;
		case VK_DELETE:	// Mute
		case VK_ADD:	// Volume ++
		case VK_SUBTRACT:// Volume --
			if(SouthernVideo()) PostMessage(MainWindow,WM_DEBUG,0,0L);
			if((long)lParam<0) PostMessage(AudioMainWindow,WM_KEYUP,wParam,lParam);
			else PostMessage(AudioMainWindow,WM_KEYDOWN,wParam,lParam);
			break;
		///////////////////// New Feature //////////////
		case VK_PAUSE:
			if((long)lParam<0)	//PAUSE KEY ONLY up
				PostMessage(MainWindow,WM_STOPVIDEO,0,0L);
			break;
		case VK_F1:	//F1 key DOWN & UP
			if((long)lParam>0)//DOWN
				PostMessage(MainWindow,WM_STEPVIDEO,0,0L);
			break;
		case VK_F12:// F12 only UP
			if((long)lParam<0)
				PostMessage(MainWindow,WM_CUTPICTURE,0,0L);
			break;
		}
	return 1;
}
//////////////////////////////////////////////////