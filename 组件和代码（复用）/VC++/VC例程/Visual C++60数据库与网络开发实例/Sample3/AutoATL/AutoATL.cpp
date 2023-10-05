// AutoATL.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AutoATL.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "AutoATLDoc.h"
#include "AutoATLView.h"
#include <initguid.h>
#include "AutoATL_i.c"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoATLApp

BEGIN_MESSAGE_MAP(CAutoATLApp, CWinApp)
	//{{AFX_MSG_MAP(CAutoATLApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoATLApp construction

CAutoATLApp::CAutoATLApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// CAutoATLApp initialization

BOOL CAutoATLApp::InitInstance()
{
	if (false == _Module.m_bATLInited)
		return FALSE;

	_Module.UpdateRegistryFromResource(IDR_AUTOATL, TRUE);
	_Module.RegisterServer(TRUE);

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_AUTOATTYPE,
		RUNTIME_CLASS(CAutoATLDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CAutoATLView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		return TRUE;
	}



	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CAutoATLApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CAutoATLApp message handlers


	
CAutoATLModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Application, CAutoATLApp)
OBJECT_ENTRY(CLSID_Document, CAutoATLDoc)
END_OBJECT_MAP()

CAutoATLModule::CAutoATLModule()
{
	m_bATLInited = TRUE;

	HRESULT hRes = CoInitialize(NULL);
	if (FAILED(hRes))
		exit(1);

	_Module.Init(ObjectMap, GetModuleHandle(NULL));
	_Module.dwThreadID = GetCurrentThreadId();

	LPTSTR lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
	TCHAR szTokens[] = _T("-/");

	BOOL bRun = TRUE;
	LPCTSTR lpszToken = _Module.FindOneOf(lpCmdLine, szTokens);
	while (lpszToken != NULL)
	{
		if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_AUTOATL, FALSE);
			_Module.UnregisterServer(TRUE); //TRUE means typelib is unreg'd
			bRun = FALSE;
			break;
		}
		if (lstrcmpi(lpszToken, _T("RegServer"))==0)
		{
			_Module.UpdateRegistryFromResource(IDR_AUTOATL, TRUE);
			_Module.RegisterServer(TRUE);
			bRun = FALSE;
			break;
		}
		lpszToken = _Module.FindOneOf(lpszToken, szTokens);
	}

	if (!bRun)
	{
		_Module.Term();
		CoUninitialize();
		exit(0);
	}

	hRes = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE);
	if (FAILED(hRes))
	{
		CoUninitialize();
		exit(1);
	}	
}

CAutoATLModule::~CAutoATLModule()
{
	if (m_bATLInited)
	{
		_Module.RevokeClassObjects();
		_Module.Term();
		CoUninitialize();
	}
}

LONG CAutoATLModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CAutoATLModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
LPCTSTR CAutoATLModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}



STDMETHODIMP CAutoATLApp::Beep()
{
	{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CWinApp* pApp = AfxGetApp();
	}

	{
	AFX_MANAGE_STATE(m_pModuleState);

	CWinApp* pApp = AfxGetApp();
	}

	::Beep(1000,1000);

	return S_OK;
}

STDMETHODIMP CAutoATLApp::get_ActiveDocument(IDocument **pVal)
{
	METHOD_PROLOGUE_ATL

	CMDIChildWnd* pChild = ((CMDIFrameWnd*)m_pMainWnd)->MDIGetActive();
	if (!pChild) 
		return E_FAIL;
	
	ASSERT_KINDOF(CMDIChildWnd, pChild);
	CComObject<CAutoATLDoc>* pDoc = dynamic_cast<CComObject<CAutoATLDoc>*>(pChild->GetActiveDocument());
	return pDoc->QueryInterface(IID_IDocument, reinterpret_cast<void**>(pVal));
}
