// ------------------------------------- //
// 您如果要使用本文件，请不要删除本说明  //
// ------------------------------------- //
//             HOOKAPI v1.0              //
//   Copyright 2002 编程沙龙 Paladin     //
//       www.ProgramSalon.com            //
// ------------------------------------- //

#ifndef __mydll_h__
#define __mydll_h__

typedef struct
{
	char *module_name;
	char *function_name;
	char *myfunc_name;
}MYAPIINFO;

int HookAPI_AddFilter(int type, void *pfilter);
int HookAPI_InsertFilter(int pos, int type, void *filter);
int HookAPI_DeleteFilter(int pos);
int HookAPI_DeleteAllFilter();

#define WSH_NOTIFY_BIND                 0x01
#define WSH_NOTIFY_LISTEN               0x02
#define WSH_NOTIFY_CONNECT              0x04
#define WSH_NOTIFY_ACCEPT               0x08
#define WSH_NOTIFY_SHUTDOWN_RECEIVE     0x10
#define WSH_NOTIFY_SHUTDOWN_SEND        0x20
#define WSH_NOTIFY_SHUTDOWN_ALL         0x40
#define WSH_NOTIFY_CLOSE                0x80
#define WSH_NOTIFY_CONNECT_ERROR        0x100

typedef int (WINAPI *WSHOPENSOCKET)(int *, int *, int *, LPWSTR, LPVOID *, LPDWORD);
typedef int (WINAPI *WSHOPENSOCKET2)(int *, int *, int *, int, int, LPWSTR, LPVOID *, LPDWORD);
typedef int (WINAPI *WSHNOTIFY)(LPVOID, int, HANDLE, HANDLE, DWORD);

#endif
