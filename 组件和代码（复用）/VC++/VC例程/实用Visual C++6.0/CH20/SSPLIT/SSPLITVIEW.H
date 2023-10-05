// SSplitView.h : interface of the CSSplitView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SSPLITVIEW_H__0C15E2A7_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
#define AFX_SSPLITVIEW_H__0C15E2A7_D487_11D2_BF13_87F5B9EBB265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class  CSSplitDoc; 
class CSSplitView : public CEditView
{
protected: // create from serialization only
	CSSplitView();
	DECLARE_DYNCREATE(CSSplitView)

// Attributes
public:
	CSSplitDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSSplitView)
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
	virtual ~CSSplitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSSplitView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SSplitView.cpp
inline CSSplitDoc* CSSplitView::GetDocument()
   { return (CSSplitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSPLITVIEW_H__0C15E2A7_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
