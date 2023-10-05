// homework2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "homework2.h"
#include "homework2Dlg.h"

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
// CHomework2Dlg dialog

CHomework2Dlg::CHomework2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHomework2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHomework2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHomework2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHomework2Dlg)
	DDX_Control(pDX, IDC_LIST_SHOW, m_Show);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHomework2Dlg, CDialog)
	//{{AFX_MSG_MAP(CHomework2Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_MEM, OnButtonMem)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_COMPUTERINFO, OnButtonComputerinfo)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework2Dlg message handlers

BOOL CHomework2Dlg::OnInitDialog()
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
	OnButtonMem();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHomework2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHomework2Dlg::OnPaint() 
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
HCURSOR CHomework2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHomework2Dlg::OnButtonMem() 
{
	SetTimer(1, 500, NULL);
}

void CHomework2Dlg::OnTimer(UINT nIDEvent) 
{
	ShowMemoryStatus();

	CDialog::OnTimer(nIDEvent);
}

void CHomework2Dlg::OnClose() 
{
	KillTimer(1);
	CDialog::OnClose();
}

void CHomework2Dlg::ShowMemoryStatus()
{
	m_Show.DeleteAllItems();

	m_Show.DeleteColumn(2);
	m_Show.DeleteColumn(1);
	m_Show.DeleteColumn(0);

	m_Show.SetBkColor(RGB(0, 100, 100)); 
	m_Show.SetTextBkColor(RGB(0, 100, 100));
	m_Show.SetTextColor(RGB(255, 255, 0));

	CString str;
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = 100;

	lvColumn.iSubItem = 0;
	lvColumn.pszText = "Memory Item";
	m_Show.InsertColumn(0, &lvColumn);

	lvColumn.cx = 100;
	lvColumn.iSubItem = 1;
	lvColumn.pszText = "Status";
	m_Show.InsertColumn(1, &lvColumn);

	LVITEM lvItem;
	// Create the items.
	lvItem.mask = LVIF_TEXT | LVIF_STATE;//| LVIF_IMAGE 
	lvItem.state = 0;      
	lvItem.stateMask = 0;  
	lvItem.iImage = 0;

	int i=0;
	
	MEMORYSTATUS mem_stat;
	GlobalMemoryStatus(&mem_stat);

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Free Memory";
	m_Show.InsertItem(&lvItem);
	str.Format("%ld KB", (int)(mem_stat.dwAvailPhys/1024.0));
	m_Show.SetItemText(i, 1, str);

	i++;

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Used Memory";
	m_Show.InsertItem(&lvItem);
	str.Format("%ld KB",
		(int)((mem_stat.dwTotalPhys - mem_stat.dwAvailPhys)/1024.0));
	m_Show.SetItemText(i, 1, str);


	i++;

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Total Memory";
	m_Show.InsertItem(&lvItem);
	str.Format("%ld KB", (int)(mem_stat.dwTotalPhys/1024.0));
	m_Show.SetItemText(i, 1, str);

	i++;

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Memory Load";
	m_Show.InsertItem(&lvItem);
	str.Format("%ld %%", mem_stat.dwMemoryLoad);
	m_Show.SetItemText(i, 1, str);
}

void CHomework2Dlg::ShowComputerInfo()
{
	m_Show.DeleteAllItems();

	m_Show.DeleteColumn(2);
	m_Show.DeleteColumn(1);
	m_Show.DeleteColumn(0);

	m_Show.SetBkColor(RGB(0, 100, 100)); 
	m_Show.SetTextBkColor(RGB(0, 100, 100));
	m_Show.SetTextColor(RGB(255, 255, 0));

	CString str;
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = 100;

	lvColumn.iSubItem = 0;
	lvColumn.pszText = "System Item";
	m_Show.InsertColumn(0, &lvColumn);

	lvColumn.cx = 100;
	lvColumn.iSubItem = 1;
	lvColumn.pszText = "Status";
	m_Show.InsertColumn(1, &lvColumn);

	LVITEM lvItem;
	// Create the items.
	lvItem.mask = LVIF_TEXT | LVIF_STATE;//| LVIF_IMAGE 
	lvItem.state = 0;      
	lvItem.stateMask = 0;  
	lvItem.iImage = 0;

	int i=0;
	
	DWORD dwSize = 256;
	GetComputerName(str.GetBuffer(256), &dwSize);

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Computer Name";
	m_Show.InsertItem(&lvItem);
	m_Show.SetItemText(i, 1, str);

	i++;

	GetUserName(str.GetBuffer(256), &dwSize);

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "User Name";
	m_Show.InsertItem(&lvItem);
	m_Show.SetItemText(i, 1, str);

	i++;

	// fill OS info
	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "OS Type";
	m_Show.InsertItem(&lvItem);
	OSVERSIONINFO OsInfo;
	OsInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (GetVersionEx(&OsInfo))
	{
		// platform
		switch (OsInfo.dwPlatformId)
		{
		case VER_PLATFORM_WIN32s:
			str = "Windows 3.x";
			break;
		case VER_PLATFORM_WIN32_WINDOWS:
			if(OsInfo.dwMinorVersion == 0)
				str = "Windows 95";
			else
				str = "Windows 98";
			break;
		case VER_PLATFORM_WIN32_NT:
			str = "Windows NT";
			break;
		default:
			str = "";
			break;
		}
		m_Show.SetItemText(i, 1, str);
	}

	i++;

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "OS Version";
	m_Show.InsertItem(&lvItem);
	if (GetVersionEx(&OsInfo))
	{
		str.Format("%d.%d",
			OsInfo.dwMajorVersion, OsInfo.dwMinorVersion);
		m_Show.SetItemText(i, 1, str);
	}

	i++;

	// screen
	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Screen Size";
	m_Show.InsertItem(&lvItem);
	str.Format("%d*%d",
		GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	m_Show.SetItemText(i, 1, str);

	i++;

	SYSTEM_INFO SysInfo;
	GetSystemInfo(&SysInfo);
	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "CPU Type";
	m_Show.InsertItem(&lvItem);
	switch (SysInfo.dwProcessorType)
	{
	case PROCESSOR_INTEL_386:
		str = "Intel 80386";
		break;
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
	m_Show.SetItemText(i, 1, str);

	i++;

	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "CPU Level";
	m_Show.InsertItem(&lvItem);
	switch (SysInfo.wProcessorLevel)
	{
	case 3:
		str = "Intel 80386";
		break;
	case 4:
		str = "Intel 80486";
		break;
	case 5:
		str = "Intel Pentium";
		break;
	case 6:
		str = "Intel Pentium Pro or Pentium II";
		break;
	default:
		str = "";
		break;
	}
	m_Show.SetItemText(i, 1, str);

	// fill disk information
	char szWindowsPath[_MAX_PATH];
	GetWindowsDirectory(szWindowsPath, _MAX_PATH);
	ULARGE_INTEGER TotalNumberOfBytes, TotalNumberOfFreeBytes;
	GetDiskFreeSpaceEx((LPSTR)szWindowsPath,//"C:\\"...
		NULL,
		&TotalNumberOfBytes,
		&TotalNumberOfFreeBytes);

	i++;

	// free space
	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Free Space";
	m_Show.InsertItem(&lvItem);
	str.Format("%lu MB", (long)(TotalNumberOfFreeBytes.QuadPart / (1024L*1024L)));
	m_Show.SetItemText(i, 1, str);

	i++;

	// total space
	lvItem.iItem = i;
	lvItem.iSubItem = 0;
	lvItem.pszText = "Total Space";
	m_Show.InsertItem(&lvItem);
	str.Format("%lu MB", (long)(TotalNumberOfBytes.QuadPart / (1024L*1024L)));
	m_Show.SetItemText(i, 1, str);
}

void CHomework2Dlg::OnButtonComputerinfo() 
{
	KillTimer(1);
	ShowComputerInfo();
}

void CHomework2Dlg::OnButtonExit() 
{
	PostMessage(WM_CLOSE);
}

void CHomework2Dlg::WinHelp(DWORD dwData, UINT nCmd) 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
