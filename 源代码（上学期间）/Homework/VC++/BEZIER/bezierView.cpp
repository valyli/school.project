// bezierView.cpp : implementation of the CBezierView class
//

#include "stdafx.h"
#include "bezier.h"

#include "bezierDoc.h"
#include "CntrItem.h"
#include "bezierView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBezierView

IMPLEMENT_DYNCREATE(CBezierView, CView)

BEGIN_MESSAGE_MAP(CBezierView, CView)
	//{{AFX_MSG_MAP(CBezierView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBezierView construction/destruction

CBezierView::CBezierView()
{
	isDBClick = TRUE;
	m_pSelection = NULL;
	// TODO: add construction code here

}

CBezierView::~CBezierView()
{
}

BOOL CBezierView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBezierView drawing

void CBezierView::OnDraw(CDC* pDC)
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_List.GetCount() > 0)
	{
		DrawResult();
	}
	if(pDoc->m_List.GetCount() > 0 && isDBClick == FALSE)
	{
		Drawing();
	}
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CBezierCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CBezierCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, CRect(10, 10, 210, 210));
}

void CBezierView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

/////////////////////////////////////////////////////////////////////////////
// CBezierView printing

BOOL CBezierView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBezierView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBezierView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CBezierView::OnDestroy()
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	POSITION m_Position;
	//释放原链表空间
	for(int i = 0; i < pDoc->m_List.GetCount(); i++)
	{
		m_Position = pDoc->m_List.GetHeadPosition();
		pDoc->m_List.GetAt(m_Position)->RemoveAll();
	}
	pDoc->m_List.RemoveAll();
   CView::OnDestroy();
   COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
   if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
   {
      pActiveItem->Deactivate();
      ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
   }
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CBezierView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CBezierCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CBezierView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CBezierCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CBezierCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CBezierDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CBezierCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);
		
        if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CBezierView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CBezierView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

void CBezierView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}
/////////////////////////////////////////////////////////////////////////////
// CBezierView diagnostics

#ifdef _DEBUG
void CBezierView::AssertValid() const
{
	CView::AssertValid();
}

void CBezierView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBezierDoc* CBezierView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBezierDoc)));
	return (CBezierDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBezierView message handlers

void CBezierView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(isDBClick == TRUE)
	{
		::SetCapture(this->m_hWnd);
		pDoc->m_Temp = new CArrayPoint;
		isDBClick = FALSE;
	}
	m_LastPoint = point;
	pDoc->m_Temp->Add(point);
	Drawing();

	CView::OnLButtonDown(nFlags, point);
}

BOOL CBezierView::Drawing()
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC* pDC = GetDC();
	CPen redPen;
	redPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	CPen greenPen;
	greenPen.CreatePen(PS_DASH, 1, RGB(0, 255, 0));
	POINT* m_lpPoint = (POINT*)malloc(sizeof(POINT) * pDoc->m_Temp->GetSize());
	pDC->MoveTo((POINT)pDoc->m_Temp->GetAt(0));
	for(int i = 0; i < pDoc->m_Temp->GetSize(); i++)
	{
		pDC->SelectObject(&greenPen);
		pDC->LineTo(pDoc->m_Temp->GetAt(i));
		pDC->SelectObject(&redPen);
		pDC->Ellipse(pDoc->m_Temp->GetAt(i).x - 2,
					pDoc->m_Temp->GetAt(i).y - 2,
					pDoc->m_Temp->GetAt(i).x + 2,
					pDoc->m_Temp->GetAt(i).y + 2);
		m_lpPoint[i] = (POINT)pDoc->m_Temp->GetAt(i);
	}

	pDC->PolyBezier(m_lpPoint, pDoc->m_Temp->GetSize());
	return true;
}

void CBezierView::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_Temp->GetSize()%3 != 1)
		return;
	pDoc->m_List.AddHead(pDoc->m_Temp);
	pDoc->SetModifiedFlag();
	isDBClick = TRUE;
	::ReleaseCapture();
	Invalidate();

	CView::OnLButtonDblClk(nFlags, point);
}

BOOL CBezierView::DrawResult()
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC* pDC = GetDC();
	for(int i = 0; i < pDoc->m_List.GetCount(); i++)
	{
		POSITION m_Position = pDoc->m_List.FindIndex(i);
		POINT* m_lpPoint = (POINT*)malloc(sizeof(POINT)
							* (pDoc->m_List.GetAt(m_Position)->GetSize() + 2));
		for(int j = 0; j < pDoc->m_List.GetAt(m_Position)->GetSize(); j++)
		{
			m_lpPoint[j] = (POINT)pDoc->m_List.GetAt(m_Position)->GetAt(j);
		}
		m_lpPoint[pDoc->m_List.GetAt(m_Position)->GetSize()] = (POINT)pDoc->m_List.GetAt(m_Position)->GetAt(0);
		m_lpPoint[pDoc->m_List.GetAt(m_Position)->GetSize() + 1] = (POINT)pDoc->m_List.GetAt(m_Position)->GetAt(0);
		CPen bluePen;
		bluePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		pDC->SelectObject(&bluePen);
		pDC->MoveTo((POINT)pDoc->m_List.GetAt(m_Position)->GetAt(0));
		pDC->PolyBezierTo(m_lpPoint, pDoc->m_List.GetAt(m_Position)->GetSize() + 2);
	}
	return true;
}

void CBezierView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CBezierDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC* pDC = GetDC();
	if(isDBClick == TRUE || pDoc->m_Temp->GetSize() < 1)
		return;
	CPen *OldPen;
	CPen greenPen;
	greenPen.CreatePen(PS_DASH, 1, RGB(0, 255, 0));
	OldPen = pDC->SelectObject(&greenPen);
	pDC->MoveTo((POINT)pDoc->m_Temp->GetAt(pDoc->m_Temp->GetSize() - 1));
	pDC->SetROP2(R2_XORPEN);
	pDC->LineTo(m_LastPoint);
	pDC->MoveTo((POINT)pDoc->m_Temp->GetAt(pDoc->m_Temp->GetSize() - 1));
	m_LastPoint = point;
	pDC->LineTo(m_LastPoint);
	pDC->SelectObject(OldPen);

	CView::OnMouseMove(nFlags, point);
}
