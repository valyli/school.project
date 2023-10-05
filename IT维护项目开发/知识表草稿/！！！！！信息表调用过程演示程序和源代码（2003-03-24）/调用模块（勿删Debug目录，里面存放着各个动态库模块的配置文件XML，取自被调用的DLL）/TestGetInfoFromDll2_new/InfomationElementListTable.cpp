// InfomationElementListTable.cpp: implementation of the CInfomationElementListTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestGetInfoFromDll.h"
#include "InfomationElementListTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInfomationElementListTable::CInfomationElementListTable()
{
	//置默认值，
	//为0表示没有设置
	m_NameBaseId = 0;
	//为0表示没有设置
	m_InfoServiceProviderId = 0;

	IsEmpty = true;
	IsLoadXML = false;
}

CInfomationElementListTable::~CInfomationElementListTable()
{

}



//根据结点类型生成数据
bool CInfomationElementListTable::DisplayChild(IXMLDOMNodePtr pChild)
{
	CString temp;

	//当获取的结点类型为NODE_TEXT，即项目值时
	if(pChild->nodeType == NODE_TEXT)
	{
		IsEmpty = false;

		temp = (char*)(pChildLast->nodeName);
		if(temp == "InfoServiceProviderId")
		{
			m_InfoServiceProviderId = atoi(pChild->text);
			IsEmpty = true;
		}
		else if(temp == "NameBaseId")
		{
			m_NameBaseId = atoi(pChild->text);
			IsEmpty = true;
		}
		else if(temp == "InfomationElementTableID")
		{
			Info.InfomationElementTableID = atoi(pChild->text);
		}
		else if(temp == "InfomationElementTableName_Chinese")
		{
			Info.InfomationElementTableName_Chinese = (char*)(pChild->text);
		}
		else if(temp == "InfomationElementTableName_English")
		{
			Info.InfomationElementTableName_English = (char*)(pChild->text);
		}
		else if(temp == "Description")
		{
			Info.Description = (char*)(pChild->text);
		}
		else if(temp == "EqualInfomationElementTableID")
		{
			Info.EqualInfomationElementTableID = atoi(pChild->text);
		}
		//若标记未定义
		else
		{
			temp = "Not Define '";
			temp += (char*)(pChildLast->nodeName);
			temp += "'";
			return AlarmErrorMessage(temp, "Internal Error");
		}
		return true;
	}
	//当获取的结点类型为NODE_ELEMENT，即标记时
	else if(pChild->nodeType == NODE_ELEMENT)
	{
		CString temp2;
		temp = (char*)(pChild->nodeName);
		//若pChildLast不为空时，再继续，防止pChildLast->nodeName操作Error
		if(pChildLast != NULL)
		{
			temp2 = (char*)(pChildLast->nodeName);
			//若不为第一个FunctionSection
			if(temp == "InfomationElementTableSection" && temp2 != "NameBaseId")
			{
				InfoArray.Add(Info);
				Info.EqualInfomationElementTableID = 0;
			}
		}
		//若pChildLast为空，必是pChild指向OperationList结点
		else
		{
			temp2 = "";
		}
		pChildLast = pChild;
	}
	return true;
}

//广度优先递归遍历XML结点树
bool CInfomationElementListTable::DisplayChildren(IXMLDOMNodePtr pParent)
{
	// display the current node's name
	if(!DisplayChild(pParent))
		return false;

	// simple for loop to get all children
	for (IXMLDOMNodePtr pChild = pParent->firstChild;
		NULL != pChild;
		pChild = pChild->nextSibling)
	{
		// for each child, call this function so that we get 
		// its children as well
		if(!DisplayChildren(pChild))
			return false;
	}
	return true;
}

bool CInfomationElementListTable::GetAllInfomationElementListTable()
{
	//清空旧数据
	InfoArray.RemoveAll();

	IsLoadXML = true;
	//设定信息项表列表所存储于xml的文件名
	CString strModuleFileName(INFORMATION_ELEMENT_LIST_TABLE_FILENAME);

	::CoInitialize(NULL);

	try
	{
	// Initialize COM
		IXMLDOMDocumentPtr m_plDomDocument;
		IXMLDOMElementPtr m_pDocRoot;

		HRESULT hr = m_plDomDocument.CreateInstance(CLSID_DOMDocument);
		if (FAILED(hr))
		{
			return AlarmErrorMessage("CreateInstance() Failed", "Internal Error");
		}

		// convert xml file name string to something COM can handle (BSTR)
		_bstr_t bstrFileName;
		bstrFileName = strModuleFileName.AllocSysString();

		// call the IXMLDOMDocumentPtr's load function to load the XML document
		variant_t vResult;
		vResult = m_plDomDocument->load(bstrFileName);
		if (((bool)vResult) == TRUE) // success!
		{
			// now that the document is loaded, we need to initialize the root pointer
			m_pDocRoot = m_plDomDocument->documentElement;
//			AfxMessageBox("Document loaded successfully!");
//			AfxMessageBox(m_plDomDocument->xml);
		}
		else
		{
			return AlarmErrorMessage("Document FAILED to load!", "Internal Error");
		}

		//准备产生数据
		pChildLast = NULL;
		Info.EqualInfomationElementTableID = 0;
		//开始遍历XML树
		if(DisplayChildren(m_pDocRoot))
		{
			//加入最后一组数据
			if(IsEmpty == false)
				InfoArray.Add(Info);

			return true;
		}
		else
		{
			return AlarmErrorMessage("Search XML Failed", "Internal Error");
		}
	}
	catch(_com_error &e)
	{
		return AlarmErrorMessage(e.ErrorMessage(), "Internal Error");
	}

	::CoUninitialize();
	return true;
}


//获取新的id值，即不复制型的primary key
bool CInfomationElementListTable::GetNewInfomationElementListTableID(unsigned int &NewID)
{
	int i;
//	CArrayInfomationElementListTableStruct InfoListArray;
//	if(GetAllInfomationElementListTable(InfoListArray))
//	{
/*		//显示从dll获得的信息，信息存储于CArrayModuleInfomationListStruct
		CString temp;
		char buff[256];
		for(i = 0; i < InfoListArray.GetSize(); i++)
		{
			temp = "InfomationElementTableSection";
			
			temp += "\nInfomationElementTableID: ";
			temp += itoa(InfoListArray.GetAt(i).InfomationElementTableID, buff, 10);
			
			temp += "\nInfomationElementTableName_Chinese: ";
			temp += InfoListArray.GetAt(i).InfomationElementTableName_Chinese;

			temp += "\nInfomationElementTableName_English: ";
			temp += InfoListArray.GetAt(i).InfomationElementTableName_English;

			temp += "\nDescription: ";
			temp += InfoListArray.GetAt(i).Description;

			temp += "\nEqualInfomationElementTableID: ";
			temp += itoa(InfoListArray.GetAt(i).EqualInfomationElementTableID, buff, 10);
			
			
			::MessageBox(0, temp, itoa(i, buff, 10), MB_OK);
		}
*/
	if(IsLoadXML == true)
	{
		//获得新ID值
		//ID值从1起
		NewID = 1;
		for(i = 0; i < InfoArray.GetSize(); i++)
		{
			if(InfoArray.GetAt(i).InfomationElementTableID >= NewID)
				NewID = InfoArray.GetAt(i).InfomationElementTableID + 1;
		}
		return true;
	}
	else
		return false;
}

//在信息项列表中添加表项
//在调用中自动取ID值
bool CInfomationElementListTable::AddInfomationElementList(InfomationElementListTableStruct &InfoList)
{
	unsigned int NewID;

	if(!GetAllInfomationElementListTable())
		return AlarmErrorMessage("GetAllInfomationElementListTable() Failed", "Internal Error");
	if(!GetNewInfomationElementListTableID(NewID))
		return AlarmErrorMessage("GetNewInfomationElementListTableID() Failed", "Internal Error");
	InfoList.InfomationElementTableID = NewID;
	InfoArray.Add(InfoList);
	if(!SaveToXML())
		return AlarmErrorMessage("SaveToXML() Failed", "Internal Error");
	return true;
}

//将InfoListArray中的数据存入XML中
bool CInfomationElementListTable::SaveToXML()
{
	if(IsLoadXML == false)
		return false;
	try
	{
		HRESULT hr;
		IXMLDOMNodePtr pXDN;
		MSXML::IXMLDOMDocumentPtr pXMLDoc = NULL;
		MSXML::IXMLDOMNodePtr   pCurrentNode = NULL;

		hr = CoInitialize(NULL); 
		hr = pXMLDoc.CreateInstance("Microsoft.XMLDOM");
		
		hr = pXMLDoc->QueryInterface(IID_IXMLDOMNode, (void **)&pXDN);


		// load a document
		_variant_t varXml("InfomationElementListTable_Original.xml");
		_variant_t varOut((bool)TRUE);
		varOut = pXMLDoc->load(varXml);
		if ((bool)varOut == FALSE)
			throw(0);
//		::MessageBox(0, pXMLDoc->xml, "", MB_OK);

	  
		VARIANT vType;
//		VariantInit(&vType);
//		V_VT(&vType) = VT_BSTR;

		vType.vt = VT_I4;
		V_I4(&vType) = 1; // NODE_ELEMENT

		CString temp;
		char buff[256];

		//set the top node as current
		pCurrentNode = pXMLDoc;

		//添加InfoServiceProviderId
		pXDN = pXMLDoc->createNode(vType, "InfoServiceProviderId", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_InfoServiceProviderId, buff, 10));

		//添加NameBaseId
		pXDN = pXMLDoc->createNode(vType, "NameBaseId", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_NameBaseId, buff, 10));


		//将InfoArray中的信息插入到pXMLDoc中
		for(int i = 0; i < InfoArray.GetSize(); i++)
		{
			//插入InfomationElementTableSection
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableSection", "");
			ASSERT(NULL != pXDN);
			pXMLDoc->documentElement->appendChild(pXDN);
			pCurrentNode = pXDN;

			//InfomationElementTableID
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableID", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoArray.GetAt(i).InfomationElementTableID, buff, 10));

			//InfomationElementTableName_Chinese
			temp = InfoArray.GetAt(i).InfomationElementTableName_Chinese;
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableName_Chinese", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));

		
			//InfomationElementTableName_English
			temp = InfoArray.GetAt(i).InfomationElementTableName_English;
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableName_English", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));
			
			//Description
			temp = InfoArray.GetAt(i).Description;
			pXDN = pXMLDoc->createNode(vType, "Description", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));

			//EqualInfomationElementTableID
			pXDN = pXMLDoc->createNode(vType, "EqualInfomationElementTableID", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoArray.GetAt(i).EqualInfomationElementTableID, buff, 10));

			pXDN = pCurrentNode->GetparentNode();
			pCurrentNode = pXDN;
		}

		//存文件
		VARIANT vFilename;
		VariantInit(&vFilename);
		V_VT(&vFilename) = VT_BSTR;
		V_BSTR(&vFilename) = SysAllocString(L"InfomationElementListTable.xml");
		
		pXMLDoc->save(vFilename);
		return true;
		
	}
	catch(...)
	{
		::MessageBox(NULL, _T("Exception occurred"), _T("Error"), MB_OK);
		return false;
	}
	CoUninitialize();
	return true;
}
