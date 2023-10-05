// CheckCpuUsage.h: interface for the CCheckCpuUsage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKCPUUSAGE_H__092C5B62_A6E4_42DA_8CE7_A0B78DA9B6EF__INCLUDED_)
#define AFX_CHECKCPUUSAGE_H__092C5B62_A6E4_42DA_8CE7_A0B78DA9B6EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "CheckSystemType.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct
{
    DWORD   dwUnknown1;
    ULONG   uKeMaximumIncrement;
    ULONG   uPageSize;
    ULONG   uMmNumberOfPhysicalPages;
    ULONG   uMmLowestPhysicalPage;
    ULONG   uMmHighestPhysicalPage;
    ULONG   uAllocationGranularity;
    PVOID   pLowestUserAddress;
    PVOID   pMmHighestUserAddress;
    ULONG   uKeActiveProcessors;
    BYTE    bKeNumberProcessors;
    BYTE    bUnknown2;
    WORD    wUnknown3;
}SYSTEM_BASIC_INFORMATION;

typedef struct
{
    LARGE_INTEGER   liIdleTime;
    DWORD           dwSpare[76];
}SYSTEM_PERFORMANCE_INFORMATION;

typedef struct
{
    LARGE_INTEGER liKeBootTime;
    LARGE_INTEGER liKeSystemTime;
    LARGE_INTEGER liExpTimeZoneBias;
    ULONG         uCurrentTimeZoneId;
    DWORD         dwReserved;
}SYSTEM_TIME_INFORMATION;


typedef LONG (WINAPI *PROCNTQSI)(UINT,PVOID,ULONG,PULONG);


// WindowsNT/2000下CPU使用率
#define SystemBasicInformation       0
#define SystemPerformanceInformation 2
#define SystemTimeInformation        3

#define Li2Double(x) ((double)((x).HighPart) * 4.294967296E9 + (double)((x).LowPart))

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class CCheckCpuUsage  
{
public:
	BOOL CheckCpuUsage9x(long& CpuUsage);
	BOOL CheckCpuUsage(long& CpuUsage);
	BOOL CheckCpuUsage2000(long& CpuUsage);
	CCheckCpuUsage();
	virtual ~CCheckCpuUsage();

};

#endif // !defined(AFX_CHECKCPUUSAGE_H__092C5B62_A6E4_42DA_8CE7_A0B78DA9B6EF__INCLUDED_)
