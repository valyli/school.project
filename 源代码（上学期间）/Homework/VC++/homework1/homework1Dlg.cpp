// homework1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "homework1.h"
#include "homework1Dlg.h"

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
// CHomework1Dlg dialog

CHomework1Dlg::CHomework1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHomework1Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHomework1Dlg)
	m_Show = 0;
	m_Recycle = FALSE;
	m_State = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Icon_play = AfxGetApp()->LoadIcon(IDI_ICON_PLAY);
	m_Icon_stop = AfxGetApp()->LoadIcon(IDI_ICON_STOP);
	m_Icon_pause = AfxGetApp()->LoadIcon(IDI_ICON_PAUSE);
	m_Icon_forward = AfxGetApp()->LoadIcon(IDI_ICON_FORWARD);
	m_Icon_backward = AfxGetApp()->LoadIcon(IDI_ICON_BACKWARD);
	m_Icon_exit = AfxGetApp()->LoadIcon(IDI_ICON_EXIT);
	m_Icon_recycle = AfxGetApp()->LoadIcon(IDI_ICON_RECYCLE);
	isplay = false;
	m_Recycle = TRUE;
	m_Step = 5;
	isForward = false;
	isBackward = false;
	m_State = "Í£Ö¹";
}

void CHomework1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHomework1Dlg)
	DDX_Slider(pDX, IDC_SLIDER_SHOW, m_Show);
	DDX_Check(pDX, IDC_CHECK_RECYCLE, m_Recycle);
	DDX_Text(pDX, IDC_EDIT_STATE, m_State);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHomework1Dlg, CDialog)
	//{{AFX_MSG_MAP(CHomework1Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PLAY, OnButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, OnButtonForward)
	ON_BN_CLICKED(IDC_BUTTON_BACKWARD, OnButtonBackward)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework1Dlg message handlers

BOOL CHomework1Dlg::OnInitDialog()
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
	CButton* pBn = (CButton*)GetDlgItem(IDC_BUTTON_PLAY);
	pBn->SetIcon(m_Icon_play);
	pBn->EnableWindow(TRUE);

	pBn = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
	pBn->SetIcon(m_Icon_stop);
	pBn->EnableWindow(FALSE);
	
	pBn = (CButton*)GetDlgItem(IDC_BUTTON_FORWARD);
	pBn->SetIcon(m_Icon_forward);
	pBn->EnableWindow(TRUE);

	pBn = (CButton*)GetDlgItem(IDC_BUTTON_BACKWARD);
	pBn->SetIcon(m_Icon_backward);
	pBn->EnableWindow(TRUE);

	pBn = (CButton*)GetDlgItem(IDOK);
	pBn->SetIcon(m_Icon_exit);
	pBn->EnableWindow(TRUE);

	pBn = (CButton*)GetDlgItem(IDC_CHECK_RECYCLE);
	pBn->SetIcon(m_Icon_recycle);
	pBn->EnableWindow(TRUE);

	CSliderCtrl* pSc = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_SHOW);
	
	pSc->SetTicFreq(100);
	pSc->SetRange(0, 1000);
	pSc->SetLineSize(10);

	SetTimer(1, 100, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHomework1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHomework1Dlg::OnPaint() 
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
HCURSOR CHomework1Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHomework1Dlg::OnButtonPlay() 
{
	CButton* pBn_play = (CButton*)GetDlgItem(IDC_BUTTON_PLAY);
	CButton* pBn_stop = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
	pBn_stop->EnableWindow(TRUE);
	if(isplay == false)
	{
		pBn_play->SetIcon(m_Icon_pause);
		m_State = "²¥·Å";
		isplay = true;
	}
	else
	{
		pBn_play->SetIcon(m_Icon_play);
		m_State = "ÔÝÍ£";
		isplay = false;
	}
	UpdateData(FALSE);
}

void CHomework1Dlg::OnButtonStop() 
{
	CButton* pBn_play = (CButton*)GetDlgItem(IDC_BUTTON_PLAY);
	CButton* pBn_stop = (CButton*)GetDlgItem(IDC_BUTTON_STOP);
	CButton* pBn_forward = (CButton*)GetDlgItem(IDC_BUTTON_FORWARD);
	CButton* pBn_backward = (CButton*)GetDlgItem(IDC_BUTTON_BACKWARD);
	pBn_play->SetIcon(m_Icon_play);
	pBn_stop->EnableWindow(FALSE);
	pBn_forward->SetState(0);
	pBn_backward->SetState(0);
	m_Show = 0;
	isplay = false;
	isForward = false;
	isBackward = false;
	m_State = "Í£Ö¹";
	UpdateData(FALSE);
}

void CHomework1Dlg::OnTimer(UINT nIDEvent) 
{
	UpdateData(TRUE);
	if(isForward == true)
	{
		m_Step = 40;
		m_State = "¿ì½ø";
	}
	else if(isBackward == true)
	{
		m_Step = -40;
		m_State = "¿ìÍË";
	}
	else if(isplay == true)
		m_Step = 5;
	else
		m_Step = 0;
	m_Show += m_Step;
	if((m_Show >= 1000 || m_Show < 0) && m_Recycle == FALSE)
		OnButtonStop();
	else if(m_Show >= 1000 && m_Recycle == TRUE)
		m_Show =0;
	else if(m_Show <0 && m_Recycle == TRUE)
		m_Show =1000;
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CHomework1Dlg::OnButtonForward() 
{
	CButton* pBn = (CButton*)GetDlgItem(IDC_BUTTON_FORWARD);
	if(isForward == false)
	{
		pBn->SetState(1);
		isForward = true;
	}
	else
	{
		pBn->SetState(0);
		isForward = false;
	}
}

void CHomework1Dlg::OnButtonBackward() 
{
	CButton* pBn = (CButton*)GetDlgItem(IDC_BUTTON_BACKWARD);
	if(isBackward == false)
	{
		pBn->SetState(1);
		isBackward = true;
	}
	else
	{
		pBn->SetState(0);
		isBackward = false;
	}
}

void CHomework1Dlg::OnClose() 
{
	if(IDYES == AfxMessageBox("Do you want to quit?",MB_YESNO))
	{
		KillTimer(1);
		CDialog::OnClose();
	}
}

void CHomework1Dlg::OnOK() 
{
	PostMessage(WM_CLOSE);
}
