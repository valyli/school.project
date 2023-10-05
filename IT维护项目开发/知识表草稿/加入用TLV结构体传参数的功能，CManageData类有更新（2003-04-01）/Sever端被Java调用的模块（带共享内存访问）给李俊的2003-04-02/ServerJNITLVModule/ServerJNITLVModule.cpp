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

//共享数据区的句柄
HANDLE hShare;
//共享数据区内存映射的句柄
HANDLE hMapFile;

//创建共享数据区
bool CreateFileMapping_Server()
{
	hShare = ::CreateFileMapping(
		(HANDLE)0xFFFFFFFF,
		NULL,
		PAGE_READWRITE,
		0,
		1024,					//共享数据区大小
		"ServerJNITLVModule"	//命名空间：ServerJNITLVModule
		);
	//创建失败
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
		UnmapViewOfFile(hMapFile);
		CloseHandle(hShare);
		TRACE0("SERVERJNITLVMODULE.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(ServerJNITLVModuleDLL);
	}
	return 1;   // ok
}


//定义全局变量TLVData，用于存储客户端返回数据
TLVStruct m_Data;


//从全局变量m_Data向共享数据区设置TLVStruct
//写共享数据区
bool SetTLVtoMapFile()
{
	//获取共享数据区
	hMapFile = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModule");
	if(hMapFile == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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

	//写入数据
	for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)lpMapAddress)[i] = ((unsigned char*)&m_Data)[i];
    }

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return true;
}


//从共享数据区获取TLVStruct到全局变量m_Data
bool GetTLVfromMapFile()
{
	//获取共享数据区
	hMapFile = OpenFileMapping(FILE_MAP_WRITE, TRUE, "ServerJNITLVModule");
	if(hMapFile == NULL)
	{
		::MessageBox(0, "Could not Open file-mapping object.", "", MB_OK);
		return false;
	}
	//获取共享数据区中内存窗口句柄
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

	//读入数据
	for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)&m_Data)[i] = ((unsigned char*)lpMapAddress)[i];
    }

	//释放内存视窗句柄
	UnmapViewOfFile(lpMapAddress);
	return true;
}



//////////////////////////////////////////////////////////////////////////
//对外接口，供调试时设置、查看数据用，均对共享数据区进行操作

//通过TLVStruct结构体设置要处理的数据内容
bool SetTLV(TLVStruct TLVData)
{
	//复制TLVStruct结构中的数据
    for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)&m_Data)[i] = ((unsigned char*)&TLVData)[i];
    }
	//写入共享数据区
	if(!SetTLVtoMapFile())
		return false;
    return true;
}

//从共享数据区中读入数据
bool GetTLV(TLVStruct& TLVData)
{
	//读入共享数据区
	if(!GetTLVfromMapFile())
		return false;
	//复制TLVStruct结构中的数据
    for(int i = 0; i < sizeof(TLVStruct); i++)
    {
       ((unsigned char*)&TLVData)[i] = ((unsigned char*)&m_Data)[i];
    }
    return true;
}
/////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////
//以下代码供Java调用
//向Java返回数据的函数


//从共享数据区获得新的数据
JNIEXPORT jboolean JNICALL Java_jni_TestDll_NewData(JNIEnv* env, jclass obj)
{
	return GetTLVfromMapFile();
}


//获取返回数据的类型的函数
JNIEXPORT jint JNICALL Java_Get_DataType(JNIEnv* env, jobject obj)
{
    return m_Data.Type;
}


//jstring型返回值
JNIEXPORT jstring JNICALL Java_jni_TestDll_jstring(JNIEnv* env, jclass obj)
{
    return env->NewStringUTF(m_Data.Value.Value_Char);
}


//jint型返回值
JNIEXPORT jint JNICALL Java_Get_jint(JNIEnv* env, jobject obj)
{
    return m_Data.Value.Value_Int;
}
