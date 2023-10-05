// EnumIcons.h : Haupt-Header-Datei für die Anwendung ENUMICONS
//

#if !defined(AFX_ENUMICONS_H__4AA59603_85BB_4AD2_A58E_0EB56E51FEF1__INCLUDED_)
#define AFX_ENUMICONS_H__4AA59603_85BB_4AD2_A58E_0EB56E51FEF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// Hauptsymbole

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsApp:
// Siehe EnumIcons.cpp für die Implementierung dieser Klasse
//

class CEnumIconsApp : public CWinApp
{
public:
	CEnumIconsApp();

// Überladungen
	// Vom Klassenassistenten generierte Überladungen virtueller Funktionen
	//{{AFX_VIRTUAL(CEnumIconsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementierung

	//{{AFX_MSG(CEnumIconsApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ fügt unmittelbar vor der vorhergehenden Zeile zusätzliche Deklarationen ein.

#endif // !defined(AFX_ENUMICONS_H__4AA59603_85BB_4AD2_A58E_0EB56E51FEF1__INCLUDED_)
