#if !defined(AFX_ADDINFOMATIONTABLEELEMENTDLG_H__6F39BFD2_1A43_4267_815D_2CC0647590C1__INCLUDED_)
#define AFX_ADDINFOMATIONTABLEELEMENTDLG_H__6F39BFD2_1A43_4267_815D_2CC0647590C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddInfomationTableElementDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddInfomationTableElementDlg dialog


#include "InfomationTable.h"


//在 信息项表 中添加信息项的对话框类
class CAddInfomationTableElementDlg : public CDialog
{
// Construction
public:
	CAddInfomationTableElementDlg(CWnd* pParent = NULL);   // standard constructor
	CString m_TableName;

// Dialog Data
	//{{AFX_DATA(CAddInfomationTableElementDlg)
	enum { IDD = IDD_DIALOG_ADDINFOMATIONTABLE_ELEMENT };
	CComboBox	m_InfomationType;
	long	m_InfomationElementTableID;
	long	m_InfomationElementID;
	CString	m_Infomation;
	CString	m_EnglishName;
	CString	m_Description;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddInfomationTableElementDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CInfomationTable m_InfomationTable;

	// Generated message map functions
	//{{AFX_MSG(CAddInfomationTableElementDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDINFOMATIONTABLEELEMENTDLG_H__6F39BFD2_1A43_4267_815D_2CC0647590C1__INCLUDED_)
