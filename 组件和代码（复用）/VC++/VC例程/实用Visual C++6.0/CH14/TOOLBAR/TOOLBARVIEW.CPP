// ToolbarView.cpp : implementation of the CToolbarView class
//

#include "stdafx.h"
#include "Toolbar.h"

#include "ToolbarDoc.h"
#include "ToolbarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolbarView

IMPLEMENT_DYNCREATE(CToolbarView, CView)

BEGIN_MESSAGE_MAP(CToolbarView, CView)
	//{{AFX_MSG_MAP(CToolbarView)
	ON_COMMAND(ID_CREATURE, OnCreature)
	ON_UPDATE_COMMAND_UI(ID_CREATURE, OnUpdateCreature)
	ON_COMMAND(ID_BUTTON32773, OnButton32773)
	//}}AFX_MSG_MAP
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolbarView construction/destruction

CToolbarView::CToolbarView()
{
	// TODO: add construction code here

}

CToolbarView::~CToolbarView()
{
}

BOOL CToolbarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarView drawing

void CToolbarView::OnDraw(CDC* pDC)
{
	CToolbarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CToolbarView printing


///////////////////
// CToolbarView diagnostics

#ifdef _DEBUG
void CToolbarView::AssertValid() const
{
	CView::AssertValid();
}

void CToolbarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CToolbarDoc* CToolbarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolbarDoc)));
	return (CToolbarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CToolbarView message handlers

void CToolbarView::OnCreature() 
{
     AfxMessageBox("Creature");	
}

void CToolbarView::OnUpdateCreature(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_bEnableCreature);
}

void CToolbarView::OnButton32773() 
{
	// TODO: Add your command handler code here
	
}
