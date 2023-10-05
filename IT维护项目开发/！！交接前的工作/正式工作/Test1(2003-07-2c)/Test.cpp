#include <iostream.h>
#include <stdio.h>

#include "LIDP_Command_Dispatch_Process.h"
#include "LIDP_Parser.h"

int main(int argc, char* argv[])
{
	//测试数据块的整合与还原操作///////////////////////////////////////////////
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


	//测试LIDP_Parser中的GetInfoBase()///////////////////////////////////////////////
/*	int i, j;
	LIDP_Parser a;
	DOMDocument* doc = a.OpenXmlFile("TestInfoBase.xml");
	LIDP_tagInfoBase b;
	a.GetInfoBase(b, doc);
	printf("ProviderID = %d\n", b.ProviderID);
	printf("InfoBaseID = %d\n", b.InfoBaseID);
	printf("Name = %s\n", XMLString::transcode(b.Name.str));
	for(i = 0; i < b.Descriptions.GetCount(); i++)
	{
		printf("Descriptions[%d].Description = %s\n", i, XMLString::transcode(b.Descriptions[i]->Description.str));
		printf("Descriptions[%d].Language = %s\n", i, XMLString::transcode(b.Descriptions[i]->Language.str));
	}

	for(i = 0; i < b.InfoBaseDataTypes.GetCount(); i++)
	{
		printf("InfoBaseDataTypes[%d].Name = %s\n", i, XMLString::transcode(b.InfoBaseDataTypes[i]->Name.str));
		printf("InfoBaseDataTypes[%d].ID = %d\n", i, b.InfoBaseDataTypes[i]->ID);
	}
	
	for(i = 0; i < b.InfoBaseActions.GetCount(); i++)
	{
		printf("InfoBaseActions.Name = %s\n", XMLString::transcode(b.InfoBaseActions[i]->Name.str));
		printf("InfoBaseActions.ID = %d\n", b.InfoBaseActions[i]->ID);
		for(j = 0; j < b.InfoBaseActions[i]->Descriptions.GetCount(); j++)
		{
			printf("InfoBaseActions[%d]->Descriptions[%d].Description = %s\n", i, j, XMLString::transcode(b.InfoBaseActions[i]->Descriptions[j]->Description.str));
			printf("InfoBaseActions[%d]->Descriptions[%d].Language = %s\n", i, j, XMLString::transcode(b.InfoBaseActions[i]->Descriptions[j]->Language.str));
		}
	}

	for(i = 0; i < b.InfoItems.GetCount(); i++)
	{
		printf("InfoItems.Name = %s\n", XMLString::transcode(b.InfoItems[i]->Name.str));
		printf("InfoItems.ID = %d\n", b.InfoItems[i]->ID);
		printf("InfoItems.DataType = %d\n", b.InfoItems[i]->DataType);
		for(j = 0; j < b.InfoItems[i]->Descriptions.GetCount(); j++)
		{
			printf("InfoItems[%d]->Descriptions[%d].Description = %s\n", i, j, XMLString::transcode(b.InfoItems[i]->Descriptions[j]->Description.str));
			printf("InfoItems[%d]->Descriptions[%d].Language = %s\n", i, j, XMLString::transcode(b.InfoItems[i]->Descriptions[j]->Language.str));
		}
	}

	printf("%d\n", b.InfoItems[0]->SubTree[0]->Actions[0]->Parameters[1]->ID);
*/


	//测试LIDP_Parser中的GetModuleDeclare()///////////////////////////////////////////////
	LIDP_Parser a;
	DOMDocument* doc = a.OpenXmlFile("TestModuleDeclare2.xml");
	LIDP_CArrayTemplate<LIDP_tagModule, LIDP_tagModule*> Modules;
	a.GetModuleDeclare(Modules, doc);

	printf("%d\n", Modules[0]->InfoItemList[0]->Parameters[1]->ID);

	return 0;
}