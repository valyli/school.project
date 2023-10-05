// ShutDownDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShutDown.h"
#include "ShutDownDlg.h"
#include "Shortcut.h"
#include "PwdDlg.h"
#include "KeyDlg.h"
#include "IdleUI.h"
#include "Input.h"

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
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
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
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		CString ss;
		pWnd->GetWindowText(ss);
		if(memcmp(ss,"chf@371.net",11) == 0)
		{
			pDC->SetTextColor(RGB(0,0,238));
		}
	}	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
CRect rcStatic; 
CPoint ptCursor; 

	CWnd *pStatic=GetDlgItem(IDC_STATIC_MAIL);
	pStatic->GetWindowRect(rcStatic);
	GetCursorPos(&ptCursor);

	if(rcStatic.PtInRect(ptCursor))
	{
		ShellExecute(m_hWnd,NULL,"mailto:chf@371.net",NULL,NULL,SW_SHOWMAXIMIZED);
	}

	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CAboutDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
CRect rcStatic; 
CPoint ptCursor; 

	CWnd *pStatic=GetDlgItem(IDC_STATIC_MAIL);
	pStatic->GetWindowRect(rcStatic);
	GetCursorPos(&ptCursor);

	if(rcStatic.PtInRect(ptCursor))
	{
//change cursor to hand
		HCURSOR hHandCursor = AfxGetApp()->LoadCursor(IDC_HAND);
		if(hHandCursor)
			SetCursor(hHandCursor); 

		return TRUE; 
	}

	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

/////////////////////////////////////////////////////////////////////////////
// CShutDownDlg dialog

CShutDownDlg::CShutDownDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShutDownDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShutDownDlg)
	m_sNowTime = _T("");
	m_Time1 = CTime(2000,8,13,11,59,0);
	m_Time2 = CTime(2000,8,13,17,59,0);
	m_Time3 = CTime(2000,8,13,21,59,0);
	m_UserTime1 = CTime(2000,8,13,0,0,0);
	m_UserTime2 = CTime(2000,8,13,1,0,0);
	m_Check1 = TRUE;
	m_Check2 = TRUE;
	m_Check3 = TRUE;
	m_Check4 = FALSE;
	m_Check5 = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Cdrom = FALSE;
}

void CShutDownDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShutDownDlg)
	DDX_Control(pDX, IDC_DATETIMEPICKER5, m_UserTimer2);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_UserTimer1);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_Timer3);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_Timer2);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_Timer1);
	DDX_Text(pDX, IDC_STATIC_NOW, m_sNowTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Time1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_Time2);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_Time3);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_UserTime1);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER5, m_UserTime2);
	DDX_Check(pDX, IDC_CHECK1, m_Check1);
	DDX_Check(pDX, IDC_CHECK2, m_Check2);
	DDX_Check(pDX, IDC_CHECK3, m_Check3);
	DDX_Check(pDX, IDC_CHECK4, m_Check4);
	DDX_Check(pDX, IDC_CHECK5, m_Check5);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShutDownDlg, CDialog)
	//{{AFX_MSG_MAP(CShutDownDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, OnDatetimechangeDatetimepicker2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER3, OnDatetimechangeDatetimepicker3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER4, OnDatetimechangeDatetimepicker4)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER5, OnDatetimechangeDatetimepicker5)
	ON_BN_CLICKED(IDC_BUTTON_SHUTDOWN, OnButtonShutdown)
	ON_BN_CLICKED(IDC_BUTTON_HIDE, OnButtonHide)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	ON_BN_CLICKED(IDC_CHECK5, OnCheck5)
	ON_COMMAND(ID_MENU_ABORT, OnMenuAbort)
	ON_COMMAND(ID_MENU_MAIN, OnMenuMain)
	ON_COMMAND(ID_MENU_NOWSHUT, OnMenuNowshut)
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	ON_COMMAND(ID_MENU_SHORTCUT, OnMenuShortcut)
	ON_COMMAND(ID_MENU_OUT, OnMenuOut)
	ON_COMMAND(ID_MENU_CLOSE, OnMenuClose)
	ON_COMMAND(ID_MENU_SYSTEM, OnMenuSystem)
	ON_COMMAND(ID_MENU_PASSWORD, OnMenuPassword)
	ON_COMMAND(ID_MENU_IDLEMIN, OnMenuIdlemin)
	ON_COMMAND(ID_MENU_REBOOT, OnMenuReboot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShutDownDlg message handlers

BOOL CShutDownDlg::OnInitDialog()
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

	CString str1,str2,str3,pwd;
	UINT	ctl1,ctl2,ctl3;
	time_t	t1,t2,t3;

	str1 = AfxGetApp()->GetProfileString("ShutDown","time1");
	str2 = AfxGetApp()->GetProfileString("ShutDown","time2");
	str3 = AfxGetApp()->GetProfileString("ShutDown","time3");
	pwd	 = AfxGetApp()->GetProfileString("ShutDown","pwd");

	t1 = (time_t) atol(str1);
	t2 = (time_t) atol(str2);
	t3 = (time_t) atol(str3);

	ctl1 = AfxGetApp()->GetProfileInt("ShutDown","timer1",1);
	ctl2 = AfxGetApp()->GetProfileInt("ShutDown","timer2",1);
	ctl3 = AfxGetApp()->GetProfileInt("ShutDown","timer3",1);
	m_IdleMin = AfxGetApp()->GetProfileInt("ShutDown","idlemin",0);

	m_Check1 = ctl1;
	m_Check2 = ctl2;
	m_Check3 = ctl3;

	if(str1.IsEmpty())
	{
		t1 = m_Time1.GetTime();
		t2 = m_Time2.GetTime();
		t3 = m_Time3.GetTime();

		str1.Format("%ld",t1);
		str2.Format("%ld",t2);
		str3.Format("%ld",t3);

		AfxGetApp()->WriteProfileString("ShutDown","time1",str1);
		AfxGetApp()->WriteProfileString("ShutDown","time2",str2);
		AfxGetApp()->WriteProfileString("ShutDown","time3",str3);

		AfxGetApp()->WriteProfileInt("ShutDown","timer1",1);
		AfxGetApp()->WriteProfileInt("ShutDown","timer2",1);
		AfxGetApp()->WriteProfileInt("ShutDown","timer3",1);
		AfxGetApp()->WriteProfileInt("ShutDown","idlemin",0);

		m_Check1 = 0;
		m_Check2 = 0;
		m_Check3 = 0;
		m_IdleMin= 0;
	}

	if(pwd.IsEmpty())
	{
		pwd = _T("12345678");
		CShutDownApp *myapp = (CShutDownApp *)AfxGetApp();
		myapp->strCheck = myapp->KeyChanged(pwd);
		AfxGetApp()->WriteProfileString("ShutDown","pwd",myapp->strCheck);
	}

	m_Time1 = CTime(t1);
	m_Time2 = CTime(t2);
	m_Time3 = CTime(t3);

	SetTimer(0,1000,NULL);

	m_Timer1.EnableWindow(m_Check1);
	m_Timer2.EnableWindow(m_Check2);
	m_Timer3.EnableWindow(m_Check3);
	m_UserTimer1.EnableWindow(m_Check4);
	m_UserTimer2.EnableWindow(m_Check5);

	m_Cdrom = GetCdrom();
	
	if(!IdleUIInit())
	{
		AfxMessageBox(IDS_INIT_IDLE_ERROR, MB_ICONWARNING);
		m_IdleOK = FALSE;
	}
	m_IdleOK = TRUE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShutDownDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShutDownDlg::OnPaint() 
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
HCURSOR CShutDownDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CShutDownDlg::OnOK() 
{
NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.uID = 10;
	nid.hWnd = m_hWnd;
	Shell_NotifyIcon(NIM_DELETE, &nid);

	KillTimer(0);
	if(m_IdleOK)
		IdleUITerm();

	CDialog::OnOK();
}

HBRUSH CShutDownDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	if(nCtlColor == CTLCOLOR_STATIC)
	{
		CString ss;
		pWnd->GetWindowText(ss);
		if(memcmp(ss,"现在时间",8) != 0 &&
			memcmp(ss,"预定时间",8) != 0 &&
			memcmp(ss,"自定义时间",10) != 0 &&
			memcmp(ss,"条件设置",8) !=0 )
		{
			pDC->SetTextColor(RGB(0,0,238));
		}
		else
		{
			pDC->SetTextColor(RGB(250,0,238));
		}
	}
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CShutDownDlg::OnTimer(UINT nIDEvent) 
{
int hour,min,sec;
int yhour,ymin,ysec;
float nmin;

	if(m_sNowTime.IsEmpty())
	{
		OnButtonHide();
	}

	CDialog::OnTimer(nIDEvent);

	if(m_IdleOK)
	{
		nmin = (float)((GetTickCount() - IdleUIGetLastInputTime())/1000)/60.00f;
		if(nmin == (float)m_IdleMin && m_IdleMin != 0)
		{
			OnMenuSystem();
		}
	}

	CTime nowtime = CTime::GetCurrentTime();
	m_sNowTime = nowtime.Format(_T("%Y-%m-%d %H:%M:%S"));

	if(m_Check5 == TRUE)
		m_UserTime2 -= CTimeSpan(0, 0, 0, 1);

	UpdateData(FALSE);

	hour = nowtime.GetHour();
	min	 = nowtime.GetMinute();
	sec  = nowtime.GetSecond();

	yhour = m_Time1.GetHour();
	ymin  = m_Time1.GetMinute();
	ysec  = m_Time1.GetSecond();

	if(hour == yhour && (ymin - min) == 1 && m_Check1 == TRUE)
	{
		LockWindow();
	}

	if(hour == yhour && min == ymin && m_Check1 == TRUE)
	{
		OnButtonShutdown();
		return;
	}

	yhour = m_Time2.GetHour();
	ymin  = m_Time2.GetMinute();
	ysec  = m_Time2.GetSecond();

	if(hour == yhour && (ymin - min) == 1 && m_Check2 == TRUE)
	{
		LockWindow();
	}

	if(hour == yhour && min == ymin && m_Check2 == TRUE)
	{
		OnButtonShutdown();
		return;
	}

	yhour = m_Time3.GetHour();
	ymin  = m_Time3.GetMinute();
	ysec  = m_Time3.GetSecond();

	if(hour == yhour && (ymin - min) == 1 && m_Check3 == TRUE)
	{
		LockWindow();
	}

	if(hour == yhour && min == ymin && m_Check3 == TRUE)
	{
		OnButtonShutdown();
		return;
	}
	
	yhour = m_UserTime1.GetHour();
	ymin  = m_UserTime1.GetMinute();
	ysec  = m_UserTime1.GetSecond();

	if(hour == yhour && (ymin - min) == 1 && m_Check4 == TRUE)
	{
		LockWindow();
	}

	if(hour == yhour && min == ymin && m_Check4 == TRUE)
	{
		OnButtonShutdown();
		return;
	}

	yhour = m_UserTime2.GetHour();
	ymin  = m_UserTime2.GetMinute();
	ysec  = m_UserTime2.GetSecond();

	if(yhour == 0 && ymin == 1 && ysec == 0 && m_Check5 == TRUE)
	{
		LockWindow();
	}

	if(yhour == 0 && ymin == 0 && ysec <= 5 && m_Check5 == TRUE)
	{
		OnButtonShutdown();
		return;
	}
}

void CShutDownDlg::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();

	time_t t = m_Time1.GetTime();
	CString str;
	str.Format("%ld",t);
	AfxGetApp()->WriteProfileString("ShutDown","time1",str);

	*pResult = 0;
}

void CShutDownDlg::OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	
	time_t t = m_Time2.GetTime();
	CString str;
	str.Format("%ld",t);
	AfxGetApp()->WriteProfileString("ShutDown","time2",str);

	*pResult = 0;
}

void CShutDownDlg::OnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	
	time_t t = m_Time3.GetTime();
	CString str;
	str.Format("%ld",t);
	AfxGetApp()->WriteProfileString("ShutDown","time3",str);

	*pResult = 0;
}

void CShutDownDlg::OnDatetimechangeDatetimepicker4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	*pResult = 0;
}

void CShutDownDlg::OnDatetimechangeDatetimepicker5(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	
	*pResult = 0;
}

void CShutDownDlg::OnButtonShutdown() 
{
	ExitWindowsEx(EWX_SHUTDOWN, 0);
}

void CShutDownDlg::OnButtonHide() 
{
NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nid.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	strcpy(nid.szTip,"定时关机V1.0");
	nid.uCallbackMessage = WM_USER + 200;
	nid.uID = 10;
	nid.hWnd =m_hWnd;

	Shell_NotifyIcon(NIM_ADD, &nid);

	ShowWindow(SW_HIDE);
	m_IsShow = FALSE;
}

LRESULT CShutDownDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch(message)
	{
	case WM_USER + 200:
		if(lParam == WM_LBUTTONDBLCLK)
		{
			if(!m_IsShow)
			{
				ShowWindow(SW_SHOWNORMAL);
				BringWindowToTop();
				m_IsShow = TRUE;
			}
			else
			{
				ShowWindow(SW_HIDE);
				m_IsShow = FALSE;
			}
		}

		if(lParam == WM_RBUTTONDOWN)
		{
			CMenu menu;

			if(!menu.LoadMenu(IDR_MENU_MAIN))	break;
			
			CMenu* pSubMenu = menu.GetSubMenu(0);
			
			if(!pSubMenu)	break;

			if(!m_Cdrom)
			{
				pSubMenu->EnableMenuItem(ID_MENU_OUT,MF_GRAYED);
				pSubMenu->EnableMenuItem(ID_MENU_CLOSE,MF_GRAYED);
			}
			
			if(!m_IdleOK)
				pSubMenu->EnableMenuItem(ID_MENU_IDLEMIN,MF_GRAYED);
		
			CPoint pos;
			GetCursorPos(&pos);
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,pos.x,pos.y, this, NULL);
			
			menu.DestroyMenu();
		}
		break;
	}	
	return CDialog::DefWindowProc(message, wParam, lParam);
}

void CShutDownDlg::OnCheck1() 
{
	UpdateData();
	m_Timer1.EnableWindow(m_Check1);
	
	AfxGetApp()->WriteProfileInt("ShutDown","timer1",m_Check1);
}

void CShutDownDlg::OnCheck2() 
{
	UpdateData();
	m_Timer2.EnableWindow(m_Check2);
	AfxGetApp()->WriteProfileInt("ShutDown","timer2",m_Check2);
}

void CShutDownDlg::OnCheck3() 
{
	UpdateData();
	m_Timer3.EnableWindow(m_Check3);
	AfxGetApp()->WriteProfileInt("ShutDown","timer3",m_Check3);
}

void CShutDownDlg::OnCheck4() 
{
	UpdateData();
	m_UserTimer1.EnableWindow(m_Check4);
}

void CShutDownDlg::OnCheck5() 
{
	UpdateData();
	m_UserTimer2.EnableWindow(m_Check5);
}

void CShutDownDlg::OnMenuAbort() 
{
CAboutDlg dlg;
	dlg.DoModal();
}

void CShutDownDlg::OnMenuMain() 
{
	ShowWindow(SW_SHOWNORMAL);
	BringWindowToTop();
	CenterWindow();
	m_IsShow = TRUE;
}

void CShutDownDlg::OnMenuNowshut() 
{
	OnButtonShutdown();
}

void CShutDownDlg::OnMenuReboot() 
{
	ExitWindowsEx(EWX_REBOOT, 0);
}

void CShutDownDlg::OnMenuExit() 
{
	OnOK();	
}

void CShutDownDlg::OnMenuShortcut() 
{
char path[MAX_PATH];
char link[MAX_PATH];
CShortcut shortcut;
SHORTCUTSTRUCT strt;

	memset(path,0,sizeof(path));
	memset(link,0,sizeof(link));

	GetWindowsDirectory(link,MAX_PATH);
	GetCurrentDirectory(MAX_PATH,path);

	wsprintf(link+strlen(link),"%s","\\Start Menu\\Programs\\启动\\定时关机.lnk");
	wsprintf(path+strlen(path),"\\%s.exe",AfxGetApp()->m_pszExeName);

	strt.nIconIndex	= 0;
	strt.nShowCmd	= 0;
	strt.wHotkey	= MAKEWORD((BYTE) 0, (BYTE) 0);
	strt.strPath	= link;
	strt.strTarget	= path;
	strt.strArgs	= _T("");
	strt.strDescription	 = _T("");
	strt.strIconLocation = _T("");

	shortcut.CreateEx(&strt);
}

void CShutDownDlg::OnMenuOut() 
{
	if(mciSendString("set cdaudio door open",NULL,0,NULL)!=0)
		MessageBox("open error!");
}

void CShutDownDlg::OnMenuClose() 
{
	if(mciSendString("set cdaudio door closed",NULL,0,NULL)!=0)
		MessageBox("close error!");
}

BOOL CShutDownDlg::GetCdrom()
{
BOOL cdrom=FALSE;

	DWORD dwDrives = GetLogicalDrives();
	UINT uType;
	char szDrive[20]; 

	szDrive[1] = ':';
	szDrive[2] = '\0';
	// do all 32 just for kicks
	for( int i = 0; i < 32; i++ )
	{
		szDrive[0] = 'A' + (char)i;
		DWORD dwTemp = dwDrives;
		if( dwTemp & 1 )
		{
			ASSERT(strlen(szDrive)== 2);
			char szTemp[5];
			strcpy(szTemp, szDrive);
			strcat(szTemp, "\\.");
			uType = GetDriveType( (LPCTSTR)szTemp );

			if(uType == DRIVE_CDROM)
				cdrom = TRUE;
		}
	}

	return cdrom;
}

void CShutDownDlg::OnMenuSystem() 
{
CPwdDlg dlg;

	dlg.DoModal();
}

void CShutDownDlg::OnMenuPassword() 
{
CKeyDlg	dlg;

	dlg.DoModal();
}

void CShutDownDlg::OnMenuIdlemin() 
{
CInput dlg;
CString ss;

	dlg.SetCaption(_T("请输入时间(分钟)"));
	dlg.SetTitle(_T("鼠标键盘停止活动多少分钟后,锁定控制台:"));
	dlg.SetTextSelect(TRUE);
	
	ss.Format("%d",m_IdleMin);
	dlg.SetEditText(ss);
	if(dlg.DoModal() == IDOK)
	{
		ss = dlg.GetEditString();
		AfxGetApp()->WriteProfileInt("ShutDown","idlemin",atoi(ss));
		m_IdleMin = atoi(ss);
	}
}

void CShutDownDlg::LockWindow()
{
	ShowWindow(SW_SHOWNORMAL);
	BringWindowToTop();
	CenterWindow();
	m_IsShow = TRUE;
	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | WS_EX_TOPMOST);
}
