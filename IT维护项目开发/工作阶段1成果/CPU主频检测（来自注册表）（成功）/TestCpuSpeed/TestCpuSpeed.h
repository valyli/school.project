// TestCpuSpeed.h : main header file for the TESTCPUSPEED application
//

#if !defined(AFX_TESTCPUSPEED_H__9E235EC1_506F_432B_9BA4_9B1344366B6B__INCLUDED_)
#define AFX_TESTCPUSPEED_H__9E235EC1_506F_432B_9BA4_9B1344366B6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestCpuSpeedApp:
// See TestCpuSpeed.cpp for the implementation of this class
//

class CTestCpuSpeedApp : public CWinApp
{
public:
	CTestCpuSpeedApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestCpuSpeedApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestCpuSpeedApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTCPUSPEED_H__9E235EC1_506F_432B_9BA4_9B1344366B6B__INCLUDED_)
