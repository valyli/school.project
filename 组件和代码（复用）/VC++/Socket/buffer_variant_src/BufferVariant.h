//===========================================================================
// Buffer Variant
// Copyright (c) 2000 Roy <luoy@eol.com.cn> 
//
// * Author      : Roy
// * File        : BufferVariant.h
// * Description : Interface and Implementation of CEasySocket.
//===========================================================================

#if !defined(ROY_BUFFERVARIANT_H__INCLUDED_)
#define ROY_BUFFERVARIANT_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBufferVariant :public ::tagVARIANT
{
public:
	// Constructors
	//
	CBufferVariant();

	CBufferVariant(const VARIANT& varSrc);
	CBufferVariant(const VARIANT* pSrc);
	CBufferVariant(const CBufferVariant& varSrc);

	CBufferVariant(const void *pSrc,long nLength);	// Creates from a buffer
	CBufferVariant(const char* pSrc);				// Creates from a string

	// Destructor
	//
	virtual ~CBufferVariant();

	// Extractors
	//
	operator const void *() const;					// Extracts a buffer
	operator const char *() const;					// Extracts a string
	operator const unsigned char *() const;			// Extracts a string
	operator void *() const;						// Extracts a buffer
	operator char *() const;						// Extracts a string
	operator unsigned char *() const;				// Extracts a string
	
	// Assignment operations
	//
	CBufferVariant& operator=(const VARIANT& varSrc);
	CBufferVariant& operator=(const VARIANT* pSrc);
	CBufferVariant& operator=(const CBufferVariant& varSrc);
	CBufferVariant& operator=(const char* pSrc);	// Assign a string
	void AssignData(const void *pSrc,long nLength);		// Assign a buffer

	// Append operations
	//
	CBufferVariant& operator+=(const VARIANT& varSrc);
	CBufferVariant& operator+=(const VARIANT* pSrc);
	CBufferVariant& operator+=(const CBufferVariant& varSrc);
	CBufferVariant& operator+=(const char* pSrc);	// Assign a string
	void AppendData(const void *pSrc,long nLength);		// Assign a buffer

	void SetLength(long nLength);
	long GetLength();
	bool IsEmpty();

	VARIANT Copy();

private:
	VARIANT		m_varData;
	void HUGEP *m_pBuffer;
	void BuildByteArrayFromData(const void *pvData, long nLength);
	void BuildByteArrayFromVariant(const VARIANT* pSrc);
	void AppendByteArrayFromData(const void *pvData, long nLength);
	void AppendByteArrayFromVariant(const VARIANT* pSrc);
};

//////////////////////////////////////////////////////////////////////////////////////////
//
// Default constructor
//
//////////////////////////////////////////////////////////////////////////////////////////
inline CBufferVariant::CBufferVariant()
{
	::VariantInit(&m_varData);
	SetLength(0);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
//////////////////////////////////////////////////////////////////////////////////////////
inline CBufferVariant::~CBufferVariant()
{
	SafeArrayUnaccessData(m_varData.parray);
	::VariantClear(&m_varData);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Constructors
//
//////////////////////////////////////////////////////////////////////////////////////////
// Construct a CBufferVariant from a const VARIANT&
//
inline CBufferVariant::CBufferVariant(const VARIANT& varSrc)
{
	::VariantInit(&m_varData);
	BuildByteArrayFromVariant(&varSrc);
}

// Construct a CBufferVariant from a const VARIANT*
//
inline CBufferVariant::CBufferVariant(const VARIANT* pSrc)
{
	::VariantInit(&m_varData);
	BuildByteArrayFromVariant(pSrc);
}

// Construct a CBufferVariant from a const CBufferVariant&
//
inline CBufferVariant::CBufferVariant(const CBufferVariant& varSrc)
{
	::VariantInit(&m_varData);
	BuildByteArrayFromVariant(&varSrc.m_varData);
}

// Construct a VT_BSTR VARIANT from a const char*
//
inline CBufferVariant::CBufferVariant(const char* pSrc)
{
	::VariantInit(&m_varData);
	BuildByteArrayFromData( pSrc, strlen(pSrc));
}

inline CBufferVariant::CBufferVariant(const void * pSrc,long nLength)
{
	::VariantInit(&m_varData);
	BuildByteArrayFromData( pSrc, nLength);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Extractors
//
//////////////////////////////////////////////////////////////////////////////////////////

// Extracts a buffer
inline CBufferVariant::operator const void *() const
{
	return m_pBuffer;
}

// Extracts a buffer
inline CBufferVariant::operator void *() const
{
	return const_cast<void *>(m_pBuffer);
}

// Extracts a string
inline CBufferVariant::operator const char *() const
{
	return (const char *)m_pBuffer;
}

// Extracts a string
inline CBufferVariant::operator char *() const
{
	return const_cast<char *>(m_pBuffer);
}

// Extracts a string
inline CBufferVariant::operator const unsigned char *() const
{
	return (const unsigned char *)m_pBuffer;
}

// Extracts a string
inline CBufferVariant::operator unsigned char *() const
{
	return const_cast<unsigned char *>(m_pBuffer);
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// Assignment operations
//
//////////////////////////////////////////////////////////////////////////////////////////
// Assign a const VARIANT&
//
inline CBufferVariant& CBufferVariant::operator=(const VARIANT& varSrc)
{
	BuildByteArrayFromVariant(&varSrc);
	return *this;
}

// Assign a const VARIANT*
//
inline CBufferVariant& CBufferVariant::operator=(const VARIANT* pSrc)
{
	BuildByteArrayFromVariant(pSrc);
	return *this;
}

// Assign a const CBufferVariant&
//
inline CBufferVariant& CBufferVariant::operator=(const CBufferVariant& varSrc)
{
	long nLength;
	SafeArrayGetUBound(varSrc.m_varData.parray, 1, &nLength);
	nLength--;
	BuildByteArrayFromData(varSrc.m_pBuffer,nLength);
	return *this;
}


// Assign a const char*
//
inline CBufferVariant& CBufferVariant::operator=(const char* pSrc)
{
	BuildByteArrayFromData( pSrc, strlen(pSrc));
	return *this;
}

// Assign a const buffer
//
inline void CBufferVariant::AssignData(const void * pSrc,long nLength)
{
	BuildByteArrayFromData( pSrc, nLength);
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Assignment operations
//
//////////////////////////////////////////////////////////////////////////////////////////
// Append a const VARIANT&
//
inline CBufferVariant& CBufferVariant::operator+=(const VARIANT& varSrc)
{
	AppendByteArrayFromVariant(&varSrc);
	return *this;
}

// Append a const VARIANT*
//
inline CBufferVariant& CBufferVariant::operator+=(const VARIANT* pSrc)
{
	AppendByteArrayFromVariant(pSrc);
	return *this;
}

// Append a const CBufferVariant&
//
inline CBufferVariant& CBufferVariant::operator+=(const CBufferVariant& varSrc)
{
	long nLength;
	SafeArrayGetUBound(varSrc.m_varData.parray, 1, &nLength);
	nLength--;
	AppendByteArrayFromData(varSrc.m_pBuffer,nLength);
	//AppendByteArrayFromData(varSrc,varSrc.GetLength());
	return *this;
}


// Append a const char*
//
inline CBufferVariant& CBufferVariant::operator+=(const char* pSrc)
{
	AppendByteArrayFromData( pSrc, strlen(pSrc));
	return *this;
}

// Append a const buffer
//
inline void CBufferVariant::AppendData(const void * pSrc,long nLength)
{
	AppendByteArrayFromData( pSrc, nLength);
}


//////////////////////////////////////////////////////////////////////////////////////////
//
// Methods
//
//////////////////////////////////////////////////////////////////////////////////////////
inline void CBufferVariant::SetLength(long nLength)
{
	//+ Ensure that we initialise the variant 
	SAFEARRAYBOUND pSafeArrayBound[1];
	
	pSafeArrayBound[0].lLbound = 0;
	pSafeArrayBound[0].cElements = nLength+1;

	if(V_VT(&m_varData) != VT_EMPTY)
	{
		SafeArrayUnaccessData(m_varData.parray);
		SafeArrayRedim( m_varData.parray ,pSafeArrayBound);
	}
	else
	{
		V_VT(&m_varData) = VT_ARRAY | VT_UI1;
		//+ Create the array 
		m_varData.parray = SafeArrayCreate(VT_UI1, 1, pSafeArrayBound);
	}

	
	// Lock and access the memory
	//+ Access the data  
	SafeArrayAccessData(m_varData.parray, (void HUGEP**)&m_pBuffer);

	char *p=(char *)m_pBuffer;
	p[nLength]=0;
	return;
}

inline VARIANT CBufferVariant::Copy()
{
	VARIANT vNew;
	::VariantInit(&vNew);
	::VariantCopy(&vNew, &m_varData);
	return vNew;
}


inline long CBufferVariant::GetLength()
{
	// TODO: Add your implementation code here
	if(V_VT(&m_varData) == VT_EMPTY)
		return 0;

	// Determine the size of the array 
	long nLength;
	SafeArrayGetUBound(m_varData.parray, 1, &nLength);
	return nLength-1;
}

//////////////////////////////////////////////////////////////////////////////////////////
//
// Helper Functions
//
//////////////////////////////////////////////////////////////////////////////////////////
inline void CBufferVariant::BuildByteArrayFromVariant(const VARIANT* pSrc)
{
	//+ Ensure that we initialise the variant 
	if(V_VT(&m_varData) != VT_EMPTY)
	{
		SafeArrayUnaccessData(m_varData.parray);
		::VariantClear(&m_varData);
		::VariantInit(&m_varData);
	}
	
	if(V_VT(pSrc) == (VT_ARRAY | VT_UI1) && SafeArrayGetDim(pSrc->parray) == 1)
	{
		::VariantCopy(&m_varData, const_cast<VARIANT*>(pSrc));
		// Lock and access the memory
		//+ Access the data  
		SafeArrayAccessData(m_varData.parray, (void HUGEP**)&m_pBuffer);
	}
	else
	{
		SetLength(0);
	}
}

inline void CBufferVariant::BuildByteArrayFromData(const void *pvData, long nLength)
{
	SetLength(nLength);
	//+ Copy the data 
	memcpy(m_pBuffer,pvData, nLength );
	return;
}

inline void CBufferVariant::AppendByteArrayFromVariant(const VARIANT* pSrc)
{
	//+ Ensure that we initialise the variant 
	CBufferVariant vbData=*pSrc;
	AppendByteArrayFromData((char *)vbData,vbData.GetLength());
}

inline void CBufferVariant::AppendByteArrayFromData(const void *pvData, long nLength)
{
	long nCurrentLen=GetLength();
	SetLength(nCurrentLen+nLength);
	//+ Copy the data
	char *p=(char *)m_pBuffer;
	memcpy(&p[nCurrentLen],pvData, nLength);
	return;
}

#endif // !defined(ROY_BUFFERVARIANT_H__INCLUDED_)
