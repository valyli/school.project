// TestDlgDlg.cpp : implementation file
//
#include "stdafx.h"
#include "TestDlg.h"
#include "TestDlgDlg.h"
#include "Base.h"
#include "test.h"
#include "smm_type.h"
#include "smm_api.cpp"
#define  USE_SSL   0    //1:使用SSL 0:不使用SSL
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
struct MessageParam							//传给线程函数的结构体
{
	HWND    hwnd;
};

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
	m_check1 = TRUE;
	m_check2 = TRUE;
	m_check3 = TRUE;
	m_check4 = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlgDlg)
	DDX_Check(pDX, IDC_CHECK1, m_check1);
	DDX_Check(pDX, IDC_CHECK2, m_check2);
	DDX_Check(pDX, IDC_CHECK3, m_check3);
	DDX_Check(pDX, IDC_CHECK4, m_check4);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_IP, OnIp)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_CHECK2, OnCheck2)
	ON_BN_CLICKED(IDC_CHECK3, OnCheck3)
	ON_BN_CLICKED(IDC_CHECK4, OnCheck4)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_DRIVERDATA,OnDriverData)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg message handlers
SMM_INT iID[4];
/*全局变量定义*/
CArrayCycleStruct m_CArrayCycleStruct;
HMODULE hLibrary;
SMM_UCHAR pcIP[15] ={'\0'}  ;//IP地址变量

BOOL Threadcheck1;
BOOL Threadcheck2;
BOOL Threadcheck3;
BOOL Threadcheck4;
HANDLE hComThread;
/*********************************************************
  Function:       checkTest()
  Description:    将各个控件变量赋值给定义的全局变量
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
					


  Output:         
  Return:         
				  

  Others:        
***********************************************************/
SMM_VOID CTestDlgDlg::checkTest()
{
	Threadcheck1=this->m_check1;	
	Threadcheck2=this->m_check2;
	Threadcheck3=this->m_check3;
	Threadcheck4=this->m_check4;
}
SMM_VOID CTestDlgDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here	
	UpdateData();
	if((this->m_check1) == FALSE)
	{
		MessageBox("操作系统版本号将不发送","警告",MB_OK|MB_ICONWARNING);
	}
	Threadcheck1=this->m_check1;
}

SMM_VOID CTestDlgDlg::OnCheck2() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if((this->m_check2) == FALSE)
	{
		MessageBox("BIOS序列号将不发送","警告",MB_OK|MB_ICONWARNING);
	}
	Threadcheck2=this->m_check2;
}

SMM_VOID CTestDlgDlg::OnCheck3() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if((this->m_check3) == FALSE)
	{
		MessageBox("用户注册信息将不发送","警告",MB_OK|MB_ICONWARNING);
	}
	Threadcheck3=this->m_check3;
}

SMM_VOID CTestDlgDlg::OnCheck4() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if((this->m_check4) == FALSE)
	{
		MessageBox("CPU利用率将不发送","警告",MB_OK|MB_ICONWARNING);
	}
	Threadcheck4=this->m_check4;
}
/*********************************************************
  Function:       Check()
  Description:    检索用户的控制选项
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:           iTableID :InfobaseTableID
				   iElementID:InfobaseElementID
				   hwnd		:窗口ID
						
  Output:         
  Return:         
				  

  Others:        
***********************************************************/
SMM_BOOL  Check(SMM_INT iTableID,SMM_INT iElementID,HWND hwnd)
{
	MessageParam *pMessage = new MessageParam;
	hwnd=pMessage->hwnd;
	if(iTableID == 1 &&  iElementID==1  &&  Threadcheck1 ==TRUE)
	{
		return TRUE;
	}
	else if(iTableID == 2 &&  iElementID == 1  &&  Threadcheck2 == TRUE)
	{
		return TRUE;
	}
	else if(iTableID == 3 &&  iElementID == 1  &&  Threadcheck3 == TRUE)
	{
		return TRUE;
	}
	else if(iTableID == 4 &&  iElementID == 1  &&  Threadcheck4 == TRUE)
	{
		return TRUE;
	}
	else if(iTableID == 5 &&  iElementID == 1  &&  Threadcheck4 == TRUE)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

//DRIVER线程//////////////////
DWORD WINAPI DriverProc(
  LPVOID lpParameter   // thread data
)
{

	HWND  hwnd=((MessageParam*)lpParameter)->hwnd;
	//11111111111111111111
	//导入CClientModuleTransfer.dll
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
	//获取当前目录下的所有合法动态库操作信息
	//调用ClientGetAllModuleInfoToMemory()
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
		Sleep(1000);
		//设置要获取的信息项id
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		       /*判断用户是否控制发送选项*/
		
	if(ITDQ_Read(iID[1],Data_Buff) != -4 )
	{
			/*模拟服务器设置频次的指令*/
		if(((Transfer_S2C_Struct *)Data_Buff)->InfoBaseID.InfomationElementTableID == 1)
			((Transfer_S2C_Struct *)Data_Buff)->Cycle = 1;

		else if(((Transfer_S2C_Struct *)Data_Buff)->InfoBaseID.InfomationElementTableID == 2)
			((Transfer_S2C_Struct *)Data_Buff)->Cycle = 1;

		else if(((Transfer_S2C_Struct *)Data_Buff)->InfoBaseID.InfomationElementTableID == 3)
			((Transfer_S2C_Struct *)Data_Buff)->Cycle = 1;
			
		else if(((Transfer_S2C_Struct *)Data_Buff)->InfoBaseID.InfomationElementTableID == 4)
			((Transfer_S2C_Struct *)Data_Buff)->Cycle = 1;

		else if(((Transfer_S2C_Struct *)Data_Buff)->InfoBaseID.InfomationElementTableID == 5)
			((Transfer_S2C_Struct *)Data_Buff)->Cycle = 1;

		else
			((Transfer_S2C_Struct *)Data_Buff)->Cycle = 0;
		
		for(SMM_UINT s = 0; s < sizeof(Transfer_S2C_Struct); s++)
		{
			((SMM_UCHAR*)&(m_S2C))[s] = ((SMM_UCHAR*)&(Data_Buff))[s];			
		}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//----------------------------------------------------------------------------------------
		//设置获取信息项的条目
		//临时开始
/*		if(ModuleInfo.InfomationElementTableID == 1)
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

		//临时结束

		m_S2C.InfoBaseID.InfomationElementTableID = ModuleInfo.InfomationElementTableID;
		m_S2C.InfoBaseID.InfomationElementID = ModuleInfo.InfomationElementID;*/
//----------------------------------------------------------------------------------------

			ModuleInfo.InfomationElementTableID = m_S2C.InfoBaseID.InfomationElementTableID;
			ModuleInfo.InfomationElementID = m_S2C.InfoBaseID.InfomationElementID;
			//不用循环处理，直接调用
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
				//将获得的结果导入m_C2S
				Data.SetDatabyTLV(TLVData);
				Data.GetDatabyTLV(m_C2S.Value);
				m_C2S.InfoBaseID.InfomationElementTableID = m_S2C.InfoBaseID.InfomationElementTableID;
				m_C2S.InfoBaseID.InfomationElementID = m_S2C.InfoBaseID.InfomationElementID;
				strcpy(m_C2S.LocalTime, m_Time.GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"));

				//将TLVData传入Data_Buff数组
				for(SMM_UINT i = 0; i < sizeof(Transfer_C2S_Struct); i++)
				{
					Data_Buff[i] = ((SMM_UCHAR*)&m_C2S)[i];
				}
				BOOL bCheck1;
				bCheck1 = Check(m_C2S.InfoBaseID.InfomationElementTableID,m_C2S.InfoBaseID.InfomationElementID,hwnd);
				if(bCheck1 == FALSE)
				{
					continue;
				}
				else
				{
					if(ITDQ_Write(iID[0],(SMM_UCHAR*)Data_Buff) == -3 )
					{
					  Sleep(1000);
					}
					PostMessage(hwnd,WM_DRIVERDATA,0,(LPARAM)Data_Buff);
				}	
			}
			//循环，加入m_CArrayCycleStruct等待处理
			else
			{
				CycleStruct m_temp;
				m_temp.LastTransferTime = m_Time.GetCurrentTime();
				for(SMM_UINT t = 0; t < sizeof(Transfer_S2C_Struct); t++)
				{
					((unsigned char*)&(m_temp.TransferData))[t] = ((unsigned char*)&(m_S2C))[t];
				}

				//4444444444444444444
				//导入要调用的动态库，获取要调用的函数地址
				//调用LoadClientTransferModuleAndFounctionHandleByCManageData()
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
				//获取导入要调用的动态库的hModule和lpfnR
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
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

////////////Driver2/////////////////////////////////////////////////////////////////////////

		COleDateTime cur_Time, temp;
		Transfer_C2S_Struct m_C2S;

		CManageData Data;
		SMM_UCHAR Data_Buff[Data_Size];
		COleDateTime m_Time;
		//设置要获取的信息项id
		ModuleInfomationListStruct ModuleInfo;
		CArrayCycleStruct m_temp_Array;
		
		for(int i = 0; i < m_CArrayCycleStruct.GetSize(); i++)
		{
			cur_Time = cur_Time.GetCurrentTime();
			//delete item when time out.
////////////////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//结束条件判断
			if(0)//cur_Time > m_CArrayCycleStruct[i].TransferData.EndTime)
			{
				//777777777777
				//释放动态库
				//调用FreeClientTransferModule()
				void (FAR *lpfn_5t)(HMODULE hModule);
				lpfn_5t = (void (__cdecl *)(HMODULE))GetProcAddress(hLibrary, "FreeClientTransferModule");
				if(lpfn_5t == NULL)
				{
					AlarmErrorMessage("Get Function FreeClientTransferModule() Failed", "Load Library Error");
					return -1;
				}
				(*lpfn_5t)(m_CArrayCycleStruct[i].hLibrary);

				//释放调用模块
				FreeLibrary(hLibrary);

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
			//循环速度控制
			else if(0)//(cur_Time - m_CArrayCycleStruct[i].LastTransferTime) < m_CArrayCycleStruct[i].TransferData.Cycle)
				continue;

			//5555555555555
			//设置要调用的动态库的hModule和lpfnR
			void (FAR *lpfn_3)(HMODULE hLibrary, bool (FAR* lpfounction)(CManageData &Data));
			lpfn_3 = (void (__cdecl *)(HMODULE , bool (FAR* )(CManageData &Data)))GetProcAddress(hLibrary, "SetModuleHandleAndFunctionAddress");
			if(lpfn_3 == NULL)
			{
				AlarmErrorMessage("Get Function SetModuleHandleAndFunctionAddress() Failed", "Load Library Error");
				return -1;
			}
			(*lpfn_3)(m_CArrayCycleStruct[i].hLibrary, m_CArrayCycleStruct[i].lpfn);


		
		
			//调用获取信息的模块
			bool (FAR *lpfn_4)(ModuleInfomationListStruct &ModuleInfo, CManageData& Data);
			lpfn_4 = (bool (__cdecl *)(struct ModuleInfomationListStruct&, class CManageData&))GetProcAddress(hLibrary, "CallClientTransferModuleByCManageData");
			if(lpfn_4 == NULL)
			{
				AlarmErrorMessage("Get Function CallClientTransferModuleByCManageData() Failed", " Error");
				return -1;
			}
			else
			{

				//由此获得指令
				m_C2S.InfoBaseID.InfomationElementTableID = m_CArrayCycleStruct[i].TransferData.InfoBaseID.InfomationElementTableID;
				m_C2S.InfoBaseID.InfomationElementID = m_CArrayCycleStruct[i].TransferData.InfoBaseID.InfomationElementID;


				ModuleInfo.InfomationElementTableID = m_C2S.InfoBaseID.InfomationElementTableID;
				ModuleInfo.InfomationElementID = m_C2S.InfoBaseID.InfomationElementID;

				Data.SetDatabyTLV(m_CArrayCycleStruct[i].TransferData.Value);
				bool flag = (*lpfn_4)(ModuleInfo, Data);
				if(!flag)
				{
					::MessageBox(0, "CallClientTransferModuleByCManageData() Failed", "", MB_OK);
					return -1;
				}

				//将获得的结果导入m_C2S
				Data.GetDatabyTLV(m_C2S.Value);
				m_C2S.InfoBaseID.InfomationElementTableID = ModuleInfo.InfomationElementTableID;
				m_C2S.InfoBaseID.InfomationElementID = ModuleInfo.InfomationElementID;
				strcpy(m_C2S.LocalTime, m_Time.GetCurrentTime().Format("%Y-%m-%d %H:%M:%S"));

				//将TLVData传入Data_Buff数组

				/*烫烫烫烫烫烫烫烫烫烫烫烫*/
				for(SMM_UINT x = 0; x < sizeof(Transfer_S2C_Struct); x++)
				{
					
					Data_Buff[x] = ((SMM_UCHAR*)&m_C2S)[x];
				}
				CString strTime;
				strTime = ((Transfer_C2S_Struct*)Data_Buff)->LocalTime;
				if(strTime.IsEmpty() == FALSE)
				{
					if(((Transfer_C2S_Struct*)Data_Buff)->Value.Value.Value_long < 0)
					{
						((Transfer_C2S_Struct*)Data_Buff)->Value.Value.Value_long = 0;
					}
					BOOL bCheck2;
					bCheck2 = Check(m_C2S.InfoBaseID.InfomationElementTableID,m_C2S.InfoBaseID.InfomationElementID,hwnd);
					if(bCheck2 == FALSE)
					{
						continue;
					}
					else
					{
						if(ITDQ_Write(iID[0],(SMM_UCHAR*)Data_Buff) == -3 )
						{
						  Sleep(1000);
						}
						PostMessage(hwnd,WM_DRIVERDATA,0,(LPARAM)Data_Buff);
					}
				}
			}
		}
////////////////Driver2 end/////////////////////////////////////////////////////////////////////
	}
	return 1;

}
 
//新增部分(2003-04-16)
SMM_INT iConnect ;  
SMM_INT iSocket ;
///////////////////////////////////////////////////////
		/*通信线程*/
DWORD WINAPI ComProc(
  LPVOID lpParameter   // thread data
)
{

	HWND  hwnd=((MessageParam*)lpParameter)->hwnd;
	if(Threadcheck1 == FALSE && Threadcheck2 == FALSE && Threadcheck3 == FALSE && Threadcheck4 == FALSE)
	{
		MessageBox(0,"如果您不发送任何数据将导致服务器的死锁!","警告",MB_OK|MB_ICONWARNING);
	}
	int n = 0;
    //SMM_INT       iSocket ;
    SMM_UCHAR pcBuffer[1024] ={'\0'}  ;
	SMM_UCHAR ucRepeat[1024] = {'\0'} ;
    SMM_UCHAR cRecv[1024]={'\0'} ;
	SMM_UCHAR cWrite[1024]={'\0'} ;
    SMM_INT iRecv = 0 ;
    SMM_INT  iRead  ;   
//	SMM_INT  iWrite ;
    SMM_INT  iCount = 0 ;   //计数器:用于计重发次数
	SMM_INT  iCountClose = 0 ;
	SMM_INT  iFlag = 1 ;  //1:客户端表示可以发送数据,0:表示不能发送数据
	SMM_INT  iWriteQueue_Flag = 1 ; //1:表示客户端可以循环写队列,0:表示不能循环写队列
    //测试
      SMM_INT i = 0 ;
      	char buff[100] = {'\0'};
		char buff01[100]={'\0'};
		char buf02[1024]={'\0'} ;
		char buf[1024]={'\0'};

    //补充(设置非阻塞模式)
    SMM_INT  iReturn ;
	SMM_ULONG ulArgpN = 1;
    SMM_INT   iQueue_empty = 0 ;  //0:表示队列为空

	//(1)初始化
	iReturn = SC_init() ; 
	//(2)创建套接字
	if (USE_SSL == 1)
	{
		iSocket = SC_socket(AF_INET,SOCK_STREAM
			,SC_VERIFY_YES,SC_ENCRYPT_NO,SC_CLIENT_YES,SC_SSLV3) ;
	}
	else
	{
       iSocket = SC_socket(AF_INET,SOCK_STREAM
			,SC_VERIFY_NO,SC_ENCRYPT_NO,SC_CLIENT_YES,SC_SSLV3) ;
	}
    //::MessageBox(0, "", "q", MB_OK	);

    //(3)连接服务器
	
    iConnect = SC_connect(iSocket,(SMM_CHAR*)pcIP,5000);
	if(iConnect != 0)
	{
		::MessageBox(0,"连接服务器失败!","失败",MB_OK|MB_ICONERROR);
		CloseHandle(hComThread);
	}
	else
	{
	//	::MessageBox(0, itoa(iConnect, buff01, 10), "connect", MB_OK);
		::MessageBox(0,"连接服务器成功","成功",MB_OK);
	
	}
	//printf("SC_connect=%d",ulreturn) ;     //测试:显示connect函数返回值

		if (USE_SSL == 0)   //0:使用非阻塞模式
		{
			//iReturn = SC_ioctl(iSocket,FIONBIO,ulArgpN) ;	//设置非阻塞方式(与SSL_accept有冲突)
		   
			iReturn = SC_queryarray(iSocket) ;
			iReturn = ioctlsocket(stSSLSocket[iReturn].s,FIONBIO,&ulArgpN) ;
			//printf("SC_ioctl00=%d\n",stSSLSocket[iReturn].s) ;
			//printf("SC_ioctl01=%d\n",iReturn) ;
		}

		//(4-3)测试从队列读出数据
		while (1)
		{    
			i++ ;
			Sleep(10) ;
			//::MessageBox(0, "bc", "", MB_OK	);
			 if (iFlag == 1)
			 {
					 iRead=ITDQ_Read(iID[0],pcBuffer);
					 //iRead=1 ;
					 //ulreturn=SC_send(iSocket,pcBuffer,sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
					 //memset(pcBuffer,'\0',sizeof(pcBuffer)) ;
					 //::MessageBox(0, ((Transfer_C2S_Struct *)pcBuffer)->Value.Value.Value_char, "queue", MB_OK	);
					 if (iRead == -4)  //-4:表示队列为空
					 {    
						  iCountClose++ ;
						  iQueue_empty = 0 ;
						  /*if (iCountClose >10000000)  //长时间没有数据,结束通讯(使用定时器)
						  {
							   SC_send(iSocket,(unsigned char *)"END",3,SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
							   break ;

						  }*/
						  //Sleep(10) ;
     
					 }
					 else
					 {   
						 iQueue_empty = 1 ;
						 memset(ucRepeat,'\0',sizeof(ucRepeat)) ;
						 //itoa(i,(char *)pcBuffer,10) ;
						 //strcat((char *)pcBuffer,"A-") ;
					  
						 iReturn=SC_send(iSocket,(unsigned char *)pcBuffer,sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
						 memcpy(ucRepeat,pcBuffer,sizeof(pcBuffer)) ;
						 memset(pcBuffer,'\0',sizeof(pcBuffer)) ;
						 iCountClose = 0 ;
					 }
			 }
			 
			 iReturn  = -10 ;
			 iReturn = SC_recv(iSocket,cRecv,sizeof(cRecv),SC_TCP_YES,NULL,&iRecv,SC_CLIENT_YES) ;
		
			 
		/*	 if (strcmp((char *)cRecv,"") == 0)  //阻塞读队列
			 {    
				  iFlag = 0 ;
				  iReturn  = -10 ;
				  //continue ;
			 }*/
		/*	CString str;
			str=cRecv;
			if(str.IsEmpty()==TRUE)
			{
				iFlag = 0 ;
				iReturn  = -10 ;
				continue;
			}*/
			

			 if (iWriteQueue_Flag == 0 ) //继续写队列
			 {
				  if (ITDQ_Write(iID[1],cWrite) != -3) //队列未满    
				  {     
						
						memset(cWrite,'\0',sizeof(cWrite)) ;
						iWriteQueue_Flag = 1 ;
						SC_send(iSocket,(unsigned char *)"CLIENT_WRITE_GOOD",sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
				 }
				 

			 }


			 if (iReturn <= 0)  //网络错误/服务器阻塞(要求客户端不要发送数据)
			 {   
				 
				if (iQueue_empty == 0 )
				{
					iFlag = 1 ;
				}
				else
				{
					iFlag = 0 ;
				}
			 }
			 else
			 {
					 if (strcmp((char *)cRecv,"SERVER_WRITE_ERR") == 0 && iCount < SC_REPEAT )  //服务器写入共享内存错误,客户端重发
					 { 
							iCount++ ;
							SC_send(iSocket,ucRepeat,sizeof(ucRepeat),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
							iFlag = 0 ;
					 }
					 else 
					 {
						 if (strcmp((char *)cRecv,"SERVER_WRITE_GOOD") == 0)   //接收到服务器的数据
						 {
							//::MessageBox(0, (char*)cRecv, "recv", MB_OK);
					
							 iFlag = 1 ;
						 }
						 else
						 {						
								 if (strcmp((char *)cRecv,"SERVER_WRITE_NO") != 0 && SC_isnull((char *)&cRecv,sizeof(cRecv)) == 0) 
									{
										if (iWriteQueue_Flag == 1 ) //第一次写队列
										 {
													 if (ITDQ_Write(iID[1],cRecv) == -3) //队列已满 (以后补充) 
													 {     
															memcpy(cWrite,cRecv,sizeof(cRecv)) ;
															iWriteQueue_Flag = 0 ;  //写队列失败
                             								SC_send(iSocket,(unsigned char *)"CLIENT_WRITE_ERR",sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
            
													 }
													 else
													 {
															memset(cWrite,'\0',sizeof(cWrite)) ;
													
															iFlag = 1 ;
															SC_send(iSocket,(unsigned char *)"CLIENT_WRITE_GOOD",sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
													 }
											}
									 }
								 else  //没有数据
								 {
									 iFlag = 0 ;
								 }

						 }
					 } 
			 }
			 //清空数据
			  memset(cRecv,'\0',sizeof(cRecv)) ; 

		}
		//(6)关闭(屏蔽)
		//SC_send(iSocket,(unsigned char *)"CLIENT_END",sizeof(pcBuffer),SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
		//iReturn = SC_close(iSocket,SD_NO,0) ;  
	return 1;
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
	InitCreate();	//创建队列
	checkTest();	
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->SetAddress(192,168,1,150);
	MessageParam *pMessage=new MessageParam;					   //分配空间
	pMessage->hwnd=m_hWnd;								           //将对话框句柄赋值给结构变量
	::CreateThread(NULL,1,&DriverProc,(LPVOID)pMessage,0,NULL);    //创建Driver线程
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
/*********************************************************
  Function:       InitCreate()
  Description:    初始化和创建队列
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	
	
					


  Output:         
  Return:         
				  

  Others:        
***********************************************************/
void CTestDlgDlg::InitCreate()
{
	ITDQ_Init();
	iID[0]=ITDQ_Create(0,10);
	iID[1]=ITDQ_Create(0,10);
}
/*********************************************************
  Function:       OnDriverData
  Description:   DRIVER线程消息响应函数
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	wParam:
	
					lParam:Driver线程传递的参数


  Output:         
  Return:         
  Others:        
***********************************************************/
/*Driver线程消息响应函数*/
void CTestDlgDlg::OnDriverData(WPARAM wParam,LPARAM lParam)
{	
	SMM_UCHAR *Data_Buff1=(SMM_UCHAR*)lParam;
	Transfer_C2S_Struct* m_Data = (Transfer_C2S_Struct*)Data_Buff1;
	//////////////文件保存发送数据//////////////////////
	CFile f("D:\\第一期原型演示程序发送数据.txt",CFile::modeWrite|CFile::modeCreate|
			CFile::modeNoTruncate);
	//////////////////////////////////////////////////
	if(m_Data->Value.Type == long_Value)
	{
		char buff1[100];
		((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(0,itoa(m_Data->Value.Value.Value_long, buff1, 10));
		((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(0,m_Data->LocalTime);
		////////////////////////////
		 /*文件读写操作*/
		    f.SeekToEnd();
			f.WriteHuge("当前CPU使用率为:",16);
			f.WriteHuge(itoa(m_Data->Value.Value.Value_long,buff1,10),strlen(itoa(m_Data->Value.Value.Value_long,buff1,10)));	
			f.Write("\r\n",2);
			f.WriteHuge(m_Data->LocalTime,strlen(m_Data->LocalTime));
			f.Write("\r\n",2);
		///////////////////	
	}
	else if(m_Data->Value.Type == CString_Value)
	{
		((CListBox*)GetDlgItem(IDC_LIST1))->InsertString(0, m_Data->Value.Value.Value_char);
		/*文件读写操作*/
		f.SeekToEnd();
		f.WriteHuge(m_Data->Value.Value.Value_char,strlen(m_Data->Value.Value.Value_char));
		f.Write("\r\n",2);
		//////////////////		
	}

}
/*********************************************************
  Function:       OnIp
  Description:    解析IP地址控件
  Calls:          // 被本函数调用的函数清单
  Called By:      // 调用本函数的函数清单
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          	


  Output:         
  Return:         

  Others:        
***********************************************************/
void CTestDlgDlg::OnIp() 
{
	// TODO: Add your control notification handler code here
	MessageParam *pMessage=new MessageParam;
	hComThread=::CreateThread(NULL,1,&ComProc,(LPVOID)pMessage,0,NULL);       //创建通信线程
	DWORD dwIP;
	int t;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1))->GetAddress(dwIP);
	char buff[100];
	char ipbuf[100];
	t = dwIP >> 24;
	strcpy(ipbuf, itoa(t, buff, 10));
	strcat(ipbuf, ".");

	t = (dwIP >> 16 ) & 0x000000ff;
	strcat(ipbuf, itoa(t, buff, 10));
	strcat(ipbuf, ".");

	t = (dwIP >> 8 ) & 0x000000ff;
	strcat(ipbuf, itoa(t, buff, 10));
	strcat(ipbuf, ".");

	t = dwIP & 0x000000ff;
	strcat(ipbuf, itoa(t, buff, 10));
	memcpy(pcIP,ipbuf,15);
}

void CTestDlgDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	if(IDOK==MessageBox("你确认要关闭吗?","关闭",MB_OKCANCEL|MB_ICONQUESTION))
	{
		if (iConnect == 0)  //0:连上服务器
		{
			SMM_INT iReturn ;
			SMM_CHAR buf[1024]={'\0'} ;			
			// TODO: Add extra cleanup here		
			iReturn =SC_send(iSocket,(unsigned char *)"CLIENT_END",1024,SC_TCP_YES,NULL,0,SC_CLIENT_YES) ;
			//	::MessageBox(0,itoa(iReturn,buf,10),"close",MB_OK) ;
			//	::MessageBox(0,"关闭连接","close",MB_OK) ;    
			SC_close(iSocket,SD_NO,0) ; 		
		}
		DestroyWindow();
	}	
}

