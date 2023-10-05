// Example5DView.cpp : implementation of the CExample5DView class
//

#include "stdafx.h"
#include "Example5D.h"

#include "Example5DDoc.h"
#include "Example5DView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample5DView

IMPLEMENT_DYNCREATE(CExample5DView, CView)

BEGIN_MESSAGE_MAP(CExample5DView, CView)
	//{{AFX_MSG_MAP(CExample5DView)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample5DView construction/destruction

CExample5DView::CExample5DView()
{
	// TODO: add construction code here
	m_clientPt.x =1;
	m_clientPt.y =1;
	m_playIndex=0;
	m_imageNumber=0;
}

CExample5DView::~CExample5DView()
{
}

BOOL CExample5DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample5DView drawing

void CExample5DView::OnDraw(CDC* pDC)
{
	CExample5DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CExample5DView printing

BOOL CExample5DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample5DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample5DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample5DView diagnostics

#ifdef _DEBUG
void CExample5DView::AssertValid() const
{
	CView::AssertValid();
}

void CExample5DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample5DDoc* CExample5DView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample5DDoc)));
	return (CExample5DDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample5DView message handlers
void CExample5DView::CreateImageList()
{
	//把要播放的图标资源加入图像列表。
	m_imageList.Create (70,50,ILC_COLOR,5,2);
	HICON hIcon;
	for(int i=0;i<=9;i++)
	{
		hIcon = ::LoadIcon(AfxGetResourceHandle(),MAKEINTRESOURCE(IDI_ICON1+i));
		m_imageList.Add(hIcon);
		m_imageNumber++;
	}
}
//绘制动画
int CExample5DView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CreateImageList();
	SetTimer(1,20,NULL);
	
	return 0;
}

void CExample5DView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pDC=GetDC();
	if(m_playIndex>m_imageNumber)
		m_playIndex=0;
	m_imageList.Draw(pDC,m_playIndex,m_clientPt,ILD_TRANSPARENT);
	m_playIndex++;
	ReleaseDC(pDC);
	
	CView::OnTimer(nIDEvent);
}

void CExample5DView::OnDestroy() 
{
	CView::OnDestroy();
	KillTimer(1);
	// TODO: Add your message handler code here
	
}
