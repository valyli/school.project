///////////////////////////////////////////////////////////////////////////////
//文件内容：自定义类型头文件，用于定义在网上传输数据和指令的数据结构，被Base.h引用
//作者：	李佳
//编写日期：2003-05-06
//需要文件：
///////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_BASETRANSFERSTRUCT_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
#define AFX_BASETRANSFERSTRUCT_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_

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


#endif // !defined(AFX_BASETRANSFERSTRUCT_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
