// SameBall.cpp : Defines the class behaviors for the application.
// 编码: Leezy
// 最后修改日期：5.12
//

#include "stdafx.h"
#include "SameBall.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSameBallApp

BEGIN_MESSAGE_MAP(CSameBallApp, CWinApp)
	//{{AFX_MSG_MAP(CSameBallApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSameBallApp construction

CSameBallApp::CSameBallApp()
{
	// TODO: add construction code here,
	m_bNeedSave=false;
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSameBallApp object

CSameBallApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSameBallApp initialization

BOOL CSameBallApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
//	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	GetReg();


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	HICON hIcon;
	hIcon=LoadIcon(IDR_MAINFRAME);
	pFrame->SetIcon(hIcon,true);

	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	if(m_sWindow==_T("Maximize"))
		pFrame->SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CSameBallApp message handlers





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
		// No message handlers
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

// App command to run the dialog
void CSameBallApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSameBallApp message handlers

////////////////////////////////////排行榜保存密码生成办法///////////
//	num		0	1	2	3	4	5	6	7	8	9	
//	char1	p	k	j	z	u	w	b	d	y	q
//  char2	h	l	r	t	a	e	x	o	f	c
//	0	dddddNNNNNoooooppppphhhhhhhhhhhhhhh
//	1	Noname1	 //dNophhh	if number is 3444 the code will be dNozutt	
//	2	Noname2	 //dNophhh
//	3   Noname3  //dNophhh
//	4   Noname4  //dNophhh
//	5	Noname5  //dNophhh
//  说明：密码使用极其简单的办法生成，用两个函数实现
//  GetScoreListItem(); 获得Index 指定的排名的人名和分数
//  SetScoreListItem(); 保存Index 指定的排名的人名和分数
//////////////////////////////////////////////////////////////////////

BOOL CSameBallApp::GetScoreListItem(int Index, CString &rsName, int &rdScore)
{
	char*    pBuf1;
	int i,dNum;
	rdScore=0;
	switch(Index)
	{
	case 1:		rsName=m_s1;	break;
	case 2:		rsName=m_s2;	break;
	case 3:		rsName=m_s3;	break;
	case 4:		rsName=m_s4;	break;
	case 5:		rsName=m_s5;	break;
	default:	rsName=_T("Error");		return false;
	}
	if(m_s0.GetLength()!=35){		rsName=_T("Error");
		return false;	}
	pBuf1=(char*)LPCTSTR(m_s0);
	dNum=0;
	switch(pBuf1[Index-1])
	{
	case 'p':		case 'h':	dNum=0;			break;
	case 'k':		case 'l':	dNum=1;			break;
	case 'j':		case 'r':	dNum=2;			break;
	case 'z':		case 't':	dNum=3;			break;
	case 'u':		case 'a':	dNum=4;			break;
	case 'w':		case 'e':	dNum=5;			break;
	case 'b':		case 'x':	dNum=6;			break;
	case 'd':		case 'o':	dNum=7;			break;
	case 'y':		case 'f':	dNum=8;			break;
	case 'q':		case 'c':	dNum=9;			break;
	default:	rsName=_T("------");	return false;
	}
	if(dNum!=rsName.GetLength())
		return false;
	if(rsName[0]!=pBuf1[Index+4] || rsName[1]!=pBuf1[Index+9])
		return false;
	dNum=0;
	for(i=3;i<7;i++)
	{
		switch(pBuf1[i*5+Index-1])
		{
		case 'p':		case 'h':	dNum=dNum*10+0;			break;
		case 'k':		case 'l':	dNum=dNum*10+1;			break;
		case 'j':		case 'r':	dNum=dNum*10+2;			break;
		case 'z':		case 't':	dNum=dNum*10+3;			break;
		case 'u':		case 'a':	dNum=dNum*10+4;			break;
		case 'w':		case 'e':	dNum=dNum*10+5;			break;
		case 'b':		case 'x':	dNum=dNum*10+6;			break;
		case 'd':		case 'o':	dNum=dNum*10+7;			break;
		case 'y':		case 'f':	dNum=dNum*10+8;			break;
		case 'q':		case 'c':	dNum=dNum*10+9;			break;
		default:	rsName=_T("------");	return false;
		}
	}
	rdScore=dNum;
	return true;
}

BOOL CSameBallApp::SetScoreListItem(int Index, CString nsName, int ndScore)
{
	char	code1[]="pkjzuwbdyq";
	char    code2[]="hlrtaexofc";
	char*	pName;
	char   pScore[50];
	int d1,d2;
	if((d1=nsName.GetLength())<2)
		return false;
	pName=(char*)LPCTSTR(nsName);
	if(m_s0.GetLength()!=35)
		m_s0=_T("dddddNNNNNoooooppppphhhhhhhhhhhhhhh");
	ZeroMemory(pScore,50);
	wsprintf(pScore,"%s",m_s0);
	m_bNeedSave=true;
	switch(Index)
	{
	case 1:		m_s1=nsName;	break;
	case 2:		m_s2=nsName;	break;
	case 3:		m_s3=nsName;	break;
	case 4:		m_s4=nsName;	break;
	case 5:		m_s5=nsName;	break;
	default:	return false;
	}
	Index--;
	d2=d1%10;
	pScore[Index]=code1[d2];
	code1[d2]=code2[d2];
	Index+=5;
	pScore[Index]=pName[0];
	Index+=5;
	pScore[Index]=pName[1];
	d1=ndScore;
	d2=d1/1000;
	d1=d1%1000;
	Index+=5;
	pScore[Index]=code1[d2];
	code1[d2]=code2[d2];
	d2=d1/100;
	d1=d1%100;
	Index+=5;
	pScore[Index]=code1[d2];
	code1[d2]=code2[d2];
	d2=d1/10;
	d1=d1%10;
	Index+=5;
	pScore[Index]=code1[d2];
	code1[d2]=code2[d2];
	Index+=5;
	pScore[Index]=code1[d1];
	code1[d1]=code2[d1];
	pScore[35]=0;
	m_s0.Format("%s",pScore);
	return true;
}

BOOL CSameBallApp::GetReg()
{
	HKEY hKey;
	DWORD dType;
	unsigned long  size;
	unsigned char bufInfo[MAX_PATH];
	LONG l = RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Polarlight\\SameBall",0, KEY_QUERY_VALUE, &hKey);
	if (l != ERROR_SUCCESS)
		goto Step1;
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"0",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		{
			RegCloseKey(hKey);
			goto Step1;
		}
	m_s0.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,NULL,0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		GetCurrentDirectory(MAX_PATH,(char*)bufInfo);
	m_sAppDir.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"1",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		m_s1=_T("Noname1");
	else
		m_s1.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"2",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		m_s2=_T("Noname2");
	else
		m_s2.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"3",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		m_s3=_T("Noname3");
	else
		m_s3.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"4",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		m_s4=_T("Noname4");
	else
		m_s4.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"5",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		m_s5=_T("Noname5");
	else
		m_s5.Format("%s",bufInfo);
	size=MAX_PATH;
	if(RegQueryValueEx(hKey,"Window",0,&dType,bufInfo,&size)!=ERROR_SUCCESS)
		m_sWindow=_T("Maximize");
	else
		m_sWindow.Format("%s",bufInfo);
	RegCloseKey(hKey);
	return true;
Step1:
   
	m_bNeedSave=true;
	SetScoreListItem(1,"Noname1",0);
	SetScoreListItem(2,"Noname2",0);
	SetScoreListItem(3,"Noname3",0);
	SetScoreListItem(4,"Noname4",0);
	SetScoreListItem(5,"Noname5",0);
	if(!GetCurrentDirectory(MAX_PATH,(char*)bufInfo))
		ASSERT(0);
	m_sAppDir.Format("%s",bufInfo);
	m_sWindow=_T("Maximize");
   RegCloseKey(hKey);
   return false;
}

BOOL CSameBallApp::SaveReg()
{
	if(!m_bNeedSave)
		return false;
	HKEY hkey;
	LONG l=RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Polarlight\\SameBall",0,NULL,REG_OPTION_NON_VOLATILE,
			KEY_CREATE_SUB_KEY|KEY_WRITE|KEY_READ,NULL,&hkey,NULL);
	if (l!=ERROR_SUCCESS)
	{
      RegCloseKey(hkey);
	  return false;
	}
	if(RegSetValueEx(hkey,NULL,0,REG_SZ,(const unsigned char*)LPCTSTR(m_sAppDir),m_sAppDir.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"0",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s0),m_s0.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"1",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s1),m_s1.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"2",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s2),m_s2.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"3",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s3),m_s3.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"4",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s4),m_s4.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"5",0,REG_SZ,(const unsigned char*)LPCTSTR(m_s5),m_s5.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	if(RegSetValueEx(hkey,"Window",0,REG_SZ,(const unsigned char*)LPCTSTR(m_sWindow),m_sWindow.GetLength()+1)!=ERROR_SUCCESS)
		return false;
	RegCloseKey(hkey);
    return true;
}

int CSameBallApp::ExitInstance() 
{
	SaveReg();
	return CWinApp::ExitInstance();
}
