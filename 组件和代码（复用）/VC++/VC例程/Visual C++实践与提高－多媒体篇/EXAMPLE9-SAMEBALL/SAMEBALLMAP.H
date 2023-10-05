// SameBallMap.h: interface for the SameBallMap class.
// 编码: Leezy
// 最后修改日期：5.3
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAMEBALLMAP_H__94E17C77_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
#define AFX_SAMEBALLMAP_H__94E17C77_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_

#include "MapNode.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////KillBall Returns//////////
#define    KILLBALL_ERROR  -1
#define    KILLBALL_NOT     0
#define    KILLBALL_OK      1
#define    KILLBALL_GOTEND  2

//////////////////////Adjust Returns//////////
#define    ADJUST_ERROR -1
#define    ADJUST_OK     0
#define    ADJUST_GOTEND 1

//////////////////////Group Returns/////////////
#define    GROUP_ERROR  -1
#define    GROUP_NOGROUP 0
#define    GROUP_OK      1

//////////////////////SizeID ////////////////////
#define    BALL_SIZE64 64
#define    BALL_SIZE48 48
#define    BALL_SIZE32 32

//////////////////////MouseOn/////////////////////
#define    MOUSEON_ERROR      -1
#define    MOUSEON_OUTRANGE    0
#define    MOUSEON_NOTCHANGE     1
#define    MOUSEON_NOTSEL      2
#define    MOUSEON_SUCCESS     3

//////////////////////OnUndo//////////////////////
#define    ONUNDO_SUCCESS       0
#define    ONUNDO_ERROR			1
class SameBallMap  
{
// Attributes
public:
	int iRemain;
	int iRemainSaved;
	BOOL bCanUndo;
	MapNode BallMap[10][15];
private:
	BOOL bLocked;
	int  iActiveNumber;
	int iScoreCount;
	CPoint dPointNextActive;
	CPoint dPointNextStatic;
	Ball*   LastBallTrail[10][15];
// Operation
public:
	int OnUndo(int& rScore,int& rRemain);
	void SetSize(int nSize);
	MapNode* GetNextStatic();
	int BeginGetStatic();
	MapNode* GetNextActive();
	int BeginGetActive();
	int MouseOn(int nLine,int nColumn,int& rSelected);
	int KillBall(int nLine,int nColumn,int& rScoreCount,int& rRemainBalls);
	void ReNew();
	SameBallMap();
	virtual ~SameBallMap();

private:
	int iScoreSaved;
	void SaveUndo();
	int Group();
	int Adjust();
};

#endif // !defined(AFX_SAMEBALLMAP_H__94E17C77_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
