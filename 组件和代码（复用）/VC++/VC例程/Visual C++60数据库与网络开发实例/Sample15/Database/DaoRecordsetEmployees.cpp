// DaoRecordsetEmployees.cpp : implementation file
//

#include "stdafx.h"
#include "Database.h"
#include "DaoRecordsetEmployees.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetEmployees

IMPLEMENT_DYNAMIC(CDaoRecordsetEmployees, CDaoRecordset)

CDaoRecordsetEmployees::CDaoRecordsetEmployees(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDaoRecordsetEmployees)
	m_SSN = 0.0;
	m_NAME = _T("");
	m_ADDRESS = _T("");
	m_TITLE = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenDynaset;
}


CString CDaoRecordsetEmployees::GetDefaultDBName()
{
	return _T("C:\\Myprojects\\Database\\db1.mdb");
}

CString CDaoRecordsetEmployees::GetDefaultSQL()
{
	return _T("[Employees]");
}

void CDaoRecordsetEmployees::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDaoRecordsetEmployees)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Double(pFX, _T("[SSN]"), m_SSN);
	DFX_Text(pFX, _T("[NAME]"), m_NAME);
	DFX_Text(pFX, _T("[ADDRESS]"), m_ADDRESS);
	DFX_Text(pFX, _T("[TITLE]"), m_TITLE);
	DFX_DateTime(pFX, _T("[HIRE DATE]"), m_HIRE_DATE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDaoRecordsetEmployees diagnostics

#ifdef _DEBUG
void CDaoRecordsetEmployees::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CDaoRecordsetEmployees::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
