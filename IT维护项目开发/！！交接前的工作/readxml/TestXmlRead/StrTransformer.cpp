#include "StrTransformer.h"

StrTransformer::StrTransformer(char* encoding)
{
	target = new StrFormatTarget();
	m_dom = new DOMString(encoding);
	format = new XMLFormatter(m_dom->rawBuffer(), target,
	XMLFormatter::NoEscapes, XMLFormatter::UnRep_CharRef);
}

StrTransformer::~StrTransformer()
{
	delete target;
	delete m_dom;
	delete format;
}

char* StrTransformer::ChangeStr(const DOMString& s)
{
	unsigned int lent = s.length();

	if (lent <= 0)
		return NULL;
    XMLCh* buf = new XMLCh[lent + 1];
    XMLString::copyNString(buf, s.rawBuffer(), lent);
    buf[lent] = 0;
    *format<< buf;
    delete [] buf;
	return target->GetResult();
}

char* StrTransformer::ChangeStr(const XMLCh* str)
{
	DOMString dom(str);
	return ChangeStr(dom); 
}

