// homework4View.h : interface of the CHomework4View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_HOMEWORK4VIEW_H__B7CD14FF_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_HOMEWORK4VIEW_H__B7CD14FF_CAC0_11D5_9486_5254AB113BB2__INCLUDED_

#include "SelStyleDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CHomework4View : public CScrollView
{
protected: // create from serialization only
	CHomework4View();
	DECLARE_DYNCREATE(CHomework4View)

// Attributes
public:
	CHomework4Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework4View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CHomework4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
private:
	char m_SelStyleStr[30];
	char m_WinOrgStr[30];
	char m_WinExtStr[30];
	char m_ViewOrgStr[30];
	char m_ViewExtStr[30];
	char m_TextPosStr[30];

protected:
	TEXTMETRIC m_Metrics;
	char m_MaxCharWidthStr[40];
	char m_AveCharWidthStr[40];
	char m_CharHightStr[40];
	BOOL m_ChangeSelStyle;
	COLORREF m_Color;
	void Draw(CDC* pDC);
	CPoint m_WinOrg, m_ViewOrg;
	CSize m_WinExt,	m_ViewExt;
	int m_SelStyle;
	SelStyleDlg m_SelStyleDlg;
	LOGFONT m_logFont;
	CFont m_Font;
	//{{AFX_MSG(CHomework4View)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in homework4View.cpp
inline CHomework4Doc* CHomework4View::GetDocument()
   { return (CHomework4Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK4VIEW_H__B7CD14FF_CAC0_11D5_9486_5254AB113BB2__INCLUDED_)
