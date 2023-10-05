// MouseDemoDlg.h : header file
//

#if !defined(AFX_MOUSEDEMODLG_H__ABA23913_C44B_46FA_BF1A_84C60E0C60A3__INCLUDED_)
#define AFX_MOUSEDEMODLG_H__ABA23913_C44B_46FA_BF1A_84C60E0C60A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMouseDemoDlg dialog

class CMouseDemoDlg : public CDialog
{
private:
	CClientHook m_hook;
	int nItem;
// Construction
public:
	CMouseDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMouseDemoDlg)
	enum { IDD = IDD_MOUSEDEMO_DIALOG };
	CListCtrl	m_Job_List;
	CListCtrl	m_Test_List;
	CString	m_RuntimeClassName;
	CString	m_Filepath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMouseDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHookCreatewindow(WPARAM wParam, LPARAM lParam);
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEDEMODLG_H__ABA23913_C44B_46FA_BF1A_84C60E0C60A3__INCLUDED_)
