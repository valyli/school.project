// homework5.h : main header file for the HOMEWORK5 application
//

#if !defined(AFX_HOMEWORK5_H__A26C8F06_CBAA_11D5_9486_5254AB113BB2__INCLUDED_)
#define AFX_HOMEWORK5_H__A26C8F06_CBAA_11D5_9486_5254AB113BB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHomework5App:
// See homework5.cpp for the implementation of this class
//

class CHomework5App : public CWinApp
{
public:
	CHomework5App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomework5App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHomework5App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMEWORK5_H__A26C8F06_CBAA_11D5_9486_5254AB113BB2__INCLUDED_)
