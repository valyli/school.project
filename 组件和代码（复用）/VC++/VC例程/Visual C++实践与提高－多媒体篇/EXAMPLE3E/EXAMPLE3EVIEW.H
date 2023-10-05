// Example3EView.h : interface of the CExample3EView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE3EVIEW_H__134B4B8C_7459_11D4_ABC8_C73FB0673F59__INCLUDED_)
#define AFX_EXAMPLE3EVIEW_H__134B4B8C_7459_11D4_ABC8_C73FB0673F59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample3EView : public CView
{
protected: // create from serialization only
	CExample3EView();
	DECLARE_DYNCREATE(CExample3EView)
//New add variable
public:
	CFont m_font;
//End add

// Attributes
public:
	CExample3EDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3EView)
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
	virtual ~CExample3EView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample3EView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example3EView.cpp
inline CExample3EDoc* CExample3EView::GetDocument()
   { return (CExample3EDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3EVIEW_H__134B4B8C_7459_11D4_ABC8_C73FB0673F59__INCLUDED_)
