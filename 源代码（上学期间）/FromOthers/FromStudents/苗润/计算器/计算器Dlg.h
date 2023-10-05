// 计算器Dlg.h : header file
//

#if !defined(AFX_DLG_H__90DC7126_2F9B_11D5_95A3_D3C454A79810__INCLUDED_)
#define AFX_DLG_H__90DC7126_2F9B_11D5_95A3_D3C454A79810__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"           // 用于数学运算的库函数
/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
	double number1,number2;         // 用于存储计算的变量
	int NumberState,OperationState; // Number用于赋值，Operation用于操作
	void Value();                   // 用于实现对数的运算

// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	double	m_number;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnNumberKey(UINT nID);
	afx_msg void OnOperationKey(UINT nID);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__90DC7126_2F9B_11D5_95A3_D3C454A79810__INCLUDED_)
