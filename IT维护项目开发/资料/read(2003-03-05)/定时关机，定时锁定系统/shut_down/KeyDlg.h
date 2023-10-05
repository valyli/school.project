#if !defined(AFX_KEYDLG_H__F7E7EB6E_7489_11D4_986A_52544C1AEF84__INCLUDED_)
#define AFX_KEYDLG_H__F7E7EB6E_7489_11D4_986A_52544C1AEF84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// KeyDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CKeyDlg dialog

class CKeyDlg : public CDialog
{
// Construction
public:
	CKeyDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CKeyDlg)
	enum { IDD = IDD_KEYDLG };
	CString	m_oldkey;
	CString	m_newkey;
	CString	m_newkeyok;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKeyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CKeyDlg)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KEYDLG_H__F7E7EB6E_7489_11D4_986A_52544C1AEF84__INCLUDED_)
