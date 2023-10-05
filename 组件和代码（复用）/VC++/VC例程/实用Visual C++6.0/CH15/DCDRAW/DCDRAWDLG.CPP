// DCDrawDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DCDraw.h"
#include "DCDrawDlg.h"

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
// CDCDrawDlg dialog

CDCDrawDlg::CDCDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDCDrawDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDCDrawDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDCDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDCDrawDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDCDrawDlg, CDialog)
	//{{AFX_MSG_MAP(CDCDrawDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DRAWIT, OnDrawit)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDCDrawDlg message handlers

BOOL CDCDrawDlg::OnInitDialog()
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

void CDCDrawDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDCDrawDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, 
			(WPARAM) dc.GetSafeHdc(), 0);

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
		//**Call our drawing function
	
	}
}
			// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDCDrawDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDCDrawDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

	
	//**Redraw the desktop and all child windows
	GetDesktopWindow()->RedrawWindow(NULL,NULL,
		RDW_ERASE|RDW_INVALIDATE|
		RDW_ALLCHILDREN|RDW_ERASENOW);	
}

void CDCDrawDlg::OnDrawit()
{
	// TODO: Add your control notification handler code

	//**Construct a paint DC from the dialog window
	CClientDC clientDC(this);

	//**Create a compatible memory device context
	CDC memDC;
	memDC.CreateCompatibleDC(&clientDC);

	//**Find the Client Rect
	CRect rcClient;
	GetClientRect(&rcClient);

	//**Create a compatible bitmaps
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&clientDC,
		rcClient.Width(),rcClient.Height());

	//**Select it into our memory device context
	memDC.SelectObject(&memBitmap);

	//**loop through the horizontal client rectangle
	for (int x=0;x<rcClient.right;x++)
	{
		//**loop through vertical client rectangle
		for (int y=0;y<rcClient.bottom;y++)
		{
			//**set each pixel to a defferent color
			 memDC.SetPixel(x,y,x*y);
		}
	}

	//**Copy the memory image back to the client
	//device context
	clientDC.BitBlt(0,0,
		rcClient.Width(),rcClient.Height(),
		&memDC,0,0,SRCINVERT);
}
