// CDAudio.cpp: implementation of the CComDisc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ComDisc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CComDisc::CComDisc()
{
	// 初始化成员变量
	m_Open=FALSE;
	m_Pause=FALSE;
	m_Playing=FALSE;
	m_wDeviceID=0;
}

CComDisc::~CComDisc()
{
	Close ();
}
//////////////////////////////////////////////////////////////////////
// Member Functions
//////////////////////////////////////////////////////////////////////
DWORD CComDisc::Open ()
{
	if(m_Open)
	{
		AfxMessageBox("已经打开了CD");
	}
	if(!m_Open)
	{
		// 初始化成员变量
		m_Open = m_Pause = m_Playing = FALSE;
		m_wDeviceID = 0;
		// 打开设备
		MCI_OPEN_PARMS OpenP;
		OpenP.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;
		OpenP.wDeviceID = 0;
		DWORD Dflag;
		Dflag = mciSendCommand (NULL, MCI_OPEN, MCI_WAIT | MCI_OPEN_TYPE |
			MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE, (DWORD)(LPVOID) &OpenP);
		if(Dflag)
			return Dflag ;
		m_wDeviceID = OpenP.wDeviceID;
		m_Open = TRUE;
		// 设置时间格式
		MCI_SET_PARMS SetP;
		SetP.dwTimeFormat = MCI_FORMAT_TMSF;
		Dflag = mciSendCommand (m_wDeviceID, MCI_SET, MCI_WAIT
			| MCI_SET_TIME_FORMAT, (DWORD)(LPVOID) &SetP);
		if(Dflag){
			Close ();
			return Dflag;
		}
		//向MCI发送命令
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
	}
	return TRUE;
}

DWORD CComDisc::Close ()
{
	DWORD Dflag;
	if (m_Open){
		//停止播放且关闭设备
		if (m_Playing || m_Pause)
			mciSendCommand (m_wDeviceID, MCI_STOP, NULL, NULL);
		Dflag = mciSendCommand (m_wDeviceID, MCI_CLOSE, MCI_WAIT, NULL);
		if(Dflag)
			return Dflag;
		// 情空成员变量
		m_Open=FALSE;
		m_Pause=FALSE;
		m_Playing=FALSE;
		m_wDeviceID = 0;
	}
	return NULL;
}
DWORD CComDisc::Play ()
{
	DWORD Dflag;
	if (!m_Open){
		Dflag = Open ();
		if(Dflag)
			return Dflag;
	}

	if (m_Open)//播放
	{
		Dflag = IsAudioTrack (GetTrack ());
		if(!Dflag)
			return Dflag;
		MCI_PLAY_PARMS PlayParms;
		PlayParms.dwCallback = NULL;
		PlayParms.dwFrom = MCI_MAKE_TMSF (GetTrack (), GetMinutes (), GetSeconds (), GetFrames ());
		Dflag = mciSendCommand (m_wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &PlayParms);
		if(Dflag)	
			return Dflag;
		m_Pause = FALSE;
		m_Playing = TRUE;
		return NULL;
	}
	return NULL;
}
DWORD CComDisc::Plays (DWORD Dfrom,DWORD Dto)
{
	DWORD Dflag;
	if (!m_Open){
		Dflag = Open ();
		if(Dflag)
			return Dflag;
	}
	if (m_Open)//播放
	{
		Dflag = IsAudioTrack (GetTrack ());
		if(!Dflag)
			return Dflag;
		MCI_PLAY_PARMS PlayP;
		PlayP.dwCallback = NULL;
		PlayP.dwFrom = Dfrom;//MCI_MAKE_TMSF (GetTrack (), GetMinutes (),
			                 //GetSeconds (), GetFrames ());
		PlayP.dwTo = Dto;
		Dflag = mciSendCommand (m_wDeviceID, MCI_PLAY, MCI_FROM, (DWORD)(LPVOID) &PlayP);
		if(Dflag)	
			return Dflag;
		m_Pause = FALSE;
		m_Playing = TRUE;
		return TRUE;
	}
	return NULL;
}

//停止播放
void CComDisc::Stop ()
{
	if (m_Open && m_Playing){
		mciSendCommand (m_wDeviceID, MCI_STOP, MCI_WAIT, NULL);
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
		m_Playing = FALSE;
		m_Pause = FALSE;
		}
}

DWORD CComDisc::Pause()
{
	DWORD Dflag;
	if (m_Open && m_Playing)
	{
		// 暂停CD
		MCI_PLAY_PARMS PlayP;
		Dflag = mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, (DWORD)(LPVOID) &PlayP);
		if(Dflag)
			return Dflag;
		m_Pause = TRUE;
	}
	return NULL;
}
//得到CD上的总音轨数
int CComDisc::GetTracks ()
{
	if (m_Open){
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_NUMBER_OF_TRACKS;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS,
			MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP))
			return -1;
		return (int) StatusP.dwReturn;
		}

	return -1;
}
//得到CD总时间
DWORD CComDisc::GetAudioLength (int *nMinutes, int *nSeconds)
{
	DWORD Dflag;
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_LENGTH;
		Dflag = mciSendCommand (m_wDeviceID, MCI_STATUS,
			MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP);
		if(Dflag)
		{
			*nMinutes = -1;
			*nSeconds = -1;
			return Dflag;
		}
		*nMinutes = MCI_MSF_MINUTE (StatusP.dwReturn);
		*nSeconds = MCI_MSF_SECOND (StatusP.dwReturn);
		return NULL;
	}

	*nMinutes = -1;
	*nSeconds = -1;
	return NULL;
}
//得到音轨长度
DWORD CComDisc::GetTrackLength (int nTrack, int *nMinutes, int *nSeconds)
{
	DWORD Dflag;
	if (m_Open){
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_LENGTH;
		StatusP.dwTrack = (DWORD) nTrack;
		Dflag = mciSendCommand (m_wDeviceID, MCI_STATUS, 
			MCI_WAIT | MCI_STATUS_ITEM | MCI_TRACK, (DWORD)(LPVOID) &StatusP);
		if(Dflag){
			*nMinutes = -1;
			*nSeconds = -1;
			return Dflag;
			}
		*nMinutes = MCI_MSF_MINUTE (StatusP.dwReturn);
		*nSeconds = MCI_MSF_SECOND (StatusP.dwReturn);
		return NULL;
		}

	*nMinutes = -1;
	*nSeconds = -1;
	return NULL;
}
//得到当前音轨
int CComDisc::GetTrack ()
{
	if (m_Open)
	{
		// 保存当前位置
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM,
			(DWORD)(LPVOID) &StatusP))
			return -1;
		return MCI_TMSF_TRACK (StatusP.dwReturn);
	}
	return -1;
}

int CComDisc::GetMinutes ()
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, 
			(DWORD)(LPVOID) &StatusP))
			return -1;
		return MCI_TMSF_MINUTE (StatusP.dwReturn);
	}

	return -1;
}

int CComDisc::GetSeconds ()
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP))
			return -1;
		return MCI_TMSF_SECOND (StatusP.dwReturn);
	}

	return -1;
}

int CComDisc::GetFrames ()
{
	if (m_Open)
	{
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_POSITION;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, 
			MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP))
			return -1;
		return MCI_TMSF_FRAME (StatusP.dwReturn);
	}
	return -1;
}

BOOL CComDisc::IsDriveReady ()
{
	if (m_Open)
	{
		// CD-ROM是否准备好了
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_STATUS_MODE;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, 
			(DWORD)(LPVOID) &StatusP))
			return FALSE;
		if (StatusP.dwReturn == MCI_MODE_NOT_READY ||
			StatusP.dwReturn == MCI_MODE_OPEN)
			return FALSE;
		// 是否是CD音轨
		StatusP.dwItem = MCI_STATUS_MEDIA_PRESENT;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM,
			(DWORD)(LPVOID) &StatusP))
			return FALSE;
		return (BOOL) StatusP.dwReturn;
	}

	return FALSE;
}

BOOL CComDisc::IsAudioTrack (int nTrack)
{
	if (m_Open)
	{
		// 是否是CD音轨
		MCI_STATUS_PARMS StatusP;
		StatusP.dwItem = MCI_CDA_STATUS_TYPE_TRACK;
		StatusP.dwTrack = nTrack;
		if (mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_STATUS_ITEM |
			MCI_TRACK, (DWORD)(LPVOID) &StatusP))
			return FALSE;
		if (StatusP.dwReturn == MCI_CDA_TRACK_AUDIO)
			return TRUE;
	}

	return FALSE;
}

BOOL CComDisc::IsPlaying (BOOL *pbPaused)
{
	*pbPaused = m_Pause;

	return m_Playing;
}

DWORD CComDisc::SeekTo (int nTrack, int nMinute, int nSecond, int nFrame)
{
	DWORD Dflag;
	if (m_Open)
	{
		MCI_SEEK_PARMS SeekP;
		SeekP.dwTo = MCI_MAKE_TMSF (nTrack, nMinute, nSecond, nFrame);
		if (m_Playing && !m_Pause)
			mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, NULL);
		Dflag = mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, (DWORD)(LPVOID) &SeekP);
		if(Dflag)
			return Dflag;
		if (m_Playing && !m_Pause)
			Play ();
		return NULL;
		}
	return NULL;
}

void CComDisc::Forward (int nSeconds)
{
	if (m_Open)
	{
		// 得到当前位置
		MCI_STATUS_PARMS StatusP;
		DWORD dwPos;
		StatusP.dwItem = MCI_STATUS_POSITION;
		mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP);
		dwPos = StatusP.dwReturn;
		// 将位置增加
		dwPos += (DWORD) nSeconds;
		// 暂停并寻找位置
		MCI_SEEK_PARMS SeekP;
		SeekP.dwTo = dwPos;
		if (m_Playing && !m_Pause)
			mciSendCommand (m_wDeviceID, MCI_PAUSE, 0, NULL);
		mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_TO | MCI_WAIT, 
			(DWORD)(LPVOID) &SeekP);
		// 播放CD
		if (m_Playing && !m_Pause)
			Play ();
		}
}

void CComDisc::Backward (int nSeconds)
{
	if (m_Open)
	{
		// 得到当前位置
		MCI_STATUS_PARMS StatusP;
		DWORD dwPos;
		StatusP.dwItem = MCI_STATUS_POSITION;
		mciSendCommand (m_wDeviceID, MCI_STATUS, MCI_WAIT | MCI_STATUS_ITEM, (DWORD)(LPVOID) &StatusP);
		dwPos = StatusP.dwReturn;
		// 将当前位置减少
		dwPos -= (DWORD) nSeconds ;
		// 暂停并寻找位置
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
DWORD Gettmsf(int nTrack,int nMinutes,int nSecond,int nFrames)
{
	return MCI_MAKE_TMSF(nTrack,nMinutes,nSecond,nFrames);
}
void CComDisc::OpenCDdoor(int flag)
{
	if (m_Open)
	{
		Stop ();
	}
	mciSendCommand (m_wDeviceID, MCI_SET, MCI_SET_DOOR_OPEN, NULL);
}
