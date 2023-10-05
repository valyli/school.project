#if !defined(AFX_PWDDLG_H__F7E7EB66_7489_11D4_986A_52544C1AEF84__INCLUDED_)
#define AFX_PWDDLG_H__F7E7EB66_7489_11D4_986A_52544C1AEF84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PwdDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPwdDlg dialog

class CPwdDlg : public CDialog
{
// Construction
public:
	
	CPwdDlg(CWnd* pParent = NULL);   // standard constructor

	
// Dialog Data
	//{{AFX_DATA(CPwdDlg)
	enum { IDD = IDD_PWDDLG };
	CEdit	m_Pwd;
	CString	m_check;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPwdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPwdDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool pOld;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PWDDLG_H__F7E7EB66_7489_11D4_986A_52544C1AEF84__INCLUDED_)
