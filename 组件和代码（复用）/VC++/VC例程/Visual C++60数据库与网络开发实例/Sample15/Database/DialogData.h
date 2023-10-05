#if !defined(AFX_DIALOGDATA_H__C3797637_442D_11D2_953B_CDD998FF14B6__INCLUDED_)
#define AFX_DIALOGDATA_H__C3797637_442D_11D2_953B_CDD998FF14B6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DialogData.h : header file
//

#include "RecordsetEmployees.h"

/////////////////////////////////////////////////////////////////////////////
// CDialogData dialog

class CDialogData : public CDialog
{
// Construction
public:
	CDialogData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDialogData)
	enum { IDD = IDD_DIALOG_DATA };
	CRecordsetEmployees*	m_pSet;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDialogData)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGDATA_H__C3797637_442D_11D2_953B_CDD998FF14B6__INCLUDED_)
