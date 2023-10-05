// TestRegisterDlg.h : header file
//

#if !defined(AFX_TESTREGISTERDLG_H__2EF9934D_60BB_4314_9D88_0E3D3F3B5953__INCLUDED_)
#define AFX_TESTREGISTERDLG_H__2EF9934D_60BB_4314_9D88_0E3D3F3B5953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestRegisterDlg dialog

class CTestRegisterDlg : public CDialog
{
// Construction
public:
	CTestRegisterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestRegisterDlg)
	enum { IDD = IDD_TESTREGISTER_DIALOG };
	CString	str_owner;
	CString	str_company;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestRegisterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestRegisterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonCheck();
	afx_msg void OnButtonSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTREGISTERDLG_H__2EF9934D_60BB_4314_9D88_0E3D3F3B5953__INCLUDED_)
