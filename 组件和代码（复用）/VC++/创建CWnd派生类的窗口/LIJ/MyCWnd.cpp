// MyCWnd.cpp : implementation file
//

#include "stdafx.h"
#include "LIJ.h"
#include "MyCWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyCWnd

MyCWnd::MyCWnd()
{
}

MyCWnd::~MyCWnd()
{
}


BEGIN_MESSAGE_MAP(MyCWnd, CWnd)
	//{{AFX_MSG_MAP(MyCWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MyCWnd message handlers

BOOL MyCWnd::Create(CWnd *pParentWnd)
{
	return CreateEx(0,
		AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
		NULL, WS_POPUP | WS_VISIBLE, 0, 0, 640, 480, pParentWnd->GetSafeHwnd(), NULL);
}
