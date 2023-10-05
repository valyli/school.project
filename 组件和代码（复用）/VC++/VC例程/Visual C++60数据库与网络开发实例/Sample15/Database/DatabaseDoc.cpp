// DatabaseDoc.cpp : implementation of the CDatabaseDoc class
//

#include "stdafx.h"
#include "Database.h"

#include "DatabaseDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc

IMPLEMENT_DYNCREATE(CDatabaseDoc, CDocument)

BEGIN_MESSAGE_MAP(CDatabaseDoc, CDocument)
	//{{AFX_MSG_MAP(CDatabaseDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc construction/destruction

CDatabaseDoc::CDatabaseDoc()
{
	// initialize the member variables
	m_pDB = NULL;
	m_pSet = NULL;
}

CDatabaseDoc::~CDatabaseDoc()
{
	// Prevent potential memory leaks when 'new'
	//  is used with pointers
	delete m_pSet;
	delete m_pDB;
}

BOOL CDatabaseDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if (m_pSet != NULL)  // Close recordset if open
	{
		m_pSet->Close();
		delete m_pSet;
		m_pSet = NULL;
	}
	if (m_pDB != NULL)   // Close database if open
	{
		m_pDB->Close();
		delete m_pDB;
		m_pDB = NULL;
	}

	m_bFileOpen = FALSE; // Database file is not open
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc serialization

void CDatabaseDoc::Serialize(CArchive& ar)
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
// CDatabaseDoc diagnostics

#ifdef _DEBUG
void CDatabaseDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDatabaseDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDatabaseDoc commands

BOOL CDatabaseDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// If user selected a file then try to open it as a database
	m_pDB = new CDatabase;
	ASSERT(m_pDB != NULL);
	try
	{
		m_pDB->Open(lpszPathName);
	}
	catch (CException* e)
	{
		delete m_pDB;
		m_pDB = NULL;

		TCHAR szCause[255];
		CString strFormatted = _T("The data file could not be opened because of this error: \n");
		e->GetErrorMessage(szCause, 255);
		strFormatted += szCause;
		AfxMessageBox(strFormatted, MB_OK | MB_ICONEXCLAMATION);
		e->Delete();
		m_bFileOpen = FALSE;
		return FALSE;
	}

	// If database successfully opened then open EMPLOYEES recordset
	m_pSet = new CRecordsetEmployees(m_pDB);
	ASSERT(m_pSet != NULL);
	try
	{
		m_pSet->Open();
		long numRec = m_pSet->GetRecordCount();
	}
	catch (CException* e)
	{
		delete m_pSet;
		m_pSet = NULL;

		TCHAR szCause[255];
		CString strFormatted = _T("The data file could not be opened because of this error: \n");
		e->GetErrorMessage(szCause, 255);
		strFormatted += szCause;
		AfxMessageBox(strFormatted, MB_OK | MB_ICONEXCLAMATION);
		e->Delete();
		m_bFileOpen = FALSE;
		return FALSE;
	}

	// boolean variable to indicate database is open
	m_bFileOpen = TRUE;
	return TRUE;
}
