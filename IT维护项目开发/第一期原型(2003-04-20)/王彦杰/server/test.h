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
#include <afx.h>
#include <process.h>
#include "conio.h"
#include "smm_type.h"
#include "Base.h"
#define Data_Size			1024				
#define ITDQ_BLOCK_YES       1					//����ģʽ
typedef   struct   tagSMM_node
	{
		SMM_UCHAR	  cData[Data_Size];			//���ݿ��С	
		tagSMM_node   *pNext;					//ָ����
	}SMM_node; 
typedef   struct  tagSMM_Queue_Info
	{
		SMM_INT	    iID;						//����ID
		SMM_INT		iSize;						//���г���	
		SMM_INT		iMode;						//�ж������������
		tagSMM_node * pFront;					
		tagSMM_node * pRear;
		tagSMM_Queue_Info* pNext;
		CRITICAL_SECTION   cs;					//�ٽ�������
		HANDLE		hSemRead;
		HANDLE      hSemWrite;
		BOOL		isFull;
		BOOL		isEmpty;
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
		pQueue_Info.iSize=256;
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
SMM_BOOL ITDQ_CreateQueue(SMM_UINT uiMaxLen, tagSMM_node* & pNode)			//�������к���
{
	if(uiMaxLen ==0)
	{
		uiMaxLen = 256;
	}
	if(uiMaxLen < 0)
	{
		return FALSE;
	}
	tagSMM_node *p1, *p2;
	pNode=(tagSMM_node*)malloc(sizeof(tagSMM_node));
	p1 = pNode;
	for(int i = 0; i < uiMaxLen-1; i++)
	{
		p2 = (tagSMM_node*)malloc(sizeof(tagSMM_node));		/*�����û�����Ķ��д�
															Сѭ�������ַ�ռ�*/														
		p1->pNext = p2;
		p1 = p2;
	}
	p1->pNext = pNode;											//ʹָ��ָ��ͷԪ��
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
SMM_INT ITDQ_Create(SMM_INT iMode,SMM_UINT uiMaxLen)	
{
	
	SMM_INT ID;	
	tagSMM_node* p_Node = 0;
	tagSMM_Queue_Info* p_Info = &pQueue_Info;					//ʹָ��p_Infoָ��ڵ�
	EnterCriticalSection(&pQueue_Info.cs);		
	if(FALSE == ITDQ_CreateQueue(uiMaxLen, p_Node))
	{
		printf("Create queue error\n");
	}
	while(p_Info->pNext != NULL)
	{
		p_Info = p_Info->pNext;									//ָ�����,�ҵ��������ڵ�
	}

	ID = p_Info->iID;
	ID = ID + 1;
	p_Info->pNext = (tagSMM_Queue_Info*)malloc(sizeof(tagSMM_Queue_Info));
	p_Info = p_Info->pNext;
	p_Info->hSemWrite = CreateSemaphore(NULL,5,5,NULL);			//����д�ź���
	p_Info->hSemRead = CreateSemaphore(NULL,0,5,NULL);			//�������ź���
	p_Info->iID = ID;
	p_Info->iSize = uiMaxLen;
	p_Info->pFront = p_Node;
	p_Info->pRear = p_Node;
	p_Info->iMode = iMode;
	pQueue_Info.iID = pQueue_Info.iID + 1;
	p_Info->pRear = p_Info->pFront;	
	p_Info->isEmpty = TRUE;
	p_Info->isFull = FALSE;	
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

				pData:Ҫ��ȡ�����ݿ�ָ�뻺����
				
  Output:         
  Return:        ʵ�ʶ�ȡ�����ݿ���Ŀ 

  Others:       0:	��ʾ���п�
			  ��1:  ��ʾû�������ID��Ӧ�����ݶ���
			   -4:  ��ʾ����Ϊ��
			  Ĭ��һ��ֻдһ�����ݿ�
			
***********************************************************/
SMM_INT ITDQ_Read( SMM_INT iId, SMM_UCHAR *pData)
{	
	tagSMM_Queue_Info *p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	int j;
	while(p_Info != NULL)
	{
		p_Info = p_Info->pNext;									//ѭ��������������Ϣ���ж�Ӧ��ID������
		if(p_Info->iID == iId)
			break;
	}
	if(p_Info->iMode == ITDQ_BLOCK_YES)							//ͬ����д����
	{
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{	
			WaitForSingleObject(p_Info->hSemRead,INFINITE);	
			EnterCriticalSection(&p_Info->cs);
			for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
			*(pData+sizeof(SMM_UCHAR)*j)= p_Info->pFront->cData[j];		
			p_Info->pFront = p_Info->pFront->pNext;
			LeaveCriticalSection(&p_Info->cs);
			ReleaseSemaphore(p_Info->hSemWrite,1,NULL);
			return 1;
		}
		else
		{
			return -1;
		}		
	}
	else
	{
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			EnterCriticalSection(&p_Info->cs);
			//����Ϊ��
			if(p_Info->pFront == p_Info->pRear && p_Info->isEmpty == TRUE)
			{
				printf("IsEmpty and return.\n");
				LeaveCriticalSection(&p_Info->cs);
				return -3;
			}
				
			for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
				*(pData+sizeof(SMM_UCHAR)*j) = p_Info->pFront->cData[j];

			p_Info->isFull = FALSE;
			if(p_Info->pFront->pNext == p_Info->pRear)
			{
				p_Info->isEmpty = TRUE;
			}

			p_Info->pFront = p_Info->pFront->pNext;
			LeaveCriticalSection(&p_Info->cs);
			return 1;
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

				pData:  Ҫд������ݿ�ָ�뻺����

				
  Output:         
  Return:        ʵ��д������ݿ���Ŀ 

  Others:       0:	��ʾ���п�
			  ��1:  ��ʾû�������ID��Ӧ�����ݶ���
			  -3:   ��ʾ������
			  Ĭ��һ��ֻдһ�����ݿ�
  			
***********************************************************/
SMM_INT ITDQ_Write(SMM_INT iId, SMM_UCHAR *pData)
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
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			WaitForSingleObject(p_Info->hSemWrite,INFINITE);	
			EnterCriticalSection(&p_Info->cs);
			for(j = 0; j < Data_Size; j++)						//�ж϶�ȡ	
			{
				p_Info->pRear->cData[j] = *(pData+sizeof(SMM_UCHAR)*j);
			}
			p_Info->pRear = p_Info->pRear->pNext;
			LeaveCriticalSection(&p_Info->cs);
			ReleaseSemaphore(p_Info->hSemRead,1,NULL);			
			return 1;
		}
		else
		{
			return -1;
		}		
	}
	else														//�첽��д
	{
		if(p_Info != NULL)										//�ҵ�ֵΪiId�Ķ���
		{
			EnterCriticalSection(&p_Info->cs);
			//���λ����Ϊ���˳�
			if(p_Info->pFront == p_Info->pRear && p_Info->isFull == TRUE)
			{			
				printf("IsFull and return.\n");
				LeaveCriticalSection(&p_Info->cs);
				return -3;
			}
			for(j = 0; j < Data_Size; j++)					//�ж϶�ȡ	
			{
				p_Info->pRear->cData[j] = *(pData+sizeof(SMM_UCHAR)*j);
			}

			p_Info->isEmpty = FALSE;
			if(p_Info->pRear->pNext == p_Info->pFront)
			{
				printf("IsFull\n");
				p_Info->isFull = TRUE;
			}

			p_Info->pRear = p_Info->pRear->pNext;
			LeaveCriticalSection(&p_Info->cs);
			return 1;
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    