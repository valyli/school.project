#if !defined(AFX_INPUT_H__88692BA3_76E1_11D4_986A_52544C1AEF84__INCLUDED_)
#define AFX_INPUT_H__88692BA3_76E1_11D4_986A_52544C1AEF84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Input.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInput dialog

class CInput : public CDialog
{
// Construction
public:
	void SetCaption(CString caption);
	CString GetEditString();
	void SetTextSelect(BOOL select);
	void SetEditText(CString text);
	void SetTitle(CString title);
	CInput(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInput)
	enum { IDD = IDD_DIALOG_INPUT };
	CEdit	m_EditCtrl;
	CString	m_EditString;
	CString	m_Title;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInput)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL EditSelect;
	CString	Caption;

	// Generated message map functions
	//{{AFX_MSG(CInput)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUT_H__88692BA3_76E1_11D4_986A_52544C1AEF84__INCLUDED_)
