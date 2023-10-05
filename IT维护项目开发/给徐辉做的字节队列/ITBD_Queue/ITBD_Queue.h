#ifndef _ITBD_QUEUE_H_
#define _ITBD_QUEUE_H_

#include "stdio.h"
#include "smm_type.h"

#define DEFAULT_DIMENSION	4096
#define DEFAULT_QUEUE_MAX	256				
#define ITBDQ_BLOCK_YES		1				//阻塞模式
#define ITBDQ_BLOCK_NO		0				//非阻塞模式
#define NULL 0


typedef struct tagSMM_Node_Info
{		
	SMM_INT			iDataBlockSize;			//数据块大小，不包含信息头占用的长度
	SMM_INT			iDataBlockID;			//数据块ID，从1起，0表示此块为完整数据
	SMM_INT			iDataBlockState;		//由于队列是FIFO的，所以不用标记顺序，但必须标记数据块是属于开始（1），中间（0）还是结束（－1），以使获得数据块的一方能确定数据是否获得完整
//	SMM_INT			UsefulLifeOfDataBlockID;//iDataBlockID的生存期，当此值为0时，
}SMM_Node_Info;

typedef struct tagSMM_Queue_Info
{
	SMM_INT		iID;						//队列ID
	SMM_INT		iDimension;					//队列总容量，按字节
											//最少要大于(sizeof(SMM_Node_Info) + sizeof(SMM_UCHAR))，否则队列无用
	SMM_INT		iAvailable;                 //可用的(即剩余)队列长度，按字节
	SMM_INT		iCurAvailDataBlockID;		//当前可用的DataBlockID，每次有新的数据块时自增1，循环使用，不可为0
	SMM_INT		iMode;						//判断阻塞或非阻塞
	SMM_UCHAR*	pBase;						//基址
 	SMM_INT		offsetRead;					//队列读指针偏移量，按字节
	SMM_INT		offsetWrite;
	tagSMM_Queue_Info* pNext;				//后继队列信息节点
	CRITICAL_SECTION cs;					//队列临界区变量
	CRITICAL_SECTION cs_write;				//队列临界区写控制变量
	CRITICAL_SECTION cs_read;				//队列临界区读控制变量
	HANDLE		hSemRead;
	HANDLE		hSemWrite;
	BOOL		isFull;
	BOOL		isEmpty;
}SMM_Queue_Info;


void ITBDQ_Init();
SMM_INT ITBDQ_Delete(SMM_INT iId);
SMM_INT ITBDQ_Create(SMM_UINT iDimension, SMM_INT iMode);
SMM_INT ITBDQ_Write(SMM_INT iId, SMM_UCHAR* pData, SMM_INT iNum, SMM_INT* iDataBlockID);
SMM_INT ITBDQ_Read(SMM_INT iId, SMM_UCHAR** pData, SMM_INT* iDataBlockID, SMM_INT* iDataBlockState);
SMM_INT ITBDQ_Count();


#endif