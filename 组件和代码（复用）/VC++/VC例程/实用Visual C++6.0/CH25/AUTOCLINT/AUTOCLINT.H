// Autoclint.h : main header file for the AUTOCLINT application
//

#if !defined(AFX_AUTOCLINT_H__21BB6E79_DD66_11D2_BF13_828252DAF362__INCLUDED_)
#define AFX_AUTOCLINT_H__21BB6E79_DD66_11D2_BF13_828252DAF362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoclintApp:
// See Autoclint.cpp for the implementation of this class
//

class CAutoclintApp : public CWinApp
{
public:
	CAutoclintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoclintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAutoclintApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCLINT_H__21BB6E79_DD66_11D2_BF13_828252DAF362__INCLUDED_)
