// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VPick.h"

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
	ON_COMMAND(ID_SHOW_EDITVIEW, OnShowEditview)
	ON_UPDATE_COMMAND_UI(ID_SHOW_EDITVIEW, OnUpdateShowEditview)
	ON_COMMAND(ID__SHOW_ARTVIEW, OnShowArtview)
	ON_UPDATE_COMMAND_UI(ID__SHOW_ARTVIEW, OnUpdateShowArtview)
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


void CMainFrame::OnShowEditview() 
{
	// TODO: Add your command handler code here
	//*views runtime class and a unique ID
	CreateActivateView(RUNTIME_CLASS(CEditView),1);
	
}

void CMainFrame::OnUpdateShowEditview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//**active view's class
	pCmdUI->Enable(
		!GetActiveView()->IsKindOf(RUNTIME_CLASS(CEditView)));	
}

void CMainFrame::OnShowArtview() 
{
	// TODO: Add your command handler code here
	//*views runtime class and a unique ID
	CreateActivateView(RUNTIME_CLASS(CArtView),2);
}

void CMainFrame::OnUpdateShowArtview(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//**active view's class
	pCmdUI->Enable(
		!GetActiveView()->IsKindOf(RUNTIME_CLASS(CArtView)));
}

void CMainFrame::CreateActivateView(CRuntimeClass *pNewViewClass, UINT nID)
{
	//**Retrieve a pointer the active view
	CView *pOldView=GetActiveView();
	CView *pNewView=NULL;

	//**Retrieve a pointer to the active document then
	//**iterate the document's views looking for a view
	//**object of the same runtime class that was passed
	//**to the fuction
	CDocument *pDoc=GetActiveDocument();
	POSITION pos=pDoc->GetFirstViewPosition();
	while (pos && pNewView)
	{
		CView *pView=pDoc->GetNextView(pos);
		if (pView->IsKindOf(pNewViewClass))
			pNewView=pView;
	}
	//**check to see if a view object was found
	//**if not construct,create and initialize one
	if (pNewView==NULL)
	{
		//**Initialize a CCreateContext variable with
		//**a pointer to the document
		CCreateContext context;
		context.m_pCurrentDoc=pDoc;

		//**Construct the view object using the runtime
		//**class and create the view window
		pNewView=(CView*) pNewViewClass->CreateObject();
		pNewView->Create(NULL,NULL,0,
			CFrameWnd::rectDefault,
			this,nID,&context);
		pNewView->OnInitialUpdate();
	}
	//**Set the new view as the active view and show it's
	//**window,Hide the window of the old view.
	SetActiveView(pNewView);
	pNewView->ShowWindow(SW_SHOW);
	pOldView->ShowWindow(SW_HIDE);

	//**Swap the two window IDs because the ID of the active
	//**view window must be set to AFX_IDW_PANE_FIRST.
	pOldView->SetDlgCtrlID(pNewView->GetDlgCtrlID());
	pNewView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);

	//**Reposition control bars and size the view window
	RecalcLayout();
}
