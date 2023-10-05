// TestShellSystemTypeDlg.h : header file
//

#if !defined(AFX_TESTSHELLSYSTEMTYPEDLG_H__A1E08907_F5C9_4913_B100_89ED087C39E9__INCLUDED_)
#define AFX_TESTSHELLSYSTEMTYPEDLG_H__A1E08907_F5C9_4913_B100_89ED087C39E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "CheckSystemType.h"

/////////////////////////////////////////////////////////////////////////////
// CTestShellSystemTypeDlg dialog


class CTestShellSystemTypeDlg : public CDialog
{
// Construction
public:
	CTestShellSystemTypeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestShellSystemTypeDlg)
	enum { IDD = IDD_TESTSHELLSYSTEMTYPE_DIALOG };
	CString	m_try1;
	UINT	m_try2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestShellSystemTypeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CTestShellSystemTypeDlg)
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

#endif // !defined(AFX_TESTSHELLSYSTEMTYPEDLG_H__A1E08907_F5C9_4913_B100_89ED087C39E9__INCLUDED_)
