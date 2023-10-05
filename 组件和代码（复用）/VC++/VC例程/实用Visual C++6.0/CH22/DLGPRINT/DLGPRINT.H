// DlgPrint.h : main header file for the DLGPRINT application
//

#if !defined(AFX_DLGPRINT_H__8B30B438_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_)
#define AFX_DLGPRINT_H__8B30B438_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDlgPrintApp:
// See DlgPrint.cpp for the implementation of this class
//

class CDlgPrintApp : public CWinApp
{
public:
	CDlgPrintApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPrintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDlgPrintApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPRINT_H__8B30B438_6C2F_11CD_BC53_E9F379BB6D52__INCLUDED_)
