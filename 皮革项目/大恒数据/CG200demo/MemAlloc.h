#include "windows.h"

typedef	DWORD MEMHANDLE,*PMEMHANDLE;
typedef	void **PPVOID;

#define WINAPI __stdcall

//data struct
typedef struct tagMEMQRY
{
	DWORD LockablePageCount;
	BOOL ReturnValue;

}MEMQRY,* PMEMQRY;

typedef struct tagMEMALLOC
{
	DWORD physAddr;
	MEMHANDLE Handle;
	PVOID LineAddress;
	BOOL ReturnValue;
	
}MEMALLOC,* PMEMALLOC;

//function prototype
HANDLE WINAPI LoadDevice(void);
BOOL WINAPI CloseDevice(HANDLE hVXD); 
BOOL WINAPI PhysMemAlloc(HANDLE hVXD,DWORD nPages,PMEMALLOC pMemAlloc);
BOOL WINAPI PhysMemFree(HANDLE hVXD,MEMHANDLE Handle);
BOOL WINAPI StaticMemAlloc(DWORD *pBlockSize,DWORD *pPhysMemAddr,DWORD *pMemHandle,DWORD *pLineAddr);

