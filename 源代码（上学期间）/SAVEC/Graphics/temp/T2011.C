/* This program is try to draw a line , a circle , a rectangle
and some prixels on the screen.
*/

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#define PI 3.14159

void init();
void frame();
void draw();

void main()
{
   init();
   frame();
   draw();
   closegraph();
}

void init()
{
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
}

void frame()
{
  outtextxy(50,50,"Practice drawing:");
  line(0,440,639,440);
  setcolor(RED);
  outtextxy(30,450,"E-exit" );
}

void draw()
{
   int x,y;
   char ch;

   setcolor(BLUE);

   circle(320,240,100);       // draw a circle

   rectangle(220,140,420,340); //draw a rectangle

   line(220,240,420,240); //draw a line

   for (x=220;x<=420;x++)
    for (y=140;y<=340;y++)
      { if( x%10==0 && y%10==0)
	 putpixel(x,y,BLUE);               /* draw some piont;*/
      }

   while(1)
     { ch=getch();
       if ((ch=='e')||(ch=='E'))
	break;
     }
}