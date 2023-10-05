// Plotter.cpp: implementation of the Plotter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "try3.h"
#include "Plotter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Plotter::Plotter()
{
	Abspos.x = 0;
	Abspos.y = 0;
	Phypos.x = 0.0;
	Phypos.y = 0.0;
	Step = PHYSTEP;
	PenDown = false;
	PenSpeed = 127;
	Enable = false;
	strcpy(pLastOut,"");
}

Plotter::~Plotter()
{
	InitPlotter();
	Enable = false;
}

char * Plotter::NumtoAsc(int num)
{
	sprintf(temp,"%d;",num);
	return temp;
}

bool Plotter::InitPlotter()
{
	if(!OutPort("IN;PU;PA0,0;"))
		return false;
	Abspos.x = 0;
	Abspos.y = 0;
	Phypos.x = 0.0;
	Phypos.y = 0.0;
	Step = PHYSTEP;
	PenDown = false;
	PenSpeed = 127;
	Enable = true;
	return true;
}

bool Plotter::OpenPort()
{
	CString m_LPTString=_T("LPT1");
	hFile=CreateFile(
		m_LPTString,
		GENERIC_READ|GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		NULL,
		NULL
		);
	if(hFile==INVALID_HANDLE_VALUE)
	{
		AfxMessageBox("Invalid LPT1 can not open");
		return FALSE;
	}
	Enable = true;
	return TRUE;
}


bool Plotter::PR(int x, int y)
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"PR");
	strcat(pOut,XYtoAsc(x,y));
	if(!OutPort(pOut))
		return false;
	Abspos.x += x;
	Abspos.y += y;
	return true;
}

char* Plotter::XYtoAsc(int x, int y)
{
	sprintf(temp,"%d,%d;",x,y);
	return temp;
}

bool Plotter::PA(int x, int y)
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"PA");
	strcat(pOut,XYtoAsc(x,y));
	if(!OutPort(pOut))
		return false;
	Abspos.x = x;
	Abspos.y = y;
	return true;
}


bool Plotter::PU(int x, int y)
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"PU;PA");
	strcat(pOut,XYtoAsc(x,y));
	if(!OutPort(pOut))
		return false;
	PenDown = false;
	Abspos.x = x;
	Abspos.y = y;
	return true;
}

bool Plotter::PD(int x, int y)
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"PD;PA");
	strcat(pOut,XYtoAsc(x,y));
	if(!OutPort(pOut))
		return false;
	PenDown = true;
	Abspos.x = x;
	Abspos.y = y;
	return true;
}

int Plotter::Absposx()
{
	return Abspos.x;
}

int Plotter::Absposy()
{
	return Abspos.y;
}

bool Plotter::VS(byte speed)
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"VS");
	strcat(pOut,NumtoAsc((int)speed));
	if(!OutPort(pOut))
		return false;
	PenSpeed = speed;
	return true;
}

bool Plotter::OutPort(char* pOut)
{
	if(hFile==INVALID_HANDLE_VALUE && Enable != false)
	{
		AfxMessageBox("Invalid LPT1 was not open!");
		return false;
	}
	else
	{
		DWORD number;
		int length = strlen(pOut);
		if(!WriteFile(hFile,pOut,length,&number,NULL))
		{
			AfxMessageBox("Fail to send data.");
			Enable = false;
			return false;
		}
		strcpy(pLastOut,pOut);
		return true;
	}
}

bool Plotter::PortEnable()
{
	return Enable;
}

char* Plotter::LastOut()
{
	return pLastOut;
}

double Plotter::Phyposx()
{
	Phypos.x = Abspos.x * Step;
	return Phypos.x;
}

double Plotter::Phyposy()
{
	Phypos.y = Abspos.y * Step;
	return Phypos.y;
}

double Plotter::PlotterStep()
{
	return Step;
}

double Plotter::PlotterStep(double input)
{
	double OldStep = Step;
	Step = input;
	return OldStep;
}

byte Plotter::VS()
{
	return PenSpeed;
}

bool Plotter::PD()
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"PD;PA");
	strcat(pOut,XYtoAsc(Abspos.x,Abspos.y));
	if(!OutPort(pOut))
		return false;
	PenDown = true;
	return true;
}

bool Plotter::PU()
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"PU;PA");
	strcat(pOut,XYtoAsc(Abspos.x,Abspos.y));
	if(!OutPort(pOut))
		return false;
	PenDown = false;
	return true;
}
