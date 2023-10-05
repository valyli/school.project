// DsplitView.cpp : implementation of the CDsplitView class
//

#include "stdafx.h"
#include "Dsplit.h"

#include "DsplitDoc.h"
#include "DsplitView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDsplitView

IMPLEMENT_DYNCREATE(CDsplitView, CScrollView)

BEGIN_MESSAGE_MAP(CDsplitView, CScrollView)
	//{{AFX_MSG_MAP(CDsplitView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDsplitView construction/destruction

CDsplitView::CDsplitView()
{
	// TODO: add construction code here

}

CDsplitView::~CDsplitView()
{
}

BOOL CDsplitView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDsplitView drawing

void CDsplitView::OnDraw(CDC* pDC)
{
	CDsplitDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	TEXTMETRIC tm;
	int nLineHeight;

	//**Get metrics of the current font & calculate the line height
	pDC->GetTextMetrics(&tm);
	nLineHeight=tm.tmHeight+tm.tmExternalLeading;

	//**Output 50 lines of text
	CString str;
	for (int nLine=1;nLine<51;nLine++)
	{
		str.Format("Line %d - I must Not feed my homework to my dog.",nLine);
		pDC->TextOut(5,nLine*nLineHeight,str);
	}
}

void CDsplitView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view

	//**Initialize the total scroll size to 1000*1000
	sizeTotal.cx = sizeTotal.cy = 1000;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CDsplitView printing

BOOL CDsplitView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDsplitView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDsplitView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDsplitView diagnostics

#ifdef _DEBUG
void CDsplitView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDsplitView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CDsplitDoc* CDsplitView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDsplitDoc)));
	return (CDsplitDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDsplitView message handlers
