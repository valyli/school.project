// MailClient.h : main header file for the MAILCLIENT application
//

#if !defined(AFX_MAILCLIENT_H__E087E9D3_DB17_11D2_BF13_AA406FC81D62__INCLUDED_)
#define AFX_MAILCLIENT_H__E087E9D3_DB17_11D2_BF13_AA406FC81D62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMailClientApp:
// See MailClient.cpp for the implementation of this class
//

class CMailClientApp : public CWinApp
{
public:
	CMailClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMailClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMailClientApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAILCLIENT_H__E087E9D3_DB17_11D2_BF13_AA406FC81D62__INCLUDED_)
