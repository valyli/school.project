// Example4EDlg.h : header file
//

#if !defined(AFX_EXAMPLE4EDLG_H__CCC00B48_A7A4_11D4_B71C_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4EDLG_H__CCC00B48_A7A4_11D4_B71C_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExample4EDlg dialog

class CExample4EDlg : public CDialog
{
// Construction
public:
	CExample4EDlg(CWnd* pParent = NULL);	// standard constructor

	CBitmapButton m_Paint;
// Dialog Data
	//{{AFX_DATA(CExample4EDlg)
	enum { IDD = IDD_EXAMPLE4E_DIALOG };
	BOOL	m_bCheck;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4EDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExample4EDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4EDLG_H__CCC00B48_A7A4_11D4_B71C_0000B48A052A__INCLUDED_)
