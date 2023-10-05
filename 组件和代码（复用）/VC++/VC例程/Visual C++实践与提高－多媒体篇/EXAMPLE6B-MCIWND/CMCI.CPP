// MciWnd.cpp : implementation file
//

#include "stdafx.h"
#include "MciWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
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

CMciWnd::CMciWnd()
{
	m_hWnd = NULL;
	m_Open = false;
	m_Playing = false;
	m_Pause = false;
	m_Step = false;
}

CMciWnd::~CMciWnd()
{
	Detach();
}


BEGIN_MESSAGE_MAP(CMciWnd, CWnd)
	//{{AFX_MSG_MAP(CMciWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMciWnd message handlers

//创建窗口
BOOL CMciWnd::Create(CWnd *pParentWnd, DWORD dwStyle, LPCSTR szFile)
{
	HWND hWnd = MCIWndCreate(pParentWnd->m_hWnd,
        AfxGetApp()->m_hInstance, dwStyle, szFile);
	if(hWnd != NULL)
	{
		this->Attach(hWnd);
		return true;
	}
	AfxMessageBox(_T("创建失败"));
	return false;
}

//打开文件
long CMciWnd::Open(LPCSTR szFile, WORD wFlags)
{
	int ret = MCIWndOpen(m_hWnd, szFile, wFlags);
	if(ret == 0)
	{
		m_Open = true;
	}
	return ret;
}

//播放文件
long CMciWnd::Play()
{
	if(m_Open)
	{
		m_Playing = true;
		m_Pause = false;
		return MCIWndPlay(m_hWnd);
	}
	else
		return false;
}

//停止播放
long CMciWnd::Stop()
{
	if(m_Open && m_Playing)
		return MCIWndStop(m_hWnd);
	else
		return false;
}

//暂停播放
long CMciWnd::Pause()
{
	if(m_Open && m_Playing)
	{
		m_Playing = false;
		m_Pause = true;
		return MCIWndPause(m_hWnd);
	}
	else
		return false;
}

//步进播放
long CMciWnd::Step(int step)
{
	m_Step = false;
	if(m_Open)
	{
		if(m_Playing)
		{
			Pause();
			m_Step = true;
		}
		return MCIWndStep(m_hWnd, step);
	}
	else
		return false;
}

//继续播放
long CMciWnd::Resume()
{
	if(m_Open && m_Pause && !m_Step)
		return MCIWndResume(m_hWnd);
	else
		return false;
}

//到头
long CMciWnd::Home()
{
	if(m_Open)
	{
		Pause();
		return MCIWndHome(m_hWnd);
	}
	else
		return false;
}

//到尾
long CMciWnd::End()
{
	if(m_Open)
	{
		Pause();
		return MCIWndEnd(m_hWnd);
	}
	else
		return false;
}

//关闭
long CMciWnd::Close()
{
	if(m_Open)
	{
		m_Open = false;
		if(m_Playing || m_Pause)
			MCIWndStop(m_hWnd);
		return MCIWndClose(m_hWnd);
	}
	else
		return false;
}

//得到源图像矩形
long CMciWnd::GetSourceRect(CRect &Rect)
{
	CRect D;
	if(m_Open)
		return MCIWndGetSource(m_hWnd, Rect);
	else
		return false;
}

//设置源图像矩形
long CMciWnd::PutSourceRect(CRect &Rect)
{
	if(m_Open)
		return MCIWndPutSource(m_hWnd, Rect);
	else
		return false;
}

//得到目的图像矩形
long CMciWnd::GetDestRect(CRect &Rect)
{
	if(m_Open)
		return MCIWndGetDest(m_hWnd, Rect);
	else
		return false;
}

//设置目的图像矩形
long CMciWnd::PutDestRect(CRect &Rect)
{
	if(m_Open)
		return MCIWndPutDest(m_hWnd, Rect);
	else
		return false;
}

//是否鼠标按下,将消息发父窗口
BOOL CMciWnd::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		GetParent()->SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}
	
	return CWnd::PreTranslateMessage(pMsg);
}