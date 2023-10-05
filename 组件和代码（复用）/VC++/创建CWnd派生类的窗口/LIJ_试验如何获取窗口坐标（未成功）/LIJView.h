// LIJView.h : interface of the CLIJView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIJVIEW_H__37E4D639_1FBA_4500_9DB0_723CB9C86896__INCLUDED_)
#define AFX_LIJVIEW_H__37E4D639_1FBA_4500_9DB0_723CB9C86896__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CLIJView : public CView
{
protected: // create from serialization only
	CLIJView();
	DECLARE_DYNCREATE(CLIJView)

// Attributes
public:
	CLIJDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLIJView)
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
	virtual ~CLIJView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLIJView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in LIJView.cpp
inline CLIJDoc* CLIJView::GetDocument()
   { return (CLIJDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIJVIEW_H__37E4D639_1FBA_4500_9DB0_723CB9C86896__INCLUDED_)
