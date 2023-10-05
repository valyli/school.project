// ScriptDocEngine.cpp : implementation file
//
//Copyright Andrew A. Garbuzov

#include "stdafx.h"
#include "AXDocContainer.h"
#include "ScriptDocEngine.h"
#include "ScriptDocument.h"

#include <AFXPRIV.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptDocEngine

IMPLEMENT_DYNAMIC(CScriptDocEngine, CScriptEngine)

CScriptDocEngine::CScriptDocEngine()
{
	m_pDoc=NULL;
}

CScriptDocEngine::~CScriptDocEngine()
{
}


BEGIN_MESSAGE_MAP(CScriptDocEngine, CScriptEngine)
	//{{AFX_MSG_MAP(CScriptDocEngine)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptDocEngine message handlers
HRESULT CScriptDocEngine::OnGetItemInfo(
		/* [in] */ LPCOLESTR   pstrName,
		/* [in] */ DWORD       dwReturnMask,
		/* [out]*/ IUnknown**  ppUnknownItem,
		/* [out]*/ ITypeInfo** ppTypeInfo)
{
	USES_CONVERSION;

	HRESULT hr=CScriptEngine::OnGetItemInfo(pstrName,dwReturnMask,ppUnknownItem,ppTypeInfo);
	
	hr=TYPE_E_ELEMENTNOTFOUND;
	if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
	{
		if (!ppTypeInfo)
			return E_INVALIDARG;
		*ppTypeInfo = NULL;
	}

	if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
	{
		if (!ppUnknownItem)
			return E_INVALIDARG;
		*ppUnknownItem = NULL;
	}


	TCHAR* lpstrItemName=OLE2T(pstrName);
	IUnknown* pUnk=0;

	if(!_tcscmp(_T("Document"), lpstrItemName) && m_pDoc)
	{
		pUnk=m_pDoc->GetIDispatch(FALSE);
	}
	
	if(pUnk)
	{
		if (dwReturnMask & SCRIPTINFO_ITYPEINFO)
		{
			IProvideClassInfo* pProvideClassInfo = NULL;
			hr = pUnk->QueryInterface(IID_IProvideClassInfo, (void**)&pProvideClassInfo);
			
			// if the object supports IprovideClassInfo ...
			if (SUCCEEDED(hr) && pProvideClassInfo != NULL)
			{
				hr = pProvideClassInfo->GetClassInfo(ppTypeInfo);
				pProvideClassInfo->Release();
			}
		}

		if (dwReturnMask & SCRIPTINFO_IUNKNOWN)
		{
			pUnk->AddRef();
			*ppUnknownItem=pUnk;
			hr=S_OK;
		}
	}

	return hr;
}
