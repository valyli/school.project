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

//共享数据区的句柄
HANDLE hShareC2S;
//共享数据区内存映射的句柄
HANDLE hMapFileC2S;

//共享数据区的句柄
HANDLE hShareS2C;
//共享数据区内存映射的句柄
HANDLE hMapFileS2C;


//创建共享数据区
bool CreateFileMappingC2S()
{
	hShareC2S = ::CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//共享数据区大小
		"ServerJNITLVModuleC2S"	//命名空间：ServerJNITLVModule
		);
	//创建失败
	if(hShareC2S == NULL)
	{
		::MessageBox(0, "Could not create file-mapping C2S object.", "", MB_OK);
		return false;
	}
//	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleC2S_Write");
//	CreateSemaphore(NULL, 0, 1, "ServerJNITLVModuleC2S_Read");
	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleC2S_CS");

	//获取共享数据区
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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


//创建共享数据区
bool CreateFileMappingS2C()
{
	hShareC2S = ::CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//共享数据区大小
		"ServerJNITLVModuleS2C"	//命名空间：ServerJNITLVModule
		);
	//创建失败
	if(hShareC2S == NULL)
	{
		::MessageBox(0, "Could not create file-mapping S2C object.", "", MB_OK);
		return false;
	}
//	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleS2C_Write");
//	CreateSemaphore(NULL, 0, 1, "ServerJNITLVModuleS2C_Read");
	CreateSemaphore(NULL, 1, 1, "ServerJNITLVModuleS2C_CS");

	//获取共享数据区
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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
//以后正式使用时，最好如下编写此处
//		//当动态库生成时，建立共享数据区
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
		//当动态苦销毁时
		//释放共享数据区
		UnmapViewOfFile(hMapFileC2S);
		CloseHandle(hShareC2S);
		TRACE0("SERVERJNITLVMODULE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ServerJNITLVModuleDLL);
	}
	return 1;   // ok
}


//定义全局变量，用于存储客户端返回服务端的数据
tagSMM_c2s m_tagSMM_c2s;
//Transfer_C2S_Struct m_Data_Transfer_C2S_Struct;

//定义全局变量，用于存储要发送到客户端的数据
tagSMM_s2c m_tagSMM_s2c;
//Transfer_S2C_Struct m_Data_Transfer_S2C_Struct;


//C2S
//从全局变量m_Data_Transfer_C2S_Struct向共享数据区设置Transfer_C2S_Struct
//写共享数据区
bool Set_C2S_toMapFile()
{
	//获取共享数据区
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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

	//获取信号量
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_CS");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 1)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//写入数据
	for(int i = 1; i <= sizeof(tagSMM_c2s); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_tagSMM_c2s)[i];
    }

	((unsigned char*)lpMapAddress)[0] = 1;

	//释放信号量
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//S2C
//从全局变量m_Data_Transfer_S2C_Struct向共享数据区设置Transfer_S2C_Struct
//写共享数据区
bool Set_S2C_toMapFile()
{
	//获取共享数据区
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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

	//获取信号量
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write");
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_CS");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 1)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//写入数据
	for(int i = 1; i <= sizeof(tagSMM_s2c); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_tagSMM_s2c)[i];
    }

	((unsigned char*)lpMapAddress)[0] = 1;

	//释放信号量
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//C2S
//从共享数据区获取TLVStruct到全局变量m_Data
bool Get_C2S_fromMapFile()
{
	//获取共享数据区
	hMapFileC2S = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleC2S");
	if(hMapFileC2S == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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

	//获取信号量
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Read");
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_CS");
	//等待信号量
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 0)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//读入数据
	for(int i = 1; i <= sizeof(tagSMM_c2s); i++)
    {
       ((unsigned char*)&m_tagSMM_c2s)[i] = ((unsigned char*)lpMapAddress)[i];
    }

	((unsigned char*)lpMapAddress)[0] = 0;

	//释放信号量
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleC2S_Write");
	ReleaseSemaphore(hSemaphore, 1, NULL);

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//S2C
//从共享数据区获取TLVStruct到全局变量m_Data
bool Get_S2C_fromMapFile()
{

	//获取共享数据区
	hMapFileS2C = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModuleS2C");
	if(hMapFileS2C == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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

	//获取信号量
//	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Write"); //
	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_CS"); //
	//等待信号量
//	::MessageBox(0, "ok", "", MB_OK);
	WaitForSingleObject(hSemaphore, INFINITE);

	if(((unsigned char*)lpMapAddress)[0] == 0)
	{
		ReleaseSemaphore(hSemaphore, 1, NULL);
		return false;
	}

	//读入数据
	for(int i = 1; i <= sizeof(tagSMM_s2c); i++)
    {
       //((unsigned char*)&m_tagSMM_s2c)[i] = ((unsigned char*)lpMapAddress)[i];
	 ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_tagSMM_s2c)[i] ;
	 //::MessageBox(0, "i", "", MB_OK);
    }
   
	((unsigned char*)lpMapAddress)[0] = 0;

	//释放信号量
//	hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, "ServerJNITLVModuleS2C_Read");
	ReleaseSemaphore(hSemaphore, 1, NULL);
    //::MessageBox(0, "i", "", MB_OK);
	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	
	return true;
}



//////////////////////////////////////////////////////////////////////////
//对外接口，供调试时设置、查看数据用，均对共享数据区进行操作

//ClientToServer共数据区

//通过TLVStruct结构体设置要处理的数据内容
bool Set_C2S(tagSMM_c2s Data)
{
	//复制TLVStruct结构中的数据
    for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
    {
       ((unsigned char*)&m_tagSMM_c2s)[i] = ((unsigned char*)&Data)[i];
    }
	//写入共享数据区
	if(!Set_C2S_toMapFile())
		return false;
    return true;
}

//从共享数据区中读入数据
bool Get_C2S(tagSMM_c2s& Data)
{
	//读入共享数据区
	if(!Get_C2S_fromMapFile())
		return false;
	//复制TLVStruct结构中的数据
    for(int i = 0; i < sizeof(tagSMM_c2s); i++)
    {
       ((unsigned char*)&Data)[i] = ((unsigned char*)&m_tagSMM_c2s)[i];
    }
    return true;
}



//ServerToClient共数据区

//通过TLVStruct结构体设置要处理的数据内容
bool Set_S2C(tagSMM_s2c Data)
{
	//复制TLVStruct结构中的数据
    for(int i = 0; i < sizeof(tagSMM_s2c); i++)
    {
       ((unsigned char*)&m_tagSMM_s2c)[i] = ((unsigned char*)&Data)[i];
    }
	//写入共享数据区
	if(!Set_S2C_toMapFile())
		return false;
    return true;
}

//从共享数据区中读入数据
bool Get_S2C(tagSMM_s2c& Data)
{
	//读入共享数据区
	if(!Get_S2C_fromMapFile())
		return false;
	//复制TLVStruct结构中的数据
    for(int i = 0; i < sizeof(tagSMM_s2c); i++)
    {
       ((unsigned char*)&Data)[i] = ((unsigned char*)&m_tagSMM_s2c)[i];
    }
    return true;
}

/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////
//以下代码供Java调用
/////////////////////////////////////////////////////////////////

//向Java返回数据的函数，从共享数据区获取的数据

//C2S

//从共享数据区获得新的数据
JNIEXPORT jboolean JNICALL Java_TestServelt_TestDll_getNewData(JNIEnv* env, jclass obj)
{
	return Get_C2S_fromMapFile();
}


//获取InfomationElementTableID
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getInfomationElementTableID(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.InfoBaseID.InfomationElementTableID;
}

//获取InfomationElementID
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getInfomationElementID(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.InfoBaseID.InfomationElementID;
}

//获取IP地址
JNIEXPORT jstring JNICALL Java_TestServelt_TestDll_getIP(JNIEnv* env, jobject obj)
{
    return env->NewStringUTF(m_tagSMM_c2s.cIp);
}

//获取端口号
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getPort(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.uiPort ;
}




//获取LocalTime字符串
JNIEXPORT jstring JNICALL Java_TestServelt_TestDll_getLocalTime(JNIEnv* env, jobject obj)
{
    return env->NewStringUTF(m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.LocalTime) ;
}


//获取返回数据的类型的函数
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getDataType(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Type;
}


//jstring型返回值
JNIEXPORT jstring JNICALL Java_TestServelt_TestDll_getjstring(JNIEnv* env, jclass obj)
{
    return env->NewStringUTF(m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Value.Value_char);
}


//jint型返回值
JNIEXPORT jint JNICALL Java_TestServelt_TestDll_getjint(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Value.Value_int;
}

//jlong型返回值
JNIEXPORT jlong JNICALL Java_TestServelt_TestDll_getjlong(JNIEnv* env, jobject obj)
{
    return m_tagSMM_c2s.m_Data_Transfer_C2S_Struct.Value.Value.Value_long;
}




//从Java获得数据的函数，向共享数据区设置数据

//S2C
//向共享数据区写入新的数据
JNIEXPORT jboolean JNICALL Java_TestServelt_TestDll_setNewData(JNIEnv* env, jclass obj)
{
	return Get_S2C_fromMapFile();
}

//设置InfomationElementTableID
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setInfomationElementTableID(JNIEnv* env, jobject obj, jint num)
{
    m_tagSMM_s2c.m_Data_Transfer_S2C_Struct.InfoBaseID.InfomationElementTableID = num;
}

//设置InfomationElementID
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setInfomationElementID(JNIEnv* env, jobject obj, jint num)
{
    m_tagSMM_s2c.m_Data_Transfer_S2C_Struct.InfoBaseID.InfomationElementID = num;
}

//设置IP地址
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

//设置端口号
JNIEXPORT void JNICALL Java_TestServelt_TestDll_setPort(JNIEnv* env, jobject obj,jint j)
{
    m_tagSMM_s2c.uiPort = j;
}

