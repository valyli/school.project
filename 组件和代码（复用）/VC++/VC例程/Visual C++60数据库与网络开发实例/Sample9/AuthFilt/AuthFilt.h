#if !defined(AFX_AUTHFILT_H__786FEB27_70F6_11D2_A281_006067323266__INCLUDED_)
#define AFX_AUTHFILT_H__786FEB27_70F6_11D2_A281_006067323266__INCLUDED_

// AUTHFILT.H - Header file for your Internet Server
//    Authentication Filter

#include "resource.h"


// The maximum number of users we will cache.  If there will be a large number
// of simultaneous users, bump this value
#define MAX_CACHED_USERS 100

// The position after which we'll move a cache entry to the front of the list
#define LIST_REORDER_THRESHOLD 6

//  This is the name of the file that contains the username/password pairs and
//  the appropriate NT account the username/password should be mapped to.
//
//  The format of the file is:
//
//  User1:Password1, NTUser1:NTPassword1
//  User2:Password2, NTUser2:NTPassword2
//  User3:Password3, NTUser3:NTPassword3
//
#define USER_LIST_FILE "c:\\winnt\\system32\\inetsrv\\userdb.txt"


// Constants
#define ISWHITE(ch)  ((ch) && ((ch) == ' ' || (ch) == '\t' || (ch) == '\n' || (ch) == '\r'))

// Cached user structure
typedef struct _USER_INFO
{
	LIST_ENTRY  ListEntry;  // Double linked list entry

	CHAR  achUserName[SF_MAX_USERNAME];   // External username and password
	CHAR  achPassword[SF_MAX_PASSWORD];

	CHAR  achNTUserName[SF_MAX_USERNAME]; // NT account and password to map user to
	CHAR  achNTUserPassword[SF_MAX_PASSWORD];

} USER_INFO, *PUSER_INFO;

class CAuthFilter : public CHttpFilter
{
public:
	CAuthFilter();
	~CAuthFilter();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CAuthFilter)
	public:
	virtual BOOL GetFilterVersion(PHTTP_FILTER_VERSION pVer);
	virtual DWORD OnAuthentication(CHttpFilterContext* pCtxt, PHTTP_FILTER_AUTHENT pAuthent);
	virtual DWORD OnLog(CHttpFilterContext* pfc, PHTTP_FILTER_LOG pLog);
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL Initialize();
	static BOOL ValidateUser(IN OUT CHAR* pszUserName, IN OUT CHAR* pszPassword, OUT BOOL* pfValid);
	// Database routines
	BOOL InitializeUserDatabase();
	static BOOL LookupUserInDb(const CHAR* pszUser, OUT BOOL* pfFound, OUT CHAR* pszPassword, OUT CHAR* pszNTUser, OUT CHAR* pszNTUserPassword);
	VOID TerminateUserDatabase();
	// Cache routines
	BOOL InitializeCache();
	static BOOL LookupUserInCache(const CHAR* pszUserName, BOOL* pfFound, CHAR* pszPassword, CHAR* pszNTUser, CHAR* pszNTUserPassword);
	static BOOL AddUserToCache(const CHAR* pszUserName, const CHAR* pszPassword, const CHAR* pszNTUser, const CHAR* pszNTUserPassword);
	VOID TerminateCache();

protected:
	BOOL  m_fCacheInitialized;	// Indicates whether the cache is initialized
	
	static DWORD m_cCacheItems;						 // Number of items in the cache
	static CHAR* m_pszUserFile;						 // Buffer for user database
	static LIST_ENTRY m_CacheListHead;		 // Circular double linked list of cached users
	static CRITICAL_SECTION m_csCacheLock; // Critical section protects cache list

	//{{AFX_MSG(CAuthFilter)
	//}}AFX_MSG
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTHFILT_H__786FEB27_70F6_11D2_A281_006067323266__INCLUDED)
