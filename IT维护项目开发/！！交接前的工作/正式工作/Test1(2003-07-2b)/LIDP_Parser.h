/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     LIDP_Command_Dispatch_Process.h

  Author:        LiJia

  Version:       v1.0

  Date:          2003/06/28

  Description:   Deal with time in char

  Others:

  Function List:

  History:
    1. Date:           2003/06/28
       Author:         LiJia
       Modification:   First Created

 *****************************************************************************/



// LIDP_Parser.h: interface for the LIDP_Parser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LIDP_PARSER_H__2153F2BB_6517_468A_BFA3_A21A0227E7FF__INCLUDED_)
#define LIDP_PARSER_H__2153F2BB_6517_468A_BFA3_A21A0227E7FF__INCLUDED_

#include "LIDP_TypeDefinition.h"


class LIDP_Parser
{
protected:
	//获取Descriptions
	//成功时返回1，失败时返回-1
	SMM_INT32 GetInfoBaseActions(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagActionDefine, LIDP_tagActionDefine*>& InfoBaseActions);
	//获取Descriptions
	//成功时返回1，失败时返回-1
	SMM_INT32 GetInfoBaseDataTypes(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagDataType, LIDP_tagDataType*>& InfoBaseDataTypes);
	//获取Descriptions
	//成功时返回1，失败时返回-1
	SMM_INT32 GetDescriptions(DOMNode* node, LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*>& Descriptions);
public:
	//获取InfoBase文件中的信息到tag中
	//成功时返回1，失败时返回-1
	SMM_INT32 GetInfoBase(LIDP_tagInfoBase& tag, DOMDocument* doc);
	//打开一个XML文件，并返回其的DOMDocument实例的句柄
	DOMDocument* OpenXmlFile(char* FileName);
	LIDP_Parser();
	virtual ~LIDP_Parser();

};

#endif // !defined(LIDP_PARSER_H__2153F2BB_6517_468A_BFA3_A21A0227E7FF__INCLUDED_)
