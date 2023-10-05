// ListCtrlEx.cpp : implementation file
//

#include "stdafx.h"
#include "processkiller.h"
#include "ListCtrlEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx

CListCtrlEx::CListCtrlEx()
{
}

CListCtrlEx::~CListCtrlEx()
{
}


BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
	ON_WM_CONTEXTMENU()
	//{{AFX_MSG_MAP(CListCtrlEx)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx message handlers

void CListCtrlEx::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

//DEL void CListCtrlEx::OnItemclick(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
//DEL 	// TODO: Add your control notification handler code here
//DEL 	
//DEL 	*pResult = 0;
//DEL }

//DEL void CListCtrlEx::OnLButtonDown(UINT nFlags, CPoint point) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	CListCtrl::OnLButtonDown(nFlags, point);
//DEL }

//DEL void CListCtrlEx::OnNcLButtonDown(UINT nHitTest, CPoint point) 
//DEL {
//DEL 	// TODO: Add your message handler code here and/or call default
//DEL 	
//DEL 	CListCtrl::OnNcLButtonDown(nHitTest, point);
//DEL }

#include "resource.h"
void CListCtrlEx::OnContextMenu(CWnd*, CPoint point)
{

	// CG: This block was added by the Pop-up Menu component
	{
		if (point.x == -1 && point.y == -1){
			//keystroke invocation
			CRect rect;
			GetClientRect(rect);
			ClientToScreen(rect);

			point = rect.TopLeft();
			point.Offset(5, 5);
		}

		CMenu menu;
		VERIFY(menu.LoadMenu(POPMENU_LIST_CTRL_EX));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);
		CWnd* pWndPopupOwner = this;

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);
	}
}

//DEL void CListCtrlEx::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
//DEL {
//DEL 	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
//DEL 	// TODO: Add your control notification handler code here
//DEL 	//pNMListView->iItem;
//DEL 	*pResult = 0;
//DEL }
