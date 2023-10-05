///////////////////////////////////////////////////////////////////////////////
//文件内容：自定义类型头文件，几乎被所有的文件导入
//作者：	李佳
//编写日期：2003-03-20
//需要文件：
//涉及调用：MSXML、afxtempl.h、BaseTransferStruct.h
///////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
#define AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_

///////////////////////////////////////////////////////////////////////////////
#include "BaseTransferStruct.h"

//Include for MSXML
#import <msxml.dll> named_guids
using namespace MSXML;

//Include for CArray
#include <afxtempl.h>
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////
//末尾加Value表示为值，加Ptr表示为指针
typedef enum tagDataType_TransferModule
{
	NoDefined,				//Not defined, error type
	int_Value,				//int
	long_Value,				//long
	unsigned_long_Value,	//unsigned long
	char_Value,				//char
	CString_Value,			//CString
	BOOL_Value,				//BOOL
	char_Ptr,				//char*
}DataType_TransferModule;

//记录DataType_TransferModule中定义的数据类型个数
#define Number_Of_DataType_TransferModule 7
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

//定义信息项表列表配置文件名
#define INFORMATION_ELEMENT_LIST_TABLE_FILENAME "InfomationElementListTable.xml"


//用于装载InfomationElementListTable信息
struct InfomationElementListTableStruct
{
	//在信息项表列表中的ID，从1起
	unsigned int InfomationElementTableID;
	//信息项表名称
	CString InfomationElementTableName_Chinese;
	//信息项表英文命名
	CString InfomationElementTableName_English;
	//描述
	CString Description;
	//等价信息表ID(0表示没有)
	unsigned int EqualInfomationElementTableID;
};


typedef CArray<InfomationElementListTableStruct, InfomationElementListTableStruct&> CArrayInfomationElementListTableStruct;

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//用于装载InfoList()返回信息
struct ModuleInfomationListStruct
{
	//操作ID
	unsigned int OperationID;
	//信息项表ID
	unsigned int InfomationElementTableID;
	//信息项ID
	unsigned int InfomationElementID;
	//操作类型
	unsigned int OperationType;
	//服务模块文件名
	CString ServiceFileName;
	//支持的操作系统类型（十六进制）
	unsigned long SupportSystemType;
	//模块类型
	unsigned int ModuleType;
	//接口函数
	CString InterfaceFunction;
	//参数类型
	unsigned int ParameterType;
	//参数记录返回值标记
	unsigned int IsStorageReturnValueInParameter;
	//参数值（可为空）
	CString ParameterValue;
};


typedef CArray<ModuleInfomationListStruct, ModuleInfomationListStruct&> CArrayModuleInfomationListStruct;

//用于返回整个动态库的全部信息
struct ModuleInfomationStruct
{
	//表明这个模块支持的模块定义
	unsigned int InfoModuleTypeProviderId;
	//表明按照该InfoModuleTypeProvider的模块类型定义，本模块属于哪个模块类型。
	unsigned int InfoModuleTypeId;
	//模块的制造商
	unsigned int InfoModuleProviderId;
	//本模块支持的是哪个信息项定义
	unsigned int InfoServiceProviderId;
	unsigned int NameBaseId;
	//用于返回动态库中操作的具体信息
	CArrayModuleInfomationListStruct ListArray;
};

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

//弹出警告信息
inline bool AlarmErrorMessage(CString ErrorMessage, CString ErrorMode)
{
	::MessageBox(0, ErrorMessage, ErrorMode, MB_OK|MB_ICONEXCLAMATION);
	return false;
}

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

//用于装载InfomationTable信息
struct InfomationElementStruct
{
	//在信息项表中的ID，从1起
	unsigned int InfomationElementID;
	//信息
	CString Infomation;
	//英文名称
	CString EnglishName;
	//信息类型参见参数类型，从1起
	unsigned int InfomationType;
	//描述
	CString Description;
};


typedef CArray<InfomationElementStruct, InfomationElementStruct&> CArrayInfomationElementStruct;
///////////////////////////////////////////////////////////////////////////////



#endif // !defined(AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
