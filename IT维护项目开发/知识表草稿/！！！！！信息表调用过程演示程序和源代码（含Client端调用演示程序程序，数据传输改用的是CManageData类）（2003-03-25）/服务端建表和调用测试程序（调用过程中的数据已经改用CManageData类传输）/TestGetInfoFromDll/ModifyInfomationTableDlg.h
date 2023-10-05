#if !defined(AFX_MODIFYINFOMATIONTABLEDLG_H__7D1AA9FF_E33E_4B94_B199_AED547A50D4F__INCLUDED_)
#define AFX_MODIFYINFOMATIONTABLEDLG_H__7D1AA9FF_E33E_4B94_B199_AED547A50D4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyInfomationTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyInfomationTableDlg dialog




/////////////////////////////////////////////////////////////////////////////
#include "InfomationElementListTable.h"
/////////////////////////////////////////////////////////////////////////////



//修改 信息项表列表 数据的对话框类
class CModifyInfomationTableDlg : public CDialog
{
// Construction
public:
	bool SetCurSelByItemData(CComboBox& Combo, DWORD itemdata);
	CModifyInfomationTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyInfomationTableDlg)
	enum { IDD = IDD_DIALOG_MODIFYINFOMATIONTABLE };
	CComboBox	m_InfomationElementTableID;
	CComboBox	m_EqualInfomationElementTableID;
	CString	m_InfomationElementTableName_Chinese;
	CString	m_InfomationElementTableName_English;
	CString	m_Description;
	long	m_InfoServiceProviderId;
	long	m_NameBaseId;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyInfomationTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CInfomationElementListTable m_InfomationElementListTable;

	// Generated message map functions
	//{{AFX_MSG(CModifyInfomationTableDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOModifyInfomationElementTableID();
	virtual void OnOK();
	afx_msg void OnButtonTomodifyInfomationtable();
	afx_msg void OnButtonToAddInfomationTableElement();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYINFOMATIONTABLEDLG_H__7D1AA9FF_E33E_4B94_B199_AED547A50D4F__INCLUDED_)
