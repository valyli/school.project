#if !defined(AFX_PAGEA_H__35089153_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
#define AFX_PAGEA_H__35089153_4921_11D5_9EAD_00E04C6832A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageA dialog

class CPageA : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageA)

// Construction
public:
	CPageA();
	~CPageA();

// Dialog Data
	//{{AFX_DATA(CPageA)
	enum { IDD = IDD_DIALOG1 };
	CString	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageA)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEA_H__35089153_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
