////////////////////////////////////////////////////////
//	Get Machine Feature with BIOS CPU & HardDisk
//		Compare This Feature with the
//	feature data file that built on installed.
//		    Southern.Liang
//		       1996.5.25
////////////////////////////////////////////////////////
#pragma	option	-zCOTHER_TEXT
#pragma	inline
#include "DOS.H"
#include "VCDAPI.H"

#define	CPUID()	__emit__(0x0F,0xA2)
char	CPUTypeString[16];
static	int	GetCPUID(void)
{
	asm	pushfd
	asm	pop	eax
	asm	mov	ecx,eax
	asm	xor	eax,0x0200000;
	asm	push	eax
	asm	popfd
	asm	pushfd
	asm	pop	eax
	asm	xor	eax,ecx
	asm	mov	ax,4
	asm	je	RETURN
	asm	push	ebx
	asm	push	ecx
	asm	push	edx
	asm	xor	eax,eax
	CPUID();
	asm	mov	dword ptr CPUTypeString,ebx
	asm	mov	dword ptr CPUTypeString+4,edx
	asm	mov	dword ptr CPUTypeString+8,ecx
	asm	mov	eax,1
	CPUID();
	asm	shr	eax,8
	asm	and	eax,0x0F
	asm	pop	edx
	asm	pop	ecx
	asm	pop	ebx
RETURN:
	return	_AX;
}
int	PASCAL	FAR	GetCPUType(void)
{
	int	Type;
	Type=GetWinFlags();
	Type=	(Type & WF_CPU286) ? 2 :
		(Type & WF_CPU386) ? 3 :
		(Type & WF_CPU486) ? 4 : -1;
	if(Type==4)
		{//Be 486 or later
		Type=GetCPUID();
		}
	if(Type!=-1)
		{
		Type*=100;
		Type+=86;
		}
	return	Type;
}
/*************************\
 Encrypt with key
 Retrun:Secret number of t
\*************************/
static	unsigned char Encrypt(unsigned char t,unsigned char key)
{
	asm 	mov	al,t
	asm 	mov	bl,key
	mark1:
	asm 	test bl,0xE7	//Can Be any value
	asm 	jpe  short mark2
	asm 	stc
	mark2:
	asm 	rcr	bl,1
	asm 	dec	al
	asm 	jnz short	mark1
	asm 	mov key,bl
	return 	key;
}
unsigned char	Feature[1024];
static	void 	SetEncode(void)
{
	int		i,j;

	Feature[1]=Encrypt(Feature[1],Feature[0]);//Feature[0]&0xF0
	for(i=1;i<511;i++)
		{
		Feature[i+1]=Encrypt(Feature[i+1],Feature[i]);
		}
}
static	int	BeZero(void)
{
	int	i;
	int	Zero=0;
	for(i=1;i<512;i++)
		{
		if(Feature[i]==0) Zero++;
		}
	if(Zero>128) return 1;
	return 0;
}
static	void	EncodeXORAdd(void)
{
	int	i;
	for(i=0;i<512;i++)
		{
		Feature[512+i]=Feature[i]^(~i);
		}
}
unsigned char	FileFeature[1024];
static	int	DataCompare(void)
{
	int	i;
	int	Ret;
	Ret=1;
	for(i=0;i<1024;i++)
		{
		if(FileFeature[i]!=Feature[i])
			{
			Ret=0;
			break;
			}
		}
	return	Ret;
}
static	int	LocalCompare(void)
{
	int	i;
	unsigned char	Data;
	int	Ret=1;
	for(i=0;i<512;i++)
		{
		Data=FileFeature[512+i]^(~i);
		if(Data!=FileFeature[i])
			{
			Ret=0;
			break;
			}
		}
	return	Ret;
}
unsigned pascal far __F000H(void);
int	PASCAL FAR	CheckSerialInstall(void)
{
	HFILE		hFile;
	unsigned 	i;
	unsigned char far *	Ptr;
	OFSTRUCT	OpenStruct;

	Ptr=MK_FP(FP_OFF(__F000H),0);
	for(i=0;i<256;i++) Feature[i]=*(Ptr+i);
	GetFAT(3,&Feature[256]);//Get C driver fat info
	Feature[257]='S';	//The FAT ID not same in Win95 & windows 3.xx
	Feature[258]&=0xF0;	//On 32 bit File access windows will less 2 cluster
	*(int *)&Feature[256+6]=GetCPUType();	//Get CPU Type.	All 8 bytes
	for(i=0;i<248;i++) Feature[256+8+i]=*(Ptr+i+256);
	//////// All 512 Byte /////////
	for(i=0;i<512;i++) Feature[512+i]=Feature[i];
	///////////////////////////////
	hFile=OpenFile("SOFTVCD.DAT",&OpenStruct,OF_EXIST);
	if(hFile==HFILE_ERROR)
		{
		return 4;	//The DATA File not present KILL them.
		}
	hFile=_lopen("SOFTVCD.DAT",READ);
	_lread(hFile,FileFeature,1024);
	_lclose(hFile);
	////////////////////////////////
	Feature[0]=FileFeature[0];
	SetEncode();
	/////////////XOR++/////////////
	EncodeXORAdd();
	////////////////////////////////
	i=LocalCompare();
	if(i==0){
		return 4;	//Modify the data Kill them
		}
	i=DataCompare();
	if(i==0){
		return 2;	//Copy to other computer Kill them.
		}
	return 0;
}