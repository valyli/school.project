//**Ensure the class isn't declared twice
#ifndef _BLOB_H
#define _BLOB_H

//**Derive a CBlob class from CObject
class CBlob:public CObject
{
	//**Include the Serialization functions
	DECLARE_SERIAL(CBlob);

public:
	//**Declare two constructors
	CBlob();
	CBlob(CPoint ptPosition);

	//**Declare a drawing function
	void Draw(CDC* pDC);
	virtual void Serialize(CArchive& ar);

	//**Declare the attributes
	CPoint m_ptPosition;
	COLORREF m_crColor;
	int m_nSize;
	unsigned m_nShape;
};

#endif // _BLOB_H