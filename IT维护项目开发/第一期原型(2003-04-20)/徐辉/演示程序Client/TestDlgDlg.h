// TestDlgDlg.h : header file
//

#if !defined(AFX_TESTDLGDLG_H__8AABF251_1615_42A0_BC01_D3CBCE08E1AD__INCLUDED_)
#define AFX_TESTDLGDLG_H__8AABF251_1615_42A0_BC01_D3CBCE08E1AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define			WM_DRIVERDATA				WM_USER+101
/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog
//#include "test.h"

#include "ManageData.h"

//存储在循环数组中
struct CycleStruct
{
	int EventID;
	//保存要调用的动态库的句柄
	HMODULE hLibrary;
	//函数指针定义
	//用lpfn定义函数指针
	//根据要求，函数指针的返回值都是bool型
	bool (FAR *lpfn)(CManageData &Data);
	//记录最后一次调用时间
	COleDateTime LastTransferTime;
	Transfer_S2C_Struct TransferData;
};

//定义循环数组
typedef CArray<CycleStruct, CycleStruct&> CArrayCycleStruct;


class CTestDlgDlg : public CDialog
{
// Construction
public:
	void checkTest();
	void InitCreate();
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlgDlg)
	enum { IDD = IDD_TESTDLG_DIALOG };
	BOOL	m_check1;
	BOOL	m_check2;
	BOOL	m_check3;
	BOOL	m_check4;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnIp();
	afx_msg void OnCheck1();
	afx_msg void OnCheck2();
	afx_msg void OnCheck3();
	afx_msg void OnCheck4();
	virtual void OnCancel();
	//}}AFX_MSG
	/*自定义的消息函数*/
	afx_msg void OnDriverData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLGDLG_H__8AABF251_1615_42A0_BC01_D3CBCE08E1AD__INCLUDED_)
