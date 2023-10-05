// Example5FView.h : interface of the CExample5FView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE5FVIEW_H__64646F4C_9D82_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE5FVIEW_H__64646F4C_9D82_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mci.h"
class CExample5FView : public CView
{
protected: // create from serialization only
	CExample5FView();
	DECLARE_DYNCREATE(CExample5FView)

// Attributes
public:
	CExample5FDoc* GetDocument();

// Operations
public:
Cmci* m_pMci;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample5FView)
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
	virtual ~CExample5FView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample5FView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example5FView.cpp
inline CExample5FDoc* CExample5FView::GetDocument()
   { return (CExample5FDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE5FVIEW_H__64646F4C_9D82_11D4_B67F_444553540000__INCLUDED_)
