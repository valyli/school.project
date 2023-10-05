// Example5AView.cpp : implementation of the CExample5AView class
//

#include "stdafx.h"
#include "Example5A.h"

#include "Example5ADoc.h"
#include "Example5AView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5AView

IMPLEMENT_DYNCREATE(CExample5AView, CView)

BEGIN_MESSAGE_MAP(CExample5AView, CView)
	//{{AFX_MSG_MAP(CExample5AView)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5AView construction/destruction

CExample5AView::CExample5AView()
{
	// TODO: add construction code here
	m_index=0;
}

CExample5AView::~CExample5AView()
{
}

BOOL CExample5AView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample5AView drawing

void CExample5AView::OnDraw(CDC* pDC)
{
	CExample5ADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExample5AView printing

BOOL CExample5AView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample5AView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample5AView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample5AView diagnostics

#ifdef _DEBUG
void CExample5AView::AssertValid() const
{
	CView::AssertValid();
}

void CExample5AView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample5ADoc* CExample5AView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample5ADoc)));
	return (CExample5ADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5AView message handlers

void CExample5AView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if(m_index!=0)
	{
		CDC* pMemDC=new CDC;
		pMemDC->CreateCompatibleDC(&dc);
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1+m_index-1);

		pMemDC->SelectObject(&bitmap);
		CRect rect;
		this->GetClientRect(&rect);
		dc.BitBlt(0,0,rect.right,rect.bottom,pMemDC,0,0,SRCCOPY);
	}	
	// Do not call CView::OnPaint() for painting messages
}

void CExample5AView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_index++;
	if(m_index>4)
		m_index=1;
	this->Invalidate();
	
	CView::OnTimer(nIDEvent);
}

void CExample5AView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	this->SetTimer(1,500,NULL);	
	CView::OnLButtonDown(nFlags, point);
}

void CExample5AView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	this->Invalidate();	
	CView::OnRButtonDown(nFlags, point);
}

BOOL CExample5AView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_index!=0)
		return true;	
	return CView::OnEraseBkgnd(pDC);
}

void CExample5AView::OnDestroy() 
{
	CView::OnDestroy();
	KillTimer(1);	
	// TODO: Add your message handler code here
	
}
