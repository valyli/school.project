#include <stdio.h>
double X[]={0.40,0.55,0.65,0.80,0.90,1.05};
double f[]={0.41075,0.57815,0.69675,0.88811,1.02652,1.25382};
double I[5][5];

void Newton()
{int i,j;
for (i=0;i<=4;i++)
 I[i][0]=(f[i+1]-f[i])/(X[i+1]-X[i]);
for (i=1;i<=4;i++)
 for (j=4;j>=i;j--)
  I[j][i]=(I[j][i-1]-I[j-1][i-1])/(X[j+1]-X[j-i]);
}

void main()
{int i,j;
double x,item;
double y=f[0];
printf("x=");
scanf("%lf",&x);
Newton();
for (i=0;i<=3;i++)
 {item=I[i][i];
  for (j=0;j<=i;j++)
   item=item*(x-X[j]);
  y+=item;
 }
printf("f(%lf)=%lf",x,y);
}