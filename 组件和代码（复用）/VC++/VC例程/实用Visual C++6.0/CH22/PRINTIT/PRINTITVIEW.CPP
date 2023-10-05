// PrintItView.cpp : implementation of the CPrintItView class
//

#include "stdafx.h"
#include "PrintIt.h"

#include "PrintItDoc.h"
#include "PrintItView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrintItView

IMPLEMENT_DYNCREATE(CPrintItView, CView)

BEGIN_MESSAGE_MAP(CPrintItView, CView)
	//{{AFX_MSG_MAP(CPrintItView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintItView construction/destruction

CPrintItView::CPrintItView()
{
	// TODO: add construction code here

}

CPrintItView::~CPrintItView()
{
}

BOOL CPrintItView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPrintItView drawing

void CPrintItView::OnDraw(CDC* pDC)
{
	CPrintItDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
 	
    // ** Set metric mapping
	pDC->SetMapMode(MM_LOMETRIC);
    // ** Declare and create a font 2.2cm high

	CFont fnBig;
	
	fnBig.CreateFont(220,0,0,0,FW_HEAVY,FALSE,FALSE,0,
 		ANSI_CHARSET,OUT_DEFAULT_PRECIS,
 		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
 		FF_SWISS+VARIABLE_PITCH,"Arial");
 
 	    // ** Select the new font and store the original
 	    CFont* pOldFont = pDC->SelectObject(&fnBig);
 
 	   //** Declare a client rectangle
 	   CRect rcClient;
 	   GetClientRect(&rcClient);

 // ** Check the device context for printing mode 
 if (pDC->IsPrinting( ))
 {
      // ** Find the Print width : Window width ratio
      double dWidthRatio = (double)m_rcPrintRect.Width( )/
                          (double)rcClient.Width( );
      // ** Find the Print height : Window height ratio
 
      double dHeightRatio = (double)m_rcPrintRect.Height( )/
                          (double)rcClient.Height( );
      
      // ** Caculate the device's aspect ratio
      double dAspect = (double)pDC->GetDeviceCaps(ASPECTX)/
                     (double)pDC->GetDeviceCaps(ASPECTY);
      
      // ** Find the new relative height
      int nHeight = (int)(rcClient.Height( ) *
                  dWidthRatio * dAspect);
      
      // ** Find the new relative width
      int nWidth = (int)(rcClient.Width( ) *
                 dHeightRatio *(1.0 / dAspect) );
      
      // ** Set the whole rectangle
      rcClient = m_rcPrintRect;
      
      // ** Determine the fit across or down the page
      if (nHeight > nWidth)
      {
           // ** Down is best, so adjust the width
           rcClient.BottomRight( ).x =
             m_rcPrintRect.TopLeft( ).x +nWidth;
      }
      else
      {
           // ** Across is best, so adjust the height
           rcClient.BottomRight( ).y =
              m_rcPrintRect.TopLeft( ).y +nHeight;
      }
 }

      
 	   // ** Convert to logical units
 	   pDC->DPtoLP(&rcClient);
 
 	   // ** Set up some drawing variables
 	   const int nPoints = 50;
 	   int xm = rcClient.Width();
 	   int ym = rcClient.Height();
 	   double dAspW = xm/(double)nPoints;
 	   double dAspH = ym/(double)nPoints;
 	
 	   // ** Select a black pen
 	   CPen* pOldPen =
 		   (CPen*)pDC->SelectStockObject(BLACK_PEN);
 
     // ** Draw the lines
 	   for (int i=0;i<nPoints;i++)
 	   {
 			int xo = (int)(i * dAspW);
 			int yo = (int)(i * dAspH);
 
 			pDC->MoveTo(xo,0);
 			pDC->LineTo(xm,yo);
 			pDC->LineTo(xm-xo,ym);
 			pDC->LineTo(0,ym-yo);
 			pDC->LineTo(xo,0);
		}
 
 	   // ** Reselect the old pen
 	   pDC->SelectObject(pOldPen);
 
   	// ** Draw the text on top
   	pDC->SetTextAlign(TA_CENTER+TA_BASELINE);
 	   pDC->SetBkMode(TRANSPARENT);
 	   // ** Set gray text
 	   pDC->SetTextColor(RGB(64,64,64));
     pDC->TextOut(xm/2,ym/2,"Sample Print");
 
 	// ** Reselect the old font
 	pDC->SelectObject(pOldFont);


}

/////////////////////////////////////////////////////////////////////////////
// CPrintItView printing

BOOL CPrintItView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	pInfo->SetMinPage(2);
    pInfo->SetMaxPage(8);

	return DoPreparePrinting(pInfo);
}

void CPrintItView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrintItView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPrintItView diagnostics

#ifdef _DEBUG
void CPrintItView::AssertValid() const
{
	CView::AssertValid();
}

void CPrintItView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPrintItDoc* CPrintItView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrintItDoc)));
	return (CPrintItDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrintItView message handlers

void CPrintItView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pInfo) m_rcPrintRect = pInfo->m_rectDraw;

      // TODO: Add your specialized code here
      
      // ** Create and select the font
      CFont fnTimes;
      fnTimes.CreatePointFont(720,"Times New Roman",pDC);
      CFont* pOldFont = (CFont*)pDC->SelectObject(&fnTimes);
     
      // ** Create and select the brushe
      CBrush brHatch(HS_CROSS, RGB(64,64,64));
      CBrush* pOldBrush =
           (CBrush*)pDC->SelectObject(&brHatch);
      
      // ** Create the page text
      CString strDocText;
      strDocText.Format("Page Number %d",
                  pInfo->m_nCurPage);
      
      pDC->SetTextAlign(TA_CENTER + TA_BASELINE);
      
      // ** Set up some usefull point objects
      CPoint ptCenter = pInfo->m_rectDraw.CenterPoint( );
      CPoint ptTopLeft = pInfo->m_rectDraw.TopLeft( );
      CPoint ptBotRight = pInfo->m_rectDraw.BottomRight( );
      
      // ** Create the points for the diamond
      CPoint ptPolyArray[4] =
      {
           CPoint(ptTopLeft.x, ptCenter.y),
           CPoint(ptCenter.x, ptTopLeft.y),
           CPoint(ptBotRight.x, ptCenter.y),
           CPoint(ptCenter.x, ptBotRight.y)
      };
      
      // Draw the diamond
      pDC->Polygon(ptPolyArray, 4);
      
      // Draw the text
      pDC->TextOut(ptCenter.x, ptCenter.y, strDocText);
      
      // ** Unselect the fonts
      pDC->SelectObject(pOldFont);
      pDC->SelectObject(pOldBrush);

}
