#if !defined(_StrTransformer_H_LIJIA_2003_05_22_)
#define _StrTransformer_H_LIJIA_2003_05_22_

#include "StrFormatTarget.h"

//用于处理字符串编码转换的类，和StrTransformer类联合使用
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