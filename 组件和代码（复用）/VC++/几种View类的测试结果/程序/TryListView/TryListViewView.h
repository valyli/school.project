// TryListViewView.h : interface of the CTryListViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRYLISTVIEWVIEW_H__BE837386_87AC_4D08_A675_540D0A7ABEC2__INCLUDED_)
#define AFX_TRYLISTVIEWVIEW_H__BE837386_87AC_4D08_A675_540D0A7ABEC2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTryListViewView : public CListView
{
protected: // create from serialization only
	CTryListViewView();
	DECLARE_DYNCREATE(CTryListViewView)

// Attributes
public:
	CTryListViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTryListViewView)
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
	CButton m1;
	CButton m2;
	CButton m3;
	virtual ~CTryListViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTryListViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TryListViewView.cpp
inline CTryListViewDoc* CTryListViewView::GetDocument()
   { return (CTryListViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYLISTVIEWVIEW_H__BE837386_87AC_4D08_A675_540D0A7ABEC2__INCLUDED_)
