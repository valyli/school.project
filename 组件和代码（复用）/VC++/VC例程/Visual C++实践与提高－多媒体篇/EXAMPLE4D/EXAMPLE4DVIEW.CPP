// Example4DView.cpp : implementation of the CExample4DView class
//

#include "stdafx.h"
#include "Example4D.h"

#include "Example4DDoc.h"
#include "Example4DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample4DView

IMPLEMENT_DYNCREATE(CExample4DView, CView)

BEGIN_MESSAGE_MAP(CExample4DView, CView)
	//{{AFX_MSG_MAP(CExample4DView)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_EFFECT_MASIC, OnEffectMasic)
	ON_COMMAND(ID_EFFECT_MOVE, OnEffectMove)
	ON_COMMAND(ID_EFFECT_SWEEP, OnEffectSweep)
	ON_COMMAND(ID_EFFECT_GRID, OnEffectGrid)
	ON_COMMAND(ID_EFFECT_WINDOW, OnEffectWindow)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample4DView construction/destruction

CExample4DView::CExample4DView()
{
	// TODO: add construction code here
	nOption=0;
}

CExample4DView::~CExample4DView()
{
}

BOOL CExample4DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample4DView drawing

void CExample4DView::OnDraw(CDC* pDC)
{
	CExample4DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowDIB(pDC,0,0,rect.Width(),rect.Height());
}

/////////////////////////////////////////////////////////////////////////////
// CExample4DView printing

BOOL CExample4DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample4DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample4DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample4DView diagnostics

#ifdef _DEBUG
void CExample4DView::AssertValid() const
{
	CView::AssertValid();
}

void CExample4DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample4DDoc* CExample4DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample4DDoc)));
	return (CExample4DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample4DView message handlers

void CExample4DView::OnFileOpen() 
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

void CExample4DView::OnEffectMasic() 
{
	// TODO: Add your command handler code here
	CDC* pDC = GetDC();
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowMasic(pDC,0,0,rect.Width(),rect.Height());	
}

void CExample4DView::OnEffectMove() 
{
	// TODO: Add your command handler code here
	CDC* pDC = GetDC();
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowMove(pDC,0,0,rect.Width(),rect.Height());	
}

void CExample4DView::OnEffectSweep() 
{
	// TODO: Add your command handler code here
	CDC* pDC = GetDC();
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowSweep(pDC,0,0,rect.Width(),rect.Height());
}

void CExample4DView::OnEffectGrid() 
{
	// TODO: Add your command handler code here
	CDC* pDC = GetDC();
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowGrid(pDC,0,0,rect.Width(),rect.Height());	
}

void CExample4DView::OnEffectWindow() 
{
	// TODO: Add your command handler code here
	CDC* pDC = GetDC();
	if(m_dib.m_pBMI==NULL||m_dib.m_pDIBData==NULL)
		return;
	CRect rect;
	GetClientRect(&rect);
	m_dib.ShowWindow(pDC,0,0,rect.Width(),rect.Height());		
}
