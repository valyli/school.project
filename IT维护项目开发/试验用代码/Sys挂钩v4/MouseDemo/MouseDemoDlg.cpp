// MouseDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseDemo.h"
#include "MouseDemoDlg.h"
#include "stdio.h"
#include "process.h"
#include "Winuser.h"
#include "Windows.h"

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
// CMouseDemoDlg dialog

CMouseDemoDlg::CMouseDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseDemoDlg::IDD, pParent)
{
	nItem = 0;
	//{{AFX_DATA_INIT(CMouseDemoDlg)
	m_RuntimeClassName = _T("");
	m_Filepath = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMouseDemoDlg)
	DDX_Control(pDX, IDC_LIST_JOB, m_Job_List);
	DDX_Control(pDX, IDC_LIST_TEST, m_Test_List);
	DDX_Text(pDX, IDC_EDIT_CLASSNAME, m_RuntimeClassName);
	DDX_Text(pDX, IDC_EDIT_FILEPATH, m_Filepath);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMouseDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_HOOK_CREATEWINDOW, OnHookCreatewindow)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseDemoDlg message handlers

BOOL CMouseDemoDlg::OnInitDialog()
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

	//加入ListBox用于显示测试结果
	LVCOLUMN lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_CENTER;
	lvColumn.cx = 300;
	lvColumn.iSubItem = 0;
	lvColumn.pszText = "测试";
	m_Test_List.InsertColumn(0, &lvColumn);

	// TODO: Add extra initialization here
	FILE *f = fopen( "c:\\tryresult.txt", "w" );
	fclose(f);
	//取得编辑框的类指针
	m_hook.StartHook(this->m_hWnd);
	//取得编辑框的窗口句柄并安装钩子 

//	char buff[100];
//	MessageBox(itoa(HC_ACTION, buff, 10));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMouseDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMouseDemoDlg::OnPaint() 
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
HCURSOR CMouseDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMouseDemoDlg::OnHookCreatewindow(WPARAM wParam, LPARAM lParam)
{
//	::MessageBox(this->m_hWnd, "", "", MB_OK);
	char szCaption[501];
	HWND hWnd = (HWND)lParam;
	HWND glhTargetWnd=hWnd;//取目标窗口句柄  
	HWND ParentWnd=glhTargetWnd;  
	if(::IsWindow(hWnd))
	{
//		while (ParentWnd !=NULL)  
//		{  
//			glhTargetWnd=ParentWnd;  
//			ParentWnd=::GetParent(hWnd); //取应用程序主窗口句柄  
//		}
		CWnd* pWnd=AfxGetMainWnd()->GetWindow(GW_HWNDFIRST);
		BOOL tt= FALSE;
	while (pWnd)
	{
		// 是否窗口可见,有标题,没有被其它窗口所有?
//		if (pWnd->GetSafeHwnd() == hWnd)//pWnd->IsWindowVisible() && pWnd->GetWindowTextLength() &&! pWnd->GetOwner())
			tt = TRUE;
		//取得下一个窗口
		pWnd=pWnd->GetWindow(GW_HWNDNEXT);
	}
	if(tt == TRUE)
	{
		::GetWindowText(hWnd, szCaption, 100); //取目标窗口标题
		DWORD dwProcessId;
		char buff[100];
		::GetWindowThreadProcessId(hWnd, &dwProcessId);
		strcat(szCaption, itoa(dwProcessId, buff, 10));
//			GetWindowModuleFileName(glhTargetWnd, szCaption, 100);//取目标窗口路径
	this->m_Filepath = szCaption;//szCaption;

//	LPTSTR exeFullPath[MAX_PATH];
//	::GetWindowModuleFileName(hWnd, exeFullPath, MAX_PATH);//取得目标窗口程序的路径

	LVITEM lvItem;
	// Create the items.
	lvItem.mask = LVIF_TEXT | LVIF_STATE;//| LVIF_IMAGE 
	lvItem.state = 0;      
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.iItem = nItem++;
	lvItem.iSubItem = 0;
	lvItem.pszText = szCaption;
	m_Test_List.InsertItem(&lvItem);

	
	FILE *f = fopen( "c:\\tryresult.txt", "a" );
	fprintf(f, "_____________________\n");
	fprintf( f, "%s\n", szCaption);
//	fprintf( f, "%s\n", exeFullPath);
	fclose( f );
//	this->m_Filepath = exeFullPath;

	//加入作业检测////////////////////////////////////////////////////////
	CString strCaption;        //窗口标题
	m_Job_List.DeleteAllItems();        //清空下拉式列表框

	//取得窗口列表中第一个窗口
	ASSERT_VALID(AfxGetMainWnd());
	CWnd* pWnd=AfxGetMainWnd()->GetWindow(GW_HWNDFIRST);
	
	//遍历窗口
	while (pWnd)
	{
		// 是否窗口可见,有标题,没有被其它窗口所有?
		if (pWnd->IsWindowVisible() && pWnd->GetWindowTextLength() &&! pWnd->GetOwner())
		{
            //将标题增加到列表框中
            pWnd->GetWindowText(strCaption);
			strCaption += itoa(dwProcessId, buff, 10);
            m_Job_List.InsertItem(nItem, strCaption);
		}
		//取得下一个窗口
		pWnd=pWnd->GetWindow(GW_HWNDNEXT);
	}
	
	
	
	UpdateData(FALSE);
		}
	}
}

void CMouseDemoDlg::OnButton1() 
{
	::PostMessage(this->m_hWnd, WM_HOOK_CREATEWINDOW, 0, 0);
}
