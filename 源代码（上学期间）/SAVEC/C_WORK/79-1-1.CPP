#include<stdio.h>           //Pratice P79 1.1
#include<conio.h>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define LEN sizeof(LNode)
#define MAN_ITEM 2

typedef int ElemType;
typedef int Status;
typedef struct LNode
{ElemType school;
 ElemType item;
 ElemType num;
 char name[20];
 ElemType result;
 struct LNode *next;
};
typedef LNode *LinkList;

int school_num=0;

Status Input_list(LinkList L,char file_name[])
{FILE *fp;
 LinkList p;
 if((fp=fopen(file_name,"r"))==NULL)
 {cprintf("Cannot open this file\n");
  fclose(fp);
  return ERROR;
 }
 fscanf(fp,"%d\n",&school_num);
 printf("%d\n",school_num);
 p=(LinkList)malloc(LEN);
 L->next=p;
 do
 {
  fscanf(fp,"%d,%d,%d,%s\n",&p->school,&p->item,&p->num,p->name);
  printf("%d,%d,%d,%s\n",p->school,p->item,p->num,p->name);
  if(feof(fp)!=NULL) break;
  p->next=(LinkList)malloc(LEN);
  p=p->next;
 }while(1);
 p->next=NULL;
 fclose(fp);
 return OK;
}

int num_result(int item,int num)
{int result=0;
 if(item%2==1)
  switch(num)
  {case 1:result=7;break;
   case 2:result=5;break;
   case 3:result=3;break;
   case 4:result=2;break;
   case 5:result=1;break;
   default:break;
  }
 else
  switch(num)
  {case 1:result=5;break;
   case 2:result=3;break;
   case 3:result=2;break;
   default:break;
  }
 return result;
}

void make_result(LinkList L)
{LinkList p;
 p=L->next;
 while(p!=NULL)
 {p->result=num_result(p->item,p->num);
  p=p->next;
 }
}

void print_personal_result(LinkList L)
{LinkList p;
 int find;
 clrscr();
 do
 {gotoxy(1,1);cprintf("Input the school number: ");
  scanf("%d",&find);
 }while(find<=0||find>school_num);
 p=L->next;
 printf("\n");
 while(p!=NULL)
 {if(find==p->school)
   printf("%d,%d,%d,%s,%d\n",p->school,p->item,p->num,p->name,p->result);
  p=p->next;
 }
 getch();
}

void print_school_result(LinkList L)
{LinkList p;
 int find,man=0,woman=0;
 for(find=1;find<=school_num;find++)
 {p=L->next;
  while(p!=NULL)
  {if(find==p->school)
   {if(p->item<=MAN_ITEM) man+=p->result;
    else woman+=p->result;
   }
   p=p->next;
  }
  printf("School: %d\n",find);
  printf("Man   : %d\n",man);
  printf("Woman : %d\n",woman);
  printf("All   : %d\n",man+woman);
  printf("\n");
  man=0;woman=0;
 }
 getch();
}

void main(void)
{LinkList L,p;
 char key;
 char file_name[12];
 clrscr();
 gotoxy(20,11);cprintf("Input filename: ");
 scanf("%s",file_name);
 if(Input_list(L,file_name)==ERROR) exit(0);
 make_result(L);
 while(1)
 {clrscr();
  gotoxy(20,10);cprintf("1. Print Personal Result\n");
  gotoxy(20,11);cprintf("2. Print School Result\n");
  gotoxy(20,12);cprintf("0. Exit\n");
  key=getch();
  clrscr();
  if(key=='1') print_personal_result(L);
  else if(key=='2') print_school_result(L);
  else if(key=='0') break;
 }
}

