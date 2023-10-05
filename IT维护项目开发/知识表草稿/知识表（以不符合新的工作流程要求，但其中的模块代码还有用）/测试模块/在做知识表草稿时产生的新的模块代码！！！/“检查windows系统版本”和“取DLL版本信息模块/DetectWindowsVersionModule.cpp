//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@�淶���ƣ�DetectWindowsVersionModule
@ģ�����ƣ�Windows����ϵͳ�汾���ģ��
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h��Version.lib
@���ߣ����
@���ڣ�2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************

		//~~~~~~~~~~~~~Define WindowsSystemVersionType_DetectWindowsVersionModule~~~~~~~~~~~~~~
		//����ϵͳ���ͱ�����ö������
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
@�������ܣ����Windows����ϵͳ�汾
@����Դ��WINAIP
@������
		strWin32SysType		CString		�����ͣ��ɷ��ز���ϵͳ����
@����ֵ���壺���ز���ϵͳ����
@�漰���Զ������ͣ�
		WindowsSystemVersionType_DetectWindowsVersionModule
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h
@��ע
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
@�������ܣ���⶯̬��汾
@����Դ��WINAIP
@������
		strDLLFilePath		CString		DLL������·�����ļ���
@����ֵ���壺��̬��汾��Ϣ�ṹ��
@�漰���Զ������ͣ�
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h��Version.lib
@��ע������ֵ�Ľṹ���е�dwFileVersionMS�ĸߵ�16λ��dwFileVersionLS�ĸߵ�16λ��10���Ʒֱ��ʾ��
		���ɰ��汾�ŵ�4�α�׼��ʾ
---------------------------------------------------------------------------------------------*/
VS_FIXEDFILEINFO DetectDLLVersion_DetectWindowsVersionModule(CString strDLLFilePath)
{
	VS_FIXEDFILEINFO Translate;
	//��ȡ�����Դ�ռ�Ĵ�С
	DWORD dwLen;
	LPVOID lpData;
	dwLen = ::GetFileVersionInfoSize(strDLLFilePath.GetBuffer(strDLLFilePath.GetLength()), 0);
	//�ж�GetFileVersionInfoSize�Ƿ�ɹ�
	if(dwLen == 0)//ʧ��
	{
		::MessageBox(0, "Error for GetFileVersionInfoSize()", "", MB_OK);
		return Translate;
	}
	else
	{
		//����Ű汾��Դ�Ŀռ�
		lpData = new char[dwLen];
		
		//��ȡ�汾��Ϣ
		//��ʧ��
		if( FALSE == ::GetFileVersionInfo(strDLLFilePath.GetBuffer(strDLLFilePath.GetLength()), 0, dwLen, lpData))
		{
			delete[] lpData;
			::MessageBox(0, "Error for GetFileVersionInfo()", "", MB_OK);
			return Translate;
		}
		else
		{
			//������Ż�ȡ�汾��Ϣ�Ŀռ�
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
