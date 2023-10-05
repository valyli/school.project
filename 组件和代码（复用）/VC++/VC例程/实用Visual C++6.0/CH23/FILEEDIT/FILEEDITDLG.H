// FileEditDlg.h : header file
//

#if !defined(AFX_FILEEDITDLG_H__8B06B2AB_D652_11D2_BF13_E2747651D762__INCLUDED_)
#define AFX_FILEEDITDLG_H__8B06B2AB_D652_11D2_BF13_E2747651D762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileEditDlg dialog

class CFileEditDlg : public CDialog
{
// Construction
public:
	CFileEditDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CFileEditDlg)
	enum { IDD = IDD_FILEEDIT_DIALOG };
	CString	m_EditBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileEditDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CFileEditDlg)
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

#endif // !defined(AFX_FILEEDITDLG_H__8B06B2AB_D652_11D2_BF13_E2747651D762__INCLUDED_)
