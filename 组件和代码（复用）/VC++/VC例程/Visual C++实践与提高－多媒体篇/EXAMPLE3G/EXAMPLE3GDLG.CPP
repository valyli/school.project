// Example3GDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Example3G.h"
#include "Example3GDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
// CExample3GDlg dialog

CExample3GDlg::CExample3GDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExample3GDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExample3GDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExample3GDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExample3GDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CExample3GDlg, CDialog)
	//{{AFX_MSG_MAP(CExample3GDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_DEL, OnEditDel)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectall)
	ON_COMMAND(ID_EDIT_SELECTFONT, OnEditSelectfont)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_WM_SIZE()
	
	//}}AFX_MSG_MAP
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExample3GDlg message handlers

BOOL CExample3GDlg::OnInitDialog()
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
	CRect rect;
	GetClientRect(&rect);
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
	if (pEdit)
	{
		pEdit->MoveWindow(&rect);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CExample3GDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CExample3GDlg::OnPaint() 
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
HCURSOR CExample3GDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CExample3GDlg::OnEditCopy() 
{
	// TODO: Add your command handler code here
	//调用CEdit类的Copy函数
	((CEdit*)GetDlgItem(IDC_EDIT1))->Copy();
}

void CExample3GDlg::OnEditCut() 
{
	// TODO: Add your command handler code here
	//调用CEdit类的Cut函数
	((CEdit*)GetDlgItem(IDC_EDIT1))->Cut();	
}

void CExample3GDlg::OnEditDel() 
{
	// TODO: Add your command handler code here
	//调用CEdit类的Clear函数
	((CEdit*)GetDlgItem(IDC_EDIT1))->Clear();	
}

void CExample3GDlg::OnEditPaste() 
{
	// TODO: Add your command handler code here
	//调用CEdit类的Paste函数
	((CEdit*)GetDlgItem(IDC_EDIT1))->Paste();	
}

void CExample3GDlg::OnEditSelectall() 
{
	// TODO: Add your command handler code here
	//设置字符开头为0
	int iStartPos=0, iEndPos=0;
	//利用GetWindowTextLength获得编辑框控件中文本的长度
	//作为所选选定字符的结尾
	iEndPos=((CEdit*)GetDlgItem(IDC_EDIT1))->GetWindowTextLength();
	//选择编辑框控件中iStartPos和iEndPos之间的字符串
	((CEdit*)GetDlgItem(IDC_EDIT1))->SetSel(iStartPos,iEndPos);
}

void CExample3GDlg::OnEditSelectfont() 
{
	// TODO: Add your command handler code here

	LOGFONT lf;
	static CFont font;

	//用lf存储原有的字体信息
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->GetFont()->GetLogFont(&lf);
	//调用字体对话框
	CFontDialog dlg(&lf);
	if (IDOK==dlg.DoModal())
	{
		dlg.GetCurrentFont(&lf);
		font.DeleteObject();
		font.CreateFontIndirect(&lf);
		pEdit->SetFont(&font);
	}	
}

void CExample3GDlg::OnEditUndo() 
{
	// TODO: Add your command handler code here
	//调用CEdit类的成员函数Undo
	((CEdit*)GetDlgItem(IDC_EDIT1))->Undo();
}

void CExample3GDlg::OnFileClose() 
{
	// TODO: Add your command handler code here
	//关闭对话框
	OnCancel(); 
}

void CExample3GDlg::OnFileNew() 
{
	// TODO: Add your command handler code here
	//清除编辑框控件中的文本，并清空撤消缓冲区中的内容
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
	pEdit->SetWindowText("");
	pEdit->EmptyUndoBuffer();	
}


void CExample3GDlg::OnInitMenuPopup( CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu )
{
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
	//如果用户单击的是窗口的控制菜单,bSysMenu为真，否则为假
	if (!bSysMenu)
	{
		//检查编辑框控件是否有可撤消的操作
		if (pEdit->CanUndo())
		{
			pPopupMenu->EnableMenuItem(ID_EDIT_UNDO,MF_ENABLED);
		}
		else
		{
			pPopupMenu->EnableMenuItem(ID_EDIT_UNDO,MF_GRAYED);
		}

		//检查编辑框控件中是否有选定的字符
		int iStartPos,iEndPos;
		pEdit->GetSel(iStartPos,iEndPos);
		if (iStartPos==iEndPos)
		{
			pPopupMenu->EnableMenuItem(ID_EDIT_CUT,MF_GRAYED);
			pPopupMenu->EnableMenuItem(ID_EDIT_COPY,MF_GRAYED);
			pPopupMenu->EnableMenuItem(ID_EDIT_DEL,MF_GRAYED);
		}
		else
		{
			pPopupMenu->EnableMenuItem(ID_EDIT_CUT,MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_EDIT_COPY,MF_ENABLED);
			pPopupMenu->EnableMenuItem(ID_EDIT_DEL,MF_ENABLED);
		}

		//检查系统剪贴板中是否有文本格式的数据
		//通过调用Win32 API函数IsClipboardFormatAvailable来实现
		if (IsClipboardFormatAvailable(CF_TEXT))
		{
			pPopupMenu->EnableMenuItem(ID_EDIT_PASTE,MF_ENABLED);
		}
		else
		{
			pPopupMenu->EnableMenuItem(ID_EDIT_PASTE,MF_GRAYED);
		}
	}
}

void CExample3GDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: Add your message handler code here

	// 调用基类的 OnSize 成员函数
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	//获得父窗口的客户区矩形
	GetClientRect(&rect);
	CEdit *pEdit=(CEdit*)GetDlgItem(IDC_EDIT1);
	if (pEdit)
	{
		// 改变编辑控件的大小以适应父窗口大小的改变
		pEdit->MoveWindow(&rect);
	}
}
