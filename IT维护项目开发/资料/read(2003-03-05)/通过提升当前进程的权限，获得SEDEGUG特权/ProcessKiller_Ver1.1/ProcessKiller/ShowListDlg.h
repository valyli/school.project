#if !defined(AFX_SHOWLISTDLG_H__78FCED69_24A4_405A_93B1_CC4DE20C7CA8__INCLUDED_)
#define AFX_SHOWLISTDLG_H__78FCED69_24A4_405A_93B1_CC4DE20C7CA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowListDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CShowListDlg dialog

class CShowListDlg : public CDialog
{
// Construction
public:
	BOOL ShowModulesList( DWORD dwPID );
	CShowListDlg(CWnd* pParent = NULL);   // standard constructor
	~CShowListDlg();

// Dialog Data
	//{{AFX_DATA(CShowListDlg)
	enum { IDD = IDD_SHOWLIST_DIALOG };
	CListCtrl	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowListDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowListDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWLISTDLG_H__78FCED69_24A4_405A_93B1_CC4DE20C7CA8__INCLUDED_)
