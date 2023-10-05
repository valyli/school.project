// MDIBillView.cpp : implementation file
//

#include "stdafx.h"
#include "MDICoin.h"
#include "MDIBillView.h"
#include "MDIBillDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMDIBillView

IMPLEMENT_DYNCREATE(CMDIBillView, CView)

CMDIBillView::CMDIBillView()
{
	
}

CMDIBillView::~CMDIBillView()
{
}


BEGIN_MESSAGE_MAP(CMDIBillView, CView)
	//{{AFX_MSG_MAP(CMDIBillView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMDIBillView drawing

void CMDIBillView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
      CBrush* pOldBrush = pDC->GetCurrentBrush( );
      
      // ** Create a solid green brush
      CBrush br;
      br.CreateSolidBrush(RGB(0,128,32));
      
      // ** Select the green brush into the device context
      pDC->SelectObject(&br);
      
      // ** Retrieve the number of bills from the document
      // and draw a rectangle and a $ to represent the bill
      for (int nCount = 0; nCount < ((CMDIBillDoc*)pDoc)->GetBillCount( );
              nCount++)
      {
           int x = 40 + 20 * nCount;
           pDC->Rectangle(x,40,x+100,90);
           pDC->TextOut(x+5,45,"$");
      }
      
      // ** Restore the current brush
      pDC->SelectObject(pOldBrush);

}

/////////////////////////////////////////////////////////////////////////////
// CMDIBillView diagnostics

#ifdef _DEBUG
void CMDIBillView::AssertValid() const
{
	CView::AssertValid();
}

void CMDIBillView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMDIBillView message handlers

CMDIBillDoc* CMDIBillView::GetDocument()
{
	return (CMDIBillDoc*)m_pDocument;
	
}
