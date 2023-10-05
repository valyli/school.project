// CDPlayer.h : main header file for the CDPLAYER application
//

#if !defined(AFX_CDPLAYER_H__69EFAE65_DBD8_11D2_BF13_CC601E893962__INCLUDED_)
#define AFX_CDPLAYER_H__69EFAE65_DBD8_11D2_BF13_CC601E893962__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCDPlayerApp:
// See CDPlayer.cpp for the implementation of this class
//

class CCDPlayerApp : public CWinApp
{
public:
	CCDPlayerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCDPlayerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCDPlayerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDPLAYER_H__69EFAE65_DBD8_11D2_BF13_CC601E893962__INCLUDED_)
