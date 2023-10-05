#include<dos.h>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#define NUM 5

background()
{int xo=20,yo=20,maxx,maxy;
cleardevice();
maxx=getmaxx();maxy=getmaxy();
setcolor(WHITE);
rectangle(xo,yo,maxx-xo,maxy-yo);
setfillstyle(6,BLUE);
floodfill(xo+1,yo+1,WHITE);
}
get_key()
 {
   union REGS r;
   r.h.ah=0;
   return (int86(0x16,&r,&r));
 }

fuc0(){background();
       moveto(300,200);
       outtextxy(300,200,"1+1=2\n");
       outtextxy(300,210,"press any key to continue");
       getch();
       }
fuc1(){}
fuc2(){}
fuc3(){}



main(){

int xo=20,yo=20,dx=150,dy=50,maxx,maxy,x1,y1,i,n=0;
char button[NUM][10]={"newfile","openfile","tongji","help","exit"};
int driver,mode;
union scan{
    int c;
    char ch[2];
    } sc;
driver=DETECT;
mode=0;
initgraph(&driver,&mode,"");
do{
cleardevice();
maxx=getmaxx();maxy=getmaxy();
x1=(maxx-dx)/2;y1=(maxy-dy*NUM)/2;

setcolor(WHITE);
rectangle(xo,yo,maxx-xo,maxy-yo);
setfillstyle(6,BLUE);
floodfill(xo+1,yo+1,WHITE);
setfillstyle(1,GREEN);
for (i=0;i<=NUM-1;i++)
   { rectangle(x1,y1+i*dy,x1+dx,y1+i*dy+dy);
     floodfill(x1+1,y1+i*dy+1,WHITE);
   }
for (i=0;i<=NUM-1;i++)
   { outtextxy(x1+(dx-strlen(button[i])*7)/2,y1+dy/2+i*dy-3,button[i]);
     outtextxy(x1+(dx-strlen(button[i])*7)/2,y1+dy/2+i*dy+4
     ,"-");

   }



      do{
      setfillstyle(9,GREEN);
      bar(x1+1,y1+n*dy+1,x1+dx-1,y1+n*dy+dy-1);
      outtextxy(x1+(dx-strlen(button[n])*7)/2,y1+dy/2+n*dy-3,button[n]);
      outtextxy(x1+(dx-strlen(button[n])*7)/2,y1+dy/2+n*dy+4,"_");
      sc.c=get_key();

      switch(sc.ch[1])
	 {
	   case 72: n--;{  setfillstyle(1,GREEN);
			   bar(x1+1,y1+(n+1)*dy+1,x1+dx-1,y1+(n+1)*dy+dy-1);
			   outtextxy(x1+(dx-strlen(button[n+1])*7)/2,y1+dy/2+(n+1)*dy-3,button[n+1]);
			   outtextxy(x1+(dx-strlen(button[n+1])*7)/2,y1+dy/2+(n+1)*dy+4,"_");
			   break;
			 }

	   case 80: n++;{ setfillstyle(1,GREEN);
			   bar(x1+1,y1+(n-1)*dy+1,x1+dx-1,y1+(n-1)*dy+dy-1);
			   outtextxy(x1+(dx-strlen(button[n-1])*7)/2,y1+dy/2+(n-1)*dy-3,button[n-1]);
			   outtextxy(x1+(dx-strlen(button[n-1])*7)/2,y1+dy/2+(n-1)*dy+4,"_");
			   break;
			 }

	 }




	   if(n>NUM-1) n=0;
	   if(n<0)   n=NUM-1;

     }while (sc.ch[0]!=13);
   switch(n){
      case 0: fuc0();break;
      case 1: fuc1();break;
      case 2: fuc2();break;
      case 3: fuc3();break;

     }
  }while(n!=4);





}

