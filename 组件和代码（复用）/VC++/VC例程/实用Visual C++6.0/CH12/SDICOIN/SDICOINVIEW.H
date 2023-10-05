// SDICoinView.h : interface of the CSDICoinView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDICOINVIEW_H__B038A62D_AD17_11D0_B1A4_20964CC10000__INCLUDED_)
#define AFX_SDICOINVIEW_H__B038A62D_AD17_11D0_B1A4_20964CC10000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSDICoinView : public CView
{
protected: // create from serialization only
	CSDICoinView();
	DECLARE_DYNCREATE(CSDICoinView)

// Attributes
public:
	CSDICoinDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSDICoinView)
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
	virtual ~CSDICoinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSDICoinView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SDICoinView.cpp
inline CSDICoinDoc* CSDICoinView::GetDocument()
   { return (CSDICoinDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDICOINVIEW_H__B038A62D_AD17_11D0_B1A4_20964CC10000__INCLUDED_)
