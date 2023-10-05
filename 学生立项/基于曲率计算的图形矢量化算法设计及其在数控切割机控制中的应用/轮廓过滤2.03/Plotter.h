//////////////////////////////////////////////////////////
//														//
//			 �׶�ʦ����ѧ�����ϵ�����Ӿ��о���			//
//			Copyright by Computer Version Studio		//
//				of Capital Normal University			//
//						  2001��8��						//
//														//
//				����HPGL��׼���豸���Ƴ���				//
//														//
//////////////////////////////////////////////////////////


// Plotter.h: interface for the Plotter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLOTTER_H__2857EDCF_82AA_11D5_8961_00609721CE30__INCLUDED_)
#define AFX_PLOTTER_H__2857EDCF_82AA_11D5_8961_00609721CE30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include<string.h>
#include<stdlib.h>

#define PHYSTEP 0.025
#define COMMANDLEN 25

struct Coordinates
{
	int x;
	int y;
};

struct Position
{
	double x;
	double y;
};

class Plotter  
{
protected:
	char temp[20];
	char pLastOut[COMMANDLEN];
	bool OutPort(char* pOut);
	char* NumtoAsc(int num);
	char* XYtoAsc(int x, int y);
	Coordinates Abspos;
	Position Phypos;
	long double Step;
	bool PenDown;
	byte PenSpeed;
	bool Enable;
	HANDLE hFile;
public:
	bool YT();
	bool XT();
	bool ClosePort();
	bool Line(int x1, int y1, int x2, int y2);
	bool Shape(Coordinates *q, int n);
	bool MoveTo(int x, int y);
	bool LineTo(int x, int y);
	bool BSP(Coordinates *q, int n, int acc);		//B����
	bool Parabola(Coordinates *q, int n, int acc);	//����������������
	bool Shape(Coordinates *q, int n, int acc);		//���պ�ͼ��
	//������
	//q[][2]��	��ֵ�����Ƶ����������
	//n��		��ֵ�����Ƶ�ĸ���
	//acc��		����
	bool PU();
	bool PD();
	byte VS();
	double PlotterStep(double input);
	double PlotterStep();
	double Phyposy();
	double Phyposx();
	char* LastOut();
	bool PortEnable();
	bool VS(byte speed);
	int Absposy();
	int Absposx();
	bool PD(int x, int y);
	bool PU(int x, int y);
	bool PA(int x, int y);
	bool PR(int x, int y);
	bool OpenPort();
	bool InitPlotter();
	Plotter();
	virtual ~Plotter();

};

#endif // !defined(AFX_PLOTTER_H__2857EDCF_82AA_11D5_8961_00609721CE30__INCLUDED_)
