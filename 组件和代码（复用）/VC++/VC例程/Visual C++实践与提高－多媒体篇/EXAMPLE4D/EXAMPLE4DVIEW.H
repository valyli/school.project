// Example4DView.h : interface of the CExample4DView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE4DVIEW_H__6221E26C_A50E_11D4_B71C_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4DVIEW_H__6221E26C_A50E_11D4_B71C_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dib.h"

class CExample4DView : public CView
{
protected: // create from serialization only
	CExample4DView();
	DECLARE_DYNCREATE(CExample4DView)

// Attributes
public:
	CExample4DDoc* GetDocument();

// Operations
public:
	CDib m_dib;
	int nOption;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4DView)
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
	virtual ~CExample4DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample4DView)
	afx_msg void OnFileOpen();
	afx_msg void OnEffectMasic();
	afx_msg void OnEffectMove();
	afx_msg void OnEffectSweep();
	afx_msg void OnEffectGrid();
	afx_msg void OnEffectWindow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example4DView.cpp
inline CExample4DDoc* CExample4DView::GetDocument()
   { return (CExample4DDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4DVIEW_H__6221E26C_A50E_11D4_B71C_0000B48A052A__INCLUDED_)
