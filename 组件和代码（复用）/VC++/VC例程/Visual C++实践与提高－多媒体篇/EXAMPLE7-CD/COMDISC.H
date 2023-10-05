// CDAudio.h: interface for the CComDisc class.
//
//////////////////////////////////////////////////////////////////////
#include <afxwin.h>
#include <mmsystem.h>

#if !defined(AFX_CDAUDIO_H__19472651_7C1F_11D3_860F_8506BBC9783C__INCLUDED_)
#define AFX_CDAUDIO_H__19472651_7C1F_11D3_860F_8506BBC9783C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CComDisc  //处理播放CD
{
public:
	BOOL m_Open;//是否打开CD音轨
	BOOL m_Pause;//是否暂停
	BOOL m_Playing;//是否正在播放
	WORD m_wDeviceID;//播放设备ID

public:
	CComDisc();//构造函数
	virtual ~CComDisc();//构析函数
	DWORD Open ();//打开CD
	DWORD Close ();//关闭CD
	DWORD Plays (DWORD Dfrom,DWORD Dto);//播放CD
	DWORD Play ();//播放CD
	void Stop ();//停止播放
	DWORD Pause ();//暂停播放
	int GetTracks ();//得到音轨总数
	int GetTrack ();//得到当前音轨
	DWORD GetAudioLength (int *pnMinutes, int *pnSeconds);
	DWORD GetTrackLength (int nTrack, int *pnMinutes, int *pnSeconds);//得到音轨长度
	int GetMinutes ();//得到当前的分钟数
	int GetSeconds ();//得到当前的秒钟数
	int GetFrames ();//得到当前祯数
	DWORD Gettmsf(int nTrack,int nMinutes,int nSecond,int nFrames);//得到当前时间参数
	BOOL IsDriveReady ();    //CD是否准备好
	BOOL IsPlaying (BOOL *); //是否正在播放
	DWORD SeekTo (int nTrack, int nMinute, int nSecond, int Frame);//跳转函数
	BOOL CComDisc::IsAudioTrack (int nTrack);
	void OpenCDdoor (int flag);   //光驱操作
	void Forward (int step);      //前进
	void Backward (int);          //后退	
};

#endif // !defined(AFX_CDAUDIO_H__19472651_7C1F_11D3_860F_8506BBC9783C__INCLUDED_)
