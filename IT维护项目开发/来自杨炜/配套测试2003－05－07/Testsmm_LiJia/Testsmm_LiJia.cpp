// Testsmm_LiJia.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "conio.h"

/* 这里包含SMM头文件 */
#include <smm/smm.h>

    SMM_KID  kTestThreadID_1, kTestThreadID_2;

SMM_VOID Test_Thread(int arg)
{
/*	SMM_ULONG pulState;
	printf("return value:%d, from SMM_ThreadGetState\n", SMM_ThreadGetState(kTestThreadID_1, &pulState));
	printf("State:%ld\n", pulState);
*/
	
//	printf("return value:%d, from SMM_ThreadSleep\n", SMM_ThreadSleep(1000));


	while(true)
	{
		Sleep(arg);
		if(arg == 100)
			printf("1");
		else
			printf("2");
	}
}


SMM_VOID Test_Thread_Count(int arg)
{
	unsigned int t = 1;
	while(true)
	{
		printf("%d ", t);
		if(t <= 1000)
			t++;
		else
			t = 1;
		Sleep(10);
	}
}

int n;

SMM_VOID Test_Thread_Restart(SMM_UINT arg)
{
	n++;
	printf("arg = %d\n", arg);
}

SMM_VOID Test_ReadEventThread(int arg)
{
	SMM_UINT32 ui32ReadEvents;
	SMM_UINT32 pui32ReturnEvents;
	ui32ReadEvents = 0x00000011;
/*	while(SMM_EventRead(ui32ReadEvents, &pui32ReturnEvents, SMM_EVNT_MODE_ALL, SMM_WAIT_NONE))
	{
		printf("%o", pui32ReturnEvents);
		pui32ReturnEvents = 0;
		Sleep(100);
		printf(".");
//	printf("return value:%d, from SMM_EventRead\n", SMM_EventRead(ui32ReadEvents, &pui32ReturnEvents, SMM_EVNT_MODE_ALL, SMM_WAIT_INFINITE));
	}
	printf("Read Event Success\n");
*/	ui32ReadEvents = 0x00010000;
	while(true)
	{
		Sleep(100);
	printf("return value:%d, from SMM_EventRead\n", SMM_EventRead(ui32ReadEvents, &pui32ReturnEvents, SMM_EVNT_MODE_ALL, SMM_WAIT_NONE));
		printf("%o", pui32ReturnEvents);
//	printf("Read Event Success\n");
	}
//	printf("return value:%d, from SMM_EventRead\n", SMM_EventRead(ui32ReadEvents, &pui32ReturnEvents, SMM_EVNT_MODE_ALL, SMM_WAIT_INFINITE));
	
}


SMM_VOID Test_Thread_GetCurrentThreadID(int arg)
{
	SMM_KID pkID;
	printf("return value:%d, from SMM_ThreadGetMyID\n", SMM_ThreadGetMyID(&pkID));
	printf("Thread ID = %ld-%ld\n", SMM_U64_HI(pkID), SMM_U64_LO(pkID));
}



int main(int argc, char* argv[])
{
//	char buff[100];
	printf("Begin Test>>>>>>>>>>>");

    printf( "\nSMM Kernel Initialized ... " );
    if( SMM_OK == SMM_Init() )
    {
        printf( "OK\n" );
    }
    else
    {
        printf( "FAIL\n" );
    }


/*
	SMM_UINT8 pui8Priority;
	for(int i = -100; i <= 355; i+=10)
	{
    SMM_KID_SETNUL(kTestThreadID_1);
	printf("return value:%d; Priority input = %d\n", SMM_ThreadCreate("MyThread_1", i, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1), i);
	SMM_ThreadGetPriority(kTestThreadID_1, &pui8Priority);
	printf("Priority = %d\n", pui8Priority);
	printf("Thread ID = %ld-%ld\n", SMM_U64_HI(kTestThreadID_1), SMM_U64_LO(kTestThreadID_1));
	SMM_ThreadDelete(kTestThreadID_1);
	}
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 200, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadDelete(kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadDelete(kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadDelete(kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 1, (SMM_THREAD_ENTRY)Test_Thread_Restart, &kTestThreadID_1));
	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadRestart(kTestThreadID_1, 2));
	Sleep(1000);
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadSuspend(kTestThreadID_1));
	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadResume(kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadSuspend(kTestThreadID_1));
	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadSuspend(kTestThreadID_1));

	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadResume(kTestThreadID_1));
	Sleep(1000);
	printf("return value:%d\n", SMM_ThreadResume(kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d, from Main Thread Sleep\n", SMM_ThreadSleep(1000));
*/
/*
	SMM_UINT8 pui8Priority;
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadGetPriority(kTestThreadID_1, &pui8Priority));
	printf("Priority = %d\n", pui8Priority);
*/
/*
	SMM_UINT8 pui8Priority;
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadSetPriority(kTestThreadID_1, 50));
	printf("return value:%d\n", SMM_ThreadGetPriority(kTestThreadID_1, &pui8Priority));
	printf("Priority = %d\n", pui8Priority);
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread_GetCurrentThreadID, &kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
    SMM_KID_SETNUL(kTestThreadID_1);
	printf("return value:%d, from SMM_ThreadGetMyID\n", SMM_ThreadGetMyID(&kTestThreadID_1));
	printf("Thread ID = %ld-%ld\n", SMM_U64_HI(kTestThreadID_1), SMM_U64_LO(kTestThreadID_1));
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
    SMM_KID_SETNUL(kTestThreadID_1);
	printf("return value:%d, from SMM_ThreadGetID\n", SMM_ThreadGetID("MyThread_2", &kTestThreadID_1));
	printf("Thread ID = %ld-%ld\n", SMM_U64_HI(kTestThreadID_1), SMM_U64_LO(kTestThreadID_1));
*/
/*
	SMM_CHAR str[256];
	strcpy(str, "NOT FOUND");
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
    SMM_KID_SETNUL(kTestThreadID_1);
	printf("return value:%d, from SMM_ThreadGetName\n", SMM_ThreadGetName(kTestThreadID_1, str));
	printf("%s\n", str);
*/
/*
	SMM_ULONG pulState;
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	Sleep(100);
	printf("return value:%d, from SMM_ThreadGetState\n", SMM_ThreadSuspend(kTestThreadID_1));
	printf("return value:%d, from SMM_ThreadGetState\n", SMM_ThreadGetState(kTestThreadID_1, &pulState));
	printf("State:%ld\n", pulState);
*/
/*
	SMM_BOOL pbAlive;
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
	printf("return value:%d\n", SMM_ThreadDelete(kTestThreadID_1));
	printf("return value:%d, from SMM_ThreadGetAlive\n", SMM_ThreadIsAlive(kTestThreadID_1, &pbAlive));
	printf("pbAlive:%ld\n", pbAlive);
*/
/*
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_1));
//	printf("return value:%d\n", SMM_ThreadDelete(kTestThreadID_1));
	printf("return value:%d, from SMM_ThreadIsValid\n", SMM_ThreadIsValid(kTestThreadID_1));
*/
/*
	printf("return value:%d from SMM_ThreadCreate\n", SMM_ThreadCreate("MyThread_1", 100, 0, 0, 100, (SMM_THREAD_ENTRY)Test_ReadEventThread, &kTestThreadID_1));
	Sleep(1000);
//    SMM_KID_SETNUL(kTestThreadID_1);
	printf("return value:%d from SMM_EventWrite\n", SMM_EventWrite(kTestThreadID_1, 0x00000001));
	Sleep(1000);
//	printf("return value:%d\n", SMM_ThreadSuspend(kTestThreadID_1));

	printf("return value:%d from SMM_EventWrite\n", SMM_EventWrite(kTestThreadID_1, 0x00000011));
*/
/*
	SMM_TIME_S pstTime;
	printf("return value:%d from SMM_TimeGetGMT\n", SMM_TimeGetGMT(&pstTime));
	printf("m_ui16Year:%d\n", pstTime.m_ui16Year);
	printf("m_ui8Month:%d\n", pstTime.m_ui8Month);
	printf("m_ui8Week:%d\n", pstTime.m_ui8Week);
	printf("m_ui8Day:%d\n", pstTime.m_ui8Day);
	printf("m_ui8Hour:%d\n", pstTime.m_ui8Hour);
	printf("m_ui8Minute:%d\n", pstTime.m_ui8Minute);
	printf("m_ui8Second:%d\n", pstTime.m_ui8Second);
	printf("m_ui16Milliseconds:%d\n", pstTime.m_ui16Milliseconds);

	printf("return value:%d from SMM_TimeSetGMT\n", SMM_TimeSetGMT(&pstTime));
*/
/*
	SMM_TIME_S pstTime;
	printf("return value:%d from SMM_TimeGetLocal\n", SMM_TimeGetLocal(&pstTime));
	printf("m_ui16Year:%d\n", pstTime.m_ui16Year);
	printf("m_ui8Month:%d\n", pstTime.m_ui8Month);
	printf("m_ui8Week:%d\n", pstTime.m_ui8Week);
	printf("m_ui8Day:%d\n", pstTime.m_ui8Day);
	printf("m_ui8Hour:%d\n", pstTime.m_ui8Hour);
	printf("m_ui8Minute:%d\n", pstTime.m_ui8Minute);
	printf("m_ui8Second:%d\n", pstTime.m_ui8Second);
	printf("m_ui16Milliseconds:%d\n", pstTime.m_ui16Milliseconds);

	printf("return value:%d from SMM_TimeSetLocal\n", SMM_TimeSetLocal(&pstTime));
*/
/*
	SMM_UINT64 pui64Time;
	printf("return value:%d from SMM_TimeGetElapse\n", SMM_TimeGetElapse(&pui64Time));
	printf("Elapse Time = %ld\n", pui64Time);
	printf("Elapse Time = %ld-%ld\n", SMM_U64_HI(pui64Time), SMM_U64_LO(pui64Time));
*/
/*
	SMM_TIME_S pstTime;
	SMM_UINT64 pui64Time;
	printf("return value:%d from SMM_TimeGetLocal\n", SMM_TimeGetLocal(&pstTime));
	SMM_TimeSysToMsec(&pstTime, &pui64Time);
	printf("Time = %ld-%ld\n", SMM_U64_HI(pui64Time), SMM_U64_LO(pui64Time));
*/

/*
	SMM_TIME_S pstTime;
	SMM_UINT64 pui64Time;
	printf("return value:%d from SMM_TimeGetLocal\n", SMM_TimeGetLocal(&pstTime));
	SMM_TimeSysToMsec(&pstTime, &pui64Time);
	SMM_TimeMsecToSys(&pui64Time, &pstTime);
	printf("m_ui16Year:%d\n", pstTime.m_ui16Year);
	printf("m_ui8Month:%d\n", pstTime.m_ui8Month);
	printf("m_ui8Week:%d\n", pstTime.m_ui8Week);
	printf("m_ui8Day:%d\n", pstTime.m_ui8Day);
	printf("m_ui8Hour:%d\n", pstTime.m_ui8Hour);
	printf("m_ui8Minute:%d\n", pstTime.m_ui8Minute);
	printf("m_ui8Second:%d\n", pstTime.m_ui8Second);
	printf("m_ui16Milliseconds:%d\n", pstTime.m_ui16Milliseconds);
*/

/*
	printf("return Day of week:%d from SMM_TimeGetDayOfWeek\n", SMM_TimeGetDayOfWeek(2003,4,31));
*/
/*
    SMM_KID kTiHookID1, kTiHookID2;
	SMM_KID_SETNUL(kTiHookID1);

	printf("return value:%d from SMM_TimeIsrHookIsValid\n", SMM_TimeIsrHookIsValid(kTiHookID1));
	printf("return value:%d from SMM_TimeIsrHookAdd\n", SMM_TimeIsrHookAdd(1111,Test_Thread_Restart,&kTiHookID1));
	printf("return value:%d from SMM_TimeIsrHookAdd\n", SMM_TimeIsrHookAdd(2222,Test_Thread_Restart,&kTiHookID2));
 //   printf( "\nTI-Hook (%d-%d) added.\n", SMM_U64_HI(kTiHookID1), SMM_U64_LO(kTiHookID1) );
    Sleep(1000);
	printf("return value:%d from SMM_TimeIsrHookDel\n", SMM_TimeIsrHookDel(kTiHookID1));
	printf("return value:%d from SMM_TimeIsrHookIsValid\n", SMM_TimeIsrHookIsValid(kTiHookID1));
	printf("return value:%d from SMM_TimeIsrHookDel\n", SMM_TimeIsrHookDel(kTiHookID2));
	printf("n=%d", n);
*/
/*
	SMM_INT piRet;
//	printf("return value:%d from SMM_IntLock\n", SMM_IntLock(&piRet));
	printf("piRet=%d", piRet);
	printf("return value:%d from SMM_IntUnLock\n", SMM_IntUnLock(piRet));
*/


/*
	printf("Test Mod(Compare with System _int64)\n");

	SMM_INT64 int1;
	SMM_INT64 int2;
	SMM_INT64 int3;
	long temp1;
	unsigned long temp2;
	long temp3;
	unsigned long temp4;
	long n = 0;
	_int64 sysint1;
	_int64 sysint2;
	_int64 sysint3;

	for(temp1 = -0x0fffffff; temp1 <= 0x0fffffff; temp1++)
	{
		for(temp2 = 0; temp2 <= 0xffffffff; temp2++)
		{
			SMM_I64_SET(int1, temp1, temp2);

			for(temp3 = -0x0fffffff; temp3 <= 0x0fffffff; temp3++)
			{
				for(temp4 = 0; temp4 <= 0xffffffff; temp4++)
				{
					SMM_I64_SET(int2, temp3, temp4);
					int3 = SMM_I64_MOD(int1, int2);

					*((unsigned long*)(&sysint1)) = temp2;
					*(((long*)(&sysint1))+1) = temp1;
					*((unsigned long*)(&sysint2)) = temp4;
					*(((long*)(&sysint2))+1) = temp3;
					sysint3 = sysint1 % sysint2;

					if(!(SMM_I64_HI(int3) == *(((long*)(&sysint3))+1)
						&& SMM_I64_LO(int3) == *((unsigned long*)(&sysint3))
						))
					{
						printf("\nwhen number1 is %d:%u, check 1 error\n", temp1, temp2);
						printf("\nwhen number2 is %d:%u, check 1 error\n", temp3, temp4);
						printf("Div: %8x:%8x\n", SMM_I64_HI(int3), SMM_I64_LO(int3));
						getch();
					}
					n++;
					if(n % 0x4fffff == 0)
					{
						printf("|%d:%u,%d:%u", temp1, temp2, temp3, temp4);
					}
				}
			}
		}
	}
*/
/*	SMM_INT64 int1;
	SMM_I64_SET(int1, 0xf, 0xff0);
	SMM_I64_SHL(int1, 4);
	printf("SHL: %8x:%8x\n", SMM_I64_HI(int1), SMM_I64_LO(int1));
*/
/*
	SMM_INT64 int1;
	SMM_I64_SET(int1, 0x7fffffff, 0xffffffff);
	SMM_I64_DEC(int1);
	printf("INC: %8x:%8x\n", SMM_I64_HI(int1), SMM_I64_LO(int1));
*/

	SMM_UINT64 int1;
	SMM_UINT64 int2;
	SMM_U64_SET(int1, 0x7fffffff, 0xffffffff);
	SMM_U64_SET(int2, 0x7ffffeff, 0xffffffff);
	printf("%d", SMM_U64_CMP(int2, int1));


/*	printf("create thread\n");
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_2", 164, 0, 0, 200, (SMM_THREAD_ENTRY)Test_Thread, &kTestThreadID_2));

	printf("\n\ndelete thread\n");
	printf("return value:%d\n", SMM_ThreadGetName(kTestThreadID_1, buff));
	printf("\npress any key to delete %s\n", buff);
	getch();
	SMM_ThreadDelete(kTestThreadID_1);
	printf("\ndelete %s\n", buff);

	printf("return value:%d\n", SMM_ThreadGetName(kTestThreadID_2, buff));
	printf("\npress any key to delete %s\n", buff);
	getch();
	SMM_ThreadDelete(kTestThreadID_2);
	printf("\ndelete %s\n", buff);

	printf("create thread to resume\n");
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_1", 164, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread_Count, &kTestThreadID_1));

	printf("\npress any key to suspend thread\n");
	getch();
	SMM_ThreadSuspend(kTestThreadID_1);

	printf("\npress any key to resume thread\n");
	getch();
	SMM_ThreadResume(kTestThreadID_1);

	printf("\npress any key to sleep 2 seconds thread\n");
	getch();
	printf("return value:%d\n", SMM_ThreadCreate("MyThread_2", 164, 0, 0, 100, (SMM_THREAD_ENTRY)Test_Thread_Count, &kTestThreadID_1));
	SMM_ThreadSleep(20000);
*/
	printf("\nEnd Test\n");
	getch();

	return 0;
}

