#include <io.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <errno.h>
#include <stdlib.h>

#include <windows.h>
#include <conio.h>
#include "dostsr.h"

#define FLAGS_OPEN            0x04

#define DOS_STATUS_OUT        0x07
#define DOS_STATUS_IN         0x06
#define DOS_READ              0x3F
#define DOS_WRITE             0x40

#define SET( value, mask )    value |= mask
#define CLR( value, mask )    value &= (~mask)

DEVICECONTEXT Device1 = { 0 };
DRIVERPARAMS DefaultParams = { 1024 };
DRIVERCAPS DriverCaps = { 0x0101 };

BOOL ValidHandle( HDEVICE hDevice );
WORD DosGetStatus( WORD hnd, WORD InOut, BOOL *pReady );
WORD DosReadOrWrite( WORD hnd, WORD ReadOrWrite, LPBYTE lpBuf, LPWORD pcbBytes );
WORD DosGetDeviceData( WORD hnd, WORD *pData );

HDEVICE FAR PASCAL _export DeviceOpen(  )
{
	HDEVICE	hDevice;
	WORD		usData;

	OutputDebugString( "DeviceOpen\n");

	hDevice = &Device1;

	if (hDevice->bFlags & FLAGS_OPEN)
		return (HDEVICE)-1;

	hDevice->usDosHandle = _open( "com1" , O_BINARY | O_RDWR );
	if (hDevice->usDosHandle == -1)
		return (HDEVICE)-1;

	hDevice->params = DefaultParams;

	SET( hDevice->bFlags, FLAGS_OPEN);

	return hDevice;
}

WORD FAR PASCAL _export DeviceClose( HDEVICE hDevice )
{
	OutputDebugString( "DeviceClose\n");

	if (!ValidHandle( hDevice ))
		return (HDEVICE)-1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return (HDEVICE)-1;

	CLR( hDevice->bFlags, FLAGS_OPEN );

	_close( hDevice->usDosHandle );

	return 0;
}

WORD FAR PASCAL _export DeviceGetWriteStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	BOOL	bReady;

	OutputDebugString( "DeviceGetWriteStatus\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

   DosGetStatus( hDevice->usDosHandle, DOS_STATUS_OUT, &bReady );
	if (bReady)
	{
		*pusStatus = 1;		// ready to transmit
	}
	else
	{
		*pusStatus = 0;		// not ready to transmit
	}

	return 0;
}

WORD FAR PASCAL _export DeviceGetReadStatus( HDEVICE hDevice, LPWORD pusStatus )
{
	BOOL	bReady;

	OutputDebugString( "DeviceGetReadStatus\n");

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

   DosGetStatus( hDevice->usDosHandle, DOS_STATUS_IN, &bReady );
	if (bReady)
	{
		*pusStatus = 1;		// data ready
	}
	else
	{
		*pusStatus = 0;		// no data ready
	}

	return 0;
}

WORD FAR PASCAL _export DeviceWrite( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	OutputDebugString( "DeviceWrite\n");

	if (!lpData)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	DosReadOrWrite( hDevice->usDosHandle, DOS_WRITE, lpData, pcBytes );

	return 0;
}

WORD FAR PASCAL _export DeviceRead( HDEVICE hDevice, LPBYTE lpData, LPWORD pcBytes )
{
	WORD		i;

	OutputDebugString( "DeviceRead\n");

	if (!lpData)
	 	return -1;

	if (!ValidHandle( hDevice ))
		return -1;

	if ((hDevice->bFlags & FLAGS_OPEN) == 0)
		return -1;

	DosReadOrWrite( hDevice->usDosHandle, DOS_READ, lpData, pcBytes );

	return 0;
}

WORD FAR PASCAL _export DeviceSetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParams )
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

WORD FAR PASCAL _export DeviceGetDriverParams( HDEVICE hDevice, PDRIVERPARAMS pParams )
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

WORD FAR PASCAL _export DeviceGetDriverCapabilities( HDEVICE hDevice, PPDRIVERCAPS ppDriverCaps )
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

WORD DosGetDeviceData( WORD hnd, WORD *pData )
{
	WORD	rc = 0;
	WORD  data;         

	_asm
	{
		mov	ah, 0x44
		mov   al, 0x00 
		mov	bx, hnd
		int	21h
		jnc   ok
		mov   rc, ax
		jmp   xit
ok:	mov   data, ax
		jmp   xit
xit:
	}

	*pData = data;                                                               

	return rc;
}

WORD DosGetStatus( WORD hnd, WORD InOut, BOOL *pReady )
{
	WORD	rc = 0;
	BYTE  stat;         

	*pReady = 0;
	_asm
	{
		mov	ax, InOut
		mov	ah, 0x44
		mov	bx, hnd
		int	21h
		jnc   ok
		mov   rc, ax
		jmp   xit
ok:	mov   stat, al
		jmp   xit
xit:
	}

	*pReady = (stat == 0xFF ? TRUE : FALSE );

	return rc;
}

WORD DosReadOrWrite( WORD hnd, WORD ReadOrWrite, LPBYTE lpBuf, LPWORD pcbBytes )
{
	WORD	rc = 0;
	WORD	cBytes = *pcbBytes;

	_asm
	{
		mov	ax, ReadOrWrite
		xchg  ah, al
		mov	bx, hnd
		mov   cx, cBytes
		push  ds
		lds   di, lpBuf
		mov   dx, di
		int	21h
		pop   ds
		jnc   ok
		mov   rc, ax
		jmp   xit
ok:	mov   cBytes, ax
		jmp   xit
xit:
	}

	*pcbBytes = cBytes;

	return rc;

}

#ifdef DOS
main()
{
   char abOut[4], abIn[4];
	unsigned short status;
	HDEVICE hDev;
	unsigned short cb;

	hDev = DeviceOpen();
	DeviceGetWriteStatus( hDev, &status );
	cb = 3;
	abOut[0] = 'a';
	abOut[1] = 't';
	abOut[2] = '\r';
	DeviceWrite( hDev, abOut, &cb );
	DeviceGetReadStatus( hDev, &status );
	DeviceRead( hDev, abIn, &cb );
	DeviceClose( hDev );
}
#endif
