// ScrollBarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollBar.h"
#include "ScrollBarDlg.h"

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
// CScrollBarDlg dialog

CScrollBarDlg::CScrollBarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScrollBarDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScrollBarDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScrollBarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScrollBarDlg)
	DDX_Control(pDX, IDC_SCROLLBAR2, m_ScrollBar2);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_ScrollBar1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScrollBarDlg, CDialog)
	//{{AFX_MSG_MAP(CScrollBarDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScrollBarDlg message handlers

BOOL CScrollBarDlg::OnInitDialog()
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
	m_ScrollBar1.SetScrollRange(0,100);
	m_ScrollBar2.SetScrollRange(0,200);
	SCROLLINFO si;
	si.cbSize=sizeof(SCROLLINFO);
	si.nPage=30;
	si.fMask=SIF_PAGE;
	m_ScrollBar1.SetScrollInfo(&si);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScrollBarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScrollBarDlg::OnPaint() 
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
HCURSOR CScrollBarDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScrollBarDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if (pScrollBar->GetDlgCtrlID()==IDC_SCROLLBAR1)
	{
		int nCurrentPos=pScrollBar->GetScrollPos();
		switch(nSBCode)
		{
		case SB_THUMBTRACK:
		case SB_THUMBPOSITION:
			pScrollBar->SetScrollPos(nPos);
			break;
		case SB_LINEUP:
			pScrollBar->SetScrollPos(nCurrentPos-1);
			break;
		case SB_LINEDOWN:
			pScrollBar->SetScrollPos(nCurrentPos+1);
			break;
        case SB_PAGEUP:
			pScrollBar->SetScrollPos(nCurrentPos-5);
			break;
		case SB_PAGEDOWN:
			pScrollBar->SetScrollPos(nCurrentPos+5);
			break;
		}
		m_ScrollBar2.SetScrollPos(2*pScrollBar->GetScrollPos());
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
