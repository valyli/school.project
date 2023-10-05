// ManageParameter.cpp: implementation of the CManageData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ManageData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CManageData::CManageData()
{
	CurrentDataType = NoDefined;
}

CManageData::~CManageData()
{

}


//SetData����
void CManageData::SetData(int Data)
{
	CurrentDataType = int_Value;
	Data_int_Value = Data;
}

void CManageData::SetData(long Data)
{
	CurrentDataType = long_Value;
	Data_long_Value = Data;
}

void CManageData::SetData(unsigned long Data)
{
	CurrentDataType = unsigned_long_Value;
	Data_unsigned_long_Value = Data;
}

void CManageData::SetData(char Data)
{
	CurrentDataType = char_Value;
	Data_char_Value = Data;
}

void CManageData::SetData(CString Data)
{
	CurrentDataType = CString_Value;
	Data_CString_Value = Data;
}
/*
void CManageData::SetData(BOOL Data)
{
	CurrentDataType = BOOL_Value;
	Data_BOOL_Value = Data;
}
*/
void CManageData::SetData(char* Data)
{
	CurrentDataType = char_Ptr;
	Data_char_Ptr = Data;
}


//GetData����
void CManageData::GetData(int& Data)
{
	Data = Data_int_Value;
}

void CManageData::GetData(long& Data)
{
	Data = Data_long_Value;
}

void CManageData::GetData(unsigned long& Data)
{
	Data = Data_unsigned_long_Value;
}

void CManageData::GetData(char& Data)
{
	Data = Data_char_Value;
}

void CManageData::GetData(CString& Data)
{
	Data = Data_CString_Value;
}
/*
void CManageData::GetData(BOOL& Data)
{
	Data = Data_BOOL_Value;
}
*/
void CManageData::GetData(char* Data)
{
	Data = Data_char_Ptr;
}

//��TLVStruct�ṹ�巵������
void CManageData::GetDatabyTLV(TLVStruct& TLVData)
{
	TLVData.Type = CurrentDataType;
	//���ݲ�ͬ����������������ռ���Ⱥ�ֵ
	switch(CurrentDataType)
	{
	case CString_Value:
		TLVData.Length = 255;
		strcpy(TLVData.Value.Value_char, Data_CString_Value.GetBuffer(Data_CString_Value.GetLength()));
		break;
	case long_Value:
		TLVData.Length = sizeof(long);
		TLVData.Value.Value_long = Data_long_Value;
		break;
	case int_Value:
		TLVData.Length = sizeof(int);
		TLVData.Value.Value_int = Data_int_Value;
		break;
	}
}


//��TLVStruct�ṹ����������
void CManageData::SetDatabyTLV(TLVStruct TLVData)
{
	CurrentDataType = (enum tagDataType_TransferModule)TLVData.Type;
	//���ݲ�ͬ��������������
	switch(CurrentDataType)
	{
	case CString_Value:
		Data_CString_Value = TLVData.Value.Value_char;
		break;
	case long_Value:
		Data_long_Value = TLVData.Value.Value_long;
		break;
	case int_Value:
		Data_int_Value = TLVData.Value.Value_int;
		break;
	}
}
