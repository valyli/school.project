// Example5AView.h : interface of the CExample5AView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE5AVIEW_H__F4775C6C_9A3E_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE5AVIEW_H__F4775C6C_9A3E_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample5AView : public CView
{
protected: // create from serialization only
	CExample5AView();
	DECLARE_DYNCREATE(CExample5AView)

// Attributes
public:
	CExample5ADoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5AView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExample5AView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_index;
// Generated message map functions
protected:
	//{{AFX_MSG(CExample5AView)
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example5AView.cpp
inline CExample5ADoc* CExample5AView::GetDocument()
   { return (CExample5ADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5AVIEW_H__F4775C6C_9A3E_11D4_B67F_444553540000__INCLUDED_)
