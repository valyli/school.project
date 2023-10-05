// ToolbarView.h : interface of the CToolbarView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBARVIEW_H__EDCE7FCD_58A0_11D1_B5D9_F552C9B11214__INCLUDED_)
#define AFX_TOOLBARVIEW_H__EDCE7FCD_58A0_11D1_B5D9_F552C9B11214__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CToolbarView : public CView
{
protected: // create from serialization only
	CToolbarView();
	DECLARE_DYNCREATE(CToolbarView)

// Attributes
public:
	CToolbarDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolbarView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_bEnableCreature;
	virtual ~CToolbarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CToolbarView)
	afx_msg void OnCreature();
	afx_msg void OnUpdateCreature(CCmdUI* pCmdUI);
	afx_msg void OnButton32773();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ToolbarView.cpp
inline CToolbarDoc* CToolbarView::GetDocument()
   { return (CToolbarDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBARVIEW_H__EDCE7FCD_58A0_11D1_B5D9_F552C9B11214__INCLUDED_)
