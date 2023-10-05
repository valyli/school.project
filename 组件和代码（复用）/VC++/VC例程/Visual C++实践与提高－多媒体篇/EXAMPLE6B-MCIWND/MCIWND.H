// mciwnd.h : main header file for the MCIWND application
//

#if !defined(AFX_MCIWND_H__74C54D73_9629_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_MCIWND_H__74C54D73_9629_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "cmci.h"
/////////////////////////////////////////////////////////////////////////////
// CMciwndApp:
// See mciwnd.cpp for the implementation of this class
//

class CMciwndApp : public CWinApp
{
public:
	CMciwndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciwndApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMciwndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIWND_H__74C54D73_9629_11D4_9300_5254AB10AACA__INCLUDED_)
