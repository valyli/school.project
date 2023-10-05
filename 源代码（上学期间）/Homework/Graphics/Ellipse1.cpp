#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.14159

void MidpointEllipse(int xc, int yc, int a, int b, int color)
{
	int aa = a * a, bb = b * b;
	int twoaa = 2 * aa, twobb = 2 * bb;
	int x = 0, y = b;
	int d;
	int dx = 0;
	int dy = twoaa * y;
	d = int(bb + aa * (-b + 0.25) + 0.5);
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
	d = int(bb * (x + 0.5) * (x + 0.5) + aa * (y - 1)*(y - 1) - aa * bb + 0.5);
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
  int a,b,color;
  a=200;
  b=100;
  color=5;
   int gdriver = VGA, gmode = VGAHI,errorcode;
   initgraph(&gdriver,&gmode, "d:\\tc\\bgi");
   /* read result of initialization */
   errorcode = graphresult();
   if (errorcode != grOk)  /* an error occurred */
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);             /* return with error code */
   }
   setbkcolor(CYAN);
   setcolor(BLUE);
  //matrix();
//  init();
  MidpointEllipse(320,240,a,b,color);
  getch();
  //kg();
  closegraph();
  exit(0);
}