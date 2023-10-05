/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     LIDP_Parser.h

  Author:        LiJia

  Version:       v1.0

  Date:          2003/07/01

  Description:   If the Parser of XML files(InfoBase XML file, Module Declare XML file).

  Others:

  Function List:

  History:
    1. Date:           2003/07/01
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
	//��ȡInfoItems In Module
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetInfoItemsInModule(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagInfoItemInModule, LIDP_tagInfoItemInModule*>& InfoItemList);
	//��ȡActions
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetActions(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagAction, LIDP_tagAction*>& Actions);
	//��ȡInfoItems
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetInfoItems(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagInfoItem, LIDP_tagInfoItem*>& InfoItems);
	//��ȡInfoBaseActions
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetInfoBaseActions(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagActionDefine, LIDP_tagActionDefine*>& InfoBaseActions);
	//��ȡInfoBaseDataTypes
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetInfoBaseDataTypes(DOMNode *node, LIDP_CArrayTemplate<LIDP_tagDataType, LIDP_tagDataType*>& InfoBaseDataTypes);
	//��ȡDescriptions
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetDescriptions(DOMNode* node, LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*>& Descriptions);
public:
	//��ȡModule
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetModuleDeclare(LIDP_CArrayTemplate<LIDP_tagModule, LIDP_tagModule*>& Modules, DOMDocument* doc);
	//��ȡInfoBase�ļ��е���Ϣ��tag��
	//�ɹ�ʱ����1��ʧ��ʱ����-1
	SMM_INT32 GetInfoBase(LIDP_tagInfoBase& tag, DOMDocument* doc);
	//��һ��XML�ļ������������DOMDocumentʵ���ľ��
	DOMDocument* OpenXmlFile(char* FileName);
	LIDP_Parser();
	virtual ~LIDP_Parser();

};

#endif // !defined(LIDP_PARSER_H__2153F2BB_6517_468A_BFA3_A21A0227E7FF__INCLUDED_)
