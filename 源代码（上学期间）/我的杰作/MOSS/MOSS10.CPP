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

int n=0;



void start_program(void)
{int colorf0=7,colorf1=14,colorb0=0,colorb1=1;
 int i;
 textcolor(colorf0);textbackground(colorb0);
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(16,10);cprintf(" ษอออออออออออออออออออออออออออออออออออออออออออป \n\r");
 gotoxy(16,11);cprintf(" บ   Management-system of Students' Status   บ \n\r");
 gotoxy(16,12);cprintf(" บ                Version 1.0                บ \n\r");
 gotoxy(16,13);cprintf(" บ      Copyright (c) 2000 by LiJia,CNU.     บ \n\r");
 gotoxy(16,14);cprintf(" ศอออออออออออออออออออออออออออออออออออออออออออผ \n\r");
 textcolor(colorf0);textbackground(colorb0);
 getch();
}

void background_program(void)
{int i;
 int colorf0=7,colorf1=14,colorb0=0,colorb1=1;
 textcolor(colorf1);textbackground(colorb1);
 clrscr();
 for(i=1;i<=23;i++) cprintf("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐ\r");
 textcolor(colorf0);textbackground(colorb0);
}

void draw_menubackground(void)
{char a,b;
 int colorf0=7,colorb0=0,colormf=7,colormb=6,coloref=7,coloreb=1;
 textcolor(colormf);textbackground(colormb);
 gotoxy(1,1);
 cprintf("  File  Edit  Print  Exit                                                 Help  ");
 gotoxy(1,24);
 textcolor(coloref);textbackground(coloreb);
 cprintf(" Comment: ESC->Exit                                                            ");
 textcolor(colorf0);textbackground(colorb0);
}

void end_program(void)
{int i;
 int colorf0=7,colorf1=14,colorb0=0,colorb1=1;
 clrscr();
 textcolor(colorf1);textbackground(colorb1);
 for(i=1;i<=4;i++) cprintf("                                                                              \n\r");
 cprintf("ษออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออป\n\r");
 cprintf("บ                                                                            บ\n\r");
 cprintf("บ  ÜÜÜÜÜÜÜÜÜ  Û                       Û                                      บ\n\r");
 cprintf("บ  ฿฿฿฿Û฿฿฿฿  Û                       Û                                      บ\n\r");
 cprintf("บ      Û      Û                       Û                                      บ\n\r");
 cprintf("บ      Û      ÛÜ฿฿Ü    ฿฿฿Ü   ÛÜ฿฿Ü   Û   Ü฿         Û    Û   Ü฿฿Ü   Û    Û  บ\n\r");
 cprintf("บ      Û      Û    Û       Û  Û    Û  Û Ü฿           Û    Û  Û    Û  Û    Û  บ\n\r");
 cprintf("บ      Û      Û    Û   Ü฿฿ÜÛ  Û    Û  ÛÛ             Û    Û  Û    Û  Û    Û  บ\n\r");
 cprintf("บ      Û      Û    Û  Û    Û  Û    Û  Û ฿Ü           Û    Û  Û    Û  Û    Û  บ\n\r");
 cprintf("บ      Û      Û    Û   ฿ÜÜ฿Û  Û    Û  Û   ฿Ü          ฿ÜÜ฿Û   ฿ÜÜ฿    ฿ÜÜ฿Û  บ\n\r");
 cprintf("บ                                                        Ü฿                  บ\n\r");
 cprintf("บ                                                    ÜÜÜ฿                    บ\n\r");
 cprintf("บ                                                                            บ\n\r");
 cprintf("ศออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออผ\n\r");
 for(i=1;i<=5;i++) cprintf("                                                                              \n\r");
 textcolor(colorf0);textbackground(colorb0);
 cprintf("\n\r");
}




struct student
{struct student *previous;
 char num[NUM_LONG];
 char name[NAME_LONG];
 int math,english,computer;
 struct student *next;
};

void input(char inputchar[],int tempinputlong)
{int i=0;
 char a;
 a=getche();
 while(a!='\r' && a!='\033')
 {inputchar[i]=a;
  a=getch();
  i++;
  if(i>=tempinputlong) break;
  printf("%c",a);
 }
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
  cprintf("ณ");
  cprintf("%-20s",p->name);
  cprintf("ณ");
  cprintf("%10d",p->math);
  cprintf("ณ");
  cprintf("%9d",p->english);
  cprintf("ณ");
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


struct student *creat(void)
{int colorf0=7,colorf1=14,colorf2=10,colorb0=0,colorb1=1,colorb2=3;
 struct student *head;
 struct student *p1,*p2;
 int i;
 char a;
 char input_temp[TEMPINPUTLONG];
 n=0;
 p1=(struct student *)malloc(LEN);
 p2=p1;
 textcolor(colorf0);textbackground(colorb0);
 for(i=9;i<=21;i++)
 {gotoxy(22,i);
  cprintf("                                          \n\r");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(21,8);cprintf(" ษออออออออออออออออออออออออออออออออออออออป \n\r");
 gotoxy(21,9);cprintf(" บ                                      บ \n\r");
 gotoxy(21,10);cprintf(" บ Input num:                           บ \n\r");
 gotoxy(21,11);cprintf(" บ                                      บ \n\r");
 gotoxy(21,12);cprintf(" บ Input name:                          บ \n\r");
 gotoxy(21,13);cprintf(" บ                                      บ \n\r");
 gotoxy(21,14);cprintf(" บ Input math:                          บ \n\r");
 gotoxy(21,15);cprintf(" บ                                      บ \n\r");
 gotoxy(21,16);cprintf(" บ Input english:                       บ \n\r");
 gotoxy(21,17);cprintf(" บ                                      บ \n\r");
 gotoxy(21,18);cprintf(" บ Input computer:                      บ \n\r");
 gotoxy(21,19);cprintf(" บ                                      บ \n\r");
 gotoxy(21,20);cprintf(" ศออออออออออออออออออออออออออออออออออออออผ \n\r");
 textcolor(colorf2);textbackground(colorb2);
 creat_input_map();
 gotoxy(40,10);
 input(p1->num,NUM_LONG-1);
 head=NULL;
 while(strcmp(p1->num,"จญ")!=0)
 {gotoxy(40,12);
  input(p1->name,NAME_LONG-1);
  if(strcmp(p1->name,"จญ")==0) break;
  do
  {gotoxy(40,14);
   input(input_temp,3);
   if(strcmp(input_temp,"จญ")==0) goto creat_end;
   p1->math=(int)char_int(input_temp);
   if(p1->math!=-1) break;
  }while(gotoxy(40,14),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,16);
   input(input_temp,3);
   if(strcmp(input_temp,"จญ")==0) goto creat_end;
   p1->english=(int)char_int(input_temp);
   if(p1->english!=-1) break;
  }while(gotoxy(40,16),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,18);
   input(input_temp,3);
   if(strcmp(input_temp,"จญ")==0) goto creat_end;
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
 return(head);
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

void find_all(struct student *head)
{struct student *temp;
 int i=0;
 long find_int;
 char find_char[NAME_LONG];
 int colorf0=7,colorf1=14,colorf2=10,colorb0=0,colorb1=1,colorb2=3;
 int j;
 temp=head;
 textcolor(colorf0);textbackground(colorb0);
 for(j=3;j<=5;j++)
 {gotoxy(3,j);
  cprintf("                                       ");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(2,2);cprintf(" ษอออออออออออออออออออออออออออออออออออป ");
 gotoxy(2,3);cprintf(" บ Text to find:                     บ ");
 gotoxy(2,4);cprintf(" ศอออออออออออออออออออออออออออออออออออผ ");
 textcolor(colorf2);textbackground(colorb2);
 gotoxy(19,3);cprintf("                   ");gotoxy(19,3);
 input(find_char,NAME_LONG-1);
 if(strcmp(find_char,"จญ")==0) return;
 find_int=(int)char_int(find_char);
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(1,7);
 cprintf(" No.ณ  Number  ณ        Name        ณ   Math   ณ English ณ Computer ");
 window(1,8,68,20);
 gotoxy(1,1);
 textcolor(colorf2);textbackground(colorb2);
 j=0;
 do
 {temp=find(temp,find_char,find_int);
  if(temp!=NULL)
  {cprintf("%-4d",i);
   cprintf("ณ");
   print(temp,0);
   temp=temp->next;
   i++;
   if(i%12==0) getch();
  }
 }while(temp!=NULL);
 window(1,1,80,25);
 textcolor(colorf1);textbackground(colorb1);
 if(i==0)
 {gotoxy(5,7);cprintf(" Search string not found ");
  getch();
 }
 else
 {gotoxy(3,22);cprintf(" Total %d record(s) found ",i);
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

struct student *del_all(struct student *head)
{struct student *temp;
 int i=0,j;
 long find_int;
 char find_char[NAME_LONG],a;
 int colorf0=7,colorf1=14,colorf2=10,colorb0=0,colorb1=1,colorb2=3;
 temp=head;
 textcolor(colorf0);textbackground(colorb0);
 for(j=3;j<=5;j++)
 {gotoxy(3,j);
  cprintf("                                         ");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(2,2);cprintf(" ษอออออออออออออออออออออออออออออออออออออป ");
 gotoxy(2,3);cprintf(" บ Text to delete:                     บ ");
 gotoxy(2,4);cprintf(" ศอออออออออออออออออออออออออออออออออออออผ ");
 textcolor(colorf2);textbackground(colorb2);
 gotoxy(21,3);cprintf("                   ");gotoxy(21,3);
 input(find_char,NAME_LONG-1);
 if(strcmp(find_char,"จญ")==0) return head;
 find_int=(int)char_int(find_char);
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(1,7);
 cprintf(" No.ณ  Number  ณ        Name        ณ   Math   ณ English ณ Computer ");
 window(1,8,68,20);
 gotoxy(1,1);
 j=0;
 do
 {textcolor(colorf2);textbackground(colorb2);
  temp=find(temp,find_char,find_int);
  if(temp!=NULL)
  {cprintf("\r%-4d",i+1);
   cprintf("ณ");
   print(temp,0);
   textcolor(colorf1);textbackground(colorb2);
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
     return head;
    }
   }while(1);
   temp=temp->next;
   i++;
  }
 }while(temp!=NULL);
 window(1,1,80,25);
 if(i==0)
 {gotoxy(3,22);
  cprintf("No record was found");
 }
 else
 {gotoxy(3,22);cprintf(" Total record(s) found: %d     ",i);
  gotoxy(3,53);cprintf("Deleted %d record(s) ",j);
 }
 getch();
 return head;
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
 int colorf0=7,colorf1=14,colorf2=10,colorb0=0,colorb1=1,colorb2=3;
 int i;
 char a;
 char input_temp[TEMPINPUTLONG];
 p1=(struct student *)malloc(LEN);
 p2=p1;
 textcolor(colorf0);textbackground(colorb0);
 for(i=9;i<=21;i++)
 {gotoxy(22,i);
  cprintf("                                          \n\r");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(21,8);cprintf(" ษออออออออออออออออออออออออออออออออออออออป \n\r");
 gotoxy(21,9);cprintf(" บ                                      บ \n\r");
 gotoxy(21,10);cprintf(" บ Input num:                           บ \n\r");
 gotoxy(21,11);cprintf(" บ                                      บ \n\r");
 gotoxy(21,12);cprintf(" บ Input name:                          บ \n\r");
 gotoxy(21,13);cprintf(" บ                                      บ \n\r");
 gotoxy(21,14);cprintf(" บ Input math:                          บ \n\r");
 gotoxy(21,15);cprintf(" บ                                      บ \n\r");
 gotoxy(21,16);cprintf(" บ Input english:                       บ \n\r");
 gotoxy(21,17);cprintf(" บ                                      บ \n\r");
 gotoxy(21,18);cprintf(" บ Input computer:                      บ \n\r");
 gotoxy(21,19);cprintf(" บ                                      บ \n\r");
 gotoxy(21,20);cprintf(" ศออออออออออออออออออออออออออออออออออออออผ \n\r");
 textcolor(colorf2);textbackground(colorb2);
 creat_input_map();
 gotoxy(40,10);
 input(p1->num,NUM_LONG-1);
 while(strcmp(p1->num,"จญ")!=0)
 {n=n+1;
  gotoxy(40,12);
  input(p1->name,NAME_LONG-1);
  if(strcmp(p1->name,"จญ")==0) break;
  do
  {gotoxy(40,14);
   input(input_temp,3);
   if(strcmp(input_temp,"จญ")==0) goto add_end;
   p1->math=(int)char_int(input_temp);
   if(p1->math!=-1) break;
  }while(gotoxy(40,14),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,16);
   input(input_temp,3);
   if(strcmp(input_temp,"จญ")==0) goto add_end;
   p1->english=(int)char_int(input_temp);
   if(p1->english!=-1) break;
  }while(gotoxy(40,16),cprintf("                    \n\r"),1);
  do
  {gotoxy(40,18);
   input(input_temp,3);
   if(strcmp(input_temp,"จญ")==0) goto add_end;
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
 textcolor(colorf1);textbackground(colorb1);
 for(i=8;i<=21;i++)
 {gotoxy(21,i);
  cprintf("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐฐ");
 }
}

void add_all(struct student *p)
{int i;
 char a1,a2;
 struct student *head;
 int colorf0=7,colorf1=14,colorf2=10,colorb0=0,colorb1=1,colorb2=3;
 head=p;
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(1,3);
 cprintf(" No.ณ  Number  ณ        Name        ณ   Math   ณ English ณ Computer ");
 add_all_again:;
 window(1,4,68,7);
 textcolor(colorf2);textbackground(colorb2);
 for(i=1;i<=4;i++) cprintf("    ณ          ณ                    ณ          ณ         ณ          ");
 i=1;
 cprintf("   1ณ");
 print(p,0);
 while(a1!='\033' && a2!='\033')
 {if(a1=='\141' || a2=='\141')
  {window(1,1,80,25);
   add(p);
   window(1,4,68,7);
   textcolor(colorf2);textbackground(colorb2);
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
   cprintf("%4dณ",i);
   print(p,0);
  }
  else if(a1=='\000' && a2=='\120' && i<n)
  {p=skip(p,1);
   i++;
   cprintf("%4dณ",i);
   print(p,0);
  }
 }
 window(1,1,80,25);
}

struct student *edit_main(struct student *head)
{char a;
 int colorf0=7,colorf1=7,colorf2=14,colorf3=14,colorb0=0,colorb1=6,colorb2=1,colorb3=4;
 int i;
 if(n==0)
 {textcolor(colorf0);textbackground(colorb0);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(colorf3);textbackground(colorb3);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("  No records to edit  ");
  gotoxy(29,15);cprintf("                      ");
  getch();
 }
 else
 {textcolor(colorf0);textbackground(colorb0);
  for(i=3;i<=7;i++)
  {gotoxy(10,i);
   cprintf("             ");
  }
  textcolor(colorf1);textbackground(colorb1);
  gotoxy(9,2);cprintf(" ฺฤฤฤฤฤฤฤฤฤฟ ");
  gotoxy(9,3);cprintf(" ณFind     ณ ");
  gotoxy(9,4);cprintf(" ณDelete   ณ ");
  gotoxy(9,5);cprintf(" ณInsert   ณ ");
  gotoxy(9,6);cprintf(" ภฤฤฤฤฤฤฤฤฤพ ");
  a=getch();
  textcolor(colorf2);textbackground(colorb2);
  for(i=2;i<=7;i++)
  {gotoxy(9,i);
   cprintf("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐ");
  }
  if(a=='f') find_all(head);
  else if(a=='d') head=del_all(head);
  else if(a=='i') add_all(head);
 }
 return head;
}

void print_all(struct student *head)
{struct student *p;
 int colorf0=7,colorf1=14,colorf2=10,colorb0=0,colorb1=1,colorb2=3;
 int i=1;
 if(n==0) goto print_end;
 p=head;
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(1,3);
 cprintf(" No.ณ  Number  ณ        Name        ณ   Math   ณ English ณ Computer ");
 window(1,4,68,20);
 textcolor(colorf2);textbackground(colorb2);
 do
 {if(i%17==0)
  {getch();
  }
  cprintf("%-4d",i);
  cprintf("ณ");
  cprintf("%-10s",p->num);
  cprintf("ณ");
  cprintf("%-20s",p->name);
  cprintf("ณ");
  cprintf("%10d",p->math);
  cprintf("ณ");
  cprintf("%9d",p->english);
  cprintf("ณ");
  cprintf("%10d",p->computer);
  p=p->next;
  i++;
 }while(p!=NULL);
 printf("\n\nYour have %d record(s)\n",n);
 getch();
 window(1,1,80,25);
 print_end:;
}

void save(struct student *head)
{FILE *fp;
 struct student *p;
 char filename[15];
 int colorf0=7,colorf1=14,colorf2=10,colorf3=14,colorb0=0,colorb1=4,colorb2=3,colorb3=1;
 int i;
 if(n==0)
 {textcolor(colorf0);textbackground(colorb0);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(colorf1);textbackground(colorb1);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("  No records to save  ");
  gotoxy(29,15);cprintf("                      ");
  getch();
  return;
 }
 textcolor(colorf0);textbackground(colorb0);
 for(i=12;i<=15;i++)
 {gotoxy(29,i);
  cprintf("                    ");
 }
 textcolor(colorf3);textbackground(colorb3);
 gotoxy(28,11);cprintf(" ษออออออออออออออออป ");
 gotoxy(28,12);cprintf(" บ Input filename บ ");
 gotoxy(28,13);cprintf(" บ          .MOS  บ ");
 gotoxy(28,14);cprintf(" ศออออออออออออออออผ ");
 textcolor(colorf2);textbackground(colorb2);
 gotoxy(32,13);cprintf("        ");gotoxy(32,13);
 input(filename,8);
 if(strcmp(filename,"จญ")==0) return;
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
 textcolor(colorf0);textbackground(colorb0);
 for(i=14;i<=16;i++)
 {gotoxy(30,i);
  cprintf("                      ");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(29,13);cprintf("                      ");
 gotoxy(29,14);cprintf("    File has saved    ");
 gotoxy(29,15);cprintf("                      ");
 getch();
 return;
}

struct student *load(struct student *head)
{struct student *p1,*p2;
 FILE *fp;
 char filename[15];
 char a;
 int i;
 int colorf0=7,colorf1=14,colorf2=10,colorf3=14,colorb0=0,colorb1=1,colorb2=3,colorb3=4;
 if(n!=0)
 {textcolor(colorf0);textbackground(colorb0);
  for(i=13;i<=16;i++)
  {gotoxy(29,i);
   cprintf("                        ");
  }
  textcolor(colorf3);textbackground(colorb3);
  gotoxy(28,12);cprintf("                        ");
  gotoxy(28,13);cprintf(" Current file not saved ");
  gotoxy(28,14);cprintf("   Without save? (Y/N)  ");
  gotoxy(28,15);cprintf("                        ");
  while(1)
  {a=getch();
   if(a=='y' || a=='Y') break;
   else if(a=='n' || a=='N' || a=='\033') return head;
  }
 }
 textcolor(colorf0);textbackground(colorb0);
 for(i=12;i<=15;i++)
 {gotoxy(29,i);
  cprintf("                    ");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(28,11);cprintf(" ษออออออออออออออออป ");
 gotoxy(28,12);cprintf(" บ Input filename บ ");
 gotoxy(28,13);cprintf(" บ          .MOS  บ ");
 gotoxy(28,14);cprintf(" ศออออออออออออออออผ ");
 textcolor(colorf2);textbackground(colorb2);
 gotoxy(32,13);cprintf  ("        ");gotoxy(32,13);
 input(filename,8);
 if(strcmp(filename,"จญ")==0) return head;
 if((fp=fopen(strcat(filename,".mos"),"rb"))==NULL)
 {
 textcolor(colorf0);textbackground(colorb0);
 for(i=14;i<=16;i++)
 {gotoxy(30,i);
  cprintf("                      ");
 }
 textcolor(colorf3);textbackground(colorb3);
 gotoxy(29,13);cprintf("                      ");
 gotoxy(29,14);cprintf("   Cannot open file   ");
 gotoxy(29,15);cprintf("                      ");
 getch();
  return head;
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
    textcolor(colorf0);textbackground(colorb0);
    for(i=14;i<=16;i++)
    {gotoxy(30,i);
    cprintf("                      ");
    }
    textcolor(colorf3);textbackground(colorb3);
    gotoxy(29,13);cprintf("                      ");
    gotoxy(29,14);cprintf("    File has read     ");
    gotoxy(29,15);cprintf("                      ");
    getch();
    fclose(fp);
    return head;
   }
   else
   {textcolor(colorf0);textbackground(colorb0);
    for(i=14;i<=16;i++)
    {gotoxy(30,i);
     cprintf("                      ");
    }
    textcolor(colorf3);textbackground(colorb3);
    gotoxy(29,13);cprintf("                      ");
    gotoxy(29,14);cprintf("   File read error    ");
    gotoxy(29,15);cprintf("                      ");
    getch();
    fclose(fp);
    return NULL;
   }
  }
 }
}

struct student *file_main(struct student *head)
{char a;
 int i;
 int colorf0=7,colorf1=7,colorf2=14,colorf3=14,colorb0=0,colorb1=6,colorb2=1,colorb3=4;
 textcolor(colorf0);textbackground(colorb0);
 for(i=3;i<=7;i++)
 {gotoxy(4,i);
  cprintf("             ");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(3,2);cprintf(" ฺฤฤฤฤฤฤฤฤฤฟ ");
 gotoxy(3,3);cprintf(" ณNew      ณ ");
 gotoxy(3,4);cprintf(" ณOpen     ณ ");
 gotoxy(3,5);cprintf(" ณSave     ณ ");
 gotoxy(3,6);cprintf(" ภฤฤฤฤฤฤฤฤฤพ ");
 a=getch();
 textcolor(colorf2);textbackground(colorb2);
 for(i=2;i<=7;i++)
 {gotoxy(3,i);
  cprintf("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐ");
 }
 if(a=='n')
 {if(n==0) head=creat();
  else
  {textcolor(colorf0);textbackground(colorb0);
   for(i=13;i<=16;i++)
   {gotoxy(29,i);
    cprintf("                        ");
   }
   textcolor(colorf3);textbackground(colorb3);
   gotoxy(28,12);cprintf("                        ");
   gotoxy(28,13);cprintf(" Current file not saved ");
   gotoxy(28,14);cprintf("   Without save? (Y/N)  ");
   gotoxy(28,15);cprintf("                        ");
   while(1)
   {a=getch();
    if(a=='y' || a=='Y')
    {head=creat();
     break;
    }
    else if(a=='n' || a=='N' || a=='\033') break;
   }
  }
 }
 else if(a=='s') save(head);
 else if(a=='o') head=load(head);
 return head;
}

void help(void)
{char a;
 int i;
 int colorf0=7,colorf1=7,colorf2=14,colorf3=14,colorb0=0,colorb1=6,colorb2=1,colorb3=4;
 textcolor(colorf0);textbackground(colorb0);
 for(i=3;i<=7;i++)
 {gotoxy(66,i);
  cprintf("             ");
 }
 textcolor(colorf1);textbackground(colorb1);
 gotoxy(65,2);cprintf(" ฺฤฤฤฤฤฤฤฤฤฟ ");
 gotoxy(65,3);cprintf(" ณContents ณ ");
 gotoxy(65,4);cprintf(" รฤฤฤฤฤฤฤฤฤด ");
 gotoxy(65,5);cprintf(" ณAbout    ณ ");
 gotoxy(65,6);cprintf(" ภฤฤฤฤฤฤฤฤฤพ ");
 a=getch();
 textcolor(colorf2);textbackground(colorb2);
 for(i=2;i<=7;i++)
 {gotoxy(65,i);
  cprintf("ฐฐฐฐฐฐฐฐฐฐฐฐฐฐ");
 }
 if(a=='a') start_program();
 if(a=='c')
 {textcolor(colorf0);textbackground(colorb0);
  for(i=14;i<=16;i++)
  {gotoxy(30,i);
   cprintf("                      ");
  }
  textcolor(colorf3);textbackground(colorb3);
  gotoxy(29,13);cprintf("                      ");
  gotoxy(29,14);cprintf("       Nothing        ");
  gotoxy(29,15);cprintf("                      ");
  getch();
 }
}

void main()
{struct student *head=NULL;
 char a;
 int i;
 int colorf0=7,colorf3=14,colorb0=0,colorb3=4;
 clrscr();
 start_program();
 clrscr();
 do
 {clrscr();
  background_program();
  draw_menubackground();
  a=getch();
  if(a=='f') head=file_main(head);
   else if(a=='e') head=edit_main(head);
   else if(a=='p')
   {if(n==0)
    {textcolor(colorf0);textbackground(colorb0);
     for(i=14;i<=16;i++)
     {gotoxy(30,i);
      cprintf("                      ");
     }
     textcolor(colorf3);textbackground(colorb3);
     gotoxy(29,13);cprintf("                      ");
     gotoxy(29,14);cprintf("  No record to print  ");
     gotoxy(29,15);cprintf("                      ");
     getch();
    }
    else print_all(head);
   }
   else if(a=='h') help();
  }while(a!='\033');
  end_program();
}