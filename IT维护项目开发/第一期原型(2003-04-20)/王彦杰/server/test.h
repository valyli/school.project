/*************************************************************
  Copyright (C)
  File name:  
  Author: 
  Version:  
  Date: 2003-3-28
  Description:    此文件是对线程间通信的基本设计的封装接口
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
#define ITDQ_BLOCK_YES       1					//阻塞模式
typedef   struct   tagSMM_node
	{
		SMM_UCHAR	  cData[Data_Size];			//数据块大小	
		tagSMM_node   *pNext;					//指针域
	}SMM_node; 
typedef   struct  tagSMM_Queue_Info
	{
		SMM_INT	    iID;						//队列ID
		SMM_INT		iSize;						//队列长度	
		SMM_INT		iMode;						//判断阻塞或非阻塞
		tagSMM_node * pFront;					
		tagSMM_node * pRear;
		tagSMM_Queue_Info* pNext;
		CRITICAL_SECTION   cs;					//临界区变量
		HANDLE		hSemRead;
		HANDLE      hSemWrite;
		BOOL		isFull;
		BOOL		isEmpty;
	}SMM_Queue_Info;
tagSMM_Queue_Info pQueue_Info;					//定义链表的头节点
/*********************************************************
  Function:       ITDQ_Init
  Description:    初始化头节点
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	


  Output:         
  Return:         成功返回TRUE
				  失败返回FALSE

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
  Description:    创建队列
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	iMaxLen: 创建的任务数据队列的最大长度
	
					p:队列节点指针


  Output:         
  Return:         成功返回唯一标识该队列的ID号,是一个非负整型.
				  失败返回-1表示创建失败

  Others:        
***********************************************************/
SMM_BOOL ITDQ_CreateQueue(SMM_UINT uiMaxLen, tagSMM_node* & pNode)			//创建队列函数
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
		p2 = (tagSMM_node*)malloc(sizeof(tagSMM_node));		/*根据用户输入的队列大
															小循环分配地址空间*/														
		p1->pNext = p2;
		p1 = p2;
	}
	p1->pNext = pNode;											//使指针指向头元素
	return TRUE;
	
}
/*********************************************************
  Function:       ITDO_Create
  Description:    初始化库
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          
                  iMode:创建一个任务间通信的数据队列模式(阻塞/非阻塞)

				  iMaxLen: 创建的任务数据队列的最大长度
  Output:         
  Return:         成功返回唯一标识该队列的ID号,是一个非负整型.
				  失败返回-1表示创建失败
  Others:        
***********************************************************/
SMM_INT ITDQ_Create(SMM_INT iMode,SMM_UINT uiMaxLen)	
{
	
	SMM_INT ID;	
	tagSMM_node* p_Node = 0;
	tagSMM_Queue_Info* p_Info = &pQueue_Info;					//使指针p_Info指向节点
	EnterCriticalSection(&pQueue_Info.cs);		
	if(FALSE == ITDQ_CreateQueue(uiMaxLen, p_Node))
	{
		printf("Create queue error\n");
	}
	while(p_Info->pNext != NULL)
	{
		p_Info = p_Info->pNext;									//指针后移,找到链表最后节点
	}

	ID = p_Info->iID;
	ID = ID + 1;
	p_Info->pNext = (tagSMM_Queue_Info*)malloc(sizeof(tagSMM_Queue_Info));
	p_Info = p_Info->pNext;
	p_Info->hSemWrite = CreateSemaphore(NULL,5,5,NULL);			//创建写信号量
	p_Info->hSemRead = CreateSemaphore(NULL,0,5,NULL);			//创建读信号量
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
  Description:    从任务间通信的数据队列读出若干数据块
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
				iId :	任务数据队列的ID号，由ITDQ_Create创建时得到

				pData:要读取的数据块指针缓冲区
				
  Output:         
  Return:        实际读取的数据块数目 

  Others:       0:	表示队列空
			  －1:  表示没有输入的ID对应的数据独列
			   -4:  表示队列为空
			  默认一次只写一个数据块
			
***********************************************************/
SMM_INT ITDQ_Read( SMM_INT iId, SMM_UCHAR *pData)
{	
	tagSMM_Queue_Info *p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	int j;
	while(p_Info != NULL)
	{
		p_Info = p_Info->pNext;									//循环往下找链表信息，有对应的ID就跳出
		if(p_Info->iID == iId)
			break;
	}
	if(p_Info->iMode == ITDQ_BLOCK_YES)							//同步读写操作
	{
		if(p_Info != NULL)										//找到值为iId的队列
		{	
			WaitForSingleObject(p_Info->hSemRead,INFINITE);	
			EnterCriticalSection(&p_Info->cs);
			for(j = 0; j < Data_Size; j++)					//判断读取	
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
		if(p_Info != NULL)										//找到值为iId的队列
		{
			EnterCriticalSection(&p_Info->cs);
			//队列为空
			if(p_Info->pFront == p_Info->pRear && p_Info->isEmpty == TRUE)
			{
				printf("IsEmpty and return.\n");
				LeaveCriticalSection(&p_Info->cs);
				return -3;
			}
				
			for(j = 0; j < Data_Size; j++)					//判断读取	
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
  Description:    向任务间通信的数据队列写入若干数据块
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
				iId :	任务数据队列的ID号，由ITDQ_Create创建时得到

				pData:  要写入的数据块指针缓冲区

				
  Output:         
  Return:        实际写入的数据块数目 

  Others:       0:	表示队列空
			  －1:  表示没有输入的ID对应的数据独列
			  -3:   表示队列满
			  默认一次只写一个数据块
  			
***********************************************************/
SMM_INT ITDQ_Write(SMM_INT iId, SMM_UCHAR *pData)
{
	tagSMM_Queue_Info *p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	int i=1;
	int j;
	while(p_Info != NULL)
	{
		p_Info = p_Info->pNext;									//循环往下找链表信息，有对应的ID就跳出
		if(p_Info->iID == iId)
			break;
	}
	if(p_Info->iMode == ITDQ_BLOCK_YES)							//同步读写操作
	{
		if(p_Info != NULL)										//找到值为iId的队列
		{
			WaitForSingleObject(p_Info->hSemWrite,INFINITE);	
			EnterCriticalSection(&p_Info->cs);
			for(j = 0; j < Data_Size; j++)						//判断读取	
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
	else														//异步读写
	{
		if(p_Info != NULL)										//找到值为iId的队列
		{
			EnterCriticalSection(&p_Info->cs);
			//标记位队列为满退出
			if(p_Info->pFront == p_Info->pRear && p_Info->isFull == TRUE)
			{			
				printf("IsFull and return.\n");
				LeaveCriticalSection(&p_Info->cs);
				return -3;
			}
			for(j = 0; j < Data_Size; j++)					//判断读取	
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
  Description:    删除一个任务间通信的数据队列
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
				iId :	任务数据队列的ID号，由ITDQ_Create创建时得到
                               
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
		p_Info = p_Info->pNext;									//循环往下找链表信息，有对应的ID就跳出
	}
	if(p_Info != NULL)
	{
		p_Node = p_Info->pFront;								//找到循环队列中的任何一个,所有的队列结点操作都是通过链表指针来操作			
		p_Node = p_Node->pNext;									//指针依次往下
		p_Info->pFront->pNext = NULL;							//将循环队列断开	
		while(p_Node != NULL)
		{
			p_Info->pRear = p_Node->pNext;			
			free(p_Node);										//释放队列
			p_Node = p_Info->pRear;								//将指针依次向下循环找
		}
	}
	p_Info_temp->pNext = p_Info->pNext;					
	free(p_Info);												//删除队列对应在链表中的节点
	pQueue_Info.iID = pQueue_Info.iID - 1;		
	LeaveCriticalSection(&pQueue_Info.cs);	
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    