// Properties.h : main header file for the PROPERTIES application
//

#if !defined(AFX_PROPERTIES_H__5AB24D45_A824_11D3_B25B_A98DD0C15F31__INCLUDED_)
#define AFX_PROPERTIES_H__5AB24D45_A824_11D3_B25B_A98DD0C15F31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPropertiesApp:
// See Properties.cpp for the implementation of this class
//

class CPropertiesApp : public CWinApp
{
public:
	CPropertiesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPropertiesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIES_H__5AB24D45_A824_11D3_B25B_A98DD0C15F31__INCLUDED_)
