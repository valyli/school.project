// MapNode.cpp: implementation of the MapNode class.
// 编码: Leezy
// 最后修改日期：5.2
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sameball.h"
#include "Ball.h"
#include "MapNode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

MapNode::MapNode()
{
	pBall=NULL;
	pT=pL=pR=pB=NULL;
	iGroupNumber=-1;

}

MapNode::~MapNode()
{
	if(pBall)
		delete pBall;
}

BOOL MapNode::SearchFriend()	//	Apr.30
{
	if(!pBall)
		return false;
	if(pT && pT->pBall && pT->pBall->iClr==pBall->iClr)
		return true;
	if(pL && pL->pBall && pL->pBall->iClr==pBall->iClr)
		return true;
	if(pR && pR->pBall && pR->pBall->iClr==pBall->iClr)
		return true;
	if(pB && pB->pBall && pB->pBall->iClr==pBall->iClr)
		return true;
	return false;
}

void MapNode::Group(int nGroupNumber)	// Apr.30
{
		// 此函数意义是察看四周是否有挂有同属性的球的节点
		// 如有，则通知他也编成此组nId
	ASSERT(pBall);
	iGroupNumber=nGroupNumber;
	if(pT && pT->iGroupNumber==0 && pT->pBall->iClr==pBall->iClr)
		pT->Group(nGroupNumber);
	if(pL && pL->iGroupNumber==0 && pL->pBall->iClr==pBall->iClr)
		pL->Group(nGroupNumber);
	if(pR && pR->iGroupNumber==0 && pR->pBall->iClr==pBall->iClr)
		pR->Group(nGroupNumber);
	if(pB && pB->iGroupNumber==0 && pB->pBall->iClr==pBall->iClr)
		pB->Group(nGroupNumber);
}

BOOL MapNode::Kill()				// Apr.30
{
	iGroupNumber=-1;
	//iOsi
	if(!pBall)
		return false;
	delete pBall;
	pBall=NULL;
	return true;
}

BOOL MapNode::Hang(Ball *npBall)	// Apr.30
{
	iGroupNumber=0;
	// iOsi
	if(pBall)
	{
		delete pBall;
		if(!npBall)
			iGroupNumber=-1;
		pBall=npBall;
		return false;
	}
	if(!npBall)
		iGroupNumber=-1;
	pBall=npBall;
	return true;

}

Ball* MapNode::MoveFrom()			// Apr.30
{									// 将本节点的球移出，此节点不再管这个球的释放
	if(!pBall)
		return NULL;
	Ball* tpBall;
	iGroupNumber=-1;
	// iOsi
	tpBall=pBall;
	pBall=NULL;
	return tpBall;
}

Ball* MapNode::CopyFrom()			// May.1
{									// 构造一个新的球，属性同本节点所挂的球，
									// 新球提交外部，不管理新球的释放
	if(!pBall)
		return NULL;
	Ball* tpBall=new Ball(pBall->iClr,pBall->iState,pBall->iOsi);
	return tpBall;
}

void MapNode::SetSize(CRect nRect)
{
	dRect.CopyRect(&nRect);
}

void MapNode::SetSize(int nL, int nT, int nR, int nB)
{
	dRect.SetRect(nL,nT,nR,nB);
}
