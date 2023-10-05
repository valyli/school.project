// ServerJNITLVModuleDemo.h : main header file for the SERVERJNITLVMODULEDEMO application
//

#if !defined(AFX_SERVERJNITLVMODULEDEMO_H__157CB39F_23BB_4093_B62D_007721BC845A__INCLUDED_)
#define AFX_SERVERJNITLVMODULEDEMO_H__157CB39F_23BB_4093_B62D_007721BC845A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CServerJNITLVModuleDemoApp:
// See ServerJNITLVModuleDemo.cpp for the implementation of this class
//

class CServerJNITLVModuleDemoApp : public CWinApp
{
public:
	CServerJNITLVModuleDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerJNITLVModuleDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CServerJNITLVModuleDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERJNITLVMODULEDEMO_H__157CB39F_23BB_4093_B62D_007721BC845A__INCLUDED_)
