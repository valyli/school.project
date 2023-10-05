// CDPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CDPlayer.h"
#include "CDPlayerDlg.h"

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
// CCDPlayerDlg dialog
#include "mmsystem.h"
CCDPlayerDlg::CCDPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCDPlayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCDPlayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCDPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCDPlayerDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCDPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CCDPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCDPlayerDlg message handlers

BOOL CCDPlayerDlg::OnInitDialog()
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


	//Play 5 seconds of CD track 3 via the Command String
	char szRetMsg[80];
	char szErrorMessage[512];
	MCIERROR errOpen;
	errOpen=mciSendString("open cdaudio alias mycd wait",
			szRetMsg,sizeof(szRetMsg),m_hWnd);
	if (szRetMsg[0]!='1')
	{
		//Display the open error
		mciGetErrorString(errOpen,szErrorMessage,512);
		AfxMessageBox(szErrorMessage);
	}
	else
	{
		//set format to tracks/minutes/seconds/frames
		mciSendString("set mycd time format tmsf",
				szRetMsg,sizeof(szRetMsg),m_hWnd);
		//Play 5 seconds of track 3 from 12 seconds in
		mciSendString(
			"play mycd from 3:0:12:0 to 3:0:17:0 wait",
			szRetMsg,sizeof(szRetMsg),m_hWnd);
		//Close the device
		mciSendString("close mycd",
			szRetMsg,sizeof(szRetMsg),m_hWnd);
	}

	//Play 5 seconds of CD track 3 via Command Message
	MCI_OPEN_PARMS myCDOpen={NULL,0,"cdaudio",NULL,NULL};
	errOpen=mciSendCommand(NULL,MCI_OPEN,
				MCI_OPEN_TYPE|MCI_WAIT,(DWORD)&myCDOpen);
	if (errOpen)
	{
		//Display the open error
		mciGetErrorString(errOpen,szErrorMessage,512);
		AfxMessageBox(szErrorMessage);
	}
	else
	{
		//set format to tracks/minutes/seconds/frames
		MCI_SET_PARMS setParams={NULL,
			MCI_FORMAT_TMSF,0};
		errOpen=mciSendCommand(myCDOpen.wDeviceID,MCI_SET,
			MCI_SET_TIME_FORMAT,(DWORD)&setParams);

		//Play 5 seconds of track 3 from 12seconds
		MCI_PLAY_PARMS playParams={NULL,
			MCI_MAKE_TMSF(3,0,12,0),
			MCI_MAKE_TMSF(3,0,17,0)};
		mciSendCommand(myCDOpen.wDeviceID,MCI_PLAY,
			MCI_FROM|MCI_TO|MCI_WAIT,
			(DWORD)&playParams);
		//Close the device
		MCI_GENERIC_PARMS genParams={NULL};
		mciSendCommand(myCDOpen.wDeviceID,MCI_CLOSE,
			NULL,(DWORD)&genParams);
	}	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCDPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCDPlayerDlg::OnPaint() 
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
HCURSOR CCDPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
