#include <windows.h>
#include "skeleton.h"

DEVICECONTEXT Device1 = { 0 };
DRIVERPARAMS DefaultParams = { 1024 };

BOOL FAR PASCAL __export SKELETON_ThunkConnect16(LPSTR pszDll16,  
    LPSTR pszDll32, WORD hInst, DWORD dwReason); 
 
BOOL FAR PASCAL __export DllEntryPoint(DWORD dwReason, WORD hInst, 
        WORD wDS, WORD wHeapSize, DWORD dwReserved1, 
        WORD wReserved2) { 
    if (!(SKELETON_ThunkConnect16("SKELETON.DLL", // name of 16-bit DLL 
            "SKEL32.DLL",                   // name of 32-bit DLL 
            hInst, dwReason))) { 
        return FALSE; 
    } 
    return TRUE; 
}
 

HDEVICE FAR PASCAL _export DeviceOpen( void )
{
  OutputDebugString( "DeviceOpen\n");

	return &Device1;
}

int FAR PASCAL _export DeviceClose( HDEVICE hDevice )
{
	OutputDebugString( "DeviceClose\n");

	return 0;
}

int FAR PASCAL _export DeviceGetWriteStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	OutputDebugString( "DeviceGetWriteStatus\n");

	return 0;
}

int FAR PASCAL _export DeviceGetReadStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	OutputDebugString( "DeviceGetReadStatus\n");

	return 0;
}

int FAR PASCAL _export DeviceWrite( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	OutputDebugString( "DeviceWrite\n");

	return 0;
}

int FAR PASCAL _export DeviceRead( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	OutputDebugString( "DeviceRead\n");

	return 0;
}

int FAR PASCAL _export DeviceSetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParms )
{
	OutputDebugString( "DeviceSetDriverParams\n");

	return 0;
}

int FAR PASCAL _export DeviceGetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParms )
{
	OutputDebugString( "DeviceGetDriverParams\n");

	return 0;
}

int FAR PASCAL _export DeviceGetDriverCapabilities( HDEVICE hDevice, PPDRIVERCAPS ppDriverCaps )
{
	OutputDebugString( "DeviceGetDriverCapabilities\n");

	return 0;
}




