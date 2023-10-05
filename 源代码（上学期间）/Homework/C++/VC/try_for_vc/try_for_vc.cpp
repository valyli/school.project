// try_for_vc.cpp : Defines the entry point for the application.
//

#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	char lpszClassName[]="´°¿Ú";
	char lpszTitle[]="My_windows";

	wndclass.style=0;
	wndclass.lpfnWndProc=WndProc;
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.hInstance=hInstance;
	wndclass.hIcon=LoadIcon(Null,IDI_APPLICATION);
	wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground=GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName=NULL;
	wndclass.lpszClassName=lpszClassName;
//-----------------------------------------------------------
	if(! RegisterClass(&wndclass))
	{
		MessageBeep(0);
		return FALSE;
	}


	

	return 0;
}



