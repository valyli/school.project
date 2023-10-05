#include <windows.h>
#include <string.h> 
#include <stdio.h> 
#include "..\vxd\postvxd.h"

typedef void (far * PVOIDFN)( void );

HANDLE 	hInst;
PVOIDFN  pfVxDApi;
DWORD hVM = 0;
BOOL  bCreated = 0;


int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);
BOOL InitApplication(HANDLE);
BOOL InitInstance(HANDLE, int);
long CALLBACK __export MainWndProc(HWND, UINT, WPARAM, LPARAM);

PVOIDFN GetVxdApiEntry( int VxdId )
{
  PVOIDFN pfApi;

  _asm
  {
     xor di, di
     mov es, di
     mov bx, VxdId
     mov ax, 1684h
     int 2fh
     mov WORD PTR pfApi+2, es
     mov WORD PTR pfApi, di
  }

  return( pfApi );
}

int PASCAL WinMain(HANDLE hInstance, HANDLE hPrevInstance, LPSTR lpCmdLine, 
				int nCmdShow)
{
	MSG msg;	  

	if (hPrevInstance)  
        	return (FALSE);

	if (!InitApplication(hInstance)) 
	        return (FALSE);	

	if (!InitInstance(hInstance, nCmdShow))
		return (FALSE);

	while (GetMessage(&msg,	
        	NULL,	  
	        NULL, 		
	        NULL))		
	{
		TranslateMessage(&msg);    
		DispatchMessage(&msg);     
	}

	return (msg.wParam);       
}

BOOL InitApplication(HANDLE hInstance)
{
	WNDCLASS  wc;

	wc.style = NULL;	  	
	wc.lpfnWndProc = MainWndProc;	
					
	wc.cbClsExtra = 0;		
	wc.cbWndExtra = 0;      	
	wc.hInstance = hInstance; 	
	wc.hIcon = LoadIcon(hInstance, NULL);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName =  NULL;	
	wc.lpszClassName = "PostWin16";

	return (RegisterClass(&wc));
}

BOOL InitInstance(HANDLE hInstance, int nCmdShow)
{
	HWND hWnd;	
   WORD err;

	hInst = hInstance;

	hWnd = CreateWindow(
		"PostWin16",	  
		"PostWin16",  
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		CW_USEDEFAULT,		
		NULL,			
		NULL,			
		hInstance,		
		NULL 			
	);


	if (!hWnd)
		return (FALSE);      
    
	pfVxDApi = GetVxdApiEntry( POSTVXD_ID );
	if (!pfVxDApi)
	{
		MessageBox( hWnd, "Error, couldn't get VxD API", "USEAPI", MB_OK );
      return FALSE;
	}

	_asm {
		mov	ax, POSTVXD_REGISTER
		mov	bx, [hWnd]
		mov	cx, seg PostMessage
		mov	dx, offset PostMessage
		call	DWORD PTR pfVxDApi
      mov   err, ax
   }
   if (err)
	{
  		MessageBox( hWnd, "Error registering callback", "USEAPI", MB_OK );
		return FALSE;
	}  
    
	ShowWindow(hWnd, SW_SHOWNORMAL); 
	UpdateWindow(hWnd);		

	return (TRUE);               
}

long CALLBACK __export MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char buf[80]; 
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rect;
	
	switch (message)
	{
    case WM_USER_POSTVXD:       
            
		hVM = lParam;
		bCreated = wParam;
		InvalidateRect(hWnd, NULL, TRUE);
     	break;

    case WM_DESTROY:          
   	_asm {
   		mov	ax, POSTVXD_DEREGISTER
   		call	DWORD PTR pfVxDApi
      }
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		sprintf(buf, "VM %08lx was %s\r\n", hVM, bCreated ? "created" : "destroyed" );
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		DrawText(hdc, buf, -1, &rect, 0);
		EndPaint(hWnd, &ps);
		break;

    default:                 
		return (DefWindowProc(hWnd, message, wParam, lParam));
    }

    return (NULL);
}


