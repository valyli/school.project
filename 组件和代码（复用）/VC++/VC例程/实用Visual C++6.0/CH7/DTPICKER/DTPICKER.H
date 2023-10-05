// dtpicker.h : main header file for the DTPICKER application
//

#if !defined(AFX_DTPICKER_H__EA4F0BC5_B01F_11D3_B25B_ED021A88CF34__INCLUDED_)
#define AFX_DTPICKER_H__EA4F0BC5_B01F_11D3_B25B_ED021A88CF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDtpickerApp:
// See dtpicker.cpp for the implementation of this class
//

class CDtpickerApp : public CWinApp
{
public:
	CDtpickerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDtpickerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDtpickerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DTPICKER_H__EA4F0BC5_B01F_11D3_B25B_ED021A88CF34__INCLUDED_)
