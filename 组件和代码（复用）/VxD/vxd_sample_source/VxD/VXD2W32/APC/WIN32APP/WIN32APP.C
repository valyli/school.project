#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include "apcvxd.h"

HANDLE	hDevice;     
char     buf[80];
DWORD WINAPI CallbackFromVxD(PVOID param);


DWORD WINAPI CallbackFromVxD(PVOID param)
{
   VMINFO *pVmInfo = param;

   printf("VM %08lx was %s\r\n", pVmInfo->hVM, 
           pVmInfo->bVmCreated ? "created" : "destroyed" );
   DeviceIoControl(hDevice, APCVXD_RELEASEMEM, pVmInfo, sizeof(pVmInfo),0,0,0,0);
   return 0;
}

void main(int ac, char* av[])
{
   DWORD err;
	const PCHAR VxDName = "\\\\.\\APCVXD.VXD";

	hDevice = CreateFile(VxDName, 0,0,0,
                        CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, 0);

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		err = GetLastError();
   	printf("Cannot load VxD, error=%08lx\n", err );
		if (err == ERROR_NOT_SUPPORTED)
		{
			DeleteFile("\\\\.\\DMABUF");
		}
	 	exit(1);
	}

	if ( !DeviceIoControl(hDevice, APCVXD_REGISTER,
               &CallbackFromVxD, sizeof(void *),
               NULL, 0, NULL, NULL))
	{
   		printf("DeviceIoControl failed, error=%d\n", GetLastError() );
	}
   else
   {
   	printf("press ctrl-C to exit . . .\n");

   	while (TRUE)
   	{
   		SleepEx(-1, TRUE);
   	}
   }
}
