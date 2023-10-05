// TestCycleTransferModule.h : main header file for the TESTCYCLETRANSFERMODULE application
//

#if !defined(AFX_TESTCYCLETRANSFERMODULE_H__6B03A54E_7E8D_45FD_A1FF_06C3ECEF75BE__INCLUDED_)
#define AFX_TESTCYCLETRANSFERMODULE_H__6B03A54E_7E8D_45FD_A1FF_06C3ECEF75BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCycleTransferModuleApp:
// See TestCycleTransferModule.cpp for the implementation of this class
//

class CTestCycleTransferModuleApp : public CWinApp
{
public:
	CTestCycleTransferModuleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCycleTransferModuleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestCycleTransferModuleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCYCLETRANSFERMODULE_H__6B03A54E_7E8D_45FD_A1FF_06C3ECEF75BE__INCLUDED_)
