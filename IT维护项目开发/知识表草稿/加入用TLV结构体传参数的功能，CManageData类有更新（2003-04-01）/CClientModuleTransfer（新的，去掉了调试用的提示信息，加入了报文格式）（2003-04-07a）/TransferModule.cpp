// TransferModule.cpp: implementation of the CTransferModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TransferModule.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransferModule::CTransferModule()
{
//	//��Client�˼�⵱ǰĿ¼�����кϷ�dll����Ϣ
//	GetAllModuleInfoToMemory();
}

CTransferModule::~CTransferModule()
{

}

//���ö�̬����ֻ࣬������ʾ
bool CTransferModule::TransferModule(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//ModuleInfo��ֻʹ��InfomationElementTableID��InfomationElementIDֵ�������ǽ��бȽ���
	//�ȽϽ������������ݶ���Դ��Client�˶�������ݣ���m_InfoArray��
	//���ж��ڿͻ����ڴӵ�ǰĿ¼�л�ȡ�Ĳ��������Ƿ������Ҫ���õķ���
	for(int i = 0; i < m_InfoArray.GetSize(); i++)
	{
		if(m_InfoArray.GetAt(i).InfomationElementTableID == ModuleInfo.InfomationElementTableID
			&& m_InfoArray.GetAt(i).InfomationElementID == ModuleInfo.InfomationElementID)
			break;
	}
	//���û����Ӧ�ķ���
	if(i >= m_InfoArray.GetSize())
	{
//		::MessageBox(0, "ServiceFileName is not Find", "CTransferModule", MB_OK);
		return false;
	}
/*	else
	{
		::MessageBox(0, m_InfoArray.GetAt(i).ServiceFileName, "ServiceFileName is Find", MB_OK);
	}
*/
	CString temp;
	bool flag;

	//���붯̬��
	HMODULE hLibrary=LoadLibrary(m_InfoArray.GetAt(i).ServiceFileName);
	//������ʧ��
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += m_InfoArray.GetAt(i).ServiceFileName;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}

	//����ָ�붨��
	//��lpfn���庯��ָ��
	//����Ҫ�󣬺���ָ��ķ���ֵ����bool��
	bool (FAR *lpfn)(CManageData &Data);

	//�Ӷ�̬���л�ȡҪ���õķ���
	lpfn = (bool (__cdecl *)(CManageData&))GetProcAddress(hLibrary, m_InfoArray.GetAt(i).InterfaceFunction);
	//��ȡʧ��
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function Failed", "Load Library Error");
	}
	else
	{
		//���ö�̬����ָ���ķ���
		flag = (*lpfn)(Data);


		//�ͷŶ�̬��
		FreeLibrary(hLibrary);

	}
	return true;
}



//�ڵ�ǰĿ¼���������еĺϷ�dll��Ϣ����¼��m_InfoArray
bool CTransferModule::GetAllModuleInfoToMemory()
{
	m_InfoArray.RemoveAll();
	//���ҵ�ǰĿ¼�µ�����dll�ļ�
	_finddata_t FileInfo;
	int n = 0;
	long cur_n;
	int SizeOfArray;
	int i;
	ModuleInfomationStruct m_Info;
	ModuleInfomationListStruct m_InfoStruct;

	cur_n = _findfirst("*.dll", &FileInfo);
	//�Ե�һ��dll�ļ����д���
	if(FileInfo.attrib != FILE_ATTRIBUTE_DIRECTORY && cur_n != -1L)
	{
			m_Info.ListArray.RemoveAll();
			if(GetInfoListFromDll(m_Info, FileInfo.name))
			{
//				::MessageBox(0, "�Ϸ��ļ����ɹ�������Ϣ", FileInfo.name, MB_OK);
				//���Ϊ�Ϸ�dll������Ϣ�������������
				for(i = 0; i < m_Info.ListArray.GetSize(); i++)
				{
					m_InfoStruct = m_Info.ListArray.GetAt(i);
					SizeOfArray = m_InfoArray.GetSize();
					//�������ò���ID����1��
					m_InfoStruct.OperationID = SizeOfArray + 1;
					m_InfoArray.Add(m_InfoStruct);
				}
			}
/*			else
			{
				::MessageBox(0, "���ǺϷ��ļ�", FileInfo.name, MB_OK);
			}
*/	}
	//�Ժ����ҵ���dll�ļ����д���
	while(_findnext(cur_n, &FileInfo) == 0)
	{
		//����ΪĿ¼ʱ�����ļ�
		if(FileInfo.attrib != FILE_ATTRIBUTE_DIRECTORY)
		{
//			::MessageBox(0, FileInfo.name, "", MB_OK);
			m_Info.ListArray.RemoveAll();
			if(GetInfoListFromDll(m_Info, FileInfo.name))
			{
//				::MessageBox(0, "�Ϸ��ļ����ɹ�������Ϣ", FileInfo.name, MB_OK);
				//���Ϊ�Ϸ�dll������Ϣ�������������
				for(i = 0; i < m_Info.ListArray.GetSize(); i++)
				{
					m_InfoStruct = m_Info.ListArray.GetAt(i);
					SizeOfArray = m_InfoArray.GetSize();
					//�������ò���ID����1��
					m_InfoStruct.OperationID = SizeOfArray + 1;
					m_InfoArray.Add(m_InfoStruct);
				}
			}
/*			else
			{
				::MessageBox(0, "���ǺϷ��ļ�", FileInfo.name, MB_OK);
			}
*/		}
	}
	return true;
}



//��ȡdll��Ϣ������m_Info����
//strDllFilePathΪ��̬���ȫ·��
bool CTransferModule::GetInfoListFromDll(ModuleInfomationStruct &m_Info, CString strDllFilePath)
{
	CString temp;

	bool (FAR *lpfn)(ModuleInfomationStruct &InfoList);


	HMODULE hLibrary=LoadLibrary(strDllFilePath);
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}
	lpfn = (bool (__cdecl *)(ModuleInfomationStruct&))GetProcAddress(hLibrary, "InfoList");
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
	}

	bool flag = (*lpfn)(m_Info);

	FreeLibrary(hLibrary);
	return true;
}