// TestDlgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"
#include "Base.h"
#include "test.h"
#include "smm_type.h"
#include "smm_api.cpp"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define   Data_Size        1024
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlgDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlgDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DRIVERDATA,OnDriverData)
	ON_MESSAGE(WM_DRIVER2DATA,OnDriver2Data)
	ON_MESSAGE(WM_COMDATA,OnComData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg message handlers
SMM_INT iID[4];









CArrayCycleStruct m_CArrayCycleStruct;
HMODULE hLibrary;




//��ѵ�һ��//////////////////
DWORD WINAPI DriverProc(
  LPVOID lpParameter   // thread data
)
{

	HWND  hwnd=((DriverParam*)lpParameter)->hwnd;

	//11111111111111111111
	//����CClientModuleTransfer.dll
	CString strDllFilePath = "CClientModuleTransfer.dll";
	hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return -1;
	}

	//22222222222
	//��ȡ��ǰĿ¼�µ����кϷ���̬�������Ϣ
	//����ClientGetAllModuleInfoToMemory()
	bool (FAR *lpfn_1)();
	lpfn_1 = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientGetAllModuleInfoToMemory");
	if(lpfn_1 == NULL)
	{
		AlarmErrorMessage("Get Function ClientGetAllModuleInfoToMemory() Failed", "Load Library Error");
		return -1;
	}
	bool flag = (*lpfn_1)();
	if(!flag)
	{
		::MessageBox(0, "ClientGetAllModuleInfoToMemory() Failed", "CClientTransferModuleDemoDlg", MB_OK);
		return -1;
	}

	//33333333333333333
	Transfer_S2C_Struct m_S2C;
	Transfer_C2S_Struct m_C2S;

	CManageData Data;
	TLVStruct TLVData;
	SMM_UCHAR Data_Buff[Data_Size];
	COleDateTime m_Time;
	ModuleInfomationListStruct ModuleInfo;


ModuleInfo.InfomationElementTableID = 0;
	while(1)
	{
		Sleep(500);

		//����Ҫ��ȡ����Ϣ��id

		
		//�ɴ˻��ָ��
		//���û�ȡ��Ϣ�����Ŀ
		//��ʱ��ʼ
		if(ModuleInfo.InfomationElementTableID == 1)
			ModuleInfo.InfomationElementTableID = 2;
		else if(ModuleInfo.InfomationElementTableID == 2)
			ModuleInfo.InfomationElementTableID = 3;
		else if(ModuleInfo.InfomationElementTableID == 3)
			ModuleInfo.InfomationElementTableID = 1;
		else if(ModuleInfo.InfomationElementTableID == 0)
			ModuleInfo.InfomationElementTableID = 4;
		else if(ModuleInfo.InfomationElementTableID == 4)
			ModuleInfo.InfomationElementTableID = 1;

		ModuleInfo.InfomationElementID = 1;

		if(ModuleInfo.InfomationElementTableID == 4)
			m_S2C.Cycle = 5;
		else
			m_S2C.Cycle = 0;

		//��ʱ����

		m_S2C.InfoBaseID.InfomationElementTableID = ModuleInfo.InfomationElementTableID;
		m_S2C.InfoBaseID.InfomationElementID = ModuleInfo.InfomationElementID;


		ModuleInfo.InfomationElementTableID = m_S2C.InfoBaseID.InfomationElementTableID;
		ModuleInfo.InfomationElementID = m_S2C.InfoBaseID.InfomationElementID;

		//����ѭ������ֱ�ӵ���
		if(m_S2C.Cycle == 0)
		{
			bool (FAR *lpfn_2)(ModuleInfomationListStruct &ModuleInfo, TLVStruct& TLVData);
			lpfn_2 = (bool (__cdecl *)(struct ModuleInfomationListStruct&, struct TLVStruct&))GetProcAddress(hLibrary, "ClientTransferModuleByTLV");
			if(lpfn_2 == NULL)
			{
				AlarmErrorMessage("Get Function ClientTransferModuleByTLV() Failed", "Load Library Error");
				return -1;
			}
			flag = (*lpfn_2)(ModuleInfo, TLVData);
			if(!flag)
			{
				::MessageBox(0, "ClientTransferModuleByTLV() Failed", "", MB_OK);
				return -1;
			}
			//����õĽ������m_C2S
			Data.SetDatabyTLV(TLVData);
			Data.GetDatabyTLV(m_C2S.Value);
			m_C2S.InfoBaseID.InfomationElementTableID = m_S2C.InfoBaseID.InfomationElementTableID;
			m_C2S.InfoBaseID.InfomationElementID = m_S2C.InfoBaseID.InfomationElementID;
			strcpy(m_C2S.LocalTime, m_Time.GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"));

			//��TLVData����Data_Buff����
			for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
			{
				Data_Buff[i] = ((SMM_UCHAR*)&m_C2S)[i];
			}
			while((ITDQ_Write(iID[0],(SMM_UCHAR*)Data_Buff)) == -3)
				Sleep(500);
			PostMessage(hwnd,WM_DRIVERDATA,0,(LPARAM)(SMM_UCHAR*)Data_Buff);
		}
		//ѭ��������m_CArrayCycleStruct�ȴ�����
		else
		{
			CycleStruct m_temp;
			m_temp.LastTransferTime = m_Time.GetCurrentTime();
			for(int t = 0; t < sizeof(Transfer_S2C_Struct); t++)
			{
				((unsigned char*)&(m_temp.TransferData))[t] = ((unsigned char*)&(m_S2C))[t];
			}

			//4444444444444444444
			//����Ҫ���õĶ�̬�⣬��ȡҪ���õĺ�����ַ
			//����LoadClientTransferModuleAndFounctionHandleByCManageData()
			bool (FAR *lpfn_2c)(ModuleInfomationListStruct &ModuleInfo);
			lpfn_2c = (bool (__cdecl *)(struct ModuleInfomationListStruct&))GetProcAddress(hLibrary, "LoadClientTransferModuleAndFounctionHandleByCManageData");
			if(lpfn_2c == NULL)
			{
				AlarmErrorMessage("Get Function LoadClientTransferModuleAndFounctionHandleByCManageData() Failed", "Load Library Error");
				return -1;
			}
			flag = (*lpfn_2c)(ModuleInfo);
			if(!flag)
			{
				::MessageBox(0, "LoadClientTransferModuleAndFounctionHandleByCManageData() Failed", "", MB_OK);
				return -1;
			}


			//5555555555555
			//��ȡ����Ҫ���õĶ�̬���hModule��lpfnR
			void (FAR *lpfn_3)(HMODULE& hLibrary, bool (FAR*& lpfounction)(CManageData &Data));
			lpfn_3 = (void (__cdecl *)(HMODULE& , bool (FAR*& )(CManageData &Data)))GetProcAddress(hLibrary, "GetModuleHandleAndFunctionAddress");
			if(lpfn_3 == NULL)
			{
				AlarmErrorMessage("Get Function GetModuleHandleAndFunctionAddress() Failed", "Load Library Error");
				return -1;
			}
			(*lpfn_3)(m_temp.hLibrary, m_temp.lpfn);
			
			
			
			m_CArrayCycleStruct.Add(m_temp);

		}
	}

}


//��ѵڶ����߳�//////////////////
DWORD WINAPI Driver2Proc(
  LPVOID lpParameter   // thread data
)
{
	HWND  hwnd=((DriverParam*)lpParameter)->hwnd;

	COleDateTime cur_Time, temp;

	while(1)
	{
		for(int i = 0; i < m_CArrayCycleStruct.GetSize(); i++)
		{
			cur_Time = cur_Time.GetCurrentTime();
			//delete item when time out.
////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if(0)//cur_Time > m_CArrayCycleStruct[i].TransferData.EndTime)
			{
				//777777777777
				//�ͷŶ�̬��
				//����FreeClientTransferModule()
				void (FAR *lpfn_5t)(HMODULE hModule);
				lpfn_5t = (void (__cdecl *)(HMODULE))GetProcAddress(hLibrary, "FreeClientTransferModule");
				if(lpfn_5t == NULL)
				{
					AlarmErrorMessage("Get Function FreeClientTransferModule() Failed", "Load Library Error");
					return -1;
				}
				(*lpfn_5t)(m_CArrayCycleStruct[i].hLibrary);

				//�ͷŵ���ģ��
				FreeLibrary(hLibrary);

				CArrayCycleStruct m_temp_Array;
				int t = 0;
				for(int j = 0; j < m_CArrayCycleStruct.GetSize(); j++)
				{
					if(j != i)
					{
						m_temp_Array.SetAt(t, m_CArrayCycleStruct.GetAt(j));
						t++;
					}
				}
				m_CArrayCycleStruct.RemoveAll();
				for(j = 0; j < m_temp_Array.GetSize(); j++)
				{
					m_CArrayCycleStruct.SetAt(j, m_temp_Array.GetAt(j));
				}
				i--;
				continue;
			}
////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			else if(0)//(cur_Time - m_CArrayCycleStruct[i].LastTransferTime) < m_CArrayCycleStruct[i].TransferData.Cycle)
				continue;

			//5555555555555
			//����Ҫ���õĶ�̬���hModule��lpfnR
			void (FAR *lpfn_3)(HMODULE hLibrary, bool (FAR* lpfounction)(CManageData &Data));
			lpfn_3 = (void (__cdecl *)(HMODULE , bool (FAR* )(CManageData &Data)))GetProcAddress(hLibrary, "SetModuleHandleAndFunctionAddress");
			if(lpfn_3 == NULL)
			{
				AlarmErrorMessage("Get Function SetModuleHandleAndFunctionAddress() Failed", "Load Library Error");
				return -1;
			}
			(*lpfn_3)(m_CArrayCycleStruct[i].hLibrary, m_CArrayCycleStruct[i].lpfn);


		
		
			//���û�ȡ��Ϣ��ģ��
			bool (FAR *lpfn_4)(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
			lpfn_4 = (bool (__cdecl *)(struct ModuleInfomationListStruct&, class CManageData&))GetProcAddress(hLibrary, "CallClientTransferModuleByCManageData");
			if(lpfn_4 == NULL)
			{
				AlarmErrorMessage("Get Function CallClientTransferModuleByCManageData() Failed", " Error");
				return -1;
			}
			else
			{
				Transfer_C2S_Struct m_C2S;

				CManageData Data;
				SMM_UCHAR Data_Buff[Data_Size];
				COleDateTime m_Time;

				//�ɴ˻��ָ��
				m_C2S.InfoBaseID.InfomationElementTableID = m_CArrayCycleStruct[i].TransferData.InfoBaseID.InfomationElementTableID;
				m_C2S.InfoBaseID.InfomationElementID = m_CArrayCycleStruct[i].TransferData.InfoBaseID.InfomationElementID;

				//����Ҫ��ȡ����Ϣ��id
				ModuleInfomationListStruct ModuleInfo;

				ModuleInfo.InfomationElementTableID = m_C2S.InfoBaseID.InfomationElementTableID;
				ModuleInfo.InfomationElementID = m_C2S.InfoBaseID.InfomationElementID;

				Data.SetDatabyTLV(m_CArrayCycleStruct[i].TransferData.Value);
				bool flag = (*lpfn_4)(ModuleInfo, Data);
				if(!flag)
				{
					::MessageBox(0, "CallClientTransferModuleByCManageData() Failed", "", MB_OK);
					return -1;
				}

				//����õĽ������m_C2S
				Data.GetDatabyTLV(m_C2S.Value);
				m_C2S.InfoBaseID.InfomationElementTableID = ModuleInfo.InfomationElementTableID;
				m_C2S.InfoBaseID.InfomationElementID = ModuleInfo.InfomationElementID;
				strcpy(m_C2S.LocalTime, m_Time.GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"));

				//��TLVData����Data_Buff����
				for(int i = 0; i < sizeof(Transfer_C2S_Struct); i++)
				{
					Data_Buff[i] = ((SMM_UCHAR*)&m_C2S)[i];
				}
				while((ITDQ_Write(iID[0],(SMM_UCHAR*)Data_Buff)) == -3)
					Sleep(500);
				PostMessage(hwnd,WM_DRIVER2DATA,0,(LPARAM)(SMM_UCHAR*)Data_Buff);

			}
		}
		Sleep(1000);
	}
	return 1;
}












///////////////////////////////////////////////////////
//������߳�////////////////////////////////////////
DWORD WINAPI ComProc(
  LPVOID lpParameter   // thread data
)
{

HWND  hwnd=((DriverParam*)lpParameter)->hwnd;

 //((CListBox*)::GetDlgItem(hwnd, IDC_LIST2))->InsertString(0,"connect");
	int n = 0;
    SMM_INT       iSocket ;
	SMM_ULONG     ulreturn ;
    SMM_UCHAR pcBuffer[1024] ={'\0'}  ;
    SMM_UCHAR cRecv[1024]={'\0'} ;
	SMM_UCHAR pcIP[15] ={'\0'}  ;
    SMM_INT iRecv = 0 ;
    SMM_INT  iRead  ;   
	SMM_INT  iWrite ;
    SMM_INT  iCount = 0 ;   //������:���ڼ��ط�����
    //����
      SMM_INT i = 0 ;

	//(1)��ʼ��
	ulreturn = SC_init() ; 
	//(2)�����׽���
    iSocket = SC_socket(AF_INET,SOCK_STREAM
		,SC_VERIFY_YES,SC_ENCRYPT_NO,SC_CLIENT_YES,SC_SSLV3) ;
	//printf("SC_socket=%d\n",iSocket) ; //����:��ʾsocket
 //   ::MessageBox(0, "", "q", MB_OK	);
    //(3)���ӷ�����
    //strcpy(pcIP,"127.0.0.1");  //���Ա���
 //   strcpy(pcIP,"192.168.1.152");
	memcpy(pcIP,(SMM_UCHAR*)"192.168.1.152",19);
//	::MessageBox(0, "", "b", MB_OK	);
//	memcpy(pcIP,(SMM_UCHAR*)"127.0.0.1 ",19);

    ulreturn = SC_connect(iSocket,(SMM_CHAR*)pcIP,5000);
//::MessageBox(0, "", "c", MB_OK	);
//	char buff[100];
// ::MessageBox(0, itoa(ulreturn, buff, 10), "", MB_OK);
	//printf("SC_connect=%d",ulreturn) ;     //����:��ʾconnect��������ֵ

	//����:�����Ƿ������
   // ulreturn = SC_queryarray(iSocket) ;
	//printf("socketclient=%d",stSSLSocket[ulreturn].s) ;
//	recv(stSSLSocket[ulreturn].s,cRecv,sizeof(iRecv),0);
    //printf("recv=%s",iRecv) ;

    //(3-2)�õ�����ip��ַ��ʹ��


    //(4)��������
	//strcpy(pcBuffer,"A hello\0") ;

    //(4-1)��������ѭ��������
	/*SMM_INT y  ;
	while (1)
    {
	   
        itoa(i,pcBuffer,10);
		strcat(pcBuffer,"A-") ;
	//	printf("pcBuffer=%s\n",pcBuffer) ;
		y = i % 100 ;
		if (y == 0)
		{
		  ulreturn = SC_send(iSocket,pcBuffer,sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
	      printf("SC_send=%d\n",ulreturn) ;  //����
		}

		i++ ;
	} */ //���Է����ַ���
	
    //(4-2)���Է����ļ�
   /* FILE* lfile = fopen("abc.txt","rt") ;
	while (!feof(lfile))
	{
       fread(pcBuffer,sizeof(pcBuffer),1,lfile);
	   ulreturn = SC_send(iSocket,pcBuffer,sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
	   printf("SC_send=%s\n",pcBuffer) ;  //����
	   //strcat(pcbuf,buf) ;
	}

    fclose(lfile);*/

 //((CListBox*)::GetDlgItem(hwnd, IDC_LIST2))->InsertString(0,"111111");
//::MessageBox(0, "", "d", MB_OK	);
	//(4-3)���ԴӶ��ж�������
	while (1)
	{
		::MessageBox(0, "bc", "", MB_OK	);
         iRead=ITDQ_Read(iID[0],pcBuffer);
		 if (iRead == -4)  //-4:��ʾ����Ϊ��
		 {
              Sleep(500) ;
		 }
		 else
		 {
			 //printf("iRead1=%s\n",((Transfer_C2S_Struct*)pcBuffer)->Value.Value.Value_char);
	         ulreturn=SC_send(iSocket,pcBuffer,sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
	         //printf("SC_send=%d\n",ulreturn) ;
		 }
	     
		 ulreturn = SC_recv(iSocket,cRecv,sizeof(cRecv),SC_TCP_YES,NULL,&iRecv,SC_CLIENT_YES) ;
//	char buff[100];
 //::MessageBox(0, (char*)cRecv/*itoa(, buff, 10)*/, "", MB_OK);
//		 printf("recv=%s",cRecv) ;

         if (strcmp((char *)cRecv,"RECV_ERR") == 0)
		 {
			 while (strcmp((char *)cRecv,"RECV_ERR") == 0 && iCount < SC_REPEAT)  //����������ʧ��,Ҫ���ط�����
			 {  
				iCount++ ;
				SC_send(iSocket,pcBuffer,sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
				SC_recv(iSocket,cRecv,sizeof(cRecv),SC_TCP_YES,NULL,&iRecv,SC_CLIENT_YES) ;
			 }
		 }
		 else
		 {
			 if (strcmp((char *)cRecv,"RECV_GOOD") != 0)   //���յ�������������
			 {
			     printf("SC_recv=%d,%s\n",ulreturn,cRecv) ; //����
			     iWrite = ITDQ_Write(iID[1],cRecv) ;
			     if (iWrite == -3)  //�������� (�Ժ󲹳�)
				 {
                     //�Ժ󲹳�
				 }
			 }
		 }
	}
	//(5)��������
	/*ulreturn = SC_recv(iSocket,cRecv,sizeof(cRecv),SC_TCP_YES,NULL,&iRecv,SC_CLIENT_YES) ;
	printf("SC_recv=%d,%s\n",ulreturn,cRecv) ; */ //����  
	//(6)�ر�
	ulreturn = SC_close(iSocket,SD_NO,0) ;    
	printf("SC_close=%d",ulreturn) ;        //����
	
	return 1;




/*

	HWND  hwnd=((ComParam*)lpParameter)->hwnd;
	SMM_UCHAR *pcBuffer=(SMM_UCHAR*)malloc(Data_Size);

	while (1)
	{
         if((ITDQ_Read(iID[0],pcBuffer)) == -4)
		 {
			 Sleep(500);
			 continue;
		 }
		 PostMessage(hwnd,WM_COMDATA,0,(LPARAM)pcBuffer);
	}
	  
	return 1;*/
}

BOOL CTestDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon	
	// TODO: Add extra initialization here
	InitCreate();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestDlgDlg::InitCreate()
{
	ITDQ_Init();
	iID[0]=ITDQ_Create(0,5);
	iID[1]=ITDQ_Create(0,5);
}

int CTestDlgDlg::OnButton1() 
{
	DriverParam *pDriver=new DriverParam;
	pDriver->hwnd=m_hWnd;
	CreateThread(NULL,1,&DriverProc,(LPVOID)pDriver,0,NULL);
	Driver2Param *pDriver2=new Driver2Param;
	pDriver2->hwnd=m_hWnd;
	CreateThread(NULL,1,&Driver2Proc,(LPVOID)pDriver2,0,NULL);
	return 1;
}

void CTestDlgDlg::OnDriverData(WPARAM wParam,LPARAM lParam)
{	
	SMM_UCHAR *Data_Buff1=(SMM_UCHAR*)lParam;
	Transfer_C2S_Struct* m_Data = (Transfer_C2S_Struct*)Data_Buff1;
	if(m_Data->Value.Type == long_Value)
	{
		char buff[100];
		((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(0,itoa(m_Data->Value.Value.Value_long, buff, 10));
	}
	else if(m_Data->Value.Type == CString_Value)
	{
		((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(0, m_Data->Value.Value.Value_char);
	}
//	((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(0,((TLVStruct*)Data_Buff1)->Value.Value_char);
}

void CTestDlgDlg::OnComData(WPARAM wParam,LPARAM lParam)
{
	SMM_UCHAR *Data_Buff1=(SMM_UCHAR*)lParam;
	Transfer_C2S_Struct* m_Data = (Transfer_C2S_Struct*)Data_Buff1;
	if(m_Data->Value.Type == long_Value)
	{
		char buff[100];
		((CListBox*)GetDlgItem(IDC_LIST2))->InsertString(0,itoa(m_Data->Value.Value.Value_long, buff, 10));
	}
	else if(m_Data->Value.Type == CString_Value)
	{
		((CListBox*)GetDlgItem(IDC_LIST2))->InsertString(0, m_Data->Value.Value.Value_char);
	}
}

int CTestDlgDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	ComParam    *pCom =new ComParam;
	pCom->hwnd=m_hWnd;
	CreateThread(NULL,1,&ComProc,(LPVOID)pCom,0,NULL);
	return 1;
}

void CTestDlgDlg::OnDriver2Data(WPARAM wParam,LPARAM lParam)
{
	SMM_UCHAR *Data_Buff1=(SMM_UCHAR*)lParam;
	Transfer_C2S_Struct* m_Data = (Transfer_C2S_Struct*)Data_Buff1;
	if(m_Data->Value.Type == long_Value)
	{
		char buff[100];
		((CListBox*)GetDlgItem(IDC_LIST3))->InsertString(0,itoa(m_Data->Value.Value.Value_long, buff, 10));
	}
	else if(m_Data->Value.Type == CString_Value)
	{
		((CListBox*)GetDlgItem(IDC_LIST3))->InsertString(0, m_Data->Value.Value.Value_char);
	}
}




/*	//��̬����CClientModuleTransfer.dll
	HWND  hwnd=((DriverParam*)lpParameter)->hwnd;
	CString strDllFilePath = "CClientModuleTransfer.dll";
	HMODULE hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		printf("Error: Load Library Failed.\n");
		return 0;
	}

	//��ȡClient�˻�ȡ��Ϣ�Ķ�̬��ģ���������Ϣ
	bool (FAR *lpfn_ClientGetAllModuleInfoToMemory)();
	lpfn_ClientGetAllModuleInfoToMemory = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientGetAllModuleInfoToMemory");
	if(lpfn_ClientGetAllModuleInfoToMemory == NULL)
	{
		printf("Error: Get Function ClientGetAllModuleInfoToMemory() Failed.\n");
		return 0;
	}
	bool flag = (*lpfn_ClientGetAllModuleInfoToMemory)();
	if(!flag)
	{
		printf("Error: ClientGetAllModuleInfoToMemory() Failed.\n");
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
	int i;

	ModuleInfo.InfomationElementTableID = 1;
	//��ͣ��ѭ�����ӿͻ��˲�ѯ����
	while(1)
	{
		//���û�ȡ��Ϣ�����Ŀ
		//��ʱ��ʼ
		if(ModuleInfo.InfomationElementTableID == 1)
			ModuleInfo.InfomationElementTableID = 2;
		else if(ModuleInfo.InfomationElementTableID == 2)
			ModuleInfo.InfomationElementTableID = 3;
		else if(ModuleInfo.InfomationElementTableID == 3)
			ModuleInfo.InfomationElementTableID = 1;

		ModuleInfo.InfomationElementID = 1;

		//��ʱ����

		//����ClientTransferModuleByTLV()��������ȡ����
		flag = (*lpfn)(ModuleInfo, TLVData);
		if(flag)
		{
			//��TLVData����Data_Buff����
			for(i = 0; i < sizeof(TLVStruct); i++)
			{
				Data_Buff[i] = ((SMM_UCHAR*)&TLVData)[i];
			}
			//�����ݼ������
			//����������������ֵ-3�����ȴ�����д��
		//	ITDQ_Write(iID[0],Data_Buff);
		//	m_list.InsertString(0,((TLVStruct*)Data_Buff)->Value.Value_Char);
			
			while((ITDQ_Write(iID[0],Data_Buff)) == -3)
			{	
				{
					Sleep(500);
				}	
			}
			PostMessage(hwnd,WM_DRIVERDATA,0,(LPARAM)Data_Buff);
		}
	}
	FreeLibrary(hLibrary);
	return 1;
	*/
















/*
	//���������ģ��
	CString strDllFilePath = "CClientModuleTransfer.dll";
	hLibrary=LoadLibrary(strDllFilePath);
	CString temp;
	if(hLibrary == NULL)
	{
		temp = "Load ";
		temp += strDllFilePath;
		temp += "Failed";
		return -1;
	}

	//��ȡ��ǰĿ¼�µ����кϷ���̬�������Ϣ
	//����ClientGetAllModuleInfoToMemory()
	bool (FAR *lpfn_1)();
	lpfn_1 = (bool (__cdecl *)())GetProcAddress(hLibrary, "ClientGetAllModuleInfoToMemory");
	if(lpfn_1 == NULL)
	{
		AlarmErrorMessage("Get Function ClientGetAllModuleInfoToMemory() Failed", "Load Library Error");
		return -1;
	}
	bool flag = (*lpfn_1)();
	if(!flag)
	{
		::MessageBox(0, "ClientGetAllModuleInfoToMemory() Success", "CClientTransferModuleDemoDlg", MB_OK);
		return -1;
	}

	//�����ȡCPU��Ϣ�Ķ�̬��
	ModuleInfomationListStruct ModuleInfo;
	//���û�ȡCPUʹ������Ϣ����Ϣ��ֵ
	ModuleInfo.InfomationElementTableID = 4;
	ModuleInfo.InfomationElementID = 1;

	//����LoadClientTransferModuleAndFounctionHandleByCManageData()
	bool (FAR *lpfn_2)(ModuleInfomationListStruct &ModuleInfo);
	lpfn_2 = (bool (__cdecl *)(struct ModuleInfomationListStruct&))GetProcAddress(hLibrary, "LoadClientTransferModuleAndFounctionHandleByCManageData");
	if(lpfn_2 == NULL)
	{
		AlarmErrorMessage("Get Function LoadClientTransferModuleAndFounctionHandleByCManageData() Failed", "Load Library Error");
		return -1;
	}
	flag = (*lpfn_2)(ModuleInfo);
	if(!flag)
	{
		::MessageBox(0, "LoadClientTransferModuleAndFounctionHandleByCManageData() Failed", "", MB_OK);
		return -1;
	}


	//�ݴ�Ҫ���õĶ�̬��͵��ú����ľ��
	HMODULE hModule;
	bool (FAR *lpfnR)(CManageData &Data);

	
	//��ȡhModule��lpfnR
	void (FAR *lpfn_3)(HMODULE& hLibrary, bool (FAR*& lpfounction)(CManageData &Data));
	lpfn_3 = (void (__cdecl *)(HMODULE& , bool (FAR*& )(CManageData &Data)))GetProcAddress(hLibrary, "GetModuleHandleAndFunctionAddress");
	if(lpfn_3 == NULL)
	{
		AlarmErrorMessage("Get Function GetModuleHandleAndFunctionAddress() Failed", "Load Library Error");
		return -1; 
	}
	(*lpfn_3)(hModule, lpfnR);


	//���û�ȡCPU��Ϣ��ģ��
	bool (FAR *lpfn_4)(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
	lpfn_4 = (bool (__cdecl *)(struct ModuleInfomationListStruct&, class CManageData&))GetProcAddress(hLibrary, "CallClientTransferModuleByCManageData");
	if(lpfn_4 == NULL)
	{
		AlarmErrorMessage("Get Function CallClientTransferModuleByCManageData() Failed", " Error");
		return -1;
	}
	else
	{
		CManageData Data;
		TLVStruct TLVData;
		Transfer_S2C_Struct ;
		SMM_UCHAR Data_Buff[Data_Size];
		//����10��
//		for(int j = 0; j < 10; j++)
		while(1)
		{
			flag = (*lpfn_4)(ModuleInfo, Data);
			Data.GetDatabyTLV(TLVData);
			if(!flag)
			{
				::MessageBox(0, "CallClientTransferModuleByCManageData() Failed", "", MB_OK);
				return -1;
			}


			//��TLVData����Data_Buff����
			for(int i = 0; i < sizeof(TLVStruct); i++)
			{
				Data_Buff[i] = ((SMM_UCHAR*)&TLVData)[i];
			}
			while((ITDQ_Write(iID[0],(SMM_UCHAR*)Data_Buff)) == -3)
			{	
					Sleep(500);
			}
			PostMessage(hwnd,WM_DRIVERDATA,0,(LPARAM)(SMM_UCHAR*)Data_Buff);

		}
	}


	//����FreeClientTransferModule()
	void (FAR *lpfn_5)(HMODULE hModule);
	lpfn_5 = (void (__cdecl *)(HMODULE))GetProcAddress(hLibrary, "FreeClientTransferModule");
	if(lpfn_5 == NULL)
	{
		AlarmErrorMessage("Get Function FreeClientTransferModule() Failed", "Load Library Error");
		return -1;
	}
	(*lpfn_5)(hModule);

*/
