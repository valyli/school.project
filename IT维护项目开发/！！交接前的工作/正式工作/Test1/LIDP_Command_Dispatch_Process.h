/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     LIDP_Command_Dispatch_Process.h

  Author:        LiJia

  Version:       v1.0

  Date:          2003/06/28

  Description:   Dispatch Command String to struct

  Others:

  Function List:

  History:
    1. Date:           2003/06/28
       Author:         LiJia
       Modification:   First Created

 *****************************************************************************/



// LIDP_Command_Dispatch_Process.h: interface for the LIDP_Command_Dispatch_Process class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LIDP_COMMAND_DISPATCH_PROCESS_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_)
#define LIDP_COMMAND_DISPATCH_PROCESS_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_

#include "LIDP_TypeDefinition.h"


class LIDP_Command_Dispatch_Process  
{
public:
	LIDP_Command_Dispatch_Process();
	virtual ~LIDP_Command_Dispatch_Process();

	LIDP_tagTransfer* LIDP_Make_tagTransfer_From_tagInstruction(LIDP_tagInstruction& tag);
	LIDP_tagInstruction* LIDP_Revert_tagInstruction_From_tagTransfer(LIDP_tagTransfer& tag);
	LIDP_tagTransfer* LIDP_Make_tagTransfer_From_tagDriverReturnBlock(LIDP_tagDriverReturnBlock& tag);
	LIDP_tagDriverReturnBlock* LIDP_Revert_tagDriverReturnBlock_From_tagTransfer(LIDP_tagTransfer& tag);
	template <typename pstContainerStruct, typename InsertStruct, typename pstInsertStruct>
	SMM_INT32 LIDP_Make_List(pstContainerStruct tag, InsertStruct tag4Insert, pstInsertStruct psttag4Insert);
	SMM_INT32 LIDP_sizeof_tagVariant(LIDP_tagVariant& tag);
	SMM_INT32 LIDP_sizeof_tagVariantParameterList(LIDP_tagVariantParameterList& tag);
	SMM_INT32 LIDP_sizeof_tagDriverCommand(LIDP_tagDriverCommand& tag);
	SMM_INT32 LIDP_sizeof_tagDriverReturnBlock(LIDP_tagDriverReturnBlock& tag);
	SMM_INT32 LIDP_sizeof_tagManagementCommand(LIDP_tagManagementCommand& tag);
	SMM_INT32 LIDP_sizeof_tagInstruction(LIDP_tagInstruction& tag);
	SMM_VOID LIDP_MemoryCopy(SMM_UCHAR* mem1, SMM_UCHAR* mem2, SMM_INT32 count);
	//以下Free函数用于释放分配的内存空间
	//注意：只能释放整合前的数据块，整合后的和还原后的数据块只能用free函数释放LIDP_tagTransfer整块
	//因为后两种数据块在空间上是连续的
	void LIDP_Free_tagVariant(LIDP_tagVariant* tag);
	void LIDP_Free_tagVariantParameterList(LIDP_tagVariantParameterList* tag);
	void LIDP_Free_tagDriverCommand(LIDP_tagDriverCommand* tag);
	void LIDP_Free_tagDriverReturnBlock(LIDP_tagDriverReturnBlock* tag);
	void LIDP_Free_tagInstruction(LIDP_tagInstruction* tag);
};

#endif // !defined(LIDP_COMMAND_DISPATCH_PROCESS_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_)
