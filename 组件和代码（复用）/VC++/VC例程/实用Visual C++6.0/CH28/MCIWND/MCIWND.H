// mciWnd.h : main header file for the MCIWND application
//

#if !defined(AFX_MCIWND_H__69EFAE73_DBD8_11D2_BF13_CC601E893962__INCLUDED_)
#define AFX_MCIWND_H__69EFAE73_DBD8_11D2_BF13_CC601E893962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMciWndApp:
// See mciWnd.cpp for the implementation of this class
//

class CMciWndApp : public CWinApp
{
public:
	CMciWndApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciWndApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMciWndApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIWND_H__69EFAE73_DBD8_11D2_BF13_CC601E893962__INCLUDED_)
