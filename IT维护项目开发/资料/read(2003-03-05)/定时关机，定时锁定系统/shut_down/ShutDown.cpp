// ShutDown.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ShutDown.h"
#include "ShutDownDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShutDownApp

BEGIN_MESSAGE_MAP(CShutDownApp, CWinApp)
	//{{AFX_MSG_MAP(CShutDownApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShutDownApp construction

CShutDownApp::CShutDownApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CShutDownApp object

CShutDownApp theApp;

BOOL CShutDownApp::AlreadyRunning()
{
	BOOL bFound = FALSE;

	// Try to create a mutex with the app's name
	HANDLE hMutexOneInstance = ::CreateMutex(NULL,TRUE,_T(AfxGetAppName()));

	// Already there...means that we are already running an instance
	if(::GetLastError() == ERROR_ALREADY_EXISTS)
		bFound = TRUE;

	// Release the mutex
	if(hMutexOneInstance)
		::ReleaseMutex(hMutexOneInstance);

	return(bFound);
}
/////////////////////////////////////////////////////////////////////////////
// CShutDownApp initialization

BOOL CShutDownApp::InitInstance()
{
	if(AlreadyRunning())
	{
		// Yep...get out now
		AfxMessageBox(IDS_ALREADY_RUNNING,MB_ICONWARNING);
		return(FALSE);
	}
	
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	SetRegistryKey(_T("Hitech software"));
	::CoInitialize(NULL);

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CShutDownDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CShutDownApp::ExitInstance() 
{
	::CoUninitialize( );

	return CWinApp::ExitInstance();
}

CString CShutDownApp::KeyChanged(CString pwd)
{
CString ss;
int len,i;
char cc;

	ss = pwd;
	cc = (char) 0x88;
	len = pwd.GetLength();
	for(i=0; i<len; i++)
	{
		 cc = pwd[i];
		 cc += (char) 0x88;
		 ss.SetAt(i,cc);
	}

	return ss;
}