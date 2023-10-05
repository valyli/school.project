//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@�淶���ƣ�DetectHardwareModule
@ģ�����ƣ�BIOS��Ϣ���ģ��
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h
@���ߣ����
@���ڣ�2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************
***********************************  Type Define Stop  ***************************************/



//*********************************  Function Define Start  ***********************************

//$$$$ DetectBIOS_DetectHardwareModule()
/*----------------------------------  Fouction Information  -----------------------------------
@�������ܣ����BIOS��Ϣ
@����Դ�����ֱ��ȡ��Ӳ��������Ϊ��������
@������
		BIOS_ID		CString		�����ͣ��ɷ���BIOS�����к�
		BIOS_Type	CString		�����ͣ��ɷ���BIOS������
		BIOS_Date	CString		�����ͣ��ɷ���BIOS������
@����ֵ���壺�����Ƿ�ɹ�
@�漰���Զ������ͣ�
@��������ļ���.h��.lib��.dll�ȣ�:stdafx.h��BiosId.Lib��BiosId.H��BiosId.Dll
@��ע
---------------------------------------------------------------------------------------------*/
BOOL DetectBIOS_DetectHardwareModule(CString &BIOS_ID, CString &BIOS_Type, CString &BIOS_Date)
{
	char buff[256];
	if(!GetBiosId(buff))
		return FALSE;
	BIOS_ID = buff;
	if(!GetBiosType(buff))
		return FALSE;
	BIOS_Type = buff;
	if(!GetBiosDate(buff))
		return FALSE;
	BIOS_Date = buff;
	return TRUE;
}

//*********************************  Function Define Stop  ************************************

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Stop  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
