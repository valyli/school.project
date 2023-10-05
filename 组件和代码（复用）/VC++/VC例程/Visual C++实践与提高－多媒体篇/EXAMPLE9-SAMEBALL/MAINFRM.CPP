// MainFrm.cpp : implementation of the CMainFrame class
// 编码: Leezy
// 最后修改日期：5.1
//

#include "stdafx.h"
#include "SameBall.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_ACTIVATEAPP()
	ON_COMMAND(ID_HELP, OnHelp)
	ON_WM_SYSCOMMAND()
	ON_COMMAND(IDM_REGENDER, OnRegender)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_COUNT,
	ID_INDICATOR_BALLSCORE,
	ID_INDICATOR_SCORE,
	ID_INDICATOR_REMAIN
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_bMaxSize=false;
	m_bMinSize=false;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(1,ID_INDICATOR_COUNT,NULL,90);
	m_wndStatusBar.SetPaneInfo(2,ID_INDICATOR_BALLSCORE,NULL,90);
	m_wndStatusBar.SetPaneInfo(3,ID_INDICATOR_SCORE,NULL,90);
	m_wndStatusBar.SetPaneInfo(4,ID_INDICATOR_REMAIN,NULL,90);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		// Delete some system menuitems
		pSysMenu->DeleteMenu(2,MF_BYPOSITION);
		// 
	}
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	CRect dRect;
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	if(((CSameBallApp*)AfxGetApp())->m_sWindow==_T("Maximize"))
		dRect=SetWinSize(1);
	else
		dRect=SetWinSize(0);
	cs.x=dRect.left;
	cs.y=dRect.top;
	cs.cx=dRect.right;
	cs.cy=dRect.bottom;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.style &= ~WS_THICKFRAME;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


CRect CMainFrame::SetWinSize(int ni)
{
	int dx,dy;				// dRect.rigth 不是右坐标，而是宽度
	dx=GetSystemMetrics(SM_CXSCREEN);
	dy=GetSystemMetrics(SM_CYSCREEN);
	CRect dRect;
	if(dx>=1024 && ni==1)
	{
		dRect.left=(dx-972)/2;
		dRect.top=(dy-709)/2;
		dRect.right=972;
		dRect.bottom=709;
		m_wndView.m_iObjSize=64;
		m_wndView.m_uBmpID=IDB_BALL64;
		return dRect;
	}
	else if(dx>=1024)
	{
		dRect.left=(dx-732)/2;
		dRect.top=(dy-549)/2;
		dRect.right=732;
		dRect.bottom=549;
		m_wndView.m_iObjSize=48;
		m_wndView.m_uBmpID=IDB_BALL48;
		return dRect;
	}
	if(dx>=800 && ni==1)
	{
		dRect.left=(dx-732)/2;
		dRect.top=(dy-549)/2;
		dRect.right=732;
		dRect.bottom=549;
		m_wndView.m_iObjSize=48;
		m_wndView.m_uBmpID=IDB_BALL48;
		return dRect;
	}
	else	if(dx>=800)
	{
		dRect.left=(dx-492)/2;
		dRect.top=(dy-389)/2;
		dRect.right=492;
		dRect.bottom=389;
		m_wndView.m_iObjSize=32;
		m_wndView.m_uBmpID=IDB_BALL32;
		return dRect;
	}

	if(dx>=640)
	{
		dRect.left=(dx-492)/2;
		dRect.top=(dy-389)/2;
		dRect.right=492;
		dRect.bottom=389;
		m_wndView.m_iObjSize=32;
		m_wndView.m_uBmpID=IDB_BALL32;
		return dRect;
	}
	else
	{
		MessageBox("显示尺寸不合适!","Warning");
		dRect.left=0;
		dRect.top=0;
		dRect.right=0;
		dRect.bottom=0;
		m_wndView.m_iObjSize=32;
		m_wndView.m_uBmpID=IDB_BALL32;
		PostMessage(WM_CLOSE);
		return dRect;
	}

}

void CMainFrame::ShowStatus(UINT nIndex, CString ndS)
{
	m_wndStatusBar.SetPaneText(nIndex,ndS);
}

void CMainFrame::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CFrameWnd::OnActivateApp(bActive, hTask);
	
	m_wndView.m_bIsActive=bActive;
}

void CMainFrame::OnHelp() 
{
	TCHAR bufDir[_MAX_PATH];
	CString dS1,dS2;
	dS1=((CSameBallApp*)AfxGetApp())->m_sAppDir;
	dS1+="\\Sameball.chm";
	GetWindowsDirectory(bufDir,_MAX_PATH);
	dS2.Format("%s\\Hh.exe  %s",bufDir,dS1);
	WinExec(dS2,SW_NORMAL);
}


void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CRect dR;
	if(nID==SC_MAXIMIZE)						// 从小窗口最大化
	{
		m_wndView.m_bIsActive=false;
		m_bMaxSize=true;
		m_wndView.FreeDD();
		ModifyStyle(0,WS_MAXIMIZE,0);
		dR=SetWinSize(1);
		SetWindowPos(NULL,dR.left,dR.top,dR.right,dR.bottom,SWP_NOZORDER|SWP_DRAWFRAME);
		m_wndView.InitDD();
		m_wndView.m_bIsActive=true;
		m_wndView.m_bNeedPaint=true;
		return;
	}
	if(nID==SC_RESTORE)
	{
		m_wndView.m_bIsActive=false;
		m_wndView.FreeDD();
		if(m_bMinSize)						// 从最小化恢复
		{
			ShowWindow(SW_RESTORE);
			m_bMinSize=false;
			if(m_bMaxSize)				// 原来的窗口模式
				dR=SetWinSize(1);
			else
				dR=SetWinSize(0);
		}
		else								// 从最大化恢复成小窗口
		{
			m_bMaxSize=false;
			ModifyStyle(WS_MAXIMIZE,0,0);
			dR=SetWinSize(0);
		}
		SetWindowPos(NULL,dR.left,dR.top,dR.right,dR.bottom,SWP_NOZORDER|SWP_DRAWFRAME);
		m_wndView.InitDD();
		m_wndView.m_bIsActive=true;
		m_wndView.m_bNeedPaint=true;
		return;
	}
	if(nID==SC_MINIMIZE)
		m_bMinSize=true;
	CFrameWnd::OnSysCommand(nID,lParam);
}

BOOL CMainFrame::DestroyWindow() 
{
	CSameBallApp* pApp=(CSameBallApp*)AfxGetApp();
	if(m_bMaxSize && pApp->m_sWindow!=_T("Maximize"))
	{
		pApp->m_sWindow=_T("Maximize");
		pApp->m_bNeedSave=true;
	}
	if(!m_bMaxSize && pApp->m_sWindow!=_T("Minimize"))
	{
		pApp->m_sWindow=_T("Minimize");
		pApp->m_bNeedSave=true;
	}
	
	return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnRegender() 
{	
	if(!m_bNeedSave)
	return false;
	HKEY hkey;
	LONG l=RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Polarlight\\SameBall",0,NULL,REG_OPTION_NON_VOLATILE,
			KEY_CREATE_SUB_KEY|KEY_WRITE|KEY_READ,NULL,&hkey,NULL);
	if (l!=ERROR_SUCCESS)
	{
      RegCloseKey(hkey);
	  return false;
	}
	if(RegSetValueEx(hkey,NULL,0,REG_SZ,(const unsigned char*)LPCTSTR(m_sAppDir),m_sAppDir.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"0",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s0),m_s0.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"1",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s1),m_s1.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"2",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s2),m_s2.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"3",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s3),m_s3.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"4",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s4),m_s4.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"5",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s5),m_s5.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"Window",0,REG_SZ,(const unsigned char*)LPCTSTR(m_sWindow),m_sWindow.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	RegCloseKey(hkey);
    return true;
}
