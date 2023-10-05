// ActiveXDlg.h : header file
//
//{{AFX_INCLUDES()
#include "calendar.h"
#include "mci.h"
//}}AFX_INCLUDES

#if !defined(AFX_ACTIVEXDLG_H__C61C8547_A834_11D3_B25B_A98DD0C15F31__INCLUDED_)
#define AFX_ACTIVEXDLG_H__C61C8547_A834_11D3_B25B_A98DD0C15F31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CActiveXDlg dialog

class CActiveXDlg : public CDialog
{
// Construction
public:
	CActiveXDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CActiveXDlg)
	enum { IDD = IDD_ACTIVEX_DIALOG };
	Cmci	m_MCI;
	CCalendar	m_Calendar;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CActiveXDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CActiveXDlg)
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

#endif // !defined(AFX_ACTIVEXDLG_H__C61C8547_A834_11D3_B25B_A98DD0C15F31__INCLUDED_)
