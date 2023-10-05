// ScrollBar.h : main header file for the SCROLLBAR application
//

#if !defined(AFX_SCROLLBAR_H__DA4733A6_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
#define AFX_SCROLLBAR_H__DA4733A6_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CScrollBarApp:
// See ScrollBar.cpp for the implementation of this class
//

class CScrollBarApp : public CWinApp
{
public:
	CScrollBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CScrollBarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CScrollBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCROLLBAR_H__DA4733A6_A891_11D3_B25B_E4FA8DFC1520__INCLUDED_)
