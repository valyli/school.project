// exCDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "exCD.h"
#include "exCDDlg.h"
#include "exsetdlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
#include "exsetdlg.h"
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
// CExCDDlg dialog

CExCDDlg::CExCDDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExCDDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExCDDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExCDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExCDDlg)
	DDX_Control(pDX, IDC_TRACK, m_track);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExCDDlg, CDialog)
	//{{AFX_MSG_MAP(CExCDDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_PLAYMODE, OnPlaymode)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_EJECT, OnEject)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_LAST, OnLast)
	ON_CBN_SELCHANGE(IDC_TRACK, OnSelchangeTrack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExCDDlg message handlers

BOOL CExCDDlg::OnInitDialog()
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
	DWORD Dflag;
	char buf[128];
	Dflag = m_cd.Open();
	if(NULL != Dflag)
	{
		for(int i=0;i<m_cd.GetTracks();i++)
		{
			CString info;
			info.Format("CD曲目 %d",i+1);
			m_track.AddString(info);
		}
		m_nCurTrack=1;
		m_track.SetCurSel(m_nCurTrack-1);
	}
	else 
	{
		mciGetErrorString(Dflag,buf,strlen(buf));
		AfxMessageBox (buf);
		return FALSE;
	}
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CExCDDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExCDDlg::OnPaint() 
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
HCURSOR CExCDDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CExCDDlg::Open()
{
	DWORD Dflag;
	char buf[128];
	Dflag = m_cd.Open();
	if(NULL != Dflag)
	{
		for(int i=0;i<m_cd.GetTracks();i++)
		{
			CString info;
			info.Format("CD曲目 %d",i+1);
			m_track.AddString(info);
		}
		m_nCurTrack=1;
		m_track.SetCurSel(m_nCurTrack-1);
	}
	else 
	{
		mciGetErrorString(Dflag,buf,strlen(buf));
		AfxMessageBox (buf);
	}
		return ;
}
void CExCDDlg::OnPlay() 
{
	if(m_cd.IsDriveReady())
	{
		if(m_cd.Play()!=NULL)
			AfxMessageBox ("播放CD出错：");
	}
	else
	{
		m_cd.Open();
		MessageBox ("光驱没有准备好：");
	}
}

void CExCDDlg::OnPlaymode() 
{
	exsetdlg dlg;
	DWORD Dflag;
	if(m_cd.m_Open)
	{
		dlg.m_fmin = dlg.m_tmin = m_cd.GetMinutes();
		dlg.m_fsec = dlg.m_tsec = m_cd.GetSeconds();
		if(dlg.DoModal() == IDOK){
			DWORD Dfrom =MCI_MAKE_TMSF(m_cd.GetTrack(),
				dlg.m_fmin,dlg.m_fsec,m_cd.GetFrames());
			DWORD Dto =MCI_MAKE_TMSF(m_cd.GetTrack(),
				dlg.m_tmin,dlg.m_tsec,m_cd.GetFrames()); 
			m_cd.Pause();
			Dflag = m_cd.Plays(Dfrom,Dto);
			if(!Dflag){
				AfxMessageBox("播放出错");
				return;
			}
		}
	}
}
void CExCDDlg::OnPause() 
{
	m_cd.Pause();
}
void CExCDDlg::OnEject() 
{
	if (m_cd.m_Open)
	{
		m_cd.OpenCDdoor(-1);
		m_cd.Close();
	}
	else
	{
		m_cd.OpenCDdoor(1);
	}
}
void CExCDDlg::OnNext() 
{
	int nTrack;//得到当前播放的音轨数
	nTrack = m_cd.GetTrack();//将当前音轨数加1
	m_cd.Pause();
	nTrack += 1;//如果是最后一条音轨就跳到第一条音轨
	if (nTrack > m_cd.GetTracks())
		nTrack = 1;//改变播放位置到新音轨开头
	m_cd.SeekTo(nTrack, 0, 0, 0);
	m_track.SetCurSel(nTrack);
	m_cd.Play();

}
void CExCDDlg::OnStop() 
{
	m_cd.Stop();
}
void CExCDDlg::OnLast() 
{
	int nTrack;	//得到当前播放的音轨数
	nTrack = m_cd.GetTrack();//将当前音轨数加1
	m_cd.Pause();
	nTrack-=1;//如果是第一条音轨就跳到最后条音轨
	if (nTrack ==1)
		nTrack = m_cd.GetTracks();//改变播放位置到新音轨开头
	m_cd.SeekTo(nTrack, 0, 0, 0);
	m_track.SetCurSel(nTrack);
	m_cd.Play();
	
}
void CExCDDlg::OnSelchangeTrack() 
{
	DWORD Dflag;
	char buf[100];
	m_nCurTrack=m_track.GetCurSel()+1;
	Dflag = m_cd.SeekTo(m_nCurTrack,0,0,0);
	if(Dflag){
		mciGetErrorString(Dflag,buf,strlen(buf));
		AfxMessageBox(buf);
	}
}

BOOL CExCDDlg::DestroyWindow() 
{
	if(m_cd.m_wDeviceID!=NULL)
		if(m_cd.Open)
		{
			m_cd.Close();
		}
	return CDialog::DestroyWindow();
}
