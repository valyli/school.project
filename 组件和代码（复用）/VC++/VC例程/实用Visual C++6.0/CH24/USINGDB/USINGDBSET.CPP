// UsingDBSet.cpp : implementation of the CUsingDBSet class
//

#include "stdafx.h"
#include "UsingDB.h"
#include "UsingDBSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsingDBSet implementation

IMPLEMENT_DYNAMIC(CUsingDBSet, CRecordset)

CUsingDBSet::CUsingDBSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CUsingDBSet)
	m_Remote_Host = _T("");
	m_Path_Info = _T("");
	m_HTTP_User_Agent = _T("");
	m_ID = 0;
	m_CustomerID = _T("");
	m_CompanyName = _T("");
	m_ContactName = _T("");
	m_ContactTitle = _T("");
	m_Address = _T("");
	m_City = _T("");
	m_Region = _T("");
	m_PostalCode = _T("");
	m_Country = _T("");
	m_Phone = _T("");
	m_Fax = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CUsingDBSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=Student registration");
}

CString CUsingDBSet::GetDefaultSQL()
{
	return _T("[Counter],[Customers]");
}

void CUsingDBSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CUsingDBSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Remote_Host]"), m_Remote_Host);
	RFX_Text(pFX, _T("[Path_Info]"), m_Path_Info);
	RFX_Text(pFX, _T("[HTTP_User_Agent]"), m_HTTP_User_Agent);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[CustomerID]"), m_CustomerID);
	RFX_Text(pFX, _T("[CompanyName]"), m_CompanyName);
	RFX_Text(pFX, _T("[ContactName]"), m_ContactName);
	RFX_Text(pFX, _T("[ContactTitle]"), m_ContactTitle);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[City]"), m_City);
	RFX_Text(pFX, _T("[Region]"), m_Region);
	RFX_Text(pFX, _T("[PostalCode]"), m_PostalCode);
	RFX_Text(pFX, _T("[Country]"), m_Country);
	RFX_Text(pFX, _T("[Phone]"), m_Phone);
	RFX_Text(pFX, _T("[Fax]"), m_Fax);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CUsingDBSet diagnostics

#ifdef _DEBUG
void CUsingDBSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CUsingDBSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
