// Plotter.cpp: implementation of the Plotter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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
	//InitPlotter();
	CloseHandle(hFile);
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

bool Plotter::LineTo(int x, int y)
{
	if(PenDown == false)
		if(!PD())
			return false;
	if(!PA(x, y))
		return false;
    Abspos.x = x;
	Abspos.y = y;
	return true;
}

bool Plotter::Parabola(Coordinates *q, int n, int acc)
{
 	int i,j;
	int px,py;
	double t,t2,t3;
	double f1,f2,f3,f4;

	px = q[1].x;
	py = q[1].y;

    if(!MoveTo(px, py))
		return false;

    for(i=0;i<n-3;i++)
	{
		for(j=1;j<acc;j++)
		{
			t=j*0.5/(acc + 1);
			t2 = t*t;
			t3 = t2*t;
			f1 = 4.0*t2-t-4.0*t3;
	        f2 = 1.0-10.0*t2+12.0*t3;
			f3 = t+8.0*t2-12.0*t3;
			f4 = 4.0*t3-2.0*t2;
			px = (int)(f1*q[i].x+f2*q[i+1].x+f3*q[i+2].x+f4*q[i+3].x);
			py = (int)(f1*q[i].y+f2*q[i+1].y+f3*q[i+2].y+f4*q[i+3].y);
			if(!(LineTo(px, py)))
				return false;
		}
		if(!(LineTo(q[i+2].x, q[i+2].y)))
			return false;
	}
	if(!(PU()))
		return false;
	return true;
}

bool Plotter::BSP(Coordinates *q, int n, int acc)
{
	int i;
	int start = 0;
	double t3,t2,t1,t;
	double f0,f1,f2,f3;
	int px,py;
	
/*    if(!(PU()) || !(PA(q[0].x,q[0].y)) || !(PD()))	//²Î¿¼Ö±Ïß
		return false;
	
	for(i=1;i<n;i++)
		LineTo(q[i].x,q[i].y);
*/
	t=1.0/acc;
	for(int j = 0; j<=n-4; j++)
	{
		for(i=1; i<=acc; i++)
		{
			t1=i*t;
			t2=t1*t1;
			t3=t2*t1;

			f0=(-t3+3*t2-3*t1+1)/6;
			f1=(3*t3-6*t2+4)/6;
			f2=(-3*t3+3*t2+3*t1+1)/6;
			f3=t3/6;

			px=(int)(f0*q[j].x+f1*q[j+1].x+f2*q[j+2].x+f3*q[j+3].x);
			py=(int)(f0*q[j].y+f1*q[j+1].y+f2*q[j+2].y+f3*q[j+3].y);
			if(start == 0)
            if(!MoveTo(px, py))
				return false;
			start++;
			LineTo(px, py);
		}
	}
	if(!PU())
		return false;
	return true;
}

bool Plotter::MoveTo(int x, int y)
{
	if(PenDown == true)
		if(!PU())
			return false;
	if(!PA(x, y))
		return false;
    Abspos.x = x;
	Abspos.y = y;
	return true;

}

bool Plotter::Shape(Coordinates *q, int n, int acc)
{
	Coordinates *p = new Coordinates[n+3];
	p[0] = q[n-1];
	for(int i = 0; i < n; i++)
		p[i+1] = q[i];
	p[n+1] = q[0];
	p[n+2] = q[1];
	if(!Parabola(p, n+3, acc))
		return false;
	return true;
}

bool Plotter::Shape(Coordinates *q, int n)
{
	int i;
	MoveTo(q[0].x, q[0].y);
	if(!PD())
		return false;
	for(i = 1; i < n; i++)
	{
		LineTo(q[i].x, q[i].y);
	}
	LineTo(q[0].x, q[0].y);
	if(!PU())
		return false;
	return true;
}

bool Plotter::Line(int x1, int y1, int x2, int y2)
{
	if(!(MoveTo(x1, y1) && LineTo(x2, y2)))
		return false;
	return true;
}

bool Plotter::ClosePort()
{
	if(CloseHandle(hFile))
	{
		Enable = false;
		return true;
	}
	else
		return false;
}

bool Plotter::XT()
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"XT;");
	if(!OutPort(pOut))
		return false;
	return true;
}

bool Plotter::YT()
{
	char pOut[COMMANDLEN];
	strcpy(pOut,"");
	strcat(pOut,"YT;");
	if(!OutPort(pOut))
		return false;
	return true;
}
