// AutoATLView.cpp : implementation of the CAutoATLView class
//

#include "stdafx.h"
#include "AutoATL.h"

#include "AutoATLDoc.h"
#include "AutoATLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoATLView

IMPLEMENT_DYNCREATE(CAutoATLView, CView)

BEGIN_MESSAGE_MAP(CAutoATLView, CView)
	//{{AFX_MSG_MAP(CAutoATLView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoATLView construction/destruction

CAutoATLView::CAutoATLView()
{
	// TODO: add construction code here

}

CAutoATLView::~CAutoATLView()
{
}

BOOL CAutoATLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoATLView drawing

void CAutoATLView::OnDraw(CDC* pDC)
{
	CAutoATLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAutoATLView printing

BOOL CAutoATLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAutoATLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAutoATLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAutoATLView diagnostics

#ifdef _DEBUG
void CAutoATLView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoATLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoATLDoc* CAutoATLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoATLDoc)));
	return (CAutoATLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoATLView message handlers
