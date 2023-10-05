#define _WINDLL

#include <windows.h>
#include <conio.h>
#include "driver.h"
#include "uart.h"

#define FLAGS_OPEN            0x04

#define SET( value, mask )    value |= mask
#define CLR( value, mask )    value &= (~mask)

DEVICECONTEXT Device1 = { 0, 0x3F8, 0, NULL };
DRIVERPARAMS DefaultParams = { 1024 };
DRIVERCAPS DriverCaps = { 0x0101 };

BOOL ValidHandle( HDEVICE hDevice );

HDEVICE FAR PASCAL _export DeviceOpen( HWND hwnd )
{
	HDEVICE	hDevice;

	OutputDebugString( "DeviceOpen\n");

	hDevice = &Device1;

	if (hDevice->bFlags & FLAGS_OPEN)
		return (HDEVICE)-1;

	hDevice->params = DefaultParams;

   // Configure UART.
   _outp( hDevice->usIoBase + UART_REG_IER, 0 );
   _outp( hDevice->usIoBase + UART_REG_LCR, UART_LCR_DLAB );
   _outp( hDevice->usIoBase + UART_REG_BAUDLO, BAUD_1200 );
   _outp( hDevice->usIoBase + UART_REG_BAUDHI, 0 );
   _outp( hDevice->usIoBase + UART_REG_LCR, UART_LCR_8N1 );
	_inp( hDevice->usIoBase + UART_REG_LSR );
	_inp( hDevice->usIoBase + UART_REG_RDR );

	SET( hDevice->bFlags, FLAGS_OPEN);

	return hDevice;
}

int FAR PASCAL _export DeviceClose( HDEVICE hDevice )
{
	OutputDebugString( "DeviceClose\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	CLR( hDevice->bFlags, FLAGS_OPEN );

	return 0;
}

int FAR PASCAL _export DeviceGetWriteStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	OutputDebugString( "DeviceGetWriteStatus\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

   if (_inp( hDevice->usIoBase + UART_REG_LSR ) & UART_LSR_THRE)
	{
		*pusStatus = 1;		// ready to transmit
	}
	else
	{
		*pusStatus = 0;		// not ready to transmit
	}

	return 0;
}

int FAR PASCAL _export DeviceGetReadStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	OutputDebugString( "DeviceGetReadStatus\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

   if (_inp( hDevice->usIoBase + UART_REG_LSR ) & UART_LSR_RXRDY)
	{
		*pusStatus = 1;		// data ready
	}
	else
	{
		*pusStatus = 0;		// no data ready
	}

	return 0;
}

int FAR PASCAL _export DeviceWrite( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	WORD	i;

	OutputDebugString( "DeviceWrite\n");

	if (!lpData)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	for (i=0; i < *pcBytes; i++)
	{
   	while ((_inp( hDevice->usIoBase + UART_REG_LSR ) & UART_LSR_THRE) == 0)
			;
   	_outp( hDevice->usIoBase + UART_REG_THR, lpData[ i ] );
	}

	return 0;
}

int FAR PASCAL _export DeviceRead( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	WORD		i;

	OutputDebugString( "DeviceRead\n");

	if (!lpData)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	for (i=0; i < *pcBytes; i++)
	{
   	while ((_inp( hDevice->usIoBase + UART_REG_LSR ) & UART_LSR_RXRDY) == 0)
			;
   	lpData[i] = _inp( hDevice->usIoBase + UART_REG_RDR );
	}

	return 0;
}

int FAR PASCAL _export DeviceSetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParams )
{
	OutputDebugString( "DeviceSetDriverParams\n");

	if (!pParams)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	hDevice->params = *pParams;
  
	return 0;
}

int FAR PASCAL _export DeviceGetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParams )
{
	OutputDebugString( "DeviceGetDriverParams\n");

	if (!pParams)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	*pParams = hDevice->params;

	return 0;
}

int FAR PASCAL _export DeviceGetDriverCapabilities( HDEVICE hDevice, PPDRIVERCAPS ppDriverCaps )
{
	OutputDebugString( "DeviceGetDriverCapabilities\n");

	if (!ppDriverCaps)
		return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	*ppDriverCaps = &DriverCaps;

	return 0;
}

BOOL ValidHandle( HDEVICE hDevice )
{
	return (hDevice == &Device1);
}

