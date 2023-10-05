// LIDP_Date.cpp: implementation of the LIDP_Date class.
//
//////////////////////////////////////////////////////////////////////

#include "LIDP_Date.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LIDP_Date::LIDP_Date()
{

}

LIDP_Date::~LIDP_Date()
{

}

//以下时间格式为"2003-04-06 20:33:35"
char* LIDP_Date::LocalTime()
{
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	char* buff;
	buff = (char*)malloc(20);
	sprintf(buff, "%4d-%2d-%2d %2d:%2d:%2d", 
		t->tm_year+1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
	for(int i = 0; i < 19; i++)
	{
		if(i == 10)
			continue;
		if(buff[i] == ' ')
			buff[i] = '0';
	}
	return buff;
}

//返回值
//-1, time1 < time2
//0, time1 = time2
//1, time1 > time2
int LIDP_Date::Compare(char* time1, char* time2)
{
	return strcmp(time1, time2);
}
