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
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyWnd message handlers

BOOL CMyWnd::Create(CWnd *pParentWnd)
{
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, 640, 480, pParentWnd->GetSafeHwnd(), NULL);
}
