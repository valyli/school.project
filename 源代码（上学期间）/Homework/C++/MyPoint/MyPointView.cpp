// MyPointView.cpp : implementation of the CMyPointView class
//

#include "stdafx.h"
#include "MyPoint.h"

#include "MyPointDoc.h"
#include "MyPointView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPointView

IMPLEMENT_DYNCREATE(CMyPointView, CView)

BEGIN_MESSAGE_MAP(CMyPointView, CView)
	//{{AFX_MSG_MAP(CMyPointView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPointView construction/destruction

CMyPointView::CMyPointView()
{
	// TODO: add construction code here

}

CMyPointView::~CMyPointView()
{
}

BOOL CMyPointView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyPointView drawing

void CMyPointView::OnDraw(CDC* pDC)
{
	CMyPointDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	int index;
	index = pDoc->m_index;
	for(int i = 1; i<= index; i++)
		pDC->Ellipse(pDoc->points[i].x-2, pDoc->points[i].y-2, pDoc->points[i].x+2, pDoc->points[i].y+2);

}

/////////////////////////////////////////////////////////////////////////////
// CMyPointView diagnostics

#ifdef _DEBUG
void CMyPointView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPointView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPointDoc* CMyPointView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPointDoc)));
	return (CMyPointDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPointView message handlers

void CMyPointView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMyPointDoc *pDoc = GetDocument();
	if(pDoc->m_index == 100)
		return;
	pDoc->m_index++;
	pDoc->points[pDoc->m_index] = point;
	pDoc->SetModifiedFlag();
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}
