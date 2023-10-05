// ManageParameter.h: interface for the CManageData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MANAGEPARAMETER_H__EEB44E79_0773_4F07_9F9A_615435BBD8C3__INCLUDED_)
#define AFX_MANAGEPARAMETER_H__EEB44E79_0773_4F07_9F9A_615435BBD8C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

////////////////////////////////////////////////////////////////////////////


#include "Base.h"


////////////////////////////////////////////////////////////////////////////

//处理各种类型参数（或者返回值）数据的类，利用重载机制
//和Base.h文件中的DataType_TransferModule定义相匹配
//一个实例只保留一个参数
class CManageData  
{
public:
	//保存当前数据
	DataType_TransferModule CurrentDataType;

protected:
	//以下变量用于保存数据
	int Data_int_Value;							//int
	long Data_long_Value;						//long
	unsigned long Data_unsigned_long_Value;		//unsigned long
	char Data_char_Value;						//char
	CString Data_CString_Value;					//CString
//	BOOL Data_BOOL_Value;						//BOOL
	char* Data_char_Ptr;						//char*

public:
	//SetData方法
	void SetData(int Data);//同	void SetData(BOOL Data);
	void SetData(long Data);
	void SetData(unsigned long Data);
	void SetData(char Data);
	void SetData(CString Data);
	void SetData(char* Data);

	//GetData方法
	void GetData(int& Data);//同	BOOL GetData();
	void GetData(long& Data);
	void GetData(unsigned long& Data);
	void GetData(char& Data);
	void GetData(CString& Data);
	void GetData(char* Data);

	CManageData();
	virtual ~CManageData();

};

#endif // !defined(AFX_MANAGEPARAMETER_H__EEB44E79_0773_4F07_9F9A_615435BBD8C3__INCLUDED_)
