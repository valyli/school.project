#include<stdio.h>

void main()
{
  int monthday[13]={1,31,28,31,30,31,30,31,31,30,31,30,31};
  int weekday[36];
  int year,day=1,month,week;
  int i,j=0;
  FILE *fp;
  fp = fopen("year.txt","w");

  for ( i=0;i<=36;i++) weekday[i]=0;

  printf("\nYear:");
  scanf("%d",&year);

  printf("\nMonth:");
  scanf("%d",&month);

  if ((year<0) || (month<0))
  {
    printf("Data error(Your number must above Zero)!");
    exit(0);
  }

  if (((year%4==0) && (year%100!=0)) || (year%400==0)) monthday[2]=29;

  for (i=0;i<month;i++) day+=monthday[i];//has past days

  week=(year-1+(int)((year-1)/4+0.5)-(int)((year-1)/100+0.5)+(int)((year-1)/400+0.5)+day)%7;//the 1st day of the year

  for ( i=week;i<monthday[month]+week;i++) weekday[i]=++j;//put days into weekday[]

  printf(" Sun Mon Tue Wed Thu Fri Sat");
  fprintf(fp," Sun Mon Tue Wed Thu Fri Sat");

  for ( i=0;i<=36;i++)
  {
    if (i%7==0)
    {
	putchar('\n');
	fprintf(fp, "\n");
    }
    if (weekday[i]!=0) printf("%4d",weekday[i]);
	else printf("%4c",' ');
    if (weekday[i]!=0) fprintf(fp,"%4d",weekday[i]);
	else fprintf(fp,"%4c",' ');
  }
  fclose(fp);
}
