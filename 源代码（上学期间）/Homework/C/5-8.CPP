#include<stdio.h>
#define N100 1000000.
#define N60 600000.
#define N40 400000.
#define N20 200000.
#define N10 100000.

float a[7]={0.,0.,0.,0.,0.,0.,0.};

void input()
{printf("Please input your profit: ");
 scanf("%f",&a[0]);printf("\na[0]=%f\n",a[0]);
}

float sum()
{int i;
 float num=0.;
 for(i=1;i<=6;i++) {num=num+a[i];printf("a[%d]=%f\n",i,a[i]);}
 return(num);
}

void output()
{if(a[0]>N100) a[6]=(a[0]-N100)*0.01;
 if(a[0]>N60) a[5]=(((a[0]<=N100)?a[0]:N100)-N60)*0.015;
 if(a[0]>N40) a[4]=(((a[0]<=N60)?a[0]:N60)-N40)*0.03;
 if(a[0]>N20) a[3]=(((a[0]<=N40)?a[0]:N40)-N20)*0.05;
 if(a[0]>N10) a[2]=(((a[0]<=N20)?a[0]:N20)-N10)*0.075;
 a[1]=((a[0]<=N10)?a[0]:N10)*0.1;
 printf("The bonus you get: %f\n",sum());
}

void main()
{input();
 output();
}
