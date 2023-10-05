#if !defined(AFX_SCROLL_H__DA4733A1_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
#define AFX_SCROLL_H__DA4733A1_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Scroll.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScroll dialog

class CScroll : public CDialog
{
// Construction
public:
	CScroll(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScroll)
	enum { IDD = IDD_DIALOG1 };
	int		m_ScrollBar1;
	int		m_ScrollBar2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScroll)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScroll)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLL_H__DA4733A1_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
