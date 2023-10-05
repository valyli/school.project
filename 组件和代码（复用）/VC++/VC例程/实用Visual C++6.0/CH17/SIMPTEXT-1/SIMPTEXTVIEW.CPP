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
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
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
	// TODO: add draw code for native data here
       //**Declare a CRect to hold hte client rect 
      CRect rcClient;
      GetClientRect(rcClient);
      
      //**Find the mid point
      CPoint ptCenter = rcClient.CenterPoint( );
      pDC->SetBkMode(TRANSPARENT);
      
      //**Loop through 360 degrees
      for (int i=0; i<360; i+=18)
      {
           CFont fnBig;
           
           //**30 high, default width
           fnBig.CreateFont(30,0,
                //**Change Orientation
                i*10,i*10,
                //**Increase the weight
                i/4,
                FALSE,
                TRUE, //**Underlined
               FALSE,
                ANSI_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                PROOF_QUALITY,
                DEFAULT_PITCH+FF_DONTCARE,
                "Arail"
                );
          
           CFont *pOldFont = pDC->SelectObject(&fnBig);
      
        //**Draw the text
           pDC->TextOut( ptCenter.x,ptCenter.y,
                 ".....Beautiful Fonts");
      
           pDC->SelectObject(pOldFont);
      }

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
