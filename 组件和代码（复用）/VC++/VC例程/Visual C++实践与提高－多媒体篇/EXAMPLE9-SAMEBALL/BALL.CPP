// Ball.cpp: implementation of the Ball class.
// 编码: Leezy
// 最后修改日期：5.1
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sameball.h"
#include "Ball.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Ball::Ball()
{
	iClr=iOsi=iState=0;

}
/*
Ball::Ball(int nClr)
{
	iClr=nClr;
	iOsi=iState=0;

}
Ball::Ball(int nClr,int nState)
{
	iOsi=0;
	iClr=nClr;
	iState=nState;

}
*/
Ball::Ball(int nClr,int nState,int nOsi)
{
	iClr=nClr;
	iOsi=nOsi;
	iState=nState;

}

Ball::~Ball()
{
}

