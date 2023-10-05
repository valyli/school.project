// PropertiesDlg.h : header file
//

#if !defined(AFX_PROPERTIESDLG_H__5AB24D47_A824_11D3_B25B_A98DD0C15F31__INCLUDED_)
#define AFX_PROPERTIESDLG_H__5AB24D47_A824_11D3_B25B_A98DD0C15F31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPropertiesDlg dialog

class CPropertiesDlg : public CDialog
{
// Construction
public:
	CPropertiesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CPropertiesDlg)
	enum { IDD = IDD_PROPERTIES_DIALOG };
	int		m_nAge;
	CString	m_strName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPropertiesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESDLG_H__5AB24D47_A824_11D3_B25B_A98DD0C15F31__INCLUDED_)
