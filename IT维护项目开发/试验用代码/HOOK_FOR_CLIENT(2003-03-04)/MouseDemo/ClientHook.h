/****************************************
*	�ļ�������			�ͻ���HOOK��س���
*	�ļ����ã�			����ͻ��˼����
*	ģ�����ͣ�			��̬�⣨DLL��
*	ģ�����ӿ����ͣ�	C����
*	���ߣ�				���
*	��д���ڣ�			2003��03��04
****************************************/

#if !defined(AFX_TEST_H__4369983D_7CAA_4EF3_987A_EA6809F5A8A1__INCLUDED_)
#define AFX_TEST_H__4369983D_7CAA_4EF3_987A_EA6809F5A8A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientHookIDResource.h"

//����ͻ��˼����
class AFX_EXT_CLASS CClientHook:public CObject  
{
public:
	//������Ĺ��캯��
	CClientHook();
	//���������������
	~CClientHook();
	//��װ���Ӻ���
	BOOL StartClientHook(HWND hWndReceiveMsg);
	//ж�ع��Ӻ���
	BOOL StopClientHook();
};

#endif // !defined(AFX_TEST_H__236D8263_C357_4BB7_89AF_CBB481D05232__INCLUDED_)
