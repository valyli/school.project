// TestBiosDlg.h : header file
//

#if !defined(AFX_TESTBIOSDLG_H__E248FD02_C031_4505_8874_52C4CBDB78B1__INCLUDED_)
#define AFX_TESTBIOSDLG_H__E248FD02_C031_4505_8874_52C4CBDB78B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestBiosDlg dialog

class CTestBiosDlg : public CDialog
{
// Construction
public:
	CTestBiosDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestBiosDlg)
	enum { IDD = IDD_TESTBIOS_DIALOG };
	CString	m_try1;
	CString	m_try2;
	CString	m_try3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBiosDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestBiosDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBIOSDLG_H__E248FD02_C031_4505_8874_52C4CBDB78B1__INCLUDED_)
