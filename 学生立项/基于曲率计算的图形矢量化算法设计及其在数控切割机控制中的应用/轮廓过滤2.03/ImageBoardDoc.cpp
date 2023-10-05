// ImageBoardDoc.cpp : implementation of the CImageBoardDoc class
//

#include "stdafx.h"
#include "ImageBoard.h"

#include "ImageBoardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc

IMPLEMENT_DYNCREATE(CImageBoardDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageBoardDoc, CDocument)
	//{{AFX_MSG_MAP(CImageBoardDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc construction/destruction

CImageBoardDoc::CImageBoardDoc()
{
	m_pDib	= new CDib;
	m_pDib->Create(DEFAULT_HEIGHT, DEFAULT_WIDTH);
}

CImageBoardDoc::~CImageBoardDoc()
{
	if (m_pDib != NULL)
		delete m_pDib;
}

BOOL CImageBoardDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc serialization

void CImageBoardDoc::Serialize(CArchive& ar)
{
	m_pDib->Serialize(ar);

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
// CImageBoardDoc diagnostics

#ifdef _DEBUG
void CImageBoardDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageBoardDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CImageBoardDoc commands


void CImageBoardDoc::OnFileSaveAs() 
{
	CFileDialog FileDlg(FALSE, "*.bmp", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szSaveFilter);

	switch (m_pDib->GetBitCount())
	{
	case 1:
		FileDlg.m_ofn.nFilterIndex = 1;
		break;
	case 4:
		FileDlg.m_ofn.nFilterIndex = 2;
		break;
	case 8:
		FileDlg.m_ofn.nFilterIndex = 3;
		break;
	case 24:
	default:
		FileDlg.m_ofn.nFilterIndex = 4;
		break;
	}

	if (FileDlg.DoModal() == IDOK)
	{
		switch (FileDlg.m_ofn.nFilterIndex)
		{
		case 1:
			m_pDib->ConvertFormat(1);
			break;
		case 2:
			m_pDib->ConvertFormat(4);
			break;
		case 3:
			m_pDib->ConvertFormat(8);
			break;
		case 4:
		default:
			m_pDib->ConvertFormat(24);
			break;
		}

		OnSaveDocument(FileDlg.m_ofn.lpstrFile);
		SetPathName(FileDlg.m_ofn.lpstrFile);
		UpdateAllViews(NULL);
		SetModifiedFlag(FALSE);
	}
}