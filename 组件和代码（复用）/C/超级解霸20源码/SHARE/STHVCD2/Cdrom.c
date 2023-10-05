//////////////////////////////////////////////////////////
//			CDROM operation
//			Southern.Liang
//			  1996.5.25
//////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include "DOS.H"
#include "VCDAPI.H"

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

typedef	struct	IOCTLtag
	{
	unsigned char	HeaderLength;
	unsigned char	SubUnit;
	unsigned char	Command;
	unsigned short	Status;
	unsigned char	Noused[8];
	}IOCTL;
typedef	struct	WRITEIOtag
	{
	IOCTL		IoCtl;
	unsigned char	BPB;		//0
	unsigned char far * CmdBuffer;
	unsigned short	CmdSize;
	unsigned short	StartSector;	//0
	unsigned long	VolumeID;	//0
	}WRITEIO;
////////////////Open Door////////////
extern	STACK	Stack;
extern	int	AutoVCDPlay;
extern	int	DrvNum;
extern	char	CDROM[10];	//CDROM Driver Name
static	int    	_OpenCDROMDoor(int CDROM,void far *Ptr)
{
	Stack.CX=CDROM;
	Stack.ES=FP_SEG(Ptr);
	Stack.BX=FP_OFF(Ptr);
	Stack.AX=0x1510;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x2F;
	_AX=0x300;
	geninterrupt(0x31);
	return 0;
}
static	int    	_CloseCDROMDoor(int CDROM,void far *Ptr)
{
	Stack.CX=CDROM;
	Stack.ES=FP_SEG(Ptr);
	Stack.BX=FP_OFF(Ptr);
	Stack.AX=0x1510;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x2F;
	_AX=0x300;
	geninterrupt(0x31);
	return 0;
}
////////////////Open Door////////////
void PASCAL FAR	OpenCDROMDoor(void)
{
	unsigned short	DOSSel,DOSSeg;
	WRITEIO far *	WriteIO;
	BYTE    far *	Cmd;
	int	CDRom;
	int	i;

//	AutoVCDPlay=0;
	GlobalDosAlloc(sizeof(WRITEIO)+2);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		return;

	WriteIO=MK_FP(DOSSel,0);
	Cmd=(BYTE far *)MK_FP(DOSSel,sizeof(WRITEIO));
	WriteIO->IoCtl.HeaderLength=sizeof(WRITEIO);
	WriteIO->IoCtl.SubUnit	=0;
	WriteIO->IoCtl.Command	=12;	//IOCTL OUTPUT
	WriteIO->IoCtl.Status	=0;
	WriteIO->BPB		=0;
	WriteIO->StartSector	=0;
	WriteIO->VolumeID	=0;
	WriteIO->CmdBuffer	=MK_FP(DOSSeg,sizeof(WRITEIO));
	WriteIO->CmdSize	=1;
	*Cmd=0;
	for(i=0;i<DrvNum;i++)
		{
		CDRom=CDROM[i]|0x20;
		CDRom-='a';
		_OpenCDROMDoor(CDRom,MK_FP(DOSSeg,0));
		}

	GlobalDosFree(DOSSel);
}
void PASCAL FAR	LockCDROM(int Code)//0-UnLock,1-Lock
{
	unsigned short	DOSSel,DOSSeg;
	WRITEIO far *	WriteIO;
	BYTE    far *	Cmd;
	int	CDRom;
	int	i;

	GlobalDosAlloc(sizeof(WRITEIO)+4);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		return;

	WriteIO=MK_FP(DOSSel,0);
	Cmd=(BYTE far *)MK_FP(DOSSel,sizeof(WRITEIO));
	WriteIO->IoCtl.HeaderLength=sizeof(WRITEIO);
	WriteIO->IoCtl.SubUnit	=0;
	WriteIO->IoCtl.Command	=12;	//IOCTL OUTPUT
	WriteIO->IoCtl.Status	=0;
	WriteIO->BPB		=0;
	WriteIO->StartSector	=0;
	WriteIO->VolumeID	=0;
	WriteIO->CmdBuffer	=MK_FP(DOSSeg,sizeof(WRITEIO));
	WriteIO->CmdSize	=1;
	*Cmd=1;	//Lock or UnLock CDROM
	*(Cmd+1)=Code;
	for(i=0;i<DrvNum;i++)
		{
		CDRom=CDROM[i]|0x20;
		CDRom-='a';
		_OpenCDROMDoor(CDRom,MK_FP(DOSSeg,0));
		}

	GlobalDosFree(DOSSel);
}
void PASCAL FAR	CloseCDROMDoor(void)
{
	unsigned short	DOSSel,DOSSeg;
	WRITEIO far *	WriteIO;
	BYTE    far *	Cmd;
	int	CDRom;
	int	i;

	GlobalDosAlloc(sizeof(WRITEIO)+2);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		return;

	WriteIO=MK_FP(DOSSel,0);
	Cmd=(BYTE far *)MK_FP(DOSSel,sizeof(WRITEIO));
	WriteIO->IoCtl.HeaderLength=sizeof(WRITEIO);
	WriteIO->IoCtl.SubUnit	=0;
	WriteIO->IoCtl.Command	=12;	//IOCTL OUTPUT
	WriteIO->IoCtl.Status	=0;
	WriteIO->BPB		=0;
	WriteIO->StartSector	=0;
	WriteIO->VolumeID	=0;
	WriteIO->CmdBuffer	=MK_FP(DOSSeg,sizeof(WRITEIO));
	WriteIO->CmdSize	=1;
	*Cmd=5;
	for(i=0;i<DrvNum;i++)
		{
		CDRom=CDROM[i]|0x20;
		CDRom-='a';
		_CloseCDROMDoor(CDRom,MK_FP(DOSSeg,0));
		}

	GlobalDosFree(DOSSel);
}
/////////////////////////////////////////////////////////
typedef	struct	READIOtag
	{
	IOCTL		IoCtl;
	unsigned char	BPB;		//0
	unsigned char far * CmdBuffer;
	unsigned short	CmdSize;
	unsigned short	StartSector;	//0
	unsigned long	VolumeID;	//0
	}READIO;

static	int	_CDROMCall(int CDROM,void far *Ptr)
{
	Stack.CX=CDROM;
	Stack.ES=FP_SEG(Ptr);
	Stack.BX=FP_OFF(Ptr);
	Stack.AX=0x1510;
	////////// Call Real INT //////////
	_ES=FP_SEG(&Stack);
	_DI=FP_OFF(&Stack);
	_CX=0;
	_BH=0;
	_BL=0x2F;
	_AX=0x300;
	geninterrupt(0x31);
	return _AX;
}

int PASCAL FAR	CDROMDoorClosed(void)
{//Test the CDROM's Door be closed
	unsigned short	DOSSel,DOSSeg;
	READIO far *	ReadIO;
	BYTE    far *	Cmd;
	DWORD   far *	RetCode;
	int	CDRom;
	int	i;
	int	Ret=1;

	GlobalDosAlloc(sizeof(READIO)+5);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		return	1;	//assume CDROM Close.

	ReadIO=MK_FP(DOSSel,0);
	Cmd=(BYTE far *)MK_FP(DOSSel,sizeof(READIO));
	RetCode=(DWORD far *)MK_FP(DOSSel,sizeof(READIO)+1);

	ReadIO->IoCtl.HeaderLength=sizeof(READIO);
	ReadIO->IoCtl.SubUnit	=0;
	ReadIO->IoCtl.Command	=3;	//IOCTL INPUT
	ReadIO->IoCtl.Status	=0;
	ReadIO->BPB		=0;
	ReadIO->StartSector	=0;
	ReadIO->VolumeID	=0;
	ReadIO->CmdBuffer	=MK_FP(DOSSeg,sizeof(READIO));
	ReadIO->CmdSize		=5;
	*Cmd=6;
	for(i=0;i<DrvNum;i++)
		{
		CDRom=CDROM[i]|0x20;
		CDRom-='a';
		_CDROMCall(CDRom,MK_FP(DOSSeg,0));
		if((*RetCode&1))	Ret=0;//Had some open still.
		}
	GlobalDosFree(DOSSel);

	return 	Ret;
}
int   PASCAL FAR	CDROMMediaChanged(void)//This function must on door closed.
{//After this founction program will error on CloseVideo()
	unsigned short	DOSSel,DOSSeg;
	READIO far *	ReadIO;
	BYTE    far *	Cmd;
	char    far *	RetCode;
	int	CDRom;
	int	i;
	int	Ret=0;

	GlobalDosAlloc(sizeof(READIO)+5);
	DOSSel=_AX;
	DOSSeg=_DX;
	if(DOSSel==0)	//Can't Allocate DOS Memory.
		return	0;	//assume CDROM Close.

	ReadIO=MK_FP(DOSSel,0);
	Cmd=(BYTE far *)MK_FP(DOSSel,sizeof(READIO));
	RetCode=(char far *)MK_FP(DOSSel,sizeof(READIO)+1);
	ReadIO->IoCtl.HeaderLength=sizeof(READIO);
	ReadIO->IoCtl.SubUnit	=0;
	ReadIO->IoCtl.Command	=3;	//IOCTL INPUT
	ReadIO->IoCtl.Status	=0;
	ReadIO->BPB		=0;
	ReadIO->StartSector	=0;
	ReadIO->VolumeID	=0;
	ReadIO->CmdBuffer	=MK_FP(DOSSeg,sizeof(READIO));
	ReadIO->CmdSize		=2;
	*Cmd=9;
	*RetCode=0;
	for(i=0;i<DrvNum;i++)
		{
		CDRom=CDROM[i]|0x20;
		CDRom-='a';
		_CDROMCall(CDRom,MK_FP(DOSSeg,0));
		if(*RetCode==-1)	Ret=1;//CDROM Media changed.
		}
	GlobalDosFree(DOSSel);

	return 	Ret;
}
