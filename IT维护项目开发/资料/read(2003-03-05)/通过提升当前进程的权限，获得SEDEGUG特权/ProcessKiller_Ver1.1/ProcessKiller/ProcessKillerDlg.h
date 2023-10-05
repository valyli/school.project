// ProcessKillerDlg.h : header file
//

#if !defined(AFX_PROCESSKILLERDLG_H__7A0A78B0_6E76_4215_8EA1_83D292ACF90F__INCLUDED_)
#define AFX_PROCESSKILLERDLG_H__7A0A78B0_6E76_4215_8EA1_83D292ACF90F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CProcessKillerDlg dialog
#include "ListCtrlEx.h"
#include "ShowListDlg.h"

class CProcessKillerDlg : public CDialog
{
// Construction
public:
	CProcessKillerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProcessKillerDlg)
	enum { IDD = IDD_PROCESSKILLER_DIALOG };
	CListCtrlEx	m_listP;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProcessKillerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProcessKillerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPopmenuKill();
	afx_msg void OnClose();
	afx_msg void OnDblclkListProcess(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAbout();
	afx_msg void OnMenuRefresh();
	afx_msg void OnPopmenuModules();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	DWORD RefreshProcessesList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line. 

#endif // !defined(AFX_PROCESSKILLERDLG_H__7A0A78B0_6E76_4215_8EA1_83D292ACF90F__INCLUDED_)
