// sdimenuView.h : interface of the CSdimenuView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SDIMENUVIEW_H__9B730123_5513_11D1_B5D9_DB30231F0417__INCLUDED_)
#define AFX_SDIMENUVIEW_H__9B730123_5513_11D1_B5D9_DB30231F0417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSdimenuView : public CView
{
protected: // create from serialization only
	CSdimenuView();
	DECLARE_DYNCREATE(CSdimenuView)

// Attributes
public:
	CSdimenuDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSdimenuView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	void OnYellow ();
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSdimenuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSdimenuView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMypopupmenuNorth();
	afx_msg void OnUpdateMypopupmenuNorth(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in sdimenuView.cpp
inline CSdimenuDoc* CSdimenuView::GetDocument()
   { return (CSdimenuDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SDIMENUVIEW_H__9B730123_5513_11D1_B5D9_DB30231F0417__INCLUDED_)
