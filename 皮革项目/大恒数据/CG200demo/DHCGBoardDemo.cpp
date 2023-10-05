// DHCGBoardDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DHCGBoardDemo.h"

#include "MainFrm.h"
#include "DHCGBoardDemoDoc.h"
#include "DHCGBoardDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoApp

BEGIN_MESSAGE_MAP(CDHCGBoardDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDHCGBoardDemoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoApp construction

CDHCGBoardDemoApp::CDHCGBoardDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDHCGBoardDemoApp object

CDHCGBoardDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoApp initialization

BOOL CDHCGBoardDemoApp::InitInstance()
{
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
	HANDLE hMapping = ::CreateFileMapping((HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, 16, "cgdlg");
	if (hMapping == NULL)
	{
		TRACE("Failed in call to CreateFileMapping, GetLastError returned %d\n", GetLastError());
		//	UnMap();
		return FALSE;
	}
	else
	{	if(GetLastError()==ERROR_ALREADY_EXISTS)
	{
		//	AfxMessageBox("内存文件以存在",MB_OK,NULL);
		//	CloseHandle(hMapping);
		return false;
	}
	}
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDHCGBoardDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDHCGBoardDemoView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

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
	CHyperLink	m_stcURL;
	//}}AFX_DATA
	void ChangeFont(CStatic *pStatic, int nHeight, int nWidth);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_DHIMAGE, m_stcURL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CDHCGBoardDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoApp message handlers


void CDHCGBoardDemoApp::OnFileOpen() 
{
	CBmpDialog* dlg;
	dlg=new CBmpDialog;
	if(dlg->DoModal()==IDOK)
	{
		OpenDocumentFile(dlg->GetPathName());

	}
	if (CBmpDialog::hpreview)
          DeleteObject(CBmpDialog::hpreview);
		delete dlg;
}
//DEL void CDHCGBoardDemoApp::OnFileSave() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	CDHCGBoardDemoDoc* doc=(CDHCGBoardDemoView
//DEL 	CFileDialog* dlg;
//DEL 	dlg=new CFileDialog;
//DEL 	if(dlg->DoModal()==IDOK)
//DEL 	{
//DEL 		
//DEL 	}
//DEL 	delete dlg;
//DEL }


BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_stcURL.SetWindowText("大恒图象主页");
	m_stcURL.SetAutoSize(FALSE);
	m_stcURL.SetURL("http://www.daheng-image.com");
	m_stcURL.SetColours( RGB(100,100,100), RGB(0,0,0) );
	ChangeFont(&m_stcURL, -12, -8);
	// TODO: Add extra initialization here
	CString str;
	// fill memory info
	MEMORYSTATUS MemStat;
	MemStat.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&MemStat);
	// Total Physical mem
	str.Format("%lu KB", MemStat.dwTotalPhys / 1024L);
	SetDlgItemText(IDC_PHYSICAL_MEM, str);
	// Free Physical mem
	str.Format("%lu KB", MemStat.dwAvailPhys / 1024L);
	SetDlgItemText(IDC_AVAIL_MEM, str);
	// Free Virtual mem
	str.Format("%lu KB", MemStat.dwAvailVirtual / 1024L);
	SetDlgItemText(IDC_AVAIL_VIRTUAL_MEM, str);
	
	// fill CPU info
	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	switch (SysInfo.dwProcessorType)
	{
	case PROCESSOR_INTEL_486:
		str = "Intel 80486";
		break;
	case PROCESSOR_INTEL_PENTIUM:
		str = "Intel Pentium";
		break;
	default:
		str = "";
		break;
	}
	SetDlgItemText(IDC_CPU, str);
	
	// fill OS info
	OSVERSIONINFO OsInfo;
	OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&OsInfo))
	{
		// platform
		switch (OsInfo.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_WINDOWS:
			str = "Windows 95";
			break;
		case VER_PLATFORM_WIN32_NT:
			str = "Windows NT";
			break;
		default:
			str = "";
			break;
		}
		SetDlgItemText(IDC_OS, str);
	}
	
	// fill disk information
	char szWindowsPath[_MAX_PATH];
	GetWindowsDirectory(szWindowsPath, _MAX_PATH);
	ULARGE_INTEGER TotalNumberOfBytes, TotalNumberOfFreeBytes;
	GetDiskFreeSpaceEx((LPSTR)szWindowsPath,
		NULL,
		&TotalNumberOfBytes,
		&TotalNumberOfFreeBytes);
	// total space
	str.Format("%lu KB", TotalNumberOfBytes.QuadPart / 1024L);
	SetDlgItemText(IDC_TOTAL_SPACE, str);
	// free space
	str.Format("%lu KB", TotalNumberOfFreeBytes.QuadPart / 1024L);
	SetDlgItemText(IDC_FREE_SPACE, str);
	return TRUE;  // return TRUE unless you set
}
void CAboutDlg::ChangeFont(CStatic *pStatic, int nHeight, int nWidth)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
{
	HFONT hFont = CreateFont(nHeight /* Height */,  nWidth /*Width*/, 0, 0, FW_NORMAL /*fontweight*/, FALSE /* Italic */, 
														FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, 
														PROOF_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");

	CFont *pFont = CFont::FromHandle(hFont);

	pStatic->SetFont(pFont);
}

