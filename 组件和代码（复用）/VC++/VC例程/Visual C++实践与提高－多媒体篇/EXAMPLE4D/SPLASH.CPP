// CG: This file was added by the Splash Screen component.
// Splash.cpp : implementation file
//

#include "stdafx.h"  // e. g. stdafx.h
#include "resource.h"  // e.g. resource.h

#include "Splash.h"  // e.g. splash.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#define	 TITLECOLOR    RGB(0,0,255)//默认标题颜色
#define  CONTENTCOLOR  RGB(0,255,255)//默认说明文字颜色
#define  FONTSIZE0  15 	//默认字号
/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class

BOOL CSplashWnd::c_bShowSplashWnd;
CSplashWnd* CSplashWnd::c_pSplashWnd;
CSplashWnd::CSplashWnd()
{
	m_nCurPos = 50 ;
}

CSplashWnd::~CSplashWnd()
{
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/)
{
	if (!c_bShowSplashWnd || c_pSplashWnd != NULL)
		return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CSplashWnd;
	if (!c_pSplashWnd->Create(pParentWnd))
		delete c_pSplashWnd;
	else
		c_pSplashWnd->UpdateWindow();
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

BOOL CSplashWnd::Create(CWnd* pParentWnd /*= NULL*/)
{
	if (!m_bitmap.LoadBitmap(IDB_SPLASH))
		return FALSE;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	//拷贝矩形区域到m_TextRect,作为滚动文字的显示区域
	m_TextRect.CopyRect(&CRect(50,100,200,200));
	
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);
}

void CSplashWnd::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();
	AfxGetMainWnd()->UpdateWindow();
}

void CSplashWnd::PostNcDestroy()
{
	// Free the C++ class.
	m_dcImage.SelectObject(m_pOldBitmap);
	m_dcText.SelectClipRgn(NULL);
	m_dcText.SelectObject(m_pOldBitmapText);
	m_bitmap.DeleteObject();
	m_rgn.DeleteObject();
	delete this;

	CWnd::PostNcDestroy();
}



void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	static BOOL bFirst = TRUE;//指示是否第一次绘制窗口
	if(bFirst)
	{
		if (!m_dcImage.CreateCompatibleDC(&dc))
			return;
		m_pOldBitmap = m_dcImage.SelectObject(&m_bitmap);
		if (!m_dcText.CreateCompatibleDC(&dc))
			return;
		m_pBitmap = new CBitmap ;
		int nBitCount = m_dcText.GetDeviceCaps(BITSPIXEL);
		m_pBitmap->CreateBitmap(bm.bmWidth,bm.bmHeight,1,nBitCount,NULL);
		m_pOldBitmapText = m_dcText.SelectObject(m_pBitmap);
		m_rgn.CreateRectRgn(m_TextRect.left,m_TextRect.top,m_TextRect.right,m_TextRect.bottom);
		bFirst = FALSE;
	}
	m_dcText.SelectClipRgn(NULL);
	m_dcText.BitBlt(0, 0, bm.bmWidth,bm.bmHeight,&m_dcImage, 0, 0, SRCCOPY);
	m_dcText.SelectClipRgn(&m_rgn);
	int nBasex = m_TextRect.left ; 
	int nBasey = m_TextRect.bottom-m_nCurPos; 
	int nMidx = m_TextRect.left + m_TextRect.Width()/2 ;

    DrawText(&m_dcText,nMidx,nBasey, 1,"楷体_GB2312", FONTSIZE0+5,TITLECOLOR,"曾经");
	DrawText(&m_dcText,nMidx,nBasey+30, 1,"楷体_GB2312", FONTSIZE0,CONTENTCOLOR,"有一份真诚的爱情");
	DrawText(&m_dcText,nMidx,nBasey+50, 1,"楷体_GB2312", FONTSIZE0,TITLECOLOR,"摆在我的面前");
	DrawText(&m_dcText,nMidx,nBasey+70, 1,"楷体_GB2312", FONTSIZE0,CONTENTCOLOR,"可是...");
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight,&m_dcText, 0,0, SRCCOPY);
}


void CSplashWnd::OnTimer(UINT nIDEvent)
{
	// Destroy the splash screen window.
	m_nCurPos++;
	if( m_nCurPos>=250 )
	{
		m_nCurPos = 0 ;
	}
	Invalidate(TRUE);
	//	HideSplashScreen();
}
///////////////////////////////////////////////////////////
//参数说明:
		//pDC:内存设备上下文，x,y:文字位置，nAlign:对齐方式
		//sFontName:字体，nBaseSize:字体高度，
		//crTextColor:文字颜色，strText：正文
///////////////////////////////////////////////////////////
void CSplashWnd::DrawText(CDC *pDC,
		int x, int y, int nAlign,
		CString sFontName, int nBaseSize,
		COLORREF crTextColor, CString strText)
{
	LOGFONT lf;//字体
	lf.lfHeight = nBaseSize ;//字号
	lf.lfEscapement =0;//角度
	lf.lfItalic = 0 ;//倾斜
	lf.lfUnderline = 0 ;//下划线
	lf.lfStrikeOut=0;//删除线
  	lf.lfCharSet = DEFAULT_CHARSET ;//字符集
	strcpy(lf.lfFaceName,sFontName.GetBuffer(sFontName.GetLength()));

	CFont font ;
	font.CreateFontIndirect(&lf);
	CFont *pOldFont = (CFont*)pDC->SelectObject(&font);
	UINT oldAlign,uAlign ;
	switch(nAlign)
	{
		case 0:
			uAlign = TA_LEFT | TA_TOP ; 
			break;
		case 1:
			uAlign = TA_CENTER | TA_TOP; 
			break;
		case 2: 
			uAlign = TA_RIGHT  | TA_TOP ; 
			break; 
		default: 
			uAlign = TA_LEFT | TA_TOP ; 
			break;
	}
	oldAlign = pDC->SetTextAlign(uAlign);
	int  oldMode =  pDC->SetBkMode(TRANSPARENT);
	int  oldColor = pDC->SetTextColor(crTextColor) ;
	pDC->TextOut(x,y,strText);

	pDC->SetTextColor(oldColor) ;
	pDC->SetTextAlign(oldAlign);
	pDC->SetBkMode(oldMode);
	pDC->SelectObject(pOldFont);
	font.DeleteObject();
}

int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	CenterWindow();
	SetTimer(1, 10, NULL);	
	return 0;
}
