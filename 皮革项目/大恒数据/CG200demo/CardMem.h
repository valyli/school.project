#ifndef __CARD_CGMEM__
#define __CARD_CGMEM__
#include "cg210-32.h"
#include "cg200-32.h"
#include "MemAlloc.h"
#include "dibapi.h"
//Used by user
void SampleImageToMem(const DWORD hCard,DWORD& mLineAddr,const WORD nSum,int flag);
void AverageMemIMG(BYTE* pBuf,HANDLE *m_hDIBFrame,int nNum);
void BufferToDIB(const BYTE* pBuf,HANDLE *m_hDIBFrame);
void ScreenBufferToDIB(const BYTE* pBuf,HANDLE *m_hDIBFrame);
BOOL EnoughMemForSampleIMG(int xSize,int ySize,int nColorDepth,int nNum);
//

#endif //__CARD_CGMEM__