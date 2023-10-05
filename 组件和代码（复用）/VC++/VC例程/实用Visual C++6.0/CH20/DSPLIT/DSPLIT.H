// Dsplit.h : main header file for the DSPLIT application
//

#if !defined(AFX_DSPLIT_H__0C15E285_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
#define AFX_DSPLIT_H__0C15E285_D487_11D2_BF13_87F5B9EBB265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDsplitApp:
// See Dsplit.cpp for the implementation of this class
//

class CDsplitApp : public CWinApp
{
public:
	CDsplitApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDsplitApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDsplitApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DSPLIT_H__0C15E285_D487_11D2_BF13_87F5B9EBB265__INCLUDED_)
