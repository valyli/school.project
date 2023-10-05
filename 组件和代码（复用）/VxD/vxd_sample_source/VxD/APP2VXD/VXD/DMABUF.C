#define WANTVXDWRAPS

#include <basedef.h>
#include <vmm.h>
#include <debug.h>
#include "vxdcall.h"
#include <vxdwraps.h>
#include <wrappers.h>
#include <vwin32.h>
#include "dmabuf.h"

#ifdef DEBUG
#define DPRINTF0(buf, fmt) _Sprintf(buf, fmt ); Out_Debug_String( buf )
#define DPRINTF1(buf, fmt, arg1) _Sprintf(buf, fmt, arg1 ); Out_Debug_String( buf )
#define DPRINTF2(buf, fmt, arg1, arg2) _Sprintf(buf, fmt, arg1, arg2 ); Out_Debug_String( buf )
#else
#define DPRINTF0(buf, fmt)
#define DPRINTF1(buf, fmt, arg1)
#define DPRINTF2(buf, fmt, arg1, arg2)
#endif

BOOL bOwned = FALSE;
DWORD nPages = 16;	// 64K = 16 * 4K
void *LinAddr;
DWORD PhysAddr;
BOOL  bWin3x = FALSE;
char  dbgbuf[80];

DWORD AllocBuffer( DMA_BUFFER_DESCRIPTOR *pBufDesc );
DWORD FreeBuffer( DMA_BUFFER_DESCRIPTOR *pBufDesc );

BOOL OnSysDynamicDeviceInit()
{
	DPRINTF0(dbgbuf,"Loading\r\n");
	return TRUE;
}

BOOL OnSysDynamicDeviceExit()
{
	DPRINTF0(dbgbuf,"Unloading\r\n");
	return TRUE;
}


DWORD OnW32Deviceiocontrol(PDIOCPARAMETERS p)
{
	DPRINTF1(dbgbuf,"W32DevIoControl code=%x\n", p->dwIoControlCode );

	switch (p->dwIoControlCode)
	{
	case DIOC_GETVERSION:	
	case DIOC_CLOSEHANDLE: 	// file closed
		return 0;

	case DMABUF_FUNC_ALLOCBUFFER:
	    if (!_Assert_Range( p->lpvInBuffer, sizeof( DMA_BUFFER_DESCRIPTOR ), 0, 0, ASSERT_RANGE_NULL_BAD))
			return DMABUF_INVALID_PARAMETER;
		else
			return( AllocBuffer( (DMA_BUFFER_DESCRIPTOR *)p->lpvInBuffer ) );

	case DMABUF_FUNC_FREEBUFFER:
	    if (!_Assert_Range( p->lpvInBuffer, sizeof( DMA_BUFFER_DESCRIPTOR ), 0, 0, ASSERT_RANGE_NULL_BAD))
			return DMABUF_INVALID_PARAMETER;
		else
			return( FreeBuffer( (DMA_BUFFER_DESCRIPTOR *)p->lpvInBuffer ) );

	default:
		return -1;
	}
}

void __cdecl PM_Api_Handler(VMHANDLE hVM, CLIENT_STRUCT *pcrs)
{
	DMA_BUFFER_DESCRIPTOR *pBufDesc;

	switch( pcrs->CWRS.Client_AX )
	{
 	case DMABUF_FUNC_ALLOCBUFFER:
		pBufDesc = MAPFLAT(Client_DS, Client_SI);
		pcrs->CWRS.Client_AX = AllocBuffer( pBufDesc );	
		break;

 	case DMABUF_FUNC_FREEBUFFER:
		pBufDesc = MAPFLAT(Client_DS, Client_SI);
		pcrs->CWRS.Client_AX = FreeBuffer( pBufDesc );		
		break;

   default:
      pcrs->CWRS.Client_AX = DMABUF_INVALID_FUNC;
      break;
	}
}

DWORD AllocBuffer( DMA_BUFFER_DESCRIPTOR *pBufDesc )
{
	DWORD rc = 0;

	if (bOwned)
	{
		rc = DMABUF_ALREADY_ALLOCED;
	}
	else
	{
		bOwned = TRUE;
		if (bWin3x)
		{
			if (pBufDesc->Size > 16 * 4 * 1024)
				rc = DMABUF_SIZE_TOO_BIG;
			else
			{
				pBufDesc->PhysAddr = PhysAddr;
				pBufDesc->LinAddr = LinAddr;
			}			
		}
		else
		{
			// Win95, can alloc phys contig pages at any time
			pBufDesc->LinAddr = LinAddr = _PageAllocate(pBufDesc->Size >> 12, PG_SYS, 0, 0x0F, 0, 0x1000, 
			                                  &pBufDesc->PhysAddr, PAGEFIXED | PAGEUSEALIGN | PAGECONTIG );
			if (!LinAddr)
				rc = DMABUF_BUF_NOT_AVAIL;
		}		
	}
	return rc;
}

DWORD FreeBuffer( DMA_BUFFER_DESCRIPTOR *pBufDesc )
{
	DWORD	rc = 0;

	if (bOwned)
	{
		bOwned = FALSE;
		// free buffer only if Win95
		// and don't free buffer unless it's the same one we allocated
		if (pBufDesc->LinAddr == LinAddr)
		{
			if (!bWin3x)
			{
				_PageFree( pBufDesc->LinAddr, 0 );
			}
		}
		else
		{
			rc = DMABUF_BUF_NOT_ALLOCED;
		}
	}
	else
	{
		rc = DMABUF_BUF_NOT_ALLOCED;
	}
	return rc;
}

BOOL OnInitComplete(VMHANDLE hVM, PCHAR CommandTail)
{
	DWORD	ver;

	Get_VMM_Version();

	if (HIWORD(ver) <= 3)
	{
		// Win3.x, not 95
		bWin3x = TRUE;
		// must alloc phys contig pages now
		LinAddr = _PageAllocate(nPages, PG_SYS, 0, 0x0F, 0, 0x1000, &PhysAddr, 
              PAGEFIXED | PAGEUSEALIGN | PAGECONTIG );
	}
	return TRUE;
}
