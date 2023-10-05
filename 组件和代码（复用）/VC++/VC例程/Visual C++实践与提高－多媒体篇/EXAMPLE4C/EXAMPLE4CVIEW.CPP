// Example4CView.cpp : implementation of the CExample4CView class
//

#include "stdafx.h"
#include "Example4C.h"

#include "Example4CDoc.h"
#include "Example4CView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExample4CView

IMPLEMENT_DYNCREATE(CExample4CView, CView)

BEGIN_MESSAGE_MAP(CExample4CView, CView)
	//{{AFX_MSG_MAP(CExample4CView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_MESSAGE(WM_DOREALIZE, OnDoRealize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample4CView construction/destruction

CExample4CView::CExample4CView()
{
	// TODO: add construction code here
	m_pLP = (LPLOGPALETTE) new char[sizeof(LOGPALETTE) +
		256 * sizeof(PALETTEENTRY)];
	FillPalette();
	m_Palette.CreatePalette(m_pLP);
}

CExample4CView::~CExample4CView()
{
	if (m_pLP) 
		delete (m_pLP);
}

BOOL CExample4CView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExample4CView drawing

void CExample4CView::OnDraw(CDC* pDC)
{
	CExample4CDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CBrush brush,*pOldBrush;
	int x,y,i,num;

	pDC->SelectPalette(&m_Palette,FALSE);
	pDC->RealizePalette();
	pDC->SelectStockObject(BLACK_PEN);

	for(i=0;i<256;i++)
	{
		num = i/64;

		y=(i/8)*15 - num*120;
		x=(i%8)*15 + num*120;
		brush.CreateSolidBrush(PALETTEINDEX(i)); //调色板索引引用
		pOldBrush=pDC->SelectObject(&brush);
		pDC->Rectangle(x,y,x+15,y+15);
		pDC->SelectObject(pOldBrush);
		brush.DeleteObject();
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExample4CView printing

BOOL CExample4CView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CExample4CView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CExample4CView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CExample4CView diagnostics

#ifdef _DEBUG
void CExample4CView::AssertValid() const
{
	CView::AssertValid();
}

void CExample4CView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CExample4CDoc* CExample4CView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CExample4CDoc)));
	return (CExample4CDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExample4CView message handlers
LRESULT CExample4CView::OnDoRealize(WPARAM wParam, LPARAM)

{
	CClientDC dc(this);
	dc.SelectPalette(&m_Palette,FALSE);
	if(dc.RealizePalette()) //若调色板映射被改变则刷新视图
		GetDocument()->UpdateAllViews(NULL);
	return 0L;
}

void CExample4CView::FillPalette()
{
	m_pLP->palVersion    = 0x300; 
	m_pLP->palNumEntries = 256; 
 
	UINT iColorIndex = 0;
	for (int nColor = 0; nColor < 4; nColor++)
	{
		// 创建调色板的颜色
		for (UINT i = iColorIndex; i < iColorIndex + 64; i++)
		{
			switch (nColor)
			{
			case 0://红色
				m_pLP->palPalEntry[i].peRed   = (BYTE)i * 4;    
				m_pLP->palPalEntry[i].peGreen = 0;    
				m_pLP->palPalEntry[i].peBlue  = 0;    
				m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
				break;
			case 1://绿色
				m_pLP->palPalEntry[i].peRed   = 0;    
				m_pLP->palPalEntry[i].peGreen = (BYTE)i * 4;    
				m_pLP->palPalEntry[i].peBlue  = 0;    
				m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
				break;
			case 2://蓝色
				m_pLP->palPalEntry[i].peRed   = 0;    
				m_pLP->palPalEntry[i].peGreen = 0;    
				m_pLP->palPalEntry[i].peBlue  = (BYTE)i * 4;    
				m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
				break;
            case 3://红色和绿色的混合色
				m_pLP->palPalEntry[i].peRed   = 0;    
				m_pLP->palPalEntry[i].peGreen = (BYTE)i * 4;    
				m_pLP->palPalEntry[i].peBlue  = (BYTE)i * 4;    
				m_pLP->palPalEntry[i].peFlags = PC_RESERVED;
				break;
			}
		}
		iColorIndex += 64;
	}
}
