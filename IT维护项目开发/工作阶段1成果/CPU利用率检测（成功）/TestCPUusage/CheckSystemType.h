// CheckSystemType.h: interface for the CCheckSystemType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKSYSTEMTYPE_H__F14CD49D_0869_4907_8FD6_E16ACE6D06BA__INCLUDED_)
#define AFX_CHECKSYSTEMTYPE_H__F14CD49D_0869_4907_8FD6_E16ACE6D06BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//声明系统类型变量的枚举类型
typedef enum tagWin32SysType
{
	Windows32s,
	WindowsNT3,
	Windows95,
	Windows98,
	WindowsME,
	WindowsNT4,
	Windows2000,
	WindowsXP
}Win32SysType;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class CCheckSystemType  
{
public:
	Win32SysType IsShellSystemType(CString& strWin32SysType);
	CCheckSystemType();
	virtual ~CCheckSystemType();

};

#endif // !defined(AFX_CHECKSYSTEMTYPE_H__F14CD49D_0869_4907_8FD6_E16ACE6D06BA__INCLUDED_)
