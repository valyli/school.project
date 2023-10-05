#define APCVXD_REGISTER 	0x8100
#define APCVXD_RELEASEMEM	0x8101

typedef struct
{
	BOOL	 bVmCreated;
	DWORD    hVM;
} VMINFO;

