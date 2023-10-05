#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

char temp[20] = {""};
char out[20] = {""};
int ox = 0,oy = 0;
int cx = 0, cy = 0;

char* Pntoc(int num)
{
	sprintf(temp,"%d",num);
	return temp;
}

void Ppa(int x, int y)
{
//	int length;
	strcpy(out,"PA");
	strcat(out,Pntoc(x));
	strcat(out,",");
	strcat(out,Pntoc(y));
	strcat(out,";");
//	length = strlen(out);
	fprintf(stdprn,out);
}

void Ppd()
{
	fprintf(stdprn,"PD;");
}

void Ppu()
{
	fprintf(stdprn,"PU;");
}

void Pline(int x1, int y1, int x2, int y2)
{
	Ppa(x1, y1);
	Ppd();
	Ppa(x2, y2);
//	Ppu();
	cx = x2;
	cy = y2;
}

void Plineto(int x, int y)
{
	Ppa(cx, cy);
	Ppd();
	Ppa(x, y);
//	Ppu();
	cx = x;
	cy = y;
}

void Pcircle(int px, int py, int r, float a)
{
//	float a;
	int x, y;
	int ix, iy;
	cx = px + ox + r;
	cy = py + oy;
	ix = cx;
	iy = cy;
	Ppu();
	Ppa(cx, cy);
	for(float i = 0.0; i < M_PI * 2; i = i + a)
	{
		y = (int)(r * sin(i));
		x = (int)(r * cos(i));
		x = px + ox + x;
		y = py + oy + y;
		printf("%f ",i);
		Plineto(x, y);
	}
	Plineto(ix,iy);
	Ppu();
}

void main()
{
	int x, y, r;
	float a;
	printf("The Computer Version Studio of Computer Department of CNU\n");
	printf("Input circle\n");
	printf("x = ");
	scanf("%d", &x);
	printf("\n");
	printf("y = ");
	scanf("%d", &y);
	printf("\n");
	printf("radius = ");
	scanf("%d", &r);
	printf("\n");
	printf("step = ");
	scanf("%f", &a);
	printf("\n");
	Pcircle(x, y, r, a);
	printf("Drawing...");
	exit(0);
}
