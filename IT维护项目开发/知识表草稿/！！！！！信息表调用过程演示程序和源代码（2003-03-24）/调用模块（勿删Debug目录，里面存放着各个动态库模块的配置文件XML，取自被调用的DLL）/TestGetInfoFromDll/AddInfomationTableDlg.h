#if !defined(AFX_ADDINFOMATIONTABLEDLG_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
#define AFX_ADDINFOMATIONTABLEDLG_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddInfomationTableDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAddInfomationTableDlg dialog



/////////////////////////////////////////////////////////////////////////////
#include "InfomationElementListTable.h"

#include "InfomationTable.h"

/////////////////////////////////////////////////////////////////////////////



//在 信息项表列表 中添加表项，并在新建信息表的类
class CAddInfomationTableDlg : public CDialog
{
// Construction
public:
	CAddInfomationTableDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAddInfomationTableDlg)
	enum { IDD = IDD_DIALOG_ADDINFOMATIONTABLE };
	CComboBox	m_EqualInfomationElementTableID;
	long	m_InfomationElementTableID;
	CString	m_InfomationElementTableName_Chinese;
	CString	m_InfomationElementTableName_English;
	CString	m_Description;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAddInfomationTableDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	CInfomationElementListTable m_InfomationElementListTable;

	// Generated message map functions
	//{{AFX_MSG(CAddInfomationTableDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDINFOMATIONTABLEDLG_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
