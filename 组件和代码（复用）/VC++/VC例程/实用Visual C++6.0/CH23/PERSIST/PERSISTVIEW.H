// PersistView.h : interface of the CPersistView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PERSISTVIEW_H__0E266271_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_)
#define AFX_PERSISTVIEW_H__0E266271_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPersistView : public CView
{
protected: // create from serialization only
	CPersistView();
	DECLARE_DYNCREATE(CPersistView)

// Attributes
public:
	CPersistDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersistView)
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
	virtual ~CPersistView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPersistView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PersistView.cpp
inline CPersistDoc* CPersistView::GetDocument()
   { return (CPersistDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSISTVIEW_H__0E266271_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_)
