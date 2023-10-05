// MLaunchDlg.h : header file
//

#if !defined(AFX_MLAUNCHDLG_H__4121F4E9_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_)
#define AFX_MLAUNCHDLG_H__4121F4E9_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMLaunchDlg dialog

class CMLaunchDlg : public CDialog
{
// Construction
public:
	CMLaunchDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMLaunchDlg)
	enum { IDD = IDD_MLAUNCH_DIALOG };
	CListBox	m_DisplayList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMLaunchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMLaunchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartModeless();
	afx_msg void OnSopModeless();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MLAUNCHDLG_H__4121F4E9_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_)
