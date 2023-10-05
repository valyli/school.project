// bezierDoc.cpp : implementation of the CBezierDoc class
//

#include "stdafx.h"
#include "bezier.h"

#include "bezierDoc.h"
#include "CntrItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBezierDoc

IMPLEMENT_DYNCREATE(CBezierDoc, COleDocument)

BEGIN_MESSAGE_MAP(CBezierDoc, COleDocument)
	//{{AFX_MSG_MAP(CBezierDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Enable default OLE container implementation
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE, COleDocument::OnUpdatePasteMenu)
	ON_UPDATE_COMMAND_UI(ID_EDIT_PASTE_LINK, COleDocument::OnUpdatePasteLinkMenu)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_CONVERT, COleDocument::OnUpdateObjectVerbMenu)
	ON_COMMAND(ID_OLE_EDIT_CONVERT, COleDocument::OnEditConvert)
	ON_UPDATE_COMMAND_UI(ID_OLE_EDIT_LINKS, COleDocument::OnUpdateEditLinksMenu)
	ON_COMMAND(ID_OLE_EDIT_LINKS, COleDocument::OnEditLinks)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OLE_VERB_FIRST, ID_OLE_VERB_LAST, COleDocument::OnUpdateObjectVerbMenu)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBezierDoc construction/destruction

CBezierDoc::CBezierDoc()
{
	// Use OLE compound files


}

CBezierDoc::~CBezierDoc()
{
}

BOOL CBezierDoc::OnNewDocument()
{
	if (!COleDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBezierDoc serialization

void CBezierDoc::Serialize(CArchive& ar)
{
	POSITION m_Position;
	//存文件
	if (ar.IsStoring())
	{
		ar.Write("BSP", 4);
		ar<<m_List.GetCount();
		for(int i = 0; i < m_List.GetCount(); i++)
		{
			m_Position = m_List.FindIndex(i);
			ar<<m_List.GetAt(m_Position)->GetSize();
			for(int j = 0; j < m_List.GetAt(m_Position)->GetSize(); j++)
			{
				ar<<(POINT)m_List.GetAt(m_Position)->GetAt(j);
			}
		}
	}
	//读文件
	else
	{
		char flag[4];
		ar.Read(flag, 4);
		if(strcmp(flag, "BSP") != 0)
		{
			MessageBox(0, "只能是.BSP文件", "", MB_OK);
			return;
		}
		int i, j;
		//释放原链表空间
		for(i = 0; i < m_List.GetCount(); i++)
		{
			m_Position = m_List.GetHeadPosition();
			m_List.GetAt(m_Position)->RemoveAll();
		}
		m_List.RemoveAll();
		//建链表
		int m_size, m_count;
		CArrayPoint *tempArray;
		ar>>m_size;
		CPoint tempPoint;
		for(i = 0; i < m_size; i++)
		{
			ar>>m_count;
			tempArray = new CArrayPoint;
			for(j = 0; j < m_count; j++)
			{
				ar>>tempPoint;
				tempArray->Add(tempPoint);
			}
			m_List.AddHead(tempArray);
		}
	}

	// Calling the base class COleDocument enables serialization
	//  of the container document's COleClientItem objects.
	COleDocument::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CBezierDoc diagnostics

#ifdef _DEBUG
void CBezierDoc::AssertValid() const
{
	COleDocument::AssertValid();
}

void CBezierDoc::Dump(CDumpContext& dc) const
{
	COleDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBezierDoc commands
