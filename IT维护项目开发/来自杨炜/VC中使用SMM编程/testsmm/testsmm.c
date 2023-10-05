/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     testsmm.c

  Author:        Yang Wei

  Version:       v1.0

  Date:          2003/05/01

  Description:   A Test File For System Management Module

  Others:

  Function List:

  History:
    1. Date:           2003/03/14
       Author:         Yang Wei
       Modification:   First Created

 *****************************************************************************/


#ifdef  __cplusplus
extern "C"{
#endif


/* 这里包含SMM头文件 */
#include <smm/smm.h>

/* 初始化SMM系统函数 */
SMM_VOID InitSys( SMM_VOID )
{
    printf( "\nSMM Kernel Initialized ... " );
    if( SMM_OK == SMM_Init() )
    {
        printf( "OK\n" );
    }
    else
    {
        printf( "FAIL\n" );
    }
}

/* 时间中断钩子测试函数 */
SMM_VOID Test_TiHook( SMM_UINT uiArg )
{
    SMM_UINT64 ui64Tm;
    SMM_TimeGetElapse(&ui64Tm);
    printf("\rTime ISR Hook %d output %05d:%03d", uiArg, SMM_U64_LO(ui64Tm)/1000, SMM_U64_LO(ui64Tm)%1000);
}

SMM_KID g_kTmrTID;
SMM_KID g_kTmrQID;

/* 回调定时器测试函数 */
SMM_VOID Test_TimerCbk( SMM_UINT uiArg, SMM_ULONG ulTime, SMM_KID kTmrID )
{
    printf("\nCall back Timer(%d-%d) timeout at %d.", SMM_U64_HI(kTmrID), SMM_U64_LO(kTmrID), ulTime );
}

/* 定时器消息处理测试线程 */
SMM_VOID Timer_Thread( SMM_UINT uiArg )
{
    SMM_UINT32  ui32EventsGet = 0;
    SMM_KID     kMyID;
    SMM_CHAR    szName[256];
    SMM_INT     iRet;

    SMM_ThreadGetMyID( &kMyID );
    SMM_ThreadGetName( kMyID, szName );

    for( ; ; )
    {
        /* Wait until receive Timer Event */
        iRet = SMM_EventRead( SMM_EVNT_PUB_TIMER, &ui32EventsGet,
                              SMM_EVNT_MODE_ANY, SMM_WAIT_INFINITE );
        if( SMM_OK == iRet )
        {
            if( SMM_EVNT_PUB_TIMER & ui32EventsGet )
            {
                /* Receive Timer Event */
                SMM_QUEUE_MSG_S stMsg;
                SMM_CHAR    szQueueName[64];

                SMM_QueueGetName( g_kTmrQID, szQueueName );

                while( SMM_OK == SMM_QueueRead(g_kTmrQID, &stMsg, SMM_WAIT_NONE ) )
                {
                    if( SMM_QMSG_TIMER == stMsg.m_ui32Type )
                    {
                        printf( "\n%s(%d-%d) report: %s timer msg(Arg:%d, Time:%d, TmrID:%d-%d).",
                                szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID), szQueueName,
                                stMsg.m_ui32Para1, stMsg.m_ui32Para2,
                                SMM_U64_HI(stMsg.m_ui64Param), SMM_U64_LO(stMsg.m_ui64Param),
                                stMsg.m_ui32Time );
                    }
                }
            }
        }
    }
}

SMM_KID g_kAAASID;
SMM_KID g_kAAAQID;

/* 信号量处理测试线程 */
SMM_VOID Test_AAA( LPVOID *pData )
{
    SMM_KID     kTID;
    SMM_CHAR    szTmp1[32];
    SMM_CHAR    szTmp2[32];
    SMM_ULONG   ulArg = (SMM_ULONG)pData;

    SMM_ThreadGetMyID(&kTID);
    SMM_ThreadGetName(kTID, szTmp1);
    printf("\n'%s'(ID: %d-%d, Arg: %d) waiting for semaphore to be created ", szTmp1, SMM_U64_HI( kTID ), SMM_U64_LO(kTID), ulArg);
    while(1)
    {
        if( !SMM_KID_ISNUL(g_kAAASID) )
        {
            SMM_SemaphoreGetName( g_kAAASID, szTmp2 );
            printf("\nSemaphore '%s(%d-%d)' created! '%s' begin to P it . . . ",
                    szTmp2, SMM_U64_HI(g_kAAASID), SMM_U64_LO(g_kAAASID), szTmp1);
            if(SMM_OK == SMM_SemaphoreTake(g_kAAASID, SMM_WAIT_INFINITE))
            {
                printf("GOT IT, Bye !\n");
            }
            else
            {
                printf("ERROR GOT, Bye !\n");
            }
            break;
        }
        else
        {
            printf(".");
            SMM_ThreadSleep(100);
        }
    }

    printf("\n'%s'(ID: %d-%d, Arg: %d) normal terminated.\n ", szTmp1, SMM_U64_HI(kTID), SMM_U64_LO(kTID), ulArg);
}

SMM_KID g_kThread1_TID;
SMM_KID g_kThread2_TID;
SMM_KID g_kThread3_TID;

#define TEST_EVENT_01 0x1
#define TEST_EVENT_02 0x2

/* 以下三个为事件，队列测试线程 */
SMM_VOID Thread1_Entry( SMM_UINT uiArg )
{
    SMM_KID     kMyID;
    SMM_CHAR    szName[64];

    SMM_ThreadGetMyID( &kMyID );
    SMM_ThreadGetName( kMyID, szName );

    for( ; ; )
    {
        if( SMM_KID_ISNUL(g_kThread3_TID) )
        {
            printf( "\n%s(%d-%d) report: Target thread not ready!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
        }
        else
        {
            if( !SMM_KID_ISNUL(g_kAAAQID) )
            {
                SMM_QUEUE_MSG_S stMsg;
                SMM_CHAR    szQueueName[64];
                SMM_INT     iQueRet;
                static SMM_ULONG ulSend = 0;

                SMM_QueueGetName( g_kAAAQID, szQueueName );
                stMsg.m_ui32Para1 = ulSend;
                stMsg.m_ui32Para2 = SMM_U64_HI(g_kAAAQID);
                stMsg.m_ui32Para3 = SMM_U64_LO(g_kAAAQID);
                stMsg.m_ui64Param = g_kThread3_TID;

                iQueRet = SMM_QueueWrite(g_kAAAQID, &stMsg, 100, FALSE );
                if( SMM_OK == iQueRet )
                {
                    ulSend ++;
                    printf( "\n%s(%d-%d) report: Write to queue %s (%d, %d, %d, %d-%d).",
                            szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID), szQueueName,
                            stMsg.m_ui32Para1, stMsg.m_ui32Para2, stMsg.m_ui32Para3,
                            SMM_U64_HI(stMsg.m_ui64Param), SMM_U64_LO(stMsg.m_ui64Param) );
                }
                else
                {
                    printf( "\n%s(%d-%d) report: Error %d write to queue %s.",
                            szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID), iQueRet, szQueueName );
                }

                if( SMM_OK != SMM_EventWrite( g_kThread3_TID, TEST_EVENT_01 ) )
                {
                    printf( "\n%s(%d-%d) report: Error write event TEST_EVENT_01!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID)  );
                }
            }
        }
        SMM_ThreadSleep( 1001 );
    }
}

SMM_VOID Thread2_Entry( SMM_UINT uiArg )
{
    SMM_KID     kMyID;
    SMM_CHAR    szName[256];

    SMM_ThreadGetMyID( &kMyID );
    SMM_ThreadGetName( kMyID, szName );

    for( ; ; )
    {
        if( SMM_KID_ISNUL(g_kThread3_TID) )
        {
            printf( "\n%s(%d-%d) report: Target thread not ready!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
        }
        else
        {
            if( SMM_OK != SMM_EventWrite( g_kThread3_TID, TEST_EVENT_02 ) )
            {
                printf( "\n%s(%d-%d) report: Error write event TEST_EVENT_02!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
            }
        }
        SMM_ThreadSleep( 1000 );
    }
}

SMM_VOID Thread3_Entry( SMM_UINT uiArg )
{
    SMM_UINT32  ui32EventsGet = 0;
    SMM_KID     kMyID;
    SMM_CHAR    szName[256];
    SMM_INT     iRet;

    SMM_ThreadGetMyID( &kMyID );
    SMM_ThreadGetName( kMyID, szName );

    for( ; ; )
    {
        /* Wait until receive TEST_EVENT_01 or TEST_EVENT_02 */
        iRet = SMM_EventRead( TEST_EVENT_01 | TEST_EVENT_02, &ui32EventsGet,
                              SMM_EVNT_MODE_ANY, SMM_WAIT_INFINITE );
        if( SMM_OK == iRet )
        {
            if( TEST_EVENT_01 & ui32EventsGet )
            {
                /* Receive TEST_EVENT_01 */
                SMM_QUEUE_MSG_S stMsg;
                SMM_CHAR    szQueueName[64];

                printf( "\n%s(%d-%d) report: Receive Event 1!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
                SMM_QueueGetName( g_kAAAQID, szQueueName );

                if( SMM_OK == SMM_QueueRead(g_kAAAQID, &stMsg, 50 ) )
                {
                    printf( "\n%s(%d-%d) report: Read from %s (%d, %d, %d, %d-%d) at timestamp %lu.",
                            szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID), szQueueName,
                            stMsg.m_ui32Para1, stMsg.m_ui32Para2, stMsg.m_ui32Para3,
                            SMM_U64_HI(stMsg.m_ui64Param), SMM_U64_LO(stMsg.m_ui64Param),
                            stMsg.m_ui32Time );
                }
                else
                {
                    printf( "\n%s(%d-%d) report: Error read from queue %s.",
                            szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID), szQueueName );
                }
            }

            if( TEST_EVENT_02 & ui32EventsGet )
            {
                /* Receive TEST_EVENT_02 */
                printf( "\n%s(%d-%d) report: Receive Event 2!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
            }
        }
        else if( SMM_ERR_EVNT_TIMEOUT == iRet )
        {
            printf( "\n%s(%d-%d) report: Timeout when read events!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
            SMM_ThreadSleep( 100 );
        }
        else
        {
            printf( "\n%s(%d-%d) report: Error occured when read events!", szName, SMM_U64_HI(kMyID), SMM_U64_LO(kMyID) );
            SMM_ThreadSleep( 100 );
        }
    }
}

/* 主函数 */
SMM_INT main( SMM_VOID )
{
    printf( "\nThis is a test of System Management Module. . .\n" );

    InitSys();

    printf( "\n>>> TEST Semaphore <<<\n" );
    {
        SMM_KID  kTestSemaID;

        SMM_KID_SETNUL( kTestSemaID );
        SMM_SemaphoreCreate( "MySemaphoreGood", 1, 0, &kTestSemaID );
        printf( "\nSemaphore (%d-%d) created ...", SMM_U64_HI(kTestSemaID), SMM_U64_LO(kTestSemaID) );
        SMM_SemaphoreTake( kTestSemaID, SMM_WAIT_INFINITE );
        printf( " taken ..." );
        SMM_SemaphoreDelete( kTestSemaID );
        printf( " deleted.\n" );
        SMM_KID_SETNUL( kTestSemaID );
        getchar();
    }

    printf( "\n>>> TEST Thread <<<\n" );
    {
        SMM_KID  kTestThreadID;
        SMM_BOOL bAlive = FALSE;

        SMM_KID_SETNUL(kTestThreadID);
        SMM_ThreadCreate( "MyThreadWonderful", 164, 0, 0, 314, (SMM_THREAD_ENTRY)Test_AAA, &kTestThreadID );
        getchar();
        SMM_ThreadIsAlive( kTestThreadID, &bAlive );
        SMM_ThreadSuspend( kTestThreadID );
        printf( "\nThread was suspended, press ENTER to resume." );
        getchar();
        SMM_ThreadIsAlive( kTestThreadID, &bAlive );
        SMM_ThreadResume( kTestThreadID );
        getchar();
        printf( "\nThread restarting . . .\n" );
        SMM_ThreadIsAlive( kTestThreadID, &bAlive );
        SMM_ThreadRestart( kTestThreadID, 413 );
        getchar();
        SMM_ThreadIsAlive( kTestThreadID, &bAlive );
        SMM_SemaphoreCreate( "MySemaphoreGood", 0, 0, &g_kAAASID );
        getchar();
        SMM_SemaphoreGive( g_kAAASID );
        getchar();
        SMM_SemaphoreDelete( g_kAAASID );
    }

    printf( "\n>>> TEST Event <<<\n" );
    {
        SMM_KID  kTestThreadID;

        SMM_KID_SETNUL(kTestThreadID);
        SMM_ThreadCreate( "Thread1", 100, 0, 0, 0, (SMM_THREAD_ENTRY)Thread1_Entry, &g_kThread1_TID );
        SMM_ThreadCreate( "Thread1Clone", 100, 0, 0, 0, (SMM_THREAD_ENTRY)Thread1_Entry, &kTestThreadID );
        SMM_ThreadCreate( "Thread2", 100, 0, 0, 0, (SMM_THREAD_ENTRY)Thread2_Entry, &g_kThread2_TID );
        getchar();
        SMM_ThreadDelete( kTestThreadID );
        SMM_ThreadCreate( "Thread3", 100, 0, 0, 0, (SMM_THREAD_ENTRY)Thread3_Entry, &g_kThread3_TID );
        getchar();
    }

    printf( "\n>>> TEST Queue <<<\n" );
    {
        SMM_KID_SETNUL( g_kAAAQID );
        SMM_QueueCreate( "TestQueue", 0, SMM_QUEU_MODE_SYNC, &g_kAAAQID );
        getchar();
        SMM_ThreadDelete( g_kThread1_TID );
        SMM_KID_SETNUL(g_kThread1_TID);
        SMM_ThreadDelete( g_kThread2_TID );
        SMM_KID_SETNUL(g_kThread2_TID);
        SMM_ThreadDelete( g_kThread3_TID );
        SMM_KID_SETNUL(g_kThread3_TID);
        SMM_QueueDelete( g_kAAAQID );
        SMM_KID_SETNUL( g_kAAAQID );
        getchar();
    }

    printf( "\n>>> TEST Time <<<\n" );
    {
        SMM_UINT64 a, b, c, d, e;
        SMM_U64_SET( a, 0xFF, 0xFFFFFFC );
        SMM_U64_SET( b, 0, 0x01234 );
        c = SMM_U64_MUL(a, b);
        d = SMM_U64_DIV(c, a);
        e = SMM_U64_SHL(a, 24);

        printf("\n%08X%08X * %08X%08X = %08X%08X\n%08X%08X %08X%08X %d\n",
                SMM_U64_HI(a), SMM_U64_LO(a),
                SMM_U64_HI(b), SMM_U64_LO(b),
                SMM_U64_HI(c), SMM_U64_LO(c),
                SMM_U64_HI(d), SMM_U64_LO(d),
                SMM_U64_HI(e), SMM_U64_LO(e),
                SMM_U64_CMP( b, a ) );
    }
    {
        SMM_TIME_S stTime = {0};
        SMM_UINT64 ui64Time;
        SMM_UINT64 ui64_1K;
        SMM_UINT8  ui8Week = 0;

        SMM_U64_SET( ui64Time, 0, 0 );
        SMM_U64_SET( ui64_1K, 0, 1000 );

        SMM_TimeGetLocal(&stTime);
        SMM_TimeSysToMsec(&stTime, &ui64Time);
        SMM_TimeMsecToSys(&ui64Time, &stTime);
        ui8Week = SMM_TimeGetDayOfWeek(stTime.m_ui16Year, stTime.m_ui8Month, stTime.m_ui8Day);

        printf("\nCurrent date: %04d/%02d/%02d %02d:%02d:%02d:%03d Week %d"
               "\nTotal: %08X%08Xms %lusec  DayofWeek: %d\n",
               stTime.m_ui16Year, stTime.m_ui8Month, stTime.m_ui8Day,
               stTime.m_ui8Hour, stTime.m_ui8Minute, stTime.m_ui8Second,
               stTime.m_ui16Milliseconds, stTime.m_ui8Week,
               SMM_U64_HI(ui64Time), SMM_U64_LO(ui64Time),
               SMM_U64_LO(SMM_U64_DIV(ui64Time, ui64_1K)), ui8Week);
    }
    {
        SMM_UINT64 ui64Elapse;
        SMM_TimeGetElapse(&ui64Elapse);

        printf("\nTime Elapse : %08X%08Xms %dms\n",
               SMM_U64_HI(ui64Elapse), SMM_U64_LO(ui64Elapse), SMM_U64_LO(ui64Elapse));
        getchar();
    }

    printf( "\n>>> TEST Time ISR Hook <<<\n" );
    {
        SMM_KID kTiHookID;
        SMM_KID_SETNUL(kTiHookID);
        SMM_TimeIsrHookAdd(888,Test_TiHook,&kTiHookID);
        printf( "\nTI-Hook (%d-%d) added.\n", SMM_U64_HI(kTiHookID), SMM_U64_LO(kTiHookID) );
        getchar();
        SMM_TimeIsrHookDel(kTiHookID);
        SMM_KID_SETNUL(kTiHookID);
        SMM_TimeIsrHookAdd(777,Test_TiHook,&kTiHookID);
        printf( "\nTI-Hook (%d-%d) added.\n", SMM_U64_HI(kTiHookID), SMM_U64_LO(kTiHookID) );
        getchar();
        SMM_TimeIsrHookDel(kTiHookID);
        SMM_KID_SETNUL(kTiHookID);
        SMM_TimeIsrHookAdd(999,Test_TiHook,&kTiHookID);
        printf( "\nTI-Hook (%d-%d) added.\n", SMM_U64_HI(kTiHookID), SMM_U64_LO(kTiHookID) );
        getchar();
        SMM_TimeIsrHookDel(kTiHookID);
    }

    printf( "\n>>> TEST Timer <<<\n" );
    {
        SMM_KID kTmrID1, kTmrID2, kTmrID3;

        SMM_KID_SETNUL(kTmrID1);
        SMM_KID_SETNUL(kTmrID2);
        SMM_KID_SETNUL(kTmrID3);

        SMM_KID_SETNUL( g_kTmrQID );
        SMM_QueueCreate( "TimerQueue", 0, SMM_QUEU_MODE_SYNC, &g_kTmrQID );
        SMM_KID_SETNUL( g_kTmrTID );
        SMM_ThreadCreate( "TimerThread", 100, 0, 0, 0, (SMM_THREAD_ENTRY)Timer_Thread, &g_kTmrTID );

        SMM_TimerCreateM(0, SMM_TIMR_MODE_ONEOFF, 0, g_kTmrTID, g_kTmrQID, &kTmrID1);
        SMM_TimerCreateM(500, SMM_TIMR_MODE_CYCLIC, 0, g_kTmrTID, g_kTmrQID, &kTmrID2);
        SMM_TimerCreateC(750, SMM_TIMR_MODE_CYCLIC, 0, Test_TimerCbk, &kTmrID3);

        getchar();
        SMM_TimerPause( kTmrID3 );
        getchar();
        SMM_TimerPause( kTmrID2 );
        SMM_TimerResume( kTmrID3 );
        getchar();

        SMM_TimerDelete(kTmrID2);
        SMM_TimerDelete(kTmrID1);
        SMM_TimerDelete(kTmrID3);

        SMM_QueueDelete(g_kTmrQID);
        SMM_ThreadDelete(g_kTmrTID);
    }

    printf("\n*** Test OVER ***\n");
    return 0;
}


#ifdef  __cplusplus
}
#endif
