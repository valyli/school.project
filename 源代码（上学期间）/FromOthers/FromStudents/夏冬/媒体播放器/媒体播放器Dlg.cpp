// 媒体播放器Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "媒体播放器.h"
#include "媒体播放器Dlg.h"


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
	CString	m_mem;
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
	m_mem = _T("");
	//}}AFX_DATA_INIT
    MEMORYSTATUS mem;
	::GlobalMemoryStatus(&mem);
	m_mem.Format("%s %d%s","windows的物理内存信息：",mem.dwTotalPhys/(1024*1024),"MB");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_mem, m_mem);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	 m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
     m_bPlay=FALSE;
	 m_bPause=FALSE;
	 Iscda=0;
	 m_MCIDeviceID=0;
	 m=0;s=0;
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyDlg)
	DDX_Control(pDX, IDC_min, m_min);
	DDX_Control(pDX, IDC_about, m_about);
	DDX_Control(pDX, IDC_close, m_close);
	DDX_Control(pDX, IDC_door, m_door);
	DDX_Control(pDX, IDC_SLIDER2, m_vol);
	DDX_Control(pDX, IDC_SLIDER1, m_time);
	DDX_Control(pDX, IDC_open, m_open);
	DDX_Control(pDX, IDC_next, m_next);
	DDX_Control(pDX, IDC_last, m_last);
	DDX_Control(pDX, IDC_back, m_back);
	DDX_Control(pDX, IDC_before, m_before);
	DDX_Control(pDX, IDC_stop, m_stop);
	DDX_Control(pDX, IDC_pause, m_pause);
	DDX_Control(pDX, IDC_play, m_play);
	DDX_Control(pDX, IDC_MASKEDBOX1, m_show);
	DDX_Control(pDX, IDC_MASKEDBOX2, m_count);
	DDX_Control(pDX, IDC_MASKEDBOX3, m_current);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	//{{AFX_MSG_MAP(CMyDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_play, Onplay)
	ON_BN_CLICKED(IDC_stop, Onstop)
	ON_BN_CLICKED(IDC_pause, Onpause)
	ON_BN_CLICKED(IDC_open, Onopen)
	ON_BN_CLICKED(IDC_close, Onclose)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_next, Onnext)
	ON_BN_CLICKED(IDC_last, Onlast)
	ON_BN_CLICKED(IDC_before, Onbefore)
	ON_BN_CLICKED(IDC_back, Onback)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_door, Ondoor)
	ON_WM_VSCROLL()
	ON_WM_NCHITTEST()
	ON_BN_CLICKED(IDC_about, Onabout)
	ON_BN_CLICKED(IDC_min, Onmin)
	//}}AFX_MSG_MAP
    ON_MESSAGE(MM_MCINOTIFY,OnMciNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlg message handlers

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    SetWindowText("媒体播放器");
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
    door=1;
	state=0;
	m_play.LoadBitmaps(IDB_B,IDB_B1,IDB_B,IDB_B2);
    m_pause.LoadBitmaps(IDB_pause,IDB_pause1,IDB_pause,IDB_pause2);
    m_stop.LoadBitmaps(IDB_stop,IDB_stop1,IDB_stop,IDB_stop2);
    m_before.LoadBitmaps(IDB_before,IDB_before1,IDB_before,IDB_before2);
	m_back.LoadBitmaps(IDB_back,IDB_back1,IDB_back,IDB_back2);
	m_last.LoadBitmaps(IDB_last,IDB_last1,IDB_last,IDB_last2);
	m_next.LoadBitmaps(IDB_next,IDB_next1,IDB_next,IDB_next2);
	m_open.LoadBitmaps(IDB_open,IDB_open1,IDB_open);
    m_door.LoadBitmaps(IDB_door,IDB_door1,IDB_door);
	m_close.LoadBitmaps(IDB_smile,IDB_smile1,IDB_smile);
	m_about.LoadBitmaps(IDB_about1,IDB_about2,IDB_about1);
	m_min.LoadBitmaps(IDB_min1,IDB_min2,IDB_min1);
	m_time.SetPos(0);
	m_time.SetLineSize(1000);
	m_time.SetTicFreq(5000);
	DWORD v,v1,v2;
	CVolumeOutMaster vo;
    v1=vo.GetMinimalVolume();
	v2=vo.GetMaximalVolume();
	v=vo.GetCurrentVolume();
    m_vol.SetRange(0,(int)v2);
	m_vol.SetLineSize(1000);
	m_vol.SetTicFreq(100);
	m_vol.SetPos((int)v);
	m_pause.EnableWindow(false);
	m_play.EnableWindow(false);
	m_stop.EnableWindow(false);
	m_before.EnableWindow(false);
	m_back.EnableWindow(false);
    m_next.EnableWindow(false);
	m_last.EnableWindow(false);
	tip=false;
	CString str;
	str.Format("%s","欢迎使用媒体播放器");
    m_show.SetText(str);
     
	//m_play.setmaskedbitmap( IDB_play, 40, 150, rgb( 255, 0, 0 ) );
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyDlg::OnPaint() 
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
LRESULT CMyDlg::OnMciNotify(WPARAM wParam,LPARAM lParam)
{
	if(wParam==MCI_NOTIFY_SUCCESSFUL)
	{
		m_bPlay=FALSE;
		m_bPause=FALSE;
		Iscda=0;
		return 0;
	}
	return -1;
}
void CMyDlg::ShowError(DWORD dwError)
{
	char szBuf[1000];
    MessageBeep(MB_ICONEXCLAMATION);
	if(mciGetErrorString(dwError,(LPSTR)szBuf,MAXERRORLENGTH))
		MessageBox(szBuf,"MCI错误",MB_ICONEXCLAMATION);
	else 
        MessageBox("未知错误","MCI错误",MB_ICONEXCLAMATION);
}
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyDlg::Onplay() 
{
	// TODO: Add your control notification handler code here
	CString str;
	MCI_PLAY_PARMS mciPlay;
	DWORD dwError;
     if(tip)
	{
		 if(Iscda==1)
		 {
             //MCI_SEEK_PARMS SeekParms;
	         //MessageBox("123",NULL,MB_OK);
	           mciPlay.dwFrom = MCI_MAKE_TMSF( track,m, s, f );
             //mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekParms );
	           mciSendCommand( m_MCIDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &mciPlay);
               SetTimer(1,1000,0);
               str.Format("正在播放CD   第%d首",track);m_show.SetText(str);
		 }
		 else
		 {
			   str.Format("正在播放");m_show.SetText(str);
			   mciPlay.dwFrom=(m*60+s)*1000; 
               mciSendCommand(m_MCIDeviceID,MCI_PLAY,MCI_FROM|MCI_NOTIFY,(DWORD)(LPVOID)&mciPlay);
			   SetTimer(1,1000,0);
		 }
	m_bPlay=true;
	tip=false;
    m_bPause=false;
		 }
	if(!m_bPlay)
	{
	  mciPlay.dwCallback=(long)GetSafeHwnd();
	  if(Iscda==1) 
	  {
	   mciPlay.dwFrom=CMyDlg::track;
	   str.Format("正在播放CD   第%d首",track);
	   m_show.SetText(str);SetTimer(1,1000,0);
       m_bPause=false;
	  }
	  else  {mciPlay.dwFrom=0;str.Format("正在播放",track);m_show.SetText(str);SetTimer(1,1000,0);}
	  dwError=mciSendCommand(m_MCIDeviceID,MCI_PLAY,MCI_FROM|MCI_NOTIFY,
		              (DWORD)(LPVOID)&mciPlay);
       }
   
	if(m_bPlay)
	{
	  if(m_bPause)
	  {
		  if(Iscda!=1)
		  {str.Format("正在播放",track);m_show.SetText(str);SetTimer(1,1000,0);mciPlay.dwFrom=state;dwError= mciSendCommand(m_MCIDeviceID,MCI_PLAY,MCI_FROM|MCI_NOTIFY,(DWORD)(LPVOID)&mciPlay);}
		  else
		  {
			  track=t;
			  str.Format("正在播放CD   第%d首",t);m_show.SetText(str);mciPlay.dwFrom = MCI_MAKE_TMSF( t,m, s, f );mciSendCommand( m_MCIDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &mciPlay);SetTimer(1,1000,0);}
          m_bPause=!m_bPause;
	  }
	  
	    
	}
	//if(dwError)
	//	{
	//		ShowError(dwError);
	//	}
      m_play.EnableWindow(FALSE);
	  m_stop.EnableWindow(TRUE);
	  m_pause.EnableWindow(TRUE);
	  m_last.EnableWindow(TRUE);
	  m_next.EnableWindow(TRUE);
	  m_back.EnableWindow(TRUE);
	  m_before.EnableWindow(true);
	  m_bPlay=TRUE;
	
}


void CMyDlg::Onstop() 
{
	// TODO: Add your control notification handler code here
    KillTimer(1);
	CString str,st; str.Format("停止");m_show.SetText(str);st.Format(_T("0\':0\""));m_count.SetText(st);m_current.SetText(st);
	mciSendCommand(m_MCIDeviceID,MCI_STOP,MCI_WAIT,NULL);
	mciSendCommand(m_MCIDeviceID,MCI_CLOSE,MCI_WAIT,NULL);
    m_bPlay=FALSE;
    m_bPause=FALSE;
	Iscda=0;
    m_time.SetPos(0);
	m_play.EnableWindow(FALSE);
    m_stop.EnableWindow(FALSE);
	m_pause.EnableWindow(FALSE);
    m_open.EnableWindow(TRUE);
	m_last.EnableWindow(FALSE);
	m_next.EnableWindow(FALSE);
    m_back.EnableWindow(false);
	m_before.EnableWindow(false);
}


void CMyDlg::Onpause() 
{
	// TODO: Add your control notification handler code here
    //KillTimer(1);
	DWORD dwError;
    CString str; str.Format("暂停");m_show.SetText(str);
	if(!m_bPause)
	{
	
			
		    dwError=mciSendCommand(m_MCIDeviceID,MCI_PAUSE,0,NULL);
		
            if(!Iscda)
			{
			MCI_STATUS_PARMS StatusParms;
	        StatusParms.dwItem = MCI_STATUS_POSITION;
		    mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	        state=StatusParms.dwReturn;
            }
	

		if(dwError)
		{
			ShowError(dwError);
		}
		m_play.EnableWindow(TRUE);
	    m_stop.EnableWindow(TRUE);
		m_pause.EnableWindow(FALSE);
	    m_last.EnableWindow(TRUE);
	    m_next.EnableWindow(TRUE);
		m_bPause=1;
	}

}

void CMyDlg::Onopen() 
{
	// TODO: Add your control notification handler code here
	CString st; st.Format("打开文件");m_show.SetText(st);
	CString filename, d;
	CString str,tp,cd,cd1;
	MCI_OPEN_PARMS mciOpen;
	DWORD dwError;
    //打开选择文件对话框
	static char szFilter[]
	="波形音频文件(*.wav)|*.wav|MIDI Audio File(*.mid)|*.mid|CD Audio(*.cda)|*.cda|所有文件(*.*)|*.*||";
	CFileDialog dlg(TRUE,"wav",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
    CMyDlg::Onstop();
	if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();//得到文件名
		str=filename.Right(3);//得到文件的扩展名
        cd=filename.Left(10);
       
		cd1=cd.Right(2);

		if(!strcmp(str,"wav")) //判断是否是wav文件
		{
			mciOpen.lpstrDeviceType="waveaudio";
		}
		if(!strcmp(str,"mid"))//判断是否是mid文件
		{
			mciOpen.lpstrDeviceType="sequencer";
		}
		if(!strcmp(str,"cda"))//判断是否是cda文件
		{
			
			mciOpen.lpstrDeviceType="cdaudio";
		    Iscda=1;t=CMyDlg::track=atoi(cd1);

		    
		}
		
		mciOpen.lpstrElementName=filename;//设置打开文件
		dwError=mciSendCommand(0,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,
			             (DWORD)(LPVOID)&mciOpen);//打开MCI设备
		if(dwError)
		{
			ShowError(dwError);
		}
		m_MCIDeviceID=mciOpen.wDeviceID;//获得打开的MCI设备的ID
		m_play.EnableWindow(TRUE);
		m_stop.EnableWindow(TRUE);
		m_pause.EnableWindow(TRUE);
		m_last.EnableWindow(TRUE);
		m_next.EnableWindow(TRUE);
		m_back.EnableWindow(TRUE);
		m_before.EnableWindow(true);
		m_bPlay=FALSE;
		m_bPause=FALSE;
        tp.Format("%s",filename);
        m_show.SetText(tp);
		//the time of CD
		if(Iscda==1)
		{
		MCI_SET_PARMS SetParms;
	    SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
		mciSendCommand( m_MCIDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ;
	    mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );
	    MCI_STATUS_PARMS StatusParms,it;
	    StatusParms.dwItem = MCI_STATUS_LENGTH;
	    StatusParms.dwTrack = (DWORD) track;
        it.dwItem=MCI_STATUS_NUMBER_OF_TRACKS;
		it.dwReturn=0;
		mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusParms );
        mciSendCommand( m_MCIDeviceID, MCI_STATUS,  MCI_STATUS_ITEM , (DWORD)(LPVOID) &it );
        trackl=(int) it.dwReturn;
		CString d;
		d.Format(_T("%2d\':%2d\""),ml=MCI_MSF_MINUTE( StatusParms.dwReturn ),sl=MCI_MSF_SECOND( StatusParms.dwReturn ));
	    m_count.SetText(d);
		m_time.SetRange(0,(ml*60+sl)*1000);
		}
		else
		{
		MCI_SET_PARMS SetParms;
		SetParms.dwTimeFormat = MCI_FORMAT_MILLISECONDS;
        mciSendCommand( m_MCIDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ;
	    mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );
        MCI_STATUS_PARMS StatusParms;
        StatusParms.dwItem = MCI_STATUS_LENGTH;
        mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM , (DWORD)(LPVOID) &StatusParms );
        CString d;
	    int timer=StatusParms.dwReturn;
		sl=timer/1000%60;ml=(timer/1000-sl)/60;
		d.Format(_T("%2d\':%2d\""),ml,sl);
        m_count.SetText(d);
		m_time.SetRange(0,(ml*60+sl)*1000);
		}
	}

    
}

void CMyDlg::Onclose() 
{
	// TODO: Add your control notification handler code here
  
	//CMyDlg::OnDestroy();
	CMyDlg::OnOK();
}

void CMyDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	mciSendCommand(m_MCIDeviceID,MCI_STOP,MCI_WAIT,NULL);//停止播放
	mciSendCommand(m_MCIDeviceID,MCI_CLOSE,MCI_WAIT,NULL);//关闭MCI设备

}




void CMyDlg::Onnext() 
{
	// TODO: Add your control notification handler code here
    KillTimer(1);
	track=t;
	
	if(Iscda==1) {if(m_bPlay) 	
	{
		mciSendCommand(m_MCIDeviceID,MCI_STOP,MCI_WAIT,NULL);}
		//the time of CD
		MCI_SET_PARMS SetParms;
	    SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
        mciSendCommand( m_MCIDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ;
	    mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );
	    
		m_play.EnableWindow(TRUE);
		m_stop.EnableWindow(TRUE);
		m_pause.EnableWindow(TRUE);
	    m_last.EnableWindow(TRUE);
	    m_back.EnableWindow(TRUE);
		m_before.EnableWindow(true);
		m_bPlay=FALSE;
		if(track==(trackl-1)||track==trackl) 
		{
			
			m_next.EnableWindow(FALSE);	
		}
	    else m_next.EnableWindow(TRUE);
	    CMyDlg::track++;t++;
	    if(track==(trackl+1))
		{
			t--;track--;
		}
		MCI_STATUS_PARMS StatusParms;
	    StatusParms.dwItem = MCI_STATUS_LENGTH;
	    StatusParms.dwTrack = (DWORD) track;
        mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusParms );
        CString d;
		d.Format(_T("%2d\':%2d\""),ml=MCI_MSF_MINUTE( StatusParms.dwReturn ),sl=MCI_MSF_SECOND( StatusParms.dwReturn ));
	    m_count.SetText(d);
		CString str; str.Format("准备播放CD 第%d首",track);m_show.SetText(str);}
        
}

void CMyDlg::Onlast() 
{
	// TODO: Add your control notification handler code here
    KillTimer(1);
	track=t;
	if(Iscda==1)  
	{
		if(m_bPlay) 	
		{mciSendCommand(m_MCIDeviceID,MCI_STOP,MCI_WAIT,NULL);}
			//the time of CD
		MCI_SET_PARMS SetParms;
	    SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
        mciSendCommand( m_MCIDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ;
	    mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );
	    
		m_play.EnableWindow(TRUE);
		m_stop.EnableWindow(TRUE);
		m_pause.EnableWindow(TRUE);
		m_back.EnableWindow(TRUE);
		m_before.EnableWindow(true);
		m_next.EnableWindow(TRUE);
		m_bPlay=FALSE;
		
	    if(track==2 ||track==1) m_last.EnableWindow(FALSE);
	    else m_last.EnableWindow(TRUE);
		track--;t--;
		if(track==0)
		{track=1;t=1;}
	    MCI_STATUS_PARMS StatusParms;
	    StatusParms.dwItem = MCI_STATUS_LENGTH;
	    StatusParms.dwTrack = (DWORD) track;
        mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusParms );
        CString d;
		d.Format(_T("%2d\':%2d\""),ml=MCI_MSF_MINUTE( StatusParms.dwReturn ),sl=MCI_MSF_SECOND( StatusParms.dwReturn ));
	    m_count.SetText(d);
		CString str; str.Format("准备播放CD 第%d首",track);m_show.SetText(str);
	}
    
}


void CMyDlg::Onbefore() 
{
	// TODO: Add your control notification handler code here
    if(Iscda==1)  
	{
		
		 	
		Onpause();
	    KillTimer(1);
        //MCI_SET_PARMS SetParms;
	    //SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
        //mciSendCommand( m_MCIDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ;
	    //mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );

		if(!tip)
		{
		MCI_STATUS_PARMS StatusParms;
	    StatusParms.dwItem = MCI_STATUS_POSITION;
		mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	    m=MCI_TMSF_MINUTE( StatusParms.dwReturn );
		s=MCI_TMSF_SECOND( StatusParms.dwReturn );
	    f=MCI_TMSF_FRAME( StatusParms.dwReturn );
		}
		tip=true;
		if(s>=(sl-5)&&m==ml)
		{
			m_before.EnableWindow(false);s=sl;m=ml;
		}
		else
		{
			m_before.EnableWindow(true);
		    if(s<=55)
			{s+=5;}
		    else
			{s=s-60;m++;}
		}
		m_back.EnableWindow(true);
		CString d;
		d.Format(_T("%2d\':%2d\""),m,s);
	    m_current.SetText(d);
		m_time.SetPos((m*60+s)*1000);
		
	}
    else
	{
        Onpause();
	    KillTimer(1);
		if(!tip)
		{
		MCI_STATUS_PARMS StatusParms;
	    StatusParms.dwItem = MCI_STATUS_POSITION;
		mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	    state=StatusParms.dwReturn;
		}
		tip=true;
		if(state>=((ml*60+sl)*1000))
		{
             m_before.EnableWindow(false);s=sl;m=ml;
		}
        else
		{
			m_before.EnableWindow(true);
		    state+=5000;
			s=state/1000%60;
			m=(state/1000-s)/60;
		}
        m_back.EnableWindow(true);
		CString d;
		d.Format(_T("%2d\':%2d\""),m,s);
	    m_current.SetText(d);
		m_time.SetPos((m*60+s)*1000);
		
	}
}

void CMyDlg::Onback() 
{
	// TODO: Add your control notification handler code here
	if(Iscda==1)  
	{
		
		 	
		Onpause();
		KillTimer(1);
		//MCI_SET_PARMS SetParms;
	    //SetParms.dwTimeFormat = MCI_FORMAT_TMSF;
        //mciSendCommand( m_MCIDeviceID, MCI_SET, MCI_WAIT | MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetParms ) ;
	    //mciSendCommand( m_MCIDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL );

		if(!tip)
		{
		MCI_STATUS_PARMS StatusParms;
	    StatusParms.dwItem = MCI_STATUS_POSITION;
		mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	    m=MCI_TMSF_MINUTE( StatusParms.dwReturn );
		s=MCI_TMSF_SECOND( StatusParms.dwReturn );
	    f=MCI_TMSF_FRAME( StatusParms.dwReturn );
		}
		tip=true;
		if(s<=5&&m<=0)
		{
			m_back.EnableWindow(false);s=0;m=0;
		}
		else
		{
			m_back.EnableWindow(true);
		    if(s>=5)
			{s-=5;}
		    else
			{s=55+s;m--;}
		}
		m_before.EnableWindow(true);
		CString d;
		d.Format(_T("%2d\':%2d\""),m,s);
	    m_current.SetText(d);
		m_time.SetPos((m*60+s)*1000);
		
		}

		else
		{
        Onpause();
	    KillTimer(1);
		if(!tip)
		{
		MCI_STATUS_PARMS StatusParms;
	    StatusParms.dwItem = MCI_STATUS_POSITION;
		mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	    state=StatusParms.dwReturn;
		}
		tip=true;
		if(state<=5000)
		{
             m_back.EnableWindow(false);s=0;m=0;
		}
        else
		{
			m_back.EnableWindow(true);
		    state-=5000;
			s=state/1000%60;
			m=(state/1000-s)/60;
		}
        m_before.EnableWindow(true);
		CString d;
		d.Format(_T("%2d\':%2d\""),m,s);
	    m_current.SetText(d);
		m_time.SetPos((m*60+s)*1000);
		
	}
}
void CMyDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnClose();
}

void CMyDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	if(Iscda==1)
	{
		int ti;
		Onpause();
		KillTimer(1);
		ti=m_time.GetPos();
        s=(ti/1000)%60;
		m=(ti/1000-s)/60;
        CString d;
		d.Format(_T("%2d\':%2d\""),m,s);
	    m_current.SetText(d);
		track=t;
		tip=1;
		//Onplay();
	}
    else
	{
	    int ti;
		Onpause();
		KillTimer(1);
		ti=m_time.GetPos();
        s=(ti/1000)%60;
		m=(ti/1000-s)/60;
        CString d;
		d.Format(_T("%2d\':%2d\""),m,s);
	    m_current.SetText(d);
		tip=1;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CMyDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CVolumeOutMaster vo;
	DWORD vl=m_vol.GetPos();
    vo.SetCurrentVolume((int)vl);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}
void CMyDlg::Ondoor() 
{
	// TODO: Add your control notification handler code here
   
	if(door==1)
	{mciSendString("Set cdAudio door open wait", NULL, 0, NULL);door=0;} 	
    else
	{mciSendString("Set cdAudio door closed wait", NULL, 0, NULL);door=1;} 	
}
void CMyDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(Iscda==1)
	{
	MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;
    mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	m=MCI_TMSF_MINUTE( StatusParms.dwReturn );
    s=MCI_TMSF_SECOND( StatusParms.dwReturn );
    t=MCI_TMSF_TRACK( StatusParms.dwReturn );
	CString d;
	d.Format(_T("%2d\':%2d\""),m,s);
    m_current.SetText(d);
	m_time.SetPos((m*60+s)*1000);
    MCI_STATUS_PARMS Parms;
	Parms.dwItem = MCI_STATUS_LENGTH;
	Parms.dwTrack = (DWORD) t;
    mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &Parms );
    CString di;
	di.Format(_T("%2d\':%2d\""),ml=MCI_MSF_MINUTE( Parms.dwReturn ),sl=MCI_MSF_SECOND( Parms.dwReturn ));
	m_count.SetText(di);

	if(s%2==0)
	{   
		CString a,b;
		a.Format("正在播放CD.   第%d首",t);b.Format(_T("%2d\':%2d\""),ml,sl);
	    m_show.SetText(a);m_count.SetText(b);
	}
	else
    {
		CString c,d;
		c.Format("正在播放CD    第%d首",t);d.Format(_T("%2d\' %2d\""),ml,sl);
	    m_show.SetText(c);m_count.SetText(d);
	}

    m_time.SetRange(0,(ml*60+sl)*1000);
	
	}
	
	else
	{
    MCI_STATUS_PARMS StatusParms;
	StatusParms.dwItem = MCI_STATUS_POSITION;
    mciSendCommand( m_MCIDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusParms );
	state=StatusParms.dwReturn;
    s=state/1000%60;
	m=(state/1000-s)/60;
	CString d;
	d.Format(_T("%2d\':%2d\""),m,s);
	m_current.SetText(d);
    if(s%2==0)
	{
		CString d1;
		d1.Format(_T("%2d\':%2d\""),ml,sl);
		m_count.SetText(d1);
	}
	else
    {
		CString d2;
		d2.Format(_T("%2d\' %2d\""),ml,sl);
	    m_count.SetText(d2);
        m_time.SetPos((m*60+s)*1000);
	}

	CDialog::OnTimer(nIDEvent);

	}
}

UINT CMyDlg::OnNcHitTest(CPoint point)
{
	return HTCAPTION;
}





void CMyDlg::Onabout() 
{
	// TODO: Add your control notification handler code here
     CAboutDlg dlg;
     dlg.DoModal();
}

void CMyDlg::Onmin() 
{
	// TODO: Add your control notification handler code here
	this->ShowWindow(SW_SHOWMINIMIZED);
}
