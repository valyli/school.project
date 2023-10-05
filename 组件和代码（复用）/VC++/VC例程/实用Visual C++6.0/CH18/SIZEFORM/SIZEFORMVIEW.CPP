// SizeFormView.cpp : implementation of the CSizeFormView class
//

#include "stdafx.h"
#include "SizeForm.h"

#include "SizeFormDoc.h"
#include "SizeFormView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSizeFormView

IMPLEMENT_DYNCREATE(CSizeFormView, CFormView)

BEGIN_MESSAGE_MAP(CSizeFormView, CFormView)
	//{{AFX_MSG_MAP(CSizeFormView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSizeFormView construction/destruction

CSizeFormView::CSizeFormView()
	: CFormView(CSizeFormView::IDD)
{
	//{{AFX_DATA_INIT(CSizeFormView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSizeFormView::~CSizeFormView()
{
}

void CSizeFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSizeFormView)
	DDX_Control(pDX, IDC_SIZEABLE_EDIT, m_SizeableEdit);
	//}}AFX_DATA_MAP
}

BOOL CSizeFormView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSizeFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CSizeFormView printing

BOOL CSizeFormView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSizeFormView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSizeFormView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSizeFormView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSizeFormView diagnostics

#ifdef _DEBUG
void CSizeFormView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSizeFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSizeFormDoc* CSizeFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSizeFormDoc)));
	return (CSizeFormDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSizeFormView message handlers

void CSizeFormView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	//**Declare a string object
     CString strTitle;
      
      //**Setup and display the Document Title
      strTitle.Format("Final Width = %d, Height = %d", cx,cy);
      GetDocument( )->SetTitle(strTitle);

	  //**Check the Edit Box is 'Alive'
      if (m_SizeableEdit.GetSafeHwnd( ))
      
      //**Size to the new window size 
      m_SizeableEdit.SetWindowPos(this,0,0,
                                cx-40,cy-40,
           //** Only Resize
           SWP_NOMOVE+SWP_NOZORDER+SWP_SHOWWINDOW+
                          SWP_NOACTIVATE);

}
