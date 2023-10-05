// Sound.h : main header file for the SOUND application
//

#if !defined(AFX_SOUND_H__27C9F385_D960_11D2_BF13_FB46B2140062__INCLUDED_)
#define AFX_SOUND_H__27C9F385_D960_11D2_BF13_FB46B2140062__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSoundApp:
// See Sound.cpp for the implementation of this class
//

class CSoundApp : public CWinApp
{
public:
	CSoundApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSoundApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSoundApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOUND_H__27C9F385_D960_11D2_BF13_FB46B2140062__INCLUDED_)
