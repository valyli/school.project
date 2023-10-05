// AutoATL.h : main header file for the AUTOATL application
//

#if !defined(AFX_AUTOATL_H__8BE69027_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)
#define AFX_AUTOATL_H__8BE69027_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "AutoATL_i.h"

/////////////////////////////////////////////////////////////////////////////
// CAutoATLApp:
// See AutoATL.cpp for the implementation of this class
//

class CAutoATLApp : public CWinApp,
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAutoATLApp, &CLSID_Application>,
	public IConnectionPointContainerImpl<CAutoATLApp>,
	public IDispatchImpl<IApplication, &IID_IApplication, &LIBID_AutoATLLib>
{
public:
	STDMETHOD(get_ActiveDocument)(/*[out, retval]*/ IDocument* *pVal);
	STDMETHOD(Beep)();
	CAutoATLApp();

DECLARE_CLASSFACTORY_SINGLETON(CAutoATLApp)

DECLARE_REGISTRY_RESOURCEID(IDR_APPLICATION)
DECLARE_NOT_AGGREGATABLE(CAutoATLApp)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CAutoATLApp)
	COM_INTERFACE_ENTRY(IApplication)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CAutoATLApp)
END_CONNECTION_POINT_MAP()

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoATLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CAutoATLApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOATL_H__8BE69027_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)
