// AutoclintDlg.h : header file
//

#if !defined(AFX_AUTOCLINTDLG_H__21BB6E7B_DD66_11D2_BF13_828252DAF362__INCLUDED_)
#define AFX_AUTOCLINTDLG_H__21BB6E7B_DD66_11D2_BF13_828252DAF362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAutoclintDlg dialog

class CAutoclintDlg : public CDialog
{
// Construction
public:
	CAutoclintDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAutoclintDlg)
	enum { IDD = IDD_AUTOCLINT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoclintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAutoclintDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCLINTDLG_H__21BB6E7B_DD66_11D2_BF13_828252DAF362__INCLUDED_)
