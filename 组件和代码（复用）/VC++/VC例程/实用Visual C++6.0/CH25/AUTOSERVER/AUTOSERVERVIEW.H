// AutoserverView.h : interface of the CAutoserverView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOSERVERVIEW_H__B282D1CC_DD47_11D2_BF13_996F03973C62__INCLUDED_)
#define AFX_AUTOSERVERVIEW_H__B282D1CC_DD47_11D2_BF13_996F03973C62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CAutoserverView : public CView
{
protected: // create from serialization only
	CAutoserverView();
	DECLARE_DYNCREATE(CAutoserverView)

// Attributes
public:
	CAutoserverDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoserverView)
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
	virtual ~CAutoserverView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAutoserverView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AutoserverView.cpp
inline CAutoserverDoc* CAutoserverView::GetDocument()
   { return (CAutoserverDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOSERVERVIEW_H__B282D1CC_DD47_11D2_BF13_996F03973C62__INCLUDED_)
