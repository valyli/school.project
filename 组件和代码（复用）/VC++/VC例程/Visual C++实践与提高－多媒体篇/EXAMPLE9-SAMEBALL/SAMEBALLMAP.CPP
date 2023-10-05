// SameBallMap.cpp: implementation of the SameBallMap class.
// 编码: Leezy
// 最后修改日期：5.8
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sameball.h"
#include "ball.h"
#include "Mapnode.h"
#include "SameBallMap.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SameBallMap::SameBallMap()
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			if(i>0)
				BallMap[i][j].pT=&BallMap[i-1][j];
			if(j>0)
				BallMap[i][j].pL=&BallMap[i][j-1];
			if(i<9)
				BallMap[i][j].pB=&BallMap[i+1][j];
			if(j<14)
				BallMap[i][j].pR=&BallMap[i][j+1];
		}
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			LastBallTrail[i][j]=NULL;
		}
//	ReNew();
	bCanUndo=false;
	srand((unsigned)time(NULL));
}

SameBallMap::~SameBallMap()
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			BallMap[i][j].Kill();
			if(LastBallTrail[i][j])
				delete LastBallTrail[i][j];
		}

}

void SameBallMap::ReNew()
{//初始化程序，功能： 生成无序的小球序列，赋给小球颜色
	int i,j;
	int iLine,iColumn;
	Ball* pB;
	iScoreCount=0;
	iScoreSaved=0;
	iRemainSaved=150;
	iRemain=150;
	bLocked=true;
	bCanUndo=false;		// add by leezy May.20
	for(i=0;i<10;i++)//晴空版面
		for(j=0;j<15;j++)
			BallMap[i][j].Kill();
	for(i=0;i<3;i++)
		for(j=0;j<50;j++)
		{
			while(1)
			{
				iColumn=rand()%15;//
				iLine=rand()%10;  //随机得到行列
				if(BallMap[iLine][iColumn].iGroupNumber<0)
					break;
			}
			pB=new Ball(i);
			if(!BallMap[iLine][iColumn].Hang(pB))
			{
				MessageBox(NULL,"初始化错误！","Error",MB_OK);
				return ;
			};
		}
	i=Adjust();
	ASSERT(i==ADJUST_OK);
	bLocked=false;

}


int SameBallMap::KillBall(int nLine, int nColumn, int &rScoreCount, int &rRemainBalls)	// May.1
{
	int iResult;
	int i,j,iKillGroup;
	int iKilledCount,iRemainBalls;
	if(bLocked)
		return KILLBALL_ERROR;
	if(nLine<0 || nLine>=10 || nColumn<0 || nColumn>=15)
		return KILLBALL_ERROR;
	if(!BallMap[nLine][nColumn].SearchFriend())
		return KILLBALL_NOT;
	bLocked=true;
	SaveUndo();
	iKilledCount=0;
	iRemainBalls=0;
	iKillGroup=BallMap[nLine][nColumn].iGroupNumber;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			if(BallMap[i][j].iGroupNumber==iKillGroup)
			{
				BallMap[i][j].Kill();
				iKilledCount++;
			}
			else
				if(BallMap[i][j].iGroupNumber>0)
					iRemainBalls++;

		}

	rScoreCount=iKilledCount-2;
	rScoreCount=rScoreCount*rScoreCount;
	rScoreCount+=iScoreCount;
	iScoreCount=rScoreCount;
	iRemain=iRemainBalls;
	rRemainBalls=iRemainBalls;
	if(rRemainBalls==0)
	{
		rScoreCount+=1000;
		iActiveNumber=0;	// Modified May.8
		bLocked=false;
		return KILLBALL_GOTEND;
	}
	iResult=Adjust();
	bLocked=false;
	if(iResult==ADJUST_OK)
	{
		return KILLBALL_OK;
	}
	if(iResult==ADJUST_GOTEND)
	{
		return KILLBALL_GOTEND;
	}
	return KILLBALL_ERROR;
}

int SameBallMap::Adjust()			// May.1
{
	int iResult;
	int i;
	MapNode*  pNode1,* pNode2,* pNode3,* pNode4;
	Ball*	      pBall1;

	// 
	for(i=0;i<15;i++)
	{
		pNode1=&BallMap[9][i];
		while(pNode1->pT!=NULL)
		{
			if(pNode1->iGroupNumber>=0)
			{
				pNode1=pNode1->pT;
				continue;
			}
			pNode2=pNode1->pT;
			while(pNode2!=NULL && pNode2->iGroupNumber<0)
				pNode2=pNode2->pT;
			if(pNode2==NULL)
				break;
			pBall1=pNode2->MoveFrom();
			pNode1->Hang(pBall1);
			pNode1=pNode1->pT;
		}
	}
	pNode1=&BallMap[9][0];
	while(pNode1->pR!=NULL)
	{
		if(pNode1->iGroupNumber>=0)
		{
			pNode1=pNode1->pR;
			continue;
		}
			pNode2=pNode1->pR;
			while(pNode2!=NULL && pNode2->iGroupNumber<0)
				pNode2=pNode2->pR;
			if(pNode2==NULL)
				break;
			pNode3=pNode1;
			pNode4=pNode2;
			while(pNode4 && pNode4->iGroupNumber>=0 )
			{
				pBall1=pNode4->MoveFrom();
				pNode3->Hang(pBall1);
				pNode4=pNode4->pT;
				pNode3=pNode3->pT;
			}
			pNode1=pNode1->pR;

	}

	iResult=Group();
	iActiveNumber=0;
	BeginGetActive();
	BeginGetStatic();
	if(iResult==GROUP_OK)
		return ADJUST_OK;
	if(iResult==GROUP_NOGROUP)
		return ADJUST_GOTEND;
	return ADJUST_ERROR;
}
//
int SameBallMap::Group()		// May.1
{
	int i,j,k;
	BOOL	bNoGroup;
	bNoGroup=true;
	for(i=0;i<10;i++)				// 将所有的节点的组号清零
		for(j=0;j<15;j++)
		{
			if(BallMap[i][j].iGroupNumber>0)  // -1　表示此节点已经删除挂球
				BallMap[i][j].iGroupNumber=0;
		}
	k=1;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			if(BallMap[i][j].pBall)
				if(BallMap[i][j].iGroupNumber==0)		// 非零表示已被自动归组
				{
					if(bNoGroup)
						if(BallMap[i][j].SearchFriend())
							bNoGroup=false;
					BallMap[i][j].Group(k); // 未被归组，指定此节点自行归组，下一组号加一
					k++;
				}
		}
	if(bNoGroup)
		return GROUP_NOGROUP;
	return GROUP_OK;

}

int SameBallMap::MouseOn(int nLine, int nColumn,int& rSelected)	// May.1
{
	int i,j;
	if(bLocked)
		return MOUSEON_ERROR;
	if(nLine<0 || nLine>=10 || nColumn<0 || nColumn>=15)
	{
		iActiveNumber=0;
		return MOUSEON_OUTRANGE;
	}
	if(BallMap[nLine][nColumn].iGroupNumber==iActiveNumber)
	{
		return MOUSEON_NOTCHANGE;
	}
	if(!BallMap[nLine][nColumn].SearchFriend())
	{
		iActiveNumber=0;
		return MOUSEON_NOTSEL;
	}
	iActiveNumber=BallMap[nLine][nColumn].iGroupNumber;
	rSelected=0;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			if(BallMap[i][j].iGroupNumber==iActiveNumber)
				rSelected++;
		}
	dPointNextActive.x=-1;
	dPointNextActive.y=0;
	if(rSelected==0)
		return MOUSEON_ERROR;
	return MOUSEON_SUCCESS;
}
//得到活动区域的小球状态
int SameBallMap::BeginGetActive()			// May.1
{
	dPointNextActive.x=-1;
	dPointNextActive.y=0;
	return 0;
}
//得到下一个需要绘制的活动区域
MapNode* SameBallMap::GetNextActive()		// May.1
{
	int i,j;
	if(bLocked)
		return NULL;
	for(i=dPointNextActive.y,j=dPointNextActive.x+1;i<10;i++,j=0)
	{
		while(j<15)
		{	
			if(BallMap[i][j].iGroupNumber==iActiveNumber)
			{
				dPointNextActive.x=j;
				dPointNextActive.y=i;
				return &BallMap[i][j];
			}
			j++;
		}
	}
	dPointNextActive.x=-1;
	dPointNextActive.y=0;
	return NULL;
}
//得到静止区域的状态
int SameBallMap::BeginGetStatic()	// May.1
{
	dPointNextStatic.x=-1;
	dPointNextStatic.y=0;
	return 0;
}
//得到下一个需要绘制的静止区域
MapNode* SameBallMap::GetNextStatic()	// May.1
{
	int i,j;
	if(bLocked)
		return NULL;
	for(i=dPointNextStatic.y,j=dPointNextStatic.x+1;i<10;i++,j=0)
	{
		while(j<15)
		{	
			if(BallMap[i][j].iGroupNumber!=iActiveNumber)
			{
				dPointNextStatic.x=j;
				dPointNextStatic.y=i;
				return &BallMap[i][j];
			}
			j++;
		}
	}
	dPointNextStatic.x=-1;
	dPointNextStatic.y=0;
	return NULL;
}

void SameBallMap::SetSize(int nSize)	// May.1
{
	int iLine,iColumn;
	BOOL tbLocked=bLocked;
	bLocked=true;
	for(iLine=0;iLine<10;iLine++)
		for(iColumn=0;iColumn<15;iColumn++)
		{
			BallMap[iLine][iColumn].SetSize(iColumn*nSize,iLine*nSize,(iColumn+1)*nSize-1,(iLine+1)*nSize-1);
		}
	bLocked=tbLocked;
}

void SameBallMap::SaveUndo()		// May.1
{
	int i,j;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			if(LastBallTrail[i][j])
				delete LastBallTrail[i][j];
			LastBallTrail[i][j]=BallMap[i][j].CopyFrom();
		}
	iScoreSaved=iScoreCount;
	iRemainSaved=iRemain;
	bCanUndo=true;
}

int SameBallMap::OnUndo(int& rScore,int& rRemain)			// May.1
{
	int i,j;
	if(bLocked)
		return ONUNDO_ERROR;
	bLocked=true;
	bCanUndo=false;
	for(i=0;i<10;i++)
		for(j=0;j<15;j++)
		{
			BallMap[i][j].Kill();
			BallMap[i][j].Hang(LastBallTrail[i][j]);
			LastBallTrail[i][j]=NULL;
		}
	if(Adjust()==ADJUST_ERROR)
		return ONUNDO_ERROR;
	iScoreCount=iScoreSaved;
	iRemain=iRemainSaved;
	rScore=iScoreCount;
	rRemain=iRemain;
	bLocked=false;
	return ONUNDO_SUCCESS;
}
