// TransferModule.cpp: implementation of the CTransferModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransferModule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransferModule::CTransferModule()
{
//	//在Client端检测当前目录下所有合法dll的信息
//	GetAllModuleInfoToMemory();
}

CTransferModule::~CTransferModule()
{

}

//调用动态库的类，只用于演示
bool CTransferModule::TransferModule(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//ModuleInfo中只使用InfomationElementTableID和InfomationElementID值，作用是进行比较用
	//比较结束后，所有数据都来源于Client端读入的数据，即m_InfoArray中
	//先判断在客户端在从当前目录中获取的操作表中是否存在想要调用的方法
	for(int i = 0; i < m_InfoArray.GetSize(); i++)
	{
		if(m_InfoArray.GetAt(i).InfomationElementTableID == ModuleInfo.InfomationElementTableID
			&& m_InfoArray.GetAt(i).InfomationElementID == ModuleInfo.InfomationElementID)
			break;
	}
	//如果没有相应的方法
	if(i >= m_InfoArray.GetSize())
	{
//		::MessageBox(0, "ServiceFileName is not Find", "CTransferModule", MB_OK);
		return false;
	}
/*	else
	{
		::MessageBox(0, m_InfoArray.GetAt(i).ServiceFileName, "ServiceFileName is Find", MB_OK);
	}
*/
	CString temp;
	bool flag;

	//导入动态库
	HMODULE hLibrary=LoadLibrary(m_InfoArray.GetAt(i).ServiceFileName);
	//若导入失败
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += m_InfoArray.GetAt(i).ServiceFileName;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}

	//函数指针定义
	//用lpfn定义函数指针
	//根据要求，函数指针的返回值都是bool型
	bool (FAR *lpfn)(CManageData &Data);

	//从动态库中获取要调用的方法
	lpfn = (bool (__cdecl *)(CManageData&))GetProcAddress(hLibrary, m_InfoArray.GetAt(i).InterfaceFunction);
	//获取失败
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function Failed", "Load Library Error");
	}
	else
	{
		//调用动态库中指定的方法
		flag = (*lpfn)(Data);


		//释放动态库
		FreeLibrary(hLibrary);

	}
	return true;
}



//在当前目录下搜索所有的合法dll信息，记录到m_InfoArray
bool CTransferModule::GetAllModuleInfoToMemory()
{
	m_InfoArray.RemoveAll();
	//查找当前目录下的所有dll文件
	_finddata_t FileInfo;
	int n = 0;
	long cur_n;
	int SizeOfArray;
	int i;
	ModuleInfomationStruct m_Info;
	ModuleInfomationListStruct m_InfoStruct;

	cur_n = _findfirst("*.dll", &FileInfo);
	//对第一个dll文件进行处理
	if(FileInfo.attrib != FILE_ATTRIBUTE_DIRECTORY && cur_n != -1L)
	{
			m_Info.ListArray.RemoveAll();
			if(GetInfoListFromDll(m_Info, FileInfo.name))
			{
//				::MessageBox(0, "合法文件，成功导入信息", FileInfo.name, MB_OK);
				//如果为合法dll，将信息加入操作表序列
				for(i = 0; i < m_Info.ListArray.GetSize(); i++)
				{
					m_InfoStruct = m_Info.ListArray.GetAt(i);
					SizeOfArray = m_InfoArray.GetSize();
					//重新设置操作ID，从1起
					m_InfoStruct.OperationID = SizeOfArray + 1;
					m_InfoArray.Add(m_InfoStruct);
				}
			}
/*			else
			{
				::MessageBox(0, "不是合法文件", FileInfo.name, MB_OK);
			}
*/	}
	//对后续找到的dll文件进行处理
	while(_findnext(cur_n, &FileInfo) == 0)
	{
		//当不为目录时，即文件
		if(FileInfo.attrib != FILE_ATTRIBUTE_DIRECTORY)
		{
//			::MessageBox(0, FileInfo.name, "", MB_OK);
			m_Info.ListArray.RemoveAll();
			if(GetInfoListFromDll(m_Info, FileInfo.name))
			{
//				::MessageBox(0, "合法文件，成功导入信息", FileInfo.name, MB_OK);
				//如果为合法dll，将信息加入操作表序列
				for(i = 0; i < m_Info.ListArray.GetSize(); i++)
				{
					m_InfoStruct = m_Info.ListArray.GetAt(i);
					SizeOfArray = m_InfoArray.GetSize();
					//重新设置操作ID，从1起
					m_InfoStruct.OperationID = SizeOfArray + 1;
					m_InfoArray.Add(m_InfoStruct);
				}
			}
/*			else
			{
				::MessageBox(0, "不是合法文件", FileInfo.name, MB_OK);
			}
*/		}
	}
	return true;
}



//获取dll信息，并用m_Info返回
//strDllFilePath为动态库的全路径
bool CTransferModule::GetInfoListFromDll(ModuleInfomationStruct &m_Info, CString strDllFilePath)
{
	CString temp;

	bool (FAR *lpfn)(ModuleInfomationStruct &InfoList);


	HMODULE hLibrary=LoadLibrary(strDllFilePath);
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}
	lpfn = (bool (__cdecl *)(ModuleInfomationStruct&))GetProcAddress(hLibrary, "InfoList");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
	}

	bool flag = (*lpfn)(m_Info);

	FreeLibrary(hLibrary);
	return true;
}