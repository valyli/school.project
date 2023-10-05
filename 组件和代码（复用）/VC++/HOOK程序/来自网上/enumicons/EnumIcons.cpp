// EnumIcons.cpp : Legt das Klassenverhalten für die Anwendung fest.
//

#include "stdafx.h"
#include "EnumIcons.h"
#include "EnumIconsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsApp

BEGIN_MESSAGE_MAP(CEnumIconsApp, CWinApp)
	//{{AFX_MSG_MAP(CEnumIconsApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsApp Konstruktion

CEnumIconsApp::CEnumIconsApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// Das einzige CEnumIconsApp-Objekt

CEnumIconsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEnumIconsApp Initialisierung

BOOL CEnumIconsApp::InitInstance()
{
	// Standardinitialisierung

	CEnumIconsDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Da das Dialogfeld geschlossen wurde, FALSE zurückliefern, so dass wir die
	//  Anwendung verlassen, anstatt das Nachrichtensystem der Anwendung zu starten.
	return FALSE;
}
