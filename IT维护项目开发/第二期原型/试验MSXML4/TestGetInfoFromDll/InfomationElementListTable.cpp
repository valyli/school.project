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
		IsEmpty = true;
}

CInfomationElementListTable::~CInfomationElementListTable()
{

}



//���ݽ��������������
bool CInfomationElementListTable::DisplayChild(IXMLDOMNodePtr pChild)
{
	CString temp;

	//����ȡ�Ľ������ΪNODE_TEXT������Ŀֵʱ
	if(pChild->nodeType == NODE_TEXT)
	{
		IsEmpty = false;

		temp = (char*)(pChildLast->nodeName);
		if(temp == "InfomationElementTableID")
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
		//�����δ����
		else
		{
			temp = "Not Define '";
			temp += (char*)(pChildLast->nodeName);
			temp += "'";
			return AlarmErrorMessage(temp, "Internal Error");
		}
		return true;
	}
	//����ȡ�Ľ������ΪNODE_ELEMENT�������ʱ
	else if(pChild->nodeType == NODE_ELEMENT)
	{
		CString temp2;
		temp = (char*)(pChild->nodeName);
		//��pChildLast��Ϊ��ʱ���ټ�������ֹpChildLast->nodeName����Error
		if(pChildLast != NULL)
		{
			temp2 = (char*)(pChildLast->nodeName);
			//����Ϊ��һ��FunctionSection
			if(temp == "InfomationElementTableSection" && temp2 != "InfomationElementListTable")
			{
				InfoArray.Add(Info);
				Info.EqualInfomationElementTableID = 0;
			}
		}
		//��pChildLastΪ�գ�����pChildָ��OperationList���
		else
		{
			temp2 = "";
		}
		pChildLast = pChild;
	}
	return true;
}

//������ȵݹ����XML�����
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

bool CInfomationElementListTable::GetAllInfomationElementListTable(CArrayInfomationElementListTableStruct &InfoListArray)
{
	//��վ�����
	InfoListArray.RemoveAll();
	InfoArray.RemoveAll();

	//�趨��Ϣ����б����洢��xml���ļ���
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

		//׼����������
		pChildLast = NULL;
		Info.EqualInfomationElementTableID = 0;
		//��ʼ����XML��
		if(DisplayChildren(m_pDocRoot))
		{
			//�������һ������
			if(IsEmpty == false)
				InfoArray.Add(Info);
			//�������ݵ��Ӳ�����������ݽṹ
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


//��ȡ�µ�idֵ�����������͵�primary key
bool CInfomationElementListTable::GetNewInfomationElementListTableID(unsigned int &NewID)
{
	int i;
	CArrayInfomationElementListTableStruct InfoListArray;
	if(GetAllInfomationElementListTable(InfoListArray))
	{
/*		//��ʾ��dll��õ���Ϣ����Ϣ�洢��CArrayModuleInfomationListStruct
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
		//�����IDֵ
		//IDֵ��1��
		NewID = 1;
		for(i = 0; i < InfoListArray.GetSize(); i++)
		{
			if(InfoListArray.GetAt(i).InfomationElementTableID >= NewID)
				NewID = InfoListArray.GetAt(i).InfomationElementTableID + 1;
		}
		return true;
	}
	else
		return false;
}

//����Ϣ���б�����ӱ���
bool CInfomationElementListTable::AddInfomationElementList(InfomationElementListTableStruct &InfoList)
{
	unsigned int NewID;
	CArrayInfomationElementListTableStruct InfoListArray;

	if(!GetAllInfomationElementListTable(InfoListArray))
		return AlarmErrorMessage("GetAllInfomationElementListTable() Failed", "Internal Error");
	if(!GetNewInfomationElementListTableID(NewID))
		return AlarmErrorMessage("GetNewInfomationElementListTableID() Failed", "Internal Error");
	InfoList.InfomationElementTableID = NewID;
	InfoListArray.Add(InfoList);
	if(!SaveToXML(InfoListArray))
		return AlarmErrorMessage("SaveToXML() Failed", "Internal Error");
	return true;
}

//��InfoListArray�е����ݴ���XML��
bool CInfomationElementListTable::SaveToXML(CArrayInfomationElementListTableStruct& InfoListArray)
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

		//��InfoArray�е���Ϣ���뵽pXMLDoc��
		for(int i = 0; i < InfoListArray.GetSize(); i++)
		{
			//����InfomationElementTableSection
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableSection", "");
			ASSERT(NULL != pXDN);
			pXMLDoc->documentElement->appendChild(pXDN);
			pCurrentNode = pXDN;

			//InfomationElementTableID
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableID", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoListArray.GetAt(i).InfomationElementTableID, buff, 10));

			//InfomationElementTableName_Chinese
			temp = InfoListArray.GetAt(i).InfomationElementTableName_Chinese;
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableName_Chinese", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));

		
			//InfomationElementTableName_English
			temp = InfoListArray.GetAt(i).InfomationElementTableName_English;
			pXDN = pXMLDoc->createNode(vType, "InfomationElementTableName_English", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));
			
			//Description
			temp = InfoListArray.GetAt(i).Description;
			pXDN = pXMLDoc->createNode(vType, "Description", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));

			//EqualInfomationElementTableID
			pXDN = pXMLDoc->createNode(vType, "EqualInfomationElementTableID", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoListArray.GetAt(i).EqualInfomationElementTableID, buff, 10));

			pXDN = pCurrentNode->GetparentNode();
			pCurrentNode = pXDN;
		}

		//���ļ�
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
