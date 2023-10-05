#include<stdio.h>
void main(void)
{
int a=3,b=4,c=5;
float x=1.2,y=2.4,z=-3.6;
long u=51274,n=128765;
char c1='a',c2='b';
printf("a=%2d  b=%2d  c=%2d\n",a,b,c);
printf("x=%f,y=%f,z=%f\n",x,y,z);
printf("x+y=%5.2f  y+z=%1.2f  z+x=%1.2f\n",x+y,y+z,z+x);
printf("u=%6u  n=%lu\n",u,n);  /* Where is the error? */
printf("n=%lu\n",n);           /* But this line is right, why?*/
printf("c1=\'%c\' or %d\n",c1,c1);
printf("C2=\'%c\' or %d\n",c2-32,c2);
}