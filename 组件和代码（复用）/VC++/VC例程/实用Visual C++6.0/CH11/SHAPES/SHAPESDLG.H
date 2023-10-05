// ShapesDlg.h : header file
//

#if !defined(AFX_SHAPESDLG_H__907300C3_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_)
#define AFX_SHAPESDLG_H__907300C3_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CShapesDlg dialog

class CShapesDlg : public CDialog
{
// Construction
public:
	CImageList m_imagelist;
	CShapesDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CShapesDlg)
	enum { IDD = IDD_SHAPES_DIALOG };
	CComboBoxEx	m_combo;
	CTreeCtrl	m_tree;
	CListCtrl	m_list;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShapesDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShapesDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHAPESDLG_H__907300C3_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_)
