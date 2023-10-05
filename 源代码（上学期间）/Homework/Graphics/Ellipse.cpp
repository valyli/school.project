#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void MidpointEllipse(int xc, int yc, int a, int b, int color)
{
	long aa = a * a, bb = b * b;
	long twoaa = 2 * aa, twobb = 2 * bb;
	long x = 0, y = b;
	long d;
	long dx = 0;
	long dy = twoaa * y;
	d = long(bb + aa * (-b + 0.25) + 0.5);
	putpixel(xc + x, yc + y, color);
	putpixel(xc + x, yc - y, color);
	putpixel(xc - x, yc + y, color);
	putpixel(xc - x, yc - y, color);
	while(dx < dy)
	{
		x++;
		dx += twobb;
		if(d<0)
			d += bb + dx;
		else
		{
			dy -= twoaa;
			d += bb + dx - dy;
			y--;
		}
		putpixel(xc + x, yc + y, color);
		putpixel(xc + x, yc - y, color);
		putpixel(xc - x, yc + y, color);
		putpixel(xc - x, yc - y, color);
	}
	d = long(bb * (x + 0.5) * (x + 0.5) + aa * (y - 1)*(y - 1) - aa * bb + 0.5);
	while(y>0)
	{
		y--;
		dy -= twoaa;
		if(d>0)
			d += aa - dy;
		else
		{
			x++;
			dx += twobb;
			d += aa -dy +dx;
		}
		putpixel(xc + x, yc + y, color);
		putpixel(xc + x, yc - y, color);
		putpixel(xc - x, yc + y, color);
		putpixel(xc - x, yc - y, color);
	}
}

void main()
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics mode */
	initgraph(&gdriver, &gmode, "d:\\tc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();

	if(errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}


	int a,b,color;
	a=100;
	b=70;
	color=5;
	MidpointEllipse(320,240,a,b,color);
	getch();
	closegraph();
	exit(1);
}