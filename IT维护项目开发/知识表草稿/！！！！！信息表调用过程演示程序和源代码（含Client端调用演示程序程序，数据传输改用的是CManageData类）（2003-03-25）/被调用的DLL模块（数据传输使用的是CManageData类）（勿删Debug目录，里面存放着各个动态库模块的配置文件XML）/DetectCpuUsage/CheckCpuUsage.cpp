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


//��2000�¼��CPU������
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

    // �õ�ϵͳ�д�������
    status = NtQuerySystemInformation(SystemBasicInformation,&SysBaseInfo,sizeof(SysBaseInfo),NULL);
    if (status != NO_ERROR)
        return FALSE;
    
    // �õ��µ�ϵͳʱ��
    status = NtQuerySystemInformation(SystemTimeInformation,&SysTimeInfo,sizeof(SysTimeInfo),0);
    if (status!=NO_ERROR)
        return FALSE;

    // �õ��µ�CPU����ʱ��
    status = NtQuerySystemInformation(SystemPerformanceInformation,&SysPerfInfo,sizeof(SysPerfInfo),NULL);
    if (status != NO_ERROR)
        return FALSE;

    // �����һ�ε�������
    if (liOldIdleTime.QuadPart != 0)
    {
        // ��ǰֵ = ����ֵ - ��ֵ
        dbIdleTime = Li2Double(SysPerfInfo.liIdleTime) - Li2Double(liOldIdleTime);
        dbSystemTime = Li2Double(SysTimeInfo.liKeSystemTime) - Li2Double(liOldSystemTime);

        // ��ǰCPU����ʱ�� = ����ʱ�� / ϵͳʱ��
        dbIdleTime = dbIdleTime / dbSystemTime;

        // ��ǰCPU������% = 100 - (��ǰCPU����ʱ�� * 100) / ��������
        dbIdleTime = 100.0 - dbIdleTime * 100.0 / (double)SysBaseInfo.bKeNumberProcessors + 0.5;

        CpuUsage = (long)dbIdleTime;
    }

    // �洢�µ�CPU���м�ϵͳʱ��
    liOldIdleTime = SysPerfInfo.liIdleTime;
    liOldSystemTime = SysTimeInfo.liKeSystemTime;

	return TRUE;
}

//���cpu�����ʣ��Զ����汾
BOOL CCheckCpuUsage::CheckCpuUsage(long &CpuUsage)
{
	CCheckSystemType m_CCheckSystemType;
	CString strWin32SysType;
	long m_SystemType;
	//��ϵͳ�汾
	m_SystemType = m_CCheckSystemType.IsShellSystemType(strWin32SysType);

	BOOL rflag;

	if(m_SystemType == 2 || m_SystemType == 3)
		rflag = CheckCpuUsage9x(CpuUsage);
	else
		rflag = CheckCpuUsage2000(CpuUsage);
	if(rflag == FALSE)
	{
		AfxMessageBox("��ȡCPU�����ʺ�������!");
		return FALSE;
	}
	return TRUE;
}


//��98�¼��CPU������
BOOL CCheckCpuUsage::CheckCpuUsage9x(long &CpuUsage)
{
	HKEY hkey;
    DWORD dwDataSize;
    DWORD dwType;
    DWORD dwCpuUsage;

    // ��������
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
    
    // �õ���ǰ����ֵ
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
    // ֹͣ����
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
