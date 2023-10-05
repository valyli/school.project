// DsplitView.h : interface of the CDsplitView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSPLITVIEW_H__0C15E28D_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
#define AFX_DSPLITVIEW_H__0C15E28D_D487_11D2_BF13_87F5B9EBB265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDsplitView : public CScrollView
{
protected: // create from serialization only
	CDsplitView();
	DECLARE_DYNCREATE(CDsplitView)

// Attributes
public:
	CDsplitDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDsplitView)
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
	virtual ~CDsplitView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDsplitView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DsplitView.cpp
inline CDsplitDoc* CDsplitView::GetDocument()
   { return (CDsplitDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPLITVIEW_H__0C15E28D_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
