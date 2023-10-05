// PSAPI.cpp: implementation of the PSAPI class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PSAPI.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ENUMPROCESSES EnumProcesses;
ENUMPROCESSMODULES EnumProcessModules;
GETMODULEFILENAMEEX GetModuleFileNameEx;

//PSAPI.DllµÄ¾ä±ú
HMODULE g_hPSAPI;

BOOL InitPSAPI()
{
	g_hPSAPI = ::LoadLibraryA( "PSAPI.DLL" ) ;
	if( g_hPSAPI == NULL )
		return FALSE ;
	
	EnumProcesses = (ENUMPROCESSES) GetProcAddress( g_hPSAPI, "EnumProcesses" );
	EnumProcessModules = (ENUMPROCESSMODULES) GetProcAddress( g_hPSAPI, "EnumProcessModules" );
	GetModuleFileNameEx = (GETMODULEFILENAMEEX) GetProcAddress( g_hPSAPI, "GetModuleFileNameExA" );
	
	if ( EnumProcesses && EnumProcessModules && GetModuleFileNameEx ) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//ÊÍ·ÅDll
void UnInitPSAPI()
{
	if ( g_hPSAPI ) {
		::FreeLibrary( g_hPSAPI );
		g_hPSAPI = 0;
	}
}
