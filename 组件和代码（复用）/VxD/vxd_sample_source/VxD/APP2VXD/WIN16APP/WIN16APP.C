#include <string.h>
#include <windows.h>

#include "dmabuf.h"

typedef void (far * PVOIDFN)( void );

static char MsgBoxBuf[ 1024 ] = { 0 };
PVOIDFN  pfDmaBufApi;
DMA_BUFFER_DESCRIPTOR dmadesc;

PVOIDFN GetVxdApiEntry( int VxdId )
{
  PVOIDFN pfApi;

  _asm
  {
     xor di, di
     mov es, di
     mov bx, VxdId
     mov ax, 1684h
     int 2fh
     mov WORD PTR pfApi+2, es
     mov WORD PTR pfApi, di
  }

  return( pfApi );
}

int PASCAL WinMain( HANDLE hInstance, HANDLE hPrevInstance, 
                    LPSTR lpCmdLine, int nCmdShow )
{
	char far *DmaBufPtr;
	unsigned short usSel, myds;
   WORD  err;

	pfDmaBufApi = GetVxdApiEntry( DMABUF_ID );
	if (!pfDmaBufApi)
	{
		MessageBox( NULL, "Error, couldn't get VxD API", "USEAPI", MB_OK );
	}
	else
	{
   	dmadesc.Size = 32L * 1024L;
   	_asm
   	{
   	   mov ax, DMABUF_FUNC_ALLOCBUFFER
   	   lea si, dmadesc     ; small model, don't need to load DS
   	   call DWORD PTR pfDmaBufApi
         mov err, ax
   	}
      if (err)
      {
   		MessageBox( NULL, "Error calling AllocBuffer", "USEAPI", MB_OK );
      }
   	else
   	{
   	  	_asm mov myds, ds
   		usSel = AllocSelector( myds );
   		SetSelectorBase( usSel, dmadesc.LinAddr );
   		SetSelectorLimit( usSel, dmadesc.Size );
   		DmaBufPtr = MAKELP( usSel, 0 );
   		wsprintf( MsgBoxBuf, "Physical=%08lX\nLinear=%08lXSelector=%X\n", 
                             dmadesc.PhysAddr, dmadesc.LinAddr, usSel );
   	   MessageBox( NULL, MsgBoxBuf, "USEAPI", MB_OK );

   		FreeSelector( usSel );
   		_asm
   		{
   		   mov ax, DMABUF_FUNC_FREEBUFFER
   		   call DWORD PTR pfDmaBufApi
   		}
   	}
	}

	return 0;

}



