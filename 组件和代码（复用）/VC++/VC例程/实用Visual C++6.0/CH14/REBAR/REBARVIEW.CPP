// rebarView.cpp : implementation of the CRebarView class
//

#include "stdafx.h"
#include "rebar.h"

#include "rebarDoc.h"
#include "rebarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRebarView

IMPLEMENT_DYNCREATE(CRebarView, CView)

BEGIN_MESSAGE_MAP(CRebarView, CView)
	//{{AFX_MSG_MAP(CRebarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRebarView construction/destruction

CRebarView::CRebarView()
{
	// TODO: add construction code here

}

CRebarView::~CRebarView()
{
}

BOOL CRebarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CRebarView drawing

void CRebarView::OnDraw(CDC* pDC)
{
	CRebarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CRebarView printing

BOOL CRebarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRebarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRebarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CRebarView diagnostics

#ifdef _DEBUG
void CRebarView::AssertValid() const
{
	CView::AssertValid();
}

void CRebarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRebarDoc* CRebarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRebarDoc)));
	return (CRebarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRebarView message handlers
