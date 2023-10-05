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
STU *mainhead=NULL;
int *yesno;
/* Draw background*/
background(BUT *pt)
    {
      setcolor(pt->drawcolor);
      rectangle(pt->xo,pt->yo,pt->maxx-pt->xo,pt->maxy-pt->yo);
      setfillstyle(pt->fillstyle,pt->fillcolor);
      bar(pt->xo+1,pt->yo+1,pt->maxx-pt->xo-1,pt->maxy-pt->yo-1);



    }

/* Draw all buttons */
drawbutton(BUT *pic,char ptr[][LEN],int number)
    { int i;
      setfillstyle(pic->fillstyle,pic->fillcolor);
      setcolor(pic->drawcolor);
      for (i=0;i<number;i++)
	    {
		rectangle(pic->x1,pic->y1+i*pic->dy,pic->x1+pic->dx,pic->y1+(i+1)*pic->dy);
		bar(pic->x1+1,pic->y1+1+i*pic->dy,pic->x1+pic->dx-1,pic->y1+(i+1)*pic->dy-1);
	    }
      for (i=0;i<number;i++)
	     {
	       outtextxy(pic->x1+(pic->dx-strlen(ptr[i])*7)/2,pic->y1+pic->dy/2+i*pic->dy-3,ptr[i]);
	       outtextxy(pic->x1+(pic->dx-strlen(ptr[i])*7)/2,pic->y1+pic->dy/2+i*pic->dy+6,"-");

	     }
     }

/* Draw one button */
activebutton(BUT *pic,char ptr[][LEN],int n)
      {   setcolor(pic->drawcolor);
	  setfillstyle(pic->fillstyle,pic->fillcolor);
	  bar(pic->x1+1,pic->y1+n*pic->dy+1,pic->x1+pic->dx-1,pic->y1+n*pic->dy+pic->dy-1);
	  outtextxy(pic->x1+(pic->dx-strlen(ptr[n])*7)/2,pic->y1+pic->dy/2+n*pic->dy-3,ptr[n]);
	  outtextxy(pic->x1+(pic->dx-strlen(ptr[n])*7)/2,pic->y1+pic->dy/2+n*pic->dy+2,"_");
      }

/*show input infomation */
show()
      {
	gotoxy (5,5);printf("Number:");
	gotoxy (5,6);printf("Name:");
	gotoxy (5,7);printf("Chinese score:");
	gotoxy (5,8);printf("English score:");
	gotoxy (5,9);printf("Computer score:");
	gotoxy (5,10);printf("Math score:");
      }


/* Input student's infomation */
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


/* Another function to create file */
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


/* Put the data into a file */
save( STU * head)
	    {    char c;
		 char fname[15];
		 STU *info;
		 FILE *fp;

		 printf("\nPlease input filename:");
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
		      printf("\n%ld\n",info->num);getch();
		      info=info->next; }
		      printf("press any key when continue");getch();
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


/* Load data from file */
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


/* List all student's infomation */
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


/* Count student's number */
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
append()
	{
	  char fname[20];
	  FILE *fp;
	  STU temp;
	  printf("input file name:>");
	  scanf("%s",fname);
	  fp=fopen(fname,"ab");
	  show();
	  input(&temp);
	  fwrite (&temp,LE,1,fp);
	  fclose(fp);
	}

/* Modidy student infomation */
modify(STU *head,long number)
	{  STU *info;
	   info=find(head,number);
	   clrscr();
	   show();
	   input(info);
	   printf("modify ok");
	   getch();
	}

/* Function of first button */
fuc0()
      {

	STU *head;
	restorecrtmode();
	head=creat1();

	clear(head);
	setgraphmode(2);
	cleardevice();
       }




/* Function of second button */
/*fuc1(){ char fname[20];
	  STU *head;
	  cleardevice();
	  printf("input file name:>");
	  scanf("%s",fname);
	  head=load(fname);
	  list(head);
	  cleardevice();


       }*/
/*fuc1(){ char fname[20];
	long number;
	STU *head,*info;
	cleardevice();
	printf("input file name:>");
	scanf("%s",fname);
	head=load(fname);
	printf("input a student number:>");
	scanf("%ld",&number);
	info=find(head,number);
	printf("\nThe student is %ld %s %d %d %d %d\n",TEXT(info));
	getch();
       }*/
/*fuc1(){
	 char fname[20];
	 int low,high,result;
	 STU *head;
	 cleardevice();
	 printf("input file name:>");
	 scanf("%s",fname);
	 head=load(fname);
	 printf("input fan wei(a,b):>");
	 scanf("%d,%d",&low,&high);
	 result=personnumber(head,low,high);
	 printf("\nThere are %d students' score in this wide\n",result);
	 getch();
      }*/

fuc1()
      {  char button[3][LEN]={"all","one","subject"};
	 BUT picture={20,20,50,150,0,0,0,0,BLUE,WHITE,1};
	 int key,n=0;

	 picture.maxx=getmaxx();
	 picture.maxy=getmaxy();
	 picture.x1=(picture.maxx-picture.dx)/2+20;
	 picture.y1=(picture.maxy-picture.dy*NUM)/2+20;

	 drawbutton(&picture,button,3);
	 do{
	     picture.fillstyle=6;
	     picture.fillcolor=GREEN;
	     activebutton(&picture,button,n);
	     key=getch();
	     switch(key)
		      {
			  case 72:  n--;
				    { picture.fillstyle=1;
				      picture.fillcolor=BLUE;
				      activebutton(&picture,button,n+1);
				      break;}

			  case 80:  n++;
				    {  picture.fillstyle=1;
				       picture.fillcolor=BLUE;
				       activebutton(&picture,button,n-1);
				       break;}

		      }
		 if(n>3-1) n=0;
		 if(n<0)   n=3-1;
	     }while(key!=13&&key!=27);





      }



/* Function of third button */
/*fuc2(){
	char *fname[20];
	printf("file name:>");
	scanf("%s",fname);
	mainhead=load(fname);
	sortby(mainhead,1);
	list(mainhead);
	getch();
	setgraphmode(2);
	cleardevice();

       }*/
fuc2(){
	long number;
	char fname[20];
	STU *info;
	printf("file name:>");
	scanf("%s",fname);
	mainhead=load(fname);
	printf("number:>");
	scanf("%ld",&number);
	info=find(mainhead,number);
	printf("%ld  %s  %d  %d  %d  %d",info->num,info->name,info->chinese,info->english,info->computer,info->math);
	getch();
       }
/* Function of forth button */
/*fuc3(){
       int classnumber,result;
       char fname[20];
       STU *info;
       cleardevice();
       printf("file name:>");
       scanf("%s",fname);
       mainhead=load(fname);
       printf("input subject number:>");
       scanf("%d",&classnumber);
       result=subjectaverage(mainhead,classnumber);
       printf("The average score is:%d",result);
       getch();

       } */
/*fuc3(){ long number;
	char fname[20];
	STU *info;
	restorecrtmode();
	printf("file name:>");
	scanf("%s",fname);
	mainhead=load(fname);
	printf("number:>");
	scanf("%ld",&number);
	info=find(mainhead,number);
	modify(mainhead,number);
	setgraphmode(2);
	list(mainhead);getch();
	save(mainhead);

	}*/
/*fuc3(){ long number;
	char fname[20];
	STU *info;
	restorecrtmode();
	printf("file name:>");
	scanf("%s",fname);
	mainhead=load(fname);
	printf("input delete number:>");
	scanf("%ld",&number);
	setgraphmode(2);
	info=find(mainhead,number);
	delete(mainhead,number);
	save(mainhead);
	printf("delete ok");
	getch();
     } */

fuc3(){ long number;
	char fname[20];
	STU *info;
	restorecrtmode();

	append();

	setgraphmode(2);


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
	int key;
	char button[NUM][LEN]={"Creat","Inquire","Statistics","Modify","Exit"};
	BUT picture={20,20,50,150,0,0,0,0};

/* Set the graphic mode */
	int driver,mode;
	driver=VGA;
	mode=2;
	initgraph(&driver,&mode,"f:\\tc\\");


	picture.maxx=getmaxx();picture.maxy=getmaxy();
	picture.x1=(picture.maxx-picture.dx)/2;picture.y1=(picture.maxy-picture.dy*NUM)/2;

    do{
	picture.fillcolor=BLUE;
	picture.drawcolor=WHITE;
	picture.fillstyle=6;

	  background(&picture);                /* Draw background */

	  picture.fillcolor=BLUE;
	  picture.fillstyle=1;
	  drawbutton(&picture,button,NUM);          /* Draw allthebuttons */

	       do{


		picture.fillstyle=6;
		picture.fillcolor=BROWN;
		activebutton(&picture,button,n);

		key=getch();         /* Get a key from keyboard */

		switch(key)
		      {
			  case 72:  n--;
				    { picture.fillstyle=1;
				      picture.fillcolor=BLUE;
				      activebutton(&picture,button,n+1);
				      break;}

			  case 80:  n++;
				    {  picture.fillstyle=1;
				       picture.fillcolor=BLUE;
				       activebutton(&picture,button,n-1);
				       break;}

		      }

		switch(key)
		      {
			  case 'C':
			  case 'c':  key=13;n=0;break;
			  case 'I':
			  case 'i':  key=13;n=1;break;
			  case 'S':
			  case 's':  key=13;n=2;break;

			  case 'm':  key=13;n=3;break;
			  case 'E':
			  case 'e':  key=13;n=4;break;
		       }
	    if(n>NUM-1) n=0;
	    if(n<0)   n=NUM-1;

       }while (key!=13);           /* Exit the loop */

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