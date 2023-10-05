// This version of DRIVER.H was copied from the 
// SKELDLL directory. However, the DLLs in 
// POLLBASI and INTBASIC have exactly the same 
// function prototypes as this one, so the DRIVER.H 
// from either of those directories could be used 
// instead. (The DRIVER.H files in the three directories 
// differ only in the fields of the DEVICECONTEXT 
// structure). 

typedef struct
{
	WORD		usDevNumber;
	LPBYTE	lpReadBuffer;
} DEVICECONTEXT, FAR *HDEVICE;

typedef struct
{
	WORD	usReadBufSize;
} DRIVERPARAMS, FAR * PDRIVERPARAMS;

typedef struct
{
	WORD	version;
} DRIVERCAPS, FAR * PDRIVERCAPS;
typedef PDRIVERCAPS FAR * PPDRIVERCAPS;

HDEVICE FAR PASCAL DeviceOpen( void );
int FAR PASCAL DeviceClose( HDEVICE );
int FAR PASCAL DeviceGetWriteStatus( HDEVICE, LPWORD pusStatus );
int FAR PASCAL DeviceGetReadStatus( HDEVICE, LPWORD pusStatus );
int FAR PASCAL DeviceWrite( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
int FAR PASCAL DeviceRead( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
int FAR PASCAL DeviceSetDriverParams( HDEVICE, PDRIVERPARAMS pParms );
int FAR PASCAL DeviceGetDriverParams( HDEVICE, PDRIVERPARAMS pParms );
int FAR PASCAL DeviceGetDriverCapabilities( HDEVICE, PPDRIVERCAPS ppDriverCaps );

