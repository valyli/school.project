// ShutDownDlg.h : header file
//

#if !defined(AFX_SHUTDOWNDLG_H__1AD5EEC9_6FA2_11D4_A7B3_0088CC164534__INCLUDED_)
#define AFX_SHUTDOWNDLG_H__1AD5EEC9_6FA2_11D4_A7B3_0088CC164534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShutDownDlg dialog

class CShutDownDlg : public CDialog
{
// Construction
public:
	CShutDownDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShutDownDlg)
	enum { IDD = IDD_SHUTDOWN_DIALOG };
	CDateTimeCtrl	m_UserTimer2;
	CDateTimeCtrl	m_UserTimer1;
	CDateTimeCtrl	m_Timer3;
	CDateTimeCtrl	m_Timer2;
	CDateTimeCtrl	m_Timer1;
	CString	m_sNowTime;
	CTime	m_Time1;
	CTime	m_Time2;
	CTime	m_Time3;
	CTime	m_UserTime1;
	CTime	m_UserTime2;
	BOOL	m_Check1;
	BOOL	m_Check2;
	BOOL	m_Check3;
	BOOL	m_Check4;
	BOOL	m_Check5;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShutDownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShutDownDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker4(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimechangeDatetimepicker5(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonShutdown();
	afx_msg void OnButtonHide();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	afx_msg void OnCheck5();
	afx_msg void OnMenuAbort();
	afx_msg void OnMenuMain();
	afx_msg void OnMenuNowshut();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuShortcut();
	afx_msg void OnMenuOut();
	afx_msg void OnMenuClose();
	afx_msg void OnMenuSystem();
	afx_msg void OnMenuPassword();
	afx_msg void OnMenuIdlemin();
	afx_msg void OnMenuReboot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL	GetCdrom();
	void	LockWindow();

private:
	BOOL	m_IsShow;
	BOOL	m_Cdrom;
	UINT	m_IdleMin;
	BOOL	m_IdleOK;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUTDOWNDLG_H__1AD5EEC9_6FA2_11D4_A7B3_0088CC164534__INCLUDED_)
