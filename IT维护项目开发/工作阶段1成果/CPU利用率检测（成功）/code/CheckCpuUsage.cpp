// CheckCpuUsage.cpp: implementation of the CCheckCpuUsage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CheckCpuUsage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckCpuUsage::CCheckCpuUsage()
{

}

CCheckCpuUsage::~CCheckCpuUsage()
{

}


//在2000下检查CPU利用率
BOOL CCheckCpuUsage::CheckCpuUsage2000(long& CpuUsage)
{
	SYSTEM_PERFORMANCE_INFORMATION SysPerfInfo;
    SYSTEM_TIME_INFORMATION        SysTimeInfo;
    SYSTEM_BASIC_INFORMATION       SysBaseInfo;
    double                         dbIdleTime;
    double                         dbSystemTime;
    LONG                           status;
	static LARGE_INTEGER           liOldIdleTime = {0,0};
    static LARGE_INTEGER           liOldSystemTime = {0,0};

	PROCNTQSI NtQuerySystemInformation;

    NtQuerySystemInformation = (PROCNTQSI)GetProcAddress(
                                          GetModuleHandle("ntdll"),
                                         "NtQuerySystemInformation"
                                         );

    if (!NtQuerySystemInformation)
        return FALSE;

    // 得到系统中处理器数
    status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
    if (status != NO_ERROR)
        return FALSE;
    
    // 得到新的系统时间
    status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
    if (status!=NO_ERROR)
        return FALSE;

    // 得到新的CPU空闲时间
    status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
    if (status != NO_ERROR)
        return FALSE;

    // 如果第一次调用跳过
    if (liOldIdleTime.QuadPart != 0)
    {
        // 当前值 = 最新值 - 旧值
        dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime);
        dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);

        // 当前CPU空闲时间 = 空闲时间 / 系统时间
        dbIdleTime = dbIdleTime / dbSystemTime;

        // 当前CPU利用率% = 100 - (当前CPU空闲时间 * 100) / 处理器数
        dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors + 0.5;

        CpuUsage = (long)dbIdleTime;
    }

    // 存储新的CPU空闲及系统时间
    liOldIdleTime = SysPerfInfo.liIdleTime;
    liOldSystemTime = SysTimeInfo.liKeSystemTime;

	return TRUE;
}

//获得cpu利用率，自动检测版本
BOOL CCheckCpuUsage::CheckCpuUsage(long &CpuUsage)
{
	CCheckSystemType m_CCheckSystemType;
	CString strWin32SysType;
	long m_SystemType;
	//查系统版本
	m_SystemType = m_CCheckSystemType.IsShellSystemType(strWin32SysType);

	BOOL rflag;

	if(m_SystemType == 2 || m_SystemType == 3)
		rflag = CheckCpuUsage9x(CpuUsage);
	else
		rflag = CheckCpuUsage2000(CpuUsage);
	if(rflag == FALSE)
	{
		AfxMessageBox("获取CPU利用率函数出错!");
		return FALSE;
	}
	return TRUE;
}


//在98下检查CPU利用率
BOOL CCheckCpuUsage::CheckCpuUsage9x(long &CpuUsage)
{
	HKEY hkey;
    DWORD dwDataSize;
    DWORD dwType;
    DWORD dwCpuUsage;

    // 启动计数
    if ( RegOpenKeyEx( HKEY_DYN_DATA,
                       "PerfStats\\StartStat",
                       0,KEY_ALL_ACCESS,
                       &hkey ) != ERROR_SUCCESS)
       return FALSE;

    dwDataSize=sizeof(DWORD);
    RegQueryValueEx( hkey,
                     "KERNEL\\CPUUsage",
                     NULL,&dwType,
                     (LPBYTE)&dwCpuUsage,
                     &dwDataSize );

    RegCloseKey(hkey);
    
    // 得到当前计数值
    if ( RegOpenKeyEx( HKEY_DYN_DATA,
                       "PerfStats\\StatData",
                       0,KEY_READ,
                       &hkey ) != ERROR_SUCCESS)
       return FALSE;

    dwDataSize=sizeof(DWORD);
    RegQueryValueEx( hkey,
                         "KERNEL\\CPUUsage",
                         NULL,&dwType,
                         (LPBYTE)&dwCpuUsage,
                         &dwDataSize );
    CpuUsage = dwCpuUsage;
    
    RegCloseKey(hkey);
/*    
    // 停止计数
    if ( RegOpenKeyEx( HKEY_DYN_DATA,
                       "PerfStats\\StopStat",
                       0,KEY_ALL_ACCESS,
                       &hkey ) != ERROR_SUCCESS)
       return S_FALSE;

    dwDataSize=sizeof(DWORD);
    RegQueryValueEx( hkey,
                     "KERNEL\\CPUUsage",
                     NULL,&dwType,
                     (LPBYTE)&dwCpuUsage,
                     &dwDataSize );

    RegCloseKey(hkey);
*/
	return TRUE;
}
