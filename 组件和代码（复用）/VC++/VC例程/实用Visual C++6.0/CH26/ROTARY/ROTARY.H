#if !defined(AFX_ROTARY_H__721757AC_EE5C_11D2_BF13_444553540000__INCLUDED_)
#define AFX_ROTARY_H__721757AC_EE5C_11D2_BF13_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Rotary.h : main header file for ROTARY.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRotaryApp : See Rotary.cpp for implementation.

class CRotaryApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROTARY_H__721757AC_EE5C_11D2_BF13_444553540000__INCLUDED)
