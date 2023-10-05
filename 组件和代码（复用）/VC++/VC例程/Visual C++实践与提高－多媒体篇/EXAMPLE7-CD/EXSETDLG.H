#if !defined(AFX_EXSETDLG_H__EFED8AEF_9AB4_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_EXSETDLG_H__EFED8AEF_9AB4_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// exsetdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// exsetdlg dialog

class exsetdlg : public CDialog
{
// Construction
public:
	exsetdlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(exsetdlg)
	enum { IDD = IDD_SET };
	int		m_fmin;
	int		m_fsec;
	int		m_tmin;
	int		m_tsec;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(exsetdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(exsetdlg)
	afx_msg void OnOK();
	afx_msg void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXSETDLG_H__EFED8AEF_9AB4_11D4_9300_5254AB10AACA__INCLUDED_)
