///////////////////////////////////////////////////////////////////////////////
//�ļ����ݣ��Զ�������ͷ�ļ������������е��ļ�����
//���ߣ�	���
//��д���ڣ�2003-03-20
//��Ҫ�ļ���
//�漰���ã�MSXML��afxtempl.h
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
//ĩβ��Value��ʾΪֵ����Ptr��ʾΪָ��
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

//��¼DataType_TransferModule�ж�����������͸���
#define Number_Of_DataType_TransferModule 7
///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

//������Ϣ����б������ļ���
#define INFORMATION_ELEMENT_LIST_TABLE_FILENAME "InfomationElementListTable.xml"


//����װ��InfomationElementListTable��Ϣ
struct InfomationElementListTableStruct
{
	//����Ϣ����б��е�ID����1��
	unsigned int InfomationElementTableID;
	//��Ϣ�������
	CString InfomationElementTableName_Chinese;
	//��Ϣ���Ӣ������
	CString InfomationElementTableName_English;
	//����
	CString Description;
	//�ȼ���Ϣ��ID(0��ʾû��)
	unsigned int EqualInfomationElementTableID;
};


typedef CArray<InfomationElementListTableStruct, InfomationElementListTableStruct&> CArrayInfomationElementListTableStruct;

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//����װ��InfoList()������Ϣ
struct ModuleInfomationListStruct
{
	//����ID
	unsigned int OperationID;
	//��Ϣ���ID
	unsigned int InfomationElementTableID;
	//��Ϣ��ID
	unsigned int InfomationElementID;
	//��������
	unsigned int OperationType;
	//����ģ���ļ���
	CString ServiceFileName;
	//֧�ֵĲ���ϵͳ���ͣ�ʮ�����ƣ�
	unsigned long SupportSystemType;
	//ģ������
	unsigned int ModuleType;
	//�ӿں���
	CString InterfaceFunction;
	//��������
	unsigned int ParameterType;
	//������¼����ֵ���
	unsigned int IsStorageReturnValueInParameter;
	//����ֵ����Ϊ�գ�
	CString ParameterValue;
};


typedef CArray<ModuleInfomationListStruct, ModuleInfomationListStruct&> CArrayModuleInfomationListStruct;

//���ڷ���������̬���ȫ����Ϣ
struct ModuleInfomationStruct
{
	//�������ģ��֧�ֵ�ģ�鶨��
	unsigned int InfoModuleTypeProviderId;
	//�������ո�InfoModuleTypeProvider��ģ�����Ͷ��壬��ģ�������ĸ�ģ�����͡�
	unsigned int InfoModuleTypeId;
	//ģ���������
	unsigned int InfoModuleProviderId;
	//��ģ��֧�ֵ����ĸ���Ϣ���
	unsigned int InfoServiceProviderId;
	unsigned int NameBaseId;
	//���ڷ��ض�̬���в����ľ�����Ϣ
	CArrayModuleInfomationListStruct ListArray;
};

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

//����������Ϣ
inline bool AlarmErrorMessage(CString ErrorMessage, CString ErrorMode)
{
	::MessageBox(0, ErrorMessage, ErrorMode, MB_OK|MB_ICONEXCLAMATION);
	return false;
}

///////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////

//����װ��InfomationTable��Ϣ
struct InfomationElementStruct
{
	//����Ϣ����е�ID����1��
	unsigned int InfomationElementID;
	//��Ϣ
	CString Infomation;
	//Ӣ������
	CString EnglishName;
	//��Ϣ���Ͳμ��������ͣ���1��
	unsigned int InfomationType;
	//����
	CString Description;
};


typedef CArray<InfomationElementStruct, InfomationElementStruct&> CArrayInfomationElementStruct;
///////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////
//����Ϊ���������ϴ������ݺ�ָ������ݽṹ����


//�洢����ֵ�Ĺ�����
union DataValueUnion
{
	char Value_char[256];
	long Value_long;
	int Value_int;
};


//TLV��Type��Length��Value����ʽ�����е�Type��ʾValue��ʲô��
//Length��ʾValue�ĳ��ȣ�Value����ʵ�ʵ����ݡ�
//����Type����ΪCPU��ʵ�ʲɼ�����Ϣ�����ͣ�LengthΪ8;ValueΪPentium4��
struct TLVStruct
{
    int Type;
    long Length;
	DataValueUnion Value;
};


//�������������INFOBASEID��ʾ
struct InfoBaseID_Struct
{
	//��Ϣ���ID
	unsigned int InfomationElementTableID;
	//��Ϣ��ID
	unsigned int InfomationElementID;
};


//�ӷ������ͻ��˷��͵�ָ�������
struct Transfer_S2C_Struct
{
	//����ID
	//0��Get
	//1��Set
	//-1��Stop
	int CommandID;
	//�������������INFOBASEID��ʾ
	InfoBaseID_Struct InfoBaseID;
	//����������ֵ
	TLVStruct Value;
	//��LOCAL��SERVER�����ر��滹���ͷ�����
	//0��LOCAL��1��SERVER
	int Position;
	//���õ�Ƶ��
	double Cycle;
	//���õ��ܴ���
	int Count;
	//����ʱ���ʽΪ"2003-04-06 20:33:35"
	//����ʱ��
	char SendTime[20];
	//��ʼʱ��
	char StartTime[20];
	//����ʱ��
	char EndTime[20];
};


//�ӿͻ��������˷��ص�����
struct Transfer_C2S_Struct
{
	//�������������INFOBASEID��ʾ
	InfoBaseID_Struct InfoBaseID;
	//����������ֵ
	TLVStruct Value;
	//����ʱ���ʽΪ"2003-04-06 20:33:35"
	//���ز���ʱ��
	char LocalTime[20];
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//��������ܵĽṹ��
struct tagSMM_c2s
{
    //unsigned char cIp[19];  //ip��ַ
	char cIp[19];  //ip��ַ
    int  uiPort;     //�˿�
    Transfer_C2S_Struct m_Data_Transfer_C2S_Struct;
};


struct tagSMM_s2c
{
    //unsigned char cIp[19] ;  //ip��ַ
	char cIp[19] ;  //ip��ַ
    int  uiPort;     //�˿�
    Transfer_S2C_Struct m_Data_Transfer_S2C_Struct;
};
///////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_BASE_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
