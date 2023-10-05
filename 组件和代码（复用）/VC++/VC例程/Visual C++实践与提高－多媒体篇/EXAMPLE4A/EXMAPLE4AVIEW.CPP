// Exmaple4AView.cpp : implementation of the CExmaple4AView class
//

#include "stdafx.h"
#include "Exmaple4A.h"

#include "Exmaple4ADoc.h"
#include "Exmaple4AView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AView

IMPLEMENT_DYNCREATE(CExmaple4AView, CView)

BEGIN_MESSAGE_MAP(CExmaple4AView, CView)
	//{{AFX_MSG_MAP(CExmaple4AView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AView construction/destruction

CExmaple4AView::CExmaple4AView()
{
	// TODO: add construction code here

}

CExmaple4AView::~CExmaple4AView()
{
}

BOOL CExmaple4AView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AView drawing

void CExmaple4AView::OnDraw(CDC* pDC)
{
	CExmaple4ADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC MemDC;						//内存设备对象
	CBitmap m_Bitmap, *oldBmp;		//构造位图对象
	BITMAP bmpInfo;					//存储新位图的信息
	int bmWidth,bmHeight;			//位图的宽度和高度
	MemDC.CreateCompatibleDC(pDC);	//创建内存设备对象
	
	//方法一：用LoadBitmap构造并显示DDB位图
	m_Bitmap.LoadBitmap(IDB_BITMAP1);
	m_Bitmap.GetBitmap(&bmpInfo); 	//获取位图的尺寸
	bmWidth=bmpInfo.bmWidth;		
	bmHeight=bmpInfo.bmHeight;	
	oldBmp=MemDC.SelectObject(&m_Bitmap);
	pDC->BitBlt(0,0,bmWidth,bmHeight,&MemDC,0,0,SRCCOPY);	//拷贝位图
	
	//方法二：用CreateCompatibleBitmap构造并显示DDB位图
	m_Bitmap.DeleteObject();
	m_Bitmap.CreateCompatibleBitmap(pDC,bmWidth,bmHeight); 	//创建一个兼容的DDB
	MemDC.SelectObject(&m_Bitmap);
	MemDC.SelectStockObject(BLACK_PEN);
	MemDC.SelectStockObject(GRAY_BRUSH);
	MemDC.Rectangle(0,0,bmWidth,bmHeight); 			//在DDB中画一个矩形
	
	pDC->BitBlt(bmWidth,0,bmWidth,bmHeight,&MemDC,0,0,SRCCOPY);	//拷贝位图
	MemDC.SelectObject(oldBmp);	//使位图m_Bitmap脱离设备上下文
}

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AView printing

BOOL CExmaple4AView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExmaple4AView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExmaple4AView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AView diagnostics

#ifdef _DEBUG
void CExmaple4AView::AssertValid() const
{
	CView::AssertValid();
}

void CExmaple4AView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExmaple4ADoc* CExmaple4AView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExmaple4ADoc)));
	return (CExmaple4ADoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExmaple4AView message handlers
