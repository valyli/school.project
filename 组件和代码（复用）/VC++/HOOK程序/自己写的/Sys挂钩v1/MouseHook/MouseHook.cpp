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
HWND glhPrevTarWnd=NULL;//�ϴ������ָ�Ĵ��ھ��  
HWND glhDisplayWnd1=NULL;//��ʾĿ�괰�ڱ���༭��ľ��
HWND glhDisplayWnd2=NULL;//��ʾ���ڳ����·��
HHOOK glhHook=NULL;//��װ����깴�Ӿ��  
HINSTANCE glhInstance=NULL;//DLLʵ�����  
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
		glhInstance=hInstance; //���뱣��DLLʵ����� 
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

LRESULT /*__declspec(dllexport)__stdcall*/WINAPI CallWndProc(int nCode,WPARAM wparam,LPARAM lparam);


BOOL CMouseHook::StartHook(HWND hWnd1, HWND hWnd2)
//��װ���Ӳ��趨������ʾ���ھ��  
{  
	BOOL bResult=FALSE;  
	glhHook=SetWindowsHookEx(WH_CALLWNDPROC,CallWndProc,glhInstance,0);  
	if(glhHook!=NULL)  
		bResult=TRUE;  
	glhDisplayWnd1=hWnd1;
	glhDisplayWnd2=hWnd2;
	//������ʾĿ�괰�ڱ���༭��ľ��  
	return bResult;  
}

BOOL CMouseHook::StopHook()//ж�ع���
{
	BOOL bResult=FALSE;
	if(glhHook)
	{
		bResult= UnhookWindowsHookEx(glhHook);
		if(bResult)
		{
			glhPrevTarWnd=NULL;
			glhDisplayWnd1=NULL;//�����
			glhDisplayWnd2=NULL;//�����
			glhHook=NULL;
		}
	}
	return bResult;
}  



LRESULT /*__declspec(dllexport)__stdcall*/WINAPI CallWndProc(int nCode,WPARAM wparam,LPARAM lparam)  
{  
//	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	PCWPSTRUCT pCWPSTRUCT=(PCWPSTRUCT)lparam;
//	::MessageBox(NULL, "", "", MB_OK);
//	if (nCode == 2)
	if(nCode>=0 && pCWPSTRUCT && pCWPSTRUCT->hwnd)
	{
//		::MessageBox(NULL,"","",MB_OK);
		HWND glhTargetWnd=pCWPSTRUCT->hwnd;//ȡĿ�괰�ھ��  
/*		HWND ParentWnd=glhTargetWnd;  
		while (ParentWnd !=NULL)  
		{  
			glhTargetWnd=ParentWnd;
			ParentWnd=GetParent(glhTargetWnd);//ȡӦ�ó��������ھ��  
		}  
//		if(glhTargetWnd!=glhPrevTarWnd)  
*/		if(pCWPSTRUCT->message==WM_SHOWWINDOW)
		{  
			char szCaption[100];  
			GetWindowText(glhTargetWnd,szCaption,100); //ȡĿ�괰�ڱ���
			TCHAR exeFullPath[MAX_PATH];
			GetModuleFileName(NULL, exeFullPath, MAX_PATH);//ȡ��Ŀ�괰�ڳ����·��

			if(IsWindow(glhDisplayWnd1) && IsWindow(glhDisplayWnd2))  
			{
				SendMessage(glhDisplayWnd1,WM_SETTEXT,0,(LPARAM)(LPCTSTR)szCaption);
				SendMessage(glhDisplayWnd2,WM_SETTEXT,0,(LPARAM)(LPCTSTR)exeFullPath);
			}
			glhPrevTarWnd=glhTargetWnd;//����Ŀ�괰��  
		}  
	}  
	return CallNextHookEx(glhHook,nCode,wparam,lparam); //����������Ϣ  
}  
