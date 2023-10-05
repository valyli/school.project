// ModuleInfoList.cpp: implementation of the CModuleInfoList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModuleInfoList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModuleInfoList::CModuleInfoList()
{

}

CModuleInfoList::~CModuleInfoList()
{

}



//���ݽ��������������
bool CModuleInfoList::DisplayChild(IXMLDOMNodePtr pChild)
{
	CString temp;

	//����ȡ�Ľ������ΪNODE_TEXT������Ŀֵʱ
	if(pChild->nodeType == NODE_TEXT)
	{
		temp = (char*)(pChildLast->nodeName);
		if(temp == "OperationID")
		{
			Info.OperationID = atoi(pChild->text);
		}
		else if(temp == "InfomationElementTableID")
		{
			Info.InfomationElementTableID = atoi(pChild->text);
		}
		else if(temp == "InfomationElementID")
		{
			Info.InfomationElementID = atoi(pChild->text);
		}
		else if(temp == "OperationType")
		{
			Info.OperationType = atoi(pChild->text);
		}
		else if(temp == "SupportSystemType")
		{
			Info.SupportSystemType = atoi(pChild->text);
		}
		else if(temp == "ModuleType")
		{
			Info.ModuleType = atoi(pChild->text);
		}
		else if(temp == "ParameterType")
		{
			Info.ParameterType = atoi(pChild->text);
		}
		else if(temp == "IsStorageReturnValueInParameter")
		{
			Info.IsStorageReturnValueInParameter = atoi(pChild->text);
		}
		else if(temp == "ServiceFileName")
		{
			Info.ServiceFileName = (char*)(pChild->text);
		}
		else if(temp == "InterfaceFunction")
		{
			Info.InterfaceFunction = (char*)(pChild->text);
		}
		else if(temp == "ParameterValue")
		{
			Info.ParameterValue = (char*)(pChild->text);
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
		//��pChildLast��Ϊ��
		if(pChildLast != NULL)
		{
			temp2 = (char*)(pChildLast->nodeName);
			//����Ϊ��һ��FunctionSection
			if(temp == "FunctionSection" && temp2 != "OperationList")
			{
				InfoArray.Add(Info);
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
bool CModuleInfoList::DisplayChildren(IXMLDOMNodePtr pParent)
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

//��ȡģ����Ϣ�Ĺ��ýӿں���
bool CModuleInfoList::GetInfoList(CArrayModuleInfomationListStruct &InfoListArray)
{
	::CoInitialize(NULL);

	try
	{
	// Initialize COM
		IXMLDOMDocumentPtr m_plDomDocument;
		IXMLDOMElementPtr m_pDocRoot;

		HRESULT hr = m_plDomDocument.CreateInstance(CLSID_DOMDocument);
		if (FAILED(hr))
		{
			return AlarmErrorMessage("CreateInstance() Failed", "Internal Error In GetInfoList()");
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
			//��ʾ�����xml�ļ���Ϣ
//			AfxMessageBox("Document loaded successfully!");
//			AfxMessageBox(m_plDomDocument->xml);
		}
		else
		{
			return AlarmErrorMessage("Document FAILED to load!", "Internal Error In GetInfoList()");
		}

		//׼����������
		pChildLast = NULL;
		//��ʼ����XML��
		if(DisplayChildren(m_pDocRoot))
		{
			//�������һ������
			InfoArray.Add(Info);
			for(int i = 0; i < InfoArray.GetSize(); i++)
				InfoListArray.Add(InfoArray.GetAt(i));

			return true;
		}
		else
		{
			return AlarmErrorMessage("Search XML Failed", "Internal Error In GetInfoList()");
		}
	}
	catch(_com_error &e)
	{
		return AlarmErrorMessage(e.ErrorMessage(), "Internal Error In GetInfoList()");
	}

	::CoUninitialize();
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////

