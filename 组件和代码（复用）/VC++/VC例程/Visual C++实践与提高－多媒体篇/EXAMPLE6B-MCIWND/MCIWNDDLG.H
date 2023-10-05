// mciwndDlg.h : header file
//

#if !defined(AFX_MCIWNDDLG_H__74C54D75_9629_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_MCIWNDDLG_H__74C54D75_9629_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "cmci.h"
/////////////////////////////////////////////////////////////////////////////
// CMciwndDlg dialog

class CMciwndDlg : public CDialog
{
// Construction
public:
	CMciwndDlg(CWnd* pParent = NULL);	// standard constructor
public:
	CMciWnd m_mciwnd;
// Dialog Data
	//{{AFX_DATA(CMciwndDlg)
	enum { IDD = IDD_MCIWND_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciwndDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMciwndDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnOpenvideo();
	afx_msg void OnPlayvideo();
	afx_msg void OnPause();
	afx_msg void OnLast();
	afx_msg void OnNext();
	afx_msg void OnClosevideo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIWNDDLG_H__74C54D75_9629_11D4_9300_5254AB10AACA__INCLUDED_)
