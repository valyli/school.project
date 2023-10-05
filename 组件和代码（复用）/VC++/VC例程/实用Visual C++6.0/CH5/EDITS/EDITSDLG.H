// EditsDlg.h : header file
//

#if !defined(AFX_EDITSDLG_H__87ACADC6_A8EE_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_EDITSDLG_H__87ACADC6_A8EE_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CEditsDlg dialog

#include "Initials.h"
class CEditsDlg : public CDialog
{
// Construction
public:
	CEditsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CEditsDlg)
	enum { IDD = IDD_EDITS_DIALOG };
	CInitials	m_EditInitials;
	CString	m_strFirst;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CEditsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnGetText();
	afx_msg void OnChangeEditSecond();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITSDLG_H__87ACADC6_A8EE_11D3_AEE1_00104B125379__INCLUDED_)
