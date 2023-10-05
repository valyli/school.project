// InfomationTable.cpp: implementation of the CInfomationTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestGetInfoFromDll.h"
#include "InfomationTable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInfomationTable::CInfomationTable()
{
		IsEmpty = true;
}

CInfomationTable::~CInfomationTable()
{

}


//创建一张新的信息项表
//参数：
//InfomationElementTableID，此表在信息项表列表中的ID值
//TableName新表的名称（不含.XML），和信息项表列表中的InfomationElementTableName_English项对应
bool CInfomationTable::CreateInfomationTable(unsigned int InfomationElementTableID, CString TableName)
{
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
		_variant_t varXml("InfomationTable_Original.xml");
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
		pCurrentNode = pXMLDoc->documentElement;
		pCurrentNode->get_firstChild(&pXDN);
		pXDN->Puttext(itoa(InfomationElementTableID, buff, 10));

		//按TableName的名称存文件
		TableName += ".xml";
		VARIANT vFilename;
		VariantInit(&vFilename);
		V_VT(&vFilename) = VT_BSTR;
		V_BSTR(&vFilename) = TableName.AllocSysString();
		
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

//获取一张信息项表的全部数据
//参数：
//InfoArray，用于返回信息项表的数据，不含此表中存储的InfomationElementTableID项。
//TableName表的名称（不含.XML），和信息项表列表中的InfomationElementTableName_English项对应
bool CInfomationTable::GetAllInfomationElement(CArrayInfomationElementStruct& InfoListArray, CString TableName)
{
	//清空旧数据
	InfoArray.RemoveAll();

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
		TableName += ".xml";
		bstrFileName = TableName.AllocSysString();

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
//		Info.EqualInfomationElementTableID = 0;
		//开始遍历XML树
		if(DisplayChildren(m_pDocRoot))
		{
			//加入最后一组数据
			if(IsEmpty == false)
				InfoArray.Add(Info);
			//复制数据到从参数传入的数据结构
			for(int i = 0; i < InfoArray.GetSize(); i++)
				InfoListArray.Add(InfoArray.GetAt(i));

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



//根据结点类型生成数据
bool CInfomationTable::DisplayChild(IXMLDOMNodePtr pChild)
{
	CString temp;

	//当获取的结点类型为NODE_TEXT，即项目值时
	if(pChild->nodeType == NODE_TEXT)
	{
		IsEmpty = false;

		temp = (char*)(pChildLast->nodeName);
		if(temp == "InfomationElementTableID")
		{
			m_InfomationElementTableID = atoi(pChild->text);
			IsEmpty = true;
		}
		else if(temp == "InfomationElementID")
		{
			Info.InfomationElementID = atoi(pChild->text);
		}
		else if(temp == "Infomation")
		{
			Info.Infomation = (char*)(pChild->text);
		}
		else if(temp == "EnglishName")
		{
			Info.EnglishName = (char*)(pChild->text);
		}
		else if(temp == "InfomationType")
		{
			Info.InfomationType = atoi(pChild->text);
		}
		else if(temp == "Description")
		{
			Info.Description = (char*)(pChild->text);
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
			if(temp == "InfomationElementSection" && temp2 != "InfomationElementTableID")
			{
				InfoArray.Add(Info);
//				Info.EqualInfomationElementTableID = 0;
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
bool CInfomationTable::DisplayChildren(IXMLDOMNodePtr pParent)
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



//将InfoListArray中的数据存入TableName指定的XML中
bool CInfomationTable::SaveToXML(CArrayInfomationElementStruct& InfoListArray, CString TableName)
{
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
		_variant_t varXml("InfomationTable_Original.xml");
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

		//修改InfomationElementTableID，其修改结果由InfomationElementTableID确定。
		//一般InfomationElementTableID不会改变，所以此修改一般不会显示出效果
		pXDN = pXMLDoc->createNode(vType, "InfomationElementTableID", "");
		ASSERT(NULL != pXDN);
		pXDN = pXMLDoc->documentElement->GetfirstChild();
		pXDN->Puttext(itoa(m_InfomationElementTableID, buff, 10));

		//将InfoArray中的信息插入到pXMLDoc中
		for(int i = 0; i < InfoListArray.GetSize(); i++)
		{

			//插入InfomationElementSection
			pXDN = pXMLDoc->createNode(vType, "InfomationElementSection", "");
			ASSERT(NULL != pXDN);
			pXMLDoc->documentElement->appendChild(pXDN);
			pCurrentNode = pXDN;

			//InfomationElementID
			pXDN = pXMLDoc->createNode(vType, "InfomationElementID", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoListArray.GetAt(i).InfomationElementID, buff, 10));

			//Infomation
			temp = InfoListArray.GetAt(i).Infomation;
			pXDN = pXMLDoc->createNode(vType, "Infomation", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));

		
			//EnglishName
			temp = InfoListArray.GetAt(i).EnglishName;
			pXDN = pXMLDoc->createNode(vType, "EnglishName", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));
			
			//InfomationType
			pXDN = pXMLDoc->createNode(vType, "InfomationType", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoListArray.GetAt(i).InfomationType, buff, 10));

			//Description
			temp = InfoListArray.GetAt(i).Description;
			pXDN = pXMLDoc->createNode(vType, "Description", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));


			pXDN = pCurrentNode->GetparentNode();
			pCurrentNode = pXDN;
		}

		//存文件
		TableName += ".xml";
		VARIANT vFilename;
		VariantInit(&vFilename);
		V_VT(&vFilename) = VT_BSTR;
		V_BSTR(&vFilename) = TableName.AllocSysString();
		
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



//获取新的id值，即不复制型的primary key
//用参数指定要操作的表名和表在信息项列表中的id值
bool CInfomationTable::GetNewInfomationElementID(unsigned int &NewID, CString TableName)
{
	int i;
	CArrayInfomationElementStruct InfoListArray;
	if(GetAllInfomationElement(InfoListArray, TableName))
	{
		//获得新ID值
		//ID值从1起
		NewID = 1;
		for(i = 0; i < InfoListArray.GetSize(); i++)
		{
			if(InfoListArray.GetAt(i).InfomationElementID >= NewID)
				NewID = InfoListArray.GetAt(i).InfomationElementID + 1;
		}
		return true;
	}
	else
		return false;
}


//在信息项表中添加表项
bool CInfomationTable::AddInfomationElementList(InfomationElementStruct &InfoList, CString TableName)
{
	unsigned int NewID;
	CArrayInfomationElementStruct InfoListArray;

	if(!GetAllInfomationElement(InfoListArray, TableName))
		return AlarmErrorMessage("GetAllInfomationElementListTable() Failed", "Internal Error");
	if(!GetNewInfomationElementID(NewID, TableName))
		return AlarmErrorMessage("GetNewInfomationElementID() Failed", "Internal Error");
	InfoList.InfomationElementID = NewID;
	InfoListArray.Add(InfoList);
	if(!SaveToXML(InfoListArray, TableName))
		return AlarmErrorMessage("SaveToXML() Failed", "Internal Error");
	return true;
}

