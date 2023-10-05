// ClientHookMonitorDemo.h : main header file for the CLIENTHOOKMONITORDEMO application
//

#if !defined(AFX_CLIENTHOOKMONITORDEMO_H__5CB3326B_A70E_4A53_8A27_3F3FD69B7C2F__INCLUDED_)
#define AFX_CLIENTHOOKMONITORDEMO_H__5CB3326B_A70E_4A53_8A27_3F3FD69B7C2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CClientHookMonitorDemoApp:
// See ClientHookMonitorDemo.cpp for the implementation of this class
//

class CClientHookMonitorDemoApp : public CWinApp
{
public:
	CClientHookMonitorDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientHookMonitorDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientHookMonitorDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTHOOKMONITORDEMO_H__5CB3326B_A70E_4A53_8A27_3F3FD69B7C2F__INCLUDED_)
