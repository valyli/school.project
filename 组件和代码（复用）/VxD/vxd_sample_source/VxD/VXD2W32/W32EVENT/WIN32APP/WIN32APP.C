#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "..\vxd\eventvxd.h"

HANDLE hDevice;
VMINFO *pVMInfo;

DWORD WINAPI SecondThread( PVOID hEventRing3 );

DWORD WINAPI SecondThread( PVOID hEventRing3 )
{
   while( TRUE )
   {
      WaitForSingleObject((HANDLE)hEventRing3, INFINITE );
      printf("VM %08lx was %s\n", pVMInfo->hVM, 
              pVMInfo->bVmCreated ? "created" : "destroyed" );
   }
   return 0;
}

void main( int ac, char *av[] )
{
	HINSTANCE hKernel32Dll;
   HANDLE    hEventRing3, hEventRing0;
   DWORD     tid;
   HANDLE    (WINAPI *pfOpenVxDHandle)(HANDLE);
DWORD cbBytesReturned;

	const PCHAR VxDName = "\\\\.\\EVENTVXD.VXD";
   
   hEventRing3 = CreateEvent( 0, FALSE, FALSE, NULL );   
   if (!hEventRing3)
   {
      printf("Cannot create Ring3 event\n");
      exit(1);
   }

   hKernel32Dll = LoadLibrary("kernel32.dll");
   if (!hKernel32Dll)
   {
   printf("Cannot load KERNEL32.DLL\n");
   exit(1);
   }

   pfOpenVxDHandle = (HANDLE (WINAPI *) (HANDLE)) 
                     GetProcAddress( hKernel32Dll, "OpenVxDHandle" ); 
   if (!pfOpenVxDHandle)
   {
      printf("Cannot get addr of OpenVxDHandle\n");
      exit(1);
   }

   hEventRing0 = (*pfOpenVxDHandle)(hEventRing3);
   if (!hEventRing0)
   {
      printf("Cannot create Ring0 event\n");
     exit(1);
   }
   
   hDevice = CreateFile( VxDName, 0, 0, 0, 
                         CREATE_NEW, FILE_FLAG_DELETE_ON_CLOSE, 0 );
   if (!hDevice)
   {
      printf("Cannot load VxD error=%x\n", GetLastError() );
      exit(1);
   }

   if (!DeviceIoControl( hDevice, EVENTVXD_REGISTER, 
                         hEventRing0, sizeof(hEventRing0), 
                         &pVMInfo, sizeof(pVMInfo), 
                         &cbBytesReturned, 0 ))
   {
      printf("DeviceIoControl failed, error=%x\n", GetLastError() );
      exit(1);
   }
   CreateThread( 0, 0x1000, SecondThread, hEventRing3, 0, &tid );
   printf("Press any key to exit...");
   getch();
   CloseHandle( hDevice );
}

