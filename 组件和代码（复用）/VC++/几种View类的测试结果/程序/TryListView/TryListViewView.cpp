// TryListViewView.cpp : implementation of the CTryListViewView class
//

#include "stdafx.h"
#include "TryListView.h"

#include "TryListViewDoc.h"
#include "TryListViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTryListViewView

IMPLEMENT_DYNCREATE(CTryListViewView, CListView)

BEGIN_MESSAGE_MAP(CTryListViewView, CListView)
	//{{AFX_MSG_MAP(CTryListViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTryListViewView construction/destruction

CTryListViewView::CTryListViewView()
{
	// TODO: add construction code here

}

CTryListViewView::~CTryListViewView()
{
}

BOOL CTryListViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTryListViewView drawing

void CTryListViewView::OnDraw(CDC* pDC)
{
	CTryListViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CTryListViewView::OnInitialUpdate()
{

	m1.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(0,10,100,30), this, 1);
	m2.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(100,10,200,30), this, 1);
	m3.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(200,10,300,30), this, 1);
 


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CTryListViewView printing

BOOL CTryListViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTryListViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTryListViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTryListViewView diagnostics

#ifdef _DEBUG
void CTryListViewView::AssertValid() const
{
	CListView::AssertValid();
}

void CTryListViewView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTryListViewDoc* CTryListViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTryListViewDoc)));
	return (CTryListViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTryListViewView message handlers
