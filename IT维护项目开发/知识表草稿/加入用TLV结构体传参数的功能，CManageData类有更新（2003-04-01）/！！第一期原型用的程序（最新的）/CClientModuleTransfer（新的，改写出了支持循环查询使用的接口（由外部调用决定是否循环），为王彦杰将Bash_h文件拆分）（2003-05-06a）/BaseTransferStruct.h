///////////////////////////////////////////////////////////////////////////////
//�ļ����ݣ��Զ�������ͷ�ļ������ڶ��������ϴ������ݺ�ָ������ݽṹ����Base.h����
//���ߣ�	���
//��д���ڣ�2003-05-06
//��Ҫ�ļ���
///////////////////////////////////////////////////////////////////////////////



#if !defined(AFX_BASETRANSFERSTRUCT_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
#define AFX_BASETRANSFERSTRUCT_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_

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


#endif // !defined(AFX_BASETRANSFERSTRUCT_H__799C1D7C_5037_40F5_A525_EBDAAAEEEBCC__INCLUDED_)
