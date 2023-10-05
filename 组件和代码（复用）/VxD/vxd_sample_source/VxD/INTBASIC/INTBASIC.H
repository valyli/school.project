#define FLAGS_ON_SLAVE_PIC    0x01
#define FLAGS_OPEN            0x02
#define FLAGS_RXQOVER			0x04

#define MASTER_PIC_CTRL       0x20
#define MASTER_PIC_MASK       0x21
#define SLAVE_PIC_CTRL        0xA0
#define SLAVE_PIC_MASK        0xA1
#define EOI                   0x20

#define SET( value, mask )    value |= mask
#define CLR( value, mask )    value &= (~mask)

typedef struct
{
	WORD	usReadBufSize;
} DRIVERPARAMS, FAR * PDRIVERPARAMS;

typedef struct
{
	WORD	version;
} DRIVERCAPS, FAR * PDRIVERCAPS;
typedef PDRIVERCAPS FAR * PPDRIVERCAPS;

typedef void (FAR interrupt *VOIDINTPROC)();

typedef struct
{
   char far *Start;
   WORD     Size;
   WORD     In;
   WORD     Out;
} BUFINFO;

typedef struct
{
	WORD		usDevNumber;
	WORD		usIoBase;
	BYTE		bIrq;
	BYTE		bFlags;
  HWND    hwnd;
   VOIDINTPROC pfOldHandler;
	BUFINFO	RxBuf;	
	BUFINFO	TxBuf;	
   DRIVERPARAMS params;
} DEVICECONTEXT, FAR *HDEVICE;

HDEVICE FAR PASCAL DeviceOpen( HWND hwnd );
int FAR PASCAL DeviceClose( HDEVICE );
int FAR PASCAL DeviceGetWriteStatus( HDEVICE, LPWORD pusStatus );
int FAR PASCAL DeviceGetReadStatus( HDEVICE, LPWORD pusStatus );
int FAR PASCAL DeviceWrite( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
int FAR PASCAL DeviceRead( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
int FAR PASCAL DeviceSetDriverParams( HDEVICE, PDRIVERPARAMS pParms );
int FAR PASCAL DeviceGetDriverParams( HDEVICE, PDRIVERPARAMS pParms );
int FAR PASCAL DeviceGetDriverCapabilities( HDEVICE, PPDRIVERCAPS ppDriverCaps );

extern DEVICECONTEXT Device1;
