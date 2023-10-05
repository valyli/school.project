// 编码: Leezy
// 最后修改日期：5.1
#if !defined(AFX_SCORELIST_H__C8962A92_0E3F_11D4_A0AC_0080AD76C3BA__INCLUDED_)
#define AFX_SCORELIST_H__C8962A92_0E3F_11D4_A0AC_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScoreList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CScoreList dialog

class CScoreList : public CDialog
{
// Construction
public:
	int  m_dCurrentId;
	CScoreList(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CScoreList)
	enum { IDD = IDD_DIALOG2 };
	CString	m_sName1;
	CString	m_sName2;
	CString	m_sName3;
	CString	m_sName4;
	CString	m_sName5;
	CString	m_sScore1;
	CString	m_sScore2;
	CString	m_sScore3;
	CString	m_sScore4;
	CString	m_sScore5;
	CString	m_sMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScoreList)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CScoreList)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCORELIST_H__C8962A92_0E3F_11D4_A0AC_0080AD76C3BA__INCLUDED_)
