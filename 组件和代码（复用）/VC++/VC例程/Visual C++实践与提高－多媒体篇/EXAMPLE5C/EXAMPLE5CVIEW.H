// Example5CView.h : interface of the CExample5CView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE5CVIEW_H__F4775C94_9A3E_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE5CVIEW_H__F4775C94_9A3E_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample5CView : public CView
{
protected: // create from serialization only
	CExample5CView();
	DECLARE_DYNCREATE(CExample5CView)

// Attributes
public:
	CExample5CDoc* GetDocument();

// Operations
public:
private:
	BOOL m_bCaptured;
	CRect rcRect;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5CView)
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
	virtual ~CExample5CView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample5CView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example5CView.cpp
inline CExample5CDoc* CExample5CView::GetDocument()
   { return (CExample5CDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5CVIEW_H__F4775C94_9A3E_11D4_B67F_444553540000__INCLUDED_)
