// Example4E.h : main header file for the EXAMPLE4E application
//

#if !defined(AFX_EXAMPLE4E_H__CCC00B46_A7A4_11D4_B71C_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4E_H__CCC00B46_A7A4_11D4_B71C_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample4EApp:
// See Example4E.cpp for the implementation of this class
//

class CExample4EApp : public CWinApp
{
public:
	CExample4EApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4EApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExample4EApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4E_H__CCC00B46_A7A4_11D4_B71C_0000B48A052A__INCLUDED_)
