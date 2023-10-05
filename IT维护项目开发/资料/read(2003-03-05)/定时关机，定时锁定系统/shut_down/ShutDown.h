// ShutDown.h : main header file for the SHUTDOWN application
//

#if !defined(AFX_SHUTDOWN_H__1AD5EEC7_6FA2_11D4_A7B3_0088CC164534__INCLUDED_)
#define AFX_SHUTDOWN_H__1AD5EEC7_6FA2_11D4_A7B3_0088CC164534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShutDownApp:
// See ShutDown.cpp for the implementation of this class
//

class CShutDownApp : public CWinApp
{
public:
	CShutDownApp();
	
	CString KeyChanged(CString pwd);

	CString strCheck;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShutDownApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShutDownApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	BOOL AlreadyRunning();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUTDOWN_H__1AD5EEC7_6FA2_11D4_A7B3_0088CC164534__INCLUDED_)
