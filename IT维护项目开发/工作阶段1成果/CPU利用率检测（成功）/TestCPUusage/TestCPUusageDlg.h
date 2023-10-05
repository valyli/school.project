// TestCPUusageDlg.h : header file
//

#if !defined(AFX_TESTCPUUSAGEDLG_H__1C57CF6F_9722_41B0_88A5_318B42EEF773__INCLUDED_)
#define AFX_TESTCPUUSAGEDLG_H__1C57CF6F_9722_41B0_88A5_318B42EEF773__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestCPUusageDlg dialog
#include "CheckCpuUsage.h"

class CTestCPUusageDlg : public CDialog
{
// Construction
public:
	CTestCPUusageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestCPUusageDlg)
	enum { IDD = IDD_TESTCPUUSAGE_DIALOG };
	long	m_try1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCPUusageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestCPUusageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCheck();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCPUUSAGEDLG_H__1C57CF6F_9722_41B0_88A5_318B42EEF773__INCLUDED_)
