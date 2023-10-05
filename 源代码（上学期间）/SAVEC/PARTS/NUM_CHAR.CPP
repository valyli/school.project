#include<stdio.h>
void cov(long x)
{
if (x/10)cov(x/10);
putchar(x%10+'0');putchar(' ');
}
void main()
{
long num;
scanf("%d",&num);
cov(num);
}
