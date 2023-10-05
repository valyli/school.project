#include<dos.h>
#include<stdio.h>
#include<graphics.h>
#include<string.h>
#define NUM 6
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
#define YES 1
#define NO 0
STU *mainhead=NULL;
int fileopen=NO,filesave=YES;


cline(){gotoxy(1,1);
	   printf("                                                               ");
	   gotoxy(1,1);}

/* Draw background*/
background(BUT *pt)
    {
      setcolor(pt->drawcolor);
      rectangle(pt->xo,pt->yo,pt->maxx-pt->xo,pt->maxy-pt->yo);
      setfillstyle(pt->fillstyle,pt->fillcolor);
      bar(pt->xo+1,pt->yo+1,pt->maxx-pt->xo-1,pt->maxy-pt->yo-1);
      outtextxy(80,100,"STUDENT SYSTEM");
      outtextxy(80,120,"Made by Bai Guang");
      outtextxy(140,160,"2000,3,9");
      gotoxy(53,3);printf(" Press F1 to Get Help !");

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
showform(){  BUT pt={100,100,50,150,0,0,640,480,BLUE,YELLOW,2};
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
	  window(1,1,80,25);
	  cline();
	  printf("input file name:>");
	  gets(fname);
	  if (strlen(fname)==NULL) return NULL;
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
	window(1,1,80,25);

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
	  cline();
	  printf("Student no found !\n");
	  return (NULL);
      }









/* Put the data into a file */
save( STU * head)
	    {    char c;
		 char fname[15];
		 STU *info;
		 FILE *fp;
		 cline();
		 printf("input file name:");
		 scanf("%s",fname);
		 if ((fp=fopen(fname,"wb"))==NULL)
		      {  printf("can not open file \n");
			 return;
		      }
		 cline();
		 printf("\n saving file.\n");
		 info=head;
		 while (info)
		      {
		      fwrite(info,LE,1,fp);
		      info=info->next; }
		      cline();
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
			  {  case 0: if ((info->num)>(temp->num)) swap(info,temp);break;
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
	    cline();
		if (n==0) {printf( "Did not find %d class\n",class);return NULL;}
		else return(sum/n);
	}



/* get each subject score */
int subjectaverage(STU *head,int subject)
	{   STU *info;
	    int sum=0,n=0;
	    info=head;
	    while(info!=NULL)
		{ switch (subject)
			 { case 1:  sum=sum+info->chinese;n++;break;
			   case 2:  sum=sum+info->english;n++;break;
			   case 3:  sum=sum+info->computer;n++;break;
			   case 4:  sum=sum+info->math;n++;break;
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
	 else {cline();printf("%ld not been found!\n",number);return NULL;}
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
modify(STU *head,long number)
	{  STU *info;
	   info=find(head,number);
	   showform();
	   input(info);
	   cline();
	   printf("modify ok");

	}

/* Function of first button */
fun0()
      {
	char fname[20];

	 STU *info;
	 FILE *fp;


	 cline();
	 printf("input file name:>");
	 gets(fname);
	 if (strlen(fname)==0) return;

	 showform();
	/*input(mainhead);*/



	if ((fp=fopen(fname,"wb"))==NULL)
	       { cline();
			 printf("can not open file\m");
			 exit(0);}
	 info=(STU *)malloc(LE);


	 input(info);
	 do {  setviewport(0,0,639,479,0);
	       showform();
	       fwrite(info,LE,1,fp);

	       input(info);

	    }while (info->num!=0);
	    free(info);fclose(fp);





      }





sec10(){
	 sortby(mainhead,0);
	 list(mainhead);

	 getch();
	}
sec11(){ long number;
	 STU *info;

	 cline();
	 printf("input a student number:>");
	 scanf("%ld",&number);
	 info=find(mainhead,number);
	 if (info==NULL) { getch();return NULL;}
	 cline();
	 printf("Number:%ld Name:%s Chinese:%d English:%d Computer:%d Maths:%d",TEXT(info));
	 getch();

}
sec12(){  int n;

	  cline();
	  printf("Sort by what?(1 Chinese,2 English,3 Computer,4 Maths):>");
	  scanf("%d",&n);
	  if (n<1 || n>4) { cline();printf("Input error!");getch();return NULL;}
	  sortby(mainhead,n);
	  list(mainhead);
	  getch();


}

fun1()
      {  char button[3][LEN]={"All","One","Subject"};
	 BUT picture={20,20,50,150,0,0,0,0,BLUE,YELLOW,3};
	 int key,n=0;

	 picture.maxx=getmaxx();
	 picture.maxy=getmaxy();
	 picture.x1=(picture.maxx-picture.dx)/2+20;
	 picture.y1=(picture.maxy-picture.dy*NUM)/2+20;
	 if(fileopen==NO) if(!openfile()) return;
	 drawbutton(&picture,button,3);
	 do{
	     picture.fillstyle=9;
	     picture.fillcolor=LIGHTBLUE;
	     activebutton(&picture,button,n);
	     key=getch();
	     switch(key)
		      {
			  case 72:  n--;
				    { picture.fillstyle=3;
				      picture.fillcolor=BLUE;
				      activebutton(&picture,button,n+1);
				      break;}

			  case 80:  n++;
				    {  picture.fillstyle=3;
				       picture.fillcolor=BLUE;
				       activebutton(&picture,button,n-1);
				       break;}

		      }
		 if(n>3-1) n=0;
		 if(n<0)   n=3-1;
	 }while(key!=13&&key!=27);
		 if (key==27) return;
		   switch(n){
			  case 0: sec10();break;
			  case 1: sec11();break;
			  case 2: sec12();break;

			    }




      }



sec20(){   int classnumber,result;

	   STU *info;


	   cline();
	   printf("Input class number:>");
	   scanf("%d",&classnumber);
	   result=classaverage(mainhead,classnumber);
	   if(result==NULL) {getch();return;}
	   printf("The average score is:%d",result);
	   getch();

}
sec21(){ int subnumber,result;

	 STU *info;


	 cline();
	 printf("Input subject number(1 chinese,2 english,3 computer 4,maths:>");
	 scanf("%d",&subnumber);
	 if (subnumber<1 || subnumber>4) { cline();printf("Input error!");getch();return NULL;}
	 result=subjectaverage(mainhead,subnumber);
	 cline();
	 printf("The average score is:%d",result);
	 getch();

	}
sec22(){
	 int low,high,result;


	 cline();
	 printf("Input fan wei(a,b):>");
	 scanf("%d,%d",&low,&high);
	 result=personnumber(mainhead,low,high);
	 cline();
	 printf("There are %d students' score in this wide\n",result);
	 getch();
	}


fun2()  {char button[3][LEN]={"Classaver","Subjectaver","Personnumber"};
	 BUT picture={20,20,50,150,0,0,0,0,BLUE,YELLOW,3};
	 int key,n=0;

	 picture.maxx=getmaxx();
	 picture.maxy=getmaxy();
	 picture.x1=(picture.maxx-picture.dx)/2+20;
	 picture.y1=(picture.maxy-picture.dy*NUM)/2+40;
	 if (fileopen==NO) if(!openfile()) return;
	 drawbutton(&picture,button,3);
	 do{
	     setviewport(0,0,639,479,1);
	     picture.fillstyle=9;
	     picture.fillcolor=LIGHTBLUE;
	     activebutton(&picture,button,n);
	     key=getch();
	     switch(key)
		      {
			  case 72:  n--;
				    { picture.fillstyle=3;
				      picture.fillcolor=BLUE;
				      activebutton(&picture,button,n+1);
				      break;}

			  case 80:  n++;
				    {  picture.fillstyle=3;
				       picture.fillcolor=BLUE;
				       activebutton(&picture,button,n-1);
				       break;}

		      }
		 if(n>3-1) n=0;
		 if(n<0)   n=3-1;
	 }while(key!=13&&key!=27);
		 if (key==27) return;
		   switch(n){
			  case 0: sec20();break;
			  case 1: sec21();break;
			  case 2: sec22();break;

			    }

	 }


sec30(){
        long number;
	STU *info;
	cline();
	printf("Input student number:>");
	scanf("%ld",&number);
	info=find(mainhead,number);
	if (info==NULL) {getch();return;}
	modify(mainhead,number);
	getch();
	list(mainhead);getch();
	save(mainhead);

       }
sec31(){long number;
	STU *info;
	int won;
	cline();
	printf("Input delete number:>");
	scanf("%ld",&number);
	won=delete(mainhead,number);
	if (won==NULL) { getch(); return;}
	save(mainhead);
	cline();
	printf("delete ok");


       }
sec32(){



	 append(mainhead);
	 save(mainhead);


}



fun3(){char button[3][LEN]={"Modify","Delete","Add"};
       BUT picture={20,20,50,150,0,0,0,0,BLUE,YELLOW,3};
	 int key,n=0;

	 picture.maxx=getmaxx();
	 picture.maxy=getmaxy();
	 picture.x1=(picture.maxx-picture.dx)/2+20;
	 picture.y1=(picture.maxy-picture.dy*NUM)/2+60;
	 if (fileopen==NO) if(!openfile()) return;
	 drawbutton(&picture,button,3);
	 do{
	     picture.fillstyle=9;
	     picture.fillcolor=LIGHTBLUE;
	     activebutton(&picture,button,n);
	     key=getch();
	     switch(key)
		      {
			  case 72:  n--;
				    { picture.fillstyle=3;
				      picture.fillcolor=BLUE;
				      activebutton(&picture,button,n+1);
				      break;}

			  case 80:  n++;
				    {  picture.fillstyle=3;
				       picture.fillcolor=BLUE;
				       activebutton(&picture,button,n-1);
				       break;}

		      }
		 if(n>3-1) n=0;
		 if(n<0)   n=3-1;
	 }while(key!=13&&key!=27);
		 if (key==27) return;
		   switch(n){
			  case 0: sec30();break;
			  case 1: sec31();break;
			  case 2: sec32();break;

			    }

       }


fun4(){openfile();




}

/* Exit the system */
fun5(){
       cleardevice();
       closegraph();
       exit(0);

      }


help(){ int c;

     do{
	rectangle(130,200,500,400);

	rectangle(132,202,498,398);
	bar(133,203,497,397);
	setcolor(WHITE);
	outtextxy(150,220,"Student SYSTEM");
	setcolor(YELLOW);
	outtextxy(200,250,"Writed by:  Baiguang");
	outtextxy(200,270,"Class number:  99070333");
	outtextxy(200,290,"E-mail address:  baiguang19@263.net");
	outtextxy(200,310,"Writing time:  March,2000");
	outtextxy(270,350,"Verson: 1.0");
	setcolor(WHITE);
	outtextxy(270,380,"Press ESC");
	c=getch();
	if(c==27) return;
	}while(1);
      }

main()
      { int i,n=0;
	int key;
	char button[NUM][LEN]={"Creat","Inquire","Statistics","Modify","Load","Exit",};
	BUT picture={50,50,60,180,0,0,0,0};

/* Set the graphic mode */
	int driver,mode;
	driver=VGA;
	mode=2;
	initgraph(&driver,&mode,"c:\\tc\\");


	picture.maxx=getmaxx();picture.maxy=getmaxy();
	picture.x1=(picture.maxx-picture.dx)/2;picture.y1=(picture.maxy-picture.dy*NUM)/2;

    do{
	window(1,1,80,25);
	cleardevice();
	picture.fillcolor=BLUE;
	picture.drawcolor=YELLOW;
	picture.fillstyle=7;

	  setviewport(0,0,639,479,0);
	  background(&picture);                /* Draw background */

	  picture.fillcolor=LIGHTBLUE;
	  picture.fillstyle=3;
	  drawbutton(&picture,button,NUM);          /* Draw allthebuttons */

	       do{


		picture.fillstyle=9;
		picture.fillcolor=BROWN;
		activebutton(&picture,button,n);

		key=getch();         /* Get a key from keyboard */

		switch(key)
		      {
			  case 72:  n--;
				    { picture.fillstyle=3;
				      picture.fillcolor=LIGHTBLUE;
				      activebutton(&picture,button,n+1);
				      break;}

			  case 80:  n++;
				    {  picture.fillstyle=3;
				       picture.fillcolor=LIGHTBLUE;
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
			  case 'L':
			  case 'l':  key=13;n=4;break;
			  case 'E':
			  case 'e':  key=13;n=5;break;
		       }

	    
	    if(n>NUM-1) n=0;
	    if(n<0)   n=NUM-1;
	    if (key==59) {help();key=13;n=6;}
       }while (key!=13);           /* Exit the loop */

    switch(n){
	      case 0: fun0();break;
	      case 1: fun1();break;
	      case 2: fun2();break;
	      case 3: fun3();break;
	      case 4: fun4();break;
	      case 5: fun5();break;
	      case 6: n=0;
	     }

       }while(1);




    }


