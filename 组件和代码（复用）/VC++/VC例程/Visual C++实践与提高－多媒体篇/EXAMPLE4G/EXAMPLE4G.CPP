#include "stdlib.h"
#include "windows.h"
#include "scrnsave.h"

#include "resource.h"

//声明三个基本的函数
LRESULT WINAPI ScreenSaveProc(HWND,UINT,WPARAM,LPARAM);
BOOL WINAPI ScreenSaverConfigureDialog(HWND,UINT,WPARAM,LPARAM);
BOOL WINAPI RegisterDialogClasses(HANDLE hInst);
BOOL WINAPI AboutDialog(HWND,UINT,WPARAM,LPARAM);

//定义全局变量
//屏幕保护程序配置数据存放在control.ini文件
char szIniFileName[]="control.ini";
//屏幕保护程序配置数据在control.ini文件位置区名称
char szSection[32];
//屏幕保护程序配置数据项名称
char szEntry[]="Slide Text:";
//屏幕保护程序配置数据，这里是文本内容
char SlideText[256];
int i=0;

//定义三个基本的函数
LRESULT WINAPI ScreenSaverProc(HWND hWnd,UINT message, WPARAM wParam,LPARAM lParam)
{
	static HBITMAP hBmp;//位图句柄
	HDC hDC,hMemDC;//hMemDC是内存设备，缓存位图。
	RECT rc;
	static int xpos=0;
	static UINT timerID;
	switch (message)
    {
	case WM_CREATE:
		//文件位置区名称szSection赋值为资源idsAPPName。
		//其中hMainInstance为SCRNSAVE.LIB定义的屏幕保护程序实例句柄
		LoadString(hMainInstance,idsAppName,szSection,sizeof(szSection));
		strcpy(SlideText,"欢迎使用屏幕保护程序!");
		//读control.ini文件中[Screen Saver.MySaver]区的配置数据到SlideText
		GetPrivateProfileString(szSection,szEntry,SlideText,SlideText,
			sizeof(SlideText),szIniFileName); 

		timerID=SetTimer(hWnd,1,2000,NULL);
		break;

	case WM_ERASEBKGND:
		hDC=GetDC(hWnd);
		GetClientRect(hWnd,&rc);
		
		FillRect(hDC,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
		ReleaseDC(hWnd,hDC);
		
		//显示位图
		hMemDC=CreateCompatibleDC(hDC);
		SelectObject(hMemDC,hBmp);
		SetRect(&rc,0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN)-25);
		BitBlt(hDC,0.5*rc.right-150,0.5*rc.bottom-225,
				300,450,hMemDC,rc.top,rc.left,SRCCOPY);
		
		//清除底行，为文本显示作准备。
		SetRect(&rc,0,GetSystemMetrics(SM_CYSCREEN)-25,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
		FillRect(hDC,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
		ReleaseDC(hWnd,hDC);
		DeleteDC(hMemDC);
		return 1;

	case WM_TIMER:
		hDC=GetDC(hWnd);
		
		//绘制位图
		HDC dcMem;
		GetClientRect(hWnd, &rc); 
		dcMem=CreateCompatibleDC(hDC);
	    if (i<4)
		{
			FillRect(hDC, &rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
			hBmp=LoadBitmap(hMainInstance,MAKEINTRESOURCE(IDB_BITMAP2+i));
			SelectObject(dcMem,hBmp);

			BitBlt(hDC,0.5*rc.right-150,0.5*rc.bottom-225,
					300,450,dcMem,0,0,SRCCOPY);
			i++;			
		}
		else 
		{
			FillRect(hDC, &rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
			hBmp=LoadBitmap(hMainInstance,MAKEINTRESOURCE(IDB_BITMAP2));
			SelectObject(dcMem,hBmp);
			BitBlt(hDC,0.5*rc.right-150,0.5*rc.bottom-225,
				300,450,dcMem,0,0,SRCCOPY);
			i = 1; 
		}

		//清除底行		
		SetRect(&rc,0,GetSystemMetrics(SM_CYSCREEN)-25,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
		FillRect(hDC,&rc,(HBRUSH)GetStockObject(BLACK_BRUSH));
		
		//输出文本
		SetTextColor(hDC,RGB(255*rand(),255*rand(),255*rand()));
		SetBkColor(hDC,RGB(0,0,0));
		TextOut(hDC,xpos,GetSystemMetrics(SM_CYSCREEN)-25,SlideText,strlen(SlideText));
		xpos=(xpos+88)%GetSystemMetrics(SM_CXSCREEN);

		ReleaseDC(hWnd,hDC);
		break;

    case WM_DESTROY:
		DeleteObject(hBmp);
		KillTimer(hWnd,timerID);
		PostQuitMessage (0);
		return 0;
	}
	return DefScreenSaverProc(hWnd,message,wParam,lParam);
}

BOOL WINAPI ScreenSaverConfigureDialog(HWND hWnd,
				UINT message,WPARAM wParam,LPARAM lParam)
{	
	switch (message)
	{
	case WM_INITDIALOG:
		LoadString(hMainInstance,idsAppName,szSection,sizeof(szSection));
		strcpy(SlideText,"欢迎使用屏幕保护程序!");
		GetPrivateProfileString(szSection,szEntry,SlideText,
		SlideText,sizeof(SlideText),szIniFileName); 
		SetDlgItemText(hWnd,IDC_EDIT,SlideText);
		SetFocus(GetDlgItem(hWnd,IDC_EDIT));
		return FALSE;

	case WM_COMMAND:
		switch(wParam)
		{
		case IDOK:
			//取EDIT控件文本数据并写入control.ini文件
			GetDlgItemText(hWnd,IDC_EDIT,SlideText,sizeof(SlideText));
			WritePrivateProfileString(szSection,szEntry,SlideText,szIniFileName);
			EndDialog(hWnd,TRUE);
			return TRUE;
		
		case IDCANCEL:
			EndDialog(hWnd,FALSE);
			return TRUE;
		
//		case ID_ABOUT:
			//调用ABOUT对话框
//			DialogBox(hMainInstance, MAKEINTRESOURCE(DLG_ABOUT),hWnd,(DLGPROC)AboutDialog);
//			return TRUE;
		}
		break;
	}
	return FALSE;
}


BOOL WINAPI RegisterDialogClasses(HANDLE hInst)//(HINSTANCE hInstance)
{
	return TRUE;
}

BOOL WINAPI AboutDialog(HWND hWnd,UINT message,WPARAM wParam,
						LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch(wParam)
		{
	     case IDOK:
			 EndDialog(hWnd,TRUE);
			 return TRUE;
		}
		break;
	}
	return FALSE;
}