// Persist.h : main header file for the PERSIST application
//

#if !defined(AFX_PERSIST_H__0E266267_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_)
#define AFX_PERSIST_H__0E266267_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPersistApp:
// See Persist.cpp for the implementation of this class
//

class CPersistApp : public CWinApp
{
public:
	CPersistApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPersistApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPersistApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PERSIST_H__0E266267_D58C_11D2_BF13_BC2C81A6F265__INCLUDED_)
