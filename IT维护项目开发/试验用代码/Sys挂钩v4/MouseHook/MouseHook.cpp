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
HWND m_hReceiveWindow=NULL;//���ܴ��ڵľ��
HHOOK m_hHook=NULL;//��װ����깴�Ӿ��  
HINSTANCE m_hInstance=NULL;//DLLʵ�����  
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
		m_hInstance=hInstance; //���뱣��DLLʵ����� 
	} 
	else if (dwReason == DLL_PROCESS_DETACH) 
	{ 
		AfxTermExtensionModule(MouseHookDLL);
	}
	return 1; // ok 

}


CMouseHook::CMouseHook() //�๹�캯��  
{  
}
 
CMouseHook::~CMouseHook() //����������  
{  
	StopHook();  
}

LRESULT __declspec(dllexport)__stdcall /*WINAPI*/ CallWndProc(int nCode,WPARAM wparam,LPARAM lparam);


//��װ���Ӳ��趨������ʾ���ھ��  
BOOL CMouseHook::StartHook(HWND hReceiveWindow)
{  
	BOOL bResult=FALSE;  
	m_hHook=SetWindowsHookEx(WH_CALLWNDPROC,CallWndProc,m_hInstance,0);  
	if(m_hHook!=NULL)  
		bResult=TRUE;
	//����Ŀ�괰�ڵľ��  
	m_hReceiveWindow = hReceiveWindow;
	return bResult;  
}

//ж�ع���
BOOL CMouseHook::StopHook()
{
	BOOL bResult=FALSE;
	if(m_hHook)
	{
		bResult= UnhookWindowsHookEx(m_hHook);
		if(bResult)
		{
			m_hReceiveWindow = NULL;//�����
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
//	HWND glhTargetWnd=pCWPStruct->hwnd;//ȡ������Ϣ�Ĵ��ھ��
	if(//ȷ����Ϣ�����ɱ�DLLʵ��������
		wparam == 0 &&
		//ȷ����������Ϣ�ǿ��Լӹ���
		nCode>=0 &&
//		//ȷ���õ��˴�������Ϣ�ṹ
//		CWPStruct &&
		//ȷ����Ϣ�Ĵ��ھ���Ǵ��ڵ�
		pCWPStruct->hwnd &&
		//ѡ�����Ҫ�������Ϣ����
		pCWPStruct->message == WM_CREATE//WM_SHOWWINDOW// &&//WM_CREATE &&
		//ȷ������õĴ�������߼����ڣ��������Ӵ���
//		::GetWindow(pCWPStruct->hwnd, GW_OWNER) == NULL &&
//		GetParent(pCWPStruct->hwnd) == NULL
		)
	{
		//�жϽ��ܴ����Ƿ����
		if(IsWindow(m_hReceiveWindow))
		{
			//��������ڷ���Ϣ�����ݲ���lparam
//			char szCaption[501];
//			::GetWindowText(hWnd, szCaption, 500); //ȡĿ�괰�ڱ���
//			::PostMessage(m_hReceiveWindow, WM_HOOK_CREATEWINDOW, 100, (LPARAM)szCaption);
			::SendMessage(/*::GetParent(*/m_hReceiveWindow/*)*/, WM_HOOK_CREATEWINDOW, 100, (LPARAM)hWnd);//(LPARAM)(PCWPSTRUCT)(&CWPStruct));//(LPARAM)hWnd);
		}
	}
	return CallNextHookEx(m_hHook,nCode,wparam,lparam); //����������Ϣ
}  
