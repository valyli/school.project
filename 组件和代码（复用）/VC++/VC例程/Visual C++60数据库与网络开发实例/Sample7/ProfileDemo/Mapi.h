#if !defined(AFX_MAPI_H__57A032A1_5249_11D2_AFCE_0080C7597ADC__INCLUDED_)
#define AFX_MAPI_H__57A032A1_5249_11D2_AFCE_0080C7597ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Mapi.h : header file
//
#include "mapiutil.h"
#include "edkmdb.h"

#define cProviders  3
#define nMAXProps   6
/////////////////////////////////////////////////////////////////////////////
// CMapi window

class CMapi : public CWnd
{
// Construction
public:
	CMapi();
	HRESULT Initialize();
	HRESULT AdminProfiles();
	HRESULT CreateNewProfile(LPSTR szProfile);
	HRESULT LogonDefaultEx();
	HRESULT LogonNewEx();
	HRESULT OpenAdminServices();
	HRESULT CreateMessagingService(LPTSTR lpszService, LPTSTR lpszDisplayName);
	HRESULT ConfigureMessagingService(LPTSTR lpszService, LPTSTR lpszExchangeNameFL, LPTSTR lpszServer);
	HRESULT DeleteMessagingService(LPTSTR lpszService);
	HRESULT GetMessageStoresTable();
	HRESULT SetDefaultMessagingStore(CString sMailbox);
	void CloseMapi();
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMapi)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMapi();

	// Generated message map functions
protected:
	LPPROFADMIN         pProfAdmin;
    LPSERVICEADMIN      pSvcAdmin;
    LPMAPITABLE         pMsgSvcTable;
	LPSRow              prow;
	LPSRowSet           prows;
	SPropValue			rgval[2];
	LPMAPISESSION       pSession;
	SRestriction		sres;    
    HRESULT             hr;
	SPropValue			pSvcProps;
    
					
    

	//{{AFX_MSG(CMapi)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAPI_H__57A032A1_5249_11D2_AFCE_0080C7597ADC__INCLUDED_)
