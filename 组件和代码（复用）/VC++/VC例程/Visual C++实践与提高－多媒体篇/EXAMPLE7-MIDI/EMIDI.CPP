// Midi.cpp: implementation of the CExMidi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "emidi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CExMidi::CExMidi()
{
	// 初始化成员变量
	m_Open  =  FALSE;
	m_Pause  =  FALSE;
	m_Playing =  FALSE;
	m_wDeviceID = 0;
}

CExMidi::~CExMidi()
{
	Close ();
}

int CExMidi::GetDevices ()
{
	return (int) midiOutGetNumDevs ();
}
DWORD CExMidi::Open ()
{
	DWORD Dflag;
	if (!m_Open)
	{
		// 初始化成员变量
		m_Open = m_Pause = m_Playing = FALSE;
		m_wDeviceID = 0;

		// 文件是否存在
		CFileStatus Status;
		if (!CFile::GetStatus (m_name, Status))
			return FALSE;

		// 打开设备
		MCI_OPEN_PARMS OpenP;
		OpenP.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_SEQUENCER;
		OpenP.lpstrElementName = (LPCSTR) m_name;
		OpenP.wDeviceID = 0;
		Dflag = mciSendCommand (NULL, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE |
			MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT, (DWORD)(LPVOID) &OpenP);
		if(Dflag)
			return Dflag;
		m_wDeviceID = OpenP.wDeviceID;
		m_Open = TRUE;

		// 将时间格式设为tmsf格式
		MCI_SET_PARMS SetP;
		SetP.dwTimeFormat = MCI_FORMAT_MILLISECONDS ;//注意只有这种格式可以播放
		Dflag = mciSendCommand (m_wDeviceID, MCI_SET, MCI_SET_TIME_FORMAT, 
			(DWORD)(LPVOID) &SetP);
		if(Dflag)
		{
			Close ();
			return Dflag;
		}
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
	}
	return NULL;
}

DWORD CExMidi::Close ()
{
	DWORD Dflag;
	if (m_Open)
	{   // 停止播放关闭设备
		if (m_Playing || m_Pause)
			mciSendCommand (m_wDeviceID, MCI_STOP, NULL, NULL);
		Dflag = mciSendCommand (m_wDeviceID, MCI_CLOSE, NULL, NULL);
		if(Dflag)return Dflag;
		// 清空成员变量
		m_Open = m_Pause = m_Playing = FALSE;
		m_wDeviceID = 0;
	}
	return NULL;
}
DWORD CExMidi::Play ()
{
	DWORD Dflag;
	if (m_Open)
	{
		MCI_PLAY_PARMS PlayP;
		PlayP.dwCallback = NULL;
		PlayP.dwFrom = ((GetMinutes () * 60) + GetSeconds ()) * 1000;
		Dflag = mciSendCommand (m_wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &PlayP);
			return Dflag;
		m_Pause = FALSE;
		m_Playing = TRUE;
		return NULL;
	}
	return NULL;
}
void CExMidi::Stop ()
{
	if (m_Open && m_Playing)
	{
		mciSendCommand (m_wDeviceID, MCI_STOP, NULL, NULL);
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
		m_Playing = FALSE;
		m_Pause = FALSE;
	}
}

DWORD CExMidi::Pause( )
{
	DWORD Dflag;
	if (m_Open && m_Playing)
	{
		MCI_PLAY_PARMS PlayP;
		Dflag = mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, (DWORD)(LPVOID) &PlayP);
		if(Dflag)
			return Dflag;
		m_Pause = TRUE;
	}
	return NULL;
}

DWORD CExMidi::GetMidiLength (int *pnMinutes, int *pnSeconds)
{
	DWORD Dflag;
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_LENGTH;
		Dflag= mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP);
		if(Dflag)
		{
			*pnMinutes = -1;
			*pnSeconds = -1;
			return Dflag;
		}
		*pnMinutes = (StatusP.dwReturn / 1000) / 60;
		*pnSeconds = (StatusP.dwReturn / 1000) % 60;
		return NULL;
	}

	*pnMinutes = -1;
	*pnSeconds = -1;
	return NULL;
}
int CExMidi::GetMinutes ()
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP))
			return -1;
		return (int) ((StatusP.dwReturn / 1000) / 60);
	}

	return -1;
}

int CExMidi::GetSeconds ()
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP))
			return -1;
		return (int) ((StatusP.dwReturn / 1000) % 60);
	}

	return -1;
}

BOOL CExMidi::IsPlaying ()
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_MODE;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT
			| MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP))
			return FALSE;
		if (StatusP.dwReturn == MCI_MODE_PLAY)
		{
			m_Playing = TRUE;
			m_Pause = FALSE;
			return TRUE;
		}
		else if (StatusP.dwReturn == MCI_MODE_PAUSE)
		{
			m_Playing = TRUE;
			m_Pause = FALSE;
			return TRUE;
		}
		else
		{
			m_Playing = FALSE;
			m_Pause = FALSE;
			return FALSE;
		}
	}
	return FALSE;
}

DWORD CExMidi::SeekTo (int nMinute, int nSecond)
{
	DWORD Dflag;
	if (m_Open)
	{
		MCI_SEEK_PARMS SeekP;
		SeekP.dwTo = (nMinute * 60 + nSecond) * 1000;
		if (m_Playing && !m_Pause)
			mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, NULL);
		Dflag = mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekP);
		if(Dflag)
			return Dflag;
		if (m_Playing && !m_Pause)
		{
			Dflag = Play ();
			if(Dflag)return Dflag;
		}
		return NULL;
	}
	return NULL;
}
void CExMidi::Forward (int nSeconds)
{
	if (m_Open)
	{// 得到当前位置
		MCI_STATUS_PARMS StatusP;
		DWORD dwPos;
		StatusP.dwItem = MCI_STATUS_POSITION;
		mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP);
		dwPos = StatusP.dwReturn;
		// 将当前位置增加
		dwPos += (DWORD) nSeconds * 1000;
		// 停止并寻找位置
		MCI_SEEK_PARMS SeekP;
		SeekP.dwTo = dwPos;
		if (m_Playing && !m_Pause)
			mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, NULL);
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekP);
		// 恢复播放
		if (m_Playing && !m_Pause)
			Play ();
		}
}

void CExMidi::Backward (int nSeconds)
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		DWORD dwPos;
		StatusP.dwItem = MCI_STATUS_POSITION;
		mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP);
 		dwPos = StatusP.dwReturn;

		dwPos -= (DWORD) nSeconds * 1000;

		MCI_SEEK_PARMS SeekP;
		SeekP.dwTo = dwPos;
		if (m_Playing && !m_Pause)
			mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, NULL);
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekP);
		if (m_Playing && !m_Pause)
			Play ();
	}
}
