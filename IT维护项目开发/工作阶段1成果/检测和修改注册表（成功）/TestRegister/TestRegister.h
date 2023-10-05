// TestRegister.h : main header file for the TESTREGISTER application
//

#if !defined(AFX_TESTREGISTER_H__675336AC_3313_44B2_90DE_D02893A8A483__INCLUDED_)
#define AFX_TESTREGISTER_H__675336AC_3313_44B2_90DE_D02893A8A483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestRegisterApp:
// See TestRegister.cpp for the implementation of this class
//

class CTestRegisterApp : public CWinApp
{
public:
	CTestRegisterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestRegisterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestRegisterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTREGISTER_H__675336AC_3313_44B2_90DE_D02893A8A483__INCLUDED_)
