// TestComputerNameDlg.h : header file
//

#if !defined(AFX_TESTCOMPUTERNAMEDLG_H__EFFC7F79_A91A_4EA7_85E8_9E02A283046B__INCLUDED_)
#define AFX_TESTCOMPUTERNAMEDLG_H__EFFC7F79_A91A_4EA7_85E8_9E02A283046B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestComputerNameDlg dialog

class CTestComputerNameDlg : public CDialog
{
// Construction
public:
	CTestComputerNameDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestComputerNameDlg)
	enum { IDD = IDD_TESTCOMPUTERNAME_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestComputerNameDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestComputerNameDlg)
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

#endif // !defined(AFX_TESTCOMPUTERNAMEDLG_H__EFFC7F79_A91A_4EA7_85E8_9E02A283046B__INCLUDED_)
