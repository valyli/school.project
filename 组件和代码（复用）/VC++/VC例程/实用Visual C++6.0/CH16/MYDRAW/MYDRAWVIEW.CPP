// MyDrawView.cpp : implementation of the CMyDrawView class
//

#include "stdafx.h"
#include "MyDraw.h"

#include "MyDrawDoc.h"
#include "MyDrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView

IMPLEMENT_DYNCREATE(CMyDrawView, CView)

BEGIN_MESSAGE_MAP(CMyDrawView, CView)
	//{{AFX_MSG_MAP(CMyDrawView)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView construction/destruction

CMyDrawView::CMyDrawView()
{
	// TODO: add construction code here

}

CMyDrawView::~CMyDrawView()
{
}

BOOL CMyDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView drawing
#include "math.h"
void CMyDrawView::OnDraw(CDC* pDC)
{
	CMyDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CPen penRed(PS_SOLID,5,RGB(255,0,0));
	CPen *pOldPen=NULL;

	pOldPen=pDC->SelectObject(&penRed);

	CRect rcClient;
	GetClientRect(&rcClient);

	CBrush brBlue(RGB(0,0,255));
	CBrush *pOldBrush=NULL;
	
	pOldBrush=pDC->SelectObject(&brBlue);

	for (int w=0;w<2;w++)
	{
		const int nPoints=5;
		double nAngle=(720.0/57.295)/(double)nPoints;
		int xOffset=(w?1:-1)*rcClient.Width()/4;
		pDC->SetPolyFillMode(w?ALTERNATE:WINDING);
		CPoint ptPolyAr[nPoints];
		for (int i=0;i<nPoints;i++)
		{
			ptPolyAr[i].x=xOffset+
				(long)(sin((double)i*nAngle)*100.0);
			ptPolyAr[i].y=
				(long)(cos((double)i*nAngle)*100.0);
			ptPolyAr[i]+=rcClient.CenterPoint();
		}
		pDC->Polygon(ptPolyAr,nPoints);

	}

	pDC->SelectObject(pOldBrush);	
	pDC->SelectObject(pOldPen);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView printing

BOOL CMyDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView diagnostics

#ifdef _DEBUG
void CMyDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDrawDoc* CMyDrawView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDrawDoc)));
	return (CMyDrawDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDrawView message handlers

BOOL CMyDrawView::OnEraseBkgnd(CDC* pDC) 
{
	CBrush brDesktop;
	brDesktop.CreateSysColorBrush(COLOR_DESKTOP);
	
	CRect rcClient;
	GetClientRect(&rcClient);

	CBrush *pOldBrush=pDC->SelectObject(&brDesktop);

//	pDC->Ellipse(rcClient);
	
	pDC->SelectObject(pOldBrush);
	return CView::OnEraseBkgnd(pDC);
}
