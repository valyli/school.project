// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Example5D.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
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
	// TODO: add member initialization code here
	m_statusPt.x =1;
	m_statusPt.y =1;
	m_statusIndex=0;
	m_statusImageNumber=0;	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

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

	CreateStatusImageList();
	SetTimer(1,50,NULL);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
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
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

//用于创建图像列表的函数
void CMainFrame::CreateStatusImageList()
{
	//把要播放的图标资源加入图像列表。
	m_statusImageList.Create (16,16,ILC_COLOR,11,2);
	HICON hIcon;
	for(int i=0;i<=8;i++)
	{
		hIcon = ::LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_STATUSICON1+i));
		m_statusImageList.Add(hIcon);
		m_statusImageNumber++;
	}
}

void CMainFrame::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_statusIndex>m_statusImageNumber)
		m_statusIndex=0;
	
	//动画图标	
	SetIcon(m_statusImageList.ExtractIcon(m_statusIndex),FALSE);
	
	//工具栏动画
	CRect rect;
	CDC *pDC1=GetDC();
	ASSERT(pDC1!=NULL);
	//获得显示有效区域
	this->GetClientRect(&rect);
	//将显示位置定在最右边
	m_statusPt.x =rect.right-15; 
	m_statusPt.y=rect.top+5;
	m_statusImageList.Draw(pDC1,m_statusIndex,m_statusPt,ILD_TRANSPARENT);
	ReleaseDC(pDC1);
	
	//状态栏动画
	CDC *pDC=this->m_wndStatusBar.GetDC();
	ASSERT(pDC!=NULL);
	m_statusPt.x =40;
	m_statusPt.y =1;
	m_statusImageList.Draw(pDC,m_statusIndex,m_statusPt,ILD_TRANSPARENT);
	ReleaseDC(pDC);
	
	m_statusIndex++;

	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnDestroy() 
{
	CFrameWnd::OnDestroy();
	KillTimer(1);
	// TODO: Add your message handler code here
	
}
