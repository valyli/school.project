#if !defined(AFX_MODIFYINFOMATIONELEMENTTABLEDLG_H__44799C2A_E589_4564_A08B_7DFF90FDEF02__INCLUDED_)
#define AFX_MODIFYINFOMATIONELEMENTTABLEDLG_H__44799C2A_E589_4564_A08B_7DFF90FDEF02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyInfomationElementTableDlg.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CModifyInfomationElementTableDlg dialog




////////////////////////////////////////////////////////////////////////////

#include "InfomationTable.h"


#include "TransferModule.h"



extern CArrayModuleInfomationListStruct m_CArrayOperationTable;


////////////////////////////////////////////////////////////////////////////




//修改InfomationTable（信息项表） 表项的对话框类
class CModifyInfomationElementTableDlg : public CDialog
{
// Construction
public:
	//用于传送获得的 信息项表 名
	CString m_TableName;

	bool SetCurSelByItemData(CComboBox &Combo, DWORD itemdata);

	CModifyInfomationElementTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyInfomationElementTableDlg)
	enum { IDD = IDD_DIALOG_MODIFY_INFOMATION_ELEMENT_TABLE };
	CComboBox	m_InfomationType;
	CComboBox	m_InfomationElementID;
	CString	m_Description;
	CString	m_EnglishName;
	CString	m_Infomation;
	long	m_InfomationElementTableID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyInfomationElementTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CInfomationTable m_InfomationTable;
	//保存数据的结构体
	CArrayInfomationElementStruct InfoListArray;
	// Generated message map functions
	//{{AFX_MSG(CModifyInfomationElementTableDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCOMBOInfomationElementID();
	virtual void OnOK();
	afx_msg void OnButtonTransferDll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYINFOMATIONELEMENTTABLEDLG_H__44799C2A_E589_4564_A08B_7DFF90FDEF02__INCLUDED_)
