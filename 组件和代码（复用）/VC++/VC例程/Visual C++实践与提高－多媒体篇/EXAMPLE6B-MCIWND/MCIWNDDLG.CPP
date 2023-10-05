// mciwndDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mciwnd.h"
#include "mciwndDlg.h"
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
// CMciwndDlg dialog

CMciwndDlg::CMciwndDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMciwndDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMciwndDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMciwndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMciwndDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMciwndDlg, CDialog)
	//{{AFX_MSG_MAP(CMciwndDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_OPENVIDEO, OnOpenvideo)
	ON_BN_CLICKED(IDC_PLAYVIDEO, OnPlayvideo)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_CLOSEVIDEO, OnClosevideo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMciwndDlg message handlers

BOOL CMciwndDlg::OnInitDialog()
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

void CMciwndDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMciwndDlg::OnPaint() 
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
HCURSOR CMciwndDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CMciwndDlg::OnSize(UINT nType, int cx, int cy) 
{
	CRect rect;
	if(m_mciwnd.m_Open){
		m_mciwnd.GetSourceRect(rect);
		rect.bottom = cy + rect.top;
		rect.right  = cx + rect.left;
		m_mciwnd.PutSourceRect(rect);
		m_mciwnd.PutDestRect(rect);
	}
	CDialog::OnSize(nType, cx, cy);	
}

void CMciwndDlg::OnOpenvideo() 
{
	CString Filter,str;
	Filter = "视频文件 (*.AVI)|*.AVI||";
	CRect rect,itemrect;
	CFileDialog FileDlg (TRUE, NULL, NULL,OFN_HIDEREADONLY,Filter);
	if (FileDlg.DoModal () == IDOK)//单击文件选择对话框的"确定"按钮
	{
		m_mciwnd.m_Open = 1;
		CRect Resoucerect,Drect,Mainwndrect,Wrect,Controlrect;
		this->GetWindowRect(&Mainwndrect);
		CWnd *cwnd = GetDlgItem(IDC_OPENVIDEO);
		cwnd->GetWindowRect(&Controlrect);
	    if (!m_mciwnd.Create(this,
			WS_CHILD|WS_VISIBLE,
			FileDlg.GetFileName()))//打开视频文件
		{
	         MessageBox ("无法打开该文件!");
	         return;
		}
		m_mciwnd.m_str = FileDlg.GetFileName();
		m_mciwnd.GetSourceRect(Resoucerect);
		Wrect.left  = 0;
		Wrect.top   = Controlrect.bottom - Controlrect.top;
		Wrect.right = Resoucerect.right;
		Wrect.bottom   = Resoucerect.bottom - Resoucerect.top + Wrect.top;
		if(5*(Controlrect.right -Controlrect.left)<
			(Resoucerect.right - Resoucerect.left))
		{
			Mainwndrect.right = Mainwndrect.left + Resoucerect.right -Resoucerect.left ;
		}
		if(Mainwndrect.bottom - Mainwndrect.top - 2.7*(Controlrect.bottom - Controlrect.top)
			< Resoucerect.bottom -Resoucerect.top)
		{
			Mainwndrect.bottom = Mainwndrect.top + Resoucerect.bottom - Resoucerect.top +
				Wrect.top*2.7;
		}
		this->MoveWindow(Mainwndrect,1);
		m_mciwnd.PutDestRect(Wrect);
	}	
}
void CMciwndDlg::OnPlayvideo() 
{
	m_mciwnd.Play();
	m_mciwnd.m_Playing = 1;
}
void CMciwndDlg::OnPause() 
{
	m_mciwnd.Pause();	
	m_mciwnd.m_Pause = 1;
}
void CMciwndDlg::OnLast() 
{
	m_mciwnd.Step(-1);	
}
void CMciwndDlg::OnNext() 
{
	m_mciwnd.Step(1);		
}

void CMciwndDlg::OnClosevideo() 
{
	m_mciwnd.Close();	
	m_mciwnd.m_Playing = 0;
	m_mciwnd.m_Open = 0;
}
