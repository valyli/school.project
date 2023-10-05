// TryListInFormView.h : main header file for the TRYLISTINFORMVIEW application
//

#if !defined(AFX_TRYLISTINFORMVIEW_H__1D3B7884_4212_4B69_809F_CA132E2DCAFC__INCLUDED_)
#define AFX_TRYLISTINFORMVIEW_H__1D3B7884_4212_4B69_809F_CA132E2DCAFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTryListInFormViewApp:
// See TryListInFormView.cpp for the implementation of this class
//

class CTryListInFormViewApp : public CWinApp
{
public:
	CTryListInFormViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTryListInFormViewApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTryListInFormViewApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRYLISTINFORMVIEW_H__1D3B7884_4212_4B69_809F_CA132E2DCAFC__INCLUDED_)
