// Example5BView.cpp : implementation of the CExample5BView class
//

#include "stdafx.h"
#include "Example5B.h"

#include "Example5BDoc.h"
#include "Example5BView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5BView

IMPLEMENT_DYNCREATE(CExample5BView, CView)

BEGIN_MESSAGE_MAP(CExample5BView, CView)
	//{{AFX_MSG_MAP(CExample5BView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5BView construction/destruction

CExample5BView::CExample5BView()
{
	// TODO: add construction code here

}

CExample5BView::~CExample5BView()
{
}

BOOL CExample5BView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample5BView drawing

void CExample5BView::OnDraw(CDC* pDC)
{
	CExample5BDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExample5BView printing

BOOL CExample5BView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample5BView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample5BView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample5BView diagnostics

#ifdef _DEBUG
void CExample5BView::AssertValid() const
{
	CView::AssertValid();
}

void CExample5BView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample5BDoc* CExample5BView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample5BDoc)));
	return (CExample5BDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5BView message handlers
