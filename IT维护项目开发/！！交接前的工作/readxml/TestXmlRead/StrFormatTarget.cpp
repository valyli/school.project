#include "StrFormatTarget.h"

void StrFormatTarget::writeChars(const XMLByte* const toWrite, const unsigned int count, XMLFormatter * const formatter)
{
	buffer = (char *)malloc(count + 1);
	memset(buffer,0,count+1);
	memcpy(buffer, (char *) toWrite, count);
}

char* StrFormatTarget::GetResult()
{
	char* ret = (char*)malloc(strlen(buffer) + 1);
	strcpy(ret, buffer);
	ret[strlen(buffer)] = 0;
	free(buffer);
	return ret;
} 
