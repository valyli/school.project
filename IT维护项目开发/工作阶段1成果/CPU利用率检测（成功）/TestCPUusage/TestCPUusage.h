// TestCPUusage.h : main header file for the TESTCPUUSAGE application
//

#if !defined(AFX_TESTCPUUSAGE_H__5244D0D0_6ADC_4DAF_8AB5_EE831937EB5B__INCLUDED_)
#define AFX_TESTCPUUSAGE_H__5244D0D0_6ADC_4DAF_8AB5_EE831937EB5B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCPUusageApp:
// See TestCPUusage.cpp for the implementation of this class
//

class CTestCPUusageApp : public CWinApp
{
public:
	CTestCPUusageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCPUusageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestCPUusageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCPUUSAGE_H__5244D0D0_6ADC_4DAF_8AB5_EE831937EB5B__INCLUDED_)
