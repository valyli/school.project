// MapModeView.cpp : implementation of the CMapModeView class
//

#include "stdafx.h"
#include "MapMode.h"

#include "MapModeDoc.h"
#include "MapModeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapModeView

IMPLEMENT_DYNCREATE(CMapModeView, CView)

BEGIN_MESSAGE_MAP(CMapModeView, CView)
	//{{AFX_MSG_MAP(CMapModeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMapModeView construction/destruction

CMapModeView::CMapModeView()
{
	// TODO: add construction code here

}

CMapModeView::~CMapModeView()
{
}

BOOL CMapModeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMapModeView drawing

void CMapModeView::OnDraw(CDC* pDC)
{
	CMapModeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here

	//*Set the mapping mode to 0.1mm
	pDC->SetMapMode(MM_ANISOTROPIC);

	//*Find the client rectangle(in device coords)
	CRect rcClient;
	GetClientRect(&rcClient);

	//**Set the device extent to the client extend
	//**acroos and 500 pixels down
	pDC->SetViewportExt(CSize(rcClient.BottomRight().x,
		500));

	//**Set the logical extent to the 10000 units
	//**across and 500 pixels down
	pDC->SetWindowExt(CSize(10000,500));

	pDC->DPtoLP(&rcClient);

	for (int x=rcClient.TopLeft().x;
			 x<rcClient.BottomRight().x;
			 x+=100)
	{
		//**Set threes pixels at the y coordinate
		pDC->SetPixel(x,rcClient.CenterPoint().y-1,0);
		pDC->SetPixel(x,rcClient.CenterPoint().y,0);
		pDC->SetPixel(x,rcClient.CenterPoint().y+1,0);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMapModeView printing

BOOL CMapModeView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMapModeView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMapModeView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMapModeView diagnostics

#ifdef _DEBUG
void CMapModeView::AssertValid() const
{
	CView::AssertValid();
}

void CMapModeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMapModeDoc* CMapModeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapModeDoc)));
	return (CMapModeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMapModeView message handlers
