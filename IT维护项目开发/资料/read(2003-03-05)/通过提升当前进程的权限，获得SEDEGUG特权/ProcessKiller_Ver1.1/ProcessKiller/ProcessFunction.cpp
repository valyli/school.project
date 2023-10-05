// ProcessFunction.cpp: implementation of the ProcessFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "processkiller.h"
#include "ProcessFunction.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Global Process Functions
// Because Use psapi.dll so Only can use in Win2000
//////////////////////////////////////////////////////////////////////

#include "psapi.h"

//提升进程权限
BOOL UpdateProcessPrivilege( HANDLE hProcess, LPCTSTR lpPrivilegeName = SE_DEBUG_NAME )
// hProcess [in] : 要提升的进程，目标进程
// lpPrivilegeName [in] : 要提升到的特权，目标特权
// 返回值 : TRUE : 成功; FALSE : 失败
{
	HANDLE hToken;
	if ( ::OpenProcessToken( hProcess, TOKEN_ALL_ACCESS, &hToken ) ) {
		
		LUID destLuid;
		if ( ::LookupPrivilegeValue( NULL, lpPrivilegeName, &destLuid ) ) {
			
			TOKEN_PRIVILEGES TokenPrivileges;
			TokenPrivileges.PrivilegeCount = 1;
			TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
			TokenPrivileges.Privileges[0].Luid = destLuid;
			int iResult;
			if ( iResult = ::AdjustTokenPrivileges( hToken, FALSE, &TokenPrivileges, 
									0, NULL, NULL ) ) {
				
				return TRUE;				
			}
		}
	}

	return FALSE;
}

//获取进程信息列表
BOOL EnumProcessesInfo( PROCESSINFO* lpPsInfo, ULONG ulSize, ULONG* pulNeeded )
// lpPsInfo [out] : 指向PROCESSINFO结构数组的指针
// nSize [in] : lpPsInfo中的元素个数
// nNeeded [out] : 实际的元素个数
// 返回值 : TRUE : 成功; FALSE : 失败
{
	ASSERT( pulNeeded );
	
	LPDWORD        lpdwPIDs ;			//存储进程ID数组
	DWORD          dwbSize, dwbSize2;
	
	dwbSize2 = 256 * sizeof( DWORD );
	lpdwPIDs = NULL;

	do {

		if( lpdwPIDs ) {

			HeapFree( GetProcessHeap(), 0, lpdwPIDs );
			dwbSize2 *= 2;
		}

		lpdwPIDs = (LPDWORD)HeapAlloc( GetProcessHeap(), 0, dwbSize2 );
		if( lpdwPIDs == NULL ) {
			return FALSE ;
		}

		if( ! ::EnumProcesses( lpdwPIDs, dwbSize2, &dwbSize ) ) {

			HeapFree( GetProcessHeap(), 0, lpdwPIDs ) ;
			return FALSE ;
		}

	}while( dwbSize == dwbSize2 ) ;

	ULONG ulCount  = dwbSize / sizeof( DWORD );
	
	//如果为询问数量，则返回实际数量
	if ( NULL == lpPsInfo && 0 == ulSize ) {
	
		*pulNeeded = ulCount;
		return TRUE;
	}

	ASSERT( lpPsInfo );
	if ( NULL == lpPsInfo ) {
		return FALSE;
	}

	if ( ulSize <= ulCount ) {
		*pulNeeded = ulSize;
	}
	else {
		*pulNeeded = ulCount;
	}

	//获得进程信息
	HANDLE	hProcess;
	HMODULE	hModule;
	DWORD		dwSize;

   
   char path_buffer[_MAX_PATH];
   char drive[_MAX_DRIVE];
   char dir[_MAX_DIR];
   char fname[_MAX_FNAME];
   char ext[_MAX_EXT];
   
	// Loop through each ProcID.
	for( ULONG ulIndex = 0 ; ulIndex < (*pulNeeded) ; ulIndex++ )
	{
		// Open the process (if we can... security does not
		// permit every process in the system).
//		TRACE("PID To Open:%d\r\n", lpdwPIDs[ulIndex] );

		lpPsInfo[ulIndex].dwPID = lpdwPIDs[ulIndex];
      lpPsInfo[ulIndex].strPath[0] = 0;
      lpPsInfo[ulIndex].strName[0] = 0;
      
      // Because Can't Open 0 And 8 Process,
      // Mark Them At There 
      if ( 0 == lpdwPIDs[ulIndex] ) {

         strcpy( lpPsInfo[ulIndex].strName, "System Idle Process" );
         continue;
      }
      else if ( 8 == lpdwPIDs[ulIndex] ) {

         strcpy( lpPsInfo[ulIndex].strName, "System" );
         continue;
      }

      // Open Process And Get Process Infomation
		hProcess = OpenProcess(
							PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
							FALSE, lpPsInfo[ulIndex].dwPID );
		if( hProcess != NULL )
		{
			// Here we call EnumProcessModules to get only the
			// first module in the process this is important,
			// because this will be the .EXE module for which we
			// will retrieve the full path name in a second.
			if( EnumProcessModules( hProcess, &hModule,
						sizeof(hModule), &dwSize ) ) {

				// Get Full pathname:
				if( GetModuleFileNameEx( hProcess, hModule, 
                     path_buffer, sizeof(path_buffer) ) ) {
               
               _tsplitpath( path_buffer, drive, dir, fname, ext );               
               strcpy( lpPsInfo[ulIndex].strPath, path_buffer );
               sprintf( lpPsInfo[ulIndex].strName, "%s%s", fname, ext );
//               TRACE( "ModuleFileName:%s\r\n", path_buffer );
				}
			}
			CloseHandle( hProcess ) ;
		}
	}	

	return TRUE;
}

BOOL KillProcess( DWORD dwPID )
// 杀掉指定的进程
// 要杀掉的进程的ID
{
	HANDLE hProcess = ::OpenProcess( PROCESS_TERMINATE, FALSE, dwPID );

	if( hProcess != NULL ) {

		if ( ::TerminateProcess( hProcess, 0 ) ) {

			::CloseHandle( hProcess );
			return TRUE;
		}
		else {
			::CloseHandle( hProcess );
		}
	}
	return FALSE;
}

//- 获取指定进程的模块列表
BOOL EnumProcessModulesInfo( DWORD dwPID, MODULEINFO *lpModInfo, 
									  DWORD dwSize, DWORD *lpdwNeeded )
//- lpModInfo [out] :	指向MODULEINFO结构数组的指针
//- dwSize [in] :			lpPsInfo中的元素个数
//- lpdwNeeded [out] :	实际的元素个数
//- 返回值 : TRUE : 成功; FALSE : 失败
{
//	ASSERT( dwPID );
	ASSERT( lpdwNeeded );

	// Because Can't Open 0 And 8 Process, Mark Them At There 
	if ( 0 == dwPID || 8 == dwPID ) {
		*lpdwNeeded = 0;
		return FALSE;
	}
	
	// It's Only Two Way To Call This Function,
	// Query Module Count Or Get Module List.
	BOOL IsQueryCount;
	if ( NULL != lpdwNeeded && NULL == lpModInfo && 0 == dwSize ) {
		IsQueryCount = TRUE;
	} 
	else if ( NULL != lpdwNeeded && NULL != lpModInfo && 0 != dwSize ) {
		IsQueryCount = FALSE;
	}
	else {
		return FALSE;
	}

	// Open Process And Get Process Infomation
	HANDLE hProcess = OpenProcess(
					PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
					FALSE, dwPID );
	
	if( hProcess == NULL ) {
		return FALSE;
	}
	
	DWORD dwCountByte;
	if( IsQueryCount ) { //if Query Modules Count
	
		BOOL bResult = EnumProcessModules( hProcess, NULL, 0, &dwCountByte );
		*lpdwNeeded = dwCountByte / sizeof(DWORD);
		CloseHandle( hProcess );
		return bResult;
	}


	//Get Modules Info 
	if ( EnumProcessModules( hProcess, NULL, 0, &dwCountByte ) ) {

		(*lpdwNeeded) = dwCountByte / sizeof(DWORD);
		HMODULE *lphMddule = new HMODULE[*lpdwNeeded];
		if ( NULL == lphMddule ) {
			CloseHandle( hProcess );
			return FALSE;
		}
				
		if ( ! EnumProcessModules( hProcess, lphMddule, 
					(*lpdwNeeded)*sizeof(DWORD), &dwCountByte ) ) {

			delete[] lphMddule;
			CloseHandle( hProcess );
			return FALSE;
		}

		char path_buffer[_MAX_PATH];
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
					
		for ( ULONG IndexMod = 0; IndexMod < (*lpdwNeeded); IndexMod++ ) {

			// Get Full pathname:
			if( GetModuleFileNameEx( hProcess, lphMddule[IndexMod], 
						path_buffer, sizeof(path_buffer) ) ) {
				
				_tsplitpath( path_buffer, drive, dir, fname, ext );               
				strcpy( lpModInfo[IndexMod].strPath, path_buffer );
				sprintf( lpModInfo[IndexMod].strName, "%s%s", fname, ext );
			}
			else {

				lpModInfo[IndexMod].strPath[0] = 0;
				lpModInfo[IndexMod].strName[0] = 0;
			}
		}

		delete[] lphMddule;
	}

	CloseHandle( hProcess );
	return TRUE;
}



