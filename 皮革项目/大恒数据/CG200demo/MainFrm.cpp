// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "DHCGBoardDemo.h"

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
	ON_WM_CLOSE()
	ON_WM_MOVE()
	ON_WM_INITMENU()
	ON_WM_NCACTIVATE()
	ON_WM_SIZE()
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
	m_bPrePrint=false;
	//	m_bFreeze=true;
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
	//	m_bPreView=false;
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
//	if( !CFrameWnd::PreCreateWindow(cs) )
//		return FALSE;
	
	//	m_pView=GetView();
	//	SetTimer(1,1000,NULL);
	return CFrameWnd::PreCreateWindow(cs);
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
//���˳�����ʱ���ж�ͼ���Ƿ���
//�ر�ͼ��Ļ״̬���������ò���
void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
	;//GetActiveView(
	if(!pView->m_bFreeze)
	{
		pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
	}
	pView->cgBoard.SetInputVideoRect(pView->InputVideoRect);
	pView->cgBoard.CloseCgBoard();
	CFrameWnd::OnClose();

}
//������ƶ�ʱ����VIEW�����ƶ���Ϣ��
//����ͼ�������������
void CMainFrame::OnMove(int x, int y) 
{
	//	x=x-x%4;
	//	y=y-y%2;
	CFrameWnd::OnMove(x, y);
	if(!m_bPrePrint)//2000 2 5������Ϣ �л�ͼ��
	{
		CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
		
		if(pView!=NULL&&pView->m_bInitCGboard)
			//	pView->OnMove(x,y);
			pView->OnChangeViewSize();	
	}
}
//���ڵ���ʱ�����ͼ��
//����VIEW����ֹͣ��Ϣ
void CMainFrame::OnInitMenu(CMenu* pMenu) 
{
	CFrameWnd::OnInitMenu(pMenu);
	if(!m_bPrePrint)
	{
		CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
		if(pView!=NULL&&!pView->m_bFreeze)
			pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
	}
}


BOOL CMainFrame::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	if(!m_bPrePrint)
	{
		CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
		if(pView!=NULL&&!pView->m_bFreeze)
			pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
	}
	return CFrameWnd::OnCommand(wParam, lParam);
}
BOOL CMainFrame::OnNcActivate(BOOL bActive) 
{
	if(!m_bPrePrint)//2000 2 5������Ϣ �л�ͼ��
	{
		// TODO: Add your message handler code here and/or call default
		CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
		if(pView!=NULL&&!pView->m_bFreeze)
		{
			pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
			//	pView->GetDocument()->UpdateAllViews(NULL);	
		}
	}
	return CFrameWnd::OnNcActivate(bActive);
}

CDHCGBoardDemoView* CMainFrame::GetView()
{
	CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
	if(pView->IsKindOf(RUNTIME_CLASS(CDHCGBoardDemoView)))
		return pView;
	else 
		return NULL;
}



void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	//	cx=cx-cx%4;
	//	cy=cy-cy%2;
	CFrameWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}
