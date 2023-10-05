// MyWnd.cpp : implementation file
//

#include "stdafx.h"
#include "LIJ.h"
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
}

CMyWnd::~CMyWnd()
{
}


BEGIN_MESSAGE_MAP(CMyWnd, CWnd)
	//{{AFX_MSG_MAP(CMyWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyWnd message handlers

BOOL CMyWnd::Create(CWnd *pParentWnd)
{
	CBrush hbrBackground;
	hbrBackground.CreateSolidBrush(RGB(255, 0, 0));
	RECT rc;
	pParentWnd->GetWindowRect(&rc);
//	pParentWnd->ClientToScreen(&rc);
	BOOL flag = CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW), (HBRUSH)(hbrBackground)),
		NULL,
		WS_CHILD | WS_VISIBLE, 
		rc.left, rc.top, rc.right, rc.bottom, /*0, 0, 640, 480,*/
		pParentWnd->GetSafeHwnd(), NULL);


	rc.left = 100;
	rc.right = 200;
	rc.top = 100;
	rc.bottom = 200;
//	pParentWnd->ClientToScreen(&rc);
	m_b.Create(_T("My button"), WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, 
	rc, pParentWnd, 1);
	m_b.ShowWindow(SW_SHOW);
	UpdateData(TRUE);

	return flag;
}

void CMyWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	::MessageBeep(MB_OK);
	CWnd::OnLButtonDown(nFlags, point);
}

void CMyWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT rc;
	GetWindowRect(&rc);
	dc.Rectangle(&rc);
	CString a;
	a= "asdfasdf";
	dc.TextOut(0, 0, a);
	
	// Do not call CWnd::OnPaint() for painting messages
}
