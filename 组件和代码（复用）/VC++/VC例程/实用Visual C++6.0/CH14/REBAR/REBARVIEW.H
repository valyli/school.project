// rebarView.h : interface of the CRebarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REBARVIEW_H__64C10F6D_5AA6_11D1_B5D9_C30D74116017__INCLUDED_)
#define AFX_REBARVIEW_H__64C10F6D_5AA6_11D1_B5D9_C30D74116017__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CRebarView : public CView
{
protected: // create from serialization only
	CRebarView();
	DECLARE_DYNCREATE(CRebarView)

// Attributes
public:
	CRebarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRebarView)
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
	virtual ~CRebarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CRebarView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in rebarView.cpp
inline CRebarDoc* CRebarView::GetDocument()
   { return (CRebarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REBARVIEW_H__64C10F6D_5AA6_11D1_B5D9_C30D74116017__INCLUDED_)
