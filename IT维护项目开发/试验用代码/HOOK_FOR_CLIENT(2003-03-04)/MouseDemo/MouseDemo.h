// MouseDemo.h : main header file for the MOUSEDEMO application
//

#if !defined(AFX_MOUSEDEMO_H__E4259AB7_0ED4_49CA_9242_723FE2C9D8CA__INCLUDED_)
#define AFX_MOUSEDEMO_H__E4259AB7_0ED4_49CA_9242_723FE2C9D8CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ClientHook.h"

/////////////////////////////////////////////////////////////////////////////
// CMouseDemoApp:
// See MouseDemo.cpp for the implementation of this class
//

class CMouseDemoApp : public CWinApp
{
public:
	CMouseDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMouseDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEDEMO_H__E4259AB7_0ED4_49CA_9242_723FE2C9D8CA__INCLUDED_)
