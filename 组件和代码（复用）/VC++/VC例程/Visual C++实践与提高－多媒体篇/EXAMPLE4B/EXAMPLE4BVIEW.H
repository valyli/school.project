// Example4BView.h : interface of the CExample4BView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE4BVIEW_H__B78C590C_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4BVIEW_H__B78C590C_A852_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Dib.h"

class CExample4BView : public CView
{
protected: // create from serialization only
	CExample4BView();
	DECLARE_DYNCREATE(CExample4BView)

// Attributes
public:
	CExample4BDoc* GetDocument();
public:
	CDib m_dib;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4BView)
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
	virtual ~CExample4BView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample4BView)
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example4BView.cpp
inline CExample4BDoc* CExample4BView::GetDocument()
   { return (CExample4BDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4BVIEW_H__B78C590C_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
