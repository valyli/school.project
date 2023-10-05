// PanSDIView.cpp : implementation of the CPanSDIView class
//

#include "stdafx.h"
#include "PanSDI.h"

#include "PanSDIDoc.h"
#include "PanSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPanSDIView

IMPLEMENT_DYNCREATE(CPanSDIView, CScrollView)

BEGIN_MESSAGE_MAP(CPanSDIView, CScrollView)
	//{{AFX_MSG_MAP(CPanSDIView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPanSDIView construction/destruction

CPanSDIView::CPanSDIView()
{
	// TODO: add construction code here

}

CPanSDIView::~CPanSDIView()
{
}

BOOL CPanSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPanSDIView drawing

void CPanSDIView::OnDraw(CDC* pDC)
{
	CPanSDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
    //**Select a Gray Brush
    CBrush* pOldBrush =
    (CBrush*)pDC->SelectStockObject(LTGRAY_BRUSH);
    
 //Make a CRect
      CRect rcTotal(CPoint(0,0), GetTotalSize( ));
      
      //Draw Ellipse
      pDC->Ellipse(rcTotal);
      
      //** Get Client Rect
      CRect  rcClient;
     GetClientRect(&rcClient);
      
      //** Get Scroll Pos
      rcClient += GetScrollPosition( );
      //** Find Middle
      CPoint ptCenter = rcClient.CenterPoint( );

      //** Top Left to Bottom Right Line
      pDC->MoveTo(ptCenter + CPoint(-30,-30));
      pDC->LineTo(ptCenter + CPoint(+30,+30));
      
      // ** Top Right to Bottom Left Line
      pDC->MoveTo(ptCenter + CPoint(+30,-30));
      pDC->LineTo(ptCenter + CPoint(-30,+30));
      
      // Reselect the old brush
      pDC->SelectObject(pOldBrush);

}

void CPanSDIView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 2000;
	SetScrollSizes(MM_TEXT, sizeTotal, CSize(200,10), CSize(20,1));
}

/////////////////////////////////////////////////////////////////////////////
// CPanSDIView printing

BOOL CPanSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPanSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPanSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPanSDIView diagnostics

#ifdef _DEBUG
void CPanSDIView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPanSDIView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPanSDIDoc* CPanSDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPanSDIDoc)));
	return (CPanSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPanSDIView message handlers

BOOL CPanSDIView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	// TODO: Add your specialized code here and/or call the base class
	Invalidate( );

	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}
