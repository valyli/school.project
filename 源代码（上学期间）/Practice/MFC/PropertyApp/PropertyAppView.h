// PropertyAppView.h : interface of the CPropertyAppView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTYAPPVIEW_H__3508914C_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
#define AFX_PROPERTYAPPVIEW_H__3508914C_4921_11D5_9EAD_00E04C6832A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPropertyAppView : public CView
{
protected: // create from serialization only
	CPropertyAppView();
	DECLARE_DYNCREATE(CPropertyAppView)

// Attributes
public:
	CPropertyAppDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertyAppView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPropertyAppView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_check;
	CString m_edit;

// Generated message map functions
protected:
	//{{AFX_MSG(CPropertyAppView)
	afx_msg void OnFunProp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PropertyAppView.cpp
inline CPropertyAppDoc* CPropertyAppView::GetDocument()
   { return (CPropertyAppDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYAPPVIEW_H__3508914C_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
