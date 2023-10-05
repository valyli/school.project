// TestBios.h : main header file for the TESTBIOS application
//

#if !defined(AFX_TESTBIOS_H__4C81A4A4_51D5_459D_A86C_3B522E5C86EC__INCLUDED_)
#define AFX_TESTBIOS_H__4C81A4A4_51D5_459D_A86C_3B522E5C86EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestBiosApp:
// See TestBios.cpp for the implementation of this class
//

class CTestBiosApp : public CWinApp
{
public:
	CTestBiosApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestBiosApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestBiosApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTBIOS_H__4C81A4A4_51D5_459D_A86C_3B522E5C86EC__INCLUDED_)
