// ServerJNITLVModuleDemoDlg.h : header file
//

#if !defined(AFX_SERVERJNITLVMODULEDEMODLG_H__80905A55_7F75_465A_AF2F_3B4CC3D0DFF4__INCLUDED_)
#define AFX_SERVERJNITLVMODULEDEMODLG_H__80905A55_7F75_465A_AF2F_3B4CC3D0DFF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServerJNITLVModuleDemoDlg dialog

class CServerJNITLVModuleDemoDlg : public CDialog
{
// Construction
public:
	CServerJNITLVModuleDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerJNITLVModuleDemoDlg)
	enum { IDD = IDD_SERVERJNITLVMODULEDEMO_DIALOG };
	CString	m_TLV;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerJNITLVModuleDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	/////////////////////////////////////////////////////////
	//µ¼Èë¶¯Ì¬¿â
	HMODULE hLibrary;

	// Generated message map functions
	//{{AFX_MSG(CServerJNITLVModuleDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonSetTlv();
	afx_msg void OnButtonGetNewDataFromMemoryToDll();
	afx_msg void OnButton2();
	afx_msg void OnButton1();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERJNITLVMODULEDEMODLG_H__80905A55_7F75_465A_AF2F_3B4CC3D0DFF4__INCLUDED_)
