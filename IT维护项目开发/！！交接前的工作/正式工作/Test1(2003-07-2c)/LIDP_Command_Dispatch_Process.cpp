// LIDP_Command_Dispatch_Process.cpp: implementation of the LIDP_Command_Dispatch_Process class.
//
//////////////////////////////////////////////////////////////////////

#include "LIDP_Command_Dispatch_Process.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LIDP_Command_Dispatch_Process::LIDP_Command_Dispatch_Process()
{

}

LIDP_Command_Dispatch_Process::~LIDP_Command_Dispatch_Process()
{

}



////////////////////////////////////////////////////////////////////////////////////
//���ϣ�
//�����ڴ�ռ亯���������ɹ������õ����ݿ� 
//���ڴ�ռ��У�����ɢ�ֲ���ʵ��ϲ���һ���ڴ�ռ��У��Է��㴫��
//������ָ���д洢�������ַת��Ϊ���ƫ����
//ƫ������LIDP_tagTransfer�Ľ���λ��Ϊ��ַ
//
//��ԭ��
//���ؿ����µĴ洢�ռ䣬ֻҪ�����е�ָ���д洢��ƫ������Ϊ���ص������ַ����
////////////////////////////////////////////////////////////////////////////////////

//����LIDP_tagInstruction
LIDP_tagTransfer* LIDP_Command_Dispatch_Process::LIDP_Make_tagTransfer_From_tagInstruction(LIDP_tagInstruction& tag)
{
	SMM_INT32 offset = 0;
	//���������Ŀռ䣬�˿ռ��С�㹻װ��ṹ������������������
	LIDP_tagTransfer* result = (LIDP_tagTransfer*)malloc(LIDP_sizeof_tagInstruction(tag) + sizeof(LIDP_tagTransfer));
	if(result == 0)
		return LIDP_NULL;

	//���ô���ṹ
	result->TransferType = TRANSFER_INSTRUCTION;
	result->Size = LIDP_sizeof_tagInstruction(tag);

	//�ҵ�����ṹ�ĺ����ռ䣬���ڴ���LIDP_tagInstruction
	LIDP_tagInstruction* temp = (LIDP_tagInstruction*)(((SMM_UCHAR*)result) + sizeof(LIDP_tagTransfer));
	LIDP_MemoryCopy((SMM_UCHAR*)temp, (SMM_UCHAR*)&tag, sizeof(LIDP_tagInstruction));
	offset += sizeof(LIDP_tagInstruction);

	LIDP_tagVariant* temp_v;
	SMM_INT32 i;
	switch(tag.InstructionID)
	{
	case COMMAND_DRIVER:
		temp->driverCommand.InfoItemID = (SMM_INT32*)offset;
		LIDP_MemoryCopy((((SMM_UCHAR*)temp) + offset), 
			(SMM_UCHAR*)(tag.driverCommand.InfoItemID), 
			sizeof(SMM_INT32) * temp->driverCommand.NumOfInfoItemID);
		offset += sizeof(SMM_INT32) * temp->driverCommand.NumOfInfoItemID;

		temp->driverCommand.ParameterList.List = (LIDP_tagVariant**)offset;
		offset += sizeof(LIDP_tagVariant*) * tag.driverCommand.ParameterList.NumOfList;
		for(i = 0; i < temp->driverCommand.ParameterList.NumOfList; i++)
		{
			//��ָ���д���ƫ����
			((LIDP_tagVariant**)((SMM_UCHAR*)temp + (int)(temp->driverCommand.ParameterList.List)))[i] = (LIDP_tagVariant*)offset;
			LIDP_MemoryCopy((((SMM_UCHAR*)temp) + offset), 
				(SMM_UCHAR*)(tag.driverCommand.ParameterList.List[i]), 
				sizeof(LIDP_tagVariant));
			temp_v = (LIDP_tagVariant*)(((SMM_UCHAR*)temp) + offset);
			offset += sizeof(LIDP_tagVariant);
			temp_v->Buff = (SMM_UCHAR*)offset;
			LIDP_MemoryCopy((((SMM_UCHAR*)temp) + offset), 
				(tag.driverCommand.ParameterList.List[i])->Buff, 
				(tag.driverCommand.ParameterList.List[i])->Length);
			offset += (tag.driverCommand.ParameterList.List[i])->Length;
		}
		break;
	case COMMAND_MANAGEMENT:
		//�������ݣ����ô���
		break;
	default:
		delete result;
 		return LIDP_NULL;
	}

	return result;
}

//��ԭLIDP_tagInstruction
LIDP_tagInstruction* LIDP_Command_Dispatch_Process::LIDP_Revert_tagInstruction_From_tagTransfer(LIDP_tagTransfer& tag)
{
	if(tag.TransferType != TRANSFER_INSTRUCTION)
		return LIDP_NULL;

	LIDP_tagInstruction* result = (LIDP_tagInstruction*)((SMM_UCHAR*)(&tag) + sizeof(LIDP_tagTransfer));

	SMM_INT32 i;
	switch(result->InstructionID)
	{
	case COMMAND_DRIVER:
		result->driverCommand.InfoItemID = 
			(SMM_INT32*)((SMM_UCHAR*)result 
			+ (int)(result->driverCommand.InfoItemID));

		result->driverCommand.ParameterList.List = 
			(LIDP_tagVariant**)((SMM_UCHAR*)result 
			+ (int)(result->driverCommand.ParameterList.List));
		for(i = 0; i < result->driverCommand.ParameterList.NumOfList; i++)
		{
			result->driverCommand.ParameterList.List[i] = 
				(LIDP_tagVariant*)((SMM_UCHAR*)result 
				+ (int)(result->driverCommand.ParameterList.List[i]));

			result->driverCommand.ParameterList.List[i]->Buff = 
				(SMM_UCHAR*)((SMM_UCHAR*)result 
				+ (int)(result->driverCommand.ParameterList.List[i]->Buff));
		}
		break;
	case COMMAND_MANAGEMENT:
		//�������ݣ����ô���
		break;
	default:
 		return LIDP_NULL;
	}


	return result;
}

//����LIDP_tagDriverReturnBlock
LIDP_tagTransfer* LIDP_Command_Dispatch_Process::LIDP_Make_tagTransfer_From_tagDriverReturnBlock(LIDP_tagDriverReturnBlock& tag)
{
	SMM_INT32 offset = 0;
	//���������Ŀռ䣬�˿ռ��С�㹻װ��ṹ������������������
	LIDP_tagTransfer* result = (LIDP_tagTransfer*)malloc(LIDP_sizeof_tagDriverReturnBlock(tag) + sizeof(LIDP_tagTransfer));
	if(result == 0)
		return LIDP_NULL;

	//���ô���ṹ
	result->TransferType = TRANSFER_DRIVERREUTRNBLOCK;
	result->Size = LIDP_sizeof_tagDriverReturnBlock(tag);

	//�ҵ�����ṹ�ĺ����ռ䣬���ڴ���LIDP_tagDriverReturnBlock
	LIDP_tagDriverReturnBlock* temp = (LIDP_tagDriverReturnBlock*)(((SMM_UCHAR*)result) + sizeof(LIDP_tagTransfer));
	LIDP_MemoryCopy((SMM_UCHAR*)temp, (SMM_UCHAR*)&tag, sizeof(LIDP_tagDriverReturnBlock));
	offset += sizeof(LIDP_tagDriverReturnBlock);

	LIDP_tagVariant* temp_v;
	SMM_INT32 i;

	
	temp->InfoItemID = (SMM_INT32*)offset;
	LIDP_MemoryCopy((((SMM_UCHAR*)temp) + offset), 
		(SMM_UCHAR*)(tag.InfoItemID), 
		sizeof(SMM_INT32) * temp->NumOfInfoItemID);
	offset += sizeof(SMM_INT32) * temp->NumOfInfoItemID;

	temp->ParameterList.List = (LIDP_tagVariant**)offset;
	offset += sizeof(LIDP_tagVariant*) * tag.ParameterList.NumOfList;
	for(i = 0; i < temp->ParameterList.NumOfList; i++)
	{
		//��ָ���д���ƫ����
		((LIDP_tagVariant**)((SMM_UCHAR*)temp + (int)(temp->ParameterList.List)))[i] = (LIDP_tagVariant*)offset;
		LIDP_MemoryCopy((((SMM_UCHAR*)temp) + offset), 
			(SMM_UCHAR*)(tag.ParameterList.List[i]), 
			sizeof(LIDP_tagVariant));
		temp_v = (LIDP_tagVariant*)(((SMM_UCHAR*)temp) + offset);
		offset += sizeof(LIDP_tagVariant);
		temp_v->Buff = (SMM_UCHAR*)offset;
		LIDP_MemoryCopy((((SMM_UCHAR*)temp) + offset), 
			(tag.ParameterList.List[i])->Buff, 
			(tag.ParameterList.List[i])->Length);
		offset += (tag.ParameterList.List[i])->Length;
	}

	return result;
}


//��ԭLIDP_tagDriverReturnBlock
LIDP_tagDriverReturnBlock* LIDP_Command_Dispatch_Process::LIDP_Revert_tagDriverReturnBlock_From_tagTransfer(LIDP_tagTransfer& tag)
{
	if(tag.TransferType != TRANSFER_DRIVERREUTRNBLOCK)
		return LIDP_NULL;

	LIDP_tagDriverReturnBlock* result = (LIDP_tagDriverReturnBlock*)((SMM_UCHAR*)(&tag) + sizeof(LIDP_tagTransfer));

	result->InfoItemID = 
		(SMM_INT32*)((SMM_UCHAR*)result 
		+ (int)(result->InfoItemID));

	SMM_INT32 i;
	result->ParameterList.List = 
		(LIDP_tagVariant**)((SMM_UCHAR*)result 
		+ (int)(result->ParameterList.List));
	for(i = 0; i < result->ParameterList.NumOfList; i++)
	{
		result->ParameterList.List[i] = 
			(LIDP_tagVariant*)((SMM_UCHAR*)result 
			+ (int)(result->ParameterList.List[i]));

		result->ParameterList.List[i]->Buff = 
			(SMM_UCHAR*)((SMM_UCHAR*)result 
			+ (int)(result->ParameterList.List[i]->Buff));
	}

	return result;
}



//��LIDP_tagLanguageList��LIDP_tagVariantParameterList��ӵ��Listָ���б��NumOfList�������Ľṹ��ʹ��
//�����¿ռ䣬�����¿ռ��ָ����뵽ָ��������
//pstContainerStructΪ����List�Ľṹ���ָ������
//InsertStructΪList�д洢��ָ����ָ���ʵ������
//pstInsertStructΪList�д洢��ָ������
template <typename pstContainerStruct, typename InsertStruct, typename pstInsertStruct>
//tag�����˰���List�Ľṹ���ʵ������ָ�����ʹ��ˣ�
//tag4Insert������ȷ��Ҫ���ٵĿռ�����ͣ��ṹ�����ͣ���Ҫ��ָ�룩����������;
//psttag4Insert������ȷ��Ҫ���ٵĿռ��ָ������
//�ں������غ��¿��ٵĿռ�ֻ����tag->List[i]->...�ķ�������
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_Make_List(pstContainerStruct tag, InsertStruct tag4Insert, pstInsertStruct psttag4Insert)
{
	//��StructList��û�пռ�ʱ
	if(tag->NumOfList == 0)
	{
		tag->List = malloc(sizeof(pstInsertStruct));
	}
	else
	{
		tag->List = realloc(tag->List, sizeof(pstInsertStruct) * (tag->List + 1));
	}
	pstInsertStruct pstNewStruct = malloc(sizeof(InsertStruct));
	tag->List[tag->NumOfList] = pstNewStruct;
	tag->NumOfList++;
	return LIDP_OK;
}

//����LIDP_tagVariantʵ��Ĵ�С
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagVariant(LIDP_tagVariant& tag)
{
	return sizeof(LIDP_tagVariant) + tag.Length;
}

//����LIDP_tagVariantParameterListʵ��Ĵ�С
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagVariantParameterList(LIDP_tagVariantParameterList& tag)
{
	int size = 0;
	for(int i = 0; i < tag.NumOfList; i++)
		size += LIDP_sizeof_tagVariant(*tag.List[i]);
	return sizeof(LIDP_tagVariantParameterList) + size;
}

//����LIDP_tagDriverCommandʵ��Ĵ�С
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagDriverCommand(LIDP_tagDriverCommand& tag)
{
	return sizeof(LIDP_tagDriverCommand) + LIDP_sizeof_tagVariantParameterList(tag.ParameterList) + sizeof(SMM_INT32) * tag.NumOfInfoItemID;
}

//����LIDP_tagDriverReturnBlockʵ��Ĵ�С
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagDriverReturnBlock(LIDP_tagDriverReturnBlock& tag)
{
	return sizeof(LIDP_tagDriverReturnBlock) + LIDP_sizeof_tagVariantParameterList(tag.ParameterList) + sizeof(SMM_INT32) * tag.NumOfInfoItemID;
}

//����LIDP_tagManagementCommandʵ��Ĵ�С
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagManagementCommand(LIDP_tagManagementCommand& tag)
{
	return sizeof(LIDP_tagManagementCommand);
}

//����LIDP_tagInstructionʵ��Ĵ�С
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagInstruction(LIDP_tagInstruction& tag)
{
	SMM_INT32 union_size = 0;
	if(tag.InstructionID == COMMAND_DRIVER)
		union_size += LIDP_sizeof_tagDriverCommand(tag.driverCommand);
	else if(tag.InstructionID == COMMAND_MANAGEMENT)
		union_size += LIDP_sizeof_tagManagementCommand(tag.managementCommand);
	else
 		return LIDP_ERR;
	tag.szParameter = union_size;
	return sizeof(LIDP_tagInstruction) + tag.szParameter;
}

//�������ݿռ䣬���ֽ�
//mem1��Ŀ�ĵ�ַ��mem2��Դ��ַ��count��Ҫ���Ƶ��ֽ��� 
SMM_VOID LIDP_Command_Dispatch_Process::LIDP_MemoryCopy(SMM_UCHAR* mem1, SMM_UCHAR* mem2, SMM_INT32 count)
{
	for(int i = 0; i < count; i++)
		mem1[i] = mem2[i];
}


void LIDP_Command_Dispatch_Process::LIDP_Free_tagVariant(LIDP_tagVariant* tag)
{
	free(tag->Buff);
}

void LIDP_Command_Dispatch_Process::LIDP_Free_tagVariantParameterList(LIDP_tagVariantParameterList* tag)
{
	for(int i = 0; i < tag->NumOfList; i++)
	{
		LIDP_Free_tagVariant(tag->List[i]);
		free(tag->List[i]);
	}
	free(tag->List);
}

void LIDP_Command_Dispatch_Process::LIDP_Free_tagDriverCommand(LIDP_tagDriverCommand* tag)
{
	free(tag->InfoItemID);
	LIDP_Free_tagVariantParameterList(&(tag->ParameterList));
}

void LIDP_Command_Dispatch_Process::LIDP_Free_tagDriverReturnBlock(LIDP_tagDriverReturnBlock* tag)
{
	free(tag->InfoItemID);
	LIDP_Free_tagVariantParameterList(&(tag->ParameterList));
}


void LIDP_Command_Dispatch_Process::LIDP_Free_tagInstruction(LIDP_tagInstruction* tag)
{
	LIDP_Free_tagDriverCommand(&(tag->driverCommand));
}
