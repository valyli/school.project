// PanSDIView.h : interface of the CPanSDIView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PANSDIVIEW_H__4157B99C_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
#define AFX_PANSDIVIEW_H__4157B99C_6DC7_11CD_BC53_EDB715115552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPanSDIView : public CScrollView
{
protected: // create from serialization only
	CPanSDIView();
	DECLARE_DYNCREATE(CPanSDIView)

// Attributes
public:
	CPanSDIDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPanSDIView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPanSDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPanSDIView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PanSDIView.cpp
inline CPanSDIDoc* CPanSDIView::GetDocument()
   { return (CPanSDIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PANSDIVIEW_H__4157B99C_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
