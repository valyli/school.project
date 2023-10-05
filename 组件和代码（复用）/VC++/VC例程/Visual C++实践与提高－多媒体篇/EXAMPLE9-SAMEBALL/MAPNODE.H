// MapNode.h: interface for the MapNode class.
// 编码: Leezy
// 最后修改日期：5.3
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPNODE_H__94E17C76_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
#define AFX_MAPNODE_H__94E17C76_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class MapNode  
{
// Attributes
public:
	Ball* pBall;
	MapNode* pT;
	MapNode* pL;
	MapNode* pB;
	MapNode* pR;
	int iGroupNumber;	// 0 Ungrouped,-1 Killed
	int iOsi;//没有用到这个参数
// Operation
public:
	CRect dRect;//用来设置区域大小
	void SetSize(int nL,int nT,int nR,int nB);
	void SetSize(CRect nRect);
	Ball* CopyFrom();
	Ball* MoveFrom();
	BOOL Hang(Ball* npBall);
	BOOL Kill();
	void Group(int nGroupNumber);
	BOOL SearchFriend();
	MapNode();
	virtual ~MapNode();
};

#endif // !defined(AFX_MAPNODE_H__94E17C76_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
