/////////////////////////////////////////////////////////////////////////////
//
// File        : TerminatorHelpers.h
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

#pragma once
#ifndef TERMINATORHELPERS_H
#define TERMINATORHELPERS_H

/////////////////////////////////////////////////////////////////////////////

DWORD GetProcessID( LPCSTR lpszName, BOOL bUsePath, DWORD idStart = 0 );
DWORD GetProcessIDs( DWORD* pdwBuffer, DWORD dwSizeBuffer );

CString GetProcessPath( DWORD idProcess );
CString GetProcessBaseModuleName( DWORD idProcess );

void TerminateProcessID( DWORD id );
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
/////////////////////////////////////////////////////////////////////////////
#endif
