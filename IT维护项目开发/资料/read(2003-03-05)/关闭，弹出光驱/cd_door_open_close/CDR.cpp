/////////////////////////////////////////////////////////////////////////////
//
// CDR.cpp : Source for CDR Utility
//
// by Chris Morse Sebrell 12-Nov-2000
//
// Public Domain
//
// LINK with winmm.lib
//

#include "stdafx.h"

#define CD_DRIVE_OPEN	1
#define CD_DRIVE_CLOSE	2

void CD_OpenCloseDrive(BOOL bOpenDrive, TCHAR cDrive);
void CD_OpenCloseAllDrives(BOOL bOpenDrives);  // TRUE to open all drives, FALSE to close all drives

int ShowUsage()
{
	printf("CDR.EXE by Chris Morse Sebrell\n");
	printf("usage:\n");
	printf("    CDR <open|close> [Drive|ALL]\n");
	printf("example:\n");
	printf("    CDR open E:\n");
	printf("    CDR close ALL\n");
	return(0);
}

BOOL ParseOptions(int argc, char* argv[], int& nOpenClose, TCHAR& cDrive)
{
	// Sanity Check
	if(argc < 2) return(FALSE); // Not enough params..
	if(argc > 3) return(FALSE);	// Too many params..

	// Open or Close Drive?
	nOpenClose = 0;
	if(stricmp(argv[1], "open") == 0) nOpenClose = CD_DRIVE_OPEN;
	if(stricmp(argv[1], "close") == 0) nOpenClose = CD_DRIVE_CLOSE;
	if(nOpenClose == 0) return(FALSE);	// argv[1] isn't "open" or "close"

	// Which Drive?
	if(argc == 2)
	{
		// No drive specified, so flag Default drive
		cDrive = 1;
		return(TRUE);
	}

	// .:. argc == 3

	// If drive is "ALL" or "*" then flag all drives
	if((stricmp(argv[2], "all") == 0) || (strcmp(argv[2], "*") == 0))
	{
		// ALL drives
		cDrive = 0;
		return(TRUE);
	}

	LPCTSTR szDrive = argv[2];
	int nLen = strlen(szDrive);
	if(nLen > 2) return(FALSE);		// Not "D" or "D:"
	if((nLen == 2) && (szDrive[1] != ':')) return(FALSE); // 2 Chars, but second isn't a ":"
	
	// Get Drive Letter
	cDrive = szDrive[0];
	if((cDrive >= 'a') && (cDrive <= 'z'))
		cDrive = cDrive - 32;	// Convert lowercase to uppercase

	// Valid Drive Letter?
	if( (cDrive < 'A') || (cDrive > 'Z') )
		return(FALSE);

	// OK
	return(TRUE);
}

int main(int argc, char* argv[])
{

	int   nOpenClose;	// See #define's above
	TCHAR cDrive;       // '*' for ALL Drives, otherwise drive letter

	if(!ParseOptions(argc, argv, nOpenClose, cDrive))
		return ShowUsage();

	if(cDrive == 0)
	{
		CD_OpenCloseAllDrives((nOpenClose == CD_DRIVE_OPEN));
	}
	else
	{
		switch(nOpenClose)
		{

		case CD_DRIVE_OPEN:
			CD_OpenCloseDrive(TRUE, cDrive);
			break;
		case CD_DRIVE_CLOSE:
			CD_OpenCloseDrive(FALSE, cDrive);
			break;
		}
	}

	return(0);
}

// Open or Close CD Drive
// cDrive is Drive Letter to Open, or 1 for 'Default' drive
// Examples:
//    CD_OpenCloseDrive(TRUE, 'G');   // Open CD Door for Drive G: 
//    CD_OpenCloseDrive(FALSE, 'G');  // Close CD Door for Drive G:
//    CD_OpenCloseDrive(TRUE, 1);     // Open First Logical CD Drive Door
void CD_OpenCloseDrive(BOOL bOpenDrive, TCHAR cDrive)
{
	MCI_OPEN_PARMS op;
	MCI_STATUS_PARMS st;
	DWORD flags;

	TCHAR szDriveName[4];
	strcpy(szDriveName, "X:");

	::ZeroMemory(&op, sizeof(MCI_OPEN_PARMS));
	op.lpstrDeviceType = (LPCSTR) MCI_DEVTYPE_CD_AUDIO;
	
	if(cDrive > 1)
	{
		szDriveName[0] = cDrive;
		op.lpstrElementName = szDriveName;
		flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_ELEMENT | MCI_OPEN_SHAREABLE;
	}
	else flags = MCI_OPEN_TYPE | MCI_OPEN_TYPE_ID | MCI_OPEN_SHAREABLE;

	if (!mciSendCommand(0,MCI_OPEN,flags,(unsigned long)&op)) 
	{
		st.dwItem = MCI_STATUS_READY;

		if(bOpenDrive)
			mciSendCommand(op.wDeviceID,MCI_SET,MCI_SET_DOOR_OPEN,0);
		else
			mciSendCommand(op.wDeviceID,MCI_SET,MCI_SET_DOOR_CLOSED,0);

		mciSendCommand(op.wDeviceID,MCI_CLOSE,MCI_WAIT,0);
	}
}

void CD_OpenCloseAllDrives(BOOL bOpenDrives)
{
	// Determine All CD Drives and Open (or Close) each one
    int nPos = 0;
    UINT nCount = 0;
    TCHAR szDrive[4];
	strcpy(szDrive, "?:\\");

    DWORD dwDriveList = ::GetLogicalDrives ();

    while (dwDriveList) {
        if (dwDriveList & 1) 
		{
            szDrive[0] = 0x41 + nPos;
			if(::GetDriveType(szDrive) == DRIVE_CDROM)
				CD_OpenCloseDrive(bOpenDrives, szDrive[0]);
        }
        dwDriveList >>= 1;
        nPos++;
    }
}

