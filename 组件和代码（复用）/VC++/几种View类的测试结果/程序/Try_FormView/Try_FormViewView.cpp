// Try_FormViewView.cpp : implementation of the CTry_FormViewView class
//

#include "stdafx.h"
#include "Try_FormView.h"

#include "Try_FormViewDoc.h"
#include "Try_FormViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewView

IMPLEMENT_DYNCREATE(CTry_FormViewView, CFormView)

BEGIN_MESSAGE_MAP(CTry_FormViewView, CFormView)
	//{{AFX_MSG_MAP(CTry_FormViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewView construction/destruction

CTry_FormViewView::CTry_FormViewView()
	: CFormView(CTry_FormViewView::IDD)
{
	//{{AFX_DATA_INIT(CTry_FormViewView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CTry_FormViewView::~CTry_FormViewView()
{
}

void CTry_FormViewView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTry_FormViewView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CTry_FormViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CTry_FormViewView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m1.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(10,10,100,30), this, WM_USER + 1);
	m2.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(100,10,200,30), this, WM_USER + 1);
	m3.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(200,10,300,30), this, WM_USER + 1);
}

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewView printing

BOOL CTry_FormViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTry_FormViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTry_FormViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTry_FormViewView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewView diagnostics

#ifdef _DEBUG
void CTry_FormViewView::AssertValid() const
{
	CFormView::AssertValid();
}

void CTry_FormViewView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CTry_FormViewDoc* CTry_FormViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTry_FormViewDoc)));
	return (CTry_FormViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTry_FormViewView message handlers
