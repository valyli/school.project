#if !defined(LIDP_TypeDefinition_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_)
#define LIDP_TypeDefinition_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_

#include "smm.h"
#include "ForXecro.h"
#include "LIDP_CArrayTemplate.h"

//LIDP����ֵ
#define LIDP_OK		1
#define LIDP_ERR	0
#define LIDP_NULL	0
//ָ��ID
#define COMMAND_DRIVER		1
#define COMMAND_MANAGEMENT	2

//��������
#define TRANSFER_INSTRUCTION		1		//���Է���˵�ָ��
#define TRANSFER_DRIVERREUTRNBLOCK	2		//�ͻ��˵ķ�������
#define TRANSFER_REQUEST			3		//���Կͻ��˵�����




////////////////////////////////////////////////////////////////////////////////////
//�˲�����Ҫ���ڴ������ݣ�����ʹ�ýṹ�壬����ʹ���࣬��Ϊ����������������С
//
//�涨��
//	�������Ľṹ��ʵ�����ڴ�ռ�ķֲ��ϣ������ǽ����ڰ������Ľṹ���ʵ��֮�󡣣�LIDP�ڲ�ʹ�õĿ��Բ��ã�
//	��˲ſ���ʹ�ṹ���ڽ�����LIDP�ⲿ���д���ʱ�Ĳ�����ü�
////////////////////////////////////////////////////////////////////////////////////

//�������Ͷ���
enum LIDP_enumVariantType
{
	LIDP_NoDefined = 0,			//Not defined, error type, 0
	LIDP_string = 1,			//String
	LIDP_Integer = 2,			//Integer
	LIDP_Binary = 3,			//Binary���ֽڣ� 
	LIDP_Real = 4				//Real
};

//��¼LIDP_VariantType�ж�����������͸���������0 
#define LIDP_Number_Of_VariantType 4


//�����洢�ṹ 
struct LIDP_tagVariant
{
	//�����жϱ�������
	LIDP_enumVariantType Type;
	//�������ݵĳ��ȣ����ֽڼ��㡣��ΪSMM_CHAR*��SMM_UCHAR*ʱ����ֵ��Ч���������ȫΪ0
	SMM_INT32 Length;
	//��Ҫ���ڶ��⴫�����ݣ�����ѡ��SMM�е�����
	SMM_UCHAR* Buff;
};

//���������ڶ��⴫�ݲ�����֧�ֶ������������
//ֻ�Ի����������ͣ�LIDP_VariantType��Ч
struct LIDP_tagVariantParameterList
{
	//�����ĸ���
	SMM_INT32 NumOfList;
	//����ָ�����飬����ָ�����
	LIDP_tagVariant** List;
};

//ģ���������
//��Driverģ��ʹ��
struct LIDP_tagDriverCommand
{
	SMM_INT32 TASKID;
	//����ȷ����Ϣ��
	SMM_INT32 InfoBaseProviderID; 
	SMM_INT32 InfoBaseID;
	//��Ϣ��ID�������е�ÿһ�Ϊ4���ֽڣ���һ������ֵ
	SMM_INT32 NumOfInfoItemID;
	SMM_INT32* InfoItemID;
	SMM_INT32 ActionID;
	//��ָ��ʹ�õĲ����� 
	LIDP_tagVariantParameterList ParameterList;
	//��LOCAL/SERVER/FASTRETURN�����ر��滹���ͷ���������������
	//�൱��TOָ��
	//1��LOCAL��2��SERVER��3��FASTRETURN
	SMM_UINT8 Position;
	//����ģʽ����ΪDO��WHEN
	//1��DO��2��WHEN
	SMM_UINT8 RunMode;
	//���õ�Ƶ��
	SMM_DOUBLE Cycle;
	//���õ��ܴ���
	SMM_UINT32 Count;
	//����ʱ���ʽΪ"2003-04-06 20:33:35"
	//����ʱ��
	SMM_CHAR SendTime[20];
	//��ʼʱ��
	SMM_CHAR StartTime[20];
	//����ʱ��
	SMM_CHAR EndTime[20];
};

//ģ����ú󣬷�������
//��Driverģ��ʹ�� 
struct LIDP_tagDriverReturnBlock
{
	SMM_INT32 TASKID;
	//����ȷ����Ϣ��
	SMM_INT32 InfoBaseProviderID; 
	SMM_INT32 InfoBaseID;
	//��Ϣ��ID�������е�ÿһ�Ϊ4���ֽڣ���һ������ֵ
	SMM_INT32 NumOfInfoItemID;
	SMM_INT32* InfoItemID;
	SMM_INT32 ActionID;
	//��ָ��ʹ�õĲ�����
	LIDP_tagVariantParameterList ParameterList;
	//����ʱ���ʽΪ"2003-04-06 20:33:35"
	//����ʱ��
	SMM_CHAR ReturnTime[20];
};


//��Managementʹ��
struct LIDP_tagManagementCommand
{
};


//ָ���ʽ
//��Instructionģ��ʹ��
struct LIDP_tagInstruction
{
	SMM_INT32 InstructionID;
	//������С�����ǹ�����Ĵ�С����������ָ����������ݵĴ�С 
	SMM_INT32 szParameter;
	//ָ�����
	//��Instructionģ��ʹ��
	union
	{
		LIDP_tagDriverCommand driverCommand;
		LIDP_tagManagementCommand managementCommand;
	};
};



//�����ýṹ
//���ݿ飬�ڿռ�ķֲ��ϱ�������ڴ˽ṹ��֮��
//����ʱ��ֻҪ���˽ṹ��ʵ�����ַ֮��sizeof(LIDP_tagTransfer) + Size������ȫ�����ͳ�ȥ����
//LIDP_tagTransfer��ʵ����LIDP_UniteOffset_tagInstruction����
struct LIDP_tagTransfer
{
	//���������������
	SMM_INT32 TransferType;
	//���ݵĴ�С
	SMM_INT32 Size;
};







//����ΪXML�ļ����ڴ���ӳ��Ľṹ�壬ֻ�ǽ���еĽṹ����������Ĺ�ϵ
//��Щ�ṹ��ֻ����LIDP�ڲ����������д�XML�ļ��еĽ���õ���Ϣ�����;�������XML4C�е�
 

/////////////////////////////////////////////////////////////////////////////////////
//���µĽṹ���ڴ��еķֲ�Ҫ����Array Template�����࣬�Է���ʵ��
//������
/////////////////////////////////////////////////////////////////////////////////////


/*//���ڴ洢�ַ���
struct LIDP_tagString
{
	//�ַ�������
	SMM_INT32 Length;
	//�ַ���
	XMLCh* Buffer;
};
*/

//����XMLʱ�ã����ַ�������ķ�װ
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


//��ӳXML�ļ��е�Description����
struct LIDP_tagDescription
{
	LIDP_String Language;
	LIDP_String Description;
};


//��ӳXML�ļ��е�DataType����
struct LIDP_tagDataType
{
	SMM_INT32 ID;
	LIDP_String Name;
};


//��ӳXML�ļ��ж���Action�Ĳ���
struct LIDP_tagActionDefine
{
	SMM_INT32 ID;
	LIDP_String Name;
	LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*> Descriptions;
};


//��ӳXML�ļ��е�Parameter����
struct LIDP_tagParameterInInfoBase
{
	SMM_INT32 ID;
	SMM_INT32 DataTypeID;
	LIDP_String Name;
};


//��ӳXML�ļ��е�Action����
struct LIDP_tagAction
{
	SMM_INT32 ID;
	LIDP_CArrayTemplate<LIDP_tagParameterInInfoBase, LIDP_tagParameterInInfoBase*> Parameters;
};


//��ӳXML�ļ��е�InfoItem����
struct LIDP_tagInfoItem
{
	SMM_INT32 ID;
	LIDP_String Name;
	SMM_INT32 DataType;
	LIDP_CArrayTemplate<LIDP_tagDescription, LIDP_tagDescription*> Descriptions;
	LIDP_CArrayTemplate<LIDP_tagAction, LIDP_tagAction*> Actions;
	LIDP_CArrayTemplate<LIDP_tagInfoItem, LIDP_tagInfoItem*> SubTree;
};


//��ӳXML�ļ��е�InfoBase�Ŀ�ʼ����
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


//��ӳXML�ļ��е�Parameter���֣���ģ�������ļ��е�InfoItem�е�
struct LIDP_tagParameterInModule
{
	SMM_INT32 ID;
	SMM_INT32 DataTypeID;
};


//��ӳXML�ļ��е�InfoItem���֣���ģ�������ļ��е�
struct LIDP_tagInfoItemInModule
{
	LIDP_String ID;
	SMM_INT32 AcitonID;
	LIDP_String FunctionName;
	LIDP_CArrayTemplate<LIDP_tagParameterInModule, LIDP_tagParameterInModule*> Parameters;
};


//��ӳXML�ļ��е�Module�Ŀ�ʼ����
struct LIDP_tagModule
{
	SMM_INT32 ProviderID;
	SMM_INT32 InfoBaseID;
	LIDP_String FileName;
	LIDP_String Name;
	LIDP_CArrayTemplate<LIDP_tagInfoItemInModule, LIDP_tagInfoItemInModule*> InfoItemList;
};















/////////////////////////////////////////////////////////////////////////////////
//�����ڲ�ʹ�õĽṹ��
//����Driver Scheduler Command List����Ľṹ��
struct LIDP_tagDriverSchedulerCommand
{
	//��Instructionģ��������
	LIDP_tagDriverCommand driverCommand;
	//����ָ����Driver Excuter�ж�ӳ���ѵ���Ķ�̬���ID����δ����ʱΪLIDP_NULL
	SMM_INT32 LibraryID;
	//��ӳ�ĺ��������ID
	SMM_INT32 FunctionID;
};



struct DriverFunction
{
	SMM_INT32 FunctionID;
	//ƽ̨���
	HANDLE hfunction;
};

//����Driver Executer�ڲ�ʹ�õĽṹ�壬���ڱ���LibraryID��FunctionID��ϵͳ��ص��ڴ����Ķ�ӳ��ϵ
//��ƽ̨���
struct DriverLibrary
{
	SMM_INT32 LibraryID;
	//ƽ̨���
	HANDLE hlibrary;
	//DriverFunction������
	LIDP_CArrayTemplate<DriverFunction, DriverFunction*> functionList;
};

struct DriverHandleInfoList
{
	//DriverLibrary������
	LIDP_CArrayTemplate<DriverLibrary, DriverLibrary*> libraryList;
};


#endif //#define LIDP_TypeDefinition_H__3D20331A_9EAD_4E3E_B3E2_BB4D26AA6C06__INCLUDED_
