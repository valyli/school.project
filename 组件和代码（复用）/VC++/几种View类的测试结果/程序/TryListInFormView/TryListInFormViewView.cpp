// TryListInFormViewView.cpp : implementation of the CTryListInFormViewView class
//

#include "stdafx.h"
#include "TryListInFormView.h"

#include "TryListInFormViewDoc.h"
#include "TryListInFormViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewView

IMPLEMENT_DYNCREATE(CTryListInFormViewView, CFormView)

BEGIN_MESSAGE_MAP(CTryListInFormViewView, CFormView)
	//{{AFX_MSG_MAP(CTryListInFormViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewView construction/destruction

CTryListInFormViewView::CTryListInFormViewView()
	: CFormView(CTryListInFormViewView::IDD)
{
	//{{AFX_DATA_INIT(CTryListInFormViewView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CTryListInFormViewView::~CTryListInFormViewView()
{
}

void CTryListInFormViewView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTryListInFormViewView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CTryListInFormViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTryListInFormViewView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewView printing

BOOL CTryListInFormViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTryListInFormViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTryListInFormViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTryListInFormViewView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewView diagnostics

#ifdef _DEBUG
void CTryListInFormViewView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTryListInFormViewView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTryListInFormViewDoc* CTryListInFormViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTryListInFormViewDoc)));
	return (CTryListInFormViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewView message handlers
