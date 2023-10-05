#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxwin.h>
#include <mmsystem.h>
#include <mciavi.h>
#include <digitalv.h>
class CWave  //处理波形类
{
public:
	BOOL m_Record;//是否在录音
	BOOL m_Open;//是否打开文件
	WORD m_wDeviceID;//播放设备ID
	BOOL m_Playing;
	CString m_Path;
public:
	CWave();//构造函数
	virtual ~CWave();//构析函数
	int GetDevices ();//得到播放设备
	DWORD Open ();//载入文件
	DWORD Close ();//关闭文件
	DWORD Play ();//播放
	void Stop ();//停止播放
	DWORD Record ();//录制
	DWORD Save (CString Filename);//保存
	WORD GetBitLong();//得到位长
	DWORD GetSampleRate();//得到采样率
	WORD GetChannel();//得到声道
	DWORD GetWaveLength();//得到音频长度
};
