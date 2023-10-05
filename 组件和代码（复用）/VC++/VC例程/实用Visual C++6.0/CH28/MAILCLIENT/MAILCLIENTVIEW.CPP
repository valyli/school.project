// MailClientView.cpp : implementation of the CMailClientView class
//

#include "stdafx.h"
#include "MailClient.h"

#include "MailClientDoc.h"
#include "MailClientView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMailClientView

IMPLEMENT_DYNCREATE(CMailClientView, CEditView)

BEGIN_MESSAGE_MAP(CMailClientView, CEditView)
	//{{AFX_MSG_MAP(CMailClientView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMailClientView construction/destruction

CMailClientView::CMailClientView()
{
	// TODO: add construction code here

}

CMailClientView::~CMailClientView()
{
}

BOOL CMailClientView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CMailClientView drawing

void CMailClientView::OnDraw(CDC* pDC)
{
	CMailClientDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMailClientView printing

BOOL CMailClientView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CMailClientView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing.
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CMailClientView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMailClientView diagnostics

#ifdef _DEBUG
void CMailClientView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMailClientView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CMailClientDoc* CMailClientView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMailClientDoc)));
	return (CMailClientDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMailClientView message handlers
