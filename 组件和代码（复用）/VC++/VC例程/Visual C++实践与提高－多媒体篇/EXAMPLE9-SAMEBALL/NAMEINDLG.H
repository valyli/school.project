// 编码: Leezy
// 最后修改日期：5.1
#if !defined(AFX_NAMEINDLG_H__C8962A91_0E3F_11D4_A0AC_0080AD76C3BA__INCLUDED_)
#define AFX_NAMEINDLG_H__C8962A91_0E3F_11D4_A0AC_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NameInDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNameInDlg dialog

class CNameInDlg : public CDialog
{
// Construction
public:
	CNameInDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNameInDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_sName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNameInDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNameInDlg)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAMEINDLG_H__C8962A91_0E3F_11D4_A0AC_0080AD76C3BA__INCLUDED_)
