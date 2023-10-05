#if !defined(_StrFormatTarget_H_LIJIA_2003_05_22_)
#define _StrFormatTarget_H_LIJIA_2003_05_22_


#include <string.h>
#include <stdlib.h>

#include "ForXecro.h"

//���ڴ����ַ�������ת�����࣬��StrTransformer������ʹ��
class StrFormatTarget : public XMLFormatTarget
{
public:
	StrFormatTarget(){};
	~StrFormatTarget(){};
	char* GetResult();
	void writeChars(const XMLByte* const toWrite, const unsigned int count, XMLFormatter * const formatter);

private:
	char* buffer;
	StrFormatTarget(const StrFormatTarget & other);
	void operator=(const StrFormatTarget & rhs);
};

#endif//_StrFormatTarget_H_LIJIA_2003_05_22_