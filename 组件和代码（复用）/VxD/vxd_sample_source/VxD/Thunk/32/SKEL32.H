#ifndef SKELETON_H
#define SKELETON_H

#include <windows.h>

typedef struct
{
	WORD		usDevNumber;
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

#ifndef DLL

#define DLLIMPORT __declspec( dllimport )

DLLIMPORT HDEVICE APIENTRY DeviceOpen32( void );
DLLIMPORT int APIENTRY DeviceClose32( HDEVICE );
DLLIMPORT int APIENTRY DeviceGetWriteStatus32( HDEVICE, LPWORD pusStatus );
DLLIMPORT int APIENTRY DeviceGetReadStatus32( HDEVICE, LPWORD pusStatus );
DLLIMPORT int APIENTRY DeviceWrite32( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
DLLIMPORT int APIENTRY DeviceRead32( HDEVICE, LPBYTE lpData, LPWORD pcBytes );
DLLIMPORT int APIENTRY DeviceSetDriverParams32( HDEVICE, PDRIVERPARAMS pParms );
DLLIMPORT int APIENTRY DeviceGetDriverParams32( HDEVICE, PDRIVERPARAMS pParms );
DLLIMPORT int APIENTRY DeviceGetDriverCapabilities32( HDEVICE, PPDRIVERCAPS ppDriverCaps );

#endif

#endif
