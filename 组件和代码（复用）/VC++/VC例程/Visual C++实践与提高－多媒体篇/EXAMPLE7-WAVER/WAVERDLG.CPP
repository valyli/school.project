// waverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "waver.h"
#include "waverDlg.h"
#include "waveaudio.h"
#include "displaydlg.h"

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
// CWaverDlg dialog

CWaverDlg::CWaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaverDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaverDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaverDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaverDlg, CDialog)
	//{{AFX_MSG_MAP(CWaverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_RECORD, OnRecord)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaverDlg message handlers

BOOL CWaverDlg::OnInitDialog()
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
	SetTimer(1,1000,NULL);
	CWnd *m_pWnd;
	m_pWnd=GetDlgItem(IDC_SAVE);
	m_pWnd->EnableWindow(FALSE);
	m_pWnd=GetDlgItem(IDC_PLAY);
	m_pWnd->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWaverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWaverDlg::OnPaint() 
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
		if(m_Wave.m_Open)
		{
//		    CWnd *m_pWnd;
    //	    CRect rect;
	        //m_pWnd=GetDlgItem(IDC_WAVE_GRAPH);
	        //m_pWnd->GetClientRect(rect);
	        //m_dlgw=rect.Width();
	        //m_dlgh=rect.Height();
	        //CClientDC dc(m_pWnd); // device context for painting
	        //DrawWave(dc.m_hDC,rect.left,rect.top,(char *)m_Wave.m_Path.operator LPCTSTR());
		}
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWaverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//;;;
void CWaverDlg::OnPlay() 
{
	if(m_Wave.Play ())
		AfxMessageBox("播放出错");
	m_Wave.m_Playing = 1;
	CString str;
	str.Format("正在播放.....");
	SetDlgItemText(IDC_STATUS,str);
}
void CWaverDlg::OnOpen() 
{
	CString Filter;
	CString str;
	char buf[128];
	DWORD Dflag;
	Filter = "波形音频文件(*.WAV)|*.WAV||";

	CFileDialog FileDlg (TRUE, NULL, NULL, OFN_HIDEREADONLY, Filter);
	if (FileDlg.DoModal () == IDOK)
	{
		m_Wave.m_Path = FileDlg.GetPathName ();
		Dflag = m_Wave.Open();
		if (Dflag)
		{
			mciGetErrorString(Dflag,buf,strlen(buf));
			AfxMessageBox (buf);
		}
		str.Format("文件已经正确打开");
		SetDlgItemText(IDC_STATUS,str);
		CWnd *m_pWnd;
	    m_pWnd=GetDlgItem(IDC_PLAY);
	    m_pWnd->EnableWindow(TRUE);
	}
}

void CWaverDlg::OnRecord() 
{
	CWnd *m_pWnd;
	m_pWnd=GetDlgItem(IDC_PLAY);
	m_pWnd->EnableWindow(FALSE);
	m_pWnd=GetDlgItem(IDC_OPEN);
	m_pWnd->EnableWindow(FALSE);
	m_pWnd=GetDlgItem(IDC_SAVE);
	m_pWnd->EnableWindow(FALSE);
	CString str;
	str.Format("正在录音.....");
	SetDlgItemText(IDC_STATUS,str);
	m_Wave.Record();
	
}

void CWaverDlg::OnSave() 
{
	CString Filter;
	char buf[128];
	DWORD Dflag;
	Filter = "Wave Files (*.WAV)|*.WAV||";

	CFileDialog FileDlg (FALSE, NULL, NULL, OFN_OVERWRITEPROMPT, Filter);
	FileDlg.m_ofn.lpstrDefExt="wav";
	if(FileDlg.DoModal()==IDOK){
		Dflag = m_Wave.Save(FileDlg.GetPathName());
		if (Dflag)
		{
			mciGetErrorString(Dflag,buf,strlen(buf));
			AfxMessageBox (buf);
			return ;
		}
	}
	CString str;
	str.Format("保存结束.....");
	SetDlgItemText(IDC_STATUS,str);
}
void CWaverDlg::OnStop() 
{
	CWnd *m_pWnd;
	m_pWnd=GetDlgItem(IDC_PLAY);
	m_pWnd->EnableWindow(TRUE);
	m_pWnd=GetDlgItem(IDC_OPEN);
	m_pWnd->EnableWindow(TRUE);
	m_pWnd=GetDlgItem(IDC_SAVE);
	m_pWnd->EnableWindow(TRUE);

	CString str;
	if(m_Wave.m_Record)
	str.Format("录音停止.....");
	if(m_Wave.m_Playing)
	str.Format("播放停止.....");
	SetDlgItemText(IDC_STATUS,str);
	m_Wave.Stop();	
}
void CWaverDlg::DrawWave(HDC hdc,unsigned int x,unsigned int y,char *path)
{
	HMMIO h;
	MMCKINFO mmParent,mmSub;
	GLOBALHANDLE gh;
	PCMWAVEFORMAT waveformat;
	char *p;
	unsigned long nextsample;
	long afactor;
	unsigned int i,n,amp;
	int *ip;
    HPEN OldPen=(HPEN)SelectObject(hdc,GetStockObject(BLACK_PEN));
	HBRUSH OldBrush=(HBRUSH)SelectObject(hdc,GetStockObject(WHITE_BRUSH));
	Rectangle(hdc,x,y,x+m_dlgw,y+m_dlgh);

	if((h=mmioOpen(path,NULL,MMIO_READ))==NULL)
		return;

	mmParent.fccType=mmioFOURCC('W','A','V','E');
	if(mmioDescend(h,(LPMMCKINFO)&mmParent,NULL,MMIO_FINDRIFF))
	{
		mmioClose(h,0);
		return;
	}

	mmSub.ckid=mmioFOURCC('f','m','t',' ');
	if(mmioDescend(h,(LPMMCKINFO)&mmSub,(LPMMCKINFO)&mmParent,MMIO_FINDCHUNK))
	{
		mmioClose(h,0);
		return;
	}

	n=min((unsigned int)mmSub.cksize,sizeof(PCMWAVEFORMAT));
	if(mmioRead(h,(LPSTR)&waveformat,n)!=n)
	{
		mmioClose(h,0);
		return;
	}
	if(waveformat.wf.wFormatTag!=WAVE_FORMAT_PCM)
	{
		mmioClose(h,0);
		return;
	}

	mmioAscend(h,&mmSub,0);

	mmSub.ckid=mmioFOURCC('d','a','t','a');
	if(mmioDescend(h,(LPMMCKINFO)&mmSub,(LPMMCKINFO)&mmParent,MMIO_FINDCHUNK))
	{
		mmioClose(h,0);
		return;
	}

	if(waveformat.wBitsPerSample==8 && waveformat.wf.nChannels==1)
	{
		nextsample=mmSub.cksize/(long)m_dlgw;
		afactor=2L*(255L/(long)m_dlgh);
	}
	else if(waveformat.wBitsPerSample==8 && waveformat.wf.nChannels==1)
	{
		nextsample=2L*((mmSub.cksize/2L)/(long)m_dlgw);
		afactor=2L*(255L/(long)m_dlgh);
	}
	else if(waveformat.wBitsPerSample>8 && waveformat.wf.nChannels==1)
	{
		nextsample=2L*((mmSub.cksize/(long)m_dlgw))& 0xfffffffeL;
		afactor=2L*(65535L/(long)m_dlgh);
	}
	else
	{
		nextsample=4L*((mmSub.cksize/4L)/(long)m_dlgw)&0xfffffffeL;
		afactor=2L*(65535L/(long)m_dlgh);
	}

	MoveToEx(hdc,x,y+m_dlgh/2,NULL);
	LineTo(hdc,x+m_dlgw,y+m_dlgh/2);
	if((gh=GlobalAlloc(GMEM_MOVEABLE,mmSub.cksize))!=NULL)
	{
		if((p=(char*)GlobalLock(gh))!=NULL)
		{
			if(mmioRead(h,p,mmSub.cksize)==mmSub.cksize)
			{
				for(i=0;i<m_dlgw;)
				{
					ip=(int *)p;
					if(waveformat.wBitsPerSample==8&&waveformat.wf.nChannels==1)
						amp=(unsigned int)max(labs(((long)p[0]-128L)/afactor),1L);
					else if(waveformat.wBitsPerSample==8&&waveformat.wf.nChannels==2)
						amp=(unsigned int)max(labs(((long)p[0]-128L+(long)p[1]-128L)/2)/afactor,1L);
					else if(waveformat.wBitsPerSample>8&&waveformat.wf.nChannels==1)
						amp=(unsigned int)max(labs((long)ip[0]/afactor),1L);
					else
						amp=(unsigned int)max(labs((((long)ip[0]+(long)ip[1])/2)/afactor),1L);

					if(amp>m_dlgh/2)
						amp=m_dlgh/2-3;

					MoveToEx(hdc,x+i,y+(m_dlgh/2)-amp,NULL);
					LineTo(hdc,x+i,y+(m_dlgh/2)+amp);
					i+=2;
					p+=nextsample;
				}
			}
			GlobalUnlock(gh);
		}
		GlobalFree(gh);
	}

    SelectObject(hdc,OldPen);
	(HBRUSH)SelectObject(hdc,OldBrush);

	mmioClose(h,0);
	return;
}

void CWaverDlg::OnInfo() 
{
	displaydlg dlg;
	CString str;
	CString path = m_Wave.m_Path;
	dlg.m_name = path;
	str.Format("%5.3f",m_Wave.GetSampleRate()/1000.);
	str+=_T(" kHZ");
	dlg.m_sam = str;
	str.Empty();
	switch(m_Wave.GetChannel())
	{
	case 1:
		str="单声道";
		break;
	case 2:
		str="立体声";
	}
	dlg.m_chan = str;
	str.Empty();
	str.Format("%d",m_Wave.GetBitLong());
	str+="位";
	dlg.m_bit = str;
	str.Empty();
	str.Format("%2.2u:%02.2f:%02.2u",m_Wave.GetWaveLength()/1000/60,m_Wave.GetWaveLength()/1000.,
		m_Wave.GetWaveLength()/1000/3600);
	dlg.m_long = str;
	dlg.DoModal();
}

void CWaverDlg::OnTimer(UINT nIDEvent) 
{	
	CDialog::OnTimer(nIDEvent);
}
