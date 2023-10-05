// try3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "try3.h"
#include "try3Dlg.h"

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
// CTry3Dlg dialog

CTry3Dlg::CTry3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTry3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTry3Dlg)
	m_x = 0;
	m_y = 0;
	m_posx = 0;
	m_posy = 0;
	m_penspeed = 0;
	m_LastOut = _T("");
	m_Phyposx = 0.0;
	m_Phyposy = 0.0;
	m_Step = 0.0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTry3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTry3Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_x);
	DDX_Text(pDX, IDC_EDIT2, m_y);
	DDX_Text(pDX, IDC_EDIT3, m_posx);
	DDX_Text(pDX, IDC_EDIT4, m_posy);
	DDX_Text(pDX, IDC_EDIT5, m_penspeed);
	DDX_Text(pDX, IDC_EDIT6, m_LastOut);
	DDX_Text(pDX, IDC_EDIT7, m_Phyposx);
	DDX_Text(pDX, IDC_EDIT8, m_Phyposy);
	DDX_Text(pDX, IDC_EDIT9, m_Step);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTry3Dlg, CDialog)
	//{{AFX_MSG_MAP(CTry3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PA, OnButtonPa)
	ON_BN_CLICKED(IDC_BUTTON_PR, OnButtonPr)
	ON_BN_CLICKED(IDC_BUTTON_PD, OnButtonPd)
	ON_BN_CLICKED(IDC_BUTTON_PU, OnButtonPu)
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_BN_CLICKED(IDC_BUTTON_VS, OnButtonVs)
	ON_BN_CLICKED(IDC_BUTTON_PDC, OnButtonPdc)
	ON_BN_CLICKED(IDC_BUTTON_PUC, OnButtonPuc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTry3Dlg message handlers

BOOL CTry3Dlg::OnInitDialog()
{
	m_Step = Print.PlotterStep();
	Setdata();
	Print.OpenPort();
	Print.InitPlotter();

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
/*	CString m_LPTString=_T("LPT1");
	hFile=CreateFile(
		m_LPTString,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL
		);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Invalid LPT or LPT1 is not open");
	}
*/
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTry3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTry3Dlg::OnPaint() 
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
HCURSOR CTry3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTry3Dlg::OnButtonPa() 
{
	UpdateData(TRUE);
	Print.PA(m_x,m_y);
	Setdata();
	UpdateData(FALSE);
}

void CTry3Dlg::OnButtonPr() 
{
	UpdateData(TRUE);
	Print.PR(m_x,m_y);
	Setdata();
	UpdateData(FALSE);
}

void CTry3Dlg::OnButtonPd() 
{
	UpdateData(TRUE);
	Print.PD(m_x,m_y);
	Setdata();
	UpdateData(FALSE);
}

void CTry3Dlg::OnButtonPu() 
{
	UpdateData(TRUE);
	Print.PU(m_x,m_y);
	Setdata();
	UpdateData(FALSE);
}

void CTry3Dlg::OnButtonInit() 
{
	UpdateData(TRUE);
	if(!Print.InitPlotter())
		MessageBox("Can not Reset!","",MB_OK);
	else
	{
		Setdata();
		m_x = 0;
		m_y = 0;
		UpdateData(FALSE);
		MessageBox("Already Reset.","",MB_OK);
	}
}

void CTry3Dlg::OnButtonVs() 
{
	UpdateData(TRUE);
	Print.VS(m_penspeed);
	Setdata();
	UpdateData(FALSE);
}

void CTry3Dlg::Setdata()
{
		Print.PlotterStep(m_Step);

		m_posx = Print.Absposx();
		m_posy = Print.Absposy();

		m_Phyposx = Print.Phyposx();
		m_Phyposy = Print.Phyposy();

		m_LastOut = Print.LastOut();
		m_penspeed = Print.VS();
}

void CTry3Dlg::OnButtonPdc() 
{
	UpdateData(TRUE);
	Print.PD();
	Setdata();
	UpdateData(FALSE);
}

void CTry3Dlg::OnButtonPuc() 
{
	UpdateData(TRUE);
	Print.PU();
	Setdata();
	UpdateData(FALSE);
}
