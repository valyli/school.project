// ClientTransferModuleDemo.h : main header file for the CLIENTTRANSFERMODULEDEMO application
//

#if !defined(AFX_CLIENTTRANSFERMODULEDEMO_H__0BFD4A2F_21F0_4F31_8B21_8B14BEA46610__INCLUDED_)
#define AFX_CLIENTTRANSFERMODULEDEMO_H__0BFD4A2F_21F0_4F31_8B21_8B14BEA46610__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientTransferModuleDemoApp:
// See ClientTransferModuleDemo.cpp for the implementation of this class
//

class CClientTransferModuleDemoApp : public CWinApp
{
public:
	CClientTransferModuleDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientTransferModuleDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientTransferModuleDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTTRANSFERMODULEDEMO_H__0BFD4A2F_21F0_4F31_8B21_8B14BEA46610__INCLUDED_)
