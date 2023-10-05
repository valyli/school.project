// CheckCPUTestDlg.h : header file
//

#if !defined(AFX_CHECKCPUTESTDLG_H__0C225532_BD8D_4CAF_9C3A_68B9868A8145__INCLUDED_)
#define AFX_CHECKCPUTESTDLG_H__0C225532_BD8D_4CAF_9C3A_68B9868A8145__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckCPUTestDlg dialog
#include "CheckCPU.h"

class CCheckCPUTestDlg : public CDialog
{
// Construction
public:
	CCheckCPU m_CheckCPU;
	CCheckCPUTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckCPUTestDlg)
	enum { IDD = IDD_CHECKCPUTEST_DIALOG };
	CString	m_CPUID_Edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckCPUTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckCPUTestDlg)
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

#endif // !defined(AFX_CHECKCPUTESTDLG_H__0C225532_BD8D_4CAF_9C3A_68B9868A8145__INCLUDED_)
