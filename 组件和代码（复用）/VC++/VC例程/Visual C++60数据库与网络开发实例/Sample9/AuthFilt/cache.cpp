/* 
DB.CPP 
    This module implements a simple user cache.  The cached users are kept
    in an LRU sorted list.  If there will be a large number of simultaneous
    users, then a sorted array would be more appropriate.
*/

#include "stdafx.h"
#include "AuthFilt.h"

/*
Routine Description:
    Initializes the cache module

Return Value:
    TRUE if initialized successfully, FALSE on error
*/
BOOL CAuthFilter::InitializeCache()
{
	if ( m_fCacheInitialized )
		return TRUE;

	InitializeCriticalSection( &m_csCacheLock );
	m_CacheListHead.Blink = m_CacheListHead.Flink = &m_CacheListHead;

	m_fCacheInitialized = TRUE;

	return TRUE;
}


/*
Routine Description:
    Checks to see if a user is in the cache and returns the user properties
    if found

Arguments:
    pszUserName - Case insensitive username to find
		pfFound     - Set to TRUE if the specified user was found
    pszPassword - Receives password for specified user if found
    pszNTUser   - Receives the NT Username to map this user to
    pszNTUserPassword - Receives the NT Password for m_achNTUser

Return Value:
    TRUE if no errors occurred.
*/
BOOL CAuthFilter::LookupUserInCache(const CHAR* pszUserName, BOOL* pfFound, CHAR* pszPassword, CHAR* pszNTUser, CHAR* pszNTUserPassword)
{
	LIST_ENTRY* pEntry;
	USER_INFO * pUser;
	DWORD       cPosition = 0;

	//  Search the cache for the specified user
	EnterCriticalSection( &m_csCacheLock );
	for ( pEntry = m_CacheListHead.Flink; pEntry != &m_CacheListHead; pEntry = pEntry->Flink)
	{
		pUser = CONTAINING_RECORD( pEntry, USER_INFO, ListEntry );
		if ( !stricmp( pszUserName, pUser->achUserName ))
			goto Found;

		cPosition++;
	}

	LeaveCriticalSection( &m_csCacheLock );

	//  Not Found
	*pfFound = FALSE;
	return TRUE;

Found:
	//  Copy out the user properties
	strcpy( pszPassword,       pUser->achPassword );
	strcpy( pszNTUser,         pUser->achNTUserName );
	strcpy( pszNTUserPassword, pUser->achNTUserPassword );

	//  Move this user entry to the front of the list as we're probably going
	//  to get subsequent requests for this user.  Note we only move it
	//  if it's not already near the front
	if ( cPosition > LIST_REORDER_THRESHOLD )
	{
		//  Remove from the old position...
		pEntry->Blink->Flink = pEntry->Flink;
		pEntry->Flink->Blink = pEntry->Blink;
		// ...and insert it at the beginning of the list
		pEntry->Blink = &m_CacheListHead;
		pEntry->Flink = m_CacheListHead.Flink;
		m_CacheListHead.Flink->Blink = pEntry;
		m_CacheListHead.Flink        = pEntry;
	}

	LeaveCriticalSection( &m_csCacheLock );

	*pfFound = TRUE;
	return TRUE;
}

/*
Routine Description:
    Adds the specified user to the cache

Arguments:
    pszUserName - Username to add
		pszPassword - Contains the external password for this user
    pszNTUser   - Contains the NT user name to use for this user
    pszNTUserPassword - Contains the password for NTUser

Return Value:
    TRUE if no errors occurred.
*/
BOOL CAuthFilter::AddUserToCache(const CHAR* pszUserName, const CHAR* pszPassword, const CHAR* pszNTUser, const CHAR* pszNTUserPassword)
{
	LIST_ENTRY* pEntry;
	USER_INFO*  pUser;

	//  Check our parameters before adding them to the cache
	if ( strlen( pszUserName ) > SF_MAX_USERNAME ||
			 strlen( pszPassword ) > SF_MAX_PASSWORD ||
			 strlen( pszNTUser   ) > SF_MAX_USERNAME ||
			 strlen( pszNTUserPassword ) > SF_MAX_PASSWORD )
	{
		SetLastError( ERROR_INVALID_PARAMETER );
		return FALSE;
	}

	//  Search the cache for the specified user to make sure there are no
	//  duplicates
	EnterCriticalSection( &m_csCacheLock );
	for ( pEntry  = m_CacheListHead.Flink; pEntry != &m_CacheListHead; pEntry = pEntry->Flink )
	{
		pUser = CONTAINING_RECORD( pEntry, USER_INFO, ListEntry );
		if ( !stricmp( pszUserName, pUser->achUserName ))
			goto Found;
	}

	//  Allocate a new cache item and put it at the head of the list
	pUser = (USER_INFO *) LocalAlloc( LPTR, sizeof( USER_INFO ));
	if ( !pUser )
	{
		LeaveCriticalSection( &m_csCacheLock );
		SetLastError( ERROR_NOT_ENOUGH_MEMORY );
		return FALSE;
	}
	pUser->ListEntry.Flink = m_CacheListHead.Flink;
	pUser->ListEntry.Blink = &m_CacheListHead;
	m_CacheListHead.Flink->Blink = &pUser->ListEntry;
	m_CacheListHead.Flink = &pUser->ListEntry;

Found:
	//  Set the various fields
	strcpy( pUser->achUserName,       pszUserName );
	strcpy( pUser->achPassword,       pszPassword );
	strcpy( pUser->achNTUserName,     pszNTUser );
	strcpy( pUser->achNTUserPassword, pszNTUserPassword );

	m_cCacheItems++;

	//  If there are too many cached users, remove the least recently
	//  used one now
	if ( m_cCacheItems > MAX_CACHED_USERS )
	{
		pEntry = m_CacheListHead.Blink;
		pEntry->Blink->Flink = &m_CacheListHead;
		m_CacheListHead.Blink  = pEntry->Blink;
		LocalFree( CONTAINING_RECORD( pEntry, USER_INFO, ListEntry ));
		m_cCacheItems--;
	}

	LeaveCriticalSection( &m_csCacheLock );

	return TRUE;
}

/*
Routine Description:
    Terminates the cache module and frees any allocated memory
*/
VOID CAuthFilter::TerminateCache()
{
	LIST_ENTRY* pEntry;
	LIST_ENTRY* pEntryNext;
	USER_INFO*  pUser;

	if ( !m_fCacheInitialized )
		return;

	EnterCriticalSection( &m_csCacheLock );

	// Free all of the cache entries
	for ( pEntry  = m_CacheListHead.Flink; pEntry != &m_CacheListHead; pEntry  = pEntryNext )
	{
		pUser = CONTAINING_RECORD( pEntry, USER_INFO, ListEntry );
		pEntryNext = pEntry->Flink;

		//  Remove this entry from the list and free it
		pEntry->Blink->Flink = pEntry->Flink;
		pEntry->Flink->Blink = pEntry->Blink;

		LocalFree( pUser );
	}

	m_cCacheItems = 0;
	LeaveCriticalSection( &m_csCacheLock );
	DeleteCriticalSection( &m_csCacheLock );
	m_fCacheInitialized = FALSE;
}
