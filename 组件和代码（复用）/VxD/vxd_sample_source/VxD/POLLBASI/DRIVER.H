typedef struct
{
	WORD	usReadBufSize;
} DRIVERPARAMS, FAR * PDRIVERPARAMS;

typedef struct
{
	WORD	version;
} DRIVERCAPS, FAR * PDRIVERCAPS;
typedef PDRIVERCAPS FAR * PPDRIVERCAPS;

typedef struct
{
	WORD		usDevNumber;
	WORD		usIoBase;
   BOOL		bFlags;
	LPBYTE	lpReadBuf;
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

