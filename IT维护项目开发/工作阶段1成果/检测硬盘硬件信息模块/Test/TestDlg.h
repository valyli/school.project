// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__086ACBF0_61FA_4177_AC0A_36298D998E2A__INCLUDED_)
#define AFX_TESTDLG_H__086ACBF0_61FA_4177_AC0A_36298D998E2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog
#include "heckHardDiskDevice.h"

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CComboBox	m_Controller_Combo;
	CString	m_DriveLevel_Edit;
	unsigned long 		m_BufferSize;
	int		m_Cylinder_Edit;
	CString	m_DriverType_Edit;
	int		m_Heads_Edit;
	CString	m_ModelNumber;
	int		m_Sector_Edit;
	CString	m_SerialNumber_Edit;
	CString	m_CtlRevisionNumber;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CheckHardDiskDevice m_CheckHardDiskDevice;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSelchangeCombo1Controller();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__086ACBF0_61FA_4177_AC0A_36298D998E2A__INCLUDED_)
