// MouseHook.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include"MouseHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE MouseHookDLL = { NULL, NULL };


#pragma data_seg("mydata")  
HWND m_hReceiveWindow=NULL;//接受窗口的句柄
HHOOK m_hHook=NULL;//安装的鼠标勾子句柄  
HINSTANCE m_hInstance=NULL;//DLL实例句柄  
#pragma data_seg()  



extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
/*	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("MOUSEHOOK.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(MouseHookDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(MouseHookDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("MOUSEHOOK.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(MouseHookDLL);
	}
	return 1;   // ok
*/
	UNREFERENCED_PARAMETER(lpReserved); 
	if (dwReason == DLL_PROCESS_ATTACH) 
	{ 
		if (!AfxInitExtensionModule(MouseHookDLL, hInstance)) 
			return 0; 
		new CDynLinkLibrary(MouseHookDLL); 
		m_hInstance=hInstance; //插入保存DLL实例句柄 
	} 
	else if (dwReason == DLL_PROCESS_DETACH) 
	{ 
		AfxTermExtensionModule(MouseHookDLL);
	}
	return 1; // ok 

}


CMouseHook::CMouseHook() //类构造函数  
{  
}
 
CMouseHook::~CMouseHook() //类析构函数  
{  
	StopHook();  
}

LRESULT __declspec(dllexport)__stdcall /*WINAPI*/ CallWndProc(int nCode,WPARAM wparam,LPARAM lparam);


//安装钩子并设定接收显示窗口句柄  
BOOL CMouseHook::StartHook(HWND hReceiveWindow)
{  
	BOOL bResult=FALSE;  
	m_hHook=SetWindowsHookEx(WH_CALLWNDPROC,CallWndProc,m_hInstance,0);  
	if(m_hHook!=NULL)  
		bResult=TRUE;
	//设置目标窗口的句柄  
	m_hReceiveWindow = hReceiveWindow;
	return bResult;  
}

//卸载钩子
BOOL CMouseHook::StopHook()
{
	BOOL bResult=FALSE;
	if(m_hHook)
	{
		bResult= UnhookWindowsHookEx(m_hHook);
		if(bResult)
		{
			m_hReceiveWindow = NULL;//清变量
			m_hHook=NULL;
		}
	}
	return bResult;
}  

LRESULT __declspec(dllexport)__stdcall /*WINAPI*/ CallWndProc(int nCode,WPARAM wparam,LPARAM lparam)  
{  
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	CWPSTRUCT CWPStruct = *((PCWPSTRUCT)lparam);
	PCWPSTRUCT pCWPStruct = (PCWPSTRUCT)lparam;
	HWND hWnd = pCWPStruct->hwnd;
//	char buff[100];
//	::MessageBox(m_hReceiveWindow, itoa((int)(CWPStruct.hwnd),buff,10),"",MB_OK);
//	HWND glhTargetWnd=pCWPStruct->hwnd;//取产生消息的窗口句柄
	if(//确定消息不是由本DLL实例发出的
		wparam == 0 &&
		//确定传来的消息是可以加工的
		nCode>=0 &&
//		//确定得到了传来的消息结构
//		CWPStruct &&
		//确定消息的窗口句柄是存在的
		pCWPStruct->hwnd &&
		//选择程序将要处理的消息种类
		pCWPStruct->message == WM_CREATE//WM_SHOWWINDOW// &&//WM_CREATE &&
		//确定所获得的窗口是最高级窗口，而不是子窗口
//		::GetWindow(pCWPStruct->hwnd, GW_OWNER) == NULL &&
//		GetParent(pCWPStruct->hwnd) == NULL
		)
	{
		//判断接受窗口是否存在
		if(IsWindow(m_hReceiveWindow))
		{
			//给输出窗口发消息，传递参数lparam
//			char szCaption[501];
//			::GetWindowText(hWnd, szCaption, 500); //取目标窗口标题
//			::PostMessage(m_hReceiveWindow, WM_HOOK_CREATEWINDOW, 100, (LPARAM)szCaption);
			::SendMessage(/*::GetParent(*/m_hReceiveWindow/*)*/, WM_HOOK_CREATEWINDOW, 100, (LPARAM)hWnd);//(LPARAM)(PCWPSTRUCT)(&CWPStruct));//(LPARAM)hWnd);
		}
	}
	return CallNextHookEx(m_hHook,nCode,wparam,lparam); //继续传递消息
}  
