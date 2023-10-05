// Midi.h: interface for the CExMidi class.
//
//////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>
#include <mmsystem.h>

class CExMidi  
{
public:
	BOOL m_Open;//是否打开MIDI文件
	BOOL m_Pause;//是否暂停
	BOOL m_Playing;//是否正在播放
	WORD m_wDeviceID;//播放设备ID
	CString m_name;
public:
	CExMidi();//构造函数
	virtual ~CExMidi();//构析函数
	int GetDevices ();//获得播放设备
	DWORD Open ();//打开MIDI文件
	DWORD Close ();//关闭MIDI文件
	DWORD Play ();//播放MIDI文件
	void Stop ();//停止播放MIDI文件
	DWORD Pause ();//暂停播放MIDI文件
    //函数功能-获得MIDI乐曲长度,*pnMinutes,*pnSeconds将会返回MIDI的分钟和秒钟
	DWORD GetMidiLength (int *pnMinutes, int *pnSeconds);
	int GetMinutes ();//获得当前播放的分钟数
	int GetSeconds ();//获得当前播放的秒钟数
	BOOL IsPlaying ();//是否正在播放
	//函数功能-跳到某位置，nMinutes,nSeconds-MIDI将要跳到的MIDI乐曲的位置
	DWORD SeekTo (int from, int to);
	void Forward (int step);//快进
	void Backward (int step);//后退	
};

