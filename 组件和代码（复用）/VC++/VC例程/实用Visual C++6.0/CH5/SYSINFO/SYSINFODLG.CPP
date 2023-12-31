// SysinfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sysinfo.h"
#include "SysinfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg dialog

CSysinfoDlg::CSysinfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSysinfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSysinfoDlg)
	m_strComputerName = _T("");
	m_strTotalMemory = _T("");
	m_strFreeMemory = _T("");
	m_strMemoryLoad = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSysinfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSysinfoDlg)
	DDX_Text(pDX, IDC_COMPUTER_NAME, m_strComputerName);
	DDX_Text(pDX, IDC_TOTAL_MEMORY, m_strTotalMemory);
	DDX_Text(pDX, IDC_FREE_MEMORY, m_strFreeMemory);
	DDX_Text(pDX, IDC_MEMORY_LOAD, m_strMemoryLoad);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSysinfoDlg, CDialog)
	//{{AFX_MSG_MAP(CSysinfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_REFRESH, OnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg message handlers

BOOL CSysinfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSysinfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSysinfoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSysinfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSysinfoDlg::OnRefresh() 
{
	// TODO: Add your control notification handler code here
	// ** Variables used for getting the computer name
	TCHAR szBuffer[256];
	DWORD dwSize=256;

	// ** Retrieve the computer name from Window
	GetComputerName(szBuffer,&dwSize);

	// ** Transfer the computer name to the appropriate
	// ** member variable
	m_strComputerName = szBuffer;

	// ** Allocate structure to recieve memory data
	MEMORYSTATUS mem_stat;

	// ** ** Retrieve the current memory status
	GlobalMemoryStatus(&mem_stat);

	// ** Transfer the memory details to the appropriate
	// ** memer variable
	m_strTotalMemory.Format("%ld KB",mem_stat.dwTotalPhys / 1024);
	m_strFreeMemory.Format("%ld KB",mem_stat.dwAvailPhys / 1024);
	m_strMemoryLoad.Format("%d %%",mem_stat.dwMemoryLoad);

	// ** Update the contents of controls to display
	UpdateData(FALSE);
}
