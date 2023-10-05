// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MemView.h"

#include "MainFrm.h"
#include "MemViewDoc.h"
#include "MemViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_CBN_EDITCHANGE  (AFX_IDW_DIALOGBAR, OnNewMemoryAddress)
	ON_CBN_SELCHANGE   (AFX_IDW_DIALOGBAR, OnNewMemoryAddress)
	ON_CBN_CLOSEUP     (AFX_IDW_DIALOGBAR, OnNewMemoryAddress)
	ON_CBN_SELENDOK    (AFX_IDW_DIALOGBAR, OnNewMemoryAddress)
	ON_COMMAND         (IDOK,              OnNewMemoryAddress)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
    */
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		//!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips
	//m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

    HBITMAP hBitmap = ::LoadBitmap( ::AfxGetInstanceHandle(), MAKEINTRESOURCE( IDB_BITMAP_GOTO));
    CWnd* pButton = m_wndDlgBar.GetDlgItem( IDOK);
    if ( pButton) {
        pButton->SendMessage( BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
    }

	return 0;
}

//******************************************************************
//
// Show a memory view by indicating its startup address and length
//
void CMainFrame::OnNewMemoryAddress()
{
    CString AddrStr;
    m_wndDlgBar.GetDlgItemText( IDC_COMBO_ADDRESS, AddrStr);

    CMemViewView* pView = (CMemViewView*)GetActiveView();
    pView->ShowAddress( AddrStr);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

