#include "ITBD_Queue.h"



SMM_Queue_Info Queue_Info; 					//���������ͷ�ڵ�



/*********************************************************
  Function:       ITDQ_Init
  Description:    ��ʼ��ͷ�ڵ�
  Calls:          // �����������õĺ����嵥
  Called By:      // ���ñ������ĺ����嵥
  Input:          ��	


  Output:         
  Return:

  Others:        
***********************************************************/
void ITBDQ_Init()
{
		Queue_Info.iID=0;
		Queue_Info.iDimension = DEFAULT_QUEUE_MAX;		//�����������			
		Queue_Info.iAvailable = 0;						//��ǰ��������
		Queue_Info.hSemRead = NULL;
		Queue_Info.hSemWrite = NULL;
		Queue_Info.pBase = NULL;
		Queue_Info.offsetRead = 0;
		Queue_Info.offsetWrite = 0;
		Queue_Info.iMode = ITBDQ_BLOCK_NO;
		Queue_Info.pNext = NULL;
		InitializeCriticalSection(&Queue_Info.cs);
}


/*
��һ������������ַ��ַ���㣬ֻ����Ǹ�����ƫ��������ַȡ��SMM_Queue_Info
*/
SMM_UCHAR* ITBDQ_WorkOutPointer(SMM_Queue_Info* pQueue_Info, SMM_INT offset)
{
	//���ƫ��������������NULL
	if((int)(offset / (double)pQueue_Info->iDimension) >= 2
		|| offset < 0)
		return NULL;
	if(pQueue_Info->pBase == NULL)
		return NULL;

	return pQueue_Info->pBase + (offset % pQueue_Info->iDimension);
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
SMM_BOOL ITBDQ_CreateQueue(SMM_UCHAR** pBase, SMM_UINT iDimension)
{
/*	if(uiMaxLen ==0)
	{
		uiMaxLen;
	}
*/	if(iDimension < 0)
	{
		return FALSE;
	}

	*pBase = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * iDimension);
	if(*pBase == NULL)
		return FALSE;
	return TRUE;
}


SMM_INT ITBDQ_Count()
{
	SMM_INT n;
	EnterCriticalSection(&Queue_Info.cs);
	n = Queue_Info.iAvailable;
	LeaveCriticalSection(&Queue_Info.cs);
	return n;
/*	SMM_INT n = 0;
	SMM_Queue_Info* p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	while(p_Info->pNext != NULL)
	{
		p_Info = p_Info->pNext;
		n++;
	}
	LeaveCriticalSection(&Queue_Info.cs);
	return n;
*/
}
/*********************************************************
  Function:       ITDO_Create
  Description:    ������Ϣ����������
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
SMM_INT ITBDQ_Create(SMM_UINT iDimension = DEFAULT_DIMENSION, SMM_INT iMode = ITBDQ_BLOCK_NO)
{	
	//ʹָ��p_Infoָ��ڵ�
	SMM_Queue_Info* p_Info_pre, *p_Info_temp, *p_Info = &Queue_Info;
	//��������Ϣ����
	EnterCriticalSection(&Queue_Info.cs);

	//�ж϶��������Ƿ��Ѵ����ֵ
	if(p_Info->iAvailable >= p_Info->iDimension)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -3;
	}

	//�������еĴ洢�ռ�
	SMM_UCHAR* pBase;
	if(FALSE == ITBDQ_CreateQueue(&pBase, iDimension))
	{
		printf("Create queue error\n");
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}

/*	//��ͷ�ڵ�����ҵ�������Ϣ�������ڵ㣬ȷ����ǰ��������
	p_Info_temp = &Queue_Info;
	int n = 0;
	while(p_Info_temp->pNext != NULL)
	{
		p_Info_temp = p_Info_temp->pNext;
		n++;
	}
		printf("---------------%d--------------------", n);
	//������������Ѵ����ֵ���򷵻ض����Ѵ����ֵ
	if(n >= DEFAULT_QUEUE_MAX)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -3;
	}
*/
	//��ȡ�¶��е�IDֵ����ֵΪ�����ɸ��ã�Ӧ��1��
	//Ҫ���ֶ�����Ϣ�����е�IDֵ�ĵ���
	SMM_INT ID;
	ID = 0;
	p_Info_pre = NULL;
	p_Info = &Queue_Info;
	do
	{
		if(ID != p_Info->iID)
			break;
		p_Info_pre = p_Info;
		p_Info = p_Info->pNext;
		ID = ID + 1;
	}
	while(p_Info != NULL);

	p_Info_temp = (SMM_Queue_Info*)malloc(sizeof(SMM_Queue_Info));
	if(p_Info_temp->pNext == NULL)
	{
		printf("Create queue_info error\n");
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}
	Queue_Info.iAvailable = Queue_Info.iAvailable + 1;

	p_Info_temp->hSemWrite = CreateSemaphore(NULL,1,1,NULL);			//����д�ź���
	p_Info_temp->hSemRead = CreateSemaphore(NULL,0,1,NULL);			//�������ź���
	p_Info_temp->iID = ID;
	p_Info_temp->iDimension = iDimension;
	p_Info_temp->iAvailable = iDimension;
	p_Info_temp->iCurAvailDataBlockID = 1;
	p_Info_temp->pBase = pBase;
	p_Info_temp->offsetRead = 0;
	p_Info_temp->offsetWrite = 0;
	p_Info_temp->iMode = iMode;
	p_Info_temp->isEmpty = TRUE;
	p_Info_temp->isFull = FALSE;	
	InitializeCriticalSection(&p_Info_temp->cs);	
	InitializeCriticalSection(&p_Info_temp->cs_write);	
	InitializeCriticalSection(&p_Info_temp->cs_read);
	
	p_Info_temp->pNext = p_Info_pre->pNext;
	p_Info_pre->pNext = p_Info_temp;

	LeaveCriticalSection(&Queue_Info.cs);
	return p_Info_temp->iID;
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
SMM_INT ITBDQ_Delete(SMM_INT iId)
{
	//����IDֵ���Ϸ�
	if(iId <= 0)
		return -2;

	SMM_Queue_Info* p_Info_pre, *p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	//ѭ��������������Ϣ���ж�Ӧ��ID������
	while(p_Info != NULL)
	{
		if(p_Info->iID==iId)
			break;
		p_Info_pre = p_Info;
		p_Info = p_Info->pNext;
	}

	//���ҵ���ӳ����
	if(p_Info != NULL)
	{
		EnterCriticalSection(&p_Info->cs);
		p_Info_pre->pNext = p_Info->pNext;
		free(p_Info->pBase);
		free(p_Info);
		Queue_Info.iAvailable = Queue_Info.iAvailable - 1;
		LeaveCriticalSection(&Queue_Info.cs);
		return 1;
	}
	//IDֵ��ָ���Ķ��в�����
	else
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
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

				pData:  Ҫд������ݿ黺����

				iNum:   ��Ҫд������ݿ���Ŀ

				
  Output:         
  Return:        ʵ��д������ݿ���Ŀ 

  Others:       0:	��ʾ���п�
			  ��1:  ��ʾû�������ID��Ӧ�����ݶ���
			  -3:   ��ʾ������
  			
***********************************************************/
SMM_INT ITBDQ_Write(SMM_INT iId, SMM_UCHAR* pData, SMM_INT iNum, SMM_INT* iDataBlockID)
{
	//����IDֵ���Ϸ�
	if(iId <= 0)
		return -2;

	//���ҵ�Ҫʹ�õĶ���
	SMM_Queue_Info *p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	while(p_Info != NULL)
	{
		if(p_Info->iID == iId)
			break;
		p_Info = p_Info->pNext;
	}

	//û�ҵ���ӳ�Ķ���
	if(p_Info == NULL)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}

	//���־ֲ�������������ʼ��
	SMM_Node_Info Node_Info;						//�����ݴ���Ϣͷ����
	int offsetWrite = p_Info->offsetWrite;			//��õ�ǰдָ��ƫ����
	int i = 0;										//���ڼ�¼�Ѿ�д�����ֽ���
	int sizeof_Node_Info = sizeof(Node_Info);		//��¼��Ϣͷ��С


	//����Ϊ������ʱ
	if(p_Info->iMode == ITBDQ_BLOCK_NO)
	{
		//���ҵ���ӳ�Ķ��У���������ִ��
		//��ռ䲻����д��һ��ڵ���Ϣ��һ����λ�����ݣ��򷵻ض�����
		if(p_Info->iAvailable < (sizeof(SMM_Node_Info) + sizeof(SMM_UCHAR)))
		{
			LeaveCriticalSection(&Queue_Info.cs);
			return -3;
		}

		EnterCriticalSection(&p_Info->cs);

		//�ж������Ƿ����һ��д��
		//�����һ��д��
		if((iNum + sizeof(SMM_Node_Info)) <= (SMM_UINT)p_Info->iAvailable)
		{
			//���¶�����Ϣ�ڵ��е���Ӧ����
			//�޸Ŀ��ÿռ�
			p_Info->iAvailable = p_Info->iAvailable - (iNum + sizeof(SMM_Node_Info));
			*iDataBlockID = p_Info->iAvailable;				//��ʱ���䷵��ʣ��ռ�
			//����ǰдָ������Ӧƫ��
			p_Info->offsetWrite = (p_Info->offsetWrite + (iNum + sizeof(SMM_Node_Info))) % p_Info->iDimension;

			LeaveCriticalSection(&Queue_Info.cs);

			//�������ݿ���Ϣͷ
			Node_Info.iDataBlockID = 0;
			Node_Info.iDataBlockState = -1;		//��ʱ��Ϊ�κ�ֵ
			Node_Info.iDataBlockSize = iNum;

			//д��
			//��д��Ϣͷ
			for(; i < sizeof_Node_Info; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
			//��д���ݿ�
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
			{
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];
			}

			LeaveCriticalSection(&p_Info->cs);
			return 0;
		}
		//�������һ��д�룬��ô��д���پ�д���٣�������д����ֽ���
		else
		{
			//�������ݿ���Ϣͷ
			Node_Info.iDataBlockID = p_Info->iCurAvailDataBlockID;
			//��Ǵ����ݿ鲻������ֻ�ǿ�ʼ
			Node_Info.iDataBlockState = 1;
			Node_Info.iDataBlockSize = p_Info->iAvailable - sizeof_Node_Info;
			//�趨����ֵiDataBlockID��ʹ�û���֪����д��ʱ��ʹ�õ����ݿ�ID
			*iDataBlockID = Node_Info.iDataBlockID;

			//���¶�����Ϣ�ڵ��е���Ӧ����
			//�޸Ŀ��ÿռ�
			//���ÿռ�Ϊ0��ʾд��
			p_Info->iAvailable = 0;
			//����ǰдָ������Ӧƫ��
			//ָ��offsetRead���ǽ���������
			p_Info->offsetWrite = p_Info->offsetRead;
			//���õ�DataBlockID����
			//��ʱ����10000���Ժ�Ӧ������
			if(p_Info->iCurAvailDataBlockID == 10000 - 1)//�˴���ֹ����iCurAvailDataBlockID �� 0
				p_Info->iCurAvailDataBlockID = 1;
			else
				p_Info->iCurAvailDataBlockID = (p_Info->iCurAvailDataBlockID + 1) % 10000;

			LeaveCriticalSection(&Queue_Info.cs);

			for(; i < sizeof_Node_Info; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
			//��д���ݿ�
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];

			LeaveCriticalSection(&p_Info->cs);
			return Node_Info.iDataBlockSize;
		}
	}

	//����Ϊ����ʱ
	else if(p_Info->iMode == ITBDQ_BLOCK_YES)
	{
		//��д������������������������д�������룬Ҳ��ֹ����뵽���ڽ��е�д������
		EnterCriticalSection(&p_Info->cs_write);

		//���־ֲ�������������ʼ��
		SMM_Node_Info Node_Info;						//�����ݴ���Ϣͷ����
		int offsetWrite = p_Info->offsetWrite;			//��õ�ǰдָ��ƫ����
		int i = 0;										//���ڼ�¼�Ѿ�д�����ֽ���
		int sizeof_Node_Info = sizeof(Node_Info);		//��¼��Ϣͷ��С

/*		//��������ǿ���һ��д���
		if((iNum + sizeof(SMM_Node_Info)) <= (SMM_UINT)p_Info->iAvailable)
		{
			EnterCriticalSection(&p_Info->cs);

			//���¶�����Ϣ�ڵ��е���Ӧ����
			//�޸Ŀ��ÿռ�
			p_Info->iAvailable = p_Info->iAvailable - (iNum + sizeof(SMM_Node_Info));
			printf("###############........%d\n", p_Info->iAvailable);
			*iDataBlockID = p_Info->iAvailable;				//��ʱ���䷵��ʣ��ռ�
			//����ǰдָ������Ӧƫ��
			p_Info->offsetWrite = (p_Info->offsetWrite + (iNum + sizeof(SMM_Node_Info))) % p_Info->iDimension;

			LeaveCriticalSection(&Queue_Info.cs);

			//�������ݿ���Ϣͷ
			Node_Info.iDataBlockID = 0;
			Node_Info.iDataBlockState = -1;		//��ʱ��Ϊ�κ�ֵ
			Node_Info.iDataBlockSize = iNum;

			//д��
			//��д��Ϣͷ
			for(; i < sizeof_Node_Info; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
			//��д���ݿ�
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
			{
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];
			}

			LeaveCriticalSection(&p_Info->cs_write);
			LeaveCriticalSection(&p_Info->cs);
			return 0;
		}
		//��������޷�һ��д��
		else
		{
*/			SMM_UCHAR* pTempData;		//��ʱ�洢��
			//������ʱ�洢��
			pTempData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * iNum);
			//�����������ȵ�����ʱ������
			for(i = 0; i < iNum; i++)
			{
				pTempData[i] = pData[i];
			}


			//��¼�Ѿ�д������ݵ��ֽ���
			int iData_Writen = 0;

			//��һҳ���
			int FirstPageFlag = 1;

			while(iNum != iData_Writen)
			{
				//����Ƿ����㹻�Ŀռ�д������
				if(p_Info->iAvailable <= sizeof_Node_Info)
				{
					LeaveCriticalSection(&Queue_Info.cs);
					Sleep(0);
					EnterCriticalSection(&Queue_Info.cs);
					continue;
				}

				//��õ�ǰдָ��ƫ����
				offsetWrite = p_Info->offsetWrite;

				//����ǵ�һ��д����
				if(FirstPageFlag == 1)
				{
					//����µõ��Ŀռ���Խ���������һ��д��
					if(p_Info->iAvailable - sizeof_Node_Info >= iNum)
					{
						i = 0;
						//���¶�����Ϣ�ڵ��е���Ӧ����
						//�޸Ŀ��ÿռ�
						p_Info->iAvailable = p_Info->iAvailable - (iNum + sizeof(SMM_Node_Info));
//						printf("$$$$$$$$$$$$$$$........%d\n", p_Info->iAvailable);
						*iDataBlockID = p_Info->iAvailable;				//��ʱ���䷵��ʣ��ռ�
						//����ǰдָ������Ӧƫ��
						p_Info->offsetWrite = (p_Info->offsetWrite + (iNum + sizeof(SMM_Node_Info))) % p_Info->iDimension;
							EnterCriticalSection(&p_Info->cs);

						LeaveCriticalSection(&Queue_Info.cs);

						//�������ݿ���Ϣͷ
						Node_Info.iDataBlockID = 0;
						Node_Info.iDataBlockState = -1;		//��ʱ��Ϊ�κ�ֵ
						Node_Info.iDataBlockSize = iNum;

						//д��
						//��д��Ϣͷ
						for(; i < sizeof_Node_Info; i++)
							p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
						//��д���ݿ�
						for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
						{
							p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];
						}

						LeaveCriticalSection(&p_Info->cs_write);
						LeaveCriticalSection(&p_Info->cs);
						return 0;
					}

					//����õ��Ŀռ䲻�ܽ���������һ��д��
					else
					{
						//�������ݿ���Ϣͷ�е�iDataBlockID
						Node_Info.iDataBlockID = p_Info->iCurAvailDataBlockID;
						//���õ�DataBlockID����
						//��ʱ����10000���Ժ�Ӧ������
						if(p_Info->iCurAvailDataBlockID == 10000 - 1)//�˴���ֹ����iCurAvailDataBlockID �� 0
							p_Info->iCurAvailDataBlockID = 1;
						else
							p_Info->iCurAvailDataBlockID = (p_Info->iCurAvailDataBlockID + 1) % 10000;
						//�趨����ֵiDataBlockID��ʹ�û���֪����д��ʱ��ʹ�õ����ݿ�ID
						*iDataBlockID = Node_Info.iDataBlockID;

						Node_Info.iDataBlockSize = p_Info->iAvailable - sizeof_Node_Info;
						//���¶�����Ϣ�ڵ��е���Ӧ����
						//�޸Ŀ��ÿռ�
						//���ÿռ�Ϊ0��ʾд��
						p_Info->iAvailable = 0;
						//����ǰдָ������Ӧƫ��
						//ָ��offsetRead���ǽ���������
						p_Info->offsetWrite = p_Info->offsetRead;

						//��Ǵ����ݿ飨ֻ�ǵ�һ������������ֻ�ǿ�ʼ
						Node_Info.iDataBlockState = 1;
						FirstPageFlag = 0;
					}
				}

				//�趨Ҫд������ݿ�Ĵ�С
				//���ʣ��ռ�>=ʣ������ݣ����趨iDataBlockSizeΪʣ�����ݴ�С
				else if(p_Info->iAvailable - sizeof_Node_Info >= iNum - iData_Writen)
				{
//				printf("write iAvailable:%d, inum-idata:%d\n", p_Info->iAvailable, iNum - iData_Writen);
					Node_Info.iDataBlockSize = iNum - iData_Writen;
					//��Ǵ����ݿ鲻�������ǽ�����
					Node_Info.iDataBlockState = -1;
					//���¶�����Ϣ�ڵ��е���Ӧ����
					//�޸Ŀ��ÿռ�
					p_Info->iAvailable = p_Info->iAvailable - ((iNum - iData_Writen) + sizeof_Node_Info);
					//����ǰдָ������Ӧƫ��
					p_Info->offsetWrite = (p_Info->offsetWrite + ((iNum - iData_Writen) + sizeof_Node_Info)) % p_Info->iDimension;
				}
				//�����������ÿռ�
				else
				{
					Node_Info.iDataBlockSize = p_Info->iAvailable - sizeof_Node_Info;
					//��Ǵ����ݿ鲻���������м��һ��
					Node_Info.iDataBlockState = 0;
					//���¶�����Ϣ�ڵ��е���Ӧ����
					//�޸Ŀ��ÿռ�
					//���ÿռ�Ϊ0��ʾд��
					p_Info->iAvailable = 0;
					//����ǰдָ������Ӧƫ��
					//ָ��offsetRead���ǽ���������
					p_Info->offsetWrite = p_Info->offsetRead;
				}				
				
				EnterCriticalSection(&p_Info->cs);

				//��ʱ�ͷŶ�����Ϣ����
				LeaveCriticalSection(&Queue_Info.cs);

				//��CPU���ø�ϵͳ���е���
				Sleep(0);

				//д�벿�����ݵ�������
				i = 0;
				//��д��Ϣͷ
				for(; i < sizeof_Node_Info; i++)
					p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
				//��д���ݿ�
				for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
					p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[iData_Writen++];

				//��ʱ�ͷŶ�������
				LeaveCriticalSection(&p_Info->cs);

				if(iNum == iData_Writen)
					break;

				//��CPU���ø�ϵͳ���е���
				Sleep(0);

				EnterCriticalSection(&Queue_Info.cs);


			}

			//���ض�ҳд��ɹ�
			LeaveCriticalSection(&p_Info->cs_write);
			return -100;
	}
	else
	{
		LeaveCriticalSection(&p_Info->cs_write);
		//���ض���ģʽ���ô���
		return -5;
	}
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

				pData:  ���е����ݻ�����

				iNum:   ��Ҫ��ȡ�����ݿ���Ŀ
				
  Output:         
  Return:        ʵ�ʶ�ȡ�����ݿ���Ŀ 

  Others:       0:	��ʾ���п�
			  ��1:  ��ʾû�������ID��Ӧ�����ݶ���
			   -4:  ��ʾ����Ϊ��
			
***********************************************************/
SMM_INT ITBDQ_Read(SMM_INT iId, SMM_UCHAR** pData, SMM_INT* iDataBlockID, SMM_INT* iDataBlockState)
{
	//����IDֵ���Ϸ�
	if(iId <= 0)
		return -2;

	//���ҵ�Ҫʹ�õĶ���
	SMM_Queue_Info *p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	while(p_Info != NULL)
	{
		if(p_Info->iID == iId)
			break;
		p_Info = p_Info->pNext;
	}

	//û�ҵ���ӳ�Ķ���
	if(p_Info == NULL)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}

	//���־ֲ�������������ʼ��
	SMM_Node_Info Node_Info;						//�����ݴ���Ϣͷ����
	int offsetRead = p_Info->offsetRead;			//��õ�ǰдָ��ƫ����
	int i = 0;										//���ڼ�¼�Ѿ��������ֽ���
	int sizeof_Node_Info = sizeof(Node_Info);		//��¼��Ϣͷ��С

	//����Ϊ������ʱ
	if(p_Info->iMode == ITBDQ_BLOCK_NO)
	{
		//���ҵ���ӳ�Ķ��У���������ִ��
		//������ÿռ�С��һ��ڵ���Ϣ��һ����λ�����ݣ��򷵻ض��п�
		if((p_Info->iDimension - p_Info->iAvailable) < (sizeof(SMM_Node_Info) + sizeof(SMM_UCHAR)))
		{
			LeaveCriticalSection(&Queue_Info.cs);
			return -3;
		}

		EnterCriticalSection(&p_Info->cs);


		//����
		//�ȶ���Ϣͷ
		for(; i < sizeof_Node_Info; i++)
			((SMM_UCHAR*)&Node_Info)[i] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];
		//�����ݴ����ݿ��õĿռ�
		*pData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize);
		//�ٶ����ݿ�
		for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
			(*pData)[i - sizeof_Node_Info] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];

		//����ȡ�������ݿ����Ϣ��Ϊ����ֵ
		*iDataBlockID = Node_Info.iDataBlockID;
		*iDataBlockState = Node_Info.iDataBlockState;

		//���¶�����Ϣ�ڵ��е���Ӧ����
		//�޸Ŀ��ÿռ�
		p_Info->iAvailable = p_Info->iAvailable + (Node_Info.iDataBlockSize + sizeof(SMM_Node_Info));
		//����ǰ��ָ������Ӧƫ��
		p_Info->offsetRead = (p_Info->offsetRead + (Node_Info.iDataBlockSize + sizeof(SMM_Node_Info))) % p_Info->iDimension;


		LeaveCriticalSection(&p_Info->cs);
		LeaveCriticalSection(&Queue_Info.cs);
		//���ض�ȡ�����ݵ��ֽ���
		return Node_Info.iDataBlockSize;
	}

	//����Ϊ����ʱ
	else if(p_Info->iMode == ITBDQ_BLOCK_YES)
	{
		EnterCriticalSection(&p_Info->cs_read);
		//��¼�Ѿ�д������ݵ��ֽ���
		int iData_Read = 0;
		SMM_INT tDataBlockID;
		SMM_INT flagDataBlockIDchange = 0;

		while(true)
		{
			if(p_Info->iDimension - p_Info->iAvailable <= sizeof_Node_Info)
			{
				LeaveCriticalSection(&Queue_Info.cs);
				Sleep(0);
				EnterCriticalSection(&Queue_Info.cs);
				continue;
			}

			EnterCriticalSection(&p_Info->cs);

			offsetRead = p_Info->offsetRead;

			LeaveCriticalSection(&Queue_Info.cs);

			i = 0;
			//����
			//�ȶ���Ϣͷ
			for(; i < sizeof_Node_Info; i++)
				((SMM_UCHAR*)&Node_Info)[i] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];


			//����������������һ�����ݿ�
			if(0 == Node_Info.iDataBlockID && Node_Info.iDataBlockState == -1)
			{
				if(flagDataBlockIDchange == 1)
				{
					LeaveCriticalSection(&p_Info->cs);
					break;
				}
				//�����ݴ����ݿ��õĿռ�
				*pData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize);
			}
			//�����������ݿ��ǵ�һ�飬�Ҳ�����
			else if(Node_Info.iDataBlockState == 1 && Node_Info.iDataBlockID != 0)
			{
				if(flagDataBlockIDchange == 1)
				{
					LeaveCriticalSection(&p_Info->cs);
					break;
				}
				flagDataBlockIDchange = 1;
				tDataBlockID = Node_Info.iDataBlockID;
				//�����ݴ����ݿ��õĿռ�
				*pData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize);
			}
			//�����������м��
			else if(tDataBlockID == Node_Info.iDataBlockID && Node_Info.iDataBlockState == 0)
			{
				//���¿����ݴ����ݿ��õĿռ�
				*pData = (SMM_UCHAR*)realloc(*pData, sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize + iData_Read);
			}
			//�������������һ��
			else if(tDataBlockID == Node_Info.iDataBlockID && Node_Info.iDataBlockState == -1)
			{
				//���¿����ݴ����ݿ��õĿռ�
				*pData = (SMM_UCHAR*)realloc(*pData, sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize + iData_Read);
			}
			//�������ݿ��Ǵ���
			else
			{
				LeaveCriticalSection(&p_Info->cs);
				LeaveCriticalSection(&p_Info->cs_read);
				return -6;
			}

			//�ٶ����ݿ�
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
				(*pData)[iData_Read++] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];

			LeaveCriticalSection(&p_Info->cs);

			EnterCriticalSection(&Queue_Info.cs);

			//���¶�����Ϣ�ڵ��е���Ӧ����
			//�޸Ŀ��ÿռ�
			p_Info->iAvailable = p_Info->iAvailable + (Node_Info.iDataBlockSize + sizeof_Node_Info);
			//����ǰ��ָ������Ӧƫ��
			p_Info->offsetRead = (p_Info->offsetRead + (Node_Info.iDataBlockSize + sizeof_Node_Info)) % p_Info->iDimension;

			if(Node_Info.iDataBlockState == -1)
			{
				LeaveCriticalSection(&Queue_Info.cs);
				break;
			}

		}
		//��Ϊ����ֵ���������ݿ�ķ���ֵ
		*iDataBlockID = 0;
		*iDataBlockState = -1;

		LeaveCriticalSection(&p_Info->cs_read);

		//���ض�ȡ�����ݵ��ֽ���
		return iData_Read;
	}
	else
	{
		LeaveCriticalSection(&p_Info->cs_read);
		//���ض���ģʽ���ô���
		return -5;
	}
}
