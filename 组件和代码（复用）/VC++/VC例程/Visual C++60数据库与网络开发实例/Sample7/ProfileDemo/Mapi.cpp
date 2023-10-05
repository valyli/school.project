// Mapi.cpp : implementation file
// 
// Written by Christopher W. Backen - VIZ Group, 1998
// 
// Simple MAPI Class to help someone Add/Delete messaging profiles,
// configure messaging services, add/delete messaging services,
// configure messaging services, and set default messaging stores.
//
// For Service Names, please consult the MAPISVC.INF file located
// in \winnt\system32
// 
// Tested on Windows NT 4.0 and Visual C++ 6.0

#include "stdafx.h"
#include "Mapi.h"
#include "mapidefs.h"
#include "edkmdb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMapi

CMapi::CMapi()
{
}

CMapi::~CMapi()
{
}


BEGIN_MESSAGE_MAP(CMapi, CWnd)
	//{{AFX_MSG_MAP(CMapi)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMapi message handlers

HRESULT CMapi::Initialize()
{
	try
	{
		hr = MAPIInitialize(NULL);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::AdminProfiles()
{
	try
	{
		hr = MAPIAdminProfiles(0, &pProfAdmin);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::CreateNewProfile(LPSTR szProfile)
{
	try
	{
		hr = pProfAdmin->CreateProfile(szProfile, NULL, 0, 0);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::LogonDefaultEx()
{
	try
	{
		hr = MAPILogonEx(0, NULL, NULL, MAPI_NO_MAIL | MAPI_USE_DEFAULT,
			&pSession);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::LogonNewEx()
{
	try
	{
		hr = MAPILogonEx(0, NULL, NULL, MAPI_NO_MAIL | MAPI_NEW_SESSION,
                           &pSession);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::OpenAdminServices()
{
	try
	{
		hr = pSession->AdminServices(0, &pSvcAdmin);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::CreateMessagingService(LPTSTR lpszService, LPTSTR lpszDisplayName)
{
	try
	{
		hr = pSvcAdmin->CreateMsgService(lpszService, lpszDisplayName, 0, 0);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::ConfigureMessagingService(LPTSTR lpszService, LPTSTR lpszExchangeNameFL, LPTSTR lpszServer)
{
	enum {iSvcName, iSvcUID, cptaSvc};
    SizedSPropTagArray (cptaSvc, ptaSvc) = { cptaSvc, 
                                            {   PR_SERVICE_NAME,
                                                PR_SERVICE_UID } };

	try
	{
		hr = pSvcAdmin->GetMsgServiceTable(0, &pMsgSvcTable);
		if (HR_FAILED(hr))
		{
			return hr;
		}

		sres.rt = RES_CONTENT;
		sres.res.resContent.ulFuzzyLevel = FL_FULLSTRING;
		sres.res.resContent.ulPropTag = PR_SERVICE_NAME;
		sres.res.resContent.lpProp = &pSvcProps;
	
		pSvcProps.ulPropTag = PR_SERVICE_NAME;
		pSvcProps.Value.lpszA = lpszService; //"MSEMS"

		hr = HrQueryAllRows(pMsgSvcTable, (LPSPropTagArray)&ptaSvc, &sres, NULL, 0, &prows);
		if (HR_FAILED(hr))
		{
			return hr;
		}
	
		// Configure Microsoft Exchange Service Here
		rgval[0].ulPropTag		= PR_PROFILE_UNRESOLVED_NAME;
		rgval[0].Value.lpszA	= lpszExchangeNameFL;	// Now we use the real name

		rgval[1].ulPropTag		= PR_PROFILE_UNRESOLVED_SERVER;
		rgval[1].Value.lpszA	= lpszServer;

		hr = pSvcAdmin->ConfigureMsgService((LPMAPIUID) prows->aRow->lpProps[iSvcUID].Value.bin.lpb,
			                            0, 0, 2, rgval);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::DeleteMessagingService(LPTSTR lpszService)
{
	enum {iSvcName, iSvcUID, cptaSvc};
    SizedSPropTagArray (cptaSvc, ptaSvc) = { cptaSvc, 
                                            {   PR_SERVICE_NAME,
                                                PR_SERVICE_UID } };
	pSvcProps.ulPropTag = PR_SERVICE_NAME;
	pSvcProps.Value.lpszA = lpszService;
	
	try
	{
		hr = HrQueryAllRows(pMsgSvcTable, (LPSPropTagArray)&ptaSvc, &sres, NULL, 0, &prows);
    	hr = pSvcAdmin->DeleteMsgService((LPMAPIUID) prows->aRow->lpProps[iSvcUID].Value.bin.lpb);
	}
	catch (...) 
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::GetMessageStoresTable()
{
	try 
	{
		hr = pSession->GetMsgStoresTable(0, &pMsgSvcTable);
		
	}
	catch (...)
	{
		return hr;
	}

	return hr;
}

HRESULT CMapi::SetDefaultMessagingStore(CString sMailbox)
{
	enum {iSvcName, iSvcUID, cptaSvc};
    SizedSPropTagArray (cptaSvc, ptaSvc) = { cptaSvc, 
                                            {   PR_DISPLAY_NAME,
                                                PR_SERVICE_UID } };

	sres.res.resProperty.ulPropTag = PR_DISPLAY_NAME;

	
	
	pSvcProps.ulPropTag = PR_DISPLAY_NAME;
	pSvcProps.Value.lpszA = sMailbox.GetBuffer(0);
	
	hr = pMsgSvcTable->FindRow(&sres, BOOKMARK_BEGINNING, 0);
	if (SUCCEEDED(hr))
	{
		LPSPropValue	lpProp = NULL;
		
		hr = pMsgSvcTable->QueryRows(1, 0, &prows);
		if(FAILED(hr))
		{
			return hr;
		}

		if (prows->cRows != 1)
		{
			return hr;
		}

		lpProp = &prows->aRow[0].lpProps[0];

		if(lpProp->ulPropTag != PR_ENTRYID)
		{
			return hr;
		}

		try 
		{
			hr = pSession->SetDefaultStore(MAPI_DEFAULT_STORE,//Default
				lpProp->Value.bin.cb, (LPENTRYID) lpProp->Value.bin.lpb);
		}
		catch (...)
		{
			return hr;
		}
	}
	
	return hr;
}

void CMapi::CloseMapi()
{
	UlRelease(pMsgSvcTable);
    UlRelease(pSvcAdmin);
    FreeProws(prows);
   	pSvcAdmin = NULL;
	pMsgSvcTable = NULL;
	prows = NULL;
	UlRelease(pSession);
    UlRelease(pProfAdmin);
    MAPIUninitialize();
	return;
}
