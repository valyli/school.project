// TestCycleTransferModuleDlg.h : header file
//

#if !defined(AFX_TESTCYCLETRANSFERMODULEDLG_H__BC062B10_7D54_49B9_B057_F93E0D544305__INCLUDED_)
#define AFX_TESTCYCLETRANSFERMODULEDLG_H__BC062B10_7D54_49B9_B057_F93E0D544305__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Base.h"

/////////////////////////////////////////////////////////////////////////////
// CTestCycleTransferModuleDlg dialog

class CTestCycleTransferModuleDlg : public CDialog
{
// Construction
public:
	CTestCycleTransferModuleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestCycleTransferModuleDlg)
	enum { IDD = IDD_TESTCYCLETRANSFERMODULE_DIALOG };
	CListBox	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCycleTransferModuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMODULE hLibrary;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestCycleTransferModuleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCycletransfermodule();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCYCLETRANSFERMODULEDLG_H__BC062B10_7D54_49B9_B057_F93E0D544305__INCLUDED_)
