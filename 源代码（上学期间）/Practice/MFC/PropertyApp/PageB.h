#if !defined(AFX_PAGEB_H__35089154_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
#define AFX_PAGEB_H__35089154_4921_11D5_9EAD_00E04C6832A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageB dialog

class CPageB : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageB)

// Construction
public:
	CPageB();
	~CPageB();

// Dialog Data
	//{{AFX_DATA(CPageB)
	enum { IDD = IDD_DIALOG2 };
	BOOL	m_check;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageB)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEB_H__35089154_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
