// tttDlg.h : header file
//

#if !defined(AFX_TTTDLG_H__5F06D681_BA07_47E0_A457_CD3C51BB14A5__INCLUDED_)
#define AFX_TTTDLG_H__5F06D681_BA07_47E0_A457_CD3C51BB14A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// 因为是通过NetAPI 来获取网卡信息，所以需要包含其题头文件nb30.h
#include "nb30.h"


/////////////////////////////////////////////////////////////////////////////
// CTttDlg dialog
typedef struct _ASTAT_
{
	ADAPTER_STATUS adapt;
	NAME_BUFFER NameBuff[30];
}ASTAT, *PASTAT;


class CTttDlg : public CDialog
{
// Construction
public:
	// 定义一个存放返回网卡信息的变量
	ASTAT Adapter;

	CTttDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTttDlg)
	enum { IDD = IDD_TTT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTttDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTttDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TTTDLG_H__5F06D681_BA07_47E0_A457_CD3C51BB14A5__INCLUDED_)
