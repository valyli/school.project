// TreeVView.cpp : implementation of the CTreeVView class
//

#include "stdafx.h"
#include "TreeV.h"

#include "TreeVDoc.h"
#include "TreeVView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeVView

IMPLEMENT_DYNCREATE(CTreeVView, CTreeView)

BEGIN_MESSAGE_MAP(CTreeVView, CTreeView)
	//{{AFX_MSG_MAP(CTreeVView)
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndlabeledit)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeVView construction/destruction

CTreeVView::CTreeVView()
{
	// TODO: add construction code here

}

CTreeVView::~CTreeVView()
{
}

BOOL CTreeVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTreeVView drawing

void CTreeVView::OnDraw(CDC* pDC)
{
	CTreeVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CTreeVView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
   //** Declare a shortcut to the tree control
   CTreeCtrl& tree = GetTreeCtrl( );
    
    //** Insert a root level item
    HTREEITEM  hAnimals = tree.InsertItem("Animals");
    
    //** Insert a sub item, the root item is parent
    HTREEITEM hVerts = tree.InsertItem("Vertibrates",hAnimals);
    
    //** Insert sub items, hVerts sub item is parent
    tree.InsertItem("Whales", hVerts, TVI_SORT);
    tree.InsertItem("Dogs", hVerts, TVI_SORT);
    tree.InsertItem("Humans", hVerts, TVI_SORT);
    
    //** Insert a sub item, root item is parent
    HTREEITEM  hInverts =  tree.InsertItem("Inverts");
    
    //** Insert sub items, hInverts sub item is parent
    tree.InsertItem("Jellyfish", hInverts, TVI_SORT);
    tree.InsertItem("Worms", hInverts, TVI_SORT);
    tree.InsertItem("Snails", hInverts, TVI_SORT);
    
    //** Insert a root level item after hAnimals
    HTREEITEM hPlants = 
      tree.InsertItem("Plants", TVI_ROOT, hAnimals);
    
    //** Insert a sub item, root item is parent
    HTREEITEM hFruit = 
       tree.InsertItem("Fruit", hPlants);
    
    //** Insert sub items, hFruit sub item is parent 
    tree.InsertItem("Apples", hFruit, TVI_SORT);
    tree.InsertItem("Plums", hFruit, TVI_SORT);
    tree.InsertItem("Pears", hFruit,TVI_SORT);
    
    //** Insert a sub item, root item is parent
    HTREEITEM hCereal = 
       tree.InsertItem("Cereal", hPlants);
    
    //** Insert sub items, hCereal sub items is parent
    tree.InsertItem("Wheat", hCereal, TVI_SORT);
    tree.InsertItem("Rye", hCereal, TVI_SORT);
    tree.InsertItem("Rice", hCereal, TVI_SORT);
    
    //** Get the current style flags
    DWORD dwStyle = GetWindowLong(GetTreeCtrl( ).GetSafeHwnd( ),GWL_STYLE);
    
    //** Add the List style
    dwStyle |= TVS_HASLINES+TVS_HASBUTTONS+TVS_LINESATROOT+TVS_EDITLABELS;
    SetWindowLong(GetTreeCtrl( ).GetSafeHwnd( ), GWL_STYLE,dwStyle);
    
    //** Redraw the list view
    SetRedraw(TRUE);

}

/////////////////////////////////////////////////////////////////////////////
// CTreeVView printing

BOOL CTreeVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTreeVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTreeVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTreeVView diagnostics

#ifdef _DEBUG
void CTreeVView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTreeVView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTreeVDoc* CTreeVView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTreeVDoc)));
	return (CTreeVDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeVView message handlers

void CTreeVView::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	 GetTreeCtrl( ).GetEditControl( )->LimitText(20);
	*pResult = 0;
}

void CTreeVView::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	    CString strText;
      GetTreeCtrl( ).GetEditControl( )->
                   GetWindowText(strText);
      
      //** Might do some text validation here
      
      //** Check string isn't empty
      if (strText.GetLength( )>0)
      {
           //** Get the selected item handle
           HTREEITEM hSelected = pTVDispInfo->item.hItem;
      
           //** Set the modified text
           GetTreeCtrl( ).SetItemText(hSelected, strText);
      }

	*pResult = 0;
}
