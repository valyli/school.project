// Example5CView.cpp : implementation of the CExample5CView class
//

#include "stdafx.h"
#include "Example5C.h"

#include "Example5CDoc.h"
#include "Example5CView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5CView

IMPLEMENT_DYNCREATE(CExample5CView, CView)

BEGIN_MESSAGE_MAP(CExample5CView, CView)
	//{{AFX_MSG_MAP(CExample5CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5CView construction/destruction

CExample5CView::CExample5CView()
{
	// TODO: add construction code here

}

CExample5CView::~CExample5CView()
{
}

BOOL CExample5CView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample5CView drawing

void CExample5CView::OnDraw(CDC* pDC)
{
	CExample5CDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	pDC->SelectStockObject(GRAY_BRUSH);
	CRect clientRect;
	GetClientRect(&clientRect);
	rcRect.left=int(clientRect.right/3);
	rcRect.top=int(clientRect.bottom/3);
	rcRect.right=int(2*clientRect.right/3);
	rcRect.bottom=int(2*clientRect.bottom/3);
	pDC->Rectangle(&rcRect);

}

/////////////////////////////////////////////////////////////////////////////
// CExample5CView printing

BOOL CExample5CView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample5CView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample5CView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample5CView diagnostics

#ifdef _DEBUG
void CExample5CView::AssertValid() const
{
	CView::AssertValid();
}

void CExample5CView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample5CDoc* CExample5CView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample5CDoc)));
	return (CExample5CDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5CView message handlers

void CExample5CView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bCaptured=true;		
	CView::OnLButtonDown(nFlags, point);
}

void CExample5CView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bCaptured)
	{
	if(rcRect.PtInRect(point))
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_WAIT));
	else if(point.y>rcRect.top&&point.y<rcRect.bottom&&point.x<rcRect.left)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORLEFT));
	else if(point.y>rcRect.top&&point.y<rcRect.bottom&&point.x>rcRect.right)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORRIGHT));
	else if(point.x>rcRect.left&&point.x<rcRect.right&&point.y<rcRect.top)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORUP));
	else if(point.x>rcRect.left&&point.x<rcRect.right&&point.y>rcRect.top)
		::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSORDOWN));
	else
		::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
	}
	CView::OnMouseMove(nFlags, point);
}

void CExample5CView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_bCaptured=false;	
	CView::OnRButtonDown(nFlags, point);
}
