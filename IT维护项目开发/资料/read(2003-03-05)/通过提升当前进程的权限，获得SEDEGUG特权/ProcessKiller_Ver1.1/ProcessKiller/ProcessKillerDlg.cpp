// ProcessKillerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessKiller.h"
#include "ProcessKillerDlg.h"

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
// CProcessKillerDlg dialog

CProcessKillerDlg::CProcessKillerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessKillerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProcessKillerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProcessKillerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProcessKillerDlg)
	DDX_Control(pDX, IDC_LIST_PROCESS, m_listP);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProcessKillerDlg, CDialog)
	//{{AFX_MSG_MAP(CProcessKillerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_COMMAND(ID_POPMENU_KILL, OnPopmenuKill)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PROCESS, OnDblclkListProcess)
	ON_COMMAND(MENU_ABOUT, OnAbout)
	ON_COMMAND(ID_MENU_REFRESH, OnMenuRefresh)
	ON_COMMAND(ID_POPMENU_MODULES, OnPopmenuModules)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProcessKillerDlg message handlers

BOOL CProcessKillerDlg::OnInitDialog()
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

////////////////////////////////////////////////////////////////////////////////////
   //Load Extention API
	if ( ! InitPSAPI() ) {
		TRACE("Load Lib Fail !");
		return 0;
	}
	
   //Update UpdateProcessPrivilege, 
   //If Not Update, You Can't Kill System Process
	if ( UpdateProcessPrivilege( ::GetCurrentProcess(), SE_DEBUG_NAME ) ) {
		TRACE("UpdateProcessPrivilege Succeed!\r\n");
	}
	else {
		TRACE("Fail!");
	}
	
	//Init ListCtrl
   m_listP.InsertColumn( 0, "PID", LVCFMT_CENTER, 30 );
   m_listP.InsertColumn( 1, "FNAME", LVCFMT_LEFT, 80 );
   m_listP.InsertColumn( 2, "FPATH", LVCFMT_LEFT, 250 );

	DWORD dwStyle = m_listP.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_INFOTIP;
	m_listP.SetExtendedStyle( dwStyle );
	
	DWORD dwPTotle = RefreshProcessesList();
	char szWTitle[256];
	sprintf( szWTitle, "Processes Totle: %d", dwPTotle );
	SetWindowText( szWTitle );

////////////////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProcessKillerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProcessKillerDlg::OnPaint() 
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
HCURSOR CProcessKillerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CProcessKillerDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
   CRect rect;
   GetClientRect( &rect );
	if ( IsWindow( m_listP.m_hWnd ) ) {
		m_listP.MoveWindow( 10, 10, rect.right-20, rect.bottom-20 );
	}
}

DWORD CProcessKillerDlg::RefreshProcessesList()
// 更新CListCtrl中的进程列表
// 返回当前进程总数
{
   //Get Processes Infomation List
	ULONG ulSize, ulNeeded;
	EnumProcessesInfo( NULL, 0, &ulNeeded );
	
	LPPROCESSINFO lparrPsInfo = new PROCESSINFO[ulNeeded];
	if ( NULL == lparrPsInfo ) {
		TRACE("Alloc Memory Fail!");
		return 0;
	}
	
	ulSize = ulNeeded;
	EnumProcessesInfo( lparrPsInfo, ulSize, &ulNeeded );
	
   //Show Processes Infomation In CListCtrl 
	if ( m_listP.GetItemCount() > 0 ) {
		m_listP.DeleteAllItems();
	}

   char szPID[64];
   for ( ULONG ulIndex = 0; ulIndex < ulNeeded; ulIndex++ ) {
      
      ltoa( lparrPsInfo[ulIndex].dwPID, szPID, 10 );
      m_listP.InsertItem( ulIndex, szPID );
      m_listP.SetItemText( ulIndex, 1, lparrPsInfo[ulIndex].strName );
      m_listP.SetItemText( ulIndex, 2, lparrPsInfo[ulIndex].strPath );
   }
	
	delete[] lparrPsInfo;

	return ulNeeded;
}

void CProcessKillerDlg::OnPopmenuKill() 
// 杀掉当前选定的进程
{
	char szPID[64];
	POSITION pos = m_listP.GetFirstSelectedItemPosition();
	int nSelected = m_listP.GetNextSelectedItem( pos );

	m_listP.GetItemText( nSelected, 0, szPID, 64 );
	KillProcess( atol( szPID ) );

	//Refresh Window's Title
	DWORD dwPTotle = RefreshProcessesList();
	char szWTitle[256];
	sprintf( szWTitle, "Processes Totle: %d", dwPTotle );
	SetWindowText( szWTitle );
}

void CProcessKillerDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	UnInitPSAPI();
	
	CDialog::OnClose();
}

void CProcessKillerDlg::OnAbout() 
{
	// TODO: Add your command handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void CProcessKillerDlg::OnDblclkListProcess(NMHDR* pNMHDR, LRESULT* pResult) 
// 双击某一进程时根据设置显示进程的线程列表、相关Dll或进程信息
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	TCHAR strPID[64];
	m_listP.GetItemText( pNMListView->iItem, 0, strPID, 64 );
	DWORD dwPID = atol(strPID);

	CShowListDlg* pListDlg = new CShowListDlg;
	pListDlg->Create( IDD_SHOWLIST_DIALOG );
	pListDlg->ShowModulesList( dwPID );

	*pResult = 0;
}

void CProcessKillerDlg::OnMenuRefresh() 
// 刷新进程显示列表区
{
	// TODO: Add your command handler code here
	RefreshProcessesList();
}

void CProcessKillerDlg::OnPopmenuModules() 
//显示进程的模块列表
{
	// TODO: Add your command handler code here
	TCHAR strPID[64];
	POSITION pos = m_listP.GetFirstSelectedItemPosition();
	int nSelected = m_listP.GetNextSelectedItem( pos );
	m_listP.GetItemText( nSelected, 0, strPID, 64 );
	DWORD dwPID = atol(strPID);
	
	CShowListDlg* pListDlg = new CShowListDlg;
	pListDlg->Create( IDD_SHOWLIST_DIALOG );
	pListDlg->ShowModulesList( dwPID );
}
