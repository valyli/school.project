// treeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tree.h"
#include "treeDlg.h"
#include "direct.h"
#include "io.h"

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
	CString	m_mem;
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
	m_mem = _T("");
	//}}AFX_DATA_INIT
	MEMORYSTATUS mem;
	::GlobalMemoryStatus(&mem);
	m_mem.Format("%s %d%s","windows的物理内存信息：",mem.dwTotalPhys/(1024*1024),"MB");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_mem, m_mem);
	//}}AFX_DATA_MAP
    
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeDlg dialog

CTreeDlg::CTreeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTreeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTreeDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTreeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTreeDlg)
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTreeDlg, CDialog)
	//{{AFX_MSG_MAP(CTreeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeDlg message handlers

BOOL CTreeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
    m_img.Create(IDB_map,16,1,RGB (255, 0, 255) );
	m_TreeCtrl.SetImageList(&m_img, TVSIL_NORMAL);
	struct _finddata_t c_file;
	long hFile;
	TV_ITEM tvItem;
	tvItem.mask=TVIF_TEXT|TVIF_PARAM|TVIF_IMAGE;
	tvItem.pszText="C:";
	tvItem.cchTextMax=2;
	

	tvItem.iImage=0;
	TV_INSERTSTRUCT  tvInsert;
	tvInsert.hParent=TVI_ROOT;
	tvInsert.hInsertAfter=TVI_LAST;
    tvInsert.item=tvItem;
	
	HTREEITEM hRoot=m_TreeCtrl.InsertItem(&tvInsert);
    
	getdir("c:\\");
	hFile=_findfirst("*",&c_file);
	tvItem.pszText=c_file.name;
	tvItem.cchTextMax=6;
	tvItem.iImage=1;
	tvInsert.hParent=hRoot;
	tvInsert.item=tvItem;
	
	m_TreeCtrl.InsertItem(&tvInsert);
    while( _findnext( hFile, &c_file ) == 0 )
	{
    tvItem.pszText=c_file.name;
	tvItem.cchTextMax=7;
	tvItem.iImage=1;
	tvInsert.hParent=hRoot;
	tvInsert.item=tvItem;
	m_TreeCtrl.InsertItem(&tvInsert);
	}
    _findclose( hFile );
	tvItem.pszText="D:";
	tvItem.cchTextMax=2;
	tvItem.iImage=0;
	tvInsert.hParent=TVI_ROOT;
	tvInsert.hInsertAfter=TVI_LAST;
	tvInsert.item=tvItem;
	m_TreeCtrl.InsertItem(&tvInsert);
    getdir("D:\\");
	hFile=_findfirst("*",&c_file);
	tvItem.pszText=c_file.name;
	tvItem.cchTextMax=6;
	tvItem.iImage=1;
	tvInsert.hParent=m_TreeCtrl.GetNextSiblingItem(hRoot);
	tvInsert.item=tvItem;
	m_TreeCtrl.InsertItem(&tvInsert);
    while( _findnext( hFile, &c_file ) == 0 )
	{
    tvItem.pszText=c_file.name;
	tvItem.cchTextMax=7;
	tvItem.iImage=1;
	tvInsert.hParent=m_TreeCtrl.GetNextSiblingItem(hRoot);
	tvInsert.item=tvItem;
	m_TreeCtrl.InsertItem(&tvInsert);
	}
    _findclose( hFile );

	
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTreeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTreeDlg::OnPaint() 
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
HCURSOR CTreeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

int CTreeDlg::getdir(char *dirname)
{
    return(	_chdir(dirname));
}
