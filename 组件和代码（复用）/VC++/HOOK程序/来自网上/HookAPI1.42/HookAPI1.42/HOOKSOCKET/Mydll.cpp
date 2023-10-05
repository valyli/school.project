// ------------------------------------- //
// 您如果要使用本文件，请不要删除本说明  //
// ------------------------------------- //
//             HOOKAPI 开发例子          //
//   Copyright 2002 编程沙龙 Paladin     //
//       www.ProgramSalon.com            //
// ------------------------------------- //

#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <lmcons.h>
#include <lmalert.h>
#include "mydll.h"
#include <nb30.h>
#include "util.h"

char g_szDllPath[128];
HINSTANCE g_hInstance;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	if(ul_reason_for_call =DLL_PROCESS_ATTACH)
	{
		GetProfileString("HookAPI", "dll_path", "", g_szDllPath, sizeof(g_szDllPath));
	}

	return TRUE;
}

int GetLocalPortBySocket(SOCKET s)
{
	struct sockaddr name;
	int namelen =sizeof(name);

	getsockname(s, &name, &namelen);
	return ntohs(((struct sockaddr_in *)&name)->sin_port);
}

int GetLocalIPBySocket(SOCKET s, char *ip)
{
	struct sockaddr name;
	int namelen =sizeof(name);

	getsockname(s, &name, &namelen);
	strcpy(ip, inet_ntoa(((struct sockaddr_in *)&name)->sin_addr));
	return 0;
}

int GetRemotePortBySocket(SOCKET s)
{
	struct sockaddr name;
	int namelen =sizeof(name);

	getpeername(s, &name, &namelen);
	return ntohs(((struct sockaddr_in *)&name)->sin_port);
}

int GetRemoteIPBySocket(SOCKET s, char *ip)
{
	struct sockaddr name;
	int namelen =sizeof(name);

	getpeername(s, &name, &namelen);
	strcpy(ip, inet_ntoa(((struct sockaddr_in *)&name)->sin_addr));
	return 0;
}

int WINAPI mysocket(int af, int type, int protocol)
{
	WriteLog("mysocket, af=%d, type=%d, protocol=%d", af, type, protocol);

	return socket(af, type, protocol);
}

struct hostent * WINAPI mygethostbyname (const char * name)
{
	// filter IE url
	WriteLog("gethostbyname:name:%s", name);
	return gethostbyname(name);
}

int WINAPI myaccept(SOCKET s, struct sockaddr *pname, int *pnamelen)
{
	WriteLog("myaccept");
	int port =GetLocalPortBySocket(s);

	int s1 =accept(s, pname, pnamelen);

	if(s1 >0)
	{
		// check filter 
	}

	return s1;
}

int WINAPI myconnect(SOCKET s, struct sockaddr *name, int namelen)
{
	WriteLog("myconnect");
	struct sockaddr_in *paddr =(struct sockaddr_in *)name;

	char *ip =inet_ntoa(paddr->sin_addr);
	int port =ntohs(paddr->sin_port);
	WriteLog("connect: ip=%s, port=%d\n", ip, port);
	// check filter
	return connect(s, name, namelen);
}

int WINAPI myrecv(SOCKET s,	char *buf, int len, int flags)
{
	WriteLog("\nmyrecv");

	int recved_len =recv(s, (char *)buf, len, flags);
	int err;

	if(recved_len <=0) err =WSAGetLastError();

	if(recved_len >0)
	{
		int port =GetLocalPortBySocket(s);
		int port1 =GetRemotePortBySocket(s);
		char ip[16];
		GetRemoteIPBySocket(s, ip);
	}
	
	if(recved_len <=0) WSASetLastError(err);

	return recved_len;
}

int WINAPI mysend(SOCKET s,	char *buf, int len,	int flags)
{
	int ret;

	WriteLog("mysend");

	int port =GetLocalPortBySocket(s);
	int port1 =GetRemotePortBySocket(s);
	char ip[16];

	GetRemoteIPBySocket(s, ip);

	// crypted data...

	ret =send(s, (char *)buf, len, flags);
	
	int err;
	if(ret <=0) err =WSAGetLastError();
	// other process...
	if(ret <=0) WSASetLastError(err);
	
	return ret;
}

int WINAPI mysendto (SOCKET s, char FAR * buf, int len, int flags, struct sockaddr FAR * to, int tolen)
{
	WriteLog("mysendto");
	return sendto(s, buf, len, flags, to, tolen);
}

int WINAPI myrecvfrom (SOCKET s, char FAR * buf, int len, int flags, struct sockaddr FAR * from, int *fromlen)
{
	WriteLog("myrecvfrom");
	return recvfrom(s, buf, len, flags, from, fromlen);
}

MYAPIINFO myapi_info[] =
{
	{"WSOCK32.DLL", "socket(a,b,c)", "mysocket"},
	{"WSOCK32.DLL", "accept(a,b,c)", "myaccept"},
	{"WSOCK32.DLL", "connect(SOCKET, struct sockaddr *, INT)", "myconnect"},
	{"WSOCK32.DLL", "recv(INT, char *, INT, INT)", "myrecv"},
	{"WSOCK32.DLL", "send(INT, char *, INT, INT)", "mysend"},
	{"WSOCK32.DLL", "sendto(INT, char *, INT, INT, struct sockaddr *, int)", "mysendto"},
	{"WSOCK32.DLL", "recvfrom(INT, char *, INT, INT, struct sockaddr *, int)", "myrecvfrom"},
	{"WSOCK32.DLL", "gethostbyname(char *)", "mygethostbyname"},
	{NULL,NULL,NULL}
};

MYAPIINFO *GetMyAPIInfo()
{
	return &myapi_info[0];
}

