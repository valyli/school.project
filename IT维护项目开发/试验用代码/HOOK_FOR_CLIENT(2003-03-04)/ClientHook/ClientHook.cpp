/****************************************
*	文件隶属：			客户端HOOK监控程序
*	文件功用：			实现客户端监控类和DLL外部接口
*	模块类型：			动态库（DLL）
*	模块对外接口类型：	C语言
*	作者：				李佳
*	编写日期：			2003－03－04
****************************************/

// ClientHook.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "ClientHook.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



static AFX_EXTENSION_MODULE ClientHookDLL = { NULL, NULL };


#pragma data_seg("ClientHookDataSeg")
//存放接受此模块发出的消息的窗口句柄
HWND m_hWndReceiveMsg=NULL;
//存放要安装的勾子句柄
HHOOK m_hHook=NULL;
//DLL实例句柄
HINSTANCE m_hInstanceDll=NULL;
#pragma data_seg()


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		if (!AfxInitExtensionModule(ClientHookDLL, hInstance))
			return 0;//fail
		new CDynLinkLibrary(ClientHookDLL);
		//插入保存DLL实例句柄
		m_hInstanceDll=hInstance;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		AfxTermExtensionModule(ClientHookDLL);
	}
	return 1;//ok
}

//处理截获的消息
LRESULT __declspec(dllexport)__stdcall /*WINAPI*/ CallWndProc(int nCode,WPARAM wparam,LPARAM lparam)
{  
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	CWPSTRUCT CWPStruct = *((PCWPSTRUCT)lparam);
//	PCWPSTRUCT pCWPStruct = (PCWPSTRUCT)lparam;
//	HWND hWnd = pCWPStruct->hwnd;
	//确定传来的是创建窗口的消息
	if(nCode==HSHELL_WINDOWCREATED)
	{
		//判断接受窗口是否存在
		if(IsWindow(m_hWndReceiveMsg))
		{
			//给输出窗口发消息
			::SendMessage(m_hWndReceiveMsg, WM_HOOK_CREATEWINDOW, wparam, lparam);
		}
	}
	return CallNextHookEx(m_hHook,nCode,wparam,lparam); //继续传递消息
}

//类构造函数
CClientHook::CClientHook()
{  
}
 
//类析构函数
CClientHook::~CClientHook()
{
	StopClientHook();
}

//安装钩子并设定接收DLL发出的消息的窗口句柄
BOOL CClientHook::StartClientHook(HWND hWndReceiveMsg)
{  
	BOOL bResult=FALSE;
	m_hHook=SetWindowsHookEx(WH_SHELL/*WH_CALLWNDPROC*/,CallWndProc,m_hInstanceDll,0);
	if(m_hHook!=NULL)
		bResult=TRUE;
	//设置目标窗口的句柄
	m_hWndReceiveMsg = hWndReceiveMsg;
	return bResult;
}

//卸载钩子
BOOL CClientHook::StopClientHook()
{
	BOOL bResult=FALSE;
	if(m_hHook)
	{
		bResult= UnhookWindowsHookEx(m_hHook);
		if(bResult)
		{
			m_hWndReceiveMsg = NULL;//清变量
			m_hHook=NULL;
		}
	}
	return bResult;
}

