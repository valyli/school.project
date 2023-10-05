// dlgbarView.cpp : implementation of the CDlgbarView class
//

#include "stdafx.h"
#include "dlgbar.h"

#include "dlgbarDoc.h"
#include "dlgbarView.h"
#include <afxwin.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgbarView

IMPLEMENT_DYNCREATE(CDlgbarView, CView)

BEGIN_MESSAGE_MAP(CDlgbarView, CView)
	//{{AFX_MSG_MAP(CDlgbarView)
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDC_APPLY_COLOR, ApplyColor)
	ON_CBN_SELCHANGE(IDC_COLOR, ColorChange)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgbarView construction/destruction

CDlgbarView::CDlgbarView()
{
	// TODO: add construction code here
	m_nColor=-1;
}

CDlgbarView::~CDlgbarView()
{
}

BOOL CDlgbarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgbarView drawing

void CDlgbarView::OnDraw(CDC* pDC)
{
	CDlgbarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDlgbarView printing

BOOL CDlgbarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDlgbarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDlgbarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDlgbarView diagnostics

#ifdef _DEBUG
void CDlgbarView::AssertValid() const
{
	CView::AssertValid();
}

void CDlgbarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgbarDoc* CDlgbarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgbarDoc)));
	return (CDlgbarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgbarView message handlers

afx_msg void CDlgbarView::ApplyColor() 
{
	Invalidate();
}

#include "MainFrm.h"
afx_msg void CDlgbarView::ColorChange() 
{
	CMainFrame* pMainFrame = 
		(CMainFrame *)GetParentFrame();
	CComboBox* pColSel = (CComboBox *)
		(pMainFrame->
			m_wndColorDlgBar.GetDlgItem(IDC_COLOR));
	if (pColSel) m_nColor = pColSel->GetCurSel();
}

BOOL CDlgbarView::OnEraseBkgnd(CDC* pDC) 
{
	COLORREF rf = RGB(255,255,255);
	switch(m_nColor)
	{
	case 0: rf = RGB(0,0,255);   break;
	case 1: rf = RGB(0,255,0);   break;
	case 2: rf = RGB(255,0,0);   break;
	case 3: rf = RGB(255,255,0); break;
	}
	CRect rcClient;
	GetClientRect(&rcClient);
	pDC->FillSolidRect(&rcClient,rf);
	return TRUE;
}
