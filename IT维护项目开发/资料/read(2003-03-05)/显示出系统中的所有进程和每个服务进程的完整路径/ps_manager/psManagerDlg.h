// psManagerDlg.h : header file
//

#if !defined(AFX_PSMANAGERDLG_H__8D43E576_4212_11D4_B568_005004FF1036__INCLUDED_)
#define AFX_PSMANAGERDLG_H__8D43E576_4212_11D4_B568_005004FF1036__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CPsManagerDlg dialog

class CPsManagerDlg : public CDialog
{
// Construction
public:
	CPsManagerDlg(CWnd* pParent = NULL);	// standard constructor
	
public:
	class CProcessesList : public CListCtrl
	{
	public:
		CProcessesList();
		int FindPIDIndex(DWORD pid );
		void DeleteZoobieItem(unsigned long aProcesses[],DWORD cProcess);
		
	protected:
		BOOL m_bLastSortAsc;
		int m_nLastSortCol;

	protected:
		int FindIndex( DWORD dw );
		static int CALLBACK CompareEntries( LPARAM lp1, LPARAM lp2, LPARAM lColSpec );
		virtual void PreSubclassWindow();
		afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
		DECLARE_MESSAGE_MAP()
	};

// Dialog Data
	//{{AFX_DATA(CPsManagerDlg)
	enum { IDD = IDD_PSMANAGER_DIALOG };
	CProcessesList	m_ctlProcesses;
	//}}AFX_DATA
	void RefreshList();
	BOOL CopySelectedItem();

//---------------------------------------------------------------------------
// attributes
//---------------------------------------------------------------------------
protected:
	DWORD m_dwSelectedPID;
	CString m_sSelectedName;
	CString m_sSelectedPath;

public:
	DWORD GetSelectedPID() const;
	CString GetSelectedName() const;
	CString GetSelectedPath() const;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPsManagerDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CPsManagerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRefresh();
	afx_msg void OnTerminate();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnHaisan();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSMANAGERDLG_H__8D43E576_4212_11D4_B568_005004FF1036__INCLUDED_)
