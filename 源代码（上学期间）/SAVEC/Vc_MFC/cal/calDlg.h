// calDlg.h : header file
//

#if !defined(AFX_CALDLG_H__4CE150C6_E435_11D2_9EAD_00E04C6832A0__INCLUDED_)
#define AFX_CALDLG_H__4CE150C6_E435_11D2_9EAD_00E04C6832A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalDlg dialog

class CCalDlg : public CDialog
{
// Construction
public:
	CCalDlg(CWnd* pParent = NULL);	// standard constructor
//	void Num_to_Char(void);
	void Carry_Num(void);
	void Show_Input(void);
	void Show_Result(void);

// Dialog Data
	//{{AFX_DATA(CCalDlg)
	enum { IDD = IDD_CAL_DIALOG };
	CEdit	m_Result_Show;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	double Result_N;
	double Input_N;
	int Flag;
	int Point, Point_Place;
	int Can_Point;
	int Input_Button;
	int Run_Sign;
	char Result_Char[20];

	// Generated message map functions
	//{{AFX_MSG(CCalDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonNum0();
	afx_msg void OnButtonNum1();
	afx_msg void OnButtonJiahao();
	afx_msg void OnButtonPoint();
	afx_msg void OnButtonNum2();
	afx_msg void OnButtonNum9();
	afx_msg void OnButtonNum3();
	afx_msg void OnButtonNum4();
	afx_msg void OnButtonNum5();
	afx_msg void OnButtonNum6();
	afx_msg void OnButtonNum7();
	afx_msg void OnButtonNum8();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALDLG_H__4CE150C6_E435_11D2_9EAD_00E04C6832A0__INCLUDED_)
