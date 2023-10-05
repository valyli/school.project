// PlotterTestDlg.h : header file
//
//{{AFX_INCLUDES()
#include "mscomm.h"
//}}AFX_INCLUDES

#if !defined(AFX_PLOTTERTESTDLG_H__81829BA7_8207_11D5_8961_00609721CE30__INCLUDED_)
#define AFX_PLOTTERTESTDLG_H__81829BA7_8207_11D5_8961_00609721CE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPlotterTestDlg dialog

class CPlotterTestDlg : public CDialog
{
// Construction
public:
	CPlotterTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPlotterTestDlg)
	enum { IDD = IDD_PLOTTERTEST_DIALOG };
	CMSComm	m_Comm;
	CString	m_Input;
	CString	m_Output;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlotterTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPlotterTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnButtonCharsend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PLOTTERTESTDLG_H__81829BA7_8207_11D5_8961_00609721CE30__INCLUDED_)
