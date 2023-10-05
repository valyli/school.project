// TreeVView.h : interface of the CTreeVView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREEVVIEW_H__98AE21AF_A463_11CF_BC51_BAE7D2415650__INCLUDED_)
#define AFX_TREEVVIEW_H__98AE21AF_A463_11CF_BC51_BAE7D2415650__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CTreeVView : public CTreeView
{
protected: // create from serialization only
	CTreeVView();
	DECLARE_DYNCREATE(CTreeVView)

// Attributes
public:
	CTreeVDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeVView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeVView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTreeVView)
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TreeVView.cpp
inline CTreeVDoc* CTreeVView::GetDocument()
   { return (CTreeVDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEVVIEW_H__98AE21AF_A463_11CF_BC51_BAE7D2415650__INCLUDED_)
