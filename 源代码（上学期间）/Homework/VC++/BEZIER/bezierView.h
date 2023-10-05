// bezierView.h : interface of the CBezierView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEZIERVIEW_H__9AEB0D3C_4547_49BE_B8F5_1F490B0732DB__INCLUDED_)
#define AFX_BEZIERVIEW_H__9AEB0D3C_4547_49BE_B8F5_1F490B0732DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBezierCntrItem;

class CBezierView : public CView
{
protected: // create from serialization only
	CBezierView();
	DECLARE_DYNCREATE(CBezierView)

// Attributes
public:
	CBezierDoc* GetDocument();
	// m_pSelection holds the selection to the current CBezierCntrItem.
	// For many applications, such a member variable isn't adequate to
	//  represent a selection, such as a multiple selection or a selection
	//  of objects that are not CBezierCntrItem objects.  This selection
	//  mechanism is provided just to help you get started.

	// TODO: replace this selection mechanism with one appropriate to your app.
	CBezierCntrItem* m_pSelection;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBezierView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual BOOL IsSelected(const CObject* pDocItem) const;// Container support
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL DrawResult();
	BOOL isDBClick;
	CPoint m_LastPoint;
	BOOL Drawing();
	virtual ~CBezierView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBezierView)
	afx_msg void OnDestroy();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInsertObject();
	afx_msg void OnCancelEditCntr();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in bezierView.cpp
inline CBezierDoc* CBezierView::GetDocument()
   { return (CBezierDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEZIERVIEW_H__9AEB0D3C_4547_49BE_B8F5_1F490B0732DB__INCLUDED_)
