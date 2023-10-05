// DrawLineView.h : interface of the CDrawLineView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWLINEVIEW_H__DC65A62B_4643_11D5_82DA_00E04C3B1D5D__INCLUDED_)
#define AFX_DRAWLINEVIEW_H__DC65A62B_4643_11D5_82DA_00E04C3B1D5D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDrawLineView : public CView
{
protected: // create from serialization only
	CDrawLineView();
	DECLARE_DYNCREATE(CDrawLineView)

// Attributes
public:
	CDrawLineDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawLineView)
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
	virtual ~CDrawLineView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_Drag;
	HCURSOR m_HCursor;
	CPoint m_pPrev;
	CPoint m_pOrigin;

// Generated message map functions
protected:
	//{{AFX_MSG(CDrawLineView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DrawLineView.cpp
inline CDrawLineDoc* CDrawLineView::GetDocument()
   { return (CDrawLineDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWLINEVIEW_H__DC65A62B_4643_11D5_82DA_00E04C3B1D5D__INCLUDED_)
