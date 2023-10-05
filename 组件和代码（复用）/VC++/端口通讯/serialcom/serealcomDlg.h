// serealcomDlg.h : header file
//

#if !defined(AFX_SEREALCOMDLG_H__DA5F5967_5DFC_11D3_81A6_00AA00BA5071__INCLUDED_)
#define AFX_SEREALCOMDLG_H__DA5F5967_5DFC_11D3_81A6_00AA00BA5071__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "com232.h"
/////////////////////////////////////////////////////////////////////////////
// CSerealcomDlg dialog
union UN
{
	float yg;
	BYTE b[4];
};
class CSerealcomDlg : public CDialog
{
// Construction
public:
	CSerealcomDlg(CWnd* pParent = NULL);	// standard constructor
    CComStatus m_comDev;
	char buf[100];
	char inbuf[100];
 	UN un;
// Dialog Data
	//{{AFX_DATA(CSerealcomDlg)
	enum { IDD = IDD_SEREALCOM_DIALOG };
	float	m_float;
	float	m_fl;
	CString	m_combo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSerealcomDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSerealcomDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEREALCOMDLG_H__DA5F5967_5DFC_11D3_81A6_00AA00BA5071__INCLUDED_)
