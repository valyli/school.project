/*************************************************************
  Copyright (C)
  File name:  
  Author: 
  Version:  
  Date: 2003-3-28
  Description:    ���ļ��Ƕ��̼߳�ͨ�ŵĻ�����Ƶķ�װ�ӿ�
  Others:           
  Function List:  
  (1)ITDQ_int
  (2)IDDQ_CreateQueue
  (3)ITDQ_Read
  (4)ITDQ_Write
  (5)ITDQ_Delete
  History:          
    1. Date:
       Author:
       Modification:
    2. ...
**************************************************************/
#ifndef __TEST_H__
#define __TEST_H__

#include "smm_type.h"


#include "stdio.h"
//#include "Windows.h"
#define Data_Size			256					//���г���
#define ITDQ_BLOCK_YES       1					//����ģʽ
typedef   struct   tagSMM_node
	{
		SMM_CHAR	  cData[Data_Size];			//��������	
		tagSMM_node   *pNext;					//ָ����
	}SMM_node; 
typedef   struct  tagSMM_Queue_Info
	{
		SMM_INT	    iID;						//����ID
		SMM_INT		iSize;						
		SMM_INT		iMode;						//�ж������������
		tagSMM_node * pFront;					
		tagSMM_node * pRear;
		tagSMM_Queue_Info* pNext;
		CRITICAL_SECTION   cs;					//�ٽ�������
		HANDLE		hSemRead;
		HANDLE      hSemWrite;
		BOOL		bFlags;
	}SMM_Queue_Info;
tagSMM_Queue_Info pQueue_Info;					//���������ͷ�ڵ�
/*********************************************************
  Function:       ITDQ_Init
  Description:    ��ʼ��ͷ�ڵ�
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          	


  Output:         
  Return:         �ɹ�����TRUE
				  ʧ�ܷ���FALSE

  Others:        
***********************************************************/
void ITDQ_Init()				
{
		pQueue_Info.iID=0;
		pQueue_Info.iSize=NULL;
		pQueue_Info.pFront=NULL;
		pQueue_Info.pRear=NULL;
		pQueue_Info.iMode=0;
		pQueue_Info.pNext=NULL;
		InitializeCriticalSection(&pQueue_Info.cs);
}
/*********************************************************
  Function:       CreateQueue
  Description:    ��������
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          	iMaxLen: �������������ݶ��е���󳤶�
	
					p:���нڵ�ָ��


  Output:         
  Return:         �ɹ�����Ψһ��ʶ�ö��е�ID��,��һ���Ǹ�����.
				  ʧ�ܷ���-1��ʾ����ʧ��

  Others:        
***********************************************************/
SMM_BOOL ITDQ_CreateQueue(SMM_UINT uiMaxLen, tagSMM_node* & p)			//�������к���
{
	if(uiMaxLen <= 0)
	{
		return FALSE;
	}
	tagSMM_node *p1, *p2;
	p=(tagSMM_node*)malloc(sizeof(tagSMM_node));
	p1 = p;
	for(int i = 0; i < uiMaxLen-1; i++)
	{
		p2 = (tagSMM_node*)malloc(sizeof(tagSMM_node));		/*�����û�����Ķ��д�
															Сѭ�������ַ�ռ�*/														
		p1->pNext = p2;
		p1 = p2;
	}
	p1->pNext = p;											//ʹָ��ָ��ͷԪ��
	return TRUE;
	
}
/*********************************************************
  Function:       ITDO_Create
  Description:    ��ʼ����
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          
                  iMode:����һ�������ͨ�ŵ����ݶ���ģʽ(����/������)

				  iMaxLen: �������������ݶ��е���󳤶�
  Output:         
  Return:         �ɹ�����Ψһ��ʶ�ö��е�ID��,��һ���Ǹ�����.
				  ʧ�ܷ���-1��ʾ����ʧ��
  Others:        
***********************************************************/
SMM_INT ITDQ_Create(SMM_INT iMode,SMM_UINT uiMaxLen=256)	
{
	SMM_INT ID;	
	tagSMM_node* p_Node = 0;
	tagSMM_Queue_Info* p_Info = &pQueue_Info;					//ʹָ��p_Infoָ��ڵ�
	EnterCriticalSection(&pQueue_Info.cs);
	if(FALSE == ITDQ_CreateQueue(uiMaxLen, p_Node))
	{
		printf("Create queue error\n");
	}
	p_Info->hSemWrite=CreateSemaphore(NULL,256,256,"write");	//����д�ź���			
	p_Info->hSemRead=CreateSemaphore(NULL,0,256,"read");		//�������ź���
	p_Info->bFlags=TRUE;										//��ʼ�����пձ��
	while(p_Info->pNext != NULL)
	{
		p_Info = p_Info->pNext;									//ָ�����,�ҵ��������ڵ�
	}
	ID = p_Info->iID;
	ID = ID + 1;
	p_Info->pNext = (tagSMM_Queue_Info*)malloc(sizeof(tagSMM_Queue_Info));
	p_Info = p_Info->pNext;
	p_Info->iID = ID;
	p_Info->iSize = uiMaxLen;
	p_Info->pFront = p_Node;
	p_Info->pRear = p_Node;
	p_Info->iMode = iMode;
	pQueue_Info.iID = pQueue_Info.iID + 1;
	p_Info->pRear = p_Info->pFront;
	InitializeCriticalSection(&p_Info->cs);	
	p_Info->pNext = NULL;
	LeaveCriticalSection(&pQueue_Info.cs);
	return p_Info->iID;
}

/*********************************************************
  Function:       ITDQ_Read
  Description:    �������ͨ�ŵ����ݶ��ж����������ݿ�
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          	
	
				iId :	�������ݶ��е�ID�ţ���ITDQ_Create����ʱ�õ�

				pData[][Data_Size] :Ҫ��ȡ�����ݿ�ָ�뻺����

				
  Output:         
  Return:        ʵ�ʶ�ȡ�����ݿ���Ŀ 

  Others:       0:	��ʾ���п�
			  ��1:  ��ʾû�������ID��Ӧ�����ݶ���
			   -4:  ��ʾ����Ϊ��
			  bFlags=TRUE:	����Ϊ��
			  bFlags=FALSE: ������
			  Ĭ��һ��ֻдһ�����ݿ�
			
***********************************************************/
SMM_INT ITDQ_Read( SMM_INT iId, SMM_CHAR *pData)
{	
	tagSMM_Queue_Info *p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	int i;
	int j;
	while(p_Info != NULL)
	{
		p_Info = p_Info->pNext;									//ѭ��������������Ϣ���ж�Ӧ��ID������
		if(p_Info->iID == iId)
			break;
	}
	if(p_Info->iMode == ITDQ_BLOCK_YES)							//ͬ����д����
	{
		WaitForSingleObject(p_Info->hSemRead,INFINITE);
		EnterCriticalSection(&p_Info->cs);
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			for(i = 0;i < 1; i++)								//��ʼ��ȡ	
			{
				for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
					*(pData+sizeof(char)*j*(1+i))= p_Info->pFront->cData[j];
				p_Info->pFront = p_Info->pFront->pNext;			
			}
			LeaveCriticalSection(&p_Info->cs);
			ReleaseSemaphore(p_Info->hSemRead,1,NULL);
			return i;
		}
		else
		{
			return -1;
		}		
	}
	else
	{
		EnterCriticalSection(&p_Info->cs);
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			for(i = 0;i < 1;i ++)										//��ʼ��ȡ	
			{
				if(p_Info->pFront == p_Info->pRear)
				{
					
					if(p_Info->bFlags == TRUE)							//����Ϊ��
					{
						return -4;
					}
					else
					{
						p_Info->bFlags=FALSE;
					}
				}
				for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
					*(pData+sizeof(char)*j*(1+i)) = p_Info->pFront->cData[j];
				p_Info->pFront = p_Info->pFront->pNext;
			}
			LeaveCriticalSection(&p_Info->cs);
			return i;
		}
		else
		{
			LeaveCriticalSection(&p_Info->cs);
			return -1;
		}
	}
	
}
/*********************************************************
  Function:       ITDQ_Write
  Description:    �������ͨ�ŵ����ݶ���д���������ݿ�
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          	
	
				iId :	�������ݶ��е�ID�ţ���ITDQ_Create����ʱ�õ�

				pData[][Data_Size] :Ҫд������ݿ�ָ�뻺����

				
  Output:         
  Return:        ʵ��д������ݿ���Ŀ 

  Others:       0:	��ʾ���п�
			  ��1:  ��ʾû�������ID��Ӧ�����ݶ���
			  -3:   ��ʾ������
			  bFlags=TRUE:	����Ϊ��
			  bFlags=FALSE: ������
			  Ĭ��һ��ֻдһ�����ݿ�
  			
***********************************************************/
SMM_INT ITDQ_Write(SMM_INT iId, SMM_CHAR *pData)
{
	tagSMM_Queue_Info *p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	int i=1;
	int j;
	while(p_Info != NULL)
	{
		p_Info = p_Info->pNext;									//ѭ��������������Ϣ���ж�Ӧ��ID������
		if(p_Info->iID == iId)
			break;
	}
	if(p_Info->iMode == ITDQ_BLOCK_YES)							//ͬ����д����
	{
		WaitForSingleObject(p_Info->hSemRead,INFINITE);
		EnterCriticalSection(&p_Info->cs);
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			for(i = 0;i < 1;i++)								//��ʼд��	
			{	
				for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
				{
					p_Info->pRear->cData[j] = *(pData+sizeof(char)*j*(1+i));
				}
				p_Info->pRear = p_Info->pRear->pNext;
			}
			LeaveCriticalSection(&p_Info->cs);
			ReleaseSemaphore(p_Info->hSemRead,1,NULL);
			return i;
		}
		else
		{
			return -1;
		}		
	}
	else
	{
		EnterCriticalSection(&p_Info->cs);
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			for(i = 0;i < 1;i++)								//��ʼд��	
			{
				if(p_Info->pFront == p_Info->pRear)
				{
					
					if(p_Info->bFlags==FALSE)							//���λ����Ϊ���˳�
					{
						return -3;
					}
					else
					{
						p_Info->bFlags=TRUE;
					}
				}
				for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
				{
					p_Info->pRear->cData[j] = *(pData+sizeof(char)*j*(1+i));
				}
				p_Info->pRear = p_Info->pRear->pNext;
			}
			LeaveCriticalSection(&p_Info->cs);
			return i;
		}
		else
		{
			LeaveCriticalSection(&p_Info->cs);
			return -1;
		}
	}
}
/*********************************************************
  Function:       ITDQ_Delete
  Description:    ɾ��һ�������ͨ�ŵ����ݶ���
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          	
	
				iId :	�������ݶ��е�ID�ţ���ITDQ_Create����ʱ�õ�
                               
  Output:         
  Return:        

  Others:      
		
***********************************************************/
SMM_VOID ITDQ_Delete(SMM_INT iId)
{
	tagSMM_Queue_Info *p_Info_temp ,*p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	EnterCriticalSection(&pQueue_Info.cs);
	while(p_Info != NULL)
	{
		if(p_Info->iID==iId)
			break;
		p_Info_temp = p_Info;
		p_Info = p_Info->pNext;									//ѭ��������������Ϣ���ж�Ӧ��ID������
	}
	if(p_Info != NULL)
	{
		p_Node = p_Info->pFront;								//�ҵ�ѭ�������е��κ�һ��,���еĶ��н���������ͨ������ָ��������			
		p_Node = p_Node->pNext;									//ָ����������
		p_Info->pFront->pNext = NULL;							//��ѭ�����жϿ�	
		while(p_Node != NULL)
		{
			p_Info->pRear = p_Node->pNext;			
			free(p_Node);										//�ͷŶ���
			p_Node = p_Info->pRear;								//��ָ����������ѭ����
		}
	}
	p_Info_temp->pNext = p_Info->pNext;					
	free(p_Info);												//ɾ�����ж�Ӧ�������еĽڵ�
	pQueue_Info.iID = pQueue_Info.iID - 1;		
	LeaveCriticalSection(&pQueue_Info.cs);	
}

#endif
