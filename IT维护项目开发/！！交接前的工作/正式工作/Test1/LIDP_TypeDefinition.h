#if !defined(LIDP_TypeDefinition_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_)
#define LIDP_TypeDefinition_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_

#include "smm.h"
#include "ForXecro.h"
#include "LIDP_CArrayTemplate.h"

//LIDP返回值
#define LIDP_OK		1
#define LIDP_ERR	0
#define LIDP_NULL	0
//指令ID
#define COMMAND_DRIVER		1
#define COMMAND_MANAGEMENT	2

//传输类型
#define TRANSFER_INSTRUCTION		1		//来自服务端的指令
#define TRANSFER_DRIVERREUTRNBLOCK	2		//客户端的返回数据
#define TRANSFER_REQUEST			3		//来自客户端的请求




////////////////////////////////////////////////////////////////////////////////////
//此部分主要用于传输数据，所以使用结构体，而不使用类，因为对象很难描述自身大小
//
//规定：
//	被包含的结构体实例在内存空间的分布上，必须是接续在包含它的结构体的实例之后。（LIDP内部使用的可以不用）
//	如此才可以使结构体在交付给LIDP外部进行传输时的操作变得简单
////////////////////////////////////////////////////////////////////////////////////

//变量类型定义
enum LIDP_enumVariantType
{
	LIDP_NoDefined = 0,			//Not defined, error type, 0
	LIDP_string = 1,			//String
	LIDP_Integer = 2,			//Integer
	LIDP_Binary = 3,			//Binary（字节） 
	LIDP_Real = 4				//Real
};

//记录LIDP_VariantType中定义的数据类型个数，不含0 
#define LIDP_Number_Of_VariantType 4


//变量存储结构 
struct LIDP_tagVariant
{
	//用于判断变量类型
	LIDP_enumVariantType Type;
	//以下数据的长度，按字节计算。当为SMM_CHAR*或SMM_UCHAR*时，此值有效，其余情况全为0
	SMM_INT32 Length;
	//主要用于对外传输数据，所以选用SMM中的类型
	SMM_UCHAR* Buff;
};

//参数表，用于对外传递参数，支持多参数，多类型
//只对基本参数类型：LIDP_VariantType有效
struct LIDP_tagVariantParameterList
{
	//参数的个数
	SMM_INT32 NumOfList;
	//变量指针数组，用于指向变量
	LIDP_tagVariant** List;
};

//模块调用命令
//供Driver模块使用
struct LIDP_tagDriverCommand
{
	SMM_INT32 TASKID;
	//用于确定信息项
	SMM_INT32 InfoBaseProviderID; 
	SMM_INT32 InfoBaseID;
	//信息项ID串，串中的每一项都为4个字节，是一个整型值
	SMM_INT32 NumOfInfoItemID;
	SMM_INT32* InfoItemID;
	SMM_INT32 ActionID;
	//供指令使用的参数表 
	LIDP_tagVariantParameterList ParameterList;
	//｛LOCAL/SERVER/FASTRETURN｝本地保存还是送服务器或立即返回
	//相当于TO指令
	//1，LOCAL；2，SERVER；3，FASTRETURN
	SMM_UINT8 Position;
	//运行模式，分为DO和WHEN
	//1，DO；2，WHEN
	SMM_UINT8 RunMode;
	//调用的频次
	SMM_DOUBLE Cycle;
	//调用的总次数
	SMM_UINT32 Count;
	//以下时间格式为"2003-04-06 20:33:35"
	//发送时间
	SMM_CHAR SendTime[20];
	//开始时间
	SMM_CHAR StartTime[20];
	//结束时间
	SMM_CHAR EndTime[20];
};

//模块调用后，返回数据
//供Driver模块使用 
struct LIDP_tagDriverReturnBlock
{
	SMM_INT32 TASKID;
	//用于确定信息项
	SMM_INT32 InfoBaseProviderID; 
	SMM_INT32 InfoBaseID;
	//信息项ID串，串中的每一项都为4个字节，是一个整型值
	SMM_INT32 NumOfInfoItemID;
	SMM_INT32* InfoItemID;
	SMM_INT32 ActionID;
	//供指令使用的参数表
	LIDP_tagVariantParameterList ParameterList;
	//以下时间格式为"2003-04-06 20:33:35"
	//返回时间
	SMM_CHAR ReturnTime[20];
};


//供Management使用
struct LIDP_tagManagementCommand
{
};


//指令格式
//供Instruction模块使用
struct LIDP_tagInstruction
{
	SMM_INT32 InstructionID;
	//参数大小，不是共用体的大小，而是其所指向的所有数据的大小 
	SMM_INT32 szParameter;
	//指令参数
	//供Instruction模块使用
	union
	{
		LIDP_tagDriverCommand driverCommand;
		LIDP_tagManagementCommand managementCommand;
	};
};



//传输用结构
//数据块，在空间的分布上必须接续在此结构体之后
//传输时，只要将此结构体实体的首址之后sizeof(LIDP_tagTransfer) + Size的数据全部发送出去即可
//LIDP_tagTransfer的实体由LIDP_UniteOffset_tagInstruction生成
struct LIDP_tagTransfer
{
	//所传输的数据类型
	SMM_INT32 TransferType;
	//数据的大小
	SMM_INT32 Size;
};







//以下为XML文件在内存中映射的结构体，只是结点中的结构，不含结点间的关系
//这些结构体只用于LIDP内部，所以其中从XML文件中的结点获得的信息的类型尽量采用XML4C中的
 

/////////////////////////////////////////////////////////////////////////////////////
//以下的结构在内存中的分布要基于Array Template，用类，以方便实现
//语言项
/////////////////////////////////////////////////////////////////////////////////////


/*//用于存储字符串
struct LIDP_tagString
{
	//字符串长度
	SMM_INT32 Length;
	//字符串
	XMLCh* Buffer;
};
*/

//处理XML时用，对字符串处理的封装
class LIDP_String
{
public:
	XMLCh* str;
	SMM_INT32 length;

public:
	LIDP_String()
	{
		length = 0;
		str = LIDP_NULL;
	}

	~LIDP_String()
	{
		XMLString::release(&str);
	}

	LIDP_String& operator=(XMLCh* string)
	{
		XMLString::release(&str);
		length = XMLString::stringLen(string);
		str = (XMLCh*)malloc(sizeof(XMLCh) * length);
		XMLString::copyString(str, string);
		return *this;
	}
};


//对映XML文件中的Description部分
struct LIDP_tagDescription
{
	LIDP_String Language;
	LIDP_String Description;
};


//对映XML文件中的DataType部分
struct LIDP_tagDataType
{
	SMM_INT32 ID;
	LIDP_String Name;
};


//对映XML文件中定义Action的部分
struct LIDP_tagActionDefine
{
	SMM_INT32 ID;
	LIDP_String Name;
	LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*> Descriptions;
};


//对映XML文件中的Parameter部分
struct LIDP_tagParameterInInfoBase
{
	SMM_INT32 ID;
	SMM_INT32 DataTypeID;
	LIDP_String Name;
};


//对映XML文件中的Action部分
struct LIDP_tagAction
{
	SMM_INT32 ID;
	LIDP_CArrayTemplate<LIDP_tagParameterInInfoBase, LIDP_tagParameterInInfoBase*> Parameters;
};


//对映XML文件中的InfoItem部分
struct LIDP_tagInfoItem
{
	SMM_INT32 ID;
	LIDP_String Name;
	SMM_INT32 DataType;
	LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*> Descriptions;
	LIDP_CArrayTemplate<LIDP_tagAction, LIDP_tagAction*> Actions;
	LIDP_CArrayTemplate<LIDP_tagInfoItem, LIDP_tagInfoItem*> SubTree;
};


//对映XML文件中的InfoBase的开始部分
struct LIDP_tagInfoBase
{
	SMM_INT32 ProviderID;
	SMM_INT32 InfoBaseID;
	LIDP_String Name;
	LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*> Descriptions;
	LIDP_CArrayTemplate<LIDP_tagDataType, LIDP_tagDataType*> InfoBaseDataTypes;
	LIDP_CArrayTemplate<LIDP_tagActionDefine, LIDP_tagActionDefine*> InfoBaseActions;
	LIDP_CArrayTemplate<LIDP_tagInfoItem, LIDP_tagInfoItem*> InfoItems;
};


//对映XML文件中的Parameter部分，在模块描述文件中的InfoItem中的
struct LIDP_tagParameterInModule
{
	SMM_INT32 ID;
	SMM_INT32 DataTypeID;
};


//对映XML文件中的InfoItem部分，在模块描述文件中的
struct LIDP_tagInfoItemInModule
{
	LIDP_String ID;
	SMM_INT32 AcitonID;
	LIDP_String FunctionName;
	LIDP_CArrayTemplate<LIDP_tagParameterInModule, LIDP_tagParameterInModule*> Parameters;
};


//对映XML文件中的Module的开始部分
struct LIDP_tagModule
{
	SMM_INT32 ProviderID;
	SMM_INT32 InfoBaseID;
	LIDP_String FileName;
	LIDP_String Name;
	LIDP_CArrayTemplate<LIDP_tagInfoItemInModule, LIDP_tagInfoItemInModule*> InfoItemList;
};















/////////////////////////////////////////////////////////////////////////////////
//用于内部使用的结构体
//用于Driver Scheduler Command List数组的结构体
struct LIDP_tagDriverSchedulerCommand
{
	//从Instruction模块送来的
	LIDP_tagDriverCommand driverCommand;
	//此条指令在Driver Excuter中对映的已导入的动态库的ID，尚未导入时为LIDP_NULL
	SMM_INT32 LibraryID;
	//对映的函数句柄的ID
	SMM_INT32 FunctionID;
};



struct DriverFunction
{
	SMM_INT32 FunctionID;
	//平台相关
	HANDLE hfunction;
};

//用于Driver Executer内部使用的结构体，用于保存LibraryID和FunctionID与系统相关的内存句柄的对映关系
//与平台相关
struct DriverLibrary
{
	SMM_INT32 LibraryID;
	//平台相关
	HANDLE hlibrary;
	//DriverFunction的数组
	LIDP_CArrayTemplate<DriverFunction, DriverFunction*> functionList;
};

struct DriverHandleInfoList
{
	//DriverLibrary的数组
	LIDP_CArrayTemplate<DriverLibrary, DriverLibrary*> libraryList;
};


#endif //#define LIDP_TypeDefinition_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_
