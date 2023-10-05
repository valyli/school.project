#include <stdio.h>
double X[5]={0.00,0.20,0.30,0.50,0.60};
double f[5]={0.0,0.20134,0.30452,0.52110,0.63665};

double Aitken(double x)
{int i,j;
double I[4][4];
for (i=0;i<4;i++)
 I[i][0]=(f[i+1]-f[0])*(x-X[0])/(X[i+1]-X[0]);
for (i=1;i<=3;i++)
 for (j=3;j>=i;j--)
 I[j][i]=I[i-1][i-1]+(I[j][i-1]-I[i-1][i-1])*(x-X[i])/(X[j+1]-X[i]);
return I[3][3];
}

void main()
{double x,y;
printf("x=");
scanf("%lf",&x);
y=Aitken(x);
printf("sh(%4.2f)=%lf",x,y);
}