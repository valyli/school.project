// Exmaple4AView.h : interface of the CExmaple4AView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXMAPLE4AVIEW_H__E7CCDF82_9158_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXMAPLE4AVIEW_H__E7CCDF82_9158_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExmaple4AView : public CView
{
protected: // create from serialization only
	CExmaple4AView();
	DECLARE_DYNCREATE(CExmaple4AView)

// Attributes
public:
	CExmaple4ADoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExmaple4AView)
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
	virtual ~CExmaple4AView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExmaple4AView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Exmaple4AView.cpp
inline CExmaple4ADoc* CExmaple4AView::GetDocument()
   { return (CExmaple4ADoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXMAPLE4AVIEW_H__E7CCDF82_9158_11D4_B67F_444553540000__INCLUDED_)
