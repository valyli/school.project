/*****************************************************************************

  Copyright (c), 2002-2005, QiDongKai Corp. All rights reserved.

  File name:     smm_kernel.h

  Author:        Yang Wei

  Version:       v1.0

  Date:          2003/03/14

  Description:   System Kernel Data And Function Definitions

  Others:

  History:
    1. Date:           2003/03/14
       Author:         Yang Wei
       Modification:   First Created

 *****************************************************************************/

#ifndef __SMM_KERNEL_H__
#define __SMM_KERNEL_H__

#ifdef  __cplusplus
extern "C" {
#endif


/*****************************************************************************
 Constant Macro Definition
 *****************************************************************************/

/*
 * Kernel ID related definition.
 */

/* Kernel ID type definition */
typedef SMM_UINT64  SMM_KID;

#define SMM_KID_SETNUL( kid ) SMM_U64_SET( kid, 0, 0 )

#define SMM_KID_ISNUL( kid ) \
( \
    SMM_U64_HI( kid ) == 0 && SMM_U64_LO( kid ) == 0 \
)

#define SMM_KID_ISEQU( kid1, kid2 ) \
( \
    SMM_U64_HI( kid1 ) == SMM_U64_HI( kid1 ) && \
    SMM_U64_LO( kid1 ) == SMM_U64_LO( kid2 ) \
)


/*
 * Time related definition.
 */

/* System time structure definition */
typedef struct tagSmmTime
{
    SMM_UINT16  m_ui16Year;
    SMM_UINT8   m_ui8Month;
    SMM_UINT8   m_ui8Week;
    SMM_UINT8   m_ui8Day;
    SMM_UINT8   m_ui8Hour;
    SMM_UINT8   m_ui8Minute;
    SMM_UINT8   m_ui8Second;
    SMM_UINT16  m_ui16Milliseconds;
} SMM_TIME_S;

/* Whether a year is a leap year */
#define SMM_TIME_ISLEAPYEAR( year ) \
( \
    ( ( ( ( year ) % 4 ) == 0 ) && ( ( ( year ) % 100 ) != 0 ) ) || \
    ( ( ( year ) % 400 ) == 0 ) \
)

/* Time isr hook entry type definition */
typedef SMM_VOID ( * SMM_TMISRHK_ENTRY )( SMM_UINT );


/*
 * Kernel name related definition.
 */

/* Max kernel name length, when define string array, should plus 1 for '\0' */
#define SMM_KERNAME_LEN             15


/*
 * Kernel synchronization related definition.
 */

/* Sync/async mode definiton */
#define SMM_WAIT_NONE               ((SMM_ULONG)( 0 ))
#define SMM_WAIT_INFINITE           ((SMM_ULONG)( -1 ))


/*
 * Semaphore related definition.
 */

/* Semaphore mode definition */
#define SMM_SEMA_MODE_FIFO          0x0000
#define SMM_SEMA_MODE_PRIO          0x0001
#define SMM_SEMA_MODE_DEFAULT       ( SMM_SEMA_MODE_FIFO )
#define SMM_SEMA_MODE_MASK          ( SMM_SEMA_MODE_PRIO )


/*
 * Event related definition.
 */

/* Event mode definition */
#define SMM_EVNT_MODE_ALL           0x0000
#define SMM_EVNT_MODE_ANY           0x0001
#define SMM_EVNT_MODE_DEFAULT       ( SMM_EVNT_MODE_ALL )
#define SMM_EVNT_MODE_MASK          ( SMM_EVNT_MODE_ANY )

/* Event Bit Mask Definition */
/*                 Total 32-bit, Divided 3 part
   +-------------+--------------------------------------------+
   | SYSBIT for  |        APPBIT for application use          |
   | SMM kernel  |---------------------+----------------------|
   | App not use |  PUBBIT for Public  |  PRVBIT for Private  |
   +-------------+---------------------+----------------------+ */
#define SMM_EVNT_SYSBIT_MASK        0xF0000000  /* Bits masked for kernel use, application can't use */
#define SMM_EVNT_APPBIT_MASK        0x0FFFFFFF  /* Bits that application can use, it's the OR of the following */
#define SMM_EVNT_PUBBIT_MASK        0x0FFF0000  /* Bits public to all application, can't be defined for private use */
#define SMM_EVNT_PRVBIT_MASK        0x0000FFFF  /* Bits can be defined for private use */

/* Event Public Bit Definition, bit range must not exceed SMM_EVNT_PUBBIT_MASK */
#define SMM_EVNT_PUB_TIMER          0x08000000  /* Event of smm timer expired */
#define SMM_EVNT_PUB_ASCKCOMM       0x04000000  /* Event of asynchronic SCK communication */


/*
 * Thread related definition.
 */

/* Thread mode definition */
#define SMM_THRD_MODE_PREEMPT       0x0000
#define SMM_THRD_MODE_NO_PREEMPT    0x0001
#define SMM_THRD_MODE_TIMESLICE     0x0000
#define SMM_THRD_MODE_NO_TIMESLICE  0x0002
#define SMM_THRD_MODE_DEFAULT       ( SMM_THRD_MODE_PREEMPT | SMM_THRD_MODE_TIMESLICE )
#define SMM_THRD_MODE_MASK          ( SMM_THRD_MODE_NO_PREEMPT | SMM_THRD_MODE_NO_TIMESLICE )

/* Thread stack size definition */
#define SMM_THRD_STACKSIZE_DEFAULT  0x8000
#define SMM_THRD_STACKSIZE_MINIMUM  0x400
#define SMM_THRD_STACKSIZE_MAXIMUM  0x2000000

/* Thread state definition */
#define SMM_THRD_STATE_READY        0x00000001  /* Ready for running */
#define SMM_THRD_STATE_INIT         0x00000002  /* Thread in creation process */
#define SMM_THRD_STATE_QUEBLK       0x00000004  /* Block by a sync queue operation */
#define SMM_THRD_STATE_EVTBLK       0x00000008  /* Block by a sync event read */
#define SMM_THRD_STATE_SEMBLK       0x00000010  /* Block by a semaphore P action */
#define SMM_THRD_STATE_SUSPEND      0x00000020  /* Suspend and not for schedule */
#define SMM_THRD_STATE_SLEEP        0x00000040  /* Thread paused for sleep */
#define SMM_THRD_STATE_MASK         ( SMM_THRD_STATE_READY | SMM_THRD_STATE_INIT | \
                                      SMM_THRD_STATE_QUEBLK | SMM_THRD_STATE_EVTBLK | \
                                      SMM_THRD_STATE_SEMBLK | SMM_THRD_STATE_SUSPEND | \
                                      SMM_THRD_STATE_SLEEP )

/* Thread entry type definition */
typedef SMM_VOID ( * SMM_THREAD_ENTRY )( SMM_UINT );


/*
 * Queue related definition.
 */

/* Queue mode definition */
#define SMM_QUEU_MODE_ASYN          0x0000
#define SMM_QUEU_MODE_SYNC          0x0001
#define SMM_QUEU_MODE_FIFO          0x0000
#define SMM_QUEU_MODE_PRIO          0x0002
#define SMM_QUEU_MODE_DEFAULT       ( SMM_QUEU_MODE_ASYN | SMM_QUEU_MODE_FIFO )
#define SMM_QUEU_MODE_MASK          ( SMM_QUEU_MODE_SYNC | SMM_QUEU_MODE_PRIO )

/* Queue length definition */
#define SMM_QUEU_LENGTH_DEFAULT     100
#define SMM_QUEU_LENGTH_MINIMUM     1
#define SMM_QUEU_LENGTH_MAXIMUM     100000

/* Queue message structure definition */
typedef struct tagSmmQueueMessage
{
    SMM_UINT32  m_ui32Type;         /* Message type, defined by system or user */
    SMM_UINT32  m_ui32Time;         /* Time stamp when message was write to queue */

    SMM_UINT32  m_ui32Para1;        /* Message 32-bit Parameter 1 */
    SMM_UINT32  m_ui32Para2;        /* Message 32-bit Parameter 2 */
    SMM_UINT32  m_ui32Para3;        /* Message 32-bit Parameter 3 */
    SMM_UINT32  m_ui32Para4;        /* Message 32-bit Parameter 4 */
    SMM_UINT64  m_ui64Param;        /* Message 64-bit Parameter */
} SMM_QUEUE_MSG_S;

/* System public queue message type code definition */
#define SMM_QMSG_TIMER              0x00000001

/* User defined private queue message type code basic begin here */
/* Should define as "#define SMM_QMSG_XXXX SMM_QMSG_USER + 1" */
#define SMM_QMSG_USER               0x00010000


/*
 * Timer related definition.
 */

/* Timer mode definition */
#define SMM_TIMR_MODE_CYCLIC        0x0000
#define SMM_TIMR_MODE_ONEOFF        0x0001
#define SMM_TIMR_MODE_DEFAULT       ( SMM_TIMR_MODE_CYCLIC )
#define SMM_TIMR_MODE_MASK          ( SMM_TIMR_MODE_ONEOFF )

/* Timer type definition */
#define SMM_TIMR_TYPE_MSG           0x0000
#define SMM_TIMR_TYPE_CBK           0x0001

/* Timer state definition */
#define SMM_TIMR_STATE_READY        0x00000001  /* Ready for schedule */
#define SMM_TIMR_STATE_PAUSED       0x00000002  /* Paused  and not for schedule */
#define SMM_TIMR_STATE_STOPPED      0x00000004  /* Stopped and not for schedule */
#define SMM_TIMR_STATE_MISSQUE      0x00000008  /* Lost queue and not for schedule */
#define SMM_TIMR_STATE_MISSTHD      0x00000010  /* Lost Thread and not for schedule */
#define SMM_TIMR_STATE_MASK         ( SMM_TIMR_STATE_READY | SMM_TIMR_STATE_PAUSED | \
                                      SMM_TIMR_STATE_STOPPED | SMM_TIMR_STATE_MISSQUE | \
                                      SMM_TIMR_STATE_MISSTHD )

/* Timer callback entry type definition */
typedef SMM_VOID ( * SMM_TIMER_ENTRY )( SMM_UINT, SMM_ULONG, SMM_KID );

/* Timer information structure definition */
typedef struct tagSmmTimerInformation
{
    SMM_USHORT      m_usType;       /* Type of timer, message or callback */
    SMM_USHORT      m_usMode;       /* Mode of timer, one-off or cyclic */
    SMM_ULONG       m_ulState;      /* Current state, e.g, activate, lost, etc */
    SMM_ULONG       m_ulTime;       /* Timeout value of the timer in milliseconds */
    SMM_UINT        m_uiArg;        /* Argument pass to the the timer when timeout */
    SMM_KID         m_kTID;         /* Notified thread when timeout under message mode */
    SMM_KID         m_kQID;         /* Queue used to post message when timeout under message mode */
    SMM_TIMER_ENTRY m_pfFunc;       /* Call back fucntion entry when timeout under callback mode */
} SMM_TIMER_INF_S;


/*
 * Kernel error code related definition.
 */

/* Error code definition for Interrupt */
#define SMM_ERR_INTR_OS_FAIL        1

/* Error code definition for Time */
#define SMM_ERR_TIME_OS_FAIL        1

/* Error code definition for Semaphore */
#define SMM_ERR_SEMA_OS_FAIL        1
#define SMM_ERR_SEMA_NOT_VALID      11
#define SMM_ERR_SEMA_NAME_FAIL      12
#define SMM_ERR_SEMA_BAD_ID         13
#define SMM_ERR_SEMA_NO_SPACE       14
#define SMM_ERR_SEMA_NOT_FOUND      15
#define SMM_ERR_SEMA_TIMEOUT        101

/* Error code definition for Event */
#define SMM_ERR_EVNT_OS_FAIL        1
#define SMM_ERR_EVNT_NOT_ACTIVE     11
#define SMM_ERR_EVNT_BAD_THREAD     12
#define SMM_ERR_EVNT_TIMEOUT        101
#define SMM_ERR_EVNT_MISS_MATCH     102

/* Error code definition for Thread */
#define SMM_ERR_THRD_OS_FAIL        1
#define SMM_ERR_THRD_NOT_VALID      11
#define SMM_ERR_THRD_BAD_ID         12
#define SMM_ERR_THRD_NAME_FAIL      13
#define SMM_ERR_THRD_NO_SPACE       14
#define SMM_ERR_THRD_NOT_FOUND      15

/* Error code definition for Queue */
#define SMM_ERR_QUEU_OS_FAIL        1
#define SMM_ERR_QUEU_NOT_VALID      11
#define SMM_ERR_QUEU_BAD_ID         12
#define SMM_ERR_QUEU_NAME_FAIL      13
#define SMM_ERR_QUEU_NO_SPACE       14
#define SMM_ERR_QUEU_NOT_FOUND      15
#define SMM_ERR_QUEU_TIMEOUT        101
#define SMM_ERR_QUEU_EMPTY          102
#define SMM_ERR_QUEU_FULL           103

/* Error code definition for Timer */
#define SMM_ERR_TIMR_NOT_VALID      11
#define SMM_ERR_TIMR_BAD_THREAD     12
#define SMM_ERR_TIMR_BAD_QUEUE      13
#define SMM_ERR_TIMR_NO_SPACE       14
#define SMM_ERR_TIMR_NOT_READY      15


/*****************************************************************************
 Function Declaration
 *****************************************************************************/

/* Kernel init funtion */
extern SMM_INT SMM_Init( SMM_VOID );

/* Interrupt funtion */
extern SMM_INT SMM_IntLock( SMM_INT * );
extern SMM_INT SMM_IntUnLock( SMM_INT );

/* Time function */
extern SMM_INT SMM_TimeGetGMT( SMM_TIME_S * );
extern SMM_INT SMM_TimeSetGMT( const SMM_TIME_S * );
extern SMM_INT SMM_TimeGetLocal( SMM_TIME_S * );
extern SMM_INT SMM_TimeSetLocal( const SMM_TIME_S * );
extern SMM_INT SMM_TimeGetElapse( SMM_UINT64 * );
extern SMM_VOID SMM_TimeSysToMsec( const SMM_TIME_S *, SMM_UINT64 * );
extern SMM_VOID SMM_TimeMsecToSys( const SMM_UINT64 *, SMM_TIME_S * );
extern SMM_UINT8 SMM_TimeGetDayOfWeek( SMM_UINT16, SMM_UINT8, SMM_UINT8 );
extern SMM_INT SMM_TimeIsrHookAdd( SMM_UINT, SMM_TMISRHK_ENTRY, SMM_KID * );
extern SMM_INT SMM_TimeIsrHookDel( SMM_KID );
extern SMM_BOOL SMM_TimeIsrHookIsValid( SMM_KID );

/* Semaphore funtion */
extern SMM_INT SMM_SemaphoreCreate( const SMM_CHAR *, SMM_ULONG, SMM_USHORT, SMM_KID * );
extern SMM_INT SMM_SemaphoreDelete( SMM_KID );
extern SMM_INT SMM_SemaphoreTake( SMM_KID, SMM_ULONG );
extern SMM_INT SMM_SemaphoreGive( SMM_KID );
extern SMM_INT SMM_SemaphoreGetID( const SMM_CHAR *, SMM_KID * );
extern SMM_INT SMM_SemaphoreGetName( SMM_KID , SMM_CHAR * );
extern SMM_BOOL SMM_SemaphoreIsValid( SMM_KID );

/* Event funtion */
extern SMM_INT SMM_EventRead( SMM_UINT32, SMM_UINT32 *, SMM_USHORT, SMM_ULONG );
extern SMM_INT SMM_EventWrite( SMM_KID, SMM_UINT32 );

/* Thread funtion */
extern SMM_INT SMM_ThreadCreate( const SMM_CHAR *, SMM_UINT8, SMM_USHORT,
                                 SMM_ULONG, SMM_UINT, SMM_THREAD_ENTRY, SMM_KID * );
extern SMM_INT SMM_ThreadDelete( SMM_KID );
extern SMM_INT SMM_ThreadRestart( SMM_KID , SMM_UINT );
extern SMM_INT SMM_ThreadSuspend( SMM_KID );
extern SMM_INT SMM_ThreadResume( SMM_KID );
extern SMM_INT SMM_ThreadSleep( SMM_ULONG );
extern SMM_INT SMM_ThreadGetPriority( SMM_KID, SMM_UINT8 * );
extern SMM_INT SMM_ThreadSetPriority( SMM_KID, SMM_UINT8 );
extern SMM_INT SMM_ThreadGetMyID( SMM_KID * );
extern SMM_INT SMM_ThreadGetID( const SMM_CHAR *, SMM_KID * );
extern SMM_INT SMM_ThreadGetName( SMM_KID , SMM_CHAR * );
extern SMM_INT SMM_ThreadGetState( SMM_KID, SMM_ULONG * );
extern SMM_INT SMM_ThreadIsAlive( SMM_KID, SMM_BOOL * );
extern SMM_BOOL SMM_ThreadIsValid( SMM_KID );

/* Queue funtion */
extern SMM_INT SMM_QueueCreate( const SMM_CHAR *, SMM_ULONG, SMM_USHORT, SMM_KID * );
extern SMM_INT SMM_QueueDelete( SMM_KID );
extern SMM_INT SMM_QueueRead( SMM_KID, SMM_QUEUE_MSG_S *, SMM_ULONG );
extern SMM_INT SMM_QueueWrite( SMM_KID, const SMM_QUEUE_MSG_S *, SMM_ULONG, SMM_BOOL );
extern SMM_INT SMM_QueueGetID( const SMM_CHAR *, SMM_KID * );
extern SMM_INT SMM_QueueGetName( SMM_KID , SMM_CHAR * );
extern SMM_INT SMM_QueueGetMsgNum( SMM_KID, SMM_ULONG * );
extern SMM_BOOL SMM_QueueIsValid( SMM_KID );

/* Timer funtion */
extern SMM_INT SMM_TimerCreateM( SMM_ULONG, SMM_USHORT, SMM_UINT, SMM_KID, SMM_KID, SMM_KID * );
extern SMM_INT SMM_TimerCreateC( SMM_ULONG, SMM_USHORT, SMM_UINT, SMM_TIMER_ENTRY, SMM_KID * );
extern SMM_INT SMM_TimerDelete( SMM_KID );
extern SMM_INT SMM_TimerPause( SMM_KID );
extern SMM_INT SMM_TimerResume( SMM_KID );
extern SMM_INT SMM_TimerGetInfo( SMM_KID, SMM_TIMER_INF_S * );
extern SMM_INT SMM_TimerGetTimeLeft( SMM_KID, SMM_ULONG * );
extern SMM_BOOL SMM_TimerIsValid( SMM_KID );


#ifdef  __cplusplus
}
#endif

#endif
