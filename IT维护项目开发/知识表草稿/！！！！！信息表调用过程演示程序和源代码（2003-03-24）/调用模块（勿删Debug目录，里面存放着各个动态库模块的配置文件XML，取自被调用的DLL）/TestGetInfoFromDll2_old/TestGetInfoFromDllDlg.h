// TestGetInfoFromDllDlg.h : header file
//

#if !defined(AFX_TESTGETINFOFROMDLLDLG_H__AC3D90A3_9CD9_4378_BDE7_A18D759B9CE9__INCLUDED_)
#define AFX_TESTGETINFOFROMDLLDLG_H__AC3D90A3_9CD9_4378_BDE7_A18D759B9CE9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestGetInfoFromDllDlg dialog

//////////////////////////////////////////////////////////////////////////////

#include "AddInfomationTableDlg.h"

#include "ModifyInfomationTableDlg.h"


extern CArrayModuleInfomationListStruct m_CArrayOperationTable;


//////////////////////////////////////////////////////////////////////////////

//演示动态库调用过程和配置文件编辑的总起类
class CTestGetInfoFromDllDlg : public CDialog
{
// Construction
public:
	bool GetInfoListFromDll(ModuleInfomationStruct& m_Info, CString strDllFilePath);
	CTestGetInfoFromDllDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestGetInfoFromDllDlg)
	enum { IDD = IDD_TESTGETINFOFROMDLL_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestGetInfoFromDllDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestGetInfoFromDllDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonGetinfo();
	afx_msg void OnButtonAddInfomationtableinlisttable();
	afx_msg void OnBUTTONViewOrModifyInfomationTableInListTable();
	afx_msg void OnButtonAddInfomationFromDllToMemory();
	afx_msg void OnButtonViewOperationInfomationInMemory();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTGETINFOFROMDLLDLG_H__AC3D90A3_9CD9_4378_BDE7_A18D759B9CE9__INCLUDED_)
