// LIDP_Parser.cpp: implementation of the LIDP_Parser class.
//
//////////////////////////////////////////////////////////////////////

#include "LIDP_Parser.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LIDP_Parser::LIDP_Parser()
{
	//初始化，与平台相关，在WIN32下必须执行此步骤
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
	//终止，与平台相关，在WIN32下必须执行此步骤
	XMLPlatformUtils::Terminate();
}

DOMDocument* LIDP_Parser::OpenXmlFile(char* FileName)
{
	//初始化，与平台无关，创建接口对象
	DOMImplementation *impl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("LS"));
	//获取解析器对象
	DOMBuilder* dbf = ((DOMImplementationLS*)impl)->createDOMBuilder(DOMImplementationLS::MODE_SYNCHRONOUS, 0);
	//读入一个文档，将句柄返回
	return dbf->parseURI(XMLString::transcode(FileName));
}

SMM_INT32 LIDP_Parser::GetInfoBase(LIDP_tagInfoBase &tag, DOMDocument* doc)
{
	//如果上一步读文件失败，就返回-1
	if(doc == LIDP_NULL)
		return -1;
	//获取文档的根结点
	DOMElement* root = doc->getDocumentElement();

	//获取ProviderID
	DOMNodeList* node_list = root->getElementsByTagName(XMLString::transcode("ProviderID"));
	if(node_list->getLength() != 1)
		return -1;
	tag.ProviderID = atoi(XMLString::transcode(node_list->item(0)->getFirstChild()->getNodeValue()));

	//获取InfoBaseID
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseID"));
	if(node_list->getLength() != 1)
		return -1;
	tag.InfoBaseID = atoi(XMLString::transcode(node_list->item(0)->getFirstChild()->getNodeValue()));

	//获取Name
	node_list = root->getElementsByTagName(XMLString::transcode("Name"));
	if(node_list->getLength() != 1)
		return -1;
	tag.Name = (XMLCh*)(node_list->item(0)->getFirstChild()->getNodeValue());

	//获取Descriptions
	node_list = root->getElementsByTagName(XMLString::transcode("Descriptions"));
	if(node_list->getLength() < 1)
		return -1;
	XMLSize_t i;
	for(i = 0; i < node_list->getLength(); i++)
	{
		//如果找到了相应的Descriptions，在此要求其父结点必须为InfoBase
		if(XMLString::equals(node_list->item(i)->getParentNode()->getNodeName(), XMLString::transcode("InfoBase")))
			break;
	}
	//如果未找到相应的Descriptions
	if(i == node_list->getLength())
		return -1;
	GetDescriptions(node_list->item(i), tag.Descriptions);

	//获取InfoBaseDataTypes
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseDataTypes"));
	if(node_list->getLength() != 1)
		return -1;
	GetInfoBaseDataTypes(node_list->item(i), tag.InfoBaseDataTypes);

	//获取InfoBaseActions
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseActions"));
	if(node_list->getLength() != 1)
		return -1;
	GetInfoBaseActions(node_list->item(i), tag.InfoBaseActions);

	//获取InfoItems
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
				//如果找到了相应的Descriptions
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Descriptions")))
					break;
			}
			//如果未找到相应的Descriptions
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
				//如果找到了相应的Descriptions
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("Descriptions")))
				{
					GetDescriptions(node_list2->item(j), tag->Descriptions);
				}
				//如果找到了相应的DataType
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("DataType")))
				{
					DOMNamedNodeMap* map2 = node_list2->item(j)->getAttributes();
					tag->DataType = atoi(XMLString::transcode(map2->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));
				}
				//如果找到了相应的Actions
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
		//如果找到了相应的Action
		if(XMLString::equals(node_list->item(i)->getNodeName(), XMLString::transcode("Action")))
		{
			DOMNamedNodeMap* map = node_list->item(i)->getAttributes();
			LIDP_tagAction* tag = new LIDP_tagAction;
			tag->ID = atoi(XMLString::transcode(map->getNamedItem(XMLString::transcode("ID"))->getNodeValue()));

			DOMNodeList* node_list2 = node_list->item(i)->getChildNodes();
			for(XMLSize_t j = 0; j < node_list2->getLength(); j++)
			{
				//如果找到了相应的Parameter
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
	//如果上一步读文件失败，就返回-1
	if(doc == LIDP_NULL)
		return -1;
	//获取文档的根结点
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
				//如果找到了相应的ProviderID
				if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("ProviderID")))
				{
					tag->ProviderID = atoi(XMLString::transcode(node_list2->item(j)->getFirstChild()->getNodeValue()));
				}
				//如果找到了相应的InfoBaseID
				else if(XMLString::equals(node_list2->item(j)->getNodeName(), XMLString::transcode("InfoBaseID")))
				{
					tag->InfoBaseID = atoi(XMLString::transcode(node_list2->item(j)->getFirstChild()->getNodeValue()));
				}
				//如果找到了相应的InfoItemList
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
				//如果找到了相应的Parameter
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
