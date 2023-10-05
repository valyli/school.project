// PersistDoc.cpp : implementation of the CPersistDoc class
//

#include "stdafx.h"
#include "Persist.h"

#include "PersistDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPersistDoc

IMPLEMENT_DYNCREATE(CPersistDoc, CDocument)

BEGIN_MESSAGE_MAP(CPersistDoc, CDocument)
	//{{AFX_MSG_MAP(CPersistDoc)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, OnUpdateEditPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPersistDoc construction/destruction
#include <afxole.h>
#include <afxadv.h>
CPersistDoc::CPersistDoc()
{
	// TODO: add one-time construction code here
	m_uClipFormat=
		RegisterClipboardFormat("PersistClipFormat");

}

void CPersistDoc::DeleteBlobs()
{
	//**Delete the allocated blobs
	for (int i=0;i<m_BlobArray.GetSize();i++)
		delete m_BlobArray.GetAt(i);
	m_BlobArray.RemoveAll();
}

CPersistDoc::~CPersistDoc()
{
	DeleteBlobs();
}

BOOL CPersistDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	DeleteBlobs();

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPersistDoc serialization

void CPersistDoc::Serialize(CArchive& ar)
{
	m_BlobArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPersistDoc diagnostics

#ifdef _DEBUG
void CPersistDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPersistDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPersistDoc commands

void CPersistDoc::OnEditCut() 
{
	OnEditCopy();
	DeleteBlobs();
	UpdateAllViews(NULL);
	
}

void CPersistDoc::OnEditCopy() 
{
	//Create a data source object
	COleDataSource *pDataSource=new COleDataSource;

	//create a shared file and attach a CArchive
	CSharedFile fileClipCopy;
	CArchive arClipCopy(&fileClipCopy,CArchive::store);

	//Serialize the document into this archive
	Serialize(arClipCopy);
	arClipCopy.Close();

	//Grab the global memory handle from the mem file
	HANDLE hGlobalMem=fileClipCopy.Detach();
	if (hGlobalMem)
	{
		//Globally cache the data with the unique format
		pDataSource->CacheGlobalData(
			m_uClipFormat,hGlobalMem);
		//Offer it on the clipboard
		pDataSource->SetClipboard();
	}
	else	AfxMessageBox("Can't alloc memory for copy");	
}

void CPersistDoc::OnEditPaste() 
{
	//Create a data object and attach to clipboard
	COleDataObject oleTarget;
	oleTarget.AttachClipboard();
	if (oleTarget.IsDataAvailable(m_uClipFormat))
	{
		//Get the global memory handle
		HANDLE hGlobalMem=
			oleTarget.GetGlobalData(m_uClipFormat);
		if (hGlobalMem)
		{
			//Unwind the data into the document
			CSharedFile fileTarget;
			fileTarget.SetHandle(hGlobalMem);
			CArchive arTarget(&fileTarget,CArchive::load);
			DeleteBlobs();

			//Run the Serialize and update the display
			Serialize(arTarget);
			UpdateAllViews(NULL);
		}
	}
}

void CPersistDoc::OnUpdateEditPaste(CCmdUI* pCmdUI) 
{
	COleDataObject oleTarget;
	oleTarget.AttachClipboard();
	pCmdUI->Enable(oleTarget.IsDataAvailable(m_uClipFormat));
}
