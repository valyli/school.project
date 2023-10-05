// DlgPrintDlg.h : header file
//

#if !defined(AFX_DLGPRINTDLG_H__8B30B43A_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_)
#define AFX_DLGPRINTDLG_H__8B30B43A_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgPrintDlg dialog

class CDlgPrintDlg : public CDialog
{
// Construction
public:
	CDlgPrintDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPrintDlg)
	enum { IDD = IDD_DLGPRINT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrintDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgPrintDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRINTDLG_H__8B30B43A_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_)
