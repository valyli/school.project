// Example5EDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Example5E.h"
#include "Example5EDlg.h"

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
// CExample5EDlg dialog

CExample5EDlg::CExample5EDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExample5EDlg::IDD, pParent),
	m_dwStyle(WS_CHILD|WS_VISIBLE|ACS_CENTER)
{
	//{{AFX_DATA_INIT(CExample5EDlg)
	m_bAutoPlay = FALSE;
	m_bCenter = TRUE;
	m_bTransparent = FALSE;
	m_cstrFileName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample5EDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExample5EDlg)
	DDX_Check(pDX, IDC_AUTOPLAY, m_bAutoPlay);
	DDX_Check(pDX, IDC_CENTER, m_bCenter);
	DDX_Check(pDX, IDC_TRANSPARENT, m_bTransparent);
	DDX_Text(pDX, IDC_EDIT1, m_cstrFileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExample5EDlg, CDialog)
	//{{AFX_MSG_MAP(CExample5EDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnFileChange)
	ON_BN_CLICKED(IDC_CENTER, OnCenter)
	ON_BN_CLICKED(IDC_AUTOPLAY, OnAutoplay)
	ON_BN_CLICKED(IDC_TRANSPARENT, OnTransparent)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5EDlg message handlers

BOOL CExample5EDlg::OnInitDialog()
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
//	m_animateCtrl.Open(IDR_AVI1);
//	m_animateCtrl.Play(0,-1,-1);
	CWnd* pFrame = GetDlgItem(IDC_ANIMFRAME);
	pFrame->GetClientRect(&m_rectAnimateCtrl);
	m_animateCtrl.Create(m_dwStyle, m_rectAnimateCtrl, pFrame,IDC_ANIMFRAME );	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExample5EDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExample5EDlg::OnPaint() 
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
HCURSOR CExample5EDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExample5EDlg::ApplyChanges()
{
	//停止并关闭当前的动画
	m_animateCtrl.Stop();
	m_animateCtrl.Close();

	//设置新的风格
	::SetWindowLong(m_animateCtrl.GetSafeHwnd(), GWL_STYLE, m_dwStyle);
	
	//更改动画控件的位置、大小
	m_animateCtrl.SetWindowPos(NULL, 0, 0, m_rectAnimateCtrl.Width(), m_rectAnimateCtrl.Height(),
							   SWP_NOZORDER|SWP_NOMOVE|SWP_NOACTIVATE|SWP_SHOWWINDOW);
	//打开文件
	m_animateCtrl.Open(m_cstrFileName);
	
	//重画并更新控件窗口
	InvalidateRect(&m_rectAnimateCtrl);
	UpdateWindow();
}

void CExample5EDlg::OnBrowse() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg( TRUE,_T("AVI"),_T("*.AVI"),
					 OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
					 _T("Animation (*.AVI)|*.AVI|"));

	if( dlg.DoModal()==IDOK )
	{
		m_cstrFileName = dlg.GetPathName();
		UpdateData(FALSE);
		ApplyChanges();
	}	
}

void CExample5EDlg::OnFileChange() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CFileStatus filestatus;
	if(CFile::GetStatus(m_cstrFileName, filestatus))
		ApplyChanges();
}

void CExample5EDlg::OnCenter() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if( m_bCenter )
		m_dwStyle |= ACS_CENTER;
	else
		m_dwStyle &= ~ ACS_CENTER;
	ApplyChanges();	
}

void CExample5EDlg::OnAutoplay() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if( m_bAutoPlay )
		m_dwStyle |= ACS_AUTOPLAY;
	else
		m_dwStyle &= ~ACS_AUTOPLAY;
	ApplyChanges();	
}

void CExample5EDlg::OnTransparent() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if( m_bTransparent )
		m_dwStyle |= ACS_TRANSPARENT;
	else
		m_dwStyle &= ~ACS_TRANSPARENT;
	ApplyChanges();	
}

void CExample5EDlg::OnPlay() 
{
	// TODO: Add your control notification handler code here
	m_animateCtrl.Play(0,-1,1);	
}

void CExample5EDlg::OnStop() 
{
	// TODO: Add your control notification handler code here
	m_animateCtrl.Stop();
}
