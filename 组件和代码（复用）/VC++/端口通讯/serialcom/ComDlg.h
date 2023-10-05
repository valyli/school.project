#if !defined(AFX_COMDLG_H__D2292905_68F7_11D3_81A7_00AA00BA5071__INCLUDED_)
#define AFX_COMDLG_H__D2292905_68F7_11D3_81A7_00AA00BA5071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComDlg.h : header file
//
#include "com232.h"
/////////////////////////////////////////////////////////////////////////////
// CComDlg dialog

class CComDlg : public CDialog
{
// Construction
public:
	CComDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComDlg)
	enum { IDD = IDD_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComDlg)
	virtual BOOL OnInitDialog();

	afx_msg void OnButton1();

	afx_msg void OnSelendokCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMDLG_H__D2292905_68F7_11D3_81A7_00AA00BA5071__INCLUDED_)
