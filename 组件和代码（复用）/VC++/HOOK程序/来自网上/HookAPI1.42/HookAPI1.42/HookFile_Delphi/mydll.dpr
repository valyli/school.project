//�鿴VC�еİ����е�File Functions

library mydll;

uses
  SysUtils, Types, Windows,WinSock,
  Classes;

type
  TMyAPIInfo = record
  module_name,func, myfunc_name:PChar;
  end;
{$R *.res}
var
  myapi_info:array[1..5] of TMyAPIInfo;

function mySetCurrentDirectoryA(dir:PChar):DWORD;stdcall;
var
  ret:LongBool;
  //err:integer;
begin
  MessageBox(0, dir, 'mySetCurrentDirectory...', MB_OK);
  ret :=SetCurrentDirectoryA(dir);
  //err =GetLastError();
  //�����Լ��Ĵ���
  //SetLastError(err);
  result :=DWORD(ret);
end;

function mySetCurrentDirectoryW(dir:PWChar):DWORD;stdcall;
var
  ret:LongBool;
  //err:integer;
begin
  MessageBoxW(0, dir, 'mySetCurrentDirectoryW...', MB_OK);
  ret :=SetCurrentDirectoryW(dir);
  //err =GetLastError();
  //�����Լ��Ĵ���
  //SetLastError(err);
  result :=DWORD(ret);
end;

// ��Win32�У�OpenFile��CreateFile���棬���Դ��ļ�ʱʵ���ϵ�����CreateFile
function myOpenFile(fname:PChar; pofs:POFSTRUCT; style:UINT):DWORD;stdcall;
var
  ret:HFILE;
  //err:integer;
begin
  MessageBox(0, fname, 'myOpenFile...', MB_OK);
  ret :=OpenFile(fname, pofs^, style);
  //err =GetLastError();
  //�����Լ��Ĵ���
  //SetLastError(err);
  Result := ret;
end;

function myCreateFileA(fname:PChar;dwDesiredAccess:DWORD;dwShareMod:DWORD;lpSecurityAttributes:PSecurityAttributes;dwCreationDisposition:DWORD;dwFlagsAndAttributes:DWORD;hTemplateFile:HFILE):DWORD;stdcall;
var
  ret:HFILE;
  //err:integer;
begin
  MessageBox(0, fname, 'myCreateFileA...', MB_OK);
  ret :=CreateFileA(fname, dwDesiredAccess, dwShareMod, lpSecurityAttributes,
		dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
  //err =GetLastError();
  //�����Լ��Ĵ���
  //SetLastError(err);
  Result := ret;
end;
Function GetMyAPIInfo():Pointer;stdCall;
begin
	GetMyAPIInfo :=Addr(myapi_info);
end;

exports
  GetMyAPIInfo,
  mySetCurrentDirectoryA,
  mySetCurrentDirectoryW,
  myOpenFile,
  myCreateFileA;

begin
  myapi_info[1].module_name :='KERNEL32.DLL';
  myapi_info[1].func :='SetCurrentDirectoryA(a)';
  myapi_info[1].myfunc_name :='mySetCurrentDirectoryA';
  myapi_info[2].module_name :='KERNEL32.DLL';
  myapi_info[2].func :='OpenFile(a,b,c)';
  myapi_info[2].myfunc_name :='myOpenFile';
  myapi_info[3].module_name :='KERNEL32.DLL';
  myapi_info[3].func :='OpenFile(a,b,c)';
  myapi_info[3].myfunc_name :='myOpenFile';
  myapi_info[4].module_name :='KERNEL32.DLL';
  myapi_info[4].func :='CreateFileA(1,2,3,4,5,6,7)';
  myapi_info[4].myfunc_name :='myCreateFileA';
  myapi_info[5].module_name :=nil;
  myapi_info[5].func :=nil;
  myapi_info[5].myfunc_name :=nil;
end.


