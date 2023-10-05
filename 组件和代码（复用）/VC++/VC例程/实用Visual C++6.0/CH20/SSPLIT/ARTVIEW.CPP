// ArtView.cpp : implementation file
//

#include "stdafx.h"
#include "SSplit.h"
#include "ArtView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CArtView

IMPLEMENT_DYNCREATE(CArtView, CView)

CArtView::CArtView()
{
}

CArtView::~CArtView()
{
}


BEGIN_MESSAGE_MAP(CArtView, CView)
	//{{AFX_MSG_MAP(CArtView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CArtView drawing

void CArtView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	// TODO: add draw code here
	//**Save the current brush
	CBrush *pOldBrush=pDC->GetCurrentBrush();

	//Create a solid blue brush
	CBrush br;
	br.CreateSolidBrush(RGB(0,0,255));

	//**Select the blue brush in to the device context
	pDC->SelectObject(&br);
	pDC->Ellipse(1,1,300,300);
	br.Detach();

	br.CreateHatchBrush(HS_FDIAGONAL,RGB(255,255,0));
	pDC->SelectObject(&br);
	pDC->Ellipse(50,50,200,200);

	//*Restore the current brush
	pDC->SelectObject(pOldBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CArtView diagnostics

#ifdef _DEBUG
void CArtView::AssertValid() const
{
	CView::AssertValid();
}

void CArtView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CArtView message handlers
