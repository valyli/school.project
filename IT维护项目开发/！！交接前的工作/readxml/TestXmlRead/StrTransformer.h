#if !defined(_StrTransformer_H_LIJIA_2003_05_22_)
#define _StrTransformer_H_LIJIA_2003_05_22_

#include "StrFormatTarget.h"

//���ڴ����ַ�������ת�����࣬��StrTransformer������ʹ��
class StrTransformer  
{
public:
	char* ChangeStr(const DOMString& s);
	char* ChangeStr(const XMLCh* str);
	StrTransformer (char* encoding);
	XMLFormatter* format;
	StrFormatTarget* target;
	~StrTransformer();
	DOMString* m_dom;
};

#endif//_StrTransformer_H_LIJIA_2003_05_22_