// TestCpuSpeedDlg.h : header file
//

#if !defined(AFX_TESTCPUSPEEDDLG_H__B6CE42C1_F272_41B4_AA10_7C3745D4E5E9__INCLUDED_)
#define AFX_TESTCPUSPEEDDLG_H__B6CE42C1_F272_41B4_AA10_7C3745D4E5E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestCpuSpeedDlg dialog

class CTestCpuSpeedDlg : public CDialog
{
// Construction
public:
	CTestCpuSpeedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestCpuSpeedDlg)
	enum { IDD = IDD_TESTCPUSPEED_DIALOG };
	long	m_try1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCpuSpeedDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestCpuSpeedDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCPUSPEEDDLG_H__B6CE42C1_F272_41B4_AA10_7C3745D4E5E9__INCLUDED_)
