// DrawLineView.cpp : implementation of the CDrawLineView class
//

#include "stdafx.h"
#include "DrawLine.h"

#include "DrawLineDoc.h"
#include "DrawLineView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView

IMPLEMENT_DYNCREATE(CDrawLineView, CView)

BEGIN_MESSAGE_MAP(CDrawLineView, CView)
	//{{AFX_MSG_MAP(CDrawLineView)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView construction/destruction

CDrawLineView::CDrawLineView()
{
	// TODO: add construction code here
	m_Drag = 0;
	m_HCursor = AfxGetApp()->LoadStandardCursor(IDC_CROSS);

}

CDrawLineView::~CDrawLineView()
{
}

BOOL CDrawLineView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,0,(HBRUSH)::GetStockObject(WHITE_BRUSH),0);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView drawing

void CDrawLineView::OnDraw(CDC* pDC)
{
	CDrawLineDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView printing

BOOL CDrawLineView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDrawLineView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDrawLineView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView diagnostics

#ifdef _DEBUG
void CDrawLineView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawLineView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawLineDoc* CDrawLineView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawLineDoc)));
	return (CDrawLineDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDrawLineView message handlers

void CDrawLineView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pPrev = point;
	m_pOrigin = point;
	SetCapture();
	m_Drag = 1;
	RECT rect;
	GetClientRect(&rect);
	ClientToScreen(&rect);
	ClipCursor(&rect);
	CView::OnLButtonDown(nFlags, point);
}

void CDrawLineView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	SetCursor(m_HCursor);
	if(m_Drag)
	{
		dc.SetROP2(R2_NOT);
		dc.MoveTo(m_pOrigin);
		dc.LineTo(m_pPrev);
		dc.MoveTo(m_pOrigin);
		dc.LineTo(point);
		m_pPrev = point;
	}
	CView::OnMouseMove(nFlags, point);
}

void CDrawLineView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_Drag)
	{
		m_Drag = 0;
		ReleaseCapture();
		ClipCursor(NULL);
	}
	CView::OnLButtonUp(nFlags, point);
}
