#include <iostream.h>
#include <stdio.h>

#include "LIDP_Command_Dispatch_Process.h"
#include "LIDP_Parser.h"

int main(int argc, char* argv[])
{
/*	LIDP_Command_Dispatch_Process a;
	LIDP_tagInstruction b;
	b.InstructionID = COMMAND_DRIVER;
	b.driverCommand.ActionID = 0;
	b.driverCommand.InfoBaseID = 1;
	b.driverCommand.InfoBaseProviderID = 2;
	b.driverCommand.InfoItemID = (SMM_INT32*)malloc(sizeof(SMM_INT32) * 2);
	b.driverCommand.InfoItemID[0] = 5;
	b.driverCommand.InfoItemID[1] = 6;
	b.driverCommand.NumOfInfoItemID = 2;
	b.driverCommand.ParameterList.NumOfList = 1;
	b.driverCommand.ParameterList.List = (LIDP_tagVariant**)malloc(sizeof(LIDP_tagVariant*));
	b.driverCommand.ParameterList.List[0] = (LIDP_tagVariant*)malloc(sizeof(LIDP_tagVariant));
	b.driverCommand.ParameterList.List[0]->Type = LIDP_Integer;
	b.driverCommand.ParameterList.List[0]->Length = 4;
	b.driverCommand.ParameterList.List[0]->Buff = (SMM_UCHAR*)malloc(4);
	*((SMM_INT32*)b.driverCommand.ParameterList.List[0]->Buff) = 10;
	LIDP_tagTransfer* c;
	c = a.LIDP_Make_tagTransfer_From_tagInstruction(b);

	LIDP_tagInstruction* d;
	d = a.LIDP_Revert_tagInstruction_From_tagTransfer(*c);

	a.LIDP_Free_tagInstruction(&b);
	free(c);
*/

/*	LIDP_tagDriverReturnBlock a;
	a.ActionID = 0;
	a.InfoBaseID = 1;
	a.InfoBaseProviderID = 2;
	a.NumOfInfoItemID = 2;
	a.InfoItemID = (SMM_INT32*)malloc(sizeof(SMM_INT32) * 2);
	a.InfoItemID[0] = 4;
	a.InfoItemID[1] = 5;
	a.ParameterList.NumOfList = 2;
	a.ParameterList.List = (LIDP_tagVariant**)malloc(sizeof(LIDP_tagVariant*) * 2);

	a.ParameterList.List[0] = (LIDP_tagVariant*)malloc(sizeof(LIDP_tagVariant));
	a.ParameterList.List[0]->Type = LIDP_Integer;
	a.ParameterList.List[0]->Length = 4;
	a.ParameterList.List[0]->Buff = (SMM_UCHAR*)malloc(4);
	*((SMM_INT32*)a.ParameterList.List[0]->Buff) = 10;

	a.ParameterList.List[1] = (LIDP_tagVariant*)malloc(sizeof(LIDP_tagVariant));
	a.ParameterList.List[1]->Type = LIDP_Integer;
	a.ParameterList.List[1]->Length = 9;
	a.ParameterList.List[1]->Buff = (SMM_UCHAR*)malloc(4);
	strcpy((SMM_CHAR*)(a.ParameterList.List[1]->Buff), "abc");

	LIDP_Command_Dispatch_Process b;
	LIDP_tagTransfer* c;
	c = b.LIDP_Make_tagTransfer_From_tagDriverReturnBlock(a);
	LIDP_tagDriverReturnBlock* d;
	d = b.LIDP_Revert_tagDriverReturnBlock_From_tagTransfer(*c);
	printf("%d", *((SMM_INT32*)(d->ParameterList.List[0]->Buff)));
	printf("%s", (SMM_CHAR*)(d->ParameterList.List[1]->Buff));

	b.LIDP_Free_tagDriverReturnBlock(&a);
	printf("%d", d->InfoItemID[1]);
	free(c);
*/


	int i, j;
	LIDP_Parser a;
	DOMDocument* doc = a.OpenXmlFile("TestInfoBase.xml");
/*	LIDP_tagInfoBase b;
	a.GetInfoBase(b, doc);
	printf("ProviderID = %d\n", b.ProviderID);
	printf("InfoBaseID = %d\n", b.InfoBaseID);
	printf("Name = %s\n", XMLString::transcode(b.Name.str));
	for(i = 0; i < b.Descriptions.GetCount(); i++)
	{
		printf("Descriptions.Description = %s\n", XMLString::transcode(b.Descriptions[i].Description.str));
		printf("Descriptions.Language = %s\n", XMLString::transcode(b.Descriptions[i].Language.str));
	}

	for(i = 0; i < b.InfoBaseDataTypes.GetCount(); i++)
	{
		printf("InfoBaseDataTypes.Name = %s\n", XMLString::transcode(b.InfoBaseDataTypes[i].Name.str));
		printf("InfoBaseDataTypes.ID = %d\n", b.InfoBaseDataTypes[i].ID);
	}
	
	for(i = 0; i < b.InfoBaseActions.GetCount(); i++)
	{
		printf("InfoBaseActions.Name = %s\n", XMLString::transcode(b.InfoBaseActions[i].Name.str));
		printf("InfoBaseActions.ID = %d\n", b.InfoBaseActions[i].ID);
		for(j = 0; i < b.InfoBaseActions[i].Descriptions.GetCount(); j++)
		{
			printf("InfoBaseActions[j].Descriptions.Description = %s\n", XMLString::transcode(b.InfoBaseActions[i].Descriptions[j].Description.str));
			printf("InfoBaseActions[j].Descriptions.Language = %s\n", XMLString::transcode(b.InfoBaseActions[i].Descriptions[j].Language.str));
		}
	}
*/


	
	
	
	
	
	
	
	
	
	//如果上一步读文件失败，就返回-1
	if(doc == LIDP_NULL)
		return -1;
	//获取文档的根结点
	DOMElement* root = doc->getDocumentElement();

	//获取ProviderID
	DOMNodeList* node_list = root->getElementsByTagName(XMLString::transcode("ProviderID"));
	if(node_list->getLength() != 1)
		return -1;

	//获取InfoBaseID
	node_list = root->getElementsByTagName(XMLString::transcode("InfoBaseID"));
	if(node_list->getLength() != 1)
		return -1;
	DOMNode* node = node_list->item(0)->getFirstChild();
	
	
	
	
	
	
	
	
	
	
	
	
	LIDP_String y;
	y = (XMLCh*)(node->getNodeValue());
printf("yyyyyyyyyyyyyyy.Name\n");
	LIDP_tagInfoBase g;
	LIDP_tagActionDefine* tag = new LIDP_tagActionDefine;
	LIDP_tagDescription* tag2 = new LIDP_tagDescription;
printf("InfoBaseActions.Name\n");
	tag2->Description = (XMLCh*)(node->getNodeValue());
printf("InfoBaseActions.Name\n");
	tag2->Language = (XMLCh*)(node->getNodeValue());
printf("size:%d\n", sizeof(LIDP_tagDescription));
	tag->Descriptions.Add(tag2);
	tag2 = new LIDP_tagDescription;
	tag2->Description = (XMLCh*)(node->getNodeValue());
	tag2->Language = (XMLCh*)(node->getNodeValue());
	tag->Descriptions.Add(tag2);
	g.InfoBaseActions.Add(tag);
	tag = new LIDP_tagActionDefine;
	tag->Descriptions.Add(tag2);
	g.InfoBaseActions.Add(tag);

	for(i = 0; i < g.InfoBaseActions.GetCount(); i++)
	{
printf("-------------- = %d\n", g.InfoBaseActions.GetCount());
//		printf("InfoBaseActions.Name = %s\n", XMLString::transcode(a.InfoBaseActions[i].Name.str));
//		printf("InfoBaseActions.ID = %d\n", a.InfoBaseActions[i].ID);
		for(j = 0; j < g.InfoBaseActions[i]->Descriptions.GetCount(); j++)
		{
			printf("InfoBaseActions[j]->Descriptions.Description = %s\n", XMLString::transcode(g.InfoBaseActions[i]->Descriptions[j]->Description.str));
printf("InfoBaseActions.11111111111\n");
			printf("InfoBaseActions[j]->Descriptions.Language = %s\n", XMLString::transcode(g.InfoBaseActions[i]->Descriptions[j]->Language.str));
		}
	}
	
	
	return 0;
}