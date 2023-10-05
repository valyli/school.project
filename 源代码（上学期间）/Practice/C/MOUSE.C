#include <stdlib.h>
#include <dos.h>
#include <process.h>
#include <conio.h>
#include <bios.h>
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>

#define BUFFLEN 10800
#define BUFFMAX 900

void Init(void);
void check(unsigned char states);
void enableports(void);
void interrupt far asyncint(void);
void interrupt (*asyncvect)(void);
void putb(unsigned char ch);

unsigned char inchar, flag = 0;
unsigned char Buffer[BUFFLEN];
int buffin = 0;
int buffout = 0;
int i = 0, ii = 0;
unsigned char temp_buffer[BUFFMAX];
unsigned char ch;//, flag;
void enableports(void)
{
	unsigned char B;
	asyncvect = getvect(0x0c);
	disable();
	inportb(0x3f8);
	inportb(0x3fe);
	inportb(0x3fb);
	inportb(0x3fa);
	outportb(0x3fc, 0x08|0x0b);
	outportb(0x3f9, 0x01);
	B = inportb(0x21)&0xef;
	outportb(0x21, B);
	setvect(0x0c, asyncint);
	enable();
}

void interrupt far asyncint(void)
{
	unsigned char ch;
	ch = inportb(0x3f8);
	flag = 1;
	putb(ch);
	outportb(0x20, 0x20);
}

void disableports(void)
{
	disable();
	outportb(0x3f9, 0x00);
	outportb(0x3fc, 0x00);
	outportb(0x21, inportb(0x21)&0x10);
	enable();
	setvect(0x0c, asyncvect);
}

void Init()
{
	outportb(0x3fb, 0x80);
	outportb(0x3f8, 0x0c);
	outportb(0x3f9, 0x00);
	outportb(0x3fb, 0x1f);
	outportb(0x3fc, 0x08|0x0b);
	outportb(0x3f9, 0x01);
}

void check(unsigned char states)
{
	while((inportb(0x3fd)&states) == 0);
}

void putb(unsigned char ch)
{
	int temp = 0;
	if(++ii>BUFFMAX) ii = 0;
		temp = buffin;
	if(++buffin == BUFFLEN) buffin = 0;
	if(buffin != buffout)
		Buffer[buffin] = ch;
	else
		buffin = temp;
		temp_buffer[ii] = ch;
}

unsigned char getb(void)
{
	if(buffout != buffin)
	{
		if(++buffout == BUFFLEN) buffout = 0;
		return (Buffer[buffout]);
	}
	else return (0xff);
}

main()
{
	clrscr();
	window(3,2,41,10);
	textcolor(0);
	textbackground(3);
	clrscr();
	gotoxy(3,2);
	cprintf("   Receive from COM1:\n");
	gotoxy(3,4);
	cprintf(" 9600 bps, 8 bit, 2 stop, even\n");
	gotoxy(3,6);
	textcolor(223);
	cprintf(" Press any key Countiune!\n");
	getch();
	window(45, 2, 79, 22);
	textbackground(1);
	textcolor(14);
	clrscr();
	Init();
	enableports();
	clrscr();
	for(;;)
	{
		if(flag == 1)
		{
			ch = getb();
			cprintf("%c", ch);
			flag = 0;
		}
		if(kbhit() != 0)
		{
			exit(1);
			disableports();
		}
	}
}

