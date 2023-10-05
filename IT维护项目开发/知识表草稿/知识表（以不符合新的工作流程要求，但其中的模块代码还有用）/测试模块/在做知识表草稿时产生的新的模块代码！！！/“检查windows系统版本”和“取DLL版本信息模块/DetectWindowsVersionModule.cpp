//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@规范名称：DetectWindowsVersionModule
@模块名称：Windows操作系统版本检测模块
@需引入的文件（.h、.lib、.dll等）:stdafx.h、Version.lib
@作者：李佳
@日期：2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************

		//~~~~~~~~~~~~~Define WindowsSystemVersionType_DetectWindowsVersionModule~~~~~~~~~~~~~~
		//声明系统类型变量的枚举类型
		typedef enum tagWindowsSystemVersionType_DetectWindowsVersionModule
		{
			Windows32s,
			WindowsNT3,
			Windows95,
			Windows98,
			WindowsME,
			WindowsNT4,
			Windows2000,
			WindowsXP
		}WindowsSystemVersionType_DetectWindowsVersionModule;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~End Define~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

***********************************  Type Define Stop  ***************************************/



//*********************************  Function Define Start  ***********************************

//$$$$ DetectWindowsVersion_DetectWindowsVersionModule()
/*----------------------------------  Fouction Information  -----------------------------------
@函数功能：检测Windows操作系统版本
@数据源：WINAIP
@参数：
		strWin32SysType		CString		引用型，可返回操作系统名称
@返回值含义：返回操作系统类型
@涉及的自定义类型：
		WindowsSystemVersionType_DetectWindowsVersionModule
@需引入的文件（.h、.lib、.dll等）:stdafx.h
@备注
---------------------------------------------------------------------------------------------*/
WindowsSystemVersionType_DetectWindowsVersionModule DetectWindowsVersion_DetectWindowsVersionModule(CString &strWindowsSystemName)
{
	WindowsSystemVersionType_DetectWindowsVersionModule  ShellType;
	DWORD winVer;
	OSVERSIONINFO *osvi;
	
	winVer=::GetVersion();
	if(winVer<0x80000000){	/*NT */
		ShellType=WindowsNT3;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL){
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			::GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L)
				ShellType=WindowsNT4;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==0L)
				ShellType=Windows2000;
			else if(osvi->dwMajorVersion==5L&&osvi->dwMinorVersion==1L)
				ShellType=WindowsXP;
			free(osvi);
		}
	}
	else if  (LOBYTE(LOWORD(winVer))<4)
		ShellType=Windows32s;
	else{
		ShellType=Windows95;
		osvi= (OSVERSIONINFO *)malloc(sizeof(OSVERSIONINFO));
		if (osvi!=NULL){
			memset(osvi,0,sizeof(OSVERSIONINFO));
			osvi->dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
			GetVersionEx(osvi);
			if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==10L)
				ShellType=Windows98;
			else if(osvi->dwMajorVersion==4L&&osvi->dwMinorVersion==90L)
				ShellType=WindowsME;
			free(osvi);
		}
	}

	switch(ShellType)
	{
	case Windows32s:
		strWindowsSystemName = "Windows32s";
		break;
	case WindowsNT3:
		strWindowsSystemName = "WindowsNT3";
		break;
	case Windows95:
		strWindowsSystemName = "Windows95";
		break;
	case Windows98:
		strWindowsSystemName = "Windows98";
		break;
	case WindowsME:
		strWindowsSystemName = "WindowsME";
		break;
	case WindowsNT4:
		strWindowsSystemName = "WindowsNT4";
		break;
	case Windows2000:
		strWindowsSystemName = "Windows2000";
		break;
	case WindowsXP:
		strWindowsSystemName = "WindowsXP";
		break;
	default:
		strWindowsSystemName = "Unknown";
	}

	return ShellType;
}



//$$$$ DetectDLLVersion_DetectWindowsVersionModule()
/*----------------------------------  Fouction Information  -----------------------------------
@函数功能：检测动态库版本
@数据源：WINAIP
@参数：
		strDLLFilePath		CString		DLL的完整路径和文件名
@返回值含义：动态库版本信息结构体
@涉及的自定义类型：
@需引入的文件（.h、.lib、.dll等）:stdafx.h、Version.lib
@备注：返回值的结构体中的dwFileVersionMS的高低16位和dwFileVersionLS的高低16位用10进制分别表示，
		即可按版本号的4段标准显示
---------------------------------------------------------------------------------------------*/
VS_FIXEDFILEINFO DetectDLLVersion_DetectWindowsVersionModule(CString strDLLFilePath)
{
	VS_FIXEDFILEINFO Translate;
	//获取相关资源空间的大小
	DWORD dwLen;
	LPVOID lpData;
	dwLen = ::GetFileVersionInfoSize(strDLLFilePath.GetBuffer(strDLLFilePath.GetLength()), 0);
	//判断GetFileVersionInfoSize是否成功
	if(dwLen == 0)//失败
	{
		::MessageBox(0, "Error for GetFileVersionInfoSize()", "", MB_OK);
		return Translate;
	}
	else
	{
		//开存放版本资源的空间
		lpData = new char[dwLen];
		
		//获取版本信息
		//若失败
		if( FALSE == ::GetFileVersionInfo(strDLLFilePath.GetBuffer(strDLLFilePath.GetLength()), 0, dwLen, lpData))
		{
			delete[] lpData;
			::MessageBox(0, "Error for GetFileVersionInfo()", "", MB_OK);
			return Translate;
		}
		else
		{
			//声明存放获取版本信息的空间
			VS_FIXEDFILEINFO *lpTranslate;
			UINT cbTranslate = sizeof(lpTranslate);
			VerQueryValue(lpData,
				TEXT("\\"),
				(LPVOID*)&lpTranslate,
				&cbTranslate);

			Translate.dwFileDateLS = lpTranslate->dwFileDateLS;
			Translate.dwFileDateMS = lpTranslate->dwFileDateMS;
			Translate.dwFileFlags = lpTranslate->dwFileFlags;
			Translate.dwFileFlagsMask = lpTranslate->dwFileFlagsMask;
			Translate.dwFileOS = lpTranslate->dwFileOS;
			Translate.dwFileSubtype = lpTranslate->dwFileSubtype;
			Translate.dwFileType = lpTranslate->dwFileType;
			Translate.dwFileVersionLS = lpTranslate->dwFileVersionLS;
			Translate.dwFileVersionMS = lpTranslate->dwFileVersionMS;
			Translate.dwProductVersionLS = lpTranslate->dwProductVersionLS;
			Translate.dwProductVersionMS = lpTranslate->dwProductVersionMS;
			Translate.dwSignature = lpTranslate->dwSignature;
			Translate.dwStrucVersion = lpTranslate->dwStrucVersion;

			delete[] lpData;

			return Translate;
		}
	}
}


//*********************************  Function Define Stop  ************************************

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Stop  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
