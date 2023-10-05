//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  Module Start  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*--------------------------------  Module Infomation  ----------------------------------------
@规范名称：DetectHardwareModule
@模块名称：BIOS信息检测模块
@需引入的文件（.h、.lib、.dll等）:stdafx.h
@作者：李佳
@日期：2003-03-13
----------------------------------------------------------------------------------------------/



/*********************************  Type Define Start  ****************************************
***********************************  Type Define Stop  ***************************************/



//*********************************  Function Define Start  ***********************************

//$$$$ DetectBIOS_DetectHardwareModule()
/*----------------------------------  Fouction Information  -----------------------------------
@函数功能：检测BIOS信息
@数据源：汇编直接取自硬件，核心为网上下载
@参数：
		BIOS_ID		CString		引用型，可返回BIOS的序列号
		BIOS_Type	CString		引用型，可返回BIOS的类型
		BIOS_Date	CString		引用型，可返回BIOS的日期
@返回值含义：返回是否成功
@涉及的自定义类型：
@需引入的文件（.h、.lib、.dll等）:stdafx.h、BiosId.Lib、BiosId.H、BiosId.Dll
@备注
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
