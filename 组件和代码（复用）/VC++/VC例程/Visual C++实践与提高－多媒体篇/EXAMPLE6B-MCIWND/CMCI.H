#if !defined(AFX_MCIWND_H__B4977901_E517_11D2_9E71_CCEC0F07384E__INCLUDED_)
#define AFX_MCIWND_H__B4977901_E517_11D2_9E71_CCEC0F07384E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MciWnd.h : header file
//

//连接Video for Window 库
#include<vfw.h>

#ifndef _VFW
#define _VFW
#pragma comment(lib,"vfw32.lib")
#endif

//连接多媒体库
#include<mmsystem.h>

#ifndef _WINMM
#define _WINMM 

#pragma comment(lib,"winmm.lib")
#endif

/////////////////////////////////////////////////////////////////////////////
//
// CMciWnd
//
// 多媒体播放
//
// 完成功能:
//     对视频的播放与单帧捕捉
//
/////////////////////////////////////////////////////////////////////////////

class CMciWnd : public CWnd
{
// Construction
public:
	CMciWnd();

// Attributes
public:
	BOOL m_Open;					//是否打开
	BOOL m_Playing;				//是否播放
	BOOL m_Pause;					//是否暂停
	BOOL m_Step;					//是否步进
	CString m_str;
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMciWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	//得到源图像矩形
	long GetSourceRect(CRect & Rect);
	//设置源图像矩形
	long PutSourceRect(CRect & Rect);
	//得到目的图像矩形
	long GetDestRect(CRect & Rect);
	//得到源图像矩形
	long PutDestRect(CRect & Rect);
	//关闭
	long Close();	
	//到尾
	long End();
	//到头
	long Home();
	//继续
	long Resume();
	//步进
	long Step(int step = 1);
	//暂停
	long Pause();
	//停止
	long Stop();
	//播放
	long Play();

	//打开文件
	long Open(LPCSTR szFile, WORD wFlags = 0);

	//创建窗口
	BOOL Create(CWnd * pParentWnd, 
		DWORD dwStyle = WS_CAPTION
		| WS_CHILD	
		| WS_VISIBLE
		| MCIWNDF_NOMENU 
		| MCIWNDF_NOPLAYBAR 
		| MCIWNDF_SHOWNAME 
		| MCIWNDF_SHOWPOS,
		LPCSTR szFile = NULL);

	virtual ~CMciWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMciWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MCIWND_H__B4977901_E517_11D2_9E71_CCEC0F07384E__INCLUDED_)
