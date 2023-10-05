#include "stdafx.h"
#include "waveaudio.h"
#include <afxwin.h>
#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CWave::CWave()
{
	m_Record = FALSE;
	m_Open = FALSE;
	m_wDeviceID = 0;
	m_Playing  = FALSE;
}
CWave::~CWave()
{
	Close();
}
int CWave::GetDevices ()
{
	return waveOutGetNumDevs ();
}
DWORD CWave::Open()
{
	Close ();
	DWORD Openflag;
	MCI_OPEN_PARMS OpenP;
	OpenP.lpstrDeviceType = "waveaudio";
	OpenP.lpstrElementName = m_Path;
	Openflag = mciSendCommand (NULL, MCI_OPEN, MCI_OPEN_ELEMENT 
		| MCI_OPEN_TYPE, (DWORD)(LPVOID) &OpenP);
	if(Openflag)
		return Openflag;
	Openflag = NULL;
	m_wDeviceID = OpenP.wDeviceID;
	m_Open = TRUE;
	MCI_SET_PARMS SetP;
	SetP.dwTimeFormat=MCI_FORMAT_MILLISECONDS;
	Openflag = mciSendCommand(m_wDeviceID,MCI_SET,MCI_SET_TIME_FORMAT,
		(DWORD)(LPVOID) &SetP);
	if(Openflag)
		return Openflag;
	return NULL;
}
DWORD CWave::Close ()
{
	m_Record = FALSE;
	m_Open = FALSE;
	m_Playing = FALSE;
	DWORD Closeflag;
	if (m_wDeviceID){
		mciSendCommand (m_wDeviceID, MCI_STOP, MCI_WAIT, NULL);
		Closeflag = mciSendCommand (m_wDeviceID, MCI_CLOSE, NULL, NULL);
		}
	if(Closeflag)
	{
		AfxMessageBox("¹Ø±Õ³öÏÖ´íÎó");
		return Closeflag;
	}
	m_wDeviceID = 0;
}

DWORD CWave::Play ()
{
	Stop ();
	MCI_PLAY_PARMS PlayP;
	mciSendCommand (m_wDeviceID, MCI_SEEK, MCI_SEEK_TO_START, NULL);
	DWORD Playflag = mciSendCommand (m_wDeviceID,
		MCI_PLAY,NULL,(DWORD)(LPVOID) &PlayP);
	if(Playflag)
		return Playflag;
	else{
		m_Playing = 1;
		return NULL;
	}
}
void CWave::Stop ()
{
	mciSendCommand (m_wDeviceID, MCI_STOP, NULL, NULL);
}

DWORD CWave::Record ()
{
	Close ();
	DWORD Recflag;
	MCI_OPEN_PARMS OpenP;
	OpenP.lpstrDeviceType = "waveaudio";
	OpenP.lpstrElementName = "";
	Recflag = mciSendCommand (NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE 
		| MCI_WAIT, (DWORD)(LPVOID) &OpenP);
	if(Recflag)
		return Recflag;
	m_wDeviceID = OpenP.wDeviceID;
	MCI_RECORD_PARMS RecordP;
	Recflag = mciSendCommand (m_wDeviceID, MCI_RECORD, NULL,
		(DWORD)(LPVOID) &RecordP);
	if(Recflag)
		return Recflag;
	m_Record = TRUE;
	m_Open = TRUE;
   	return NULL;
}

DWORD CWave::Save (CString Filename)
{
	if (!m_Record)
		return FALSE;
	Stop ();
	MCI_SAVE_PARMS SaveP;
	SaveP.lpfilename = (LPCSTR) Filename;
	DWORD Saveflag = mciSendCommand (m_wDeviceID, MCI_SAVE, MCI_SAVE_FILE | MCI_WAIT, 
		(DWORD)(LPVOID) &SaveP);
	if(Saveflag)
		return Saveflag;

	m_Record = FALSE;
//	Open();
	return NULL;
}

DWORD CWave::GetSampleRate()
{
	MCI_STATUS_PARMS StatusP;
	StatusP.dwItem=MCI_WAVE_STATUS_SAMPLESPERSEC;
	if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusP))
		return -1;
	else return StatusP.dwReturn;
}
WORD CWave::GetChannel()
{
	MCI_STATUS_PARMS StatusP;
	StatusP.dwItem=MCI_WAVE_STATUS_CHANNELS;
	if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusP))
		return -1;
	else return StatusP.dwReturn;
}
WORD CWave::GetBitLong()
{
	MCI_STATUS_PARMS StatusP;
	StatusP.dwItem=MCI_WAVE_STATUS_BITSPERSAMPLE;
	if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,(DWORD)(LPVOID) &StatusP))
		return -1;
	else return StatusP.dwReturn;
}
DWORD CWave::GetWaveLength()
{
	MCI_STATUS_PARMS StatusP;
	StatusP.dwItem=MCI_STATUS_LENGTH;
	if(mciSendCommand(m_wDeviceID,MCI_STATUS,MCI_WAIT|MCI_STATUS_ITEM,
		(DWORD)(LPVOID) &StatusP))
		return -1;
	else return StatusP.dwReturn;
}
