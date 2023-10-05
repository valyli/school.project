/********************************************/
/*				艺术字的输出				*/
/********************************************/
// Example3EView.cpp : implementation of the CExample3EView class
//

#include "stdafx.h"
#include "Example3E.h"

#include "Example3EDoc.h"
#include "Example3EView.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample3EView

IMPLEMENT_DYNCREATE(CExample3EView, CView)

BEGIN_MESSAGE_MAP(CExample3EView, CView)
	//{{AFX_MSG_MAP(CExample3EView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample3EView construction/destruction

CExample3EView::CExample3EView()
{
	// TODO: add construction code here
	//创建新的字体
	m_font.CreateFont(100, 0, 0, 0, FW_BLACK,FALSE, FALSE, FALSE,
						GB2312_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,FIXED_PITCH|FF_MODERN, "楷体_GB2312");
}

CExample3EView::~CExample3EView()
{
}

BOOL CExample3EView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample3EView drawing

void CExample3EView::OnDraw(CDC* pDC)
{
	CExample3EDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	
	//获得窗口用户区的大小
	RECT rect;
	GetClientRect(&rect);

	//选中m_font,作为当前字体
	CFont* pOldFont;
	pOldFont = pDC->SelectObject(&m_font);
	
	//设置背景模式
	pDC->SetBkMode(TRANSPARENT);

	//定义路径
	pDC->BeginPath();
	pDC->TextOut(0,10,"我",2);
	pDC->TextOut(100,10,"的",2);
	pDC->TextOut(200,10,"爱",2);
	pDC->TextOut(300,10,"如",2);
	pDC->TextOut(400,10,"潮",2);
	pDC->TextOut(500,10,"水",2);
	pDC->EndPath();

	//提取路径上的端点和控制点的数目数据
	int iCount=pDC->GetPath(NULL,NULL,0);
	
	//得到路径上的端点和控制点的坐标
	CPoint* pPoints=new CPoint[iCount];
	BYTE* bBytes=new BYTE[iCount];
	pDC->GetPath(pPoints,bBytes,iCount);

	//对路径上各点进行正弦变换（X坐标不变，Y坐标正弦变换）
	int i;
	for(i=0;i<iCount;i++)
		pPoints[i].y=pPoints[i].y+(int)(60*sin(pPoints[i].x/100.*3.1415926)+100);

	//重建偏移后的路径
	CPoint ptStartPoint;//定义路径的起点
	pDC->BeginPath();
	for(i=0;i<iCount;i++)
	{
		switch(bBytes[i])
		{
		//绘制独立的图形，移动到当前点，令其为路径的起点
		case PT_MOVETO:
			pDC->MoveTo(pPoints[i]);
			ptStartPoint=pPoints[i];
			break;
		//当前点和先前点是一条直线的两个端点，画直线
		case PT_LINETO:
			pDC->LineTo(pPoints[i]);
			break;
		//当前点是贝齐尔曲线的端点或控制定点，过后面相邻的3个点画贝齐尔曲线
		case PT_BEZIERTO:
			pDC->PolyBezierTo(pPoints+i,3);
			i=i+2;
			break;
		//判断此点是最后一点，画直线并且封闭图形
		case PT_LINETO | PT_CLOSEFIGURE:
			pDC->LineTo(ptStartPoint);
			break;
		//判断此点是最后一点，画贝齐尔曲线并且封闭图形
		case PT_BEZIERTO | PT_CLOSEFIGURE:
			pPoints[i+2]=ptStartPoint;
			pDC->PolyBezierTo(pPoints+i,3);
			i=i+2;
			break;
		default:
			break;
		}
	}
	pDC->EndPath();

	//用灰色绘制窗口背景
	CBrush* pOldBrush=(CBrush*)(pDC->SelectStockObject(GRAY_BRUSH));
	pDC->Rectangle(&rect);
	pDC->SelectObject(pOldBrush);
	
	//设置设备上下文裁剪路径
	pDC->SelectClipPath(RGN_COPY);
	pDC->Rectangle(&rect);
	pDC->SelectObject(pOldFont);
		
	//用位图填充裁剪区域
	CBitmap bmpPic;
	CBitmap* pOldBmp;
	bmpPic.LoadBitmap(IDB_BITMAP);//载入位图

	//生成与pDC所指设备兼容的存储器设备上下文
	//用拷贝图片前，进行内存内部的准备
	CDC dcMemory;
	dcMemory.CreateCompatibleDC(pDC);
	pOldBmp=dcMemory.SelectObject(&bmpPic);

	//将图片从原矩形拷贝到目的矩形中，并作相应的拉伸或压缩
	pDC->StretchBlt(0,0,rect.right,rect.bottom,&dcMemory,0,0,600,200,SRCCOPY);

	dcMemory.SelectObject(pOldBmp);
	dcMemory.DeleteDC();
	bmpPic.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// CExample3EView printing

BOOL CExample3EView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample3EView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample3EView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample3EView diagnostics

#ifdef _DEBUG
void CExample3EView::AssertValid() const
{
	CView::AssertValid();
}

void CExample3EView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample3EDoc* CExample3EView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample3EDoc)));
	return (CExample3EDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample3EView message handlers
