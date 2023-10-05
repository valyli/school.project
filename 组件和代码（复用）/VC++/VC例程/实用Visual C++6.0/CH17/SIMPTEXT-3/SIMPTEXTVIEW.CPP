// SimpTextView.cpp : implementation of the CSimpTextView class
//

#include "stdafx.h"
#include "SimpText.h"

#include "SimpTextDoc.h"
#include "SimpTextView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSimpTextView

IMPLEMENT_DYNCREATE(CSimpTextView, CView)

BEGIN_MESSAGE_MAP(CSimpTextView, CView)
	//{{AFX_MSG_MAP(CSimpTextView)
	ON_COMMAND(ID_CHOOSEFONT, OnChoosefont)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSimpTextView construction/destruction

CSimpTextView::CSimpTextView()
{
	// TODO: add construction code here

}

CSimpTextView::~CSimpTextView()
{
}

BOOL CSimpTextView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSimpTextView drawing

void CSimpTextView::OnDraw(CDC* pDC)
{
	CSimpTextDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
      CFont* pOldFont = pDC->SelectObject(&m_fnCustom);
     
      CRect rcSmall(CPoint(20,20),CPoint(200,100));
      pDC->Rectangle(rcSmall);
      pDC->SetBkMode(TRANSPARENT);
      //**Call DrawText with the message int the rect
      //**Word Breaking and centralized
     
      pDC->DrawText(
           "Bah bah black sheep , have you any wool",
           rcSmall, DT_WORDBREAK+DT_CENTER);
      pDC->SelectObject(pOldFont);

}

/////////////////////////////////////////////////////////////////////////////
// CSimpTextView printing

BOOL CSimpTextView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSimpTextView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSimpTextView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSimpTextView diagnostics

#ifdef _DEBUG
void CSimpTextView::AssertValid() const
{
	CView::AssertValid();
}

void CSimpTextView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSimpTextDoc* CSimpTextView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSimpTextDoc)));
	return (CSimpTextDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSimpTextView message handlers

void CSimpTextView::OnChoosefont() 
{
	// TODO: Add your command handler code here
      //**Declare the CFontDialog
      CFontDialog dlgChooseFont;
      if (dlgChooseFont.DoModal( ) == IDOK)
      {
          m_fnCustom.DeleteObject( );
           m_fnCustom.CreateFontIndirect( 
                dlgChooseFont.m_cf.lpLogFont);
           Invalidate( );
      }

}
