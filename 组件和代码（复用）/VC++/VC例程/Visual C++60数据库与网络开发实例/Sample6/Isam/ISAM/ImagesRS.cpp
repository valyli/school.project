// ImagesRS.cpp : implementation file
//

#include "stdafx.h"
#include "ISAM.h"
#include "ImagesRS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagesRS

IMPLEMENT_DYNAMIC(CImagesRS, CRecordset)

CImagesRS::CImagesRS(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CImagesRS)
	m_image_filename = _T("");
	m_image_title = _T("");
	m_image_id = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT

	m_image_id_param = 0;
	m_nParams = 1;
	
	m_nDefaultType = snapshot;
}


CString CImagesRS::GetDefaultConnect()
{
	return _T("ODBC;DSN=");
}

CString CImagesRS::GetDefaultSQL()
{
	return _T("SELECT image_id, image_title, image_filename FROM images");
}

void CImagesRS::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CImagesRS)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[image_id]"), m_image_id);
	RFX_Text(pFX, _T("[image_title]"), m_image_title);
	RFX_Text(pFX, _T("[image_filename]"), m_image_filename);
	//}}AFX_FIELD_MAP

	pFX->SetFieldType(CFieldExchange::param);
	RFX_Long(pFX, _T("[image_id]"), m_image_id_param);
}

/////////////////////////////////////////////////////////////////////////////
// CImagesRS diagnostics

#ifdef _DEBUG
void CImagesRS::AssertValid() const
{
	CRecordset::AssertValid();
}

void CImagesRS::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
