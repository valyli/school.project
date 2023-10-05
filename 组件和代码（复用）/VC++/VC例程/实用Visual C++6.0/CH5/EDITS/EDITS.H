// Edits.h : main header file for the EDITS application
//

#if !defined(AFX_EDITS_H__87ACADC4_A8EE_11D3_AEE1_00104B125379__INCLUDED_)
#define AFX_EDITS_H__87ACADC4_A8EE_11D3_AEE1_00104B125379__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CEditsApp:
// See Edits.cpp for the implementation of this class
//

class CEditsApp : public CWinApp
{
public:
	CEditsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEditsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITS_H__87ACADC4_A8EE_11D3_AEE1_00104B125379__INCLUDED_)
