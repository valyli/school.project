// dlgbarView.h : interface of the CDlgbarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGBARVIEW_H__E9683ECF_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_)
#define AFX_DLGBARVIEW_H__E9683ECF_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDlgbarView : public CView
{
protected: // create from serialization only
	CDlgbarView();
	DECLARE_DYNCREATE(CDlgbarView)

// Attributes
public:
	CDlgbarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgbarView)
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
	int m_nColor;
	virtual ~CDlgbarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDlgbarView)
	afx_msg void ApplyColor();
	afx_msg void ColorChange();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in dlgbarView.cpp
inline CDlgbarDoc* CDlgbarView::GetDocument()
   { return (CDlgbarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBARVIEW_H__E9683ECF_59B9_11D1_B5D9_BC53D39E0517__INCLUDED_)
