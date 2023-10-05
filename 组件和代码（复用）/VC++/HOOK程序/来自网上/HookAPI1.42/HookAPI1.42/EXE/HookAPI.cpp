// ------------------------------------- //
// 您如果要使用本文件，请不要删除本说明  //
// ------------------------------------- //
//             HOOKAPI v1.4              //
//   Copyright 2002 编程沙龙 Paladin     //
//       www.ProgramSalon.com            //
// ------------------------------------- //

#include <windows.h>
#include "insthook.h"

#define MsgBox(msg) MessageBox(NULL, msg, "HookAPI 1.4 - www.programsalon.com", MB_OK)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(InitHookAPI() <0)
	{
		MsgBox("InitHookAPI error!");
		return 0;
	}

	if(HookAllProcesses() <0)
	{
		MsgBox("HookAllProcesses error!");

		return 0;
	}
	/// HookAllProcesses2是针对无法截获按Ctrl-Alt_Del键时运行的任务管理器等程序的情况使用的。
	/*if(HookAllProcesses2(1000) <0)
	{
		MsgBox("HookAllProcesses error!");

		return 0;
	}*/
	MsgBox("在测试前，请不要关闭本窗口。\n\n请打开一个网络程序如IE；再查看c:\\hookapi.log。\n\n\n欢迎光临【编程沙龙】：http://www.ProgramSalon.com\n\n近500M的几千个超级酷的C语言源码等着您去下载，光盘只要50元!\n\nHookAPI所有源码只售300元，高级会员只需要200元。\n\n\t\t\t\t\tPaladin 2002.05.01");

	UnhookAllProcesses();

	return 0;
}
