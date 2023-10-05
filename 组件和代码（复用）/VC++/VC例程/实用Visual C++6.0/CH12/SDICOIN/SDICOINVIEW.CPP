// SDICoinView.cpp : implementation of the CSDICoinView class
//

#include "stdafx.h"
#include "SDICoin.h"

#include "SDICoinDoc.h"
#include "SDICoinView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSDICoinView

IMPLEMENT_DYNCREATE(CSDICoinView, CView)

BEGIN_MESSAGE_MAP(CSDICoinView, CView)
	//{{AFX_MSG_MAP(CSDICoinView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSDICoinView construction/destruction

CSDICoinView::CSDICoinView()
{
	// TODO: add construction code here

}

CSDICoinView::~CSDICoinView()
{
}

BOOL CSDICoinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSDICoinView drawing

void CSDICoinView::OnDraw(CDC* pDC)
{
	// **Retrieve a pointer to the document
	CSDICoinDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// TODO: add draw code for native data here
	//** Save the current brush
	CBrush * pOldBrush = pDC->GetCurrentBrush();

	// ** Create a solid yellow brush
	CBrush br;
	br.CreateSolidBrush(RGB(255,255,0));

	// Select the yellow brush into the device context
	pDC->SelectObject(&br);

	//Retrieve the number of coins from the document
	//and draw two ellipses to represent each coin 
	for (int nCount = 0; nCount<pDoc->GetCoinCount();nCount++)
	{
		int y = 200 - 10 * nCount;
		pDC->Ellipse(40,y,100,y-30);
		pDC->Ellipse(40,y-10,100,y-35);
	}

	//** Restore the current brush 
	pDC->SelectObject(pOldBrush);
}

/////////////////////////////////////////////////////////////////////////////
// CSDICoinView printing

BOOL CSDICoinView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSDICoinView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSDICoinView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSDICoinView diagnostics

#ifdef _DEBUG
void CSDICoinView::AssertValid() const
{
	CView::AssertValid();
}

void CSDICoinView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDICoinDoc* CSDICoinView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDICoinDoc)));
	return (CSDICoinDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSDICoinView message handlers
