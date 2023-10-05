#if !defined(AFX_MODELESS_H__4889656F_967F_11CE_B78D_444553540000__INCLUDED_)
#define AFX_MODELESS_H__4889656F_967F_11CE_B78D_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Modeless.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModeless dialog

#include "MLaunchDlgDlg.h"
class CMLaunchDlg;
class CModeless : public CDialog
{
// Construction
public:
	CModeless(CMLaunchDlgDlg* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModeless)
	enum { IDD = IDD_DIALOG1 };
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
	CMLaunchDlgDlg* m_pParent;
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

#endif // !defined(AFX_MODELESS_H__4889656F_967F_11CE_B78D_444553540000__INCLUDED_)
