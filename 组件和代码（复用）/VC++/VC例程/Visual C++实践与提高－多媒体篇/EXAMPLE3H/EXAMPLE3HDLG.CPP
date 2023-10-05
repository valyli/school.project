// Example3HDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Example3H.h"
#include "Example3HDlg.h"

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
// CExample3HDlg dialog

CExample3HDlg::CExample3HDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExample3HDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExample3HDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample3HDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExample3HDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExample3HDlg, CDialog)
	//{{AFX_MSG_MAP(CExample3HDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample3HDlg message handlers

BOOL CExample3HDlg::OnInitDialog()
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
	CRect rect;
	GetClientRect(&rect);
	int nWidth	=	rect.Width();
	int nHeight	=	rect.Height();

	m_ctlRichEdit.Create(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE,
							CRect(0, 0, nWidth, nHeight), this, IDC_RICHEDIT);
	m_ctlRichEdit.DragAcceptFiles(TRUE);
	DrawRichText();//用来创建文字
	m_ctlRichEdit.ShowWindow(SW_SHOW);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExample3HDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExample3HDlg::OnPaint() 
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
HCURSOR CExample3HDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExample3HDlg::DrawRichText()    // CRichEditCtrl
{
	//创建字符串
	CString sText1	=	"No pains, no gains";
	CString sText2	=	"Haste makes waste";
	CString sText3	=	"As you sow you shall mow";
	CString sText;

	//将字符串加到编辑控件中
	sText.Format(sText1 + "\r\n" + sText2 + "\r\n" + sText3);
	m_ctlRichEdit.SetWindowText(sText);

	
	CHARFORMAT cf;
	
	//设置sText1的输出格式
	long nStartChar	=	0;
	int nEndChar	=	sText1.GetLength();
	SetStyle1(cf);
	m_ctlRichEdit.SetSel(nStartChar, nEndChar);
	m_ctlRichEdit.SetSelectionCharFormat(cf);

	//设置sText2的输出格式
	nStartChar	=	nEndChar+2;
	nEndChar	=	nStartChar+sText2.GetLength();
	SetStyle2(cf);
	m_ctlRichEdit.SetSel(nStartChar, nEndChar);
	m_ctlRichEdit.SetSelectionCharFormat(cf);
   
	//设置sText3的输出格式
	nStartChar	=	nEndChar+2;
	nEndChar	=	nStartChar+sText3.GetLength();
	SetStyle3(cf);
	m_ctlRichEdit.SetSel(nStartChar, nEndChar);
	m_ctlRichEdit.SetSelectionCharFormat(cf);
	m_ctlRichEdit.HideSelection(true,false);
}

void CExample3HDlg::SetStyle1(CHARFORMAT& cf)
{
   cf.cbSize          = sizeof(CHARFORMAT); 
   cf.dwMask          = CFM_COLOR | CFM_FACE | CFM_SIZE | 
                        CFM_ITALIC | CFM_BOLD;
   cf.dwEffects       = CFE_BOLD | CFE_ITALIC; 
   cf.yHeight         = 600; 
   cf.crTextColor     = RGB(0,0,255);
   cf.bCharSet        = ANSI_CHARSET;
   cf.bPitchAndFamily = FF_ROMAN;
   
   lstrcpy(cf.szFaceName, "Times New Roman"); 
}

void CExample3HDlg::SetStyle2(CHARFORMAT& cf)
{
   cf.cbSize          = sizeof(CHARFORMAT);
   cf.dwMask          = CFM_COLOR | CFM_FACE | CFM_SIZE |
                        CFM_ITALIC | CFM_BOLD;
   cf.dwEffects       = CFE_BOLD | CFE_ITALIC; 
   cf.yHeight         = 450; 
   cf.crTextColor     = RGB(0,255,0);
   cf.bCharSet        = ANSI_CHARSET;
   cf.bPitchAndFamily = FF_ROMAN;

   lstrcpy(cf.szFaceName, "Arial");
}   

void CExample3HDlg::SetStyle3(CHARFORMAT& cf)
{
   cf.cbSize          = sizeof(CHARFORMAT);
   cf.dwMask          = CFM_COLOR | CFM_FACE | CFM_SIZE;
   cf.yHeight         = 300; 
   cf.crTextColor     = RGB(255,0,0);
   cf.bCharSet        = ANSI_CHARSET;
   cf.bPitchAndFamily = FF_SWISS;   

   lstrcpy(cf.szFaceName, "Comis Sans MS");
}