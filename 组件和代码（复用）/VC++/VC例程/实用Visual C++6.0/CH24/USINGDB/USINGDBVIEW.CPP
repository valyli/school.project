// UsingDBView.cpp : implementation of the CUsingDBView class
//

#include "stdafx.h"
#include "UsingDB.h"

#include "UsingDBSet.h"
#include "UsingDBDoc.h"
#include "UsingDBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsingDBView

IMPLEMENT_DYNCREATE(CUsingDBView, CRecordView)

BEGIN_MESSAGE_MAP(CUsingDBView, CRecordView)
	//{{AFX_MSG_MAP(CUsingDBView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsingDBView construction/destruction

CUsingDBView::CUsingDBView()
	: CRecordView(CUsingDBView::IDD)
{
	//{{AFX_DATA_INIT(CUsingDBView)
		// NOTE: the ClassWizard will add member initialization here
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CUsingDBView::~CUsingDBView()
{
}

void CUsingDBView::DoDataExchange(CDataExchange* pDX)
{
	CRecordView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsingDBView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BOOL CUsingDBView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CRecordView::PreCreateWindow(cs);
}

void CUsingDBView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_usingDBSet;
	CRecordView::OnInitialUpdate();
}

/////////////////////////////////////////////////////////////////////////////
// CUsingDBView printing

BOOL CUsingDBView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CUsingDBView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CUsingDBView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CUsingDBView diagnostics

#ifdef _DEBUG
void CUsingDBView::AssertValid() const
{
	CRecordView::AssertValid();
}

void CUsingDBView::Dump(CDumpContext& dc) const
{
	CRecordView::Dump(dc);
}

CUsingDBDoc* CUsingDBView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CUsingDBDoc)));
	return (CUsingDBDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CUsingDBView database support
CRecordset* CUsingDBView::OnGetRecordset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CUsingDBView message handlers
