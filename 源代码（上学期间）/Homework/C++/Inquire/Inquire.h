// Inquire.h : main header file for the INQUIRE application
//

#if !defined(AFX_INQUIRE_H__12B2F585_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
#define AFX_INQUIRE_H__12B2F585_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CInquireApp:
// See Inquire.cpp for the implementation of this class
//

class CInquireApp : public CWinApp
{
public:
	LOGFONT m_logFont;	// 用于保存文档缺省字型。
	CInquireApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInquireApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CInquireApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INQUIRE_H__12B2F585_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
