#include <windows.h>
#include "driver.h"

DEVICECONTEXT Device1 = { 0 };
DRIVERPARAMS DefaultParams = { 1024 };

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




