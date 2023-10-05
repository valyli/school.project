#if !defined(AFX_MYWND_H__D05BD4A0_A9DE_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_MYWND_H__D05BD4A0_A9DE_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyWnd window

class CMyWnd : public CWnd
{
// Construction
public:
	CMyWnd();

// Attributes
public:
	static LPCSTR lpszClassName; //注册类名	
	CPoint m_prePoint; //检测鼠标移动
	void DrawBitmap(CDC& dc, int nIndexBit);
public:
	BOOL Create();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyWnd)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnActivateApp(BOOL bActive, HTASK hTask);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWND_H__D05BD4A0_A9DE_11D4_8EAF_0000B48A052A__INCLUDED_)
