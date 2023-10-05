// XmlTreeViewCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "LoadXML2Mem.h"
#include "XmlTreeViewCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXmlTreeViewCtrl

CXmlTreeViewCtrl::CXmlTreeViewCtrl()
{
}

CXmlTreeViewCtrl::~CXmlTreeViewCtrl()
{
}


BEGIN_MESSAGE_MAP(CXmlTreeViewCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CXmlTreeViewCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXmlTreeViewCtrl message handlers

bool CXmlTreeViewCtrl::SetXml2View(CString strFileName)
{
	m_XmlMemMapping.LoadXml2Mem(strFileName);

	SearchChildren(m_XmlMemMapping.m_plDomDocument->documentElement);

/*	
	HICON hIcon[7];
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_ICON_ROOT);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_ICON_FD);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_ICON_HD);
	hIcon[3] = AfxGetApp()->LoadIcon(IDI_ICON_CD);
	hIcon[4] = AfxGetApp()->LoadIcon(IDI_ICON_CLSFOLD);
	hIcon[5] = AfxGetApp()->LoadIcon(IDI_ICON_OPENFOLD);
	hIcon[6] = AfxGetApp()->LoadIcon(IDI_ICON_FILE);
	m_TreeImageList.Create(13, 13, ILC_COLOR, 7, 0);
	m_TreeDir.SetBkColor(RGB(250, 250, 0 ));
	m_TreeImageList.SetBkColor(RGB(250, 250, 0));
	for(int i = 0; i < 7; i++)
		m_TreeImageList.Add(hIcon[i]);

	// Create the Tree View control.
	m_TreeDir.SetImageList(&m_TreeImageList, TVSIL_NORMAL);
*/	
	
	
	
	
	
	char buff[100];
	HTREEITEM hRoot;

	// Create the root item.
	TVITEM tvItem;
	tvItem.mask = TVIF_TEXT | TVIF_IMAGE;// | TVIF_SELECTEDIMAGE;
	strcpy(buff, (char*)(m_XmlMemMapping.m_plDomDocument->documentElement->nodeName));
	::MessageBox(0, (char*)(m_XmlMemMapping.m_plDomDocument->documentElement->nodeName), "", MB_OK);
	tvItem.pszText = buff;//"�ҵĵ���";
	tvItem.cchTextMax = 50;
//	tvItem.iImage = 0;
//	tvItem.iSelectedImage = 0;
	TV_INSERTSTRUCT tvInsert;
	tvInsert.hParent = TVI_ROOT;
	tvInsert.hInsertAfter = TVI_FIRST;
	tvInsert.item = tvItem;
	hRoot = InsertItem(&tvInsert);
		
			tvItem.pszText = "asdfasdf";
			tvItem.cchTextMax = 12;
//			tvItem.iImage = 2;
//			tvItem.iSelectedImage = 2;
			tvInsert.hParent = hRoot;
			tvInsert.item = tvItem;
			InsertItem(&tvInsert);



			return true;

}



//	//��¼ǰһ�����
//	IXMLDOMNodePtr pChildLast;



//���ݽ��������������
bool CXmlTreeViewCtrl::SearchChild(IXMLDOMNodePtr pChild)
{
	CString temp;

	//����ȡ�Ľ������ΪNODE_TEXT������Ŀֵʱ
	if(pChild->nodeType == NODE_TEXT)
	{
//		temp = (char*)(pChildLast->nodeName);
		return true;
	}
	//����ȡ�Ľ������ΪNODE_ELEMENT�������ʱ
	else if(pChild->nodeType == NODE_ELEMENT)
	{
		CString temp2;
		temp = (char*)(pChild->nodeName);
//		pChildLast = pChild;
	}
	return true;
}



//������ȵݹ����XML�����
bool CXmlTreeViewCtrl::SearchChildren(IXMLDOMNodePtr pParent)
{
	// display the current node's name
	if(!SearchChild(pParent))
		return false;

	// simple for loop to get all children
	for (IXMLDOMNodePtr pChild = pParent->firstChild;
		NULL != pChild;
		pChild = pChild->nextSibling)
	{
		// for each child, call this function so that we get 
		// its children as well
		if(!SearchChildren(pChild))
			return false;
	}
	return true;
}



