#include "ITBD_Queue.h"



SMM_Queue_Info Queue_Info; 					//定义链表的头节点



/*********************************************************
  Function:       ITDQ_Init
  Description:    初始化头节点
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Input:          无	


  Output:         
  Return:

  Others:        
***********************************************************/
void ITBDQ_Init()
{
		Queue_Info.iID=0;
		Queue_Info.iDimension = DEFAULT_QUEUE_MAX;		//队列最大数量			
		Queue_Info.iAvailable = 0;						//当前队列数量
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
在一条队列中做基址编址运算，只允许非负整数偏移量，基址取自SMM_Queue_Info
*/
SMM_UCHAR* ITBDQ_WorkOutPointer(SMM_Queue_Info* pQueue_Info, SMM_INT offset)
{
	//如果偏移量不合理，返回NULL
	if((int)(offset / (double)pQueue_Info->iDimension) >= 2
		|| offset < 0)
		return NULL;
	if(pQueue_Info->pBase == NULL)
		return NULL;

	return pQueue_Info->pBase + (offset % pQueue_Info->iDimension);
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
  Description:    利用信息链表创建队列
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
SMM_INT ITBDQ_Create(SMM_UINT iDimension = DEFAULT_DIMENSION, SMM_INT iMode = ITBDQ_BLOCK_NO)
{	
	//使指针p_Info指向节点
	SMM_Queue_Info* p_Info_pre, *p_Info_temp, *p_Info = &Queue_Info;
	//锁队列信息链表
	EnterCriticalSection(&Queue_Info.cs);

	//判断队列条数是否已达最大值
	if(p_Info->iAvailable >= p_Info->iDimension)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -3;
	}

	//创建队列的存储空间
	SMM_UCHAR* pBase;
	if(FALSE == ITBDQ_CreateQueue(&pBase, iDimension))
	{
		printf("Create queue error\n");
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}

/*	//从头节点查起，找到队列信息链表最后节点，确定当前队列数量
	p_Info_temp = &Queue_Info;
	int n = 0;
	while(p_Info_temp->pNext != NULL)
	{
		p_Info_temp = p_Info_temp->pNext;
		n++;
	}
		printf("---------------%d--------------------", n);
	//如果队列数量已达最大值，则返回队列已达最大值
	if(n >= DEFAULT_QUEUE_MAX)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -3;
	}
*/
	//获取新队列的ID值，此值为递增可复用，应从1起
	//要保持队列信息链表中的ID值的单增
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

	p_Info_temp->hSemWrite = CreateSemaphore(NULL,1,1,NULL);			//创建写信号量
	p_Info_temp->hSemRead = CreateSemaphore(NULL,0,1,NULL);			//创建读信号量
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
SMM_INT ITBDQ_Delete(SMM_INT iId)
{
	//队列ID值不合法
	if(iId <= 0)
		return -2;

	SMM_Queue_Info* p_Info_pre, *p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	//循环往下找链表信息，有对应的ID就跳出
	while(p_Info != NULL)
	{
		if(p_Info->iID==iId)
			break;
		p_Info_pre = p_Info;
		p_Info = p_Info->pNext;
	}

	//如找到对映队列
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
	//ID值所指定的队列不存在
	else
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
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

				pData:  要写入的数据块缓冲区

				iNum:   需要写入的数据块数目

				
  Output:         
  Return:        实际写入的数据块数目 

  Others:       0:	表示队列空
			  －1:  表示没有输入的ID对应的数据独列
			  -3:   表示队列满
  			
***********************************************************/
SMM_INT ITBDQ_Write(SMM_INT iId, SMM_UCHAR* pData, SMM_INT iNum, SMM_INT* iDataBlockID)
{
	//队列ID值不合法
	if(iId <= 0)
		return -2;

	//先找到要使用的队列
	SMM_Queue_Info *p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	while(p_Info != NULL)
	{
		if(p_Info->iID == iId)
			break;
		p_Info = p_Info->pNext;
	}

	//没找到对映的队列
	if(p_Info == NULL)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}

	//部分局部变量声明、初始化
	SMM_Node_Info Node_Info;						//由于暂存信息头数据
	int offsetWrite = p_Info->offsetWrite;			//获得当前写指针偏移量
	int i = 0;										//用于记录已经写过的字节数
	int sizeof_Node_Info = sizeof(Node_Info);		//记录信息头大小


	//队列为非阻塞时
	if(p_Info->iMode == ITBDQ_BLOCK_NO)
	{
		//若找到对映的队列，继续向下执行
		//如空间不足以写下一组节点信息和一个单位的数据，则返回队列满
		if(p_Info->iAvailable < (sizeof(SMM_Node_Info) + sizeof(SMM_UCHAR)))
		{
			LeaveCriticalSection(&Queue_Info.cs);
			return -3;
		}

		EnterCriticalSection(&p_Info->cs);

		//判断数据是否可以一次写入
		//如果能一次写入
		if((iNum + sizeof(SMM_Node_Info)) <= (SMM_UINT)p_Info->iAvailable)
		{
			//更新队列信息节点中的相应数据
			//修改可用空间
			p_Info->iAvailable = p_Info->iAvailable - (iNum + sizeof(SMM_Node_Info));
			*iDataBlockID = p_Info->iAvailable;				//暂时用其返回剩余空间
			//将当前写指针做相应偏移
			p_Info->offsetWrite = (p_Info->offsetWrite + (iNum + sizeof(SMM_Node_Info))) % p_Info->iDimension;

			LeaveCriticalSection(&Queue_Info.cs);

			//生成数据块信息头
			Node_Info.iDataBlockID = 0;
			Node_Info.iDataBlockState = -1;		//暂时可为任何值
			Node_Info.iDataBlockSize = iNum;

			//写入
			//先写信息头
			for(; i < sizeof_Node_Info; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
			//再写数据块
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
			{
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];
			}

			LeaveCriticalSection(&p_Info->cs);
			return 0;
		}
		//如果不能一次写入，那么能写多少就写多少，并返回写入的字节数
		else
		{
			//生成数据块信息头
			Node_Info.iDataBlockID = p_Info->iCurAvailDataBlockID;
			//标记此数据块不完整，只是开始
			Node_Info.iDataBlockState = 1;
			Node_Info.iDataBlockSize = p_Info->iAvailable - sizeof_Node_Info;
			//设定返回值iDataBlockID，使用户得知继续写入时该使用的数据块ID
			*iDataBlockID = Node_Info.iDataBlockID;

			//更新队列信息节点中的相应数据
			//修改可用空间
			//可用空间为0表示写满
			p_Info->iAvailable = 0;
			//将当前写指针做相应偏移
			//指向offsetRead即是将队列填满
			p_Info->offsetWrite = p_Info->offsetRead;
			//可用的DataBlockID自增
			//暂时先用10000，以后应作处理
			if(p_Info->iCurAvailDataBlockID == 10000 - 1)//此处防止出现iCurAvailDataBlockID ＝ 0
				p_Info->iCurAvailDataBlockID = 1;
			else
				p_Info->iCurAvailDataBlockID = (p_Info->iCurAvailDataBlockID + 1) % 10000;

			LeaveCriticalSection(&Queue_Info.cs);

			for(; i < sizeof_Node_Info; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
			//再写数据块
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];

			LeaveCriticalSection(&p_Info->cs);
			return Node_Info.iDataBlockSize;
		}
	}

	//队列为阻塞时
	else if(p_Info->iMode == ITBDQ_BLOCK_YES)
	{
		//给写控制上锁，即而不允许其它写操作介入，也防止其介入到正在进行的写操作中
		EnterCriticalSection(&p_Info->cs_write);

		//部分局部变量声明、初始化
		SMM_Node_Info Node_Info;						//由于暂存信息头数据
		int offsetWrite = p_Info->offsetWrite;			//获得当前写指针偏移量
		int i = 0;										//用于记录已经写过的字节数
		int sizeof_Node_Info = sizeof(Node_Info);		//记录信息头大小

/*		//如果数据是可以一次写入的
		if((iNum + sizeof(SMM_Node_Info)) <= (SMM_UINT)p_Info->iAvailable)
		{
			EnterCriticalSection(&p_Info->cs);

			//更新队列信息节点中的相应数据
			//修改可用空间
			p_Info->iAvailable = p_Info->iAvailable - (iNum + sizeof(SMM_Node_Info));
			printf("###############........%d\n", p_Info->iAvailable);
			*iDataBlockID = p_Info->iAvailable;				//暂时用其返回剩余空间
			//将当前写指针做相应偏移
			p_Info->offsetWrite = (p_Info->offsetWrite + (iNum + sizeof(SMM_Node_Info))) % p_Info->iDimension;

			LeaveCriticalSection(&Queue_Info.cs);

			//生成数据块信息头
			Node_Info.iDataBlockID = 0;
			Node_Info.iDataBlockState = -1;		//暂时可为任何值
			Node_Info.iDataBlockSize = iNum;

			//写入
			//先写信息头
			for(; i < sizeof_Node_Info; i++)
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
			//再写数据块
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
			{
				p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];
			}

			LeaveCriticalSection(&p_Info->cs_write);
			LeaveCriticalSection(&p_Info->cs);
			return 0;
		}
		//如果数据无法一次写入
		else
		{
*/			SMM_UCHAR* pTempData;		//临时存储区
			//建立临时存储区
			pTempData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * iNum);
			//将所有数据先导入临时数据区
			for(i = 0; i < iNum; i++)
			{
				pTempData[i] = pData[i];
			}


			//记录已经写入的数据的字节数
			int iData_Writen = 0;

			//第一页标记
			int FirstPageFlag = 1;

			while(iNum != iData_Writen)
			{
				//检查是否有足够的空间写入数据
				if(p_Info->iAvailable <= sizeof_Node_Info)
				{
					LeaveCriticalSection(&Queue_Info.cs);
					Sleep(0);
					EnterCriticalSection(&Queue_Info.cs);
					continue;
				}

				//获得当前写指针偏移量
				offsetWrite = p_Info->offsetWrite;

				//如果是第一次写数据
				if(FirstPageFlag == 1)
				{
					//如果新得到的空间可以将所有数据一次写入
					if(p_Info->iAvailable - sizeof_Node_Info >= iNum)
					{
						i = 0;
						//更新队列信息节点中的相应数据
						//修改可用空间
						p_Info->iAvailable = p_Info->iAvailable - (iNum + sizeof(SMM_Node_Info));
//						printf("$$$$$$$$$$$$$$$........%d\n", p_Info->iAvailable);
						*iDataBlockID = p_Info->iAvailable;				//暂时用其返回剩余空间
						//将当前写指针做相应偏移
						p_Info->offsetWrite = (p_Info->offsetWrite + (iNum + sizeof(SMM_Node_Info))) % p_Info->iDimension;
							EnterCriticalSection(&p_Info->cs);

						LeaveCriticalSection(&Queue_Info.cs);

						//生成数据块信息头
						Node_Info.iDataBlockID = 0;
						Node_Info.iDataBlockState = -1;		//暂时可为任何值
						Node_Info.iDataBlockSize = iNum;

						//写入
						//先写信息头
						for(; i < sizeof_Node_Info; i++)
							p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
						//再写数据块
						for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
						{
							p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[i - sizeof_Node_Info];
						}

						LeaveCriticalSection(&p_Info->cs_write);
						LeaveCriticalSection(&p_Info->cs);
						return 0;
					}

					//如果得到的空间不能将所有数据一次写入
					else
					{
						//生成数据块信息头中的iDataBlockID
						Node_Info.iDataBlockID = p_Info->iCurAvailDataBlockID;
						//可用的DataBlockID自增
						//暂时先用10000，以后应作处理
						if(p_Info->iCurAvailDataBlockID == 10000 - 1)//此处防止出现iCurAvailDataBlockID ＝ 0
							p_Info->iCurAvailDataBlockID = 1;
						else
							p_Info->iCurAvailDataBlockID = (p_Info->iCurAvailDataBlockID + 1) % 10000;
						//设定返回值iDataBlockID，使用户得知继续写入时该使用的数据块ID
						*iDataBlockID = Node_Info.iDataBlockID;

						Node_Info.iDataBlockSize = p_Info->iAvailable - sizeof_Node_Info;
						//更新队列信息节点中的相应数据
						//修改可用空间
						//可用空间为0表示写满
						p_Info->iAvailable = 0;
						//将当前写指针做相应偏移
						//指向offsetRead即是将队列填满
						p_Info->offsetWrite = p_Info->offsetRead;

						//标记此数据块（只是第一个）不完整，只是开始
						Node_Info.iDataBlockState = 1;
						FirstPageFlag = 0;
					}
				}

				//设定要写入的数据块的大小
				//如果剩余空间>=剩余的数据，则设定iDataBlockSize为剩余数据大小
				else if(p_Info->iAvailable - sizeof_Node_Info >= iNum - iData_Writen)
				{
//				printf("write iAvailable:%d, inum-idata:%d\n", p_Info->iAvailable, iNum - iData_Writen);
					Node_Info.iDataBlockSize = iNum - iData_Writen;
					//标记此数据块不完整，是结束块
					Node_Info.iDataBlockState = -1;
					//更新队列信息节点中的相应数据
					//修改可用空间
					p_Info->iAvailable = p_Info->iAvailable - ((iNum - iData_Writen) + sizeof_Node_Info);
					//将当前写指针做相应偏移
					p_Info->offsetWrite = (p_Info->offsetWrite + ((iNum - iData_Writen) + sizeof_Node_Info)) % p_Info->iDimension;
				}
				//否则，填满可用空间
				else
				{
					Node_Info.iDataBlockSize = p_Info->iAvailable - sizeof_Node_Info;
					//标记此数据块不完整，是中间的一个
					Node_Info.iDataBlockState = 0;
					//更新队列信息节点中的相应数据
					//修改可用空间
					//可用空间为0表示写满
					p_Info->iAvailable = 0;
					//将当前写指针做相应偏移
					//指向offsetRead即是将队列填满
					p_Info->offsetWrite = p_Info->offsetRead;
				}				
				
				EnterCriticalSection(&p_Info->cs);

				//暂时释放队列信息链表
				LeaveCriticalSection(&Queue_Info.cs);

				//将CPU出让给系统进行调度
				Sleep(0);

				//写入部分数据到队列中
				i = 0;
				//先写信息头
				for(; i < sizeof_Node_Info; i++)
					p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = ((SMM_UCHAR*)&Node_Info)[i];
				//再写数据块
				for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
					p_Info->pBase[(offsetWrite + i) % p_Info->iDimension] = pData[iData_Writen++];

				//暂时释放队列链表
				LeaveCriticalSection(&p_Info->cs);

				if(iNum == iData_Writen)
					break;

				//将CPU出让给系统进行调度
				Sleep(0);

				EnterCriticalSection(&Queue_Info.cs);


			}

			//返回多页写入成功
			LeaveCriticalSection(&p_Info->cs_write);
			return -100;
	}
	else
	{
		LeaveCriticalSection(&p_Info->cs_write);
		//返回队列模式设置错误
		return -5;
	}
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

				pData:  队列的数据缓冲区

				iNum:   需要读取的数据块数目
				
  Output:         
  Return:        实际读取的数据块数目 

  Others:       0:	表示队列空
			  －1:  表示没有输入的ID对应的数据独列
			   -4:  表示队列为空
			
***********************************************************/
SMM_INT ITBDQ_Read(SMM_INT iId, SMM_UCHAR** pData, SMM_INT* iDataBlockID, SMM_INT* iDataBlockState)
{
	//队列ID值不合法
	if(iId <= 0)
		return -2;

	//先找到要使用的队列
	SMM_Queue_Info *p_Info = &Queue_Info;
	EnterCriticalSection(&Queue_Info.cs);
	while(p_Info != NULL)
	{
		if(p_Info->iID == iId)
			break;
		p_Info = p_Info->pNext;
	}

	//没找到对映的队列
	if(p_Info == NULL)
	{
		LeaveCriticalSection(&Queue_Info.cs);
		return -1;
	}

	//部分局部变量声明、初始化
	SMM_Node_Info Node_Info;						//由于暂存信息头数据
	int offsetRead = p_Info->offsetRead;			//获得当前写指针偏移量
	int i = 0;										//用于记录已经读过的字节数
	int sizeof_Node_Info = sizeof(Node_Info);		//记录信息头大小

	//队列为非阻塞时
	if(p_Info->iMode == ITBDQ_BLOCK_NO)
	{
		//若找到对映的队列，继续向下执行
		//如果已用空间小于一组节点信息和一个单位的数据，则返回队列空
		if((p_Info->iDimension - p_Info->iAvailable) < (sizeof(SMM_Node_Info) + sizeof(SMM_UCHAR)))
		{
			LeaveCriticalSection(&Queue_Info.cs);
			return -3;
		}

		EnterCriticalSection(&p_Info->cs);


		//读出
		//先读信息头
		for(; i < sizeof_Node_Info; i++)
			((SMM_UCHAR*)&Node_Info)[i] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];
		//开辟暂存数据块用的空间
		*pData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize);
		//再读数据块
		for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
			(*pData)[i - sizeof_Node_Info] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];

		//将读取到的数据块的信息设为返回值
		*iDataBlockID = Node_Info.iDataBlockID;
		*iDataBlockState = Node_Info.iDataBlockState;

		//更新队列信息节点中的相应数据
		//修改可用空间
		p_Info->iAvailable = p_Info->iAvailable + (Node_Info.iDataBlockSize + sizeof(SMM_Node_Info));
		//将当前读指针做相应偏移
		p_Info->offsetRead = (p_Info->offsetRead + (Node_Info.iDataBlockSize + sizeof(SMM_Node_Info))) % p_Info->iDimension;


		LeaveCriticalSection(&p_Info->cs);
		LeaveCriticalSection(&Queue_Info.cs);
		//返回读取的数据的字节数
		return Node_Info.iDataBlockSize;
	}

	//队列为阻塞时
	else if(p_Info->iMode == ITBDQ_BLOCK_YES)
	{
		EnterCriticalSection(&p_Info->cs_read);
		//记录已经写入的数据的字节数
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
			//读出
			//先读信息头
			for(; i < sizeof_Node_Info; i++)
				((SMM_UCHAR*)&Node_Info)[i] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];


			//如果读入的是完整的一个数据块
			if(0 == Node_Info.iDataBlockID && Node_Info.iDataBlockState == -1)
			{
				if(flagDataBlockIDchange == 1)
				{
					LeaveCriticalSection(&p_Info->cs);
					break;
				}
				//开辟暂存数据块用的空间
				*pData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize);
			}
			//如果读入的数据块是第一块，且不完整
			else if(Node_Info.iDataBlockState == 1 && Node_Info.iDataBlockID != 0)
			{
				if(flagDataBlockIDchange == 1)
				{
					LeaveCriticalSection(&p_Info->cs);
					break;
				}
				flagDataBlockIDchange = 1;
				tDataBlockID = Node_Info.iDataBlockID;
				//开辟暂存数据块用的空间
				*pData = (SMM_UCHAR*)malloc(sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize);
			}
			//如果读入的是中间块
			else if(tDataBlockID == Node_Info.iDataBlockID && Node_Info.iDataBlockState == 0)
			{
				//重新开辟暂存数据块用的空间
				*pData = (SMM_UCHAR*)realloc(*pData, sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize + iData_Read);
			}
			//如果读入的是最后一块
			else if(tDataBlockID == Node_Info.iDataBlockID && Node_Info.iDataBlockState == -1)
			{
				//重新开辟暂存数据块用的空间
				*pData = (SMM_UCHAR*)realloc(*pData, sizeof(SMM_UCHAR) * Node_Info.iDataBlockSize + iData_Read);
			}
			//返回数据块标记错误
			else
			{
				LeaveCriticalSection(&p_Info->cs);
				LeaveCriticalSection(&p_Info->cs_read);
				return -6;
			}

			//再读数据块
			for(; i < sizeof_Node_Info + Node_Info.iDataBlockSize; i++)
				(*pData)[iData_Read++] = p_Info->pBase[(offsetRead + i) % p_Info->iDimension];

			LeaveCriticalSection(&p_Info->cs);

			EnterCriticalSection(&Queue_Info.cs);

			//更新队列信息节点中的相应数据
			//修改可用空间
			p_Info->iAvailable = p_Info->iAvailable + (Node_Info.iDataBlockSize + sizeof_Node_Info);
			//将当前读指针做相应偏移
			p_Info->offsetRead = (p_Info->offsetRead + (Node_Info.iDataBlockSize + sizeof_Node_Info)) % p_Info->iDimension;

			if(Node_Info.iDataBlockState == -1)
			{
				LeaveCriticalSection(&Queue_Info.cs);
				break;
			}

		}
		//设为返回值完整的数据块的返回值
		*iDataBlockID = 0;
		*iDataBlockState = -1;

		LeaveCriticalSection(&p_Info->cs_read);

		//返回读取的数据的字节数
		return iData_Read;
	}
	else
	{
		LeaveCriticalSection(&p_Info->cs_read);
		//返回队列模式设置错误
		return -5;
	}
}
