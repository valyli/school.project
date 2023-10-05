// SSplitView.cpp : implementation of the CSSplitView class
//

#include "stdafx.h"
#include "SSplit.h"

#include "SSplitDoc.h"
#include "SSplitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSplitView

IMPLEMENT_DYNCREATE(CSSplitView, CEditView)

BEGIN_MESSAGE_MAP(CSSplitView, CEditView)
	//{{AFX_MSG_MAP(CSSplitView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSSplitView construction/destruction

CSSplitView::CSSplitView()
{
	// TODO: add construction code here

}

CSSplitView::~CSSplitView()
{
}

BOOL CSSplitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CSSplitView drawing

void CSSplitView::OnDraw(CDC* pDC)
{
	CSSplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSSplitView printing

BOOL CSSplitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CSSplitView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CSSplitView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CSSplitView diagnostics

#ifdef _DEBUG
void CSSplitView::AssertValid() const
{
	CEditView::AssertValid();
}

void CSSplitView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CSSplitDoc* CSSplitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSSplitDoc)));
	return (CSSplitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSSplitView message handlers
