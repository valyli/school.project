#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
#define TEMPINPUTLONG 20
#define LEN sizeof(struct student)
#define NULL 0
#define NUM_LONG 10
#define NAME_LONG 20

struct student
{struct student *previous;
 char num[NUM_LONG];
 char name[NAME_LONG];
 int math,english,computer;
 struct student *next;
};

enum color{HEI,LAN,LU,QING,HONG,Y_HONG,HE,L_HUI,SHEN_HUI,
	   L_LAN,L_LU,L_QING,L_HONG,L_YANGHONG,HUANG,BAI};

struct student *head=NULL;
int n=0;
int mainkey=10;
int MB=HE,MF=L_HUI,MAB=Y_HONG,MAF=BAI,WB=LAN,WF=HUANG,
    WIB=LU,WIF=HUANG,WOB=LU,WOF=HUANG,WOTB=LAN,
    WOTF=HUANG,AB=HONG,AF=HUANG,Y=HEI,BB=LAN,BF=L_HUI,
    LB=HE,LF=BAI;


void presskey(void)
{char a1,a2;
 do
 {a1=getch();
  if(a1=='\015')
  {mainkey=mainkey+100;
   goto enter;
  }
  if(a1=='\033')
  {mainkey=0;
   goto enter;
  }
  if(a1!='\000')
  {a2='\000';
   break;
  }
  a2=getch();
  if(a2=='\120' || a2=='\110' || a2=='\113' || a2=='\115') break;
 }while(1);
 if(a2=='\120')
 {mainkey=mainkey+1;
  if(mainkey==14) mainkey=11;
  else if(mainkey==24) mainkey=21;
  else if(mainkey==32) mainkey=31;
  else if(mainkey==42) mainkey=41;
  else if(mainkey==53) mainkey=51;
 }
 if(a2=='\110')
 {mainkey=mainkey-1;
  if(mainkey==10) mainkey=13;
  else if(mainkey==20) mainkey=23;
  else if(mainkey==30) mainkey=31;
  else if(mainkey==40) mainkey=41;
  else if(mainkey==50) mainkey=52;
 }
 if(a2=='\113')
 {mainkey=(int)(mainkey/10);
  mainkey=mainkey*10;
  mainkey=mainkey-10;
  if(mainkey==0) mainkey=50;
  mainkey=mainkey+1;
 }
 if(a2=='\115')
 {mainkey=(int)(mainkey/10);
  mainkey=mainkey*10;
  mainkey=mainkey+10;
  if(mainkey==60) mainkey=10;
  mainkey=mainkey+1;
 }
 enter:;
}


void start_program(void)
{int i;
 textcolor(Y);textbackground(Y);
 for(i=11;i<=15;i++)
 {gotoxy(17,i);
  cprintf("                                               ");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(16,10);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» ");
 gotoxy(16,11);cprintf(" º   Management-system of Students' Status   º ");
 gotoxy(16,12);cprintf(" º                Version 1.1                º ");
 gotoxy(16,13);cprintf(" º     Copyright (c) 2000,9 by LiJia,CNU.    º ");
 gotoxy(16,14);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ ");
 getch();
}

void background_program(void)
{int i;
 textcolor(LF);textbackground(LB);
 gotoxy(1,25);
 cprintf("                                                                                ");
 textcolor(BF);textbackground(BB);
 gotoxy(1,1);
 for(i=1;i<=24;i++)
 {gotoxy(1,i);
  cprintf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
 }
}

void draw_menubackground(void)
{char a,b;
 textcolor(MF);textbackground(MB);
 gotoxy(1,1);
 cprintf("  File  Edit  Print  Quit                                                 Help  ");
 gotoxy(1,25);
 textcolor(LF);textbackground(LB);
 cprintf(" Comment: ESC->Main ");
}

void end_program(void)
{int i;
// int colorf0=7,colorf1=14,colorb0=0,colorb1=1;
 clrscr();
 textcolor(WF);textbackground(WB);
 for(i=1;i<=23;i++)
 {gotoxy(1,i);
  cprintf("                                                                                ");
 }
 gotoxy(1,5);
 cprintf("ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ»\n\r");
 cprintf("º                                                                            º\n\r");
 cprintf("º  ÜÜÜÜÜÜÜÜÜ  Û                       Û                                      º\n\r");
 cprintf("º  ßßßßÛßßßß  Û                       Û                                      º\n\r");
 cprintf("º      Û      Û                       Û                                      º\n\r");
 cprintf("º      Û      ÛÜßßÜ    ßßßÜ   ÛÜßßÜ   Û   Üß         Û    Û   ÜßßÜ   Û    Û  º\n\r");
 cprintf("º      Û      Û    Û       Û  Û    Û  Û Üß           Û    Û  Û    Û  Û    Û  º\n\r");
 cprintf("º      Û      Û    Û   ÜßßÜÛ  Û    Û  ÛÛ             Û    Û  Û    Û  Û    Û  º\n\r");
 cprintf("º      Û      Û    Û  Û    Û  Û    Û  Û ßÜ           Û    Û  Û    Û  Û    Û  º\n\r");
 cprintf("º      Û      Û    Û   ßÜÜßÛ  Û    Û  Û   ßÜ          ßÜÜßÛ   ßÜÜß    ßÜÜßÛ  º\n\r");
 cprintf("º                                                        Üß                  º\n\r");
 cprintf("º                                                    ÜÜÜß                    º\n\r");
 cprintf("º                                                                            º\n\r");
 cprintf("ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼\n\r");
 textcolor(Y);textbackground(Y);
 for(i=24;i<=25;i++)
 {gotoxy(1,i);
  cprintf("                                                                                ");
 }
}




void input(char inputchar[],int tempinputlong)
{int i=0;
 char a;
 do
 {a=getch();
  if(a=='\r' || a=='\033') break;
  else if(a=='\000')
  {a=getch();
   goto input_error;
  }
  else if(a=='\010')
  {if(i==0) goto input_error;
   else
   {printf("\b \b");
    i--;
    goto input_error;
   }
  }
  printf("%c",a);
  inputchar[i]=a;
  i++;
  if(i>=tempinputlong) break;
  input_error:;
 }while(a!='\r' && a!='\033');
 if(a=='\033')
 {inputchar[0]='\250';
  inputchar[1]='\255';
  inputchar[2]='\0';
 }
 else inputchar[i]='\0';
}

long char_int(char inputchar[])
{int i=0,end=0,temp;
 long outputint=0;
 while(inputchar[i]!='\0') i++;
 end=i;
 if(end>9)
 {outputint=-1;
  goto error_intput;
 }
 i=0;
 while(end!=0)
 {switch(inputchar[end-1])
  {case'0':temp=0;break;
   case'1':temp=1;break;
   case'2':temp=2;break;
   case'3':temp=3;break;
   case'4':temp=4;break;
   case'5':temp=5;break;
   case'6':temp=6;break;
   case'7':temp=7;break;
   case'8':temp=8;break;
   case'9':temp=9;break;
   default:temp=-1;
  }
  if(temp==-1)
  {outputint=-1;
   goto error_intput;
  }
  outputint=outputint+temp*pow(10,i);
  end--;
  i++;
 }
 error_intput:
 return(outputint);
}

void print(struct student *p,int step)
{int d=1;
 if(step<0) d=-1;
 step+=d;
 do
 {step-=d;
  cprintf("%-10s",p->num);
  cprintf("³");
  cprintf("%-20s",p->name);
  cprintf("³");
  cprintf("%10d",p->math);
  cprintf("³");
  cprintf("%9d",p->english);
  cprintf("³");
  cprintf("%10d",p->computer);
  if(p->previous==NULL || p->next==NULL) break;
 }while(step);
}

void creat_input_map(void)
{gotoxy(40,10);cprintf("                    \n\r");
 gotoxy(40,12);cprintf("                    \n\r");
 gotoxy(40,14);cprintf("                    \n\r");
 gotoxy(40,16);cprintf("                    \n\r");
 gotoxy(40,18);cprintf("                    \n\r");
}


void creat(void)
{struct student *p1,*p2;
 int i;
 char a;
 char input_temp[TEMPINPUTLONG];
 n=0;
 p1=(struct student *)malloc(LEN);
 p2=p1;
 textcolor(Y);textbackground(Y);
 for(i=9;i<=21;i++)
 {gotoxy(22,i);
  cprintf("                                          \n\r");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(21,8);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» \n\r");
 gotoxy(21,9);cprintf(" º                                      º \n\r");
 gotoxy(21,10);cprintf(" º Input num:                           º \n\r");
 gotoxy(21,11);cprintf(" º                                      º \n\r");
 gotoxy(21,12);cprintf(" º Input name:                          º \n\r");
 gotoxy(21,13);cprintf(" º                                      º \n\r");
 gotoxy(21,14);cprintf(" º Input math:                          º \n\r");
 gotoxy(21,15);cprintf(" º                                      º \n\r");
 gotoxy(21,16);cprintf(" º Input english:                       º \n\r");
 gotoxy(21,17);cprintf(" º                                      º \n\r");
 gotoxy(21,18);cprintf(" º Input computer:                      º \n\r");
 gotoxy(21,19);cprintf(" º                                      º \n\r");
 gotoxy(21,20);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ \n\r");
 textcolor(WIF);textbackground(WIB);
 creat_input_map();
 gotoxy(40,10);
 input(p1->num,NUM_LONG-1);
 head=NULL;
 while(strcmp(p1->num,"¨­")!=0)
 {gotoxy(40,12);
  input(p1->name,NAME_LONG-1);
  if(strcmp(p1->name,"¨­")==0) break;
  do
  {gotoxy(40,14);
   input(input_temp,3);
   if(strcmp(input_temp,"¨­")==0) goto creat_end;
   p1->math=(int)char_int(input_temp);
   if(p1->math!=-1) break;
  }while(gotoxy(40,14),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,16);
   input(input_temp,3);
   if(strcmp(input_temp,"¨­")==0) goto creat_end;
   p1->english=(int)char_int(input_temp);
   if(p1->english!=-1) break;
  }while(gotoxy(40,16),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,18);
   input(input_temp,3);
   if(strcmp(input_temp,"¨­")==0) goto creat_end;
   p1->computer=(int)char_int(input_temp);
   if(p1->computer!=-1) break;
  }while(gotoxy(40,18),cprintf("                    \n\r"),1);
  n++;
  if(n==1)
  {head=p1;
   p1->previous=NULL;
  }
  else
  {p2->next=p1;
   p1->previous=p2;
  }
  p2=p1;
  p1=(struct student *)malloc(LEN);
  creat_input_map();
  gotoxy(40,10);
  input(p1->num,NUM_LONG-1);
 }
 creat_end:;
 if(n==0) head=NULL;
 p2->next=NULL;
}

struct student *find(struct student *temp_head,char find_char[NAME_LONG],int find_int)
{struct student *p;
 p=temp_head;
 while(p!=NULL)
 {if(strcmp(p->num,find_char)==0 || strcmp(p->name,find_char)==0 || p->math==find_int || p->english==find_int || p->computer==find_int)
  {temp_head=p;
   return temp_head;
  }
  p=p->next;
 }
 return NULL;
}

void find_all(void)
{struct student *temp;
 int i=0;
 long find_int;
 char find_char[NAME_LONG];
 char a;
 int j;
 temp=head;
 textcolor(Y);textbackground(Y);
 for(j=3;j<=5;j++)
 {gotoxy(3,j);
  cprintf("                                       ");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(2,2);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» ");
 gotoxy(2,3);cprintf(" º Text to find:                     º ");
 gotoxy(2,4);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ ");
 textcolor(WIF);textbackground(WIB);
 gotoxy(19,3);cprintf("                   ");gotoxy(19,3);
 input(find_char,NAME_LONG-1);
 if(strcmp(find_char,"¨­")==0) return;
 find_int=(int)char_int(find_char);
 textcolor(WF);textbackground(WB);
 gotoxy(1,7);
 cprintf(" No.³  Number  ³        Name        ³   Math   ³ English ³ Computer ");
 window(1,8,68,20);
 gotoxy(1,1);
 textcolor(WOF);textbackground(WOB);
 j=0;
 do
 {temp=find(temp,find_char,find_int);
  if(temp!=NULL)
  {cprintf("%-4d",i);
   cprintf("³");
   print(temp,0);
   temp=temp->next;
   i++;
   if(i%12==0) a=getch();
   if(a=='\033')
   {window(1,1,80,25);
    return;
   }
  }
 }while(temp!=NULL);
 window(1,1,80,25);
 textcolor(BF);textbackground(BB);
 if(i==0)
 {textcolor(LF);textbackground(LB);
  gotoxy(1,25);cprintf(" Search string not found ");
  getch();
 }
 else
 {textcolor(LF);textbackground(LB);
  gotoxy(1,25);cprintf(" Total %d record(s) found ",i);
  getch();
 }
}

struct student *del(struct student *temp_head)
{struct student *p;
 if(temp_head->previous==NULL)
 {p=temp_head->next;
  p->previous=NULL;
  temp_head=p;
  return temp_head;
 }
 p=temp_head->previous;
 p->next=temp_head->next;
 temp_head=p;
 return temp_head;
}

void del_all(void)
{struct student *temp;
 int i=0,j;
 long find_int;
 char find_char[NAME_LONG],a;
 temp=head;
 textcolor(Y);textbackground(Y);
 for(j=3;j<=5;j++)
 {gotoxy(3,j);
  cprintf("                                         ");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(2,2);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» ");
 gotoxy(2,3);cprintf(" º Text to delete:                     º ");
 gotoxy(2,4);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ ");
 textcolor(WIF);textbackground(WIB);
 gotoxy(21,3);cprintf("                   ");gotoxy(21,3);
 input(find_char,NAME_LONG-1);
 if(strcmp(find_char,"¨­")==0) return;
 find_int=(int)char_int(find_char);
 textcolor(WF);textbackground(WB);
 gotoxy(1,7);
 cprintf(" No.³  Number  ³        Name        ³   Math   ³ English ³ Computer ");
 window(1,8,68,20);
 gotoxy(1,1);
 j=0;
 do
 {textcolor(WOF);textbackground(WOB);
  temp=find(temp,find_char,find_int);
  if(temp!=NULL)
  {cprintf("\r%-4d",i+1);
   cprintf("³");
   print(temp,0);
   textcolor(HUANG);textbackground(WOB);
   cprintf("\rAre you sure to delete it? (Y/N)   ");
   do
   {a=getch();
    if(a=='y' || a=='Y')
    {if(temp->previous==NULL)
     {temp=del(temp);
      head=temp;
     }
     else temp=del(temp);
     cprintf("..........................Deleted");
     j++;
     n--;
     break;
    }
    else if(a=='n' || a=='N')
    {cprintf("                                 ");
     break;
    }
    else if(a=='\033')
    {window(1,1,80,25);
     return;
    }
   }while(1);
   temp=temp->next;
   i++;
  }
 }while(temp!=NULL);
 window(1,1,80,25);
 if(i==0)
 {textcolor(LF);textbackground(LB);
  gotoxy(1,25);cprintf("No record was found");
 }
 else
 {textcolor(LF);textbackground(LB);
  gotoxy(1,25);cprintf(" Total record(s) found: %d      Deleted %d record(s) ",i,j);
 }
 getch();
 return;
}

struct student *skip(struct student *p,int i)
{int step;
 step=abs(i);
 for(;step>0;step--)
 {if(i>0 && p->next!=NULL) p=p->next;
  else if(i>0 && p->next==NULL) p=p;
  else if(i<0 && p->previous!=NULL) p=p->previous;
  else if(i<0 && p->previous==NULL) p=p;
 }
 return p;
}

void add(struct student *p)
{struct student *p1,*p2;
 int i;
 char a;
 char input_temp[TEMPINPUTLONG];
 p1=(struct student *)malloc(LEN);
 p2=p1;
 textcolor(Y);textbackground(Y);
 for(i=9;i<=21;i++)
 {gotoxy(22,i);
  cprintf("                                          \n\r");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(21,8);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» \n\r");
 gotoxy(21,9);cprintf(" º                                      º \n\r");
 gotoxy(21,10);cprintf(" º Input num:                           º \n\r");
 gotoxy(21,11);cprintf(" º                                      º \n\r");
 gotoxy(21,12);cprintf(" º Input name:                          º \n\r");
 gotoxy(21,13);cprintf(" º                                      º \n\r");
 gotoxy(21,14);cprintf(" º Input math:                          º \n\r");
 gotoxy(21,15);cprintf(" º                                      º \n\r");
 gotoxy(21,16);cprintf(" º Input english:                       º \n\r");
 gotoxy(21,17);cprintf(" º                                      º \n\r");
 gotoxy(21,18);cprintf(" º Input computer:                      º \n\r");
 gotoxy(21,19);cprintf(" º                                      º \n\r");
 gotoxy(21,20);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ \n\r");
 textcolor(WIF);textbackground(WIB);
 creat_input_map();
 gotoxy(40,10);
 input(p1->num,NUM_LONG-1);
 while(strcmp(p1->num,"¨­")!=0)
 {n=n+1;
  gotoxy(40,12);
  input(p1->name,NAME_LONG-1);
  if(strcmp(p1->name,"¨­")==0) break;
  do
  {gotoxy(40,14);
   input(input_temp,3);
   if(strcmp(input_temp,"¨­")==0) goto add_end;
   p1->math=(int)char_int(input_temp);
   if(p1->math!=-1) break;
  }while(gotoxy(40,14),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,16);
   input(input_temp,3);
   if(strcmp(input_temp,"¨­")==0) goto add_end;
   p1->english=(int)char_int(input_temp);
   if(p1->english!=-1) break;
  }while(gotoxy(40,16),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,18);
   input(input_temp,3);
   if(strcmp(input_temp,"¨­")==0) goto add_end;
   p1->computer=(int)char_int(input_temp);
   if(p1->computer!=-1) break;
  }while(gotoxy(40,18),cprintf("                    \n\r"),1);
  p2=p->next;
  p1->next=p->next;
  p->next=p1;
  p1->previous=p;
  p2->previous=p1;
  p=p1;
  p1=(struct student *)malloc(LEN);
  creat_input_map();
  gotoxy(40,10);
  input(p1->num,NUM_LONG-1);
 }
 add_end:;
 textcolor(BF);textbackground(BB);
 for(i=8;i<=21;i++)
 {gotoxy(21,i);
  cprintf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°");
 }
}

void add_all(void)
{struct student *p;
 int i;
 char a1,a2;
 textcolor(LF);textbackground(LB);
 gotoxy(1,25);cprintf(" Press button A to add record ");
 textcolor(WF);textbackground(WB);
 gotoxy(1,3);
 cprintf(" No.³  Number  ³        Name        ³   Math   ³ English ³ Computer ");
 add_all_again:;
 window(1,4,68,7);
 textcolor(WOF);textbackground(WOB);
 for(i=1;i<=4;i++) cprintf("    ³          ³                    ³          ³         ³          ");
 i=1;
 cprintf("   1³");
 p=head;
 print(p,0);
 while(a1!='\033' && a2!='\033')
 {if(a1=='\141' || a2=='\141' || a1=='\101' || a2=='\101')
  {window(1,1,80,25);
   add(p);
   window(1,4,68,7);
   textcolor(WOF);textbackground(WOB);
   gotoxy(1,4);
  }
  do
  {a1=getch();
   if(a1!='\000') break;
   a2=getch();
   if(a2!='\120' || a2!='\110') break;
  }while(a1!='\000');
  if(a1=='\000' && a2=='\110' && i>1)
  {p=skip(p,-1);
   i--;
   cprintf("%4d³",i);
   print(p,0);
  }
  else if(a1=='\000' && a2=='\120' && i<n)
  {p=skip(p,1);
   i++;
   cprintf("%4d³",i);
   print(p,0);
  }
 }
 window(1,1,80,25);
}

void edit_main(void)
{char a;
 int i;
 mainkey=21;
 textcolor(Y);textbackground(Y);
 for(i=3;i<=7;i++)
 {gotoxy(10,i);
  cprintf("             ");
 }
 do
 {textcolor(MF);textbackground(MB);
  gotoxy(9,2);cprintf(" ÚÄÄÄÄÄÄÄÄÄ¿ ");
  gotoxy(9,3);cprintf(" ³Find     ³ ");
  gotoxy(9,4);cprintf(" ³Delete   ³ ");
  gotoxy(9,5);cprintf(" ³Insert   ³ ");
  gotoxy(9,6);cprintf(" ÀÄÄÄÄÄÄÄÄÄ¾ ");
  textcolor(MAF);textbackground(MAB);
  gotoxy(9,1);cprintf("Edit");
  if(mainkey==21)
  {gotoxy(11,3);cprintf("Find     ");
  }
  else if(mainkey==22)
  {gotoxy(11,4);cprintf("Delete   ");
  }
  else if(mainkey==23)
  {gotoxy(11,5);cprintf("Insert   ");
  }
  presskey();
  textcolor(MF);textbackground(MB);
  gotoxy(9,1);cprintf("Edit");
  if(mainkey==11 || mainkey==31 || mainkey==0)
  {textcolor(BF);textbackground(BB);
   for(i=2;i<=7;i++)
   {gotoxy(9,i);
    cprintf("°°°°°°°°°°°°°°");
   }
   return;
  }
 }while(mainkey!=0 && mainkey<=100);
 textcolor(BF);textbackground(BB);
 for(i=2;i<=7;i++)
 {gotoxy(9,i);
  cprintf("°°°°°°°°°°°°°°");
 }
 if(n!=0)
 {if(mainkey==121) find_all();
  else if(mainkey==122) del_all();
  else if(mainkey==123) add_all();
 }
 else if(n==0)
 {textcolor(Y);textbackground(Y);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(AF);textbackground(AB);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("  No records to edit  ");
  gotoxy(29,15);cprintf("                      ");
  getch();
 }
 mainkey=0;
 return;
}

void print_all(void)
{struct student *p;
 int i=1;
 char a;
 mainkey=31;
 do
 {textcolor(MF);textbackground(MB);
  gotoxy(15,1);cprintf("Print");
  textcolor(MAF);textbackground(MAB);
  if(mainkey==31)
  {gotoxy(15,1);cprintf("Print");
  }
  presskey();
  if(mainkey==21 || mainkey==41 || mainkey==0)
  {textcolor(MF);textbackground(MB);
   gotoxy(15,1);cprintf("Print");
   return;
  }
 }while(mainkey!=0 && mainkey<=100);
 if(n==0)
 {textcolor(Y);textbackground(Y);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(AF);textbackground(AB);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("  No record to print  ");
  gotoxy(29,15);cprintf("                      ");
  getch();
  goto print_end;
 }
 p=head;
 textcolor(WF);textbackground(WB);
 gotoxy(1,3);
 cprintf(" No.³  Number  ³        Name        ³   Math   ³ English ³ Computer ");
 window(1,4,68,20);
 textcolor(WOF);textbackground(WOB);
 do
 {if(i%17==0)
  {a=getch();
   if(a=='\033')
   {window(1,1,80,25);
    goto print_end;
   }
  }
  cprintf("%-4d",i);
  cprintf("³");
  cprintf("%-10s",p->num);
  cprintf("³");
  cprintf("%-20s",p->name);
  cprintf("³");
  cprintf("%10d",p->math);
  cprintf("³");
  cprintf("%9d",p->english);
  cprintf("³");
  cprintf("%10d",p->computer);
  p=p->next;
  i++;
 }while(p!=NULL);
 window(1,1,80,25);
 textcolor(LF);textbackground(LB);
 gotoxy(1,25);cprintf(" Your have %d record(s)",n);
 getch();
 print_end:;
 mainkey=0;
}

void save(void)
{FILE *fp;
 struct student *p;
 char filename[15];
 int i;
 if(n==0)
 {textcolor(Y);textbackground(Y);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(AF);textbackground(AB);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("  No records to save  ");
  gotoxy(29,15);cprintf("                      ");
  getch();
  return;
 }
 textcolor(Y);textbackground(Y);
 for(i=12;i<=15;i++)
 {gotoxy(29,i);
  cprintf("                    ");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(28,11);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» ");
 gotoxy(28,12);cprintf(" º Input filename º ");
 gotoxy(28,13);cprintf(" º          .MOS  º ");
 gotoxy(28,14);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ ");
 textcolor(WIF);textbackground(WIB);
 gotoxy(32,13);cprintf("        ");gotoxy(32,13);
 input(filename,8);
 if(strcmp(filename,"¨­")==0) return;
 if((fp=fopen(strcat(filename,".mos"),"wb"))==NULL)
 {printf("cannot open file\n");
  getch();
  return;
 }
 p=head;
 for(i=1;i<=n;i++)
 {if(fwrite(p,LEN,1,fp)!=0);
  p=p->next;
 }
 fclose(fp);
 textcolor(Y);textbackground(Y);
 for(i=14;i<=16;i++)
 {gotoxy(30,i);
  cprintf("                      ");
 }
 textcolor(AF);textbackground(AB);
 gotoxy(29,13);cprintf("                      ");
 gotoxy(29,14);cprintf("    File has saved    ");
 gotoxy(29,15);cprintf("                      ");
 n=0;
 head=NULL;
 getch();
 return;
}

void load(void)
{struct student *p1,*p2;
 FILE *fp;
 char filename[15];
 char a;
 int i;
 if(n!=0)
 {textcolor(Y);textbackground(Y);
  for(i=13;i<=16;i++)
  {gotoxy(29,i);
   cprintf("                        ");
  }
  textcolor(AF);textbackground(AB);
  gotoxy(28,12);cprintf("                        ");
  gotoxy(28,13);cprintf(" Current file not saved ");
  gotoxy(28,14);cprintf("   Without save? (Y/N)  ");
  gotoxy(28,15);cprintf("                        ");
  while(1)
  {a=getch();
   if(a=='y' || a=='Y') break;
   else if(a=='n' || a=='N' || a=='\033') return;
  }
 }
 textcolor(Y);textbackground(Y);
 for(i=12;i<=15;i++)
 {gotoxy(29,i);
  cprintf("                    ");
 }
 textcolor(WF);textbackground(WB);
 gotoxy(28,11);cprintf(" ÉÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ» ");
 gotoxy(28,12);cprintf(" º Input filename º ");
 gotoxy(28,13);cprintf(" º          .MOS  º ");
 gotoxy(28,14);cprintf(" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ ");
 textcolor(WIF);textbackground(WIB);
 gotoxy(32,13);cprintf  ("        ");gotoxy(32,13);
 input(filename,8);
 if(strcmp(filename,"¨­")==0) return;
 if((fp=fopen(strcat(filename,".mos"),"rb"))==NULL)
 {
 textcolor(Y);textbackground(Y);
 for(i=14;i<=16;i++)
 {gotoxy(30,i);
  cprintf("                      ");
 }
 textcolor(AF);textbackground(AB);
 gotoxy(29,13);cprintf("                      ");
 gotoxy(29,14);cprintf("   Cannot open file   ");
 gotoxy(29,15);cprintf("                      ");
 getch();
 return;
 }
 n=0;
 p1=(struct student *)malloc(LEN);
 fread(p1,LEN,1,fp);
 while(1)
 {n++;
  if(n==1)
  {head=p1;
   p1->previous=NULL;
  }
  else
  {p2->next=p1;
   p1->previous=p2;
  }
  p2=p1;
  p1=(struct student *)malloc(LEN);
  if(fread(p1,LEN,1,fp)!=1)
  {if(feof(fp))
   {p2->next=NULL;
    textcolor(Y);textbackground(Y);
    for(i=14;i<=16;i++)
    {gotoxy(30,i);
    cprintf("                      ");
    }
    textcolor(AF);textbackground(AB);
    gotoxy(29,13);cprintf("                      ");
    gotoxy(29,14);cprintf("    File has read     ");
    gotoxy(29,15);cprintf("                      ");
    getch();
    fclose(fp);
    return;
   }
   else
   {textcolor(Y);textbackground(Y);
    for(i=14;i<=16;i++)
    {gotoxy(30,i);
     cprintf("                      ");
    }
    textcolor(AF);textbackground(AB);
    gotoxy(29,13);cprintf("                      ");
    gotoxy(29,14);cprintf("   File read error    ");
    gotoxy(29,15);cprintf("                      ");
    getch();
    fclose(fp);
    head=NULL;
    return;
   }
  }
 }
}

void file_main(void)
{char a;
 int i;
 mainkey=11;
 textcolor(Y);textbackground(Y);
 for(i=3;i<=7;i++)
 {gotoxy(4,i);
  cprintf("             ");
 }
 do
 {textcolor(MF);textbackground(MB);
  gotoxy(3,2);cprintf(" ÚÄÄÄÄÄÄÄÄÄ¿ ");
  gotoxy(3,3);cprintf(" ³New      ³ ");
  gotoxy(3,4);cprintf(" ³Open     ³ ");
  gotoxy(3,5);cprintf(" ³Save     ³ ");
  gotoxy(3,6);cprintf(" ÀÄÄÄÄÄÄÄÄÄ¾ ");
  textcolor(MAF);textbackground(MAB);
  gotoxy(3,1);cprintf("File");
  if(mainkey==11)
  {gotoxy(5,3);cprintf("New      ");
  }
  else if(mainkey==12)
  {gotoxy(5,4);cprintf("Open     ");
  }
  else if(mainkey==13)
  {gotoxy(5,5);cprintf("Save     ");
  }
  presskey();
  textcolor(MF);textbackground(MB);
  gotoxy(3,1);cprintf("File");
  if(mainkey==21 || mainkey==51 || mainkey==0)
  {textcolor(BF);textbackground(BB);
   for(i=2;i<=7;i++)
   {gotoxy(3,i);
    cprintf("°°°°°°°°°°°°°°");
   }
   return;
  }
 }while(mainkey!=0 && mainkey<=100);
 textcolor(BF);textbackground(BB);
 for(i=2;i<=7;i++)
 {gotoxy(3,i);
  cprintf("°°°°°°°°°°°°°°");
 }
 if(mainkey==111)
 {if(n==0)
  {creat();
   mainkey=0;
  }
  else
  {textcolor(Y);textbackground(Y);
   for(i=13;i<=16;i++)
   {gotoxy(29,i);
    cprintf("                        ");
   }
   textcolor(AF);textbackground(AB);
   gotoxy(28,12);cprintf("                        ");
   gotoxy(28,13);cprintf(" Current file not saved ");
   gotoxy(28,14);cprintf("   Without save? (Y/N)  ");
   gotoxy(28,15);cprintf("                        ");
   while(1)
   {a=getch();
    if(a=='y' || a=='Y')
    {creat();
     mainkey=0;
     break;
    }
    else if(a=='n' || a=='N' || a=='\033') break;
   }
   mainkey=0;
  }
 }
 else if(mainkey==112)
 {load();
  mainkey=0;
 }
 else if(mainkey==113)
 {save();
  mainkey=0;
 }
 return;
}

void help(void)
{char a;
 int i;
 mainkey=51;
 textcolor(Y);textbackground(Y);
 for(i=3;i<=7;i++)
 {gotoxy(66,i);
  cprintf("             ");
 }
 do
 {textcolor(MF);textbackground(MB);
  gotoxy(65,2);cprintf(" ÚÄÄÄÄÄÄÄÄÄ¿ ");
  gotoxy(65,3);cprintf(" ³Contents ³ ");
  gotoxy(65,4);cprintf(" ÃÄÄÄÄÄÄÄÄÄ´ ");
  gotoxy(65,5);cprintf(" ³About    ³ ");
  gotoxy(65,6);cprintf(" ÀÄÄÄÄÄÄÄÄÄ¾ ");
  textcolor(MAF);textbackground(MAB);
  gotoxy(75,1);cprintf("Help");
  if(mainkey==51)
  {gotoxy(67,3);cprintf("Contents ");
  }
  else if(mainkey==52)
  {gotoxy(67,5);cprintf("About    ");
  }
  presskey();
  textcolor(MF);textbackground(MB);
  gotoxy(75,1);cprintf("Help");
  if(mainkey==11 || mainkey==41 || mainkey==0)
  {textcolor(BF);textbackground(BB);
   for(i=2;i<=7;i++)
   {gotoxy(65,i);
    cprintf("°°°°°°°°°°°°°°");
   }
   return;
  }
 }while(mainkey!=0 && mainkey<=100);
 textcolor(BF);textbackground(BB);
 for(i=2;i<=7;i++)
 {gotoxy(65,i);
  cprintf("°°°°°°°°°°°°°°");
 }
 if(mainkey==152) start_program();
 else if(mainkey==151)
 {textcolor(Y);textbackground(Y);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(AF);textbackground(AB);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("       Nothing        ");
  gotoxy(29,15);cprintf("                      ");
  getch();
 }
 mainkey=0;
}

void main()
{char a;
 int i;
 textcolor(Y);textbackground(Y);
 clrscr();
 start_program();
 clrscr();
 do
 {clrscr();
  background_program();
  draw_menubackground();
  do
  {a=getch();
   if(a=='\033')
   {a='\000';
    mainkey=11;
    break;
   }
  }while(1);
  do
  {if(mainkey==11) file_main();
   else if(mainkey==21) edit_main();
   else if(mainkey==31) print_all();
   else if(mainkey==41)
   {textcolor(MAF);textbackground(MAB);
    gotoxy(22,1);cprintf("Quit");
    presskey();
    if(mainkey==141)
    {if(n!=0 && head!=NULL)
     {textcolor(Y);textbackground(Y);
      for(i=13;i<=16;i++)
      {gotoxy(29,i);
       cprintf("                        ");
      }
      textcolor(AF);textbackground(AB);
      gotoxy(28,12);cprintf("                        ");
      gotoxy(28,13);cprintf(" Current file not saved ");
      gotoxy(28,14);cprintf("   Without save? (Y/N)  ");
      gotoxy(28,15);cprintf("                        ");
      while(1)
      {a=getch();
       if(a=='y' || a=='Y')
       {a='q';
	mainkey=0;
	break;
       }
       else if(a=='n' || a=='N' || a=='\033')
       {mainkey=0;
	break;
       }
      }
     }
     else if(n==0 && head==NULL)
     {a='q';
      mainkey=0;
     }
    }
    textcolor(MF);textbackground(MB);
    gotoxy(22,1);cprintf("Quit");
   }
   else if(mainkey==51) help();
  }while(mainkey!=0);
 }while(a!='q');
 end_program();
}