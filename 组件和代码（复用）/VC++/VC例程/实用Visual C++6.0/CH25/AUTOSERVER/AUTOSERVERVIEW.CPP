// AutoserverView.cpp : implementation of the CAutoserverView class
//

#include "stdafx.h"
#include "Autoserver.h"

#include "AutoserverDoc.h"
#include "AutoserverView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoserverView

IMPLEMENT_DYNCREATE(CAutoserverView, CView)

BEGIN_MESSAGE_MAP(CAutoserverView, CView)
	//{{AFX_MSG_MAP(CAutoserverView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoserverView construction/destruction

CAutoserverView::CAutoserverView()
{
	// TODO: add construction code here

}

CAutoserverView::~CAutoserverView()
{
}

BOOL CAutoserverView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAutoserverView drawing

void CAutoserverView::OnDraw(CDC* pDC)
{
	CAutoserverDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAutoserverView printing

BOOL CAutoserverView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAutoserverView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAutoserverView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAutoserverView diagnostics

#ifdef _DEBUG
void CAutoserverView::AssertValid() const
{
	CView::AssertValid();
}

void CAutoserverView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAutoserverDoc* CAutoserverView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAutoserverDoc)));
	return (CAutoserverDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoserverView message handlers
