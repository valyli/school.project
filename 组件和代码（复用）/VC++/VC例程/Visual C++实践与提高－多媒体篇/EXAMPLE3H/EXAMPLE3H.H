// Example3H.h : main header file for the EXAMPLE3H application
//

#if !defined(AFX_EXAMPLE3H_H__13743966_9FE8_11D4_B67F_444553540000__INCLUDED_)
#define AFX_EXAMPLE3H_H__13743966_9FE8_11D4_B67F_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExample3HApp:
// See Example3H.cpp for the implementation of this class
//

class CExample3HApp : public CWinApp
{
public:
	CExample3HApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExample3HApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExample3HApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXAMPLE3H_H__13743966_9FE8_11D4_B67F_444553540000__INCLUDED_)
