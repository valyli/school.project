// Example4CView.h : interface of the CExample4CView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXAMPLE4CVIEW_H__B78C5931_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4CVIEW_H__B78C5931_A852_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExample4CView : public CView
{

protected:
	CPalette m_Palette;
	LPLOGPALETTE m_pLP;
	void FillPalette();

protected: // create from serialization only
	CExample4CView();
	DECLARE_DYNCREATE(CExample4CView)

// Attributes
public:
	CExample4CDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4CView)
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
	virtual ~CExample4CView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExample4CView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	afx_msg LRESULT OnDoRealize(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Example4CView.cpp
inline CExample4CDoc* CExample4CView::GetDocument()
   { return (CExample4CDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4CVIEW_H__B78C5931_A852_11D4_8EAF_0000B48A052A__INCLUDED_)
