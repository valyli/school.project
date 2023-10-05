#ifndef _INSTHOOK_H_
#define _INSTHOOK_H_

int InitHookAPI();
int HookAllProcesses();
int HookAllProcesses2(int msec);
int UnhookAllProcesses();
int HookProcess(DWORD process_id);
int UnhookProcess(DWORD process_id);

#endif
