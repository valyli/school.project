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
	lpfn = NULL;
	hLibrary = NULL;
}

CTransferModule::~CTransferModule()
{

}

//��ȡ��̬��ľ����Ҫ���õĺ����ľ��
//��������ڴ���Ϣ�������false
bool CTransferModule::LoadTransferModuleAndFounctionHandleByCManageData(ModuleInfomationListStruct &ModuleInfo)
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
		return false;
	}
	CString temp;

	//���붯̬��
	hLibrary=LoadLibrary(m_InfoArray.GetAt(i).ServiceFileName);
	//������ʧ��
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += m_InfoArray.GetAt(i).ServiceFileName;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}

	//�Ӷ�̬���л�ȡҪ���õķ���
	lpfn = (bool (__cdecl *)(CManageData&))GetProcAddress(hLibrary, m_InfoArray.GetAt(i).InterfaceFunction);
	//��ȡʧ��
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function Failed", "Load Library Error");
	}
	else
		return true;
}


//���ö�̬���еķ���
bool CTransferModule::CallTransferModule(ModuleInfomationListStruct &ModuleInfo, CManageData& Data)
{
	//�����ȡ����ָ��ʧ��
	if(lpfn == NULL)
	{
		FreeLibrary(hLibrary);
		return false;//AlarmErrorMessage("Get Function Failed", "Load Library Error");
	}
	else
	{
		//���ö�̬����ָ���ķ���
		bool flag = (*lpfn)(Data);
		return flag;
	}
}


//�ͷŶ�̬��
void CTransferModule::FreeTransferModule()
{
	lpfn = NULL;
	FreeLibrary(hLibrary);
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

	bool (FAR *lpfn_t)(ModuleInfomationStruct &InfoList);


	HMODULE hLibrary_t=LoadLibrary(strDllFilePath);
	if(hLibrary_t == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return false;//AlarmErrorMessage(temp, "Load Library Error");
	}
	lpfn_t = (bool (__cdecl *)(ModuleInfomationStruct&))GetProcAddress(hLibrary_t, "InfoList");
	if(lpfn_t == NULL)
	{
		FreeLibrary(hLibrary_t);
		return false;//AlarmErrorMessage("Get Function 'InfoList()' Failed", "Load Library Error");
	}

	bool flag = (*lpfn_t)(m_Info);

	FreeLibrary(hLibrary_t);
	return true;
}