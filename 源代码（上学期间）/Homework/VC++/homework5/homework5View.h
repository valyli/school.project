// homework5View.h : interface of the CHomework5View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMEWORK5VIEW_H__A26C8F0E_CBAA_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_HOMEWORK5VIEW_H__A26C8F0E_CBAA_11D5_9486_5254AB113BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHomework5View : public CView
{
protected: // create from serialization only
	CHomework5View();
	DECLARE_DYNCREATE(CHomework5View)

// Attributes
public:
	CHomework5Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework5View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL DestroyWindow();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawResult(PointQueue* m_apt, int m_count);
	POINT m_lastPoint;
	void Drawing(PointQueue* m_apt, int m_count);
	BOOL m_isdraw;
	virtual ~CHomework5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CHomework5View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in homework5View.cpp
inline CHomework5Doc* CHomework5View::GetDocument()
   { return (CHomework5Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK5VIEW_H__A26C8F0E_CBAA_11D5_9486_5254AB113BB2__INCLUDED_)
