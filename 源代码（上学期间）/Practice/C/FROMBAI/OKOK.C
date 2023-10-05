#include<dos.h>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#define NUM 5
#define LEN 15
struct student{
    long num;
    char name[20];
    int chinese,english,computer,math;
    struct student *next;
      };
#define NULL 0
#define TEXT(x) x->num,x->name,x->chinese,x->english,x->computer,x->math
#define LE sizeof(struct student)
#define STU struct student
STU *mainhead=NULL;
/* These are window's option */
   int xo=20,yo=20,dy=50,dx=150,x1,y1,maxx,maxy;

/* Draw background*/
background()
    {
      setcolor(WHITE);
      rectangle(xo,yo,maxx-xo,maxy-yo);
      setfillstyle(6,BLUE);
      bar(xo+1,yo+1,maxx-xo-1,maxy-yo-1);



    }

/* Draw all buttons */
drawbutton(char ptr[][LEN])
    { int i;
      setfillstyle(1,GREEN);
      for (i=0;i<=NUM-1;i++)
	    {
		rectangle(x1,y1+i*dy,x1+dx,y1+i*dy+dy);
		floodfill(x1+1,y1+i*dy+1,WHITE);
	    }
      for (i=0;i<=NUM-1;i++)
	     {
	       outtextxy(x1+(dx-strlen(ptr[i])*7)/2,y1+dy/2+i*dy-3,ptr[i]);
	       outtextxy(x1+(dx-strlen(ptr[i])*7)/2,y1+dy/2+i*dy+6,"-");

	     }
     }

/* Draw one button */
activebutton(char ptr[][LEN],int n)
      {
	  bar(x1+1,y1+n*dy+1,x1+dx-1,y1+n*dy+dy-1);
	  outtextxy(x1+(dx-strlen(ptr[n])*7)/2,y1+dy/2+n*dy-3,ptr[n]);
	  outtextxy(x1+(dx-strlen(ptr[n])*7)/2,y1+dy/2+n*dy+2,"_");
      }

/* Input a key from keyboard */
get_key()
      {
	  union REGS r;
	  r.h.ah=0;
	  return (int86(0x16,&r,&r));
      }

show()
      { clrscr();
	gotoxy (5,5);printf("Number:");
	gotoxy (5,6);printf("Name:");
	gotoxy (5,7);printf("Chinese score:");
	gotoxy (5,8);printf("English score:");
	gotoxy (5,9);printf("Computer score:");
	gotoxy (5,10);printf("Math score:");
      }

input(STU *ptr)
      {
	gotoxy (5+7,5);scanf("%ld",&ptr->num);
	if (ptr->num==0) return;
	gotoxy (5+5,6);scanf("%s",ptr->name);

	gotoxy (5+14,7);scanf("%d",&ptr->chinese);
	gotoxy (5+14,8);scanf("%d",&ptr->english);
	gotoxy (5+15,9);scanf("%d",&ptr->computer);
	gotoxy (5+11,10);scanf("%d",&ptr->math);
      }


STU *find(STU *head,long number)
      {   STU *p,*old;
	  p=head;
	  while(p)
	      {
		 if(number==p->num) return p;
		 p=p->next;
	      }
	  printf("Student no found !\n");
	  return (NULL);
      }

STU *creat1()
     {   char fname[20];
	 STU *info;
	 FILE *fp;
	 printf("filename:>");
	 scanf("%s",fname);
	 if ((fp=fopen(fname,"wb"))==NULL)
	       { printf("can not open file\m");
		 exit(0);}
	 info=(STU *)malloc(LE);
	 clrscr();
	 show();
	 input(info);
	 do {  fwrite(info,LE,1,fp);
	       show();
	       input(info);

	    }while (info->num!=0);
	    free(info);fclose(fp);}



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
		 show();
		 input(p1);
		 p2->next=NULL;
	     }
		 free(p1);
		 return (head);


     }

save( STU * head)
	    {    char c;
		 char fname[15];
		 STU *info;
		 FILE *fp;

		 printf("\nPlease input filename:");
		 scanf("%s",fname);
		 if ((fp=fopen(fname,"w"))==NULL)
		      {  printf("can not open file \n");
			 return;
		      }
		 printf("\n saving file.");
		 info=head;
		 while (info)
		      {
		      fwrite(info,LE,1,fp);
		      printf("%ld",info->num);getch();
		      info=info->next; }
		 printf("%ld",info->num);getch();
		 fclose(fp);
	   }
clear(STU *head)
	 {   STU *info;
	     info=head;
	     while (info)
		{  free(info);
		   info=info->next;
		}
	 }

STU *load ( char *fname)
  {  STU *info,*head=NULL,*temp;
     FILE *fp;
     fp=fopen(fname,"rb");
     printf("\nloading file \n");
     head=(STU *)malloc(LE);
     info=head;
     while(!feof(fp)){
	      fread(info,LE,1,fp);

	      if(feof(fp)) break;
	      temp=info;
	      printf("%ld,%s,%d,%d,%d,%d\n",TEXT(info));
	      getch();
	      info->next=(STU *)malloc(LE);

	      info=info->next;
	      }

	      temp->next=NULL;

	      fclose(fp);
	      free(info);
	      return head;
	 }
list(STU *head)
	{   STU *ptr;
	    cleardevice();
	    printf("Number\tName\tChinese\tEnglish\tComputer\tMath\n");
	    ptr=head;
	       do
	       { printf("%ld     %s     %d     %d     %d     %d\n",TEXT(ptr));

		 ptr=ptr->next;
	       }while(ptr!=NULL);


	}

int sum(STU *head)
	{   STU *info;
	    int n=0;
	    info=head;
	    while (info!=NULL)
		{  n++;
		   info=info->next;
		}
	    printf("in sum function n is %d\n",n);
	    return n;
	}

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

sortby(STU *head,int subject)
	{   int n;
	    int i,j;
	    STU *info,*temp;
	    info=head;
	    temp=info->next;
	    n=sum(info);
	    printf("sum is %d\n",n);getch();
	    for (i=2;i<=n;i++){
		for (j=2;j<=n;j++)
		    {  switch (subject)
			  {  case 0: /*printf ("now swaping\n");getch();*/
				     if ((info->num)>(temp->num)) swap(info,temp);printf("swap ok\n");break;
			     case 1: if (info->chinese>temp->chinese) swap(info,temp);break;
			     case 2: if (info->english>temp->english) swap(info,temp);break;
			     case 3: if (info->computer>temp->computer) swap(info,temp);break;
			     case 4: if (info->math>temp->math) swap(info,temp);break;
			   }
			info=temp;
			temp=temp->next;
		    }
		 printf("11111\n");
		 getch();
		 info=head;
		 temp=head->next;
		 }

	}






/* Function of first button */
fuc0()
      { STU *head;
	restorecrtmode();
	head=creat1();

	clear(head);
	setgraphmode(2);
	cleardevice();
       }




/* Function of second button */
fuc1(){ char fname[20];
	STU *head;
	cleardevice();
	printf("input file name:>");
	scanf("%s",fname);
	head=load(fname);
	list(head);
	cleardevice();


       }

/* Function of third button */
fuc2(){
	char *fname[20];
	printf("file name:>");
	scanf("%s",fname);
	mainhead=load(fname);
	sortby(mainhead,0);
	list(mainhead);
	getch();
	setgraphmode(2);
	cleardevice();

       }

/* Function of forth button */
fuc3(){
       background();




       }

/* Exit the system */
fuc4(){
       cleardevice();
       closegraph();
       exit(0);

      }


main()
      {
	int i,n=0;
	char button[NUM][LEN]={"Creat","Inquire","Statistics","Modify","Exit"};
	union scan
	      {
		int c;
		char ch[2];
	      } sc;

     /* Set the graphic mode */
	int driver,mode;

	driver=VGA;
	mode=2;
	initgraph(&driver,&mode,"c:\\tc\\");

	maxx=getmaxx();maxy=getmaxy();
	x1=(maxx-dx)/2;y1=(maxy-dy*NUM)/2;

       do{
	  background();                /* Draw background */

	  drawbutton(button);          /* Draw allthebuttons */



	   do{
		setfillstyle(9,GREEN);
		activebutton(button,n);

		sc.c=get_key();         /* Get a key from keyboard */

		switch(sc.ch[1])
		      {
			  case 72:  n--;
				    { setfillstyle(1,GREEN);
				      activebutton(button,n+1);
				      break;}

			  case 80:  n++;
				    {  setfillstyle(1,GREEN);
				       activebutton(button,n-1);
				       break;}

		      }
		switch(sc.ch[0])
		      {
			  case 'C':
			  case 'c':  sc.ch[0]=13;n=0;break;
			  case 'I':
			  case 'i':  sc.ch[0]=13;n=1;break;
			  case 'S':
			  case 's':  sc.ch[0]=13;n=2;break;
			  case 'M':
			  case 'm':  sc.ch[0]=13;n=3;break;
			  case 'E':
			  case 'e':  sc.ch[0]=13;n=4;break;
		       }
	    if(n>NUM-1) n=0;
	    if(n<0)   n=NUM-1;

       }while (sc.ch[0]!=13);           /* Exit the loop */

    switch(n){
	      case 0: fuc0();break;
	      case 1: fuc1();break;
	      case 2: fuc2();break;
	      case 3: fuc3();break;
	      case 4: fuc4();break;
	     }

       }while(1);




    }


