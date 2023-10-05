#include <time.h>
#include <stdio.h>
#include <dos.h>

void int_speed(void)
{time_t t1,t2;
 register long i;
 register long count=-2147483640;
 printf("\n\n\n\n");
 printf("Testing CPU INT-MATH speed...\n");
 printf("That need about one minutes, please wait...\n");
 t1=time(NULL);
 for(i=1;i<=10200000;i++)
 {count=count+3221225460;
  count=count*2;
  count=count/2;
  count=count-3221225460;
 }
 t2=time(NULL);
 printf("Start test seconds is : %ld\n",t1);
 printf("End test seconds is   : %ld\n",t2);
 printf("CPU INT-speed is      : %f MHz\n",7200.0/(t2-t1));
}

void float_speed(void)
{time_t t1,t2;
 register long i;
 register long double count=-9.87654321987654321e4930;
 printf("\n\n");
 printf("Testing CPU FLOAT-MATH speed...\n");
 printf("That need about one minutes, please wait...\n");
 t1=time(NULL);
 for(i=1;i<=33000000;i++)
 {count=count+1.97530123456789012e4931;
  count=count*1.23456789012345678;
  count=count/1.23456789012345678;
  count=count-1.97530123456789012e4931;
 }
 t2=time(NULL);
 printf("Start test seconds is : %ld\n",t1);
 printf("End test seconds is   : %ld\n",t2);
 printf("CPU FLOAT-speed is    : %f MHz\n",7200.0/(t2-t1));
}

void main(void)
{int_speed();
 float_speed();
}
