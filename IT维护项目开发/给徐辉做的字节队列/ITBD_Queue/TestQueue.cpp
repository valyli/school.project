#include "ITBD_Queue.h"


DWORD WINAPI WriteProc(LPVOID lpParameter)
{
	SMM_INT ret;
	//≤‚ ‘–¥
	char buff[11];
	strcpy(buff, "01234567");
	SMM_INT iDataBlockID;
	while(true)
	{
		ret = ITBDQ_Write(1, (SMM_UCHAR*)buff, 10, &iDataBlockID);
		printf("#QUEUE<<<<<<<<W           ret:%d            iDataBlockID:%d\n", ret, iDataBlockID);
//		printf("ITDQ_Write's return value:%d\n", ret);
//		printf("iDataBlockID value:%d\n\n", iDataBlockID);
//		if(ret < 0)
//			Sleep(1000);
		Sleep(0);
	}
		return 0;
}

DWORD WINAPI ReadProc(LPVOID lpParameter)
{
	SMM_INT ret;
	//≤‚ ‘∂¡
	SMM_UCHAR* pResult;
	SMM_INT iDataBlockState;
	SMM_INT iDataBlockID;
	while(true)
	{
		ret = ITBDQ_Read(1, &pResult, &iDataBlockID, &iDataBlockState);
		printf("#QUEUE>>>>>>>R         ret:%d        string:%s\n", ret, (char*)pResult);
/*		printf("ITBDQ_Read's return value:%d\n", ret);
		printf("iDataBlockID value:%d\n", iDataBlockID);
		printf("iDataBlockState value:%d\n\n", iDataBlockState);
		printf("DataBlock string:%s\n", (char*)pResult);
*/		free(pResult);
//		if(ret < 0)
			Sleep(0);
	}
		return 0;
}


DWORD WINAPI CreateProc(LPVOID lpParameter)
{
	SMM_INT ret;
	//≤‚ ‘Ω®
	while(true)
	{
		ret = ITBDQ_Create(5, ITBDQ_BLOCK_NO);
		printf(">>>>>>>>>>>>>ITBDQ_Create's return value:%d\n", ret);
		Sleep(0);
	}
	return 0;
}

DWORD WINAPI DeleteProc(LPVOID lpParameter)
{
	SMM_INT ret, id;
	//≤‚ ‘…æ
	while(true)
	{
		id = (SMM_INT)(ITBDQ_Count() * (rand()/(double)(RAND_MAX)));
		if(id != 0)
		{
			ret = ITBDQ_Delete(id);
			if(ret == 1)
				printf("id = %d<<<<<<<<<<<<<<<<ITBDQ_Delete's return value:%d\n", id, ret);
			Sleep(0);
		}
		Sleep(0);
	}
	return 0;
}



int main()
{
	printf("Test Queue\n");
	ITBDQ_Init();
	SMM_INT ret;
	SMM_INT iID;
	ret = ITBDQ_Create(17, ITBDQ_BLOCK_NO);		//22
	printf("ITBDQ_Create's return value:%d\n", ret);
	ret = ITBDQ_Create(5, ITBDQ_BLOCK_NO);
	printf("ITBDQ_Create's return value:%d\n", ret);
	ret = ITBDQ_Create(5, ITBDQ_BLOCK_NO);
	printf("ITBDQ_Create's return value:%d\n", ret);
	if(ret != -1)
	{
		//≤‚ ‘–¥
		char buff[10];
		strcpy(buff, "asdf");
		SMM_INT iDataBlockID;
		ret = ITBDQ_Write(1, (SMM_UCHAR*)buff, 10, &iDataBlockID);
		printf("ITDQ_Write's return value:%d\n", ret);
		printf("iDataBlockID value:%d\n", iDataBlockID);

//		ret = ITBDQ_Delete(1);
//		printf("ITBDQ_Delete's return value:%d\n", ret);

		//≤‚ ‘∂¡
		SMM_UCHAR* pResult;
		SMM_INT iDataBlockState;
		ret = ITBDQ_Read(1, &pResult, &iDataBlockID, &iDataBlockState);
		printf("ITBDQ_Read's return value:%d\n", ret);
		printf("iDataBlockID value:%d\n", iDataBlockID);
		printf("iDataBlockState value:%d\n", iDataBlockState);
		printf("DataBlock string:%s\n", (char*)pResult);

		iID = ret;
		ret = ITBDQ_Delete(2);
		printf("ITBDQ_Delete's return value:%d\n", ret);
		ret = ITBDQ_Create(5, ITBDQ_BLOCK_NO);
		printf("ITBDQ_Create's return value:%d\n", ret);
		ret = ITBDQ_Delete(1);
		printf("ITBDQ_Delete's return value:%d\n", ret);
		ret = ITBDQ_Delete(3);
		printf("ITBDQ_Delete's return value:%d\n", ret);
		ret = ITBDQ_Delete(0);
		printf("ITBDQ_Delete's return value:%d\n", ret);
	}
/*
	//‘⁄œﬂ≥Ã÷–≤‚ ‘∂¡–¥
	printf("\n\nTest W&R in thread(ITBDQ_BLOCK_YES)\n");
	ret = ITBDQ_Create(24, ITBDQ_BLOCK_YES);		//22
	iID = ret;
	printf("ITBDQ_Create's return value:%d\n", ret);

	HANDLE hWriteProc;
	HANDLE hReadProc;
	hWriteProc = CreateThread(NULL,0,WriteProc,NULL,0,NULL);
	hReadProc = CreateThread(NULL,0,ReadProc,NULL,0,NULL);

	printf("press enter to stop\n");
	getchar();

	TerminateThread(hWriteProc, 0);
	TerminateThread(hReadProc, 0);

	ret = ITBDQ_Delete(iID);
	printf("ITBDQ_Delete's return value:%d\n", ret);


	//‘⁄œﬂ≥Ã÷–≤‚ ‘¥¥Ω®∫Õ…æ≥˝∂”¡–
	printf("\n\nTest C&D in thread\n");
	HANDLE hCreateProc;
	HANDLE hDeleteProc;
	hCreateProc = CreateThread(NULL,0,CreateProc,NULL,0,NULL);
	hDeleteProc = CreateThread(NULL,0,DeleteProc,NULL,0,NULL);

	printf("press enter to stop\n");
	getchar();

	TerminateThread(hCreateProc, 0);
	TerminateThread(hDeleteProc, 0);

*/	printf("stop......................\n");
	SMM_INT id = ITBDQ_Count();
	while(id != 0)
	{
		ret = ITBDQ_Delete(id);
		printf("id = %d<<<<<<<<<<<<<<<<ITBDQ_Delete's return value:%d\n", id, ret);
		id--;
	}

	return 0;
}
