// homework4View.cpp : implementation of the CHomework4View class
//

#include "stdafx.h"
#include "homework4.h"
#include "SelStyleDlg.h"

#include "homework4Doc.h"
#include "homework4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHomework4View

IMPLEMENT_DYNCREATE(CHomework4View, CScrollView)

BEGIN_MESSAGE_MAP(CHomework4View, CScrollView)
	//{{AFX_MSG_MAP(CHomework4View)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework4View construction/destruction

CHomework4View::CHomework4View()
{
	strcpy(m_SelStyleStr, "Now the Map Mode = ");
	strcpy(m_WinOrgStr, "The Window Original = ");
	strcpy(m_WinExtStr, "The Window Extent = ");
	strcpy(m_ViewOrgStr, "The View Port Original = ");
	strcpy(m_ViewExtStr, "The View Port Extent = ");
	strcpy(m_TextPosStr, "The Position of Text = ");
	strcpy(m_CharHightStr, "The Height of Character = ");
	strcpy(m_MaxCharWidthStr, "The Maximum Width of Character = ");
	strcpy(m_AveCharWidthStr, "The Average Width of Character = ");
	m_SelStyleDlg.m_SelStyle = "MM_TEXT";
	m_SelStyleDlg.m_x = 1;
	m_SelStyleDlg.m_y = 1;
	m_SelStyle = MM_TEXT;
}

CHomework4View::~CHomework4View()
{
}

BOOL CHomework4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CHomework4View drawing

void CHomework4View::OnDraw(CDC* pDC)
{
	CHomework4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	//按照用户选择的映射方式设置窗口
	if(m_ChangeSelStyle == TRUE)
	{
		switch(m_SelStyle)
		{
		case MM_TEXT:
			pDC->SetMapMode(MM_TEXT);
			break;
		case MM_LOMETRIC:
			pDC->SetMapMode(MM_LOMETRIC);
			break;
		case MM_HIMETRIC:
			pDC->SetMapMode(MM_HIMETRIC);
			break;
		case MM_LOENGLISH:
			pDC->SetMapMode(MM_LOENGLISH);
			break;
		case MM_HIENGLISH:
			pDC->SetMapMode(MM_HIENGLISH);
			break;
		case MM_TWIPS:
			pDC->SetMapMode(MM_TWIPS);
			break;
		case MM_ISOTROPIC:
			pDC->SetMapMode(MM_ISOTROPIC);
			break;
		case MM_ANISOTROPIC:
			pDC->SetMapMode(MM_ANISOTROPIC);
			break;
		default:
			pDC->SetMapMode(MM_TEXT);
		}
		//若选择了MM_ISOTROPIC或MM_ANISOTROPIC时，进行相应设置
		if(pDC->GetMapMode() == MM_ISOTROPIC
			|| pDC->GetMapMode() == MM_ANISOTROPIC)
		{
			pDC->SetWindowExt(m_SelStyleDlg.m_x, 
				m_SelStyleDlg.m_y);
		}
		m_ChangeSelStyle = FALSE;
	}
	//按照新的映射方式获取相应信息
	m_WinOrg = pDC->GetWindowOrg();
	m_ViewOrg = pDC->GetViewportOrg();
	m_WinExt = pDC->GetWindowExt();
	m_ViewExt = pDC->GetViewportExt();

	pDC->SelectObject(&m_Font);
	pDC->SetTextColor(m_Color);
	Draw(pDC);
}

void CHomework4View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal, sizePage, sizeLine;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 3000;
	sizePage.cx = 50;
	sizePage.cy = 50;
	sizeLine.cx = 10;
	sizeLine.cy = 10;
	SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
	CDC* pDC = GetDC();
	pDC->SetMapMode(MM_TEXT);
	m_WinOrg = pDC->GetWindowOrg();
	m_ViewOrg = pDC->GetViewportOrg();
	m_WinExt = pDC->GetWindowExt();
	m_ViewExt = pDC->GetViewportExt();
	m_ChangeSelStyle = FALSE;

	pDC->GetCurrentFont()->GetLogFont(&m_logFont);
	m_Font.CreateFontIndirect(&m_logFont);
	m_Color = COLOR_WINDOWTEXT;
}

/////////////////////////////////////////////////////////////////////////////
// CHomework4View diagnostics

#ifdef _DEBUG
void CHomework4View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CHomework4View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CHomework4Doc* CHomework4View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHomework4Doc)));
	return (CHomework4Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHomework4View message handlers

void CHomework4View::OnLButtonDown(UINT nFlags, CPoint point) 
{
	//响应鼠标左键，现实“选择映射方式”对话框
	if(IDOK == m_SelStyleDlg.DoModal())
	{
		//将所选内容转换成相应的ID值
		char* SelStr = m_SelStyleDlg.m_SelStyle.GetBuffer(m_SelStyleDlg.m_SelStyle.GetLength());
		if(!strcmp(SelStr, "MM_TEXT"))
			m_SelStyle = MM_TEXT;
		if(!strcmp(SelStr, "MM_LOMETRIC"))
			m_SelStyle = MM_LOMETRIC;
		if(!strcmp(SelStr, "MM_HIMETRIC"))
			m_SelStyle = MM_HIMETRIC;
		if(!strcmp(SelStr, "MM_LOENGLISH"))
			m_SelStyle = MM_LOENGLISH;
		if(!strcmp(SelStr, "MM_HIENGLISH"))
			m_SelStyle = MM_HIENGLISH;
		if(!strcmp(SelStr, "MM_TWIPS"))
			m_SelStyle = MM_TWIPS;
		if(!strcmp(SelStr, "MM_ISOTROPIC"))
			m_SelStyle = MM_ISOTROPIC;
		if(!strcmp(SelStr, "MM_ANISOTROPIC"))
			m_SelStyle = MM_ANISOTROPIC;
		m_ChangeSelStyle = TRUE;
		//刷新窗口
		Invalidate();
	}
	CScrollView::OnLButtonDown(nFlags, point);
}

void CHomework4View::Draw(CDC *pDC)
{
	
	char OutText[100];
	char temp[50];
	//设置文本输出点，按逻辑坐标
	LPPOINT lpPoint = new(CPoint);
	LPPOINT lpTextPos = new(CPoint);//save the position of text
	long YStep = pDC->GetTextExtent("H").cy;
	if(m_WinExt.cy < 0)
		YStep = -1*YStep;

	lpPoint->x = 100;
	lpPoint->y = 100;
	pDC->LPtoDP(lpPoint);
	lpTextPos->x = lpPoint->x;
	lpTextPos->y = lpPoint->y;
	strcpy(OutText, m_SelStyleStr);
	strcat(OutText, m_SelStyleDlg.m_SelStyle);
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_WinOrgStr);
	strcat(OutText, itoa(m_WinOrg.x, temp, 10));
	strcat(OutText, ", ");
	strcat(OutText, itoa(m_WinOrg.y, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_WinExtStr);
	strcat(OutText, itoa(m_WinExt.cx, temp, 10));
	strcat(OutText, ", ");
	strcat(OutText, itoa(m_WinExt.cy, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_ViewOrgStr);
	strcat(OutText, itoa(m_ViewOrg.x, temp, 10));
	strcat(OutText, ", ");
	strcat(OutText, itoa(m_ViewOrg.y, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_ViewExtStr);
	strcat(OutText, itoa(m_ViewExt.cx, temp, 10));
	strcat(OutText, ", ");
	strcat(OutText, itoa(m_ViewExt.cy, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_TextPosStr);
	strcat(OutText, itoa(lpTextPos->x, temp, 10));
	strcat(OutText, ", ");
	strcat(OutText, itoa(lpTextPos->y, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	//获取字体信息
	pDC->GetTextMetrics(&m_Metrics);
	lpPoint->y += YStep;
	strcpy(OutText, m_CharHightStr);
	strcat(OutText, itoa(m_Metrics.tmHeight, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_AveCharWidthStr);
	strcat(OutText, itoa(m_Metrics.tmAveCharWidth, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);

	lpPoint->y += YStep;
	strcpy(OutText, m_MaxCharWidthStr);
	strcat(OutText, itoa(m_Metrics.tmMaxCharWidth, temp, 10));
	pDC->TextOut(lpPoint->x, lpPoint->y, OutText);
}

void CHomework4View::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(NULL);
	CFontDialog dlg(&m_logFont);
	dlg.m_cf.rgbColors = m_Color;
	if (dlg.DoModal() == IDOK)
	{
		m_Color = dlg.GetColor();
		m_Font.DeleteObject();
		m_Font.CreateFontIndirect(dlg.m_cf.lpLogFont);
		Invalidate();
	}

	CScrollView::OnRButtonDown(nFlags, point);
}

BOOL CHomework4View::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) 
{
	Invalidate();
	return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
}
