// homework5Doc.cpp : implementation of the CHomework5Doc class
//

#include "stdafx.h"
#include "homework5.h"

#include "homework5Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHomework5Doc

IMPLEMENT_DYNCREATE(CHomework5Doc, CDocument)

BEGIN_MESSAGE_MAP(CHomework5Doc, CDocument)
	//{{AFX_MSG_MAP(CHomework5Doc)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework5Doc construction/destruction

CHomework5Doc::CHomework5Doc()
{
//	m_apt->count = 0;
//	m_apt->apt = 0;
	m_apt = 0;
	m_count = 0;
	SetModifiedFlag(FALSE);
}

CHomework5Doc::~CHomework5Doc()
{
}

BOOL CHomework5Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CHomework5Doc serialization

void CHomework5Doc::Serialize(CArchive& ar)
{
	int i, j;
	char test[4];
	if (ar.IsStoring())
	{
		ar.Write("BSP", 4);
		ar<<m_count;
		for(i = 0; i < m_count; i++)
		{
			ar<<m_apt[i].count;
			for(j = 0; j < m_apt[i].count; j++)
				ar<<m_apt[i].apt[j];
		}
	}
	else
	{
		ar.Read(test, 4);
		if(strcmp(test, "BSP") != 0)
		{
			MessageBox(0, "File type wrong!", "", MB_OK);
			return;
		}
		ar>>m_count;
		if(m_count == 0)
			return;
		m_apt = (PointQueue*)malloc(m_count * sizeof(PointQueue));
		if(m_apt == 0)
		{
			MessageBox(0, "Alloc is wrong!", "", MB_OK);
			return;
		}
		for(i = 0; i < m_count; i++)
		{
			ar>>m_apt[i].count;
			m_apt[i].apt = (POINT*)malloc(m_apt[i].count * sizeof(POINT));
			for(j = 0; j < m_apt[i].count; j++)
				ar>>m_apt[i].apt[j];
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CHomework5Doc diagnostics

#ifdef _DEBUG
void CHomework5Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHomework5Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHomework5Doc commands

void CHomework5Doc::OnAppExit() 
{
	if(IsModified())
		SaveModified();
}
