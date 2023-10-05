// MyPointView.h : interface of the CMyPointView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPOINTVIEW_H__F13CC959_44C0_11D5_82DA_00E04C3B196D__INCLUDED_)
#define AFX_MYPOINTVIEW_H__F13CC959_44C0_11D5_82DA_00E04C3B196D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMyPointView : public CView
{
protected: // create from serialization only
	CMyPointView();
	DECLARE_DYNCREATE(CMyPointView)

// Attributes
public:
	CMyPointDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPointView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyPointView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMyPointView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in MyPointView.cpp
inline CMyPointDoc* CMyPointView::GetDocument()
   { return (CMyPointDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPOINTVIEW_H__F13CC959_44C0_11D5_82DA_00E04C3B196D__INCLUDED_)
