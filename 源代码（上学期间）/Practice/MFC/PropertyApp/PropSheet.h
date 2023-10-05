#if !defined(AFX_PROPSHEET_H__35089155_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
#define AFX_PROPSHEET_H__35089155_4921_11D5_9EAD_00E04C6832A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PropSheet.h : header file
//
#include "PageA.h"
#include "PageB.h"

/////////////////////////////////////////////////////////////////////////////
// PropSheet

class PropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(PropSheet)

// Construction
public:
	PropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	PropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CPageA m_page1;
	CPageB m_page2;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PropSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~PropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(PropSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPSHEET_H__35089155_4921_11D5_9EAD_00E04C6832A0__INCLUDED_)
