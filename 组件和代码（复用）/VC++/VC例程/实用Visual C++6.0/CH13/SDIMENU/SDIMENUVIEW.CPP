// sdimenuView.cpp : implementation of the CSdimenuView class
//

#include "stdafx.h"
#include "sdimenu.h"

#include "sdimenuDoc.h"
#include "sdimenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ID_MENU_RED    5001
#define ID_MENU_GREEN  5002
#define ID_MENU_BLUE   5003
#define ID_MENU_YELLOW 5004

/////////////////////////////////////////////////////////////////////////////
// CSdimenuView

IMPLEMENT_DYNCREATE(CSdimenuView, CView)

BEGIN_MESSAGE_MAP(CSdimenuView, CView)
	//{{AFX_MSG_MAP(CSdimenuView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CONTEXT_ITEM1, OnMypopupmenuNorth)
	ON_UPDATE_COMMAND_UI(ID_CONTEXT_ITEM1, OnUpdateMypopupmenuNorth)
	ON_COMMAND(ID_MENU_YELLOW,OnYellow)	
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSdimenuView construction/destruction

CSdimenuView::CSdimenuView()
{
	// TODO: add construction code here

}

CSdimenuView::~CSdimenuView()
{
}

BOOL CSdimenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSdimenuView drawing

void CSdimenuView::OnDraw(CDC* pDC)
{
	CSdimenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CSdimenuView printing

BOOL CSdimenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSdimenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSdimenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CSdimenuView diagnostics

#ifdef _DEBUG
void CSdimenuView::AssertValid() const
{
	CView::AssertValid();
}

void CSdimenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSdimenuDoc* CSdimenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSdimenuDoc)));
	return (CSdimenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSdimenuView message handlers


void CSdimenuView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	//  Declare a CMenu object
	CMenu menuPopup;

	//  Create the pop-up menu resoucre
	if (menuPopup.CreatePopupMenu())
	{
		// Add simple menu items 
		menuPopup.AppendMenu(MF_STRING,ID_MENU_RED,"&Red");

		// Insert an item at the top of the menu
		menuPopup.InsertMenu(0,MF_BYPOSITION | MF_STRING,
			                 ID_MENU_GREEN,"&Green");


		menuPopup.AppendMenu(MF_SEPARATOR);

		// Add a checked item
		menuPopup.AppendMenu(MF_STRING | MF_CHECKED,
							 ID_MENU_BLUE,"&Blue");

		// MF_MENUBARBREAK
		menuPopup.AppendMenu(MF_STRING | MF_MENUBARBREAK,
							 ID_MENU_YELLOW,"&Yellow");
menuPopup.ModifyMenu( ID_MENU_YELLOW, 
MF_BYCOMMAND | MF_CHECKED | MF_STRING | MF_MENUBARBREAK,
ID_MENU_YELLOW, "&Yellow");

		menuPopup.TrackPopupMenu(TPM_LEFTALIGN,
								 point.x,point.y,this);
	}
	// ** Initialize with the context menu resource
//	menuPopu p.LoadMenu(IDR_MYCONTEXT);

	// ** Display and start tracking the new menu
//	menuPopup.GetSubMenu(0)->TrackPopupMenu
//		(TPM_LEFTALIGN,point.x,point.y,this);
}

void CSdimenuView::OnMypopupmenuNorth() 
{
	AfxMessageBox("North");
}

void CSdimenuView::OnUpdateMypopupmenuNorth(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(TRUE); 	
}

void CSdimenuView::OnYellow( )
{
	AfxMessageBox("Yellow");
}