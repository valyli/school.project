// ClientHookMonitorDemoDlg.h : header file
//

#if !defined(AFX_CLIENTHOOKMONITORDEMODLG_H__90A0E521_B719_41C2_AA78_F39F07FCF53A__INCLUDED_)
#define AFX_CLIENTHOOKMONITORDEMODLG_H__90A0E521_B719_41C2_AA78_F39F07FCF53A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientHookMonitorDemoDlg dialog

#include "ClientHook.h"

class CClientHookMonitorDemoDlg : public CDialog
{
// Construction
public:
	BOOL CreatJobView(WPARAM wParam, LPARAM lParam);
	CClientHookMonitorDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientHookMonitorDemoDlg)
	enum { IDD = IDD_CLIENTHOOKMONITORDEMO_DIALOG };
	CListCtrl	m_NewJobList;
	CListCtrl	m_JobList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientHookMonitorDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ViewJob(void);
	HICON m_hIcon;
	//ÉùÃ÷¹³×ÓÀà
	CClientHook m_ClientHook;

	// Generated message map functions
	//{{AFX_MSG(CClientHookMonitorDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHookCreatewindow(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTHOOKMONITORDEMODLG_H__90A0E521_B719_41C2_AA78_F39F07FCF53A__INCLUDED_)
