// ClientTransferModuleDemoDlg.h : header file
//

#if !defined(AFX_CLIENTTRANSFERMODULEDEMODLG_H__3570D6B1_A87A_43A4_8024_4401283FFD87__INCLUDED_)
#define AFX_CLIENTTRANSFERMODULEDEMODLG_H__3570D6B1_A87A_43A4_8024_4401283FFD87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientTransferModuleDemoDlg dialog


#include "ManageData.h"



class CClientTransferModuleDemoDlg : public CDialog
{
// Construction
public:
	bool Load_CTransferModule();
	CClientTransferModuleDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientTransferModuleDemoDlg)
	enum { IDD = IDD_CLIENTTRANSFERMODULEDEMO_DIALOG };
	long	m_InfomationElementTableID;
	long	m_InfomationElementID;
	CString	m_Data;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientTransferModuleDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMODULE hLibrary;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientTransferModuleDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGetallmoduleinfo();
	afx_msg void OnBUTTONLoadCTransferModule();
	afx_msg void OnBUTTONFreeCTransferModule();
	afx_msg void OnBUTTONTransferModule();
	afx_msg void OnBUTTONTransferModuleByTLV();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTTRANSFERMODULEDEMODLG_H__3570D6B1_A87A_43A4_8024_4401283FFD87__INCLUDED_)
