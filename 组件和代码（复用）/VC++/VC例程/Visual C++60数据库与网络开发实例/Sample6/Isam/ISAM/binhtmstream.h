#if !defined BINHTMSTREAM_H
#define BINHTMSTREAM_H

class CBinaryHtmlStream : public CHtmlStream
{
public:
	// we have a special overload of << to allow for a single byte
	CBinaryHtmlStream& operator<<(BYTE b) { Write(&b, 1); return *this; }
};

#endif // !defined BINHTMSTREAM_H