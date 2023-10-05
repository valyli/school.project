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
   BOOL		bFlags;
   DRIVERPARAMS params;
   WORD		usDosHandle;
} DEVICECONTEXT, FAR *HDEVICE;

HDEVICE FAR PASCAL DeviceOpen( void );
WORD FAR PASCAL DeviceClose( HDEVICE );
WORD FAR PASCAL DeviceGetWriteStatus( HDEVICE, LPWORD pusStatus );
WORD FAR PASCAL DeviceGetReadStatus( HDEVICE, LPWORD pusStatus );
WORD FAR PASCAL DeviceWrite( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
WORD FAR PASCAL DeviceRead( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
WORD FAR PASCAL DeviceSetDriverParams( HDEVICE, PDRIVERPARAMS pParms );
WORD FAR PASCAL DeviceGetDriverParams( HDEVICE, PDRIVERPARAMS pParms );
WORD FAR PASCAL DeviceGetDriverCapabilities( HDEVICE, PPDRIVERCAPS ppDriverCaps );

