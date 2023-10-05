// exmidi.h : main header file for the EXMIDI application
//

#if !defined(AFX_EXMIDI_H__B9232CC5_9A48_11D4_9300_5254AB10AACA__INCLUDED_)
#define AFX_EXMIDI_H__B9232CC5_9A48_11D4_9300_5254AB10AACA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CExmidiApp:
// See exmidi.cpp for the implementation of this class
//

class CExmidiApp : public CWinApp
{
public:
	CExmidiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExmidiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CExmidiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXMIDI_H__B9232CC5_9A48_11D4_9300_5254AB10AACA__INCLUDED_)
