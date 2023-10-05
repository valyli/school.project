// ListVView.cpp : implementation of the CListVView class
//

#include "stdafx.h"
#include "ListV.h"

#include "ListVDoc.h"
#include "ListVView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListVView

IMPLEMENT_DYNCREATE(CListVView, CListView)

BEGIN_MESSAGE_MAP(CListVView, CListView)
	//{{AFX_MSG_MAP(CListVView)
	ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListVView construction/destruction

CListVView::CListVView()
{
	// TODO: add construction code here

}

CListVView::~CListVView()
{
}

BOOL CListVView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CListVView drawing

void CListVView::OnDraw(CDC* pDC)
{
	CListVDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CListVView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
    //**Get a pointer to the document 
    CListVDoc* pDoc = GetDocument( );
    //**make sure it is a valid document
    ASSERT_VALID(pDoc);
     
      GetListCtrl( ).InsertColumn(0, "Element Name",
                             LVCFMT_LEFT,120);
      GetListCtrl( ).InsertColumn(1,"Symbol",
                            LVCFMT_CENTER,70);
      GetListCtrl( ).InsertColumn(2,"Atomic Number",
                            LVCFMT_RIGHT,130);
      
      //Get a pointer to the document
      
      //Find the head position of the string list
      POSITION pos =
           pDoc->GetElements( ).GetHeadPosition( );
      
      // While the position is not NULL, add elements
      while (pos)
      {
      	//Get the next element in the list
    		CString strElement =
  			pDoc->GetElements( ).GetNext(pos);
      
    		// ** Find the name part of the string 
         CString strName =
  			strElement.Left(strElement.Find(",")+1);
      
  		//** Find the sombol & Number part
   		CString strSymbol =
  			strElement.Mid(strElement.Find(",")+1);
//      注释：这部分代码作用是将字符串中用逗号分开的不同元素分离出来，以显示在不同的栏目中。
  		//** Find the atomic number part
  		CString strAtomicNumber =
  			strSymbol.Mid(strSymbol.Find(",")+1);
      
      	//** Cut the atomic number from the end 
  		strSymbol =
  			strSymbol.Left(strSymbol.Find(",")+1);
       
      	//** Insert it into the list view at 0
    		GetListCtrl( ).InsertItem(0,strName);
      
   		//** Set the second column text to the symbol
         GetListCtrl().SetItemText(0,1,strSymbol);
  		
  		//** Set the third column text to the symbol
        		GetListCtrl( ).SetItemText(0,2,
  						strAtomicNumber);
      
  	}
     
  	 // Get the current style flags
      DWORD dwStyle =
      	GetWindowLong(GetListCtrl( ).GetSafeHwnd( ),
                                    GWL_STYLE);
      
      //Remove the current style flags
      dwStyle &= -LVS_TYPEMASK;
      
      //** Add the List style
      dwStyle |= LVS_REPORT;
//71      注释：LVS_REPORT样式使得我们可以将可变大小的栏目头加到List视图中。
      // Set it back into the list view
      SetWindowLong(GetListCtrl( ).GetSafeHwnd( ),
                            GWL_STYLE,dwStyle);
      
      //Redraw the list view
      SetRedraw(TRUE);
  

}

/////////////////////////////////////////////////////////////////////////////
// CListVView printing

BOOL CListVView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CListVView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CListVView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CListVView diagnostics

#ifdef _DEBUG
void CListVView::AssertValid() const
{
	CListView::AssertValid();
}

void CListVView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CListVDoc* CListVView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CListVDoc)));
	return (CListVDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CListVView message handlers

void CListVView::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
	   //** String to hold selected items
      CString strSelectedItems;
      
      //** Initial GetNextItem( ) index must be zero 
      int nSelected = -1;
      do 
      {
           //** Find the next selected item
           nSelected = GetListCtrl( ).GetNextItem( 
                       nSelected, LVNI_SELECTED);
           //** Is there a selected item
           if (nSelected != -1)
           {
                //** Add its text to the list
                strSelectedItems += " "+                    GetListCtrl( ).GetItemText(nSelected,0);
           }
      } while (nSelected != -1);
      
      //** Set the document title to the selected items
      GetDocument( )->SetTitle(
            "Selected:" + strSelectedItems);

}
