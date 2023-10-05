//给徐辉的Driver线程，用于获取客户端数据

//死循环，不返回此线程
//返回值0表示错误，
//1表示成功
DWORD WINAPI DriverProc(LPVOID lpParameter)
{
	//动态导入CClientModuleTransfer.dll
	CString strDllFilePath = "CClientModuleTransfer.dll";
	hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		printf("Error: Load Library Failed.\n");
		return 0;
	}

	//获取ClientTransferModuleByTLV()函数指针
	bool (FAR *lpfn)(ModuleInfomationListStruct &ModuleInfo, TLVStruct &TLVData);
	lpfn = (bool (__cdecl *)(struct ModuleInfomationListStruct &,struct TLVStruct &))GetProcAddress(hLibrary, "ClientTransferModuleByTLV");
	if(lpfn == NULL)
	{
		printf("Error: Get Function ClientTransferModuleByTLV() Failed.\n");
		return 0;
	}

	ModuleInfomationListStruct ModuleInfo;
	TLVStruct TLVData;
	SMM_UCHAR Data_Buff[Data_Size];
	bool flag;
	int i;

	//不停的循环，从客户端查询数据
	while(1)
	{
		//设置获取信息项的条目
		//临时开始
		ModuleInfo.InfomationElementTableID = 1;
		ModuleInfo.InfomationElementID = 1;
		//临时结束

		//调用ClientTransferModuleByTLV()函数，获取数据
		flag = (*lpfn)(ModuleInfo, TLVData);
		if(flag)
		{
			printf("ClientTransferModuleByTLV() Success.");
			//将TLVData传入Data_Buff数组
			for(i = 0; i < sizeof(TLVStruct); i++)
			{
				Data_Buff[i] = ((SMM_UCHAR*)&TLVData)[i];
			}
			//将数据加入队列
			//若队列已满（返回值-3），等待继续写入
			while(ITDQ_Write(iID[0],Data_Buff) == -3)
			{
				//等待500毫秒
				Sleep(500);
			}
		}
	}
	return 1;
}