// ImageDlg.h : header file
//

#if !defined(AFX_IMAGEDLG_H__907300B5_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_)
#define AFX_IMAGEDLG_H__907300B5_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CImageDlg dialog

class CImageDlg : public CDialog
{
// Construction
public:
	CBitmap m_bmp;
	CImageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CImageDlg)
	enum { IDD = IDD_IMAGE_DIALOG };
	CStatic	m_i5;
	CStatic	m_i4;
	CStatic	m_i3;
	CStatic	m_i1;
	CStatic	m_i2;
	CStatic	m_b1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CImageDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGEDLG_H__907300B5_AF40_11D3_B25B_ACE5E3DA1335__INCLUDED_)
