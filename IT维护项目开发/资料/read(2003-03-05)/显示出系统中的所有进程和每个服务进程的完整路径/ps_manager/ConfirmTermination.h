#if !defined(AFX_CONFIRMTERMINATION_H__63550D85_2528_11D3_B572_005004FF1036__INCLUDED_)
#define AFX_CONFIRMTERMINATION_H__63550D85_2528_11D3_B572_005004FF1036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfirmTermination.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConfirmTermination dialog

class CConfirmTermination : public CDialog
{
// Construction
public:
	CConfirmTermination(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfirmTermination)
	enum { IDD = IDD_CONFIRM_TERMINATION };
	DWORD	m_idProcess;
	CString	m_sProcessPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfirmTermination)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfirmTermination)
	afx_msg void OnYes();
	afx_msg void OnNo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIRMTERMINATION_H__63550D85_2528_11D3_B572_005004FF1036__INCLUDED_)
