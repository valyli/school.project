//����Ե�Driver�̣߳����ڻ�ȡ�ͻ�������

//��ѭ���������ش��߳�
//����ֵ0��ʾ����
//1��ʾ�ɹ�
DWORD WINAPI DriverProc(LPVOID lpParameter)
{
	//��̬����CClientModuleTransfer.dll
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

	//��ȡClientTransferModuleByTLV()����ָ��
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

	//��ͣ��ѭ�����ӿͻ��˲�ѯ����
	while(1)
	{
		//���û�ȡ��Ϣ�����Ŀ
		//��ʱ��ʼ
		ModuleInfo.InfomationElementTableID = 1;
		ModuleInfo.InfomationElementID = 1;
		//��ʱ����

		//����ClientTransferModuleByTLV()��������ȡ����
		flag = (*lpfn)(ModuleInfo, TLVData);
		if(flag)
		{
			printf("ClientTransferModuleByTLV() Success.");
			//��TLVData����Data_Buff����
			for(i = 0; i < sizeof(TLVStruct); i++)
			{
				Data_Buff[i] = ((SMM_UCHAR*)&TLVData)[i];
			}
			//�����ݼ������
			//����������������ֵ-3�����ȴ�����д��
			while(ITDQ_Write(iID[0],Data_Buff) == -3)
			{
				//�ȴ�500����
				Sleep(500);
			}
		}
	}
	return 1;
}