// SysinfoDlg.h : header file
//

#if !defined(AFX_SYSINFODLG_H__5964FCC6_A8D4_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_SYSINFODLG_H__5964FCC6_A8D4_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSysinfoDlg dialog

class CSysinfoDlg : public CDialog
{
// Construction
public:
	CSysinfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSysinfoDlg)
	enum { IDD = IDD_SYSINFO_DIALOG };
	CString	m_strComputerName;
	CString	m_strTotalMemory;
	CString	m_strFreeMemory;
	CString	m_strMemoryLoad;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysinfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSysinfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSINFODLG_H__5964FCC6_A8D4_11D3_AEE1_00104B125379__INCLUDED_)
