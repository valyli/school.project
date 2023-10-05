// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>

#define VWIN32_DIOC_DOS_IOCTL 1 
 
typedef struct _DEVIOCTL_REGISTERS 
{ 
    DWORD reg_EBX; 
    DWORD reg_EDX; 
    DWORD reg_ECX; 
    DWORD reg_EAX; 
    DWORD reg_EDI; 
    DWORD reg_ESI; 
    DWORD reg_Flags; 
} DEVIOCTL_REGISTERS, *PDEVIOCTL_REGISTERS; 
 
typedef struct _MID 
{ 
    WORD  midInfoLevel; 
    DWORD midSerialNum; 
    BYTE  midVolLabel[11]; 
    BYTE  midFileSysType[8]; 
} MID, *PMID; 
 
BOOL DoIOCTL(PDEVIOCTL_REGISTERS preg);

void main(void)
{ 
    DEVIOCTL_REGISTERS reg; 
	PMID pmid;

    reg.reg_EAX = 0x440D;       // IOCTL for block devices 
    reg.reg_EBX = 0;       // zero-based drive ID 
    reg.reg_ECX = 0x0866;       // Get Media ID command 
    reg.reg_EDX = (DWORD) pmid; // receives media ID info 
	DoIOCTL(&reg);
 
/*    if (!DoIOCTL(&reg)) 
        return FALSE; 
 
    if (reg.reg_Flags & 0x8000) // error if carry flag set 
        return FALSE; 
 
    return TRUE; 
*/} 
 
BOOL DoIOCTL(PDEVIOCTL_REGISTERS preg) 
{ 
    HANDLE hDevice; 
 
    BOOL fResult; 
    DWORD cb; 
 
    preg->reg_Flags = 0x8000; // assume error (carry flag set) 
 
    hDevice = CreateFile("\\\\.\\vwin32", 
        GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
        (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, 
        FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL); 
 
    if (hDevice == (HANDLE) INVALID_HANDLE_VALUE) 
        return FALSE; 
    else 
    { 
        fResult = DeviceIoControl(hDevice, VWIN32_DIOC_DOS_IOCTL, 
            preg, sizeof(*preg), preg, sizeof(*preg), &cb, 0); 
 
        if (!fResult) 
            return FALSE; 
    } 
 
    CloseHandle(hDevice); 
 
    return TRUE; 
}