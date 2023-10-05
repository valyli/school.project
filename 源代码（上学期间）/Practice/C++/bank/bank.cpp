// bank.cpp : Defines the entry point for the console application.
//
//��־ע�ͣ�
//A���й˿͵���
//A+\-���˿ͽ���\�뿪����A
//B+\-���˿ͽ���\�뿪����B
//D���˿����ڶ�����������ȥ
//NON������Ա����
//AC���˿��ɶ���Aת��B
//BC���˿��ɶ���Bת��A

#include "stdafx.h"
#include "stdlib.h"
#include "conio.h"
//����TC�б������У��������¸Ķ���
//enum bool{false, true};
//������vc6.0�е�win32����̨�±�������

#define QueueMax 4//���г���
#define MaxTime 1000.0//�ܹ�ʱ���ֵ

double TotalTime = MaxTime;//�ܹ�ʱ��
double CurTime;//��ǰʱ��
bool QueueIsEmpty = false;//����Ϊ��ʱ���жϱ�־

long DepartureCustomer = 0;//���������ȥ�Ĺ˿���
long ChangeCustomer = 0;//���Ŷ���ת�����еĹ˿���
double NotServeForCustomer = 0.0;//����Ա��������
long NumOfCustomer = 0;//ϵͳ�еĹ˿�����

//�˿���Ϣ�ṹ��
struct Customer
{
	double EnterTime;//�˿�����ʱ��
	double ServeTime;//��ҪΪ�˿ͷ���ʱ��
	double LeaveTime;//�˿��뿪ʱ��
};

//������������
class Queue
{
private:
	int NumOfQueue;//�����й˿͵ĸ���
	Customer OldCustomer[QueueMax];//�ڶ����еĹ˿���Ϣ
public:
	Queue(void)
	{
		NumOfQueue = 0;
	}
	int GetNumOfQueue(void)
	{
		return NumOfQueue;
	}
	bool GetHead(Customer &Head)//��ö��е�ͷ��ɾ��
	{
		if(NumOfQueue <=0)
			return false;
		Head = OldCustomer[0];
		for(int i = 0; i < QueueMax - 1; i++)
			OldCustomer[i] = OldCustomer[i + 1];
		NumOfQueue--;
		return true;
	}
	bool ShowHead(Customer &Head)//��ö��е�ͷ
	{
		if(NumOfQueue <=0)
			return false;
		Head = OldCustomer[0];
		return true;
	}
	bool AddElem(Customer Elem)//�����β��ӹ˿���Ϣ
	{
		if(NumOfQueue >= QueueMax)
			return false;
		OldCustomer[NumOfQueue++] = Elem;
		return true;
	}
	bool IsFull(void)//�ж϶����Ƿ�Ϊ��
	{
		if(NumOfQueue >= QueueMax)
			return true;
		return false;
	}
	bool IsEmpty(void)//�ж϶����Ƿ�Ϊ��
	{
		if(NumOfQueue <= 0)
			return true;
		return false;
	}
	bool GetTail(Customer &Elem)//��ö���β��ɾ��
	{
		if(NumOfQueue <= 0)
			return false;
		Elem = OldCustomer[NumOfQueue - 1];
		NumOfQueue--;
		return true;
	}
	bool ShowTail(Customer &Elem)//��ö���β
	{
		if(NumOfQueue <= 0)
			return false;
		Elem = OldCustomer[NumOfQueue - 1];
		return true;
	}
}A,B;//����A��B��������

//��ø��˿͵ķ���ʱ��
double ServeTime(void)
{
	return 800.0 * rand() / 32767.0;/*��Ҫ�Ķ�*///rand����int�ͣ�0~32767
}

//��ù˿͵����ʱ��
double EnterTime(void)
{
	return 10.0 * rand() / 32767.0;/*��Ҫ�Ķ�*/
}

//�й˿͵���
bool CustomerArrived(void)
{
	printf("A ");
	NumOfCustomer++;
	if(A.IsFull() == true && B.IsFull() == true)//�����������˿���ȥ
	{
		CurTime += EnterTime();
		DepartureCustomer++;
		printf("D ");
		return false;
	}
	Customer temp;
	double tempTime = EnterTime();
	if(QueueIsEmpty == true)
	{
		NotServeForCustomer += tempTime;
		QueueIsEmpty = false;
	}
	temp.ServeTime = ServeTime();
	if(A.GetNumOfQueue() <= B.GetNumOfQueue())//A,B����������ͬʱ����ѡ��A����
	{
		A.ShowTail(temp);
		temp.EnterTime += tempTime;
		temp.LeaveTime = temp.EnterTime + temp.ServeTime;
		A.AddElem(temp);
		CurTime += tempTime;
		printf("A+ ");
	}
	else//�˿ͽ������B
	{
		B.ShowTail(temp);
		temp.EnterTime += tempTime;
		temp.LeaveTime = temp.EnterTime + temp.ServeTime;
		B.AddElem(temp);
		CurTime += tempTime;
		printf("B+ ");
	}
	return true;
}

//��÷���Ĺ˿���ȥ
bool CustomerDeparture(void)
{
	Customer temp;
	while(A.ShowHead(temp) == true)
	{
		if(temp.LeaveTime <= CurTime)
		{
			A.GetHead(temp);
			printf("A- ");
		}
		else
			break;
	}
	while(B.ShowHead(temp) == true)
	{
		if(temp.LeaveTime <= CurTime)
		{
			B.GetHead(temp);
			printf("B- ");
		}
		else
			break;
	}
	if(A.IsEmpty() == true && B.IsEmpty() == true)//������գ�����Ա�ȴ�
	{
		QueueIsEmpty = true;//���ö��пձ�־
		printf("NON ");
		return false;
	}
	return true;//���в�Ϊ�գ�����Աæ
}

//�˿ͱ任����
bool CustomerChange(void)
{
	Customer temp1, temp2;
	//A���г���B����+1ʱ
	while(A.GetNumOfQueue() > B.GetNumOfQueue() + 1 && B.GetNumOfQueue() < QueueMax)
	{
		A.GetTail(temp1);
		B.GetTail(temp2);
		temp1.EnterTime = temp2.LeaveTime;
		temp1.LeaveTime = temp1.EnterTime + temp1.ServeTime;
		B.AddElem(temp1);
		ChangeCustomer++;
		printf("AC ");
	}
	//B���г���A����+1ʱ
	while(A.GetNumOfQueue() + 1 < B.GetNumOfQueue() && A.GetNumOfQueue() < QueueMax)
	{
		B.GetTail(temp1);
		A.GetTail(temp2);
		temp1.EnterTime = temp2.LeaveTime;
		temp1.LeaveTime = temp1.EnterTime + temp1.ServeTime;
		A.AddElem(temp1);
		ChangeCustomer++;
		printf("BC ");
	}
	return true;
}

//��ʼ��������A��B
bool OpenForDay(void)
{
	CurTime = 0.0;
	Customer temp1, temp2;
	//��ʼ��A����
	temp1.EnterTime = 0.1;
	temp1.ServeTime = ServeTime();
	temp1.LeaveTime = temp1.EnterTime + temp1.ServeTime;
	A.AddElem(temp1);
	CurTime = 0.1;
	temp1.EnterTime = CurTime + EnterTime();
	temp1.ServeTime = ServeTime();
	temp1.LeaveTime = temp1.EnterTime + temp1.ServeTime;
	A.AddElem(temp1);
	CurTime = 0.0;
	//��ʼ��B����
	temp2.EnterTime = 0.1;
	temp2.ServeTime = ServeTime();
	temp2.LeaveTime = temp2.EnterTime + temp2.ServeTime;
	B.AddElem(temp2);
	CurTime = 0.1;
	temp2.EnterTime = CurTime + EnterTime();
	temp2.ServeTime = ServeTime();
	temp2.LeaveTime = temp2.EnterTime + temp2.ServeTime;
	B.AddElem(temp2);
	//ȷ����ǰʱ��CurTime
	if(temp1.EnterTime < temp2.EnterTime)
		CurTime = temp2.EnterTime;
	else
		CurTime = temp1.EnterTime;
	return true;
}

int main(int argc, char* argv[])
{
	OpenForDay();
	while(CurTime < TotalTime)
	{
		CustomerChange();
		CustomerDeparture();
		CustomerArrived();
	}
	printf("\nϵͳ�е�ƽ���˿�����%f", NumOfCustomer/TotalTime);
	printf("\n����Ա�������ʣ�%f", (TotalTime - NotServeForCustomer)/TotalTime);
	printf("\n��˿���������ȥ�Ĺ˿�����%ld", DepartureCustomer);
	printf("\n���Ŷ���ת�����еĹ˿�����%ld", ChangeCustomer);
	getch();
	return 0;
}

