// MonthCalDlg.h : header file
//
//{{AFX_INCLUDES()
#include "calendar.h"
#include "mci.h"
//}}AFX_INCLUDES

#if !defined(AFX_MONTHCALDLG_H__6766F3E7_1E12_11D1_B78E_444553540000__INCLUDED_)
#define AFX_MONTHCALDLG_H__6766F3E7_1E12_11D1_B78E_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMonthCalDlg dialog

class CMonthCalDlg : public CDialog
{
// Construction
public:
	CMonthCalDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMonthCalDlg)
	enum { IDD = IDD_MONTHCAL_DIALOG };
	CCalendar	m_Calendar;
	Cmci	m_MCI;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonthCalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMonthCalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClickCalendar();
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONTHCALDLG_H__6766F3E7_1E12_11D1_B78E_444553540000__INCLUDED_)
