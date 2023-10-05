// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__54E88179_7A55_410B_A186_DB055D18F584__INCLUDED_)
#define AFX_TESTDLG_H__54E88179_7A55_410B_A186_DB055D18F584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//需加入以下头文件
#include "Winver.h"
#include "Windows.h"

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog
/*struct VS_VERSIONINFO
{ 
  WORD  wLength; 
  WORD  wValueLength; 
  WORD  wType; 
  WCHAR szKey[1024]; 
  WORD  Padding1[1024]; 
  VS_FIXEDFILEINFO Value; 
  WORD  Padding2[1024]; 
  WORD  Children[1024]; 
}; 
*/

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	UINT	m_try1;
	UINT	m_try2;
	UINT	m_try3;
	UINT	m_try4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__54E88179_7A55_410B_A186_DB055D18F584__INCLUDED_)
