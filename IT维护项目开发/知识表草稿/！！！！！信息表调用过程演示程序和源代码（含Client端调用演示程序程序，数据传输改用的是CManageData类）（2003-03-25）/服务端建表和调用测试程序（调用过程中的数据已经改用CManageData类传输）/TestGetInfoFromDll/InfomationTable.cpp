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
	IsLoadXML = false;
	IsEmpty = true;
}

CInfomationTable::~CInfomationTable()
{

}


//����һ���µ���Ϣ���
//������
bool CInfomationTable::CreateInfomationTable()
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

		//���InfoServiceProviderId
		pXDN = pXMLDoc->createNode(vType, "InfoServiceProviderId", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_InfoServiceProviderId, buff, 10));

		//���NameBaseId
		pXDN = pXMLDoc->createNode(vType, "NameBaseId", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_NameBaseId, buff, 10));

		//�޸�InfomationElementTableID�����޸Ľ����InfomationElementTableIDȷ����
		//һ��InfomationElementTableID����ı䣬���Դ��޸�һ�㲻����ʾ��Ч��
		pXDN = pXMLDoc->createNode(vType, "InfomationElementTableID", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_InfomationElementTableID, buff, 10));
/*
		//set the top node as current
		pCurrentNode = pXMLDoc->documentElement;
		pCurrentNode->get_firstChild(&pXDN);
		pXDN->Puttext(itoa(m_InfomationElementTableID, buff, 10));
*/
		//��m_TableName�����ƴ��ļ�
		temp = m_TableName;
		temp += ".xml";
		VARIANT vFilename;
		VariantInit(&vFilename);
		V_VT(&vFilename) = VT_BSTR;
		V_BSTR(&vFilename) = temp.AllocSysString();
		
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

//��ȡһ����Ϣ����ȫ������
//������
//InfoArray�����ڷ�����Ϣ�������ݣ������˱��д洢��InfomationElementTableID�
//TableName������ƣ�����.XML��������Ϣ����б��е�InfomationElementTableName_English���Ӧ
bool CInfomationTable::GetAllInfomationElement()
{
	//��վ�����
	InfoArray.RemoveAll();

	IsLoadXML = true;

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

		//��m_TableName�����ƴ��ļ�
		CString temp;
		_bstr_t bstrFileName;
		temp = m_TableName;
		temp += ".xml";
		bstrFileName = temp.AllocSysString();

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
//		Info.EqualInfomationElementTableID = 0;
		//��ʼ����XML��
		if(DisplayChildren(m_pDocRoot))
		{
			//�������һ������
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



//���ݽ��������������
bool CInfomationTable::DisplayChild(IXMLDOMNodePtr pChild)
{
	CString temp;

	//����ȡ�Ľ������ΪNODE_TEXT������Ŀֵʱ
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
			if(temp == "InfomationElementSection" && temp2 != "InfomationElementTableID")
			{
				InfoArray.Add(Info);
//				Info.EqualInfomationElementTableID = 0;
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



//��InfoListArray�е����ݴ���m_TableNameָ����XML��
bool CInfomationTable::SaveToXML()
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

		//���InfoServiceProviderId
		pXDN = pXMLDoc->createNode(vType, "InfoServiceProviderId", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_InfoServiceProviderId, buff, 10));

		//���NameBaseId
		pXDN = pXMLDoc->createNode(vType, "NameBaseId", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_NameBaseId, buff, 10));

		//�޸�InfomationElementTableID�����޸Ľ����InfomationElementTableIDȷ����
		//һ��InfomationElementTableID����ı䣬���Դ��޸�һ�㲻����ʾ��Ч��
		pXDN = pXMLDoc->createNode(vType, "InfomationElementTableID", "");
		ASSERT(NULL != pXDN);
		pCurrentNode = pXMLDoc->documentElement->appendChild(pXDN);
		pCurrentNode->Puttext(itoa(m_InfomationElementTableID, buff, 10));


		//��InfoArray�е���Ϣ���뵽pXMLDoc��
		for(int i = 0; i < InfoArray.GetSize(); i++)
		{

			//����InfomationElementSection
			pXDN = pXMLDoc->createNode(vType, "InfomationElementSection", "");
			ASSERT(NULL != pXDN);
			pXMLDoc->documentElement->appendChild(pXDN);
			pCurrentNode = pXDN;

			//InfomationElementID
			pXDN = pXMLDoc->createNode(vType, "InfomationElementID", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoArray.GetAt(i).InfomationElementID, buff, 10));

			//Infomation
			temp = InfoArray.GetAt(i).Infomation;
			pXDN = pXMLDoc->createNode(vType, "Infomation", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));

		
			//EnglishName
			temp = InfoArray.GetAt(i).EnglishName;
			pXDN = pXMLDoc->createNode(vType, "EnglishName", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));
			
			//InfomationType
			pXDN = pXMLDoc->createNode(vType, "InfomationType", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(itoa(InfoArray.GetAt(i).InfomationType, buff, 10));

			//Description
			temp = InfoArray.GetAt(i).Description;
			pXDN = pXMLDoc->createNode(vType, "Description", "");
			ASSERT(NULL != pXDN);
			pCurrentNode->appendChild(pXDN);
			pXDN->Puttext(temp.GetBuffer(temp.GetLength()));


			pXDN = pCurrentNode->GetparentNode();
			pCurrentNode = pXDN;
		}

		//���ļ�
		temp = m_TableName;
		temp += ".xml";
		VARIANT vFilename;
		VariantInit(&vFilename);
		V_VT(&vFilename) = VT_BSTR;
		V_BSTR(&vFilename) = temp.AllocSysString();
		
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



//��ȡ�µ�idֵ�����������͵�primary key
//�ò���ָ��Ҫ�����ı����ͱ�����Ϣ���б��е�idֵ
bool CInfomationTable::GetNewInfomationElementID(unsigned int &NewID)
{
	int i;
	if(IsLoadXML == true)
	{
		//�����IDֵ
		//IDֵ��1��
		NewID = 1;
		for(i = 0; i < InfoArray.GetSize(); i++)
		{
			if(InfoArray.GetAt(i).InfomationElementID >= NewID)
				NewID = InfoArray.GetAt(i).InfomationElementID + 1;
		}
		return true;
	}
	else
		return false;
}


//����Ϣ�������ӱ���
bool CInfomationTable::AddInfomationElementList(InfomationElementStruct &InfoList)
{
	unsigned int NewID;

	if(!GetAllInfomationElement())
		return AlarmErrorMessage("GetAllInfomationElementListTable() Failed", "Internal Error");
	if(!GetNewInfomationElementID(NewID))
		return AlarmErrorMessage("GetNewInfomationElementID() Failed", "Internal Error");
	InfoList.InfomationElementID = NewID;
	InfoArray.Add(InfoList);
	if(!SaveToXML())
		return AlarmErrorMessage("SaveToXML() Failed", "Internal Error");
	return true;
}

