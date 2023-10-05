// MyWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Example4F.h"
#include "MyWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyWnd

CMyWnd::CMyWnd()
{
	m_prePoint=CPoint(0,0);
}
LPCSTR CMyWnd::lpszClassName=NULL;
CMyWnd::~CMyWnd()
{
}


BEGIN_MESSAGE_MAP(CMyWnd, CWnd)
	//{{AFX_MSG_MAP(CMyWnd)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_SYSKEYDOWN()
	ON_WM_ACTIVATE()
	ON_WM_ACTIVATEAPP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyWnd message handlers

//创建全屏窗口
BOOL CMyWnd::Create()
{
	if(lpszClassName==NULL)
	{
		lpszClassName=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW, 
			::LoadCursor(AfxGetResourceHandle(),MAKEINTRESOURCE(IDC_NOCURSOR)));
		//注册类；IDC_NOCURSOR为新建光标的ID，这个光标没有任何图案
	}
	CRect rect(0, 0, ::GetSystemMetrics(SM_CXSCREEN),::GetSystemMetrics(SM_CYSCREEN));
	CreateEx(WS_EX_TOPMOST, lpszClassName,_T(""), WS_VISIBLE|WS_POPUP, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		GetSafeHwnd(), NULL, NULL); //创建一个全屏窗口
	SetTimer(1, 1500, NULL);//计时器，ID_TIMER别忘了定义//ID_TIMER
	return TRUE;
}


//计数器函数
void CMyWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	static nIndexBit=0;
	if(nIndexBit>3)
		nIndexBit=0;
	DrawBitmap(dc, nIndexBit++);
	
	CWnd::OnTimer(nIDEvent);
}
//绘制位图
void CMyWnd::DrawBitmap(CDC& dc, int nIndexBit)
{
	CRect rect;
	GetClientRect(rect);
	CDC dcmem;
	dcmem.CreateCompatibleDC(&dc);
	CBitmap m_Bitmap;
	m_Bitmap.LoadBitmap(IDB_BITMAP1+nIndexBit);
	dcmem.SelectObject(m_Bitmap);
	dc.BitBlt(0.5*rect.right-150, 0.5*rect.bottom-225,300,450,&dcmem,0,0,SRCCOPY);
}

void CMyWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CBrush brush(RGB(0,0,0));
	CRect rect;
	GetClientRect(rect);
	dc.FillRect(&rect, &brush);	
	// Do not call CWnd::OnPaint() for painting messages
}

void CMyWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE);	
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMyWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE);	
	CWnd::OnLButtonDown(nFlags, point);
}

void CMyWnd::OnMButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE);	
	CWnd::OnMButtonDown(nFlags, point);
}

void CMyWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_prePoint == CPoint(0,0))
		m_prePoint = point;
	else if(m_prePoint!=point)
		PostMessage(WM_CLOSE);
	
	CWnd::OnMouseMove(nFlags, point);
}

void CMyWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE);	
	CWnd::OnRButtonDown(nFlags, point);
}

void CMyWnd::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	PostMessage(WM_CLOSE);	
	CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}

void CMyWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
	if (nState==WA_INACTIVE)
		PostMessage(WM_CLOSE);	
}

void CMyWnd::OnActivateApp(BOOL bActive, HTASK hTask) 
{
	CWnd::OnActivateApp(bActive, hTask);
	
	// TODO: Add your message handler code here
	if (!bActive) 
		PostMessage(WM_CLOSE);
}
