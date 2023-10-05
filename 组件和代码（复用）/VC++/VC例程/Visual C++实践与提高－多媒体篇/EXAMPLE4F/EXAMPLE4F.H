// Example4F.h : main header file for the EXAMPLE4F application
//

#if !defined(AFX_EXAMPLE4F_H__F9A23EA4_A9C8_11D4_8EAF_0000B48A052A__INCLUDED_)
#define AFX_EXAMPLE4F_H__F9A23EA4_A9C8_11D4_8EAF_0000B48A052A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample4FApp:
// See Example4F.cpp for the implementation of this class
//

class CExample4FApp : public CWinApp
{
public:
	CExample4FApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample4FApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExample4FApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE4F_H__F9A23EA4_A9C8_11D4_8EAF_0000B48A052A__INCLUDED_)
