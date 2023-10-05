// StatusMouseView.h : interface of the CStatusMouseView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_STATUSMOUSEVIEW_H__44E6900D_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_)
#define AFX_STATUSMOUSEVIEW_H__44E6900D_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CStatusMouseView : public CView
{
protected: // create from serialization only
	CStatusMouseView();
	DECLARE_DYNCREATE(CStatusMouseView)

// Attributes
public:
	CStatusMouseDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatusMouseView)
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
	virtual ~CStatusMouseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CStatusMouseView)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in StatusMouseView.cpp
inline CStatusMouseDoc* CStatusMouseView::GetDocument()
   { return (CStatusMouseDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATUSMOUSEVIEW_H__44E6900D_5A1C_11D1_B5D9_F41150DD6517__INCLUDED_)
