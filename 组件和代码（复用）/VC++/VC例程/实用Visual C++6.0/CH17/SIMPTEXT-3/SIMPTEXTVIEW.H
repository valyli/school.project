// SimpTextView.h : interface of the CSimpTextView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPTEXTVIEW_H__4157B974_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
#define AFX_SIMPTEXTVIEW_H__4157B974_6DC7_11CD_BC53_EDB715115552__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSimpTextView : public CView
{
protected: // create from serialization only
	CSimpTextView();
	DECLARE_DYNCREATE(CSimpTextView)

// Attributes
public:
	CSimpTextDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSimpTextView)
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
	CFont m_fnCustom;
	virtual ~CSimpTextView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSimpTextView)
	afx_msg void OnChoosefont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SimpTextView.cpp
inline CSimpTextDoc* CSimpTextView::GetDocument()
   { return (CSimpTextDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPTEXTVIEW_H__4157B974_6DC7_11CD_BC53_EDB715115552__INCLUDED_)
