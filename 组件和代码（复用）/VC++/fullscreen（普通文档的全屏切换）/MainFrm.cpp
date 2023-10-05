// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "FS.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_VIEW_FULL_SCREEN, OnViewFullScreen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_FULL_SCREEN, OnUpdateViewFullScreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bFullScreenMode=false;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	m_wndToolBar.ModifyStyle(0, TBSTYLE_FLAT);
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::FullScreenModeOn()
{
	// available only if there is an active doc
	CMDIChildWnd* pChild=MDIGetActive();
	if(!pChild) return;
	m_bToolBarWasVisible=(m_wndToolBar.IsWindowVisible()!=0);
	m_wndToolBar.ShowWindow(SW_HIDE);
	m_bStatusBarWasVisible=(m_wndStatusBar.IsWindowVisible()!=0);
	m_wndStatusBar.ShowWindow(SW_HIDE);
	// first create the new toolbar
	// this will contain the full-screen off button
	m_pwndFullScreenBar=new CToolBar;
	m_pwndFullScreenBar->Create(this);
	m_pwndFullScreenBar->LoadToolBar(IDR_FULLSCREEN);
	m_pwndFullScreenBar->SetBarStyle(m_pwndFullScreenBar->GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	// to look better:
	m_pwndFullScreenBar->ModifyStyle(0, TBSTYLE_FLAT);
	m_pwndFullScreenBar->EnableDocking(0);
	// place the full-screen off button somewhere:
	CPoint pt(300,200);
	FloatControlBar(m_pwndFullScreenBar,pt);
	
	// now save the old positions of the main and child windows
	GetWindowRect(&m_mainRect);
	// remove the caption of the mainWnd:
	LONG style=::GetWindowLong(m_hWnd,GWL_STYLE);
	style&=~WS_CAPTION;
	::SetWindowLong(m_hWnd,GWL_STYLE,style);
	int screenx=GetSystemMetrics(SM_CXSCREEN);
	int screeny=GetSystemMetrics(SM_CYSCREEN);
	// resize:
	SetWindowPos(NULL,0,0,screenx,screeny,SWP_NOZORDER);
	//SetWindowPos(NULL,-5,-5,80,80,SWP_NOZORDER);
	style=::GetWindowLong(pChild->m_hWnd,GWL_STYLE);
	m_bChildMax=(style & WS_MAXIMIZE)?true:false;
	// note here: m_bMainMax is not needed since m_hWnd only
	// changed its caption...
	///***************
	//Save the Original Menu and set menu to NULL
    ASSERT(m_OrgMenu.GetSafeHmenu()==NULL);
    CMenu* pOldMenu=GetMenu();
    m_OrgMenu.Attach(pOldMenu->Detach());
    SetMenu((CMenu*)NULL);
	//************
	// and maximize the child window
	// it will remove its caption, too.
	 //pChild->
	this->ShowWindow (SW_SHOWMAXIMIZED);
	style=::GetWindowLong(pChild->m_hWnd,GWL_STYLE);
	style&=~WS_CAPTION;
	::SetWindowLong(pChild->m_hWnd,GWL_STYLE,style);
	//pChild->SetWindowPos (NULL,-5,-5,screenx+5,screeny+5,SWP_NOZORDER);
	pChild->ShowWindow(SW_SHOWMAXIMIZED);

	//RecalcLayout();
	m_bFullScreenMode=true;

}

void CMainFrame::FullScreenModeOff()
{
	ASSERT(m_OrgMenu.GetSafeHmenu()!=NULL);
    SetMenu(&m_OrgMenu);
    m_OrgMenu.Detach();

	// You can use SaveBarState() in OnClose(),
	// so remove the newly added toolbar entirely
	// in order SaveBarState() not
	// to save its state. That is why I used dynamic
	// allocation
	delete m_pwndFullScreenBar;
	LONG style=::GetWindowLong(m_hWnd,GWL_STYLE);
	style|=WS_CAPTION;
	::SetWindowLong(m_hWnd,GWL_STYLE,style);
	if(m_bToolBarWasVisible)
		m_wndToolBar.ShowWindow(SW_SHOW);
	if(m_bStatusBarWasVisible)
		m_wndStatusBar.ShowWindow(SW_SHOW);
	MoveWindow(&m_mainRect);
	RecalcLayout();
	CMDIChildWnd* pChild=MDIGetActive();

	style=::GetWindowLong(pChild->m_hWnd,GWL_STYLE);
	style|=WS_CAPTION;
	::SetWindowLong(pChild->m_hWnd,GWL_STYLE,style);
	// pchild can be NULL if the USER closed all the
	// childs during Full Screen Mode:
	if(pChild){
		if(m_bChildMax)
			MDIMaximize(pChild);
		else MDIRestore(pChild);
	}
	m_bFullScreenMode=false;
}

void CMainFrame::OnClose() 
{
	if(m_bFullScreenMode)
		FullScreenModeOff();
	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnViewFullScreen() 
{
	if(m_bFullScreenMode)
		FullScreenModeOff();
	else FullScreenModeOn();
}

void CMainFrame::OnUpdateViewFullScreen(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bFullScreenMode);	
}
