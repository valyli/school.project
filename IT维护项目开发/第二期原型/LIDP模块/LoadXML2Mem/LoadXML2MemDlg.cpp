// LoadXML2MemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LoadXML2Mem.h"
#include "LoadXML2MemDlg.h"




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
// CLoadXML2MemDlg dialog

CLoadXML2MemDlg::CLoadXML2MemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLoadXML2MemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoadXML2MemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoadXML2MemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoadXML2MemDlg)
	DDX_Control(pDX, IDC_TREE_XML, m_Tree);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CLoadXML2MemDlg, CDialog)
	//{{AFX_MSG_MAP(CLoadXML2MemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TEST, OnButtonTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoadXML2MemDlg message handlers

BOOL CLoadXML2MemDlg::OnInitDialog()
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
	

	

	//创建树形浏览窗口
	m.Create(WS_VISIBLE | WS_TABSTOP | WS_CHILD | WS_BORDER
	   | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_HASLINES
	   | TVS_DISABLEDRAGDROP,
	   CRect(10, 10, 300, 100), this, 0x1005);
	//简单测试
	m.SetXml2View("InfomationElementListTable.xml");
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLoadXML2MemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLoadXML2MemDlg::OnPaint() 
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
HCURSOR CLoadXML2MemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}







void CLoadXML2MemDlg::OnButtonTest() 
{



//			IXMLDOMNodePtr pChild = m_pDocRoot->firstChild;

		CString temp;
/*				temp = (char*)(pChild->nodeName);
			::MessageBox(0, temp, "", MB_OK);
*/

		
		
	HTREEITEM hRoot;

	// Create the root item.
	TVITEM tvItem;
	tvItem.mask = TVIF_TEXT | TVIF_IMAGE;// | TVIF_SELECTEDIMAGE;
	tvItem.pszText = "我的电脑";
	tvItem.cchTextMax = 8;
//	tvItem.iImage = 0;
//	tvItem.iSelectedImage = 0;
	TV_INSERTSTRUCT tvInsert;
	tvInsert.hParent = TVI_ROOT;
	tvInsert.hInsertAfter = TVI_FIRST;
	tvInsert.item = tvItem;
	hRoot = m_Tree.InsertItem(&tvInsert);
		
			tvItem.pszText = "asdfasdf";
			tvItem.cchTextMax = 12;
//			tvItem.iImage = 2;
//			tvItem.iSelectedImage = 2;
			tvInsert.hParent = hRoot;
			tvInsert.item = tvItem;
			m_Tree.InsertItem(&tvInsert);
		
/*		
		if(m_pDocRoot->hasChildNodes() == -1)
			{
				for(IXMLDOMNodePtr p = m_pDocRoot->firstChild; NULL != p; p = p->nextSibling)
				{
					temp = (char*)(p->nodeName);
					::MessageBox(0, temp, "", MB_OK);
				}
			}
*/


}
