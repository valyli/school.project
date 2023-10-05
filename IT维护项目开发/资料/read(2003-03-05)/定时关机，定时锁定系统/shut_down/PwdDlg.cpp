// PwdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ShutDown.h"
#include "PwdDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPwdDlg dialog


//全局变量的定义
HHOOK hHook=NULL;
CRect rt;
extern "C" LRESULT WINAPI HookProc(int nCode,WPARAM wParam,LPARAM lParam); 


CPwdDlg::CPwdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPwdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPwdDlg)
	m_check = _T("");
	//}}AFX_DATA_INIT
}

void CPwdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPwdDlg)
	DDX_Control(pDX, IDC_EDIT1, m_Pwd);
	DDX_Text(pDX, IDC_EDIT1, m_check);
	DDV_MaxChars(pDX, m_check, 15);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPwdDlg, CDialog)
	//{{AFX_MSG_MAP(CPwdDlg)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPwdDlg message handlers

void CPwdDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString m_strPwd;
	m_Pwd.GetWindowText(m_strPwd);
	
	CShutDownApp *myapp = (CShutDownApp *)AfxGetApp();

	m_strPwd = myapp->KeyChanged(m_strPwd);

	if(m_strPwd.Compare(myapp->strCheck))
	{
		AfxMessageBox("您所输入的密码无效，无权使用本机！"
			                               ,MB_OK | MB_ICONSTOP);
		return;
	}
	else
	{
		SystemParametersInfo(SPI_SETSCREENSAVERRUNNING,
		false,&pOld,SPIF_UPDATEINIFILE);
		UnhookWindowsHookEx(hHook);
	}

	ReleaseCapture();
//	::ShowCursor(true);
	ClipCursor(NULL);
	CDialog::OnOK();
}

BOOL CPwdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CShutDownApp *myapp = (CShutDownApp *)AfxGetApp();

	CString strValue;

	strValue = myapp->GetProfileString("ShutDown","pwd","");
	
	myapp->strCheck=strValue;
   
	//锁定初始化
	SetForegroundWindow();

	hHook=SetWindowsHookEx(WH_MOUSE,HookProc,NULL,0);

	//过滤系统键
	SystemParametersInfo(SPI_SETSCREENSAVERRUNNING,true,&pOld,SPIF_UPDATEINIFILE);

	m_Pwd.SetPasswordChar('*');
	
	GetWindowRect(rt);
	ClipCursor(rt);

	SetCursor(LoadCursor(NULL,IDC_NO));

	SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | WS_EX_TOPMOST);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPwdDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	return;
	//CDialog::OnCancel();
}

void CPwdDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}


extern "C" LRESULT WINAPI HookProc(int nCode,WPARAM wParam,LPARAM lParam)
{
	//MessageBeep(MB_OK);
	return -1;
	//return CallNextHookEx(hHook,nCode,wParam,lParam);
}
