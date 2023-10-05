// LoadXML2MemDlg.h : header file
//

#if !defined(AFX_LOADXML2MEMDLG_H__B4C79959_DB28_4150_9C06_B99B931D745B__INCLUDED_)
#define AFX_LOADXML2MEMDLG_H__B4C79959_DB28_4150_9C06_B99B931D745B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLoadXML2MemDlg dialog

#include "XmlTreeViewCtrl.h"






class CLoadXML2MemDlg : public CDialog
{
// Construction
public:
	CLoadXML2MemDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLoadXML2MemDlg)
	enum { IDD = IDD_LOADXML2MEM_DIALOG };
	CTreeCtrl	m_Tree;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadXML2MemDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CXmlTreeViewCtrl m;

	// Generated message map functions
	//{{AFX_MSG(CLoadXML2MemDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADXML2MEMDLG_H__B4C79959_DB28_4150_9C06_B99B931D745B__INCLUDED_)
