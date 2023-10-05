// CalculatorDlg.h : header file
//

#if !defined(AFX_CALCULATORDLG_H__BE8DB347_328E_11D5_82DA_00E04C3B2494__INCLUDED_)
#define AFX_CALCULATORDLG_H__BE8DB347_328E_11D5_82DA_00E04C3B2494__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCalculatorDlg dialog

class CCalculatorDlg : public CDialog
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// standard constructor
	void Getnum(int);
	void Showresult();
	void Endnewnum();
	void Oldproc();
// Dialog Data
	//{{AFX_DATA(CCalculatorDlg)
	enum { IDD = IDD_CALCULATOR_DIALOG };
	double	m_Shownum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	double Oldnum, Newnum;
	int Point;
	int Firstnum;
	int Lastproc;
	int Equed;

	// Generated message map functions
	//{{AFX_MSG(CCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonNum0();
	afx_msg void OnButtonNum1();
	afx_msg void OnButtonNum2();
	afx_msg void OnButtonNum3();
	afx_msg void OnButtonNum4();
	afx_msg void OnButtonNum5();
	afx_msg void OnButtonNum6();
	afx_msg void OnButtonNum7();
	afx_msg void OnButtonNum8();
	afx_msg void OnButtonNum9();
	afx_msg void OnButtonPoint();
	afx_msg void OnButtonCe();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonC();
	afx_msg void OnButtonDec();
	afx_msg void OnButtonDiv();
	afx_msg void OnButtonMul();
	afx_msg void OnButtonEqu();
	afx_msg void OnButtonSin();
	afx_msg void OnButtonCos();
	afx_msg void OnButtonLog();
	afx_msg void OnButtonLn();
	afx_msg void OnButtonSqr();
	afx_msg void OnButtonSqrt();
	afx_msg void OnButtonEx();
	afx_msg void OnButtonX();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALCULATORDLG_H__BE8DB347_328E_11D5_82DA_00E04C3B2494__INCLUDED_)
