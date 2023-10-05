// ButtonDlg.h : header file
//

#if !defined(AFX_BUTTONDLG_H__160448C6_A5CB_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_BUTTONDLG_H__160448C6_A5CB_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CButtonDlg dialog

class CButtonDlg : public CDialog
{
// Construction
public:
	void ChangeDialogTitle(UINT nID);
	UINT m_nIDofLastButton;
	CButtonDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CButtonDlg)
	enum { IDD = IDD_BUTTON_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButtonDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CButtonDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowHide();
	afx_msg void OnEnableDisable();
	afx_msg void OnLeft();
	afx_msg void OnCenter();
	afx_msg void OnRight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTONDLG_H__160448C6_A5CB_11D3_AEE1_00104B125379__INCLUDED_)
