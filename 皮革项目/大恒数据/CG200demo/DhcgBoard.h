// DhcgBoard.h: interface for the CDhcgBoard class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_DHCGBOARD_H__2FAEEE2C_62D0_11D4_A0B9_5254AB3256ED__INCLUDED_)
#define AFX_DHCGBOARD_H__2FAEEE2C_62D0_11D4_A0B9_5254AB3256ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mmsystem.h"
#include "cg210-32.h"
#include "cg200-32.h"
#include "VideoCGPara.h"
#include "DHCardID.h"
#include "CardMem.h"
//	#include "ddutil.h"
#include "DhCgboardGen.h"

class CDhcgBoard  
{
public:
	CDhcgBoard();
	virtual ~CDhcgBoard();
	
	BOOL InitialCgBoard(int CGOption,BOOL bDirectXSupport,HWND hwnd);
	void CloseCgBoard();

private:
	DWORD m_hCG;			//卡的句柄
	int m_cgType;			//卡的类型
	CRect m_recDisp;		//显示窗口，要求recDisp是屏幕坐标
	int m_AverNum;			//采集到内存的帧数,并平均
	CString m_IniName;		//存的INI文件名

	//Qiao,Memory operation
	DWORD m_dwPage;
	DWORD m_dwSize;
	DWORD m_PhysMemAddr;
	DWORD m_MemHandle;
	LPSTR m_LineAddr;

	//DirectX Support
	HWND m_hwnd_DDraw;
	BOOL	m_bDDrawInit;
	MMRESULT m_MMRESULT;
	int	TIMER_RESOLUTION;
	int m_WhereSurfaceIs;
public:
	int GetMaxAverageNum();
	BOOL GetDDarawInit();
	int GetAverageNum();
	int GetCGBoardType();
	DWORD GetCGBoardHandle();
	void GetVisualVideoRect(CRect& rec);
	void GetInputVideoRect(CRect& rec);
	void SetVisualVideoRect(CRect& recDisp);
	void SetInputVideoRect(CRect& rec);
	void SetAverageNum(int nAver);	//设置采集几幅图像到内存
	void SetCgBoardLiveOrFreeze(BOOL m_bLive);
	void DhBoardCaptureImage(HANDLE &hDIB);	//采集到内存,但不显示
	void DhBoardCaptureImage(HDC hDC,HANDLE &hDIB);	//采集到内存并显示
	
	//Qiao,2000.8.31
	//start
	int DhBoardSetColorSpace(BYTE Space);
	//根据屏幕的分辨率设置ColorSpace
	int DhBoardSetColorSpaceToScreen();
	int	DhBoardSnapOneToMem( DWORD dwOffset, BOOL bFrmMode );		//帧或场方式采集
	int DhBoardGetSnappingStatus( BOOL *pbFlag);
	void GetPhysicalMemInfo();
	int DhBoardWaitOddVSync();
	int DhBoardWaitVSync();
	int DhBoardEnableOverlay(BOOL Enable);
	int DhBoardSetDelay(WORD XDelay, WORD YDelay);
	int DhBoardSetDispMode(BOOL Mode);
	int DhBoardSetMask(BYTE Param, DWORD Address);
	int DhBoardSnap();

	DWORD GetPhysicalMemSize()
	{
		return m_dwSize;
		//return dwPage*4*1024;
	};
	DWORD GetPhysicalAdd()
	{
		return m_PhysMemAddr;
	};
	LPSTR GetLinearAdd()
	{
		return m_LineAddr;
	};
	DWORD GetPhysicalMemHandle()
	{
		return m_MemHandle;
	};

	//DirectX Support
	BOOL InitDirectDraw(HWND hwnd);
	void DDrawSample(BOOL m_bLive);
	//end//

	CVideoCGPara m_CVideoCGPara;
private:
	//DirectX Support
	void ReleaseDDrawObjects();
};

#endif // !defined(AFX_DHCGBOARD_H__2FAEEE2C_62D0_11D4_A0B9_5254AB3256ED__INCLUDED_)
