// LIJView.cpp : implementation of the CLIJView class
//

#include "stdafx.h"
#include "LIJ.h"

#include "LIJDoc.h"
#include "LIJView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLIJView

IMPLEMENT_DYNCREATE(CLIJView, CView)

BEGIN_MESSAGE_MAP(CLIJView, CView)
	//{{AFX_MSG_MAP(CLIJView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLIJView construction/destruction

CLIJView::CLIJView()
{
	// TODO: add construction code here

}

CLIJView::~CLIJView()
{
}

BOOL CLIJView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLIJView drawing

void CLIJView::OnDraw(CDC* pDC)
{
	CLIJDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CLIJView printing

BOOL CLIJView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLIJView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLIJView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CLIJView diagnostics

#ifdef _DEBUG
void CLIJView::AssertValid() const
{
	CView::AssertValid();
}

void CLIJView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLIJDoc* CLIJView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLIJDoc)));
	return (CLIJDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLIJView message handlers
