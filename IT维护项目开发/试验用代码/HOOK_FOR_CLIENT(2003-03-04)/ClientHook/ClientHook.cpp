/****************************************
*	�ļ�������			�ͻ���HOOK��س���
*	�ļ����ã�			ʵ�ֿͻ��˼�����DLL�ⲿ�ӿ�
*	ģ�����ͣ�			��̬�⣨DLL��
*	ģ�����ӿ����ͣ�	C����
*	���ߣ�				���
*	��д���ڣ�			2003��03��04
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
//��Ž��ܴ�ģ�鷢������Ϣ�Ĵ��ھ��
HWND m_hWndReceiveMsg=NULL;
//���Ҫ��װ�Ĺ��Ӿ��
HHOOK m_hHook=NULL;
//DLLʵ�����
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
		//���뱣��DLLʵ�����
		m_hInstanceDll=hInstance;
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		AfxTermExtensionModule(ClientHookDLL);
	}
	return 1;//ok
}

//����ػ����Ϣ
LRESULT __declspec(dllexport)__stdcall /*WINAPI*/ CallWndProc(int nCode,WPARAM wparam,LPARAM lparam)
{  
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
//	CWPSTRUCT CWPStruct = *((PCWPSTRUCT)lparam);
//	PCWPSTRUCT pCWPStruct = (PCWPSTRUCT)lparam;
//	HWND hWnd = pCWPStruct->hwnd;
	//ȷ���������Ǵ������ڵ���Ϣ
	if(nCode==HSHELL_WINDOWCREATED)
	{
		//�жϽ��ܴ����Ƿ����
		if(IsWindow(m_hWndReceiveMsg))
		{
			//��������ڷ���Ϣ
			::SendMessage(m_hWndReceiveMsg, WM_HOOK_CREATEWINDOW, wparam, lparam);
		}
	}
	return CallNextHookEx(m_hHook,nCode,wparam,lparam); //����������Ϣ
}

//�๹�캯��
CClientHook::CClientHook()
{  
}
 
//����������
CClientHook::~CClientHook()
{
	StopClientHook();
}

//��װ���Ӳ��趨����DLL��������Ϣ�Ĵ��ھ��
BOOL CClientHook::StartClientHook(HWND hWndReceiveMsg)
{  
	BOOL bResult=FALSE;
	m_hHook=SetWindowsHookEx(WH_SHELL/*WH_CALLWNDPROC*/,CallWndProc,m_hInstanceDll,0);
	if(m_hHook!=NULL)
		bResult=TRUE;
	//����Ŀ�괰�ڵľ��
	m_hWndReceiveMsg = hWndReceiveMsg;
	return bResult;
}

//ж�ع���
BOOL CClientHook::StopClientHook()
{
	BOOL bResult=FALSE;
	if(m_hHook)
	{
		bResult= UnhookWindowsHookEx(m_hHook);
		if(bResult)
		{
			m_hWndReceiveMsg = NULL;//�����
			m_hHook=NULL;
		}
	}
	return bResult;
}

