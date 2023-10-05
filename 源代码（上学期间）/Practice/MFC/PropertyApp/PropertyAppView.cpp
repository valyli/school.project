// PropertyAppView.cpp : implementation of the CPropertyAppView class
//

#include "stdafx.h"
#include "PropertyApp.h"

#include "PropertyAppDoc.h"
#include "PropertyAppView.h"
#include "PropSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppView

IMPLEMENT_DYNCREATE(CPropertyAppView, CView)

BEGIN_MESSAGE_MAP(CPropertyAppView, CView)
	//{{AFX_MSG_MAP(CPropertyAppView)
	ON_COMMAND(ID_FUN_PROP, OnFunProp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppView construction/destruction

CPropertyAppView::CPropertyAppView()
{
	// TODO: add construction code here

}

CPropertyAppView::~CPropertyAppView()
{
}

BOOL CPropertyAppView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppView drawing

void CPropertyAppView::OnDraw(CDC* pDC)
{
	CPropertyAppDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDC->TextOut(20,20,m_edit);
	if(m_check ==1)
		pDC->TextOut(20,40,"You check the control!");
	else
		pDC->TextOut(20,40,"You have not check the control!");
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppView diagnostics

#ifdef _DEBUG
void CPropertyAppView::AssertValid() const
{
	CView::AssertValid();
}

void CPropertyAppView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPropertyAppDoc* CPropertyAppView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPropertyAppDoc)));
	return (CPropertyAppDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPropertyAppView message handlers

void CPropertyAppView::OnFunProp() 
{
	// TODO: Add your command handler code here
	PropSheet myProperty(" Ù–‘±Ì",this,0);
	myProperty.m_page1.m_edit = m_edit;
	myProperty.m_page2.m_check = m_check;
	if(myProperty.DoModal() == IDOK)
	{
		m_edit = myProperty.m_page1.m_edit;
		m_check = myProperty.m_page2.m_check;
		Invalidate(TRUE);
	}
}
