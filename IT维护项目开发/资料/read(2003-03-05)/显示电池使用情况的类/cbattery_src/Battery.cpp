//////////////////////////////////////////////////////////////////////
//
// Battery.cpp: implementation of the CBattery class.
//
// Daniel Chirca - D.Chirca@finsiel.ro
// June 2000
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Battery.h"

#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
	#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBattery::CBattery()
{
	if(::GetSystemPowerStatus(&m_SysPower))
	{
		LoadStatus(m_SysPower);
		m_bOK = true;
	}
	else
	{
		m_bOK = false;
	}
}

CBattery::~CBattery()
{
}

//////////////////////////////////////////////////////////////////////
// Implementation
//////////////////////////////////////////////////////////////////////

BOOL CBattery::ReloadSystemPowerStatus()
{
	if(::GetSystemPowerStatus(&m_SysPower))
	{
		LoadStatus(m_SysPower);
		m_bOK = true;
	}
	else
	{
		m_bOK = false;
	}
	return m_bOK;
}

void CBattery::LoadStatus(SYSTEM_POWER_STATUS SysPower)
{
		m_ACLineStatus = (AC_LINE_STATUS)SysPower.ACLineStatus;
		m_BatteryFlag = (BATTERY_FLAG)SysPower.BatteryFlag;
		m_BatteryFullTime = SysPower.BatteryFullLifeTime;
		m_BatteryLifeTime = SysPower.BatteryLifeTime;
		m_BatteryLifePercent = SysPower.BatteryLifePercent;
}

SYSTEM_POWER_STATUS CBattery::SystemPowerStatus()
	{
		return m_SysPower;
	}
  
CBattery::AC_LINE_STATUS CBattery::ACLineStatus()
{
	return m_ACLineStatus;
}

CBattery::BATTERY_FLAG CBattery::BatteryFlag()
{
	return m_BatteryFlag;
}

long CBattery::BatteryFullTime()
{
	return m_BatteryFullTime;
}

long CBattery::BatteryLifeTime()
{
	return m_BatteryLifeTime;
}

BYTE CBattery::BatteryLifePercent()
{
	return m_BatteryLifePercent;
}

BOOL CBattery::BatteryIsCharging()
{
	return(m_BatteryFlag && CBattery::BF_CHARGING);
}

BOOL CBattery::BatteryIsUnknown()
{
	if(m_BatteryFlag && CBattery::BF_UNKNOWN)
		return TRUE;
	else
		return FALSE;
}

CBattery::DEVICE_POWER_STATE CBattery::DevicePowerState(HANDLE hDevice)
{
	if(::GetDevicePowerState(hDevice))
	{
		return DPS_ON;
	}
	else
	{
		return DPS_OFF;
	}
}
