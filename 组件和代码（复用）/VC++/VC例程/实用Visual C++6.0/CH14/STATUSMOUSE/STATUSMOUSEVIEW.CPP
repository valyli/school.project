// StatusMouseView.cpp : implementation of the CStatusMouseView class
//

#include "stdafx.h"
#include "StatusMouse.h"

#include "StatusMouseDoc.h"
#include "StatusMouseView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseView

IMPLEMENT_DYNCREATE(CStatusMouseView, CView)

BEGIN_MESSAGE_MAP(CStatusMouseView, CView)
	//{{AFX_MSG_MAP(CStatusMouseView)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseView construction/destruction

CStatusMouseView::CStatusMouseView()
{
	// TODO: add construction code here

}

CStatusMouseView::~CStatusMouseView()
{
}

BOOL CStatusMouseView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseView drawing

void CStatusMouseView::OnDraw(CDC* pDC)
{
	CStatusMouseDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseView printing

BOOL CStatusMouseView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CStatusMouseView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CStatusMouseView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseView diagnostics

#ifdef _DEBUG
void CStatusMouseView::AssertValid() const
{
	CView::AssertValid();
}

void CStatusMouseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CStatusMouseDoc* CStatusMouseView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStatusMouseDoc)));
	return (CStatusMouseDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStatusMouseView message handlers

#include "MainFrm.h"
void CStatusMouseView::OnMouseMove(UINT nFlags, 
								   CPoint point) 
{
	// ** Setup a mouse position string 
	CString strMousePosition;
	strMousePosition.Format("(%d,%d)",
							point.x,point.y);

	// ** Get the SDI application frame window
	CMainFrame* pMainFrame=
					(CMainFrame *) GetParentFrame();

	// ** Set the indicator pane text
	pMainFrame->SetMousePosText(strMousePosition);

	CView::OnMouseMove(nFlags, point);
}
