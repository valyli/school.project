#include <dos.h>
#include <windows.h>
#include <stdarg.h>
#include <string.h>

#include "testdriv.h"
#include "resource.h"
#include "driver.h"

HDEVICE		hDevice;
HINSTANCE 	hInst;
HWND        hwndMain;

char abData[ 16 ];

long FAR PASCAL _export WndProc( HWND hwnd, 
	WORD message, WORD wParam, LONG lParam )
{
  WORD  cbWritten, cbRead;
  WORD  usStatus;

	switch( message )
	{
	case WM_COMMAND:
		switch( wParam )
		{
		case IDM_OPEN:
			hDevice = DeviceOpen();
			break;

		case IDM_CLOSE:
			DeviceClose( hDevice );
			break;

		case IDM_GETWRITESTATUS:
			DeviceGetWriteStatus( hDevice, &usStatus );
			break;

		case IDM_GETREADSTATUS:
			DeviceGetReadStatus( hDevice, &usStatus );
			break;

		case IDM_WRITE:
      strcpy( abData, "at\r\n" );
      cbWritten = 4;
			DeviceWrite( hDevice, abData, &cbWritten );
			break;

		case IDM_READ:
      cbRead = 4;
			DeviceRead( hDevice, abData, &cbRead);
			break;

		case IDM_SETDRIVERPARAMS:
			DeviceSetDriverParams( hDevice, NULL );
			break;

		case IDM_GETDRIVERPARAMS:
			DeviceGetDriverParams( hDevice, NULL );
			break;

		case IDM_GETDRIVERCAPS:
			DeviceGetDriverCapabilities( hDevice, NULL );
			break;

		}
		break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		return( 0 );

	default:
		return( DefWindowProc( hwnd, message, wParam, lParam ) );

	}
}

int PASCAL WinMain( HANDLE hInstance,
			 HANDLE hPrevInstance,
			 LPSTR lpszCmdParam,
			 int nCmdShow )
{
	MSG          msg;
	WNDCLASS     wndclass;

	if (!hPrevInstance)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNCLIENT;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra   = 0;
		wndclass.cbWndExtra   = 0;
		wndclass.hInstance    = hInstance;
		wndclass.lpszMenuName = "DeviceMenu";
		wndclass.lpszClassName = "Test Drive";
		wndclass.hIcon  =  LoadIcon( NULL, IDI_APPLICATION );
		wndclass.hCursor = LoadCursor( NULL, IDC_ARROW );
		wndclass.hbrBackground = GetStockObject( WHITE_BRUSH );

		RegisterClass( &wndclass );
	}

	hwndMain = CreateWindow( "Test Drive",
			"Test Drive",
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, 
			300, 150,
			NULL, NULL, hInstance, NULL );

	hInst = hInstance;

	ShowWindow( hwndMain, nCmdShow );
	UpdateWindow( hwndMain );

	while( GetMessage( &msg, NULL, 0, 0 ))
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
		
	return( msg.wParam );
}
