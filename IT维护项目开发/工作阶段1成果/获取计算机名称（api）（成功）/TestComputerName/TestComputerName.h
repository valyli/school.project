// TestComputerName.h : main header file for the TESTCOMPUTERNAME application
//

#if !defined(AFX_TESTCOMPUTERNAME_H__64D91540_36F9_4C25_8C4E_516D931A602A__INCLUDED_)
#define AFX_TESTCOMPUTERNAME_H__64D91540_36F9_4C25_8C4E_516D931A602A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestComputerNameApp:
// See TestComputerName.cpp for the implementation of this class
//

class CTestComputerNameApp : public CWinApp
{
public:
	CTestComputerNameApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestComputerNameApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestComputerNameApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCOMPUTERNAME_H__64D91540_36F9_4C25_8C4E_516D931A602A__INCLUDED_)
