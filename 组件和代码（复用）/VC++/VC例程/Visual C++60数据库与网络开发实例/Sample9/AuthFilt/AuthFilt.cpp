// AUTHFILT.CPP - Implementation file for the Internet Server
//    Authentication Filter

#include "stdafx.h"
#include "AuthFilt.h"

///////////////////////////////////////////////////////////////////////
// The one and only CWinApp object
// NOTE: You may remove this object if you alter your project to no
// longer use MFC in a DLL.

CWinApp theApp;


///////////////////////////////////////////////////////////////////////
// The one and only CAuthFilter object

CAuthFilter theFilter;


///////////////////////////////////////////////////////////////////////
// CAuthFilter static members

DWORD CAuthFilter::m_cCacheItems = 0;
CHAR* CAuthFilter::m_pszUserFile = NULL;
LIST_ENTRY CAuthFilter::m_CacheListHead;
CRITICAL_SECTION CAuthFilter::m_csCacheLock;

///////////////////////////////////////////////////////////////////////
// CAuthFilter implementation

CAuthFilter::CAuthFilter()
{
	m_fCacheInitialized = FALSE;
}

CAuthFilter::~CAuthFilter()
{
	TerminateCache();
	TerminateUserDatabase();
}

BOOL CAuthFilter::Initialize()
{
	return (InitializeUserDatabase() && InitializeCache());
}

BOOL CAuthFilter::GetFilterVersion(PHTTP_FILTER_VERSION pVer)
{
	ISAPITRACE2( "[GetFilterVersion] Server filter version is %d.%d\n",
               HIWORD( pVer->dwServerFilterVersion ),
               LOWORD( pVer->dwServerFilterVersion ) );

	if ( !Initialize() )
	{
		ISAPITRACE1("[GetFilterVersion] Database or cache failed, error %d\n", GetLastError() );
		return FALSE;
	}

	// Call default implementation for initialization
	CHttpFilter::GetFilterVersion(pVer);

	// Set the flags we are interested in
	pVer->dwFlags = SF_NOTIFY_ORDER_DEFAULT |
									SF_NOTIFY_SECURE_PORT | SF_NOTIFY_NONSECURE_PORT | 
									SF_NOTIFY_LOG | SF_NOTIFY_AUTHENTICATION;

	// Load description string
	TCHAR sz[SF_MAX_FILTER_DESC_LEN+1];
	ISAPIVERIFY(::LoadString(AfxGetResourceHandle(), IDS_FILTER, sz, SF_MAX_FILTER_DESC_LEN));
	_tcscpy(pVer->lpszFilterDesc, sz);
	return TRUE;
}

DWORD CAuthFilter::OnAuthentication(CHttpFilterContext* pCtxt, PHTTP_FILTER_AUTHENT pAuthent)
{
	// Ignore the anonymous user
	if ( !*pAuthent->pszUser )
	{
		//  Tell the server to notify any subsequent notifications in the chain
		return SF_STATUS_REQ_NEXT_NOTIFICATION;
	}
	
	//  Save the unmapped username so we can log it later
	CHAR achUser[SF_MAX_USERNAME];
	strcpy(achUser, pAuthent->pszUser);

	//  Make sure this user is a valid user and map to the appropriate Windows NT user
	BOOL fAllowed;
	if ( !ValidateUser( pAuthent->pszUser, pAuthent->pszPassword, &fAllowed ))
	{
		ISAPITRACE2("[OnAuthentication] Error %d validating user %s\n", GetLastError(), pAuthent->pszUser );
		return SF_STATUS_REQ_ERROR;
	}

	if ( !fAllowed )
	{
		//  This user isn't allowed access.  Indicate this to the server
		SetLastError( ERROR_ACCESS_DENIED );
		return SF_STATUS_REQ_ERROR;
	}

	//  Save the unmapped user name so we can log it later on.  We allocate
	//  enough space for two usernames so we can use this memory block
	//  for logging.  Note we may have already allocated it from a previous
	//  request on this TCP session
	if ( !pCtxt->m_pFC->pFilterContext )
	{
		pCtxt->m_pFC->pFilterContext = pCtxt->AllocMem( 2 * SF_MAX_USERNAME + 4 );
		if ( !pCtxt->m_pFC->pFilterContext )
		{
			SetLastError( ERROR_NOT_ENOUGH_MEMORY );
			return SF_STATUS_REQ_ERROR;
		}
	}

	strcpy( (CHAR *) pCtxt->m_pFC->pFilterContext, achUser );
	return SF_STATUS_REQ_HANDLED_NOTIFICATION;
}

DWORD CAuthFilter::OnLog(CHttpFilterContext *pCtxt, PHTTP_FILTER_LOG pLog)
{
	//  The unmapped username is in pFilterContext if this filter authenticated this user
	if ( pCtxt->m_pFC->pFilterContext )
	{
		CHAR *pch = (CHAR *)pCtxt->m_pFC->pFilterContext;

		//  Put both the original username and the NT mapped username
		//  into the log in the form "Original User (NT User)"
		strcat( pch, " (" );
		strcat( pch, pLog->pszClientUserName );
		strcat( pch, ")" );
		pLog->pszClientUserName = pch;
	}

	return SF_STATUS_REQ_NEXT_NOTIFICATION;
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CAuthFilter, CHttpFilter)
	//{{AFX_MSG_MAP(CAuthFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

///////////////////////////////////////////////////////////////////////
// If your extension will not use MFC, you'll need this code to make
// sure the extension objects can find the resource handle for the
// module.  If you convert your extension to not be dependent on MFC,
// remove the comments arounn the following AfxGetResourceHandle()
// and DllMain() functions, as well as the g_hInstance global.

/***

static HINSTANCE g_hInstance;

HINSTANCE AFXISAPI AfxGetResourceHandle()
{
	return g_hInstance;
}

BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ulReason, LPVOID lpReserved)
{
	if (ulReason == DLL_PROCESS_ATTACH)
	{
		g_hInstance = hInst;
	}

	return TRUE;
}

***/