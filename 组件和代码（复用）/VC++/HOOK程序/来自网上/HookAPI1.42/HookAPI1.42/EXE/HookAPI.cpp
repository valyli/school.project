// ------------------------------------- //
// �����Ҫʹ�ñ��ļ����벻Ҫɾ����˵��  //
// ------------------------------------- //
//             HOOKAPI v1.4              //
//   Copyright 2002 ���ɳ�� Paladin     //
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
	/// HookAllProcesses2������޷��ػ�Ctrl-Alt_Del��ʱ���е�����������ȳ�������ʹ�õġ�
	/*if(HookAllProcesses2(1000) <0)
	{
		MsgBox("HookAllProcesses error!");

		return 0;
	}*/
	MsgBox("�ڲ���ǰ���벻Ҫ�رձ����ڡ�\n\n���һ�����������IE���ٲ鿴c:\\hookapi.log��\n\n\n��ӭ���١����ɳ������http://www.ProgramSalon.com\n\n��500M�ļ�ǧ���������C����Դ�������ȥ���أ�����ֻҪ50Ԫ!\n\nHookAPI����Դ��ֻ��300Ԫ���߼���Աֻ��Ҫ200Ԫ��\n\n\t\t\t\t\tPaladin 2002.05.01");

	UnhookAllProcesses();

	return 0;
}
