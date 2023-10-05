#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<graphics.h>
#include<string.h>
#define ESC  27
#define RETURN 13
#define U_ARRO 72
#define D_ARRO 80
#define L_ARRO 75
#define R_ARRO 77
#define NUM 5
#define LEN 15
#define MAX 20
struct  student{
   long num;
   char  name[MAX];

   int chinese;
   int english;
   int computer;
   int math;
   struct student *next;
 };
struct button
	{  int xo;
	   int yo;
	   int dy;
	   int dx;
	   int x1;
	   int y1;
	   int maxx,maxy;
	   int fillcolor;
	   int drawcolor;
	   int fillstyle;
	} ;



#define NULL 0
#define TEXT(x) x->num,x->name,x->chinese,x->english,x->computer,x->math
#define LE sizeof(struct student)
#define STU struct student
#define BUT struct button
#define YES 1
#define NO 0


STU *mainhead=NULL;
int fileopen=NO;
char *m[]={
   "File",
   "Inquire",
   "Modify",
   "Numertion"};
char *f1[]={
     "new",
     "load",
     "exit"};
char *f2[]={

     "all",
     "one",
     "subject",
     };
char *f3[]={
     "add",
     "modify",
     "delete"};
char *f4[]={
     "allaver",
     "oneaver",
     "num"};
int key,key1,key2,key3,key4;
int pos1=0,pos2=0,pos3=0,pos4=0,pos5=0;






void win(){
    int r;
    window(1,1,80,25);
    clrscr();
    textbackground(CYAN);
    mainlist();
    for(r=0;r<1;r++)
    printf("\n");}

background(BUT *pt)
    {
      setcolor(pt->drawcolor);
      rectangle(pt->xo,pt->yo,pt->maxx-pt->xo,pt->maxy-pt->yo);
      setfillstyle(pt->fillstyle,pt->fillcolor);
      bar(pt->xo+1,pt->yo+1,pt->maxx-pt->xo-1,pt->maxy-pt->yo-1);



    }

showform(){  BUT pt={100,100,50,150,0,0,640,480,BLUE,WHITE,1};
	     setcolor(pt.drawcolor);
	     rectangle(pt.xo,pt.yo+40,pt.maxx-pt.xo,pt.maxy-pt.yo);
	     setfillstyle(pt.fillstyle,pt.fillcolor);
	     bar(pt.xo+1,pt.yo+1+40,pt.maxx-pt.xo-1,pt.maxy-pt.yo-1);
	     setviewport(pt.xo+1,pt.yo+1+40,pt.maxx-pt.xo-1,pt.maxy-pt.yo-1+40,1);

	     moveto (20,23);outtext("Number:");
	     moveto (20,54);outtext("Name:");
	     moveto (20,86);outtext("Chinese score:");
	     moveto (20,120);outtext("English score:");
	     moveto (20,150);outtext("Computer score:");
	     moveto (20,182);outtext("Math score:");


	  }

openfile(){
	  STU *load();
	  char fname[20];

	  printf("input file name:>");
	  scanf("%s",fname);
	  mainhead=load(fname);

	  fileopen=YES;
	  }

/*input student's infomation */
input(STU *ptr)
      {
	gotoxy (16+7,11);window(23,11,40,11);clrscr();scanf("%ld",&ptr->num);
	if (ptr->num==0) return;
	gotoxy (16+5,13);window(21,13,40,13);clrscr();scanf("%s",ptr->name);

	gotoxy (16+14,15);window(30,15,40,15);clrscr();scanf("%d",&ptr->chinese);
	gotoxy (16+14,17);window(30,17,40,17);clrscr();scanf("%d",&ptr->english);
	gotoxy (16+15,19);window(31,19,40,19);clrscr();scanf("%d",&ptr->computer);

	gotoxy (16+11,21);window(27,21,40,21);clrscr();scanf("%d",&ptr->math);
	      }


/* Find the student by number */
STU *find(STU *head,long number)
      {   STU *p;
	  p=head;
	  while(p)
	      {

		 if(p->num==number) return(p);
		 p=p->next;
	      }
	  printf("Student no found !\n");
	  return (NULL);
      }



/* Creat a file */

/*STU *creat1()
     {   char fname[20];
	 STU *info;
	 FILE *fp;
	 printf("input file name:>");
	 scanf("%s",fname);

	 if ((fp=fopen(fname,"wb"))==NULL)
	       { printf("can not open file\m");
		 exit(0);}
	 info=(STU *)malloc(LE);


	 input(info);
	 do {  cleardevice();

	       fwrite(info,LE,1,fp);

	       input(info);

	    }while (info->num!=0);
	    free(info);fclose(fp);
	    }   */


/* Another function to create file */
/*
STU *creat()
   {  int n;
      STU *head;
      STU *p1,*p2;
      n=0;
      p1=p2=(STU *)malloc(LE);
      show();
      input(p1);
      head=NULL;
      while(p1->num!=0)
	    {    n=n+1;
		 if (n==1) head=p1;
		 else p2->next=p1;
		 p2=p1;
		 p1=(STU *)malloc(LE);

		 input(p1);
		 p2->next=NULL;
	     }
		 free(p1);
		 return (head);


     }
	*/

/* Put the data into a file */
save( STU * head)
	    {    char c;
		 char fname[15];
		 STU *info;
		 FILE *fp;

		 printf("input file name:");
		 scanf("%s",fname);
		 if ((fp=fopen(fname,"wb"))==NULL)
		      {  printf("can not open file \n");
			 return;
		      }
		 printf("\n saving file.\n");
		 info=head;
		 while (info)
		      {
		      fwrite(info,LE,1,fp);
		      info=info->next; }
		      printf("save ok");
		      fclose(fp);
		 }

/* Clear the useless memory */

clear(STU *head)
	 {   STU *info;
	     info=head;
	     while (info)
		{  free(info);
		   info=info->next;
		}
	 }


show(){}
/* Load data from file */
STU *load ( char *fname)
  {  STU *info,*head=NULL,*temp;
     FILE *fp;
     fp=fopen(fname,"rb");

     head=(STU *)malloc(LE);
     info=head;
     while(!feof(fp)){
	      fread(info,LE,1,fp);

	      if(feof(fp)) break;
	      temp=info;
	      info->next=(STU *)malloc(LE);

	      info=info->next;
	      }

	      temp->next=NULL;

	      fclose(fp);
	      free(info);
	      return head;
	 }


/* List all student's infomation */
list(STU *head)
	{   STU *ptr;
	    cleardevice();
	    gotoxy(1,1);
	    printf("Number\tName\tChinese\tEnglish\tCompu\tMath\n");
	    ptr=head;
	       do
	       { printf("%ld\t%s\t%d\t%d\t%d\t%d\n",TEXT(ptr));



		 ptr=ptr->next;
	       }while(ptr!=NULL);


	}


/* Count student's number */
int sum(STU *head)
	{   STU *info;
	    int n=0;
	    info=head;
	    while (info!=NULL)
		{  n++;
		   info=info->next;
		}

	    return n;
	}


/* swap the two struction */
swap (STU *a,STU *b)
       {  int i;
	  STU *temp;
	  temp=(STU *)malloc(LE);

	  /*printf("a=%ld,%s,%d,%d,%d,%d\n",a->num,a->name,a->chinese,a->english,a->computer,a->math);
	  printf("b=%ld,%s,%d,%d,%d,%d\n",TEXT(b)); */
	  temp->num=a->num;
	  for(i=0;i<20;i++) temp->name[i]=a->name[i];
	  temp->chinese=a->chinese;
	  temp->english=a->english;
	  temp->computer=a->computer;
	  temp->math=a->math;


	       a->num=b->num;
	       for (i=0;i<20;i++) a->name[i]=b->name[i];
	       a->chinese=b->chinese;
	       a->english=b->english;
	       a->computer=b->computer;
	       a->math=b->math;



		     b->num=temp->num;
		     for (i=0;i<20;i++) b->name[i]=temp->name[i];
		     b->chinese=temp->chinese;
		     b->english=temp->english;
		     b->computer=temp->computer;
		     b->math=temp->math;

	  free(temp);

	  }


/* sort all the infomation */
sortby(STU *head,int subject)
	{   int n;
	    int i,j;
	    STU *info,*temp;
	    info=head;
	    temp=info->next;
	    n=sum(info);
	    for (i=2;i<=n;i++){
		for (j=2;j<=n;j++)
		    {  switch (subject)
			  {  case 0: /*printf ("now swaping\n");getch();*/
				     if ((info->num)>(temp->num)) swap(info,temp);break;
			     case 1: if (info->chinese>temp->chinese) swap(info,temp);break;
			     case 2: if (info->english>temp->english) swap(info,temp);break;
			     case 3: if (info->computer>temp->computer) swap(info,temp);break;
			     case 4: if (info->math>temp->math) swap(info,temp);break;
			   }
			info=temp;
			temp=temp->next;
		    }
		 info=head;
		 temp=head->next;
		 }

	}


/* get class average score */
int classaverage(STU *head,int class)
	{   STU *info;
	    long sum=0;
	    int classnum,score,n=0;
	    info=head;
	    while(info!=NULL)
		{  classnum=(info->num)%1000/100;
		   if (classnum==class) { score=info->chinese+info->english+info->computer+info->math;
					  sum=sum+score;
					  n++;}
		   info=info->next;
		}
	    if (n==0) printf( "Did not find %d class\n",class);
	    return(sum/n);
	}



/* get each subject score */
int subjectaverage(STU *head,int subject)
	{   STU *info;
	    int sum=0,n=0;
	    info=head;
	    while(info!=NULL)
		{ switch (subject)
		     { case 0:  sum=sum+info->chinese;n++;break;
		       case 1:  sum=sum+info->english;n++;break;
		       case 2:  sum=sum+info->computer;n++;break;
		       case 3:  sum=sum+info->math;n++;break;
		      }
		  info=info->next;
		}
	    return (sum/n);
	}


/* get the number of person */
int personnumber(STU *head,int low,int high)
	{   STU *info;
	    int sum=0;
	    int n=0;
	    info=head;
	    while (info!=NULL)
		{  sum=info->chinese+info->english+info->computer+info->math;
		   /*printf("\nchinese %d,english %d,computer %d,math %d\n",TEXT(info));
		   printf("\nThe sum is %d\n%d,%d\n",sum,low,high);getch();*/
		   if (sum>=low && sum<=high) n++;
		   info=info->next;
		}
	    return n;
	}

/* delete a student infomation */
delete(STU *head,long number)
      {  STU *p1,*p2;
	 p1=head;
	 while (number!=p1->num&&p1->next!=NULL)
	      { p2=p1;p1=p1->next;}
	 if (number==p1->num)
	      {
		 if (p1==head) {head=p1->next;free (p1);}
		 else {p2->next=p1->next;free(p1);}
	      }
	 else printf("%ld not been found!\n",number);
      }


/* add one student infomation on the file */
append(STU *head)
	{
	  STU *temp;
	  STU *info;
	  temp=(STU *)malloc(LE);
	  temp->next=NULL;

	  showform();
	  input(temp);
	  info=head;
	  while(info!=NULL){info=info->next;}
	  info->next=temp;

	}

/* Modidy student infomation */
modify1(STU *head,long number)
	{  STU *info;
	   info=find(head,number);
	   showform();
	   input(info);
	   printf("modify ok");
	   getch();
	}

/* Function of first button */
new()
      {
	BUT picture={20,20,50,150,0,0,640,480,BLUE,WHITE,6};
	char fname[20];

	 STU *info;
	 FILE *fp;

	 background(&picture);
	 printf("input file name:>");
	 scanf("%s",fname);
	 cleardevice();
	 background(&picture);

	 showform();
	/*input(mainhead);*/



	if ((fp=fopen(fname,"wb"))==NULL)
	       { printf("can not open file\m");
		 exit(0);}
	 info=(STU *)malloc(LE);


	 input(info);
	 do {  setviewport(0,0,639,479,0);
	       cleardevice();
	       background(&picture);
	       showform();
	       fwrite(info,LE,1,fp);

	       input(info);

	    }while (info->num!=0);
	    free(info);fclose(fp);





      }




all(){ /*BUT picture={20,20,50,150,0,0,0,0,BLUE,WHITE,6};
	 BUT picture1={30,60,50,150,0,0,639,479,BLACK,WHITE,1};
	 int i;
	 setviewport(0,0,639,479,0);
	 window(10,10,20,15);
	 gotoxy(1,1);
	 for(i=1;i<=1000;i++) {getch();printf("%d\n",i);}
	 sortby(mainhead,0);
	 list(mainhead);
	 background(&picture1);*/
	 sortby(mainhead,0);
	 list(mainhead);

	 getch();
	}
one(){
	 long number;
	 STU *info;
	 cleardevice();

	 printf("input a student number:>");
	 scanf("%ld",&number);
	 info=find(mainhead,number);
	 printf("\nThe student's number:%ld name:%s chinese:%d english:%d computer:%d maths:%d\n",TEXT(info));
	 getch();

}
subject(){  int n;
	  cleardevice();
	  printf("Sort by what?(1 chinese,2 english,3 computer,4 maths):>");
	  scanf("%d",&n);
	  sortby(mainhead,n);
	  list(mainhead);
	  getch();


}



allaver(){   int classnumber,result;

	   STU *info;
	   cleardevice();


	   printf("input class number:>");
	   scanf("%d",&classnumber);
	   result=classaverage(mainhead,classnumber);
	   printf("The average score is:%d",result);
	   getch();

}
subaver(){ int subnumber,result;

	 STU *info;
	 cleardevice();


	 printf("input subject number(1 chinese,2 english,3 computer 4,maths:>");
	 scanf("%d",&subnumber);
	 result=subjectaverage(mainhead,subnumber);
	 printf("The average score is:%d",result);
	 getch();

	}
num(){
	 int low,high,result;

	 cleardevice();

	 printf("input fan wei(a,b):>");
	 scanf("%d,%d",&low,&high);
	 result=personnumber(mainhead,low,high);
	 printf("\nThere are %d students' score in this wide\n",result);
	 getch();
	}




modify1(){
        long number;
	STU *info;
	printf("input student number:>");
	scanf("%ld",&number);
	info=find(mainhead,number);
	modify(mainhead,number);
	getch();
	list(mainhead);getch();
	save(mainhead);

       }
delete1(){long number;
	STU *info;
	printf("input delete number:>");
	scanf("%ld",&number);
	delete(mainhead,number);
	save(mainhead);
	printf("delete ok");


       }
add(){



	 append(mainhead);
	 save(mainhead);


}





mainlist()
{
 int i;
 clrscr();
 window(1,2,80,2);
 textbackground(BROWN);
 clrscr();
 for(i=0;i<4;i++)
 {if(i==pos1)
   textcolor(BLACK);
  else textcolor(YELLOW);
  cprintf("%s       ",m[i]);
 }
}
filelist1()
{
 int i;
 while(1){
 while((key1!=RETURN)&&(key1!=ESC)){
  window(1,3,5,6);
 textbackground(BROWN);
 clrscr();
 gotoxy(1,1);
 for (i=0;i<3;i++)
   {
      if(i==pos2) textcolor(YELLOW);
      else  textcolor(BLACK);
      cprintf("%s",f1[i]);
      gotoxy(1,2+i);
   }
 key1=getch();
   if(key1==U_ARRO)keysel2(0);
   else
       if(key1==D_ARRO)keysel2(1);
   for(i=0;i<12;i++)
       printf("\n");
   }

 if(key1==ESC){
      window(1,1,80,25);
      clrscr();
      textbackground(CYAN);
      mainlist();
      key=0;
      key1=0;
      return;
      }
 switch(pos2)
     {
      case 0:new();break;
      case 1:save(mainhead);break;
      case 2:exit(0);
      }
      key1=ESC;}
      }
filelist2()
{
 int i;
 while(2){
 while((key2!=RETURN)&&(key2!=ESC))
{ window(11,3,19,6);
 textbackground(BROWN);
 clrscr();
 gotoxy(1,1);
 for(i=0;i<3;i++)
 {
  if(i==pos3) textcolor(YELLOW);
     else textcolor(BLACK);
  cprintf("%s",f2[i]);
  gotoxy(1,2+i);}
 key2=getch();
 if(key2==U_ARRO)keysel3(0);
 else if(key2==D_ARRO)keysel3(1);
 for(i=0;i<12;i++)
 printf("\n");}
 if(key2==ESC){
  window(1,1,80,25);
  clrscr();
  textbackground(CYAN);
  mainlist();
  key=0;
  key2=0;
 return;}
 switch(pos3)
 {  case 0:all();break;
   case 1:one();break;
   case 2:subject();break;

  }
  key2=ESC;}
 }

filelist3()
{
 int i;
 while(3){
 while((key3!=RETURN)&&(key3!=ESC))
{ window(24,3,30,5);
 textbackground(BROWN);
 clrscr();
 gotoxy(1,1);
 for(i=0;i<3;i++)
 {
  if(i==pos4) textcolor(YELLOW);
   else textcolor(BLACK);
  cprintf("%s",f3[i]);
  gotoxy(1,2+i);
  }
  key3=getch();
  if(key==U_ARRO)keysel4(0);
  else if(key3==D_ARRO)keysel4(1);
  for(i=0;i<12;i++)
  printf("\n");}
  if(key3==ESC){
   window(1,1,80,25);
   clrscr();
   textbackground(CYAN);
   mainlist();
   key=0;
   key3=0;
   return;}
 switch(pos4)
 {case 0:add();break;
  case 1:modidy1();break;
  case 2:delete1();break;
 }
 key3=ESC;}
 }
filelist4()
{
 int i;
 while(4)
{ while((key4!=RETURN)&&(key4!=ESC))
{ window(37,3,43,6);
 textbackground(BROWN);
 clrscr();
 gotoxy(1,1);
 for(i=0;i<3;i++)
 {
  if(i==pos5) textcolor(YELLOW);
   else textcolor(BLACK);
  cprintf("%s",f4[i]);
  gotoxy(1,2+i);
 }
 key4=getch();
 if(key4==U_ARRO) keysel5(0);
  else if(key4==D_ARRO) keysel5(1);
 for(i=0;i<12;i++)
 printf("\n");}
 if(key4==ESC){
   window(1,1,80,25);
   clrscr();
   textbackground(CYAN);
   mainlist();
   key=0;
   key4=0;
   return;}
switch(pos5)
{ case 0:allaver();break;
  case 1:oneaver();break;
  case 2:num();break;
 }
 key4=ESC;}
}

keysel1(k)
int k;
{
  if(k)pos1=(pos1==3)?0:++pos1;
  else pos1=(pos1==0)?3:--pos1;
  }
keysel2(k)
 int k;
{  if(k)pos2=(pos2==2)?0:++pos2;
  else pos2=(pos2==0)?2:--pos2;
 }
keysel3(k)
 int k;
{ if(k)pos3=(pos3==2)?0:++pos3;
 else pos3=(pos3==0)?2:--pos3;
}
keysel4(k)
 int k;
{ if(k)pos4=(pos4==2)?0:++pos4;
  else pos4=(pos4==0)?2:--pos4;
}
keysel5(k)
 int k;
{ if(k)pos5=(pos5==2)?0:++pos5;
 else pos5=(pos5==0)?2:--pos5;
}
main(){
int i;


textbackground(CYAN);
clrscr();
while(1){

while((key!=RETURN)&&(key!=ESC))
{
 mainlist();
 key=getch();
 if(key==L_ARRO) keysel1(0);
 else if(key==R_ARRO) keysel1(1);

}
if (key==ESC) exit(0);
 switch(pos1)
 {
  case 0:filelist1();break;
  case 1:filelist2();break;
  case 2:filelist3();break;
  case 3:filelist4();break;
 }

 }

}




