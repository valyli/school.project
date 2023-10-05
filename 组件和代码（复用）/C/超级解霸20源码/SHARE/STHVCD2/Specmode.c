////////////////////////////////////////////////////////
//	   Buildin 10E mode supported driver
//	   For S3 86xx,S3 Trioxx and GD54xx
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#include <windows.h>
#include "DOS.H"
#include "VCDAPI.H"

unsigned pascal far __C000H(void);
unsigned pascal far __F000H(void);

extern	int	VESACanUse;
int	VideoCardType=0;
int	SubType=0;
void  PASCAL FAR	SearchVESAType(char far *OEMPtr)
{//This pointer is real mode pointer
	WORD	i;
	int	Len;
	WORD	Seg;

	Seg=FP_SEG(OEMPtr);
	if(Seg==0xC000)
		{
		OEMPtr=MK_FP(FP_OFF(__C000H),FP_OFF(OEMPtr));
		}
	else 	if(Seg==0xF000)
			{
			OEMPtr=MK_FP(FP_OFF(__F000H),FP_OFF(OEMPtr));
			}
		else	{//Other DOS Mem.
			////////// Segment -> Selector ///////////
			_BX=FP_SEG(OEMPtr);
			_AX=2;
			geninterrupt(0x31);	//DOS Segment to Selector.
			asm	jnc	short	NEXT3;
			_AX=0;//Error
			NEXT3:
			*((WORD *)&OEMPtr+1)=_AX;//High WORD = Selector.
			}
	if(FP_SEG(OEMPtr)==0)	return;
	Len=lstrlen(OEMPtr);
	Len-=1;
	if(Len<0) return;
	for(i=0;i<Len;i++)
		{//Search S3
		if(*(WORD far *)(OEMPtr+i)==0x3353)	//' S3 '
			{
			VideoCardType=3;
			break;
			}
		if(*(DWORD far *)(OEMPtr+i)==0x34354447)//'GD54'
			{//Be GD54xx
			VideoCardType=5;
			break;
			}
//		if(*(DWORD far *)(OEMPtr+i)==0x35374447)//'GD75'
//			{//Be GD54xx
//			VideoCardType=75;
//			break;
//			}
		}
	if(VideoCardType==3)
		{
		for(i=0;i<Len;i++)
			{//Search S3 86 or Trio
			if(*(WORD far *)(OEMPtr+i)==0x3638)//'86'
				{
				SubType=86;
				break;
				}
			if(*(DWORD far *)(OEMPtr+i)==0x6F697254)//Trio
				{
				SubType=0x100;	//Trio
				break;
				}
			}
		}
}
int PASCAL FAR	TestSupportCard(void)
{
	BYTE far *Ptr;
	WORD	i;
	int	True;

	if(VESACanUse==0)	return 8;//Not support VESA Call
	if(VideoCardType!=0)
		{
		if(VideoCardType==3)
			{
			if(SubType==86) return 163;
			else	{
				if(SubType==0x100) return 16;
				else	return 8;
				}
			}
		if(VideoCardType==5)	//GD54xx
			return 16;
		}

	i=FP_OFF(__C000H);
	Ptr=MK_FP(i,0);	//Point to C000:0
	if(*(WORD far *)(Ptr)!=0xAA55)	return 8;
	True=0;
	for(i=0;i<0x120;i++)
		{//Search S3
		if(*(DWORD far *)(Ptr+i)==0x20335320)	//' S3 '
			{//Be S3
			VideoCardType=3;
			break;
			}
		if(*(DWORD far *)(Ptr+i)==0x34354447)	//'GD54'
			{//Be GD54xx
			VideoCardType=5;
			break;
			}
//		if(*(DWORD far *)(Ptr+i)==0x35374447)//'GD75'
//			{//Be GD75xx
//			VideoCardType=75;
//			True=1;
//			break;
//			}
		}
	if(VideoCardType==3)
		{
		for(i=0;i<0x120;i++)
			{//Search S3 86 or Trio
			if(*(DWORD far *)(Ptr+i)==0x3638)//'86'
				{
				SubType=86;
				True=1;
				break;
				}
			if(*(DWORD far *)(Ptr+i)==0x6F697254)//Trio
				{
				SubType=0x100;	//Trio
				True=1;
				break;
				}
			}
		}
	if(VideoCardType==5)
		{
		True=1;
		}
	return	True? 16:8;	//Normal support 13 mode 8 bits color
}
static	void	EnableRAMDAC(void)
{
	inportb(0x3C8);
	inportb(0x3C6);inportb(0x3C6);
	inportb(0x3C6);inportb(0x3C6);
}
static	void	SetS386Mode10E(void)
{
	int	Port;
	outport(0x3D4,0x4838);outport(0x3D4,0xA539);	//Unlock
	outportb(0x3D4,0x31);
	Port=inportb(0x3D5);
	outportb(0x3D5,Port&0xCF);
	outportb(0x3D4,0x43);
	Port=inportb(0x3D5);
	outportb(0x3D5,Port&0xF9);
	outportb(0x3D4,0x51);
	Port=inportb(0x3D5);
	outportb(0x3D5,Port&0xC0);
	outportb(0x3D4,0x58);
	Port=inportb(0x3D5);
	outportb(0x3D5,Port&0xEC);
	outport(0x3D4,0x0059);outport(0x3D4,0x0A5A);
	outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//lock
	/////////////////////////////
	EnableRAMDAC();
	outportb(0x3C6,0);
	inportb(0x3C8);	//Disable RAMDAC
	_AX=3;
	geninterrupt(0x10);	//To TEXT mode.
	_AX=0x4F02;
	_BX=0x101;
	geninterrupt(0x10);
	outport(0x3D4,0x4838);outport(0x3D4,0xA539);	//Unlock
	outportb(0x3D4,0x31);
	Port=inportb(0x3D5);
	outportb(0x3D5,Port|0x09);
	outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//lock
	EnableRAMDAC();
	outportb(0x3C6,0xC0);	//16 bit RAMDAC
	inportb(0x3C8);	//Disable RAMDAC
	//////////////////
	outport(0x3C4,0x0100);
	Port=inportb(0x3CC);
	outportb(0x3C2,0x63);
	outport(0x3C4,0x0101);
	outport(0x3C4,0x0300);
	///////////////////
	outport(0x3D4,0x0E11);
	////////////// CRTC //////////
	outport(0x3D4,0xBF06);
	outport(0x3D4,0x1F07);
	outport(0x3D4,0x4109);
	outport(0x3D4,0x9C10);
	outport(0x3D4,0x8E11);
	outport(0x3D4,0x8F12);
	outport(0x3D4,0x9615);
	outport(0x3D4,0xB916);
	////////////////////
	outport(0x3D4,0x5013);	//offset
	////////////
	//Clear screen here
	////////////
	outport(0x3D4,0x4838);outport(0x3D4,0xA539);	//Unlock
	outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//lock
}
static	void	SetGD54Mode10E(void)
{	//GD542x
	int	Port;
	outportb(0x3C4,0x0F);
	outportb(0x3C5,0x14);
	outportb(0x3CE,0x0B);
	outportb(0x3CF,0x00);
	/////////////////////////////
	EnableRAMDAC();
	outportb(0x3C6,0);
	inportb(0x3C8);	//Disable RAMDAC
	_AX=3;
	geninterrupt(0x10);	//To TEXT mode.
	_AX=0x5F;
	geninterrupt(0x10);
	/////////////////////
	outport(0x3C4,0x1206);
	outportb(0x3D4,0x1B);
	outportb(0x3D5,0x22);
	outportb(0x3C4,0x0F);
	outportb(0x3C5,0xB4);
	outportb(0x3CE,0x0B);
	outportb(0x3CF,0x20);
	/////////////////////
	EnableRAMDAC();
	inportb(0x3C6);
	EnableRAMDAC();
	outportb(0x3C6,0xE1);	//16 bit RAMDAC
	inportb(0x3C8);		//Disable RAMDAC
	//////////////////
	outport(0x3C4,0x0100);
	outportb(0x3C2,0x63);
	outport(0x3C4,0x0101);
	outport(0x3C4,0x0300);
	///////////////////
	outport(0x3D4,0x0E11);
	////////////// CRTC //////////
	outport(0x3D4,0xBF06);
	outport(0x3D4,0x1F07);
	outport(0x3D4,0x4109);
	outport(0x3D4,0x9C10);
	outport(0x3D4,0x8E11);
	outport(0x3D4,0x8F12);
	outport(0x3D4,0x9615);
	outport(0x3D4,0xB916);
	////////////////////
	outport(0x3D4,0x5013);	//offset
	////////////
	//Clear screen here
	////////////
	outport(0x3CE,0x0009);
}
static	void	SetGD75Mode10E(void)
{	//GD75xx
	int	Port;
	_AX=0x5F;
	geninterrupt(0x10);
	EnableRAMDAC();
	outportb(0x3C6,0xC0);	//16 bit RAMDAC
	inportb(0x3C8);		//Disable RAMDAC
	//////////////////
	outport(0x3C4,0x0100);
	outportb(0x3C2,0x63);
	outport(0x3C4,0x0101);
	outport(0x3C4,0x0300);
	///////////////////
	outport(0x3D4,0x0E11);
	////////////// CRTC //////////
	outport(0x3D4,0xBF06);
	outport(0x3D4,0x1F07);
	outport(0x3D4,0x4109);
	outport(0x3D4,0x9C10);
	outport(0x3D4,0x8E11);
	outport(0x3D4,0x8F12);
	outport(0x3D4,0x9615);
	outport(0x3D4,0xB916);
	////////////////////
	outport(0x3D4,0x5013);	//offset
	////////////
	//Clear screen here
	////////////
	outport(0x3CE,0x0009);
}

static	void	SetS3Linear(DWORD Linear)
{
	int	Port;
	Linear>>=16;
	outport(0x3D4,0x4838);outport(0x3D4,0xA539);	//Unlock
	outport(0x3D4,0x8C31);	//No 64K page blanking
	outport(0x3D4,0x1958);	//Video buffer size 1M
	outportb(0x3D4,0x5A);	//Linear's low 8bit
	outportb(0x3D5,Linear);
	Linear>>=8;
	outportb(0x3D4,0x59);	//Linear's high 8bit
	outportb(0x3D5,Linear);
	outportb(0x3D4,0x40);
	Port=inportb(0x3D5);
	outportb(0x3D4,0x40);
	outportb(0x3D5,Port&0xEF);	//Zero wait state
	outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//Unlock
}
static	DWORD	GetS3LinearState(void)
{
	DWORD	Base;
	int	Port;
	outport(0x3D4,0x4838);outport(0x3D4,0xA539);	//Unlock
	outportb(0x3D4,0x58);
	Port=inportb(0x3D5);
	if((Port&3)==0)
		{//Not Linear mode.It is banking.
		outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//Unlock
		return 0xA0000;
		}
	if((Port&0x10)==0)
		{//Not enable linear addressing mode.
		outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//Unlock
		return 0xA0000;
		}
	outportb(0x3D4,0x59);	//0x0200's high 8bit
	Base=inportb(0x3D5);
	Base<<=8;
	outportb(0x3D4,0x5A);	//0x0200's low 8bit
	Base|=inportb(0x3D5);
	outport(0x3D4,0x0038);outport(0x3D4,0x0039);	//Unlock
	Base<<=16;
	return Base;
}
DWORD	S3Linear=0;
extern	DWORD	VideoPhysBase;
void	SetVideoBufferBase(DWORD Base);
void	PASCAL FAR	SetVideoMode(void)
{
	if(VideoCardType==3)
		{//Only S3 86 banking
		/////////////////
		if(SubType==86)
			{//S3 86xx
			SetS386Mode10E();
			}
		else	{//Trio 32/64
			if(SubType==0x100)
				{
				_AX=0x13;//Graphics mode VESA ready
				geninterrupt(0x10);
				InitS3Trio10E();
				}
			}
		}
	//////////// Cirrus Logic GD54xx //////////////
	if(VideoCardType==5)
		{//GD54xx
		SetGD54Mode10E();
		}
	//////////// Cirrus Logic GD75xx //////////////
	if(VideoCardType==75)
		{//GD75xx
		SetGD75Mode10E();
		}
}
/////////////////////////////////////////////////
