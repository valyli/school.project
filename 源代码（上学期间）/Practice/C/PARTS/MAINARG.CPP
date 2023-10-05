#include<stdio.h>
#include<string.h>
main(int argc,char *argv[])
{argv++;
 if(!strcmp(*argv,"y")) printf("%s\n",*argv);
}