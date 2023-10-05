// PersistView.cpp : implementation of the CPersistView class
//

#include "stdafx.h"
#include "Persist.h"

#include "PersistDoc.h"
#include "PersistView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersistView

IMPLEMENT_DYNCREATE(CPersistView, CView)

BEGIN_MESSAGE_MAP(CPersistView, CView)
	//{{AFX_MSG_MAP(CPersistView)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersistView construction/destruction
#include "blob.h"
CPersistView::CPersistView()
{
	// TODO: add construction code here

}

CPersistView::~CPersistView()
{
}

BOOL CPersistView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPersistView drawing

void CPersistView::OnDraw(CDC* pDC)
{
	CPersistDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	for (int i=0;i<pDoc->m_BlobArray.GetSize();i++)
	{
		CBlob *pBlob=(CBlob *) pDoc->m_BlobArray.GetAt(i);
		pBlob->Draw(pDC);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPersistView printing

BOOL CPersistView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPersistView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPersistView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPersistView diagnostics

#ifdef _DEBUG
void CPersistView::AssertValid() const
{
	CView::AssertValid();
}

void CPersistView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPersistDoc* CPersistView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPersistDoc)));
	return (CPersistDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersistView message handlers

void CPersistView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	GetDocument()->m_BlobArray.Add(new CBlob(point));
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}
