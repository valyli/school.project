// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__8BE69029_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)
#define AFX_STDAFX_H__8BE69029_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


	#define _ATL_APARTMENT_THREADED

#define DECLARE_DYNCREATE_ATL(class_name) \
	DECLARE_DYNCREATE(class_name) 

#define IMPLEMENT_DYNCREATE_ATL(class_name, base_class_name) \
	CObject* PASCAL class_name::CreateObject() \
		{ CComObject<class_name>* pObj = NULL; \
		  HRESULT hr = CComObject<class_name>::CreateInstance(&pObj); \
		  if (FAILED(hr)) { AfxThrowOleException(hr); } \
		  pObj->InternalAddRef(); \
		  return pObj; } \
	IMPLEMENT_RUNTIMECLASS(class_name, base_class_name, 0xFFFF, \
		class_name::CreateObject)

#define METHOD_PROLOGUE_ATL AFX_MANAGE_STATE(m_pModuleState);

#define m_dwRef						m_dwRefAtl
#define m_pOuterUnknown				m_pOuterUnknownAtl
#define InternalQueryInterface	InternalQueryInterfaceAtl
#define InternalAddRef				InternalAddRefAtl
#define InternalRelease				InternalReleaseAtl
#include <atlbase.h>
//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
class CAutoATLModule : public CComModule
{
public:
	bool m_bATLInited;
	CAutoATLModule();
	~CAutoATLModule();

	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CAutoATLModule _Module;
#include <atlcom.h>

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__8BE69029_68EF_11D2_9AE7_00A0C9E52DCB__INCLUDED_)
