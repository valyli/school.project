// MemViewView.cpp : implementation of the CMemViewView class
//

#include "stdafx.h"
#include "MemView.h"

#include "MemViewDoc.h"
#include "MemViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMemViewView

IMPLEMENT_DYNCREATE(CMemViewView, CView)

BEGIN_MESSAGE_MAP(CMemViewView, CView)
	//{{AFX_MSG_MAP(CMemViewView)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMemViewView construction/destruction

CMemViewView::CMemViewView()
{
}

CMemViewView::~CMemViewView()
{
}

//**************************************************************************
//
// Show memory in the bianry display window
//
void CMemViewView::ShowAddress(LPCTSTR MemAddr, LPCTSTR AddrLen)
{
    char *endptr = NULL;
    DWORD ptr = strtoul( MemAddr, &endptr, 16);
    DWORD Len = strtoul( AddrLen, &endptr, 16);

    ShowAddress( (LPBYTE)ptr, Len);
}

//**************************************************************************
//
void CMemViewView::ShowAddress(LPBYTE MemAddr, UINT AddrLen)
{
    if ( m_BWnd.SetDataPtr( MemAddr, AddrLen)) {
        m_BWnd.SetScrollPos( SB_VERT, 0);
        m_BWnd.SetScrollPos( SB_HORZ, 0);
        m_BWnd.Invalidate();
    }
}

/////////////////////////////////////////////////////////////////////////////
// CMemViewView drawing

void CMemViewView::OnDraw(CDC* pDC)
{
}
/////////////////////////////////////////////////////////////////////////////
// CMemViewView message handlers
//**************************************************************************
//
// Add the binary display window
//
void CMemViewView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
    CRect ClientR;
    GetClientRect( ClientR);
    m_BWnd.Create( WS_CHILD|WS_VISIBLE, ClientR, this);
    m_BWnd.SetEndless( TRUE);
    ShowAddress( (LPBYTE)0X00400000);
}

//**************************************************************************
//
// Resize the binary display window while the view is resizing.
//
void CMemViewView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

    if ( !::IsWindow( m_BWnd.m_hWnd)) return;
    m_BWnd.SetWindowPos( NULL, 0, 0, cx, cy, SWP_NOZORDER|SWP_NOMOVE|SWP_SHOWWINDOW);
}
//**************************************************************************
//
