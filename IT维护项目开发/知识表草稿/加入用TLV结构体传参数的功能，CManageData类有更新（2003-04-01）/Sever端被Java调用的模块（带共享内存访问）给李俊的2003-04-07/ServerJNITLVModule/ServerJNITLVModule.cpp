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
HANDLE hShareC2S;
//�����������ڴ�ӳ��ľ��
HANDLE hMapFileC2S;

//�����������ľ��
HANDLE hShareS2C;
//�����������ڴ�ӳ��ľ��
HANDLE hMapFileS2C;


//��������������
bool CreateFileMappingC2S()
{
	hShareC2S = ::CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//������������С
		"ServerJNITLVModuleC2S"	//�����ռ䣺ServerJNITLVModule
		);
	//����ʧ��
	if(hShareC2S == NULL)
	{
		::MessageBox(0, "Could not create file-mapping C2S object.", "", MB_OK);
		return false;
	}
	return true;
}


//��������������
bool CreateFileMappingS2C()
{
	hShareC2S = ::CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//������������С
		"ServerJNITLVModuleS2C"	//�����ռ䣺ServerJNITLVModule
		);
	//����ʧ��
	if(hShareC2S == NULL)
	{
		::MessageBox(0, "Could not create file-mapping S2C object.", "", MB_OK);
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
		UnmapViewOfFile(hMapFileC2S);
		CloseHandle(hShareC2S);
		TRACE0("SERVERJNITLVMODULE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ServerJNITLVModuleDLL);
	}
	return 1;   // ok
}


//����ȫ�ֱ��������ڴ洢�ͻ��˷��ط���˵�����
Transfer_C2S_Struct m_Data_Transfer_C2S_Struct;

//����ȫ�ֱ��������ڴ洢Ҫ���͵��ͻ��˵�����
Transfer_S2C_Struct m_Data_Transfer_S2C_Struct;


//C2S
//��ȫ�ֱ���m_Data_Transfer_C2S_Struct��������������Transfer_C2S_Struct
//д����������
bool SetTransfer_C2S_StructtoMapFileC2S()
{
	//��ȡ����������
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//��ȡ�������������ڴ洰�ھ��
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileC2S, // Handle to mapping object. 
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
	for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_Data_Transfer_C2S_Struct)[i];
    }

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//S2C
//��ȫ�ֱ���m_Data_Transfer_S2C_Struct��������������Transfer_S2C_Struct
//д����������
bool SetTransfer_S2C_StructtoMapFileS2C()
{
	//��ȡ����������
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//��ȡ�������������ڴ洰�ھ��
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileS2C, // Handle to mapping object. 
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
	for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_Data_Transfer_S2C_Struct)[i];
    }

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//C2S
//�ӹ�����������ȡTLVStruct��ȫ�ֱ���m_Data
bool GetTransfer_C2S_StructfromMapFileC2S()
{
	//��ȡ����������
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//��ȡ�������������ڴ洰�ھ��
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileC2S, // Handle to mapping object. 
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
	for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    {
       ((unsigned char*)&m_Data_Transfer_C2S_Struct)[i] = ((unsigned char*)lpMapAddress)[i];
    }

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//S2C
//�ӹ�����������ȡTLVStruct��ȫ�ֱ���m_Data
bool GetTransfer_S2C_StructfromMapFileS2C()
{
	//��ȡ����������
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//��ȡ�������������ڴ洰�ھ��
	LPVOID lpMapAddress;
	lpMapAddress = MapViewOfFile(hMapFileS2C, // Handle to mapping object. 
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
	for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
    {
       ((unsigned char*)&m_Data_Transfer_S2C_Struct)[i] = ((unsigned char*)lpMapAddress)[i];
    }

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}



//////////////////////////////////////////////////////////////////////////
//����ӿڣ�������ʱ���á��鿴�����ã����Թ������������в���

//ClientToServer��������

//ͨ��TLVStruct�ṹ������Ҫ�������������
bool SetTransfer_C2S_StructC2S(Transfer_C2S_Struct Data)
{
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    {
       ((unsigned char*)&m_Data_Transfer_C2S_Struct)[i] = ((unsigned char*)&Data)[i];
    }
	//д�빲��������
	if(!SetTransfer_C2S_StructtoMapFileC2S())
		return false;
    return true;
}

//�ӹ����������ж�������
bool GetTransfer_C2S_StructC2S(Transfer_C2S_Struct& Data)
{
	//���빲��������
	if(!GetTransfer_C2S_StructfromMapFileC2S())
		return false;
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    {
       ((unsigned char*)&Data)[i] = ((unsigned char*)&m_Data_Transfer_C2S_Struct)[i];
    }
    return true;
}



//ServerToClient��������

//ͨ��TLVStruct�ṹ������Ҫ�������������
bool SetTransfer_S2C_StructS2C(Transfer_S2C_Struct Data)
{
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
    {
       ((unsigned char*)&m_Data_Transfer_S2C_Struct)[i] = ((unsigned char*)&Data)[i];
    }
	//д�빲��������
	if(!SetTransfer_S2C_StructtoMapFileS2C())
		return false;
    return true;
}

//�ӹ����������ж�������
bool GetTransfer_S2C_StructS2C(Transfer_S2C_Struct& Data)
{
	//���빲��������
	if(!GetTransfer_S2C_StructfromMapFileS2C())
		return false;
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(Transfer_S2C_Struct); i++)
    {
       ((unsigned char*)&Data)[i] = ((unsigned char*)&m_Data_Transfer_S2C_Struct)[i];
    }
    return true;
}

/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////
//���´��빩Java����
/////////////////////////////////////////////////////////////////

//��Java�������ݵĺ������ӹ�����������ȡ������

//C2S

//�ӹ�������������µ�����
JNIEXPORT jboolean JNICALL Java_jni_TestDll_getNewData(JNIEnv* env, jclass obj)
{
	return GetTransfer_C2S_StructfromMapFileC2S();
}


//��ȡInfomationElementTableID
JNIEXPORT jint JNICALL Java_jni_TestDll_getInfomationElementTableID(JNIEnv* env, jobject obj)
{
    return m_Data_Transfer_C2S_Struct.InfoBaseID.InfomationElementTableID;
}

//��ȡInfomationElementID
JNIEXPORT jint JNICALL Java_jni_TestDll_getInfomationElementID(JNIEnv* env, jobject obj)
{
    return m_Data_Transfer_C2S_Struct.InfoBaseID.InfomationElementID;
}

//��ȡLocalTime�ַ���
JNIEXPORT jstring JNICALL Java_jni_TestDll_getLocalTime(JNIEnv* env, jobject obj)
{
    return env->NewStringUTF(m_Data_Transfer_C2S_Struct.LocalTime);
}


//��ȡ�������ݵ����͵ĺ���
JNIEXPORT jint JNICALL Java_jni_TestDll_getDataType(JNIEnv* env, jobject obj)
{
    return m_Data_Transfer_C2S_Struct.Value.Type;
}


//jstring�ͷ���ֵ
JNIEXPORT jstring JNICALL Java_jni_TestDll_getjstring(JNIEnv* env, jclass obj)
{
    return env->NewStringUTF(m_Data_Transfer_C2S_Struct.Value.Value.Value_char);
}


//jint�ͷ���ֵ
JNIEXPORT jint JNICALL Java_jni_TestDll_getjint(JNIEnv* env, jobject obj)
{
    return m_Data_Transfer_C2S_Struct.Value.Value.Value_int;
}

//jlong�ͷ���ֵ
JNIEXPORT jlong JNICALL Java_jni_TestDll_getjlong(JNIEnv* env, jobject obj)
{
    return m_Data_Transfer_C2S_Struct.Value.Value.Value_long;
}




//��Java������ݵĺ�����������������������

//S2C
//����������д���µ�����
JNIEXPORT jboolean JNICALL Java_jni_TestDll_setNewData(JNIEnv* env, jclass obj)
{
	return GetTransfer_S2C_StructfromMapFileS2C();
}
