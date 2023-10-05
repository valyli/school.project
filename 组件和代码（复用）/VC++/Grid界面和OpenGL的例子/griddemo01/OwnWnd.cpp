// OwnWnd.cpp : implementation file
//

#include "stdafx.h"
#include "Ö÷¿Ø±¨±í.h"
#include "OwnWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COwnWnd

IMPLEMENT_DYNCREATE(COwnWnd, CView)

COwnWnd::COwnWnd()
{
	RegistryWindow();
}

COwnWnd::~COwnWnd()
{
	
}


BEGIN_MESSAGE_MAP(COwnWnd, CView)
	//{{AFX_MSG_MAP(COwnWnd)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COwnWnd drawing

void COwnWnd::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	m_hzgl.Render();
	
}

/////////////////////////////////////////////////////////////////////////////
// COwnWnd diagnostics

#ifdef _DEBUG
void COwnWnd::AssertValid() const
{
	CView::AssertValid();
}

void COwnWnd::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COwnWnd message handlers

void COwnWnd::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	m_hzgl.OnResize(cx,cy);
	
}

int COwnWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	BOOL Result=m_hzgl.Create(this);
	if(Result)
	   {
		SetTimer(100,100,NULL);
		return 0;
	}
	else 
		return -1;
}

BOOL COwnWnd::RegistryWindow()
{

	
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();
   // HINSTANCE hInst = AfxGetResourceHandle(); 

    if (!(::GetClassInfo(hInst,"ownWndClass" , &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
        wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = "ownWndClass";

        if (!AfxRegisterClass(&wndcls)) {
            AfxThrowResourceException();
            return FALSE;
        }
    }

    return TRUE;


}

void COwnWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	OnDraw(&dc);
	// Do not call CView::OnPaint() for painting messages
}

BOOL COwnWnd::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

BOOL COwnWnd::Create(const RECT &rect, CWnd *parent, UINT nID, DWORD dwStyle)
{

	ASSERT(parent->GetSafeHwnd());

    if (!CWnd::Create("ownWndClass", NULL, dwStyle, rect, parent, nID)) 
        return FALSE;//

	return TRUE;

}

void COwnWnd::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	Invalidate();
	//CView::OnTimer(nIDEvent);
}

void COwnWnd::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class

	CView::PostNcDestroy();
}

BOOL COwnWnd::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
		KillTimer(100);
	return CView::DestroyWindow();
}
