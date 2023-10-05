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
//整合：
//整合内存空间函数，以生成供传输用的数据块 
//在内存空间中，将分散分布的实体合并到一块内存空间中，以方便传输
//将所有指针中存储的物理地址转换为相对偏移量
//偏移量以LIDP_tagTransfer的结束位置为基址
//
//还原：
//不必开辟新的存储空间，只要将其中的指针中存储的偏移量改为本地的物理地址即可
////////////////////////////////////////////////////////////////////////////////////

//整合LIDP_tagInstruction
LIDP_tagTransfer* LIDP_Command_Dispatch_Process::LIDP_Make_tagTransfer_From_tagInstruction(LIDP_tagInstruction& tag)
{
	SMM_INT32 offset = 0;
	//分配完整的空间，此空间大小足够装入结构体所包含的所有数据
	LIDP_tagTransfer* result = (LIDP_tagTransfer*)malloc(LIDP_sizeof_tagInstruction(tag) + sizeof(LIDP_tagTransfer));
	if(result == 0)
		return LIDP_NULL;

	//设置传输结构
	result->TransferType = TRANSFER_INSTRUCTION;
	result->Size = LIDP_sizeof_tagInstruction(tag);

	//找到传输结构的后续空间，用于存入LIDP_tagInstruction
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
			//在指针中存入偏移量
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
		//暂无数据，不用处理
		break;
	default:
		delete result;
 		return LIDP_NULL;
	}

	return result;
}

//还原LIDP_tagInstruction
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
		//暂无数据，不用处理
		break;
	default:
 		return LIDP_NULL;
	}


	return result;
}

//整合LIDP_tagDriverReturnBlock
LIDP_tagTransfer* LIDP_Command_Dispatch_Process::LIDP_Make_tagTransfer_From_tagDriverReturnBlock(LIDP_tagDriverReturnBlock& tag)
{
	SMM_INT32 offset = 0;
	//分配完整的空间，此空间大小足够装入结构体所包含的所有数据
	LIDP_tagTransfer* result = (LIDP_tagTransfer*)malloc(LIDP_sizeof_tagDriverReturnBlock(tag) + sizeof(LIDP_tagTransfer));
	if(result == 0)
		return LIDP_NULL;

	//设置传输结构
	result->TransferType = TRANSFER_DRIVERREUTRNBLOCK;
	result->Size = LIDP_sizeof_tagDriverReturnBlock(tag);

	//找到传输结构的后续空间，用于存入LIDP_tagDriverReturnBlock
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
		//在指针中存入偏移量
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


//还原LIDP_tagDriverReturnBlock
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



//供LIDP_tagLanguageList和LIDP_tagVariantParameterList等拥有List指针列表和NumOfList计数器的结构体使用
//开辟新空间，并将新空间的指针加入到指针数组中
//pstContainerStruct为包含List的结构体的指针类型
//InsertStruct为List中存储的指针所指向的实体类型
//pstInsertStruct为List中存储的指针类型
template <typename pstContainerStruct, typename InsertStruct, typename pstInsertStruct>
//tag，传人包含List的结构体的实例（用指针类型传人）
//tag4Insert，用于确定要开辟的空间的类型（结构体类型，不要用指针），无其它用途
//psttag4Insert，用于确定要开辟的空间的指针类型
//在函数返回后，新开辟的空间只能用tag->List[i]->...的方法访问
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_Make_List(pstContainerStruct tag, InsertStruct tag4Insert, pstInsertStruct psttag4Insert)
{
	//若StructList还没有空间时
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

//计算LIDP_tagVariant实体的大小
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagVariant(LIDP_tagVariant& tag)
{
	return sizeof(LIDP_tagVariant) + tag.Length;
}

//计算LIDP_tagVariantParameterList实体的大小
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagVariantParameterList(LIDP_tagVariantParameterList& tag)
{
	int size = 0;
	for(int i = 0; i < tag.NumOfList; i++)
		size += LIDP_sizeof_tagVariant(*tag.List[i]);
	return sizeof(LIDP_tagVariantParameterList) + size;
}

//计算LIDP_tagDriverCommand实体的大小
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagDriverCommand(LIDP_tagDriverCommand& tag)
{
	return sizeof(LIDP_tagDriverCommand) + LIDP_sizeof_tagVariantParameterList(tag.ParameterList) + sizeof(SMM_INT32) * tag.NumOfInfoItemID;
}

//计算LIDP_tagDriverReturnBlock实体的大小
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagDriverReturnBlock(LIDP_tagDriverReturnBlock& tag)
{
	return sizeof(LIDP_tagDriverReturnBlock) + LIDP_sizeof_tagVariantParameterList(tag.ParameterList) + sizeof(SMM_INT32) * tag.NumOfInfoItemID;
}

//计算LIDP_tagManagementCommand实体的大小
SMM_INT32 LIDP_Command_Dispatch_Process::LIDP_sizeof_tagManagementCommand(LIDP_tagManagementCommand& tag)
{
	return sizeof(LIDP_tagManagementCommand);
}

//计算LIDP_tagInstruction实体的大小
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

//复制数据空间，按字节
//mem1，目的地址；mem2，源地址；count，要复制的字节数 
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
