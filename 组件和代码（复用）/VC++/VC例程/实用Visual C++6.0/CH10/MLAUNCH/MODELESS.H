#if !defined(AFX_MODELESS_H__4121F4F1_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_)
#define AFX_MODELESS_H__4121F4F1_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modeless.h : header file
//
#include "MLaunchDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog

class CModeless : public CDialog
{
// Construction
public:
	CModeless(CMLaunchDlg* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModeless)
	enum { IDD = IDD_MODELESS };
	CString	m_DispMsg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModeless)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CMLaunchDlg* m_pParent;

	// Generated message map functions
	//{{AFX_MSG(CModeless)
	afx_msg void OnPop();
	afx_msg void OnPow();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELESS_H__4121F4F1_9202_11D2_B25C_8BE0A8C5C934__INCLUDED_)
