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

 //**The Font Callback function 
int CALLBACK FontCallBack(ENUMLOGFONT FAR* lpelf,
                            NEWTEXTMETRIC FAR *lpnt,
                            int FontType,
                            LPARAM lParam)
 {
      //**Pick the DC pointer from the lParam
      CDC* pDC = (CDC*)lParam;
     CFont fnEnum;
      
      //**Create the font indirectly
      fnEnum.CreateFontIndirect(&lpelf->elfLogFont);
      CFont* pOldFont = pDC->SelectObject(&fnEnum);
      
      //**Get the current Cursor position
      int nYPos = pDC->GetCurrentPosition( ).y;
      
      //*Draw the font name
      pDC->TextOut(5,nYPos,CString(lpelf->elfLogFont.lfFaceName));
      
      //**Move down by the height of the font 
      pDC->MoveTo(0,nYPos+lpelf->elfLogFont.lfHeight);
      pDC->SelectObject(pOldFont);
      
      //**return TRUE to keep on going 
      return TRUE;
 }
      
      
      
 ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 //CSimpTextView drawing
      
 void CSimpTextView::OnDraw(CDC* pDC)
 {
      CSimpTextDoc* pDoc = GetDocument( );
      ASSERT_VALID(pDoc);
      
      //TODO: add draw code for native data here
      
      //**Setup the enum callback calling your function 
      EnumFontFamilies(pDC->GetSafeHdc( ),NULL,(FONTENUMPROC)FontCallBack,(LPARAM)pDC);
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
