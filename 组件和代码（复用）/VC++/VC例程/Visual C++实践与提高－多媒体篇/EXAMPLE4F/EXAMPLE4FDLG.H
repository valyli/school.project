// Example4FDlg.h : header file
//

#if !defined(AFX_EXAMPLE4FDLG_H__F9A23EA6_A9C8_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4FDLG_H__F9A23EA6_A9C8_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CExample4FDlg dialog

class CExample4FDlg : public CDialog
{
// Construction
public:
	CExample4FDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CExample4FDlg)
	enum { IDD = IDD_EXAMPLE4F_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4FDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CExample4FDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4FDLG_H__F9A23EA6_A9C8_11D4_8EAF_0000B48A052A__INCLUDED_)
