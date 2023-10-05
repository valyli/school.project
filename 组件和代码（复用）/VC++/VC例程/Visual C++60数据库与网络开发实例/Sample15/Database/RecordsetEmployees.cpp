// RecordsetEmployees.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "RecordsetEmployees.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordsetEmployees

IMPLEMENT_DYNAMIC(CRecordsetEmployees, CRecordset)

CRecordsetEmployees::CRecordsetEmployees(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRecordsetEmployees)
	m_SSN = 0.0;
	m_NAME = _T("");
	m_ADDRESS = _T("");
	m_TITLE = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRecordsetEmployees::GetDefaultConnect()
{
	return _T("ODBC;DSN=db1");
}

CString CRecordsetEmployees::GetDefaultSQL()
{
	return _T("[Employees]");
}

void CRecordsetEmployees::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRecordsetEmployees)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[SSN]"), m_SSN);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[ADDRESS]"), m_ADDRESS);
	RFX_Text(pFX, _T("[TITLE]"), m_TITLE);
	RFX_Date(pFX, _T("[HIRE DATE]"), m_HIRE_DATE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRecordsetEmployees diagnostics

#ifdef _DEBUG
void CRecordsetEmployees::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetEmployees::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
