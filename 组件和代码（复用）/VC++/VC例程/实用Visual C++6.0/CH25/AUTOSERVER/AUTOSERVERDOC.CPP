// AutoserverDoc.cpp : implementation of the CAutoserverDoc class
//

#include "stdafx.h"
#include "Autoserver.h"

#include "AutoserverDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAutoserverDoc

IMPLEMENT_DYNCREATE(CAutoserverDoc, CDocument)

BEGIN_MESSAGE_MAP(CAutoserverDoc, CDocument)
	//{{AFX_MSG_MAP(CAutoserverDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CAutoserverDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CAutoserverDoc)
	DISP_FUNCTION(CAutoserverDoc, "SquareRoot", SquareRoot, VT_R8, VTS_R8)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IAutoserver to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {B282D1C0-DD47-11D2-BF13-996F03973C62}
static const IID IID_IAutoserver =
{ 0xb282d1c0, 0xdd47, 0x11d2, { 0xbf, 0x13, 0x99, 0x6f, 0x3, 0x97, 0x3c, 0x62 } };

BEGIN_INTERFACE_MAP(CAutoserverDoc, CDocument)
	INTERFACE_PART(CAutoserverDoc, IID_IAutoserver, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAutoserverDoc construction/destruction

CAutoserverDoc::CAutoserverDoc()
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CAutoserverDoc::~CAutoserverDoc()
{
	AfxOleUnlockApp();
}

BOOL CAutoserverDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAutoserverDoc serialization

void CAutoserverDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAutoserverDoc diagnostics

#ifdef _DEBUG
void CAutoserverDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAutoserverDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAutoserverDoc commands
#include "math.h"
double CAutoserverDoc::SquareRoot(double dInputVal) 
{
	return sqrt(dInputVal);
}
