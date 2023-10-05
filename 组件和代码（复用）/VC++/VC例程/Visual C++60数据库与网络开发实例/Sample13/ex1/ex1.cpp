#include <windows.h>
#include <odbcinst.h>
#include <stdio.h>
#include "resource.h"
#include "ex1.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;
	wc.style=0; 
    wc.lpfnWndProc=MainWndProc; 
    wc.cbClsExtra=0; 
    wc.cbWndExtra=0; 
    wc.hInstance=hInstance; 
    wc.hIcon=LoadIcon(NULL,IDI_HAND); 
    wc.hCursor=LoadCursor(NULL,IDC_ARROW); 
    wc.hbrBackground=(struct HBRUSH__ *)GetStockObject(WHITE_BRUSH); 
    wc.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);
    wc.lpszClassName="MyClass";
	
	

	if (RegisterClass(&wc)==0){

		MessageBox(NULL,"Error","Failed to register class", MB_OK);
		return 0;
	}
	
	


	hWnd=CreateWindow(wc.lpszClassName,"My Window",WS_BORDER|WS_CAPTION|WS_OVERLAPPEDWINDOW|WS_SYSMENU|WS_VISIBLE,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);
	ShowWindow(hWnd,SW_MAXIMIZE);
	UpdateWindow(hWnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

return msg.wParam;
}

LRESULT CALLBACK MainWndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam )
{
	
	switch(uMsg)
	{
	case WM_COMMAND:
		switch(LOWORD( wParam ))
		{
		case ID_FILE_EXIT:
			if (MessageBox(hwnd,"Are you sure you want to quit","Information",MB_OKCANCEL) == IDOK)
			DestroyWindow(hwnd);
			break;
		case ID_DATABASE_ACCESS:
/*
If you want to create the DSN depending on the user input then you 
will need to follow the below procedure. To hardcode it you could just pass
"DSN=TestDB\0DBQ=D:\\Database\\Friends.mdb\0DEFAULTDIR=D:\\DATABASE\0\0" as the 
third parameter
*/
			char* szDesc;
			int mlen;
			szDesc=new char[256];
			sprintf(szDesc,"DSN=%s? DESCRIPTION=TOC support source? DBQ=%s? FIL=MicrosoftAccess? DEFAULTDIR=c:?? ","TestDB","db1.mdb");
			mlen = strlen(szDesc);
			  for (int i=0; i<mlen; i++)
			  {
				if (szDesc[i] == '?')
				  szDesc[i] = '\0';
			  }

			if (FALSE == SQLConfigDataSource(NULL,ODBC_ADD_DSN,"Microsoft Access Driver (*.mdb)\0",(LPCSTR)szDesc))
				 MessageBox(hwnd,"Failed","INFORMATION",MB_OK);
			else
				 MessageBox(hwnd,"Sucess","INFORMATION",MB_OK);

			break;
		}
		break;
	case WM_CLOSE:
		if (MessageBox(hwnd,"Are you sure you want to quit","Information",MB_OKCANCEL) == IDOK)
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	
	}
		return DefWindowProc(hwnd,uMsg,wParam,lParam); 
	}