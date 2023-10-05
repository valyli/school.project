///////////////////////////////////////////////////////////////////////////////
//文件内容：自定义类型头文件，几乎被所有的文件导入
//作者：	李佳
//编写日期：2003-03-20
//需要文件：
//涉及调用：MSXML、afxtempl.h
///////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
#define AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_

///////////////////////////////////////////////////////////////////////////////
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




///////////////////////////////////////////////////////////////////////////////
//以下为用于在网上传输数据和指令的数据结构定义


//存储数据值的共用体
union DataValueUnion
{
	char Value_char[256];
	long Value_long;
	int Value_int;
};


//TLV（Type－Length－Value）格式，其中的Type表示Value是什么，
//Length表示Value的长度，Value就是实际的数据。
//比如Type可以为CPU等实际采集的信息的类型；Length为8;Value为Pentium4。
struct TLVStruct
{
    int Type;
    long Length;
	DataValueUnion Value;
};


//命令操作对象用INFOBASEID表示
struct InfoBaseID_Struct
{
	//信息项表ID
	unsigned int InfomationElementTableID;
	//信息项ID
	unsigned int InfomationElementID;
};


//从服务端向客户端发送的指令和数据
struct Transfer_S2C_Struct
{
	//命令ID
	//0，Get
	//1，Set
	//-1，Stop
	int CommandID;
	//命令操作对象用INFOBASEID表示
	InfoBaseID_Struct InfoBaseID;
	//操作的数据值
	TLVStruct Value;
	//｛LOCAL／SERVER｝本地保存还是送服务器
	//0，LOCAL；1，SERVER
	int Position;
	//调用的频次
	double Cycle;
	//调用的总次数
	int Count;
	//以下时间格式为"2003-04-06 20:33:35"
	//发送时间
	char SendTime[20];
	//开始时间
	char StartTime[20];
	//结束时间
	char EndTime[20];
};


//从客户端向服务端返回的数据
struct Transfer_C2S_Struct
{
	//命令操作对象用INFOBASEID表示
	InfoBaseID_Struct InfoBaseID;
	//操作的数据值
	TLVStruct Value;
	//以下时间格式为"2003-04-06 20:33:35"
	//本地采样时间
	char LocalTime[20];
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//来自王彦杰的结构体
struct tagSMM_c2s
{
    //unsigned char cIp[19];  //ip地址
	char cIp[19];  //ip地址
    int  uiPort;     //端口
    Transfer_C2S_Struct m_Data_Transfer_C2S_Struct;
};


struct tagSMM_s2c
{
    //unsigned char cIp[19] ;  //ip地址
	char cIp[19] ;  //ip地址
    int  uiPort;     //端口
    Transfer_S2C_Struct m_Data_Transfer_S2C_Struct;
};
///////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
