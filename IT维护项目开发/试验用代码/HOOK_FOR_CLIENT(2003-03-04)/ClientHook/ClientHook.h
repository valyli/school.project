/****************************************
*	文件隶属：			客户端HOOK监控程序
*	文件功用：			定义客户端监控类
*	模块类型：			动态库（DLL）
*	模块对外接口类型：	C语言
*	作者：				李佳
*	编写日期：			2003－03－04
****************************************/

#if !defined(AFX_TEST_H__4369983D_7CAA_4EF3_987A_EA6809F5A8A1__INCLUDED_)
#define AFX_TEST_H__4369983D_7CAA_4EF3_987A_EA6809F5A8A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientHookIDResource.h"

//定义客户端监控类
class AFX_EXT_CLASS CClientHook:public CObject  
{
public:
	//钩子类的构造函数
	CClientHook();
	//钩子类的析构函数
	~CClientHook();
	//安装钩子函数
	BOOL StartClientHook(HWND hWndReceiveMsg);
	//卸载钩子函数
	BOOL StopClientHook();
};

#endif // !defined(AFX_TEST_H__236D8263_C357_4BB7_89AF_CBB481D05232__INCLUDED_)
