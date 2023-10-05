// LIDP_Parser.cpp: implementation of the LIDP_Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "LIDP_Parser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LIDP_Parser::LIDP_Parser()
{
	//��ʼ������ƽ̨��أ���WIN32�±���ִ�д˲���
	try
	{
		XMLPlatformUtils::Initialize();
	}
	catch (const XMLException& toCatch)
	{
		char* message = XMLString::transcode(toCatch.getMessage());
		printf("Error during initialization! : %s\n", message);
		XMLString::release(&message);
	}
}

LIDP_Parser::~LIDP_Parser()
{
	//��ֹ����ƽ̨��أ���WIN32�±���ִ�д˲���
	XMLPlatformUtils::Terminate();
}

DOMDocument* LIDP_Parser::OpenXmlFile(char* FileName)
{
	//��ʼ������ƽ̨�޹أ������ӿڶ���
	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
	//��ȡ����������
	DOMBuilder* dbf = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	//����һ���ĵ������������
	return dbf->parseURI(XMLString::transcode(FileName));
}

SMM_INT32 LIDP_Parser::GetInfoBase(LIDP_tagInfoBase &tag, DOMDocument* doc)
{
	//�����һ�����ļ�ʧ�ܣ��ͷ���-1
	if(doc == LIDP_NULL)
		return -1;
	//��ȡ�ĵ��ĸ����
	DOMElement* root = doc->getDocumentElement();

	//��ȡProviderID
	DOMNodeList* node_list = root->getElementsByTagName(XMLString::transcode("ProviderID"));
	if(node_list->getLength() != 1)
		return -1;
	tag.ProviderID = atoi(XMLString::transcode(node_list->item(0)->getFirstChild()->getNodeValue()));

	//��ȡInfoBaseID
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseID"));
	if(node_list->getLength() != 1)
		return -1;
	tag.InfoBaseID = atoi(XMLString::transcode(node_list->item(0)->getFirstChild()->getNodeValue()));

	//��ȡName
	node_list = root->getElementsByTagName(XMLString::transcode("Name"));
	if(node_list->getLength() != 1)
		return -1;
	tag.Name = (XMLCh*)(node_list->item(0)->getFirstChild()->getNodeValue());

	//��ȡDescriptions
	node_list = root->getElementsByTagName(XMLString::transcode("Descriptions"));
	if(node_list->getLength() < 1)
		return -1;
	XMLSize_t i;
	for(i = 0; i < node_list->getLength(); i++)
	{
		//����ҵ�����Ӧ��Descriptions���ڴ�Ҫ���丸������ΪInfoBase
		if(XMLString::equals(node_list->item(i)->getParentNode()->getNodeName(), XMLString::transcode("InfoBase")))
			break;
	}
	//���δ�ҵ���Ӧ��Descriptions
	if(i == node_list->getLength())
		return -1;
	GetDescriptions(node_list->item(i), tag.Descriptions);

	//��ȡInfoBaseDataTypes
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseDataTypes"));
	if(node_list->getLength() != 1)
		return -1;
	GetInfoBaseDataTypes(node_list->item(i), tag.InfoBaseDataTypes);

	//��ȡInfoBaseActions
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseActions"));
	if(node_list->getLength() != 1)
		return -1;
	GetInfoBaseActions(node_list->item(i), tag.InfoBaseActions);

	//��ȡInfoItems
	node_list = root->getElementsByTagName(XMLString::transcode("InfoItems"));
	if(node_list->getLength() != 1)
		return -1;
	GetInfoItems(node_list->item(i), tag.InfoItems);

	return 1;
}


SMM_INT32 LIDP_Parser::GetDescriptions(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*>& Descriptions)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("Description")))
		{
			LIDP_tagDescription* tag = new LIDP_tagDescription;
			tag->Description = (XMLCh*)(node_list->item(i)->getFirstChild()->getNodeValue());
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			tag->Language = (XMLCh*)(map->getNamedItem(XMLString::transcode("Language"))->getNodeValue());
			Descriptions.Add(tag);
		}
	}

	return 1;
}



SMM_INT32 LIDP_Parser::GetInfoBaseDataTypes(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagDataType, LIDP_tagDataType*>& InfoBaseDataTypes)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("DataType")))
		{
			LIDP_tagDataType* tag = new LIDP_tagDataType;
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			tag->Name = (XMLCh*)(map->getNamedItem(XMLString::transcode("Name"))->getNodeValue());
			tag->ID = atoi(XMLString::transcode(map->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));
			InfoBaseDataTypes.Add(tag);
		}
	}

	return 1;
}


SMM_INT32 LIDP_Parser::GetInfoBaseActions(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagActionDefine, LIDP_tagActionDefine*>& InfoBaseActions)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("Action")))
		{
			LIDP_tagActionDefine* tag = new LIDP_tagActionDefine;
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			tag->Name = (XMLCh*)(map->getNamedItem(XMLString::transcode("Name"))->getNodeValue());
			tag->ID = atoi(XMLString::transcode(map->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));

			DOMNodeList* node_list2 = node_list->item(i)->getChildNodes();
			for(XMLSize_t j = 0; j < node_list2->getLength(); j++)
			{
				//����ҵ�����Ӧ��Descriptions
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Descriptions")))
					break;
			}
			//���δ�ҵ���Ӧ��Descriptions
			if(j == node_list2->getLength())
				return -1;
			GetDescriptions(node_list2->item(j), tag->Descriptions);


			InfoBaseActions.Add(tag);
		}
	}

	return 1;
}



SMM_INT32 LIDP_Parser::GetInfoItems(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagInfoItem, LIDP_tagInfoItem*>& InfoItems)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("InfoItem")))
		{
			LIDP_tagInfoItem* tag = new LIDP_tagInfoItem;
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			tag->Name = (XMLCh*)(map->getNamedItem(XMLString::transcode("Name"))->getNodeValue());
			tag->ID = atoi(XMLString::transcode(map->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));

			DOMNodeList* node_list2 = node_list->item(i)->getChildNodes();
			for(XMLSize_t j = 0; j < node_list2->getLength(); j++)
			{
				//����ҵ�����Ӧ��Descriptions
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Descriptions")))
				{
					GetDescriptions(node_list2->item(j), tag->Descriptions);
				}
				//����ҵ�����Ӧ��DataType
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("DataType")))
				{
					DOMNamedNodeMap* map2 = node_list2->item(j)->getAttributes();
					tag->DataType = atoi(XMLString::transcode(map2->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));
				}
				//����ҵ�����Ӧ��Actions
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Actions")))
				{
					GetActions(node_list2->item(j), tag->Actions);
				}
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("SubTree")))
				{
					GetInfoItems(node_list2->item(j), tag->SubTree);
				}
			}
			InfoItems.Add(tag);
		}
	}
	return 1;
}



SMM_INT32 LIDP_Parser::GetActions(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagAction, LIDP_tagAction*>& Actions)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		//����ҵ�����Ӧ��Action
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("Action")))
		{
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			LIDP_tagAction* tag = new LIDP_tagAction;
			tag->ID = atoi(XMLString::transcode(map->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));

			DOMNodeList* node_list2 = node_list->item(i)->getChildNodes();
			for(XMLSize_t j = 0; j < node_list2->getLength(); j++)
			{
				//����ҵ�����Ӧ��Parameter
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Parameter")))
				{
					LIDP_tagParameterInInfoBase* tag2 = new LIDP_tagParameterInInfoBase;
					DOMNamedNodeMap* map2 = node_list2->item(j)->getAttributes();
					tag2->Name = (XMLCh*)(map2->getNamedItem(XMLString::transcode("Name"))->getNodeValue());
					tag2->ID = atoi(XMLString::transcode(map2->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));
					tag2->DataTypeID = atoi(XMLString::transcode(map2->getNamedItem(XMLString::transcode("DataTypeID"))->getNodeValue()));

					tag->Parameters.Add(tag2);
				}
			}

			Actions.Add(tag);
		}
	}
	return 1;
}


SMM_INT32 LIDP_Parser::GetModuleDeclare(LIDP_CArrayTemplate<LIDP_tagModule, LIDP_tagModule*>& Modules, DOMDocument* doc)
{
	//�����һ�����ļ�ʧ�ܣ��ͷ���-1
	if(doc == LIDP_NULL)
		return -1;
	//��ȡ�ĵ��ĸ����
	DOMElement* root = doc->getDocumentElement();
	DOMNode* node = root->getFirstChild();
	DOMNodeList* node_list = root->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("Module")))
		{
			LIDP_tagModule* tag = new LIDP_tagModule;
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			tag->Name = (XMLCh*)(map->getNamedItem(XMLString::transcode("Name"))->getNodeValue());
			tag->FileName = (XMLCh*)(map->getNamedItem(XMLString::transcode("FileName"))->getNodeValue());

			DOMNodeList* node_list2 = node_list->item(i)->getChildNodes();
			for(XMLSize_t j = 0; j < node_list2->getLength(); j++)
			{
				//����ҵ�����Ӧ��ProviderID
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("ProviderID")))
				{
					tag->ProviderID = atoi(XMLString::transcode(node_list2->item(j)->getFirstChild()->getNodeValue()));
				}
				//����ҵ�����Ӧ��InfoBaseID
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("InfoBaseID")))
				{
					tag->InfoBaseID = atoi(XMLString::transcode(node_list2->item(j)->getFirstChild()->getNodeValue()));
				}
				//����ҵ�����Ӧ��InfoItemList
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("InfoItemList")))
				{
					GetInfoItemsInModule(node_list2->item(j), tag->InfoItemList);
				}
			}
			Modules.Add(tag);
		}
	}
	return 1;
}






SMM_INT32 LIDP_Parser::GetInfoItemsInModule(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagInfoItemInModule, LIDP_tagInfoItemInModule*>& InfoItemList)
{
	DOMNodeList* node_list = node->getChildNodes();
	for(XMLSize_t i = 0; i < node_list->getLength(); i++)
	{
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("InfoItem")))
		{
			LIDP_tagInfoItemInModule* tag = new LIDP_tagInfoItemInModule;
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			tag->ID = (XMLCh*)(map->getNamedItem(XMLString::transcode("ID"))->getNodeValue());
			tag->AcitonID = atoi(XMLString::transcode(map->getNamedItem(XMLString::transcode("AcitonID"))->getNodeValue()));
			tag->FunctionName = (XMLCh*)(map->getNamedItem(XMLString::transcode("FunctionName"))->getNodeValue());

			DOMNodeList* node_list2 = node_list->item(i)->getChildNodes();
			for(XMLSize_t j = 0; j < node_list2->getLength(); j++)
			{
				//����ҵ�����Ӧ��Parameter
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Parameter")))
				{
					LIDP_tagParameterInModule* tag2 = new LIDP_tagParameterInModule;
					DOMNamedNodeMap* map2 = node_list2->item(j)->getAttributes();
					tag2->ID = atoi(XMLString::transcode(map2->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));
					tag2->DataTypeID = atoi(XMLString::transcode(map2->getNamedItem(XMLString::transcode("DataTypeID"))->getNodeValue()));
					tag->Parameters.Add(tag2);
				}
			}
			InfoItemList.Add(tag);
		}
	}
	return 1;
}
