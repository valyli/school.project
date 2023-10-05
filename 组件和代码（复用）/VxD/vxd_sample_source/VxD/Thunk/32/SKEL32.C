#include <windows.h>
#include "..\16\skeleton.h"

DEVICECONTEXT Device1 = { 0 };
DRIVERPARAMS DefaultParams = { 1024 };

BOOL WINAPI SKELETON_ThunkConnect32(LPSTR pszDll16,
    LPSTR pszDll32, HINSTANCE hInst, DWORD dwReason);
 
BOOL WINAPI DllMain(HINSTANCE hDllInst, DWORD dwReason, LPVOID lpvReserved)
{
    if (!(SKELETON_ThunkConnect32("SKELETON.DLL", // name of 16-bit DLL
            "SKEL32.DLL",                   // name of 32-bit DLL 
            hDllInst, dwReason))) {
        return FALSE; 
    } 
    return TRUE; 
}

#define DLLEXPORT __declspec( dllexport )

DLLEXPORT HDEVICE APIENTRY DeviceOpen32( void )
{
   return DeviceOpen();
}

DLLEXPORT int APIENTRY DeviceClose32( HDEVICE hDevice )
{
   return DeviceClose( hDevice );
}

DLLEXPORT int APIENTRY DeviceGetWriteStatus32( HDEVICE hDevice, LPWORD pusStatus )
{
   return DeviceGetWriteStatus( hDevice, pusStatus );
}

DLLEXPORT int APIENTRY DeviceGetReadStatus32( HDEVICE hDevice, LPWORD pusStatus )
{
   return DeviceGetReadStatus( hDevice, pusStatus );
}

DLLEXPORT int APIENTRY DeviceWrite32( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
   return DeviceWrite( hDevice, lpData, pcBytes );
}

DLLEXPORT int APIENTRY DeviceRead32( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
   return DeviceRead( hDevice, lpData, pcBytes );
}

DLLEXPORT int APIENTRY DeviceSetDriverParams32( HDEVICE hDevice, PDRIVERPARAMS pParms )
{
   return DeviceSetDriverParams( hDevice, pParms );
}

DLLEXPORT int APIENTRY DeviceGetDriverParams32( HDEVICE hDevice, PDRIVERPARAMS pParms )
{
   return DeviceGetDriverParams( hDevice, pParms );
}

DLLEXPORT int APIENTRY DeviceGetDriverCapabilities32( HDEVICE hDevice, PPDRIVERCAPS ppDriverCaps )
{
   return DeviceGetDriverCapabilities( hDevice, ppDriverCaps );
}




