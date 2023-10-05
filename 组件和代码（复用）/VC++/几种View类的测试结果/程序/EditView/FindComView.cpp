// FindComView.cpp : implementation of the CFindComView class
//

#include "stdafx.h"
#include "FindCom.h"

#include "FindComDoc.h"
#include "FindComView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindComView

IMPLEMENT_DYNCREATE(CFindComView, CEditView)

BEGIN_MESSAGE_MAP(CFindComView, CEditView)
	//{{AFX_MSG_MAP(CFindComView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindComView construction/destruction

CFindComView::CFindComView()
{
	// TODO: add construction code here

}

CFindComView::~CFindComView()
{
}

BOOL CFindComView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CFindComView drawing

void CFindComView::OnDraw(CDC* pDC)
{
	CFindComDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	int i = 1000;
	while(i >= 0)
	{
		pDC->TextOut(100, i, "asdfasdfasdfasdf");
		i--;
	}
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CFindComView printing

BOOL CFindComView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CFindComView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CFindComView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CFindComView diagnostics

#ifdef _DEBUG
void CFindComView::AssertValid() const
{
	CEditView::AssertValid();
}

void CFindComView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CFindComDoc* CFindComView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFindComDoc)));
	return (CFindComDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFindComView message handlers

void CFindComView::OnInitialUpdate() 
{
	CEditView::OnInitialUpdate();
	m1.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(10,10,100,30), this, 1);
	m2.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(100,10,200,30), this, 1);
	m3.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
   CRect(200,10,300,30), this, 1);

	// TODO: Add your specialized code here and/or call the base class
	
}
