// ServerJNITLVModule.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include <stdio.h>
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
//	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleC2S_Write");
//	CreateSemaphore(NULL, 0, 1, "ServerJNITLVModuleC2S_Read");
	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleC2S_CS");

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

	((unsigned char*)lpMapAddress)[0] = 0;
	
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
//	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleS2C_Write");
//	CreateSemaphore(NULL, 0, 1, "ServerJNITLVModuleS2C_Read");
	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleS2C_CS");

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

	((unsigned char*)lpMapAddress)[0] = 0;

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
tagSMM_c2s m_tagSMM_c2s;
//Transfer_C2S_Struct m_Data_Transfer_C2S_Struct;

//����ȫ�ֱ��������ڴ洢Ҫ���͵��ͻ��˵�����
tagSMM_s2c m_tagSMM_s2c;
//Transfer_S2C_Struct m_Data_Transfer_S2C_Struct;


//C2S
//��ȫ�ֱ���m_Data_Transfer_C2S_Struct��������������Transfer_C2S_Struct
//д����������
bool Set_C2S_toMapFile()
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

	//��ȡ�ź���
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_CS");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 1)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//д������
	for(int i = 1; i <= sizeof(tagSMM_c2s); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_tagSMM_c2s)[i];
    }

	((unsigned char*)lpMapAddress)[0] = 1;

	//�ͷ��ź���
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//S2C
//��ȫ�ֱ���m_Data_Transfer_S2C_Struct��������������Transfer_S2C_Struct
//д����������
bool Set_S2C_toMapFile()
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

	//��ȡ�ź���
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write");
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_CS");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 1)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//д������
	for(int i = 1; i <= sizeof(tagSMM_s2c); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_tagSMM_s2c)[i];
    }

	((unsigned char*)lpMapAddress)[0] = 1;

	//�ͷ��ź���
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//C2S
//�ӹ�����������ȡTLVStruct��ȫ�ֱ���m_Data
bool Get_C2S_fromMapFile()
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

	//��ȡ�ź���
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_CS");
	//�ȴ��ź���
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 0)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//��������
	for(int i = 1; i <= sizeof(tagSMM_c2s); i++)
    {
       ((unsigned char*)&m_tagSMM_c2s)[i] = ((unsigned char*)lpMapAddress)[i];
    }

	((unsigned char*)lpMapAddress)[0] = 0;

	//�ͷ��ź���
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//S2C
//�ӹ�����������ȡTLVStruct��ȫ�ֱ���m_Data
bool Get_S2C_fromMapFile()
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

	//��ȡ�ź���
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write"); //
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_CS"); //
	//�ȴ��ź���
//	::MessageBox(0, "ok", "", MB_OK);
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 0)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//��������
	for(int i = 1; i <= sizeof(tagSMM_s2c); i++)
    {
       //((unsigned char*)&m_tagSMM_s2c)[i] = ((unsigned char*)lpMapAddress)[i];
	 ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_tagSMM_s2c)[i] ;
	 //::MessageBox(0, "i", "", MB_OK);
    }
   
	((unsigned char*)lpMapAddress)[0] = 0;

	//�ͷ��ź���
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);
    //::MessageBox(0, "i", "", MB_OK);
	//�ͷ��ڴ��Ӵ����
	UnmapViewOfFile(lpMapAddress);
	
	return true;
}



//////////////////////////////////////////////////////////////////////////
//����ӿڣ�������ʱ���á��鿴�����ã����Թ������������в���

//ClientToServer��������

//ͨ��TLVStruct�ṹ������Ҫ�������������
bool Set_C2S(tagSMM_c2s Data)
{
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    {
       ((unsigned char*)&m_tagSMM_c2s)[i] = ((unsigned char*)&Data)[i];
    }
	//д�빲��������
	if(!Set_C2S_toMapFile())
		return false;
    return true;
}

//�ӹ����������ж�������
bool Get_C2S(tagSMM_c2s& Data)
{
	//���빲��������
	if(!Get_C2S_fromMapFile())
		return false;
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(tagSMM_c2s); i++)
    {
       ((unsigned char*)&Data)[i] = ((unsigned char*)&m_tagSMM_c2s)[i];
    }
    return true;
}



//ServerToClient��������

//ͨ��TLVStruct�ṹ������Ҫ�������������
bool Set_S2C(tagSMM_s2c Data)
{
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(tagSMM_s2c); i++)
    {
       ((unsigned char*)&m_tagSMM_s2c)[i] = ((unsigned char*)&Data)[i];
    }
	//д�빲��������
	if(!Set_S2C_toMapFile())
		return false;
    return true;
}

//�ӹ����������ж�������
bool Get_S2C(tagSMM_s2c& Data)
{
	//���빲��������
	if(!Get_S2C_fromMapFile())
		return false;
	//����TLVStruct�ṹ�е�����
    for(int i = 0; i < sizeof(tagSMM_s2c); i++)
    {
       ((unsigned char*)&Data)[i] = ((unsigned char*)&m_tagSMM_s2c)[i];
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
JNIEXPORT jboolean JNICALL Java_TestServelt_TestDll_getNewData(JNIEnv* env, jclass obj)
{
	return Get_C2S_fromMapFile();
}


//��ȡInfomationElementTableID
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getInfomationElementTableID(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.InfoBaseID.InfomationElementTableID;
}

//��ȡInfomationElementID
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getInfomationElementID(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.InfoBaseID.InfomationElementID;
}

//��ȡIP��ַ
JNIEXPORT jstring JNICALL Java_TestServelt_TestDll_getIP(JNIEnv* env, jobject obj)
{
    return env->NewStringUTF(m_tagSMM_c2s.cIp);
}

//��ȡ�˿ں�
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getPort(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.uiPort ;
}




//��ȡLocalTime�ַ���
JNIEXPORT jstring JNICALL Java_TestServelt_TestDll_getLocalTime(JNIEnv* env, jobject obj)
{
    return env->NewStringUTF(m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.LocalTime) ;
}


//��ȡ�������ݵ����͵ĺ���
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getDataType(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Type;
}


//jstring�ͷ���ֵ
JNIEXPORT jstring JNICALL Java_TestServelt_TestDll_getjstring(JNIEnv* env, jclass obj)
{
    return env->NewStringUTF(m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Value.Value_char);
}


//jint�ͷ���ֵ
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getjint(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Value.Value_int;
}

//jlong�ͷ���ֵ
JNIEXPORT jlong JNICALL Java_TestServelt_TestDll_getjlong(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Value.Value_long;
}




//��Java������ݵĺ�����������������������

//S2C
//����������д���µ�����
JNIEXPORT jboolean JNICALL Java_TestServelt_TestDll_setNewData(JNIEnv* env, jclass obj)
{
	return Get_S2C_fromMapFile();
}

//����InfomationElementTableID
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setInfomationElementTableID(JNIEnv* env, jobject obj, jint num)
{
    m_tagSMM_s2c.m_Data_Transfer_S2C_Struct.InfoBaseID.InfomationElementTableID = num;
}

//����InfomationElementID
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setInfomationElementID(JNIEnv* env, jobject obj, jint num)
{
    m_tagSMM_s2c.m_Data_Transfer_S2C_Struct.InfoBaseID.InfomationElementID = num;
}

//����IP��ַ
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setIP(JNIEnv* env, jobject obj, jcharArray i)
{
    
	jsize len = env->GetArrayLength(i);
    jchar *body = env->GetCharArrayElements(i, 0);
    for (int j=0; j<len; j++)
    {	
		m_tagSMM_s2c.cIp[j] = (char)body[j] ;
	}
    
    env->ReleaseCharArrayElements(i, body, 0);
    
}

//���ö˿ں�
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setPort(JNIEnv* env, jobject obj,jint j)
{
    m_tagSMM_s2c.uiPort = j;
}

