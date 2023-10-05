/*************************************************************
  Copyright (C)
  File name:  
  Author: 
  Version:  
  Date: 2003-3-28
  Description:    此文件是对多线程通信的测试程序
  Others:           
  Function List:  
  (1)ITDQ_int
  (2)IDDQ_CreateQueue
  (3)ITDQ_Read
  (4)ITDQ_Write
  (5)ITDQ_Delete
  History:          
    1. Date:   2003-04-01
       Author: xuhui
       Modification: First version
    2. ...
**************************************************************/
#include "stdafx.h"
#include "test.h"

#include "Base.h"
#include "ManageData.h"


//#include "smm_type.h"


#define  Data_Size     256
DWORD WINAPI DriverProc(LPVOID lpParameter);					// Driver线程声明
DWORD WINAPI ComProc(LPVOID lpParameter);						// 通信线程声明
CRITICAL_SECTION cs;
SMM_INT  iID[4];													//队列ID
SMM_CHAR *pSize=(char*)malloc(sizeof(Data_Size));
//SMM_CHAR pData[1][Data_Size];
int main(int argc, char* argv[])
{
	ITDQ_Init();
	iID[0]=ITDQ_Create(1,Data_Size);
	iID[1]=ITDQ_Create(1,Data_Size);
	iID[2]=ITDQ_Create(1,Data_Size);
	iID[3]=ITDQ_Create(1,Data_Size);
	InitializeCriticalSection(&cs);
	CreateThread(NULL,0,DriverProc,NULL,0,NULL);				//创建Driver线程
//	Sleep(1000);
	CreateThread(NULL,0,ComProc,NULL,0,NULL);					//创建通信线程
	Sleep(3000);
	DeleteCriticalSection(&cs);
	return 1;
}

DWORD WINAPI DriverProc(LPVOID lpParameter)
{
	EnterCriticalSection(&cs);


/////////////////////////////////////////////////////////////////////////////////
//需要导入文件：Base.h、CClientModuleTransfer.dll
	//导入CClientModuleTransfer模块的动态联接库
	HMODULE hLibrary=LoadLibrary("CClientModuleTransfer.dll");
	if(hLibrary == NULL)
	{
		return 0;
	}
	//获取Client端当前目录下搜索所有的合法dll信息
	bool (FAR *lpfn)();
	lpfn = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientGetAllModuleInfoToMemory");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return 0;
	}
	//获取Client端指定的信息
	ModuleInfomationListStruct ModuleInfo;
	CManageData Data;
	//设定要查看的信息
	ModuleInfo.InfomationElementTableID = 1;
	ModuleInfo.InfomationElementID = 1;
	//设置参数值
	CString temp = _T("Test Data");
	Data.SetData(temp);
	bool (FAR *lpfn1)(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
	lpfn1 = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientTransferModule");
	if(lpfn1 == NULL)
	{
		FreeLibrary(hLibrary);
		return 0;
	}

	//写入队列
	SMM_INT  iWrite=ITDQ_Write(iID[1],pSize);
	printf("iWrite=%d\n",iWrite2);

	FreeLibrary(hLibrary);
	return 1;
/////////////////////////////////////////////////////////////////////////////////




//	int n = 0;
/*	for(int i=0; i<10 ; i++)
	{
		for(int  j = 0;j < Data_Size;j++)
		{
			pSize[i][j]= n++;
		}
	}*/
/*	SMM_INT  iWrite1=ITDQ_Write(iID[0],pSize);
	printf("iWrite1=%d\n",iWrite1);
	SMM_INT  iWrite2=ITDQ_Write(iID[1],pSize);
	printf("iWrite2=%d\n",iWrite2);
	SMM_INT  iWrite3=ITDQ_Write(iID[2],pSize);
	printf("iWrite3=%d\n",iWrite3);
	SMM_INT  iWrite4=ITDQ_Write(iID[3],pSize);
	printf("iWrite4=%d\n",iWrite4);
	strcpy(pSize,"Hello!!!");
	printf("%s\n",pSize);
	*/
/*	strcpy(pSize,"Test!!!");
	ITDQ_Write(iID[0],pSize);	
	printf("%s\n",pSize);
	SMM_INT iWrite3=ITDQ_Write(iID[0],pSize);
	printf("iWrite3=%d\n",iWrite3);	
	ITDQ_Write(iID[0],pSize);*/

	LeaveCriticalSection(&cs);
	return 1;
}

DWORD WINAPI ComProc(LPVOID lpParameter)
{
	EnterCriticalSection(&cs);
	int n = 0;
/*	for(int i=0; i<10 ; i++)
	{
		for(int  j = 0;j < Data_Size;j++)
		{
			printf("%d ",pSize[i][j]);
		}
	}*/
	SMM_INT  iRead=ITDQ_Read(iID[0],pSize);
	printf("iRead1=%d\n",iRead);
	SMM_INT  iRead2=ITDQ_Read(iID[1],pSize);
	printf("iRead2=%d\n",iRead);
	SMM_INT  iRead3=ITDQ_Read(iID[2],pSize);
	printf("iRead3=%d\n",iRead);
	SMM_INT  iRead4=ITDQ_Read(iID[3],pSize);
	printf("iRead4=%d\n",iRead);
//	ITDQ_Read(iID[0],pSize);
//	printf("%s\n",pSize);
//	ITDQ_Read(iID[0],pSize);
//	printf("%s",pSize);
//	LeaveCriticalSection(&cs);
	return 1;
}

