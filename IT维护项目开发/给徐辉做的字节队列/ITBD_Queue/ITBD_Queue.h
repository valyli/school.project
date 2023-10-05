#ifndef _ITBD_QUEUE_H_
#define _ITBD_QUEUE_H_

#include "stdio.h"
#include "smm_type.h"

#define DEFAULT_DIMENSION	4096
#define DEFAULT_QUEUE_MAX	256				
#define ITBDQ_BLOCK_YES		1				//����ģʽ
#define ITBDQ_BLOCK_NO		0				//������ģʽ
#define NULL 0


typedef struct tagSMM_Node_Info
{		
	SMM_INT			iDataBlockSize;			//���ݿ��С����������Ϣͷռ�õĳ���
	SMM_INT			iDataBlockID;			//���ݿ�ID����1��0��ʾ�˿�Ϊ��������
	SMM_INT			iDataBlockState;		//���ڶ�����FIFO�ģ����Բ��ñ��˳�򣬵����������ݿ������ڿ�ʼ��1�����м䣨0�����ǽ�������1������ʹ������ݿ��һ����ȷ�������Ƿ�������
//	SMM_INT			UsefulLifeOfDataBlockID;//iDataBlockID�������ڣ�����ֵΪ0ʱ��
}SMM_Node_Info;

typedef struct tagSMM_Queue_Info
{
	SMM_INT		iID;						//����ID
	SMM_INT		iDimension;					//���������������ֽ�
											//����Ҫ����(sizeof(SMM_Node_Info) + sizeof(SMM_UCHAR))�������������
	SMM_INT		iAvailable;                 //���õ�(��ʣ��)���г��ȣ����ֽ�
	SMM_INT		iCurAvailDataBlockID;		//��ǰ���õ�DataBlockID��ÿ�����µ����ݿ�ʱ����1��ѭ��ʹ�ã�����Ϊ0
	SMM_INT		iMode;						//�ж������������
	SMM_UCHAR*	pBase;						//��ַ
 	SMM_INT		offsetRead;					//���ж�ָ��ƫ���������ֽ�
	SMM_INT		offsetWrite;
	tagSMM_Queue_Info* pNext;				//��̶�����Ϣ�ڵ�
	CRITICAL_SECTION cs;					//�����ٽ�������
	CRITICAL_SECTION cs_write;				//�����ٽ���д���Ʊ���
	CRITICAL_SECTION cs_read;				//�����ٽ��������Ʊ���
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