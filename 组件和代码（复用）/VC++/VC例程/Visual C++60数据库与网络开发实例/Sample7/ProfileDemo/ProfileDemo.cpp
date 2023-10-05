// ProfileDemo.cpp : Defines the class behaviors for the application.
// 
// Written by Christopher W. Backen - VIZ Group, 1998
//
// ProfileDemo - Simple Dialog Wizaard to Add a service to the default
// Microsoft Exchange Profile, then configure it and delete
// a Microsoft Mail Account and then set all messages to goto the 
// Exchange Mailbox
//
// About MAPI Class
// Simple MAPI Class to help someone Add/Delete messaging profiles,
// configure messaging services, add/delete messaging services,
// configure messaging services, and set default messaging stores.
//
// For Service Names, please consult the MAPISVC.INF file located
// in \winnt\system32
// 
// Tested on Windows NT 4.0 and Visual C++ 6.0

#include "stdafx.h"
#include "ProfileDemo.h"
#include "ProfileDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProfileDemoApp

BEGIN_MESSAGE_MAP(CProfileDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CProfileDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProfileDemoApp construction

CProfileDemoApp::CProfileDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CProfileDemoApp object

CProfileDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CProfileDemoApp initialization

BOOL CProfileDemoApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CProfileDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
