// LoadXML2Mem.h : main header file for the LOADXML2MEM application
//

#if !defined(AFX_LOADXML2MEM_H__BFEFCFEA_9C1C_4E43_8E24_54969729192F__INCLUDED_)
#define AFX_LOADXML2MEM_H__BFEFCFEA_9C1C_4E43_8E24_54969729192F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLoadXML2MemApp:
// See LoadXML2Mem.cpp for the implementation of this class
//

class CLoadXML2MemApp : public CWinApp
{
public:
	CLoadXML2MemApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadXML2MemApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLoadXML2MemApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOADXML2MEM_H__BFEFCFEA_9C1C_4E43_8E24_54969729192F__INCLUDED_)
