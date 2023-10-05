#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define FALSE 0
#define TURE 1
typedef int Stautes;

void int_speed(void)
{
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	textcolor(GREEN);
	textbackground(BLACK);
	time_t t1,t2;
	int i,j=2;       //"j" is  times of  run time
	cprintf("\n\n\n\n\n\r");
	cprintf("  Testing CPU speed...\n\n\r");
	cprintf("  May be need several minutes, please wait...\n\r");
	asm mov ax,0ffffh
	asm mov bx,0
	t1=time(NULL);
	for(i=1;i<=j;i++)
	{
		asm mov cx,0ffffh
	     next11:
		asm mov dx,0ffffh
	     next12:
		asm dec ax
		asm inc bx
		asm sub ax,bx
		asm add ax,bx
		asm inc ax
		asm dec bx
		asm dec dx
		asm jnz next12
		asm loop next11
	}
	t2=time(NULL);
	cprintf("\n\n\n\n\n\r  Test used total  ");
	textcolor(YELLOW);
	textbackground(BLUE);
	cprintf("%ld",(t2-t1));
	textcolor(GREEN);
	textbackground(BLACK);
	cprintf("  seconds\n\n\n\r");
	cprintf("  CPU speed is  ");
	textcolor(YELLOW);
	textbackground(BLUE);
	textcolor(YELLOW);
	textbackground(BLUE);
	cprintf("%lf",j*19500.0/(t2-t1));
	textcolor(GREEN);
	textbackground(BLACK);
	cprintf("  MHz: \n\n\n\n\r");
	textcolor(8);
	textbackground(BLACK);
	cprintf("  Press any to quit.");
	getch();
}

Stautes first_page()
{
       char presskey;
       textbackground(BLACK);
       textcolor(WHITE);
       clrscr();
       textcolor(YELLOW);
       textbackground(GREEN);
       gotoxy(33,6);
       cprintf("              ");
       gotoxy(33,7);
       cprintf("   CPUSPEED   ");
       gotoxy(33,8);
       cprintf("              ");
       gotoxy(16,11);
       cprintf("                   Version 1.0                    ");
       gotoxy(16,12);
       cprintf(" Copyright (c) 2001 by the self-programmer LiJia  ");
       gotoxy(16,13);
       cprintf(" Computer department of Capital Normal University ");
       textbackground(YELLOW);
       textcolor(135);
       gotoxy(20,16);
       cprintf("Do you want to check your CPU speed?(Y/N)");
       presskey=getch();
       if(presskey=='Y' || presskey=='y') return TURE;
       else return FALSE;
}

void main(void)
{
	if(first_page()==FALSE) goto end;
	else int_speed();
      end:
	textbackground(BLACK);
	textcolor(WHITE);
	clrscr();
	textbackground(BLACK);
	textcolor(15);
	gotoxy(30,12);
	cprintf("The program is end.");
	exit(0);
}
