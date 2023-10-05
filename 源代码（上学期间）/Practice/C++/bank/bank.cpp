// bank.cpp : Defines the entry point for the console application.
//
//标志注释：
//A：有顾客到来
//A+\-：顾客进入\离开队列A
//B+\-：顾客进入\离开队列B
//D：顾客由于队列已满而离去
//NON：服务员空闲
//AC：顾客由队列A转向B
//BC：顾客由队列B转向A

#include "stdafx.h"
#include "stdlib.h"
#include "conio.h"
//若在TC中编译运行，需作如下改动：
//enum bool{false, true};
//建议在vc6.0中的win32控制台下编译运行

#define QueueMax 4//队列长度
#define MaxTime 1000.0//总共时间的值

double TotalTime = MaxTime;//总共时间
double CurTime;//当前时间
bool QueueIsEmpty = false;//队列为空时的判断标志

long DepartureCustomer = 0;//因队满而离去的顾客数
long ChangeCustomer = 0;//在排队中转换队列的顾客数
double NotServeForCustomer = 0.0;//出纳员的利用率
long NumOfCustomer = 0;//系统中的顾客总数

//顾客信息结构体
struct Customer
{
	double EnterTime;//顾客来到时刻
	double ServeTime;//将要为顾客服务时间
	double LeaveTime;//顾客离开时刻
};

//定义服务队列类
class Queue
{
private:
	int NumOfQueue;//队列中顾客的个数
	Customer OldCustomer[QueueMax];//在队列中的顾客信息
public:
	Queue(void)
	{
		NumOfQueue = 0;
	}
	int GetNumOfQueue(void)
	{
		return NumOfQueue;
	}
	bool GetHead(Customer &Head)//获得队列的头并删除
	{
		if(NumOfQueue <=0)
			return false;
		Head = OldCustomer[0];
		for(int i = 0; i < QueueMax - 1; i++)
			OldCustomer[i] = OldCustomer[i + 1];
		NumOfQueue--;
		return true;
	}
	bool ShowHead(Customer &Head)//获得队列的头
	{
		if(NumOfQueue <=0)
			return false;
		Head = OldCustomer[0];
		return true;
	}
	bool AddElem(Customer Elem)//向队列尾添加顾客信息
	{
		if(NumOfQueue >= QueueMax)
			return false;
		OldCustomer[NumOfQueue++] = Elem;
		return true;
	}
	bool IsFull(void)//判断队列是否为满
	{
		if(NumOfQueue >= QueueMax)
			return true;
		return false;
	}
	bool IsEmpty(void)//判断队列是否为空
	{
		if(NumOfQueue <= 0)
			return true;
		return false;
	}
	bool GetTail(Customer &Elem)//获得队列尾并删除
	{
		if(NumOfQueue <= 0)
			return false;
		Elem = OldCustomer[NumOfQueue - 1];
		NumOfQueue--;
		return true;
	}
	bool ShowTail(Customer &Elem)//获得队列尾
	{
		if(NumOfQueue <= 0)
			return false;
		Elem = OldCustomer[NumOfQueue - 1];
		return true;
	}
}A,B;//声明A、B两个队列

//获得给顾客的服务时间
double ServeTime(void)
{
	return 800.0 * rand() / 32767.0;/*需要改动*///rand返回int型，0~32767
}

//获得顾客到达的时刻
double EnterTime(void)
{
	return 10.0 * rand() / 32767.0;/*需要改动*/
}

//有顾客到达
bool CustomerArrived(void)
{
	printf("A ");
	NumOfCustomer++;
	if(A.IsFull() == true && B.IsFull() == true)//队列已满，顾客离去
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
	if(A.GetNumOfQueue() <= B.GetNumOfQueue())//A,B窗口人数相同时优先选择A窗口
	{
		A.ShowTail(temp);
		temp.EnterTime += tempTime;
		temp.LeaveTime = temp.EnterTime + temp.ServeTime;
		A.AddElem(temp);
		CurTime += tempTime;
		printf("A+ ");
	}
	else//顾客进入队列B
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

//获得服务的顾客离去
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
	if(A.IsEmpty() == true && B.IsEmpty() == true)//队列清空，服务员等待
	{
		QueueIsEmpty = true;//设置队列空标志
		printf("NON ");
		return false;
	}
	return true;//队列不为空，服务员忙
}

//顾客变换队列
bool CustomerChange(void)
{
	Customer temp1, temp2;
	//A队列长于B队列+1时
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
	//B队列长于A队列+1时
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

//初始化两队列A、B
bool OpenForDay(void)
{
	CurTime = 0.0;
	Customer temp1, temp2;
	//初始化A队列
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
	//初始化B队列
	temp2.EnterTime = 0.1;
	temp2.ServeTime = ServeTime();
	temp2.LeaveTime = temp2.EnterTime + temp2.ServeTime;
	B.AddElem(temp2);
	CurTime = 0.1;
	temp2.EnterTime = CurTime + EnterTime();
	temp2.ServeTime = ServeTime();
	temp2.LeaveTime = temp2.EnterTime + temp2.ServeTime;
	B.AddElem(temp2);
	//确定当前时间CurTime
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
	printf("\n系统中的平均顾客数：%f", NumOfCustomer/TotalTime);
	printf("\n出纳员的利用率：%f", (TotalTime - NotServeForCustomer)/TotalTime);
	printf("\n因顾客排满而离去的顾客数：%ld", DepartureCustomer);
	printf("\n在排队中转换队列的顾客数：%ld", ChangeCustomer);
	getch();
	return 0;
}

