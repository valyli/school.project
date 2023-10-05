#if !defined(AFX_MYWND_H__378ABEA9_FB78_40F1_A13E_7D54EB39DCE9__INCLUDED_)
#define AFX_MYWND_H__378ABEA9_FB78_40F1_A13E_7D54EB39DCE9__INCLUDED_

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

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	CButton m_b;
	BOOL Create(CWnd* pParentWnd);
	virtual ~CMyWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYWND_H__378ABEA9_FB78_40F1_A13E_7D54EB39DCE9__INCLUDED_)
