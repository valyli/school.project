//**include the standard header
#include "stdafx.h"
#include "blob.h"

//**Add the implementation for serialization
IMPLEMENT_SERIAL(CBlob,CObject,1)


//**Implement the default constructor
CBlob::CBlob()
{
}

//**Implement the position constructor
CBlob::CBlob(CPoint ptPosition)
{
	//**Set the random seed
	srand(GetTickCount());

	//**Set the position to the specified position
	m_ptPosition=ptPosition;


	//**Set the attributes to random values
	m_crColor=RGB(rand()%255,rand()%255,rand()%255);
	m_nSize=10+rand()%30;
	m_nShape=rand();
}

void CBlob::Draw(CDC *pDC)
{
	//**Create and select a colored brush
	CBrush brDraw(m_crColor);
	CBrush *pOldBrush=pDC->SelectObject(&brDraw);
	CPen *pOldPen=
		(CPen *) pDC->SelectStockObject(NULL_PEN);
	//**See the random generator to the shape
	srand(m_nShape);
	for (int n=0;n<3;n++)
	{
		//**Set the blob position and random shift
		CPoint ptBlob(m_ptPosition);
		ptBlob+=CPoint(rand()%m_nSize,rand()%m_nSize);

		//**Create and draw a rectangle
		CRect rcBlob(ptBlob,ptBlob);
		rcBlob.InflateRect(m_nSize,m_nSize);
		pDC->Ellipse(rcBlob);
	}

	//**Reselect the GDI Objects
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
}

void CBlob::Serialize(CArchive& ar)
{
	CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		ar<<m_ptPosition;
		ar<<m_crColor;
		ar<<m_nSize;
		ar<<m_nShape;
	}
	else
	{
		ar>>m_ptPosition;
		ar>>m_crColor;
		ar>>m_nSize;
		ar>>m_nShape;
	}
}
