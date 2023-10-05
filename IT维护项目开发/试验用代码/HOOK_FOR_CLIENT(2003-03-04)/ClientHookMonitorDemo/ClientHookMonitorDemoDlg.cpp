// ClientHookMonitorDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClientHookMonitorDemo.h"
#include "ClientHookMonitorDemoDlg.h"

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
// CClientHookMonitorDemoDlg dialog

CClientHookMonitorDemoDlg::CClientHookMonitorDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientHookMonitorDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientHookMonitorDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientHookMonitorDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientHookMonitorDemoDlg)
	DDX_Control(pDX, IDC_LIST_NEW_JOB, m_NewJobList);
	DDX_Control(pDX, IDC_LIST_JOB, m_JobList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientHookMonitorDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClientHookMonitorDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_HOOK_CREATEWINDOW, OnHookCreatewindow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientHookMonitorDemoDlg message handlers

BOOL CClientHookMonitorDemoDlg::OnInitDialog()
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
	
	//初始化Job ListBox
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_CENTER;
	//加入“作业名”列
	lvColumn.cx = 400;
	lvColumn.iSubItem = 0;
	lvColumn.pszText = "作业名";
	m_JobList.InsertColumn(0, &lvColumn);
	//加入“进程号”列
	lvColumn.cx = 100;
	lvColumn.iSubItem = 1;
	lvColumn.pszText = "进程号";
	m_JobList.InsertColumn(1, &lvColumn);

	//初始化New Job ListBox
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_CENTER;
	//加入“序号”列
	lvColumn.cx = 100;
	lvColumn.iSubItem = 0;
	lvColumn.pszText = "序号";
	m_NewJobList.InsertColumn(0, &lvColumn);
	//加入“作业名”列
	lvColumn.cx = 400;
	lvColumn.iSubItem = 1;
	lvColumn.pszText = "作业名";
	m_NewJobList.InsertColumn(1, &lvColumn);


	//启动HOOK程序，并将当前对话框窗口句柄传给HOOK程序
	m_ClientHook.StartClientHook(this->m_hWnd);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientHookMonitorDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientHookMonitorDemoDlg::OnPaint() 
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
HCURSOR CClientHookMonitorDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//响应WM_HOOK_CREATEWINDOW消息
void CClientHookMonitorDemoDlg::OnHookCreatewindow(WPARAM wParam, LPARAM lParam)
{
	//生成Job视图
	ViewJob();
	//生成最新创建的Job记录视图
	CreatJobView(wParam, lParam);
	UpdateData(FALSE);
}

//在CListBox控件中生成Job视图，此处控件为m_JobList
BOOL CClientHookMonitorDemoDlg::ViewJob()
{
	//存储窗口标题
	CString strCaption;
	//存储进程号ID值
	DWORD dwProcessId;
	//临时缓存
	char buff[10];




	//为列表框初始化项目结构体
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_STATE;//| LVIF_IMAGE 
	lvItem.state = 0;      
	lvItem.stateMask = 0;
	lvItem.iImage = 0;

	//清空下拉式列表框
	m_JobList.DeleteAllItems();
	lvItem.iItem = 0;
	//遍历作业窗口
	//取得窗口列表中第一个窗口
	ASSERT_VALID(AfxGetMainWnd());
	CWnd* pWnd=AfxGetMainWnd()->GetWindow(GW_HWNDFIRST);
	while (pWnd)
	{
		// 是否窗口可见,有标题,没有被其它窗口所有?
		if (pWnd->IsWindowVisible() && pWnd->GetWindowTextLength() &&! pWnd->GetOwner())
		{
			//将作业标题增加到列表框中
			lvItem.iSubItem = 0;
			pWnd->GetWindowText(strCaption);
			lvItem.pszText = strCaption.GetBuffer(strCaption.GetLength());
			m_JobList.InsertItem(&lvItem);

			//添加进程号
			::GetWindowThreadProcessId(pWnd->GetSafeHwnd(), &dwProcessId);
			m_JobList.SetItemText(lvItem.iItem, 1, itoa(dwProcessId, buff, 10));

			//列下移
			lvItem.iItem++;
		}
		//取得下一个窗口
		pWnd=pWnd->GetWindow(GW_HWNDNEXT);
	}
	return TRUE;
}

//在CListBox控件中生成最新创建的Job记录视图，此处控件为m_NewJobList
BOOL CClientHookMonitorDemoDlg::CreatJobView(WPARAM wParam, LPARAM lParam)
{
	//存储序号
	static long serial_number = 1;
	//存储从消息中获取被截获的窗口句柄
	HWND hWnd = (HWND)wParam;
	//存储窗口标题
	char szCaption[501];
	//临时缓存
	char buff[10];
	//列表框加入项的结构体
	LVITEM lvItem;

/*	BOOL bflag = FALSE;
	//取得窗口列表中第一个窗口
	ASSERT_VALID(AfxGetMainWnd());
	CWnd* pWnd=AfxGetMainWnd()->GetWindow(GW_HWNDFIRST);
	
	//遍历窗口
	while(pWnd)
	{
		//是否窗口可见,有标题,没有被其它窗口所有?
		if (pWnd->IsWindowVisible() && pWnd->GetWindowTextLength() &&! pWnd->GetOwner())
		{
			if(pWnd->GetSafeHwnd() == hWnd)
			{
				bflag = TRUE;
				break;
			}
		}
		//取得下一个窗口
		pWnd=pWnd->GetWindow(GW_HWNDNEXT);
	}
*/
	//为列表框初始化项目结构体
	lvItem.mask = LVIF_TEXT | LVIF_STATE;//| LVIF_IMAGE 
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;

	//加入新起动的Job的标题
	//加入序号
	lvItem.pszText = itoa(serial_number++, buff, 10);
	m_NewJobList.InsertItem(&lvItem);

	//取目标窗口标题
	::GetWindowText(hWnd, szCaption, 500);
	m_NewJobList.SetItemText(0, 1, szCaption);
	return TRUE;
}
