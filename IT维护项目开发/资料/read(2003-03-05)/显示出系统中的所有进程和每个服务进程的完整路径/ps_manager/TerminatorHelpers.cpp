/////////////////////////////////////////////////////////////////////////////
//
// File        : TerminatorHelpers.cpp
// Project     : TERMINATOR
// Component   : Terminator
//---------------------------------------------------------------------------
// Description : 
//
/////////////////////////////////////////////////////////////////////////////
//
// SourceSafe Strings. Do not change.
//---------------------------------------------------------------------------
// $Author: Jeskes $
// $Date: 20.04.98 10:01 $
// $Revision: 1 $
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "psapi.h"
#pragma comment( lib, "psapi" )

#include "Terminator.h"
#include "TerminatorHelpers.h"

/////////////////////////////////////////////////////////////////////////////

DWORD GetProcessID( LPCSTR lpszNameToSearch, BOOL bUsePath, DWORD idStart )
{
    // Get the list of process IDs

	DWORD idx = 0; 
    DWORD aProcesses[ 1024 ];
    DWORD cProcesses = GetProcessIDs( aProcesses, sizeof( aProcesses ) );

	// position to start off

	if( 0 != idStart )
	{
		while( ( idx < cProcesses ) && ( idStart != aProcesses[ idx ] ) )
		{
			idx++;
		}

		if( idx == cProcesses )
		{
			idx = 0;
		}
		else
		{
			idx++;
		}
	}

	// search for process

    while( idx < cProcesses )
	{
		CString sName = bUsePath ? GetProcessPath( aProcesses[ idx ] ) :
								   GetProcessBaseModuleName( aProcesses[ idx ] );

		if( 0 == sName.CompareNoCase( lpszNameToSearch ) )
		{
			return( aProcesses[ idx ] );
		}

		idx++;
	}

	return( 0 );
}

/////////////////////////////////////////////////////////////////////////////

DWORD GetProcessIDs( DWORD* pdwBuffer, DWORD dwSizeBuffer )
{
    // Get the list of process IDs

	DWORD cbNeeded = 0;

    if( !EnumProcesses( pdwBuffer, dwSizeBuffer, &cbNeeded ) )
	{
		ASSERT( FALSE );
		return( 0 );
	}
    
	return( cbNeeded / sizeof( DWORD ) );
}

/////////////////////////////////////////////////////////////////////////////

CString GetProcessPath( DWORD idProcess )
{
    CString sPath;
    
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                    FALSE, 
									idProcess );
    if( NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;
        
        if( EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded ) )
        {
			DWORD dw = GetModuleFileNameEx( hProcess, hMod, sPath.GetBuffer( MAX_PATH ), MAX_PATH );
			sPath.ReleaseBuffer();
        }
	
	    CloseHandle( hProcess );
    }

	return( sPath );
}

/////////////////////////////////////////////////////////////////////////////

CString GetProcessBaseModuleName( DWORD idProcess )
{
    CString sName;
    
    HANDLE hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                    FALSE, 
									idProcess );
    if( NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;
        
        if( EnumProcessModules( hProcess, &hMod, sizeof( hMod ), &cbNeeded ) )
        {
			DWORD dw = GetModuleBaseName( hProcess, hMod, sName.GetBuffer( MAX_PATH ), MAX_PATH );
			sName.ReleaseBuffer();
        }
	
	    CloseHandle( hProcess );
    }

	return( sName );
}

/////////////////////////////////////////////////////////////////////////////

void TerminateProcessID( DWORD id )
{
    HANDLE hProcess = OpenProcess(  PROCESS_TERMINATE, FALSE, id );

    if( NULL != hProcess )
    {
		TerminateProcess( hProcess, 0 );
		CloseHandle( hProcess );
	}
}
