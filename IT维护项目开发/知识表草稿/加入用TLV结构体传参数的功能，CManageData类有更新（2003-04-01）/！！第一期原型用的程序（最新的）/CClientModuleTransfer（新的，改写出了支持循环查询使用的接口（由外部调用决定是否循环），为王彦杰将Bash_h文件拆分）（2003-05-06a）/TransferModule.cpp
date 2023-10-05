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
	lpfn = NULL;
	hLibrary = NULL;
}

CTransferModule::~CTransferModule()
{

}

//获取动态库的句柄和要调用的函数的句柄
//如果不存在此信息项，将返回false
bool CTransferModule::LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfomationListStruct &ModuleInfo)
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
		return false;
	}
	CString temp;

	//导入动态库
	hLibrary=LoadLibrary(m_InfoArray.GetAt(i).ServiceFileName);
	//若导入失败
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += m_InfoArray.GetAt(i).ServiceFileName;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}

	//从动态库中获取要调用的方法
	lpfn = (bool (__cdecl *)(CManageData&))GetProcAddress(hLibrary, m_InfoArray.GetAt(i).InterfaceFunction);
	//获取失败
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function Failed", "Load Library Error");
	}
	else
		return true;
}


//调用动态库中的方法
bool CTransferModule::CallTransferModule(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//如果获取函数指针失败
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function Failed", "Load Library Error");
	}
	else
	{
		//调用动态库中指定的方法
		bool flag = (*lpfn)(Data);
		return flag;
	}
}


//释放动态库
void CTransferModule::FreeTransferModule()
{
	lpfn = NULL;
	FreeLibrary(hLibrary);
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

	bool (FAR *lpfn_t)(ModuleInfomationStruct &InfoList);


	HMODULE hLibrary_t=LoadLibrary(strDllFilePath);
	if(hLibrary_t == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}
	lpfn_t = (bool (__cdecl *)(ModuleInfomationStruct&))GetProcAddress(hLibrary_t, "InfoList");
	if(lpfn_t == NULL)
	{
		FreeLibrary(hLibrary_t);
		return false;//AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
	}

	bool flag = (*lpfn_t)(m_Info);

	FreeLibrary(hLibrary_t);
	return true;
}