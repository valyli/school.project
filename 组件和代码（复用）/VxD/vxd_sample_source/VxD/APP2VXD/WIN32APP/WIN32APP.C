#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "dmabuf.h"

HANDLE		hDevice;
DMA_BUFFER_DESCRIPTOR dmadesc;	

void main(int ac, char* av[])
{
	DWORD   cbBytesReturned;
	DWORD	err;

	const PCHAR VxDName = "\\\\.\\DMABUF.VXD";
	hDevice = CreateFile(VxDName, 0,0,0,
                        CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, 0);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		err = GetLastError();
       	fprintf(stderr, "Cannot load VxD, error=%08lx\n", err );
		if (err == ERROR_NOT_SUPPORTED)
		{
			DeleteFile("\\\\.\\DMABUF");
		}
	 	exit(1);
	}


	dmadesc.Size = 32 * 1024;
	if (!DeviceIoControl(hDevice, DMABUF_FUNC_ALLOCBUFFER,
               &dmadesc, sizeof(DMA_BUFFER_DESCRIPTOR), 
               NULL, 0, &cbBytesReturned, NULL))
   {
		printf("DeviceIoControl failed, error=%d\n", GetLastError() );
   }
	else
	{
		printf( "Physical=%08lX\nLinear=%08lX\n", dmadesc.PhysAddr, dmadesc.LinAddr );
		if (!DeviceIoControl(hDevice, DMABUF_FUNC_FREEBUFFER,
    	           &dmadesc, sizeof(DMA_BUFFER_DESCRIPTOR), 
        	       NULL, 0, &cbBytesReturned, NULL)
		   )
      {
			printf("DeviceIoControl failed, error=%d\n", GetLastError() );
		}
	}

	CloseHandle( hDevice );
}
