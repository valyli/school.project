// FileEdit.h : main header file for the FILEEDIT application
//

#if !defined(AFX_FILEEDIT_H__8B06B2A9_D652_11D2_BF13_E2747651D762__INCLUDED_)
#define AFX_FILEEDIT_H__8B06B2A9_D652_11D2_BF13_E2747651D762__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFileEditApp:
// See FileEdit.cpp for the implementation of this class
//

class CFileEditApp : public CWinApp
{
public:
	CFileEditApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileEditApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFileEditApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEEDIT_H__8B06B2A9_D652_11D2_BF13_E2747651D762__INCLUDED_)
