// DHCGBoardDemo.h : main header file for the DHCGBOARDDEMO application
//

#if !defined(AFX_DHCGBOARDDEMO_H__591A7389_C6AB_11D4_8E81_5254AB30C250__INCLUDED_)
#define AFX_DHCGBOARDDEMO_H__591A7389_C6AB_11D4_8E81_5254AB30C250__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoApp:
// See DHCGBoardDemo.cpp for the implementation of this class
//

class CDHCGBoardDemoApp : public CWinApp
{
public:
	CDHCGBoardDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHCGBoardDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDHCGBoardDemoApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DHCGBOARDDEMO_H__591A7389_C6AB_11D4_8E81_5254AB30C250__INCLUDED_)
