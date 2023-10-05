// Ball.h: interface for the Ball class.
// 编码: Leezy
// 最后修改日期：5.1
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BALL_H__94E17C75_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
#define AFX_BALL_H__94E17C75_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//球类，用来决定求的状态
class Ball  
{
public:
	int iOsi;
	int iState;//
	int iClr;//颜色状态
	Ball();
//	Ball(int nClr);
//	Ball(int nClr,int nState);
	Ball(int nClr,int nState=0,int nOsi=0);
	virtual ~Ball();

};

#endif // !defined(AFX_BALL_H__94E17C75_1EE0_11D4_A0AA_0080AD76C3BA__INCLUDED_)
