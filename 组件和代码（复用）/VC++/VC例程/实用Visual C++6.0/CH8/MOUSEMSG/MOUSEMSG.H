// MouseMsg.h : main header file for the MOUSEMSG application
//

#if !defined(AFX_MOUSEMSG_H__3FCF3064_ACD9_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_MOUSEMSG_H__3FCF3064_ACD9_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMouseMsgApp:
// See MouseMsg.cpp for the implementation of this class
//

class CMouseMsgApp : public CWinApp
{
public:
	CMouseMsgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseMsgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMouseMsgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSEMSG_H__3FCF3064_ACD9_11D3_AEE1_00104B125379__INCLUDED_)
