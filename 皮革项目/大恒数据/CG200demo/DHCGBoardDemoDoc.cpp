// DHCGBoardDemoDoc.cpp : implementation of the CDHCGBoardDemoDoc class
//

#include "stdafx.h"
#include "bmpdlg.h"
#include "DHCGBoardDemo.h"

#include "DHCGBoardDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoDoc

IMPLEMENT_DYNCREATE(CDHCGBoardDemoDoc, CDocument)

BEGIN_MESSAGE_MAP(CDHCGBoardDemoDoc, CDocument)
	//{{AFX_MSG_MAP(CDHCGBoardDemoDoc)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoDoc construction/destruction

CDHCGBoardDemoDoc::CDHCGBoardDemoDoc()
{
	// TODO: add one-time construction code here
	hdib=NULL;
}

CDHCGBoardDemoDoc::~CDHCGBoardDemoDoc()
{
	FreeDIBHandle();
}

BOOL CDHCGBoardDemoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)AfxGetMainWnd()->GetActiveWindow();//GetActiveView();
	if(pView!=NULL&&!pView->m_bFreeze)
		pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	FreeDIBHandle();
	//	SetModifiedFlag(true);
	UpdateAllViews(NULL);
	return TRUE;

}



/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoDoc serialization

void CDHCGBoardDemoDoc::Serialize(CArchive& ar)
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
// CDHCGBoardDemoDoc diagnostics

#ifdef _DEBUG
void CDHCGBoardDemoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDHCGBoardDemoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDHCGBoardDemoDoc commands

BOOL CDHCGBoardDemoDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	// TODO: Add your specialized creation code here
	CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)AfxGetMainWnd()->GetActiveWindow();
	if(pView!=NULL&&!pView->m_bFreeze)
		pView->SendMessage(WM_COMMAND,ID_CGBOARDSTOP);
	FreeDIBHandle();
	CFile file(lpszPathName,CFile::modeReadWrite);
	hdib=ReadDIBFile(file);
	return TRUE;
	//	return TRUE;
}

BOOL CDHCGBoardDemoDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	// TODO: Add your specialized code here and/or call the base class
//	CDHCGBoardDemoView* pView=(CDHCGBoardDemoView*)GetActiveView();
//	if(pView!=NULL&&!pView->m_bFreeze)
//		pView->SendMessage(WM_COMMAND,ID_CGBOARDPLAY);
	if(hdib!=NULL)
	{
		CFile file(lpszPathName,CFile::modeWrite|CFile::modeCreate);
		return SaveDIB(hdib,file);
	}
	return CDocument::OnSaveDocument(lpszPathName);
}

void CDHCGBoardDemoDoc::FreeDIBHandle()
{
	if(hdib!=NULL)
	{
		FreeDIB(hdib);
		hdib=NULL;
	}
}

void CDHCGBoardDemoDoc::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	if(hdib!=NULL)
	{
		CBmpDialog* dlg;
		dlg=new CBmpDialog(FALSE,"bmp","*.bmp",OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,"BMP Files(*.Bmp)|*.Bmp|All Files(*.*)|*.*||");
		
		if(dlg->DoModal()==IDOK)
		{
			if(OnSaveDocument(dlg->GetPathName()))
			{
				SetTitle(dlg->GetFileName());
			}
		}
		delete dlg;
	}
}

