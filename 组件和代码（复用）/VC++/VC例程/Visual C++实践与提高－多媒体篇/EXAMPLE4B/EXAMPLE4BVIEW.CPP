// Example4BView.cpp : implementation of the CExample4BView class
//

#include "stdafx.h"
#include "Example4B.h"

#include "Example4BDoc.h"
#include "Example4BView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample4BView

IMPLEMENT_DYNCREATE(CExample4BView, CView)

BEGIN_MESSAGE_MAP(CExample4BView, CView)
	//{{AFX_MSG_MAP(CExample4BView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample4BView construction/destruction

CExample4BView::CExample4BView()
{
	// TODO: add construction code here

}

CExample4BView::~CExample4BView()
{
}

BOOL CExample4BView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample4BView drawing

void CExample4BView::OnDraw(CDC* pDC)
{
	CExample4BDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowDIB(pDC,0,0,rect.Width(),rect.Height());
}

/////////////////////////////////////////////////////////////////////////////
// CExample4BView printing

BOOL CExample4BView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample4BView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample4BView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample4BView diagnostics

#ifdef _DEBUG
void CExample4BView::AssertValid() const
{
	CView::AssertValid();
}

void CExample4BView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample4BDoc* CExample4BView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample4BDoc)));
	return (CExample4BDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample4BView message handlers

void CExample4BView::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CString filename;
	static char szFilter[]="BMPÎÄ¼þ(*.bmp)|*.bmp||";
	CFileDialog dlg(TRUE,"bmp",NULL,
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,szFilter);
	if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();
		if(!(m_dib.LoadBmp(filename)))
			return;
		Invalidate(FALSE);
	}	
}
