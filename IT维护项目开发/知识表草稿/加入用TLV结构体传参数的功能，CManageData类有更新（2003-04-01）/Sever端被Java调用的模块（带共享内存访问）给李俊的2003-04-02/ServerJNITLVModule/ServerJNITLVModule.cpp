// ServerJNITLVModule.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "jni.h"

#include "Base.h"

#include "TestDll.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE ServerJNITLVModuleDLL = { NULL, NULL };

//�����������ľ��
HANDLE hShare;
//�����������ڴ�ӳ��ľ��
HANDLE hMapFile;

//��������������
bool CreateFileMapping_Server()
{
	hShare = ::CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//������������С
		"ServerJNITLVModule"	//�����ռ䣺ServerJNITLVModule
		);
	//����ʧ��
	if(hShare == NULL)
	{
		::MessageBox(0, "Could not create file-mapping object.", "", MB_OK);
		return false;
	}
	return true;
}


extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
//�Ժ���ʽʹ��ʱ��������±�д�˴�
//		//����̬������ʱ����������������
//		if(!CreateFileMapping_Server())
//			return false;

		TRACE0("SERVERJNITLVMODULE.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(ServerJNITLVModuleDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(ServerJNITLVModuleDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		//����̬������ʱ
		//�ͷŹ���������
		UnmapViewOfFile(hMapFile);
		CloseHandle(hShare);
		TRACE0("SERVERJNITLVMODULE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ServerJNITLVModuleDLL);
	}
	return 1;   // ok
}


//����ȫ�ֱ���TLVData�����ڴ洢�ͻ��˷�������
TLVStruct m_Data;


//��ȫ�ֱ���m_Data��������������TLVStruct
//д����������
bool SetTLVtoMapFile()
{
	//��ȡ����������
	hMapFile = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModule");
	if(hMapFile == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//��ȡ�������������ڴ洰�ھ��
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFile, // Handle to mapping object. 
		FILE_MAP_WRITE,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		0);                                // Map entire file. 
	if (lpMapAddress == NULL)
	{ 
		::MessageBox(0, "Could not map view of file.", "", MB_OK);
		return false;
	} 

	//д������
	for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_Data)[i];
    }

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//�ӹ�����������ȡTLVStruct��ȫ�ֱ���m_Data
bool GetTLVfromMapFile()
{
	//��ȡ����������
	hMapFile = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModule");
	if(hMapFile == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//��ȡ�������������ڴ洰�ھ��
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFile, // Handle to mapping object. 
		FILE_MAP_WRITE,               // Read/write permission 
		0,                                 // Max. object size. 
		0,                                 // Size of hFile. 
		0);                                // Map entire file. 
	if (lpMapAddress == NULL)
	{ 
		::MessageBox(0, "Could not map view of file.", "", MB_OK);
		return false;
	} 

	//��������
	for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)&m_Data)[i] = ((unsigned char*)lpMapAddress)[i];
    }

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}



//////////////////////////////////////////////////////////////////////////
//����ӿڣ�������ʱ���á��鿴�����ã����Թ������������в���

//ͨ��TLVStruct�ṹ������Ҫ�������������
bool SetTLV(TLVStruct TLVData)
{
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)&m_Data)[i] = ((unsigned char*)&TLVData)[i];
    }
	//д�빲��������
	if(!SetTLVtoMapFile())
		return false;
    return true;
}

//�ӹ����������ж�������
bool GetTLV(TLVStruct& TLVData)
{
	//���빲��������
	if(!GetTLVfromMapFile())
		return false;
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)&TLVData)[i] = ((unsigned char*)&m_Data)[i];
    }
    return true;
}
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////
//���´��빩Java����
//��Java�������ݵĺ���


//�ӹ�������������µ�����
JNIEXPORT jboolean JNICALL Java_jni_TestDll_NewData(JNIEnv* env, jclass obj)
{
	return GetTLVfromMapFile();
}


//��ȡ�������ݵ����͵ĺ���
JNIEXPORT jint JNICALL Java_Get_DataType(JNIEnv* env, jobject obj)
{
    return m_Data.Type;
}


//jstring�ͷ���ֵ
JNIEXPORT jstring JNICALL Java_jni_TestDll_jstring(JNIEnv* env, jclass obj)
{
    return env->NewStringUTF(m_Data.Value.Value_Char);
}


//jint�ͷ���ֵ
JNIEXPORT jint JNICALL Java_Get_jint(JNIEnv* env, jobject obj)
{
    return m_Data.Value.Value_Int;
}
