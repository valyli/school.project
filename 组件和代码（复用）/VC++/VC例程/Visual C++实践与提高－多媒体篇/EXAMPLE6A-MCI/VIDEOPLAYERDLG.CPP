// VideoPlayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VideoPlayer.h"
#include "VideoPlayerDlg.h"
#include "infodlg.h"
#include "Digitalvideo.h"

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
// CVideoPlayerDlg dialog

CVideoPlayerDlg::CVideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Open = FALSE;
	m_Loop = FALSE;
	m_FullScreen = FALSE;
	m_Sound = TRUE;
	m_flag = 0;
	m_str = "";
}

void CVideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoPlayerDlg)
	DDX_Control(pDX, IDC_SCROLLBAR, m_displaybar);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVideoPlayerDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoPlayerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_INFORMATION, OnInformation)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_WM_TIMER()
	ON_COMMAND(IDC_LOOP, OnLoop)
	ON_COMMAND(IDC_FULLSCREEN, OnFullscreen)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoPlayerDlg message handlers

BOOL CVideoPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
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
	//初始化滚动条
	m_displaybar.SetScrollRange(1,100);
	m_displaybar.SetScrollPos(1);
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	// TODO: Add extra initialization here
	//创建用于显示动画的对话框窗口,但是还不用显示
   	Display = new CDialog;
    Display->Create(IDD_DISPLAY);
	SetTimer(1,100,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVideoPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CVideoPlayerDlg::OnPaint() 
{
	if (IsIconic())//最小化
	{
		CPaintDC dc(this); // device context for painting
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		// Center icon in client rectangle
		int xIcon = GetSystemMetrics(SM_CXICON);
		int yIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - xIcon + 1) / 2;
		int y = (rect.Height() - yIcon + 1) / 2;
	}
	else
	{
		CDialog::OnPaint();
	}
}
HCURSOR CVideoPlayerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CVideoPlayerDlg::OnOpen() 
{
	// TODO: Add your control notification handler code here
	if(m_Open)
	{
		AfxMessageBox("请在打开视频文件前先关闭原来的文件");
		m_Video.Pause();
		return;
	}
	CString Filter,str;
	Filter = "视频文件 (*.AVI)|*.AVI||";
	//得到窗口尺寸
	CRect rect,itemrect;
	this->GetWindowRect(rect);
	CFileDialog FileDlg (TRUE, NULL, NULL, OFN_HIDEREADONLY, Filter);
	if (FileDlg.DoModal () == IDOK)//单击文件选择对话框的"确定"按钮
	{
	    CWnd *m_wnd=GetDlgItem(IDC_DISPLAYBOX);
		m_wnd->GetWindowRect(itemrect);
	    if (!m_Video.Open(FileDlg.GetPathName(),m_wnd,0,0,
			itemrect.Width(),itemrect.Height()))//打开视频文件
		{
	         MessageBox ("无法打开该文件!", "Error", MB_OK | MB_ICONSTOP);
	         return;
		}		
		m_str = FileDlg.GetFileName();
		m_Video.SetSpeed(1020);
	    m_Open=TRUE;
	}
}
void CVideoPlayerDlg::OnStop() 
{
	m_Video.Stop();
}
void CVideoPlayerDlg::OnPause() 
{
	m_Video.Pause();
}
void CVideoPlayerDlg::OnPlay() 
{
	m_Video.Play(m_Loop,m_FullScreen);
}

void CVideoPlayerDlg::OnNext() 
{
	m_Video.Forward(1);
	m_displaybar.SetScrollPos(m_Video.GetFrame()*100/m_Video.GetFrames());
}

void CVideoPlayerDlg::OnPrev() 
{
	m_Video.Backward(1);
	m_displaybar.SetScrollPos(m_Video.GetFrame()*100/m_Video.GetFrames());
}
void CVideoPlayerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd *m_Wnd=GetDlgItem(IDC_PLAY);
	m_Wnd->EnableWindow(m_Open);//如果m_Open为真
	m_Wnd=GetDlgItem(IDC_PAUSE);
	m_Wnd->EnableWindow(m_Open);
	m_Wnd=GetDlgItem(IDC_STOP);
	m_Wnd->EnableWindow(m_Open);
	m_Wnd=GetDlgItem(IDC_NEXT);
	m_Wnd->EnableWindow(m_Open);
	m_Wnd=GetDlgItem(IDC_LAST);
	m_Wnd->EnableWindow(m_Open);
	if(m_Open)
	{
		CString Info;
		Info.Format("当前播放第 -- %d -- 帧",m_Video.GetFrame());
		if(!m_Video.GetPause()){
			int frame;
			frame = (m_Video.GetFrame()*100)/m_Video.GetFrames();
		    m_displaybar.SetScrollPos(frame);
		}
		m_Wnd = GetDlgItem(IDC_DISPLAY);
		CClientDC dc(m_Wnd);
		//
		CRect rect;
		CBrush brush(RGB(255,255,255)),*OldBrush;
		OldBrush=(CBrush *)dc.SelectObject(brush);

		m_Wnd->GetClientRect(rect);
		dc.SetTextColor(RGB(255,0,0));
		dc.SetBkColor(RGB(255,255,255));
		dc.FillRect(rect,&brush);
		CSize size=dc.GetTextExtent(Info);
		dc.TextOut((rect.Width()-size.cx)/2,(rect.Height()-size.cy)/2,Info);
		dc.SelectObject(&OldBrush);
	 }
	CDialog::OnTimer(nIDEvent);
}
void CVideoPlayerDlg::OnLoop() 
{
	// TODO: Add your command handler code here
	m_Loop=!m_Loop;
}
void CVideoPlayerDlg::OnSound() 
{
	// TODO: Add your command handler code here
	m_Sound=!m_Sound;
}
void CVideoPlayerDlg::OnFullscreen() 
{
	// TODO: Add your command handler code here
	m_FullScreen=!m_FullScreen;
}
void CVideoPlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScroll) 
{
	int frame;
	switch(nSBCode)
	{
	case SB_THUMBPOSITION://拖动滑动块
			pScroll->SetScrollPos(nPos);
			if(m_Open){
		    	m_Video.Pause();
				frame = (nPos*m_Video.GetFrames())/100;
				m_Video.SeekTo(frame);
			pScroll->SetScrollPos(nPos);
			}
			break;
	case SB_LINELEFT:
			frame = 100/m_Video.GetFrames();
			if(frame<=1)frame =1;
			pScroll->SetScrollPos(pScroll->GetScrollPos()-frame);
			if(m_Open){
		    	m_Video.Pause();
				frame = (pScroll->GetScrollPos()*m_Video.GetFrames())/100;
				m_Video.SeekTo(frame);
			}
			break;
	case SB_LINERIGHT:
			frame = 100/m_Video.GetFrames();
			if(frame<=1)frame =1;
			pScroll->SetScrollPos(pScroll->GetScrollPos()+frame);
			if(m_Open){
		    	m_Video.Pause();
				frame = (pScroll->GetScrollPos()*m_Video.GetFrames())/100;
				m_Video.SeekTo(frame);
				m_Video.Play();
			}
			break;
	case SB_THUMBTRACK:
		{
			pScroll->SetScrollPos(nPos);
			m_Video.Pause();
			break;
		}
	case SB_PAGELEFT:
		{
			int pos = pScroll->GetScrollPos();
			frame = 5*100/m_Video.GetFrames();
			if(frame<=1)frame =1;
			pScroll->SetScrollPos(pScroll->GetScrollPos()-frame);
			if(m_Open){
		    	m_Video.Pause();
				frame = (pScroll->GetScrollPos()*m_Video.GetFrames())/100;
				m_Video.SeekTo(frame);
			}
			break;
		}
	case SB_PAGERIGHT:
		{
			int pos = pScroll->GetScrollPos();
			frame = 5*100/m_Video.GetFrames();
			if(frame<=1)frame =1;
			pScroll->SetScrollPos(pScroll->GetScrollPos()+frame);
			if(m_Open){
		    	m_Video.Pause();
				frame = (pScroll->GetScrollPos()*m_Video.GetFrames())/100;
				m_Video.SeekTo(frame);
			}
			break;
		}
	default :
		break;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScroll);
}
void CVideoPlayerDlg::OnInformation() 
{
	if(!m_Open){
		AfxMessageBox("当前没有视频文件");
		return ;
	}
	Cinfodlg dlg;
	CString str;
	str.Format("%d 帧/分",m_Video.GetSpeed());
	dlg.m_strspeed = str;
	str.Format("%d 帧",m_Video.GetFrames());
	dlg.m_strframe = str;
	str.Format("宽 %d 高 %d",m_Video.GetWidth(),m_Video.GetHeight());
	dlg.m_strrect  = str;
	//SetDlgItemText(IDC_FRAMES,str);
	SetDlgItemText(IDC_PLAY_SOUND,str);
	dlg.m_strname  = m_str;
	dlg.DoModal();
}
void CVideoPlayerDlg::OnClose() 
{
		m_Video.Close();
		m_Open = 0;
}
