// TestDlgDlg.h : header file
//

#if !defined(AFX_TESTDLGDLG_H__8AABF251_1615_42A0_BC01_D3CBCE08E1AD__INCLUDED_)
#define AFX_TESTDLGDLG_H__8AABF251_1615_42A0_BC01_D3CBCE08E1AD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define			WM_DRIVERDATA				WM_USER+101
#define			WM_DRIVER2DATA				WM_USER+102
#define			WM_COMDATA					WM_USER+103
/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog
//#include "test.h"

#include "ManageData.h"

struct DriverParam
{
	HWND    hwnd;
};
struct Driver2Param
{
	HWND    hwnd;
};
struct ComParam
{
	HWND    hwnd;
};

//�洢��ѭ��������
struct CycleStruct
{
	int EventID;
	//����Ҫ���õĶ�̬��ľ��
	HMODULE hLibrary;
	//����ָ�붨��
	//��lpfn���庯��ָ��
	//����Ҫ�󣬺���ָ��ķ���ֵ����bool��
	bool (FAR *lpfn)(CManageData &Data);
	//��¼���һ�ε���ʱ��
	COleDateTime LastTransferTime;
	Transfer_S2C_Struct TransferData;
};

//����ѭ������
typedef CArray<CycleStruct, CycleStruct&> CArrayCycleStruct;


class CTestDlgDlg : public CDialog
{
// Construction
public:
	void InitCreate();
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlgDlg)
	enum { IDD = IDD_TESTDLG_DIALOG };
	CListBox	m_list;
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
	afx_msg int OnButton1();
	afx_msg int OnButton2();
	//}}AFX_MSG
	afx_msg void OnDriverData(WPARAM wParam,LPARAM lParam);
	afx_msg void OnDriver2Data(WPARAM wParam,LPARAM lParam);
	afx_msg void OnComData(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLGDLG_H__8AABF251_1615_42A0_BC01_D3CBCE08E1AD__INCLUDED_)
