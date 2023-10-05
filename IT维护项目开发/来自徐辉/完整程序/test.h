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
#ifndef __TEST_H__
#define __TEST_H__

#include "smm_type.h"


#include "stdio.h"
//#include "Windows.h"
#define Data_Size			256					//队列长度
#define ITDQ_BLOCK_YES       1					//阻塞模式
typedef   struct   tagSMM_node
	{
		SMM_CHAR	  cData[Data_Size];			//队列数据	
		tagSMM_node   *pNext;					//指针域
	}SMM_node; 
typedef   struct  tagSMM_Queue_Info
	{
		SMM_INT	    iID;						//队列ID
		SMM_INT		iSize;						
		SMM_INT		iMode;						//判断阻塞或非阻塞
		tagSMM_node * pFront;					
		tagSMM_node * pRear;
		tagSMM_Queue_Info* pNext;
		CRITICAL_SECTION   cs;					//临界区变量
		HANDLE		hSemRead;
		HANDLE      hSemWrite;
		BOOL		bFlags;
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
		pQueue_Info.iSize=NULL;
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
SMM_BOOL ITDQ_CreateQueue(SMM_UINT uiMaxLen, tagSMM_node* & p)			//创建队列函数
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
		p2 = (tagSMM_node*)malloc(sizeof(tagSMM_node));		/*根据用户输入的队列大
															小循环分配地址空间*/														
		p1->pNext = p2;
		p1 = p2;
	}
	p1->pNext = p;											//使指针指向头元素
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
SMM_INT ITDQ_Create(SMM_INT iMode,SMM_UINT uiMaxLen=256)	
{
	SMM_INT ID;	
	tagSMM_node* p_Node = 0;
	tagSMM_Queue_Info* p_Info = &pQueue_Info;					//使指针p_Info指向节点
	EnterCriticalSection(&pQueue_Info.cs);
	if(FALSE == ITDQ_CreateQueue(uiMaxLen, p_Node))
	{
		printf("Create queue error\n");
	}
	p_Info->hSemWrite=CreateSemaphore(NULL,256,256,"write");	//创建写信号量			
	p_Info->hSemRead=CreateSemaphore(NULL,0,256,"read");		//创建读信号量
	p_Info->bFlags=TRUE;										//初始化队列空标记
	while(p_Info->pNext != NULL)
	{
		p_Info = p_Info->pNext;									//指针后移,找到链表最后节点
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
  Description:    从任务间通信的数据队列读出若干数据块
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
				iId :	任务数据队列的ID号，由ITDQ_Create创建时得到

				pData[][Data_Size] :要读取的数据块指针缓冲区

				
  Output:         
  Return:        实际读取的数据块数目 

  Others:       0:	表示队列空
			  －1:  表示没有输入的ID对应的数据独列
			   -4:  表示队列为空
			  bFlags=TRUE:	队列为空
			  bFlags=FALSE: 队列满
			  默认一次只写一个数据块
			
***********************************************************/
SMM_INT ITDQ_Read( SMM_INT iId, SMM_CHAR *pData)
{	
	tagSMM_Queue_Info *p_Info = &pQueue_Info;
	tagSMM_node* p_Node = 0;
	int i;
	int j;
	while(p_Info != NULL)
	{
		p_Info = p_Info->pNext;									//循环往下找链表信息，有对应的ID就跳出
		if(p_Info->iID == iId)
			break;
	}
	if(p_Info->iMode == ITDQ_BLOCK_YES)							//同步读写操作
	{
		WaitForSingleObject(p_Info->hSemRead,INFINITE);
		EnterCriticalSection(&p_Info->cs);
		if(p_Info != NULL)										//找到值为iId的队列
		{
			for(i = 0;i < 1; i++)								//开始读取	
			{
				for(j = 0; j < Data_Size; j++)					//判断读取	
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
		if(p_Info != NULL)										//找到值为iId的队列
		{
			for(i = 0;i < 1;i ++)										//开始读取	
			{
				if(p_Info->pFront == p_Info->pRear)
				{
					
					if(p_Info->bFlags == TRUE)							//队列为空
					{
						return -4;
					}
					else
					{
						p_Info->bFlags=FALSE;
					}
				}
				for(j = 0; j < Data_Size; j++)					//判断读取	
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
  Description:    向任务间通信的数据队列写入若干数据块
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
				iId :	任务数据队列的ID号，由ITDQ_Create创建时得到

				pData[][Data_Size] :要写入的数据块指针缓冲区

				
  Output:         
  Return:        实际写入的数据块数目 

  Others:       0:	表示队列空
			  －1:  表示没有输入的ID对应的数据独列
			  -3:   表示队列满
			  bFlags=TRUE:	队列为空
			  bFlags=FALSE: 队列满
			  默认一次只写一个数据块
  			
***********************************************************/
SMM_INT ITDQ_Write(SMM_INT iId, SMM_CHAR *pData)
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
		WaitForSingleObject(p_Info->hSemRead,INFINITE);
		EnterCriticalSection(&p_Info->cs);
		if(p_Info != NULL)										//找到值为iId的队列
		{
			for(i = 0;i < 1;i++)								//开始写入	
			{	
				for(j = 0; j < Data_Size; j++)					//判断读取	
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
		if(p_Info != NULL)										//找到值为iId的队列
		{
			for(i = 0;i < 1;i++)								//开始写入	
			{
				if(p_Info->pFront == p_Info->pRear)
				{
					
					if(p_Info->bFlags==FALSE)							//标记位队列为满退出
					{
						return -3;
					}
					else
					{
						p_Info->bFlags=TRUE;
					}
				}
				for(j = 0; j < Data_Size; j++)					//判断读取	
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

#endif
