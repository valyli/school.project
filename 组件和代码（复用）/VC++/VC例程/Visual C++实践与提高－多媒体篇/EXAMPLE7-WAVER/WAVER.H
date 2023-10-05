// waver.h : main header file for the WAVER application
//

#if !defined(AFX_WAVER_H__FEB2D333_9A3A_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_WAVER_H__FEB2D333_9A3A_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWaverApp:
// See waver.cpp for the implementation of this class
//

class CWaverApp : public CWinApp
{
public:
	CWaverApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaverApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWaverApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVER_H__FEB2D333_9A3A_11D4_9300_5254AB10AACA__INCLUDED_)
