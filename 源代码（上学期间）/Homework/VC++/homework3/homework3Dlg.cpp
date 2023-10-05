// homework3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "homework3.h"
#include "homework3Dlg.h"

#include "string.h"
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
// CHomework3Dlg dialog

CHomework3Dlg::CHomework3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHomework3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHomework3Dlg)
	m_Show = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHomework3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHomework3Dlg)
	DDX_Control(pDX, IDC_TREE_DIR, m_TreeDir);
	DDX_Text(pDX, IDC_EDIT1, m_Show);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHomework3Dlg, CDialog)
	//{{AFX_MSG_MAP(CHomework3Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DIR, OnSelchangedTreeDir)
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_TREE_DIR, OnItemexpandedTreeDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomework3Dlg message handlers

BOOL CHomework3Dlg::OnInitDialog()
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
	HICON hIcon[7];
	hIcon[0] = AfxGetApp()->LoadIcon(IDI_ICON_ROOT);
	hIcon[1] = AfxGetApp()->LoadIcon(IDI_ICON_FD);
	hIcon[2] = AfxGetApp()->LoadIcon(IDI_ICON_HD);
	hIcon[3] = AfxGetApp()->LoadIcon(IDI_ICON_CD);
	hIcon[4] = AfxGetApp()->LoadIcon(IDI_ICON_CLSFOLD);
	hIcon[5] = AfxGetApp()->LoadIcon(IDI_ICON_OPENFOLD);
	hIcon[6] = AfxGetApp()->LoadIcon(IDI_ICON_FILE);
	m_TreeImageList.Create(13, 13, ILC_COLOR, 7, 0);
	m_TreeDir.SetBkColor(RGB(250, 250, 0 ));
	m_TreeImageList.SetBkColor(RGB(250, 250, 0));
	for(int i = 0; i < 7; i++)
		m_TreeImageList.Add(hIcon[i]);

	// Create the Tree View control.
	m_TreeDir.SetImageList(&m_TreeImageList, TVSIL_NORMAL);

	// Create the root item.
	TVITEM tvItem;
	tvItem.mask =
		TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvItem.pszText = "ÎÒµÄµçÄÔ";
	tvItem.cchTextMax = 8;
	tvItem.iImage = 0;
	tvItem.iSelectedImage = 0;
	TV_INSERTSTRUCT tvInsert;
	tvInsert.hParent = TVI_ROOT;
	tvInsert.hInsertAfter = TVI_FIRST;
	tvInsert.item = tvItem;
	hRoot = m_TreeDir.InsertItem(&tvInsert);
	
	//Create C: disk item
    int nDrives;
	char DriNam[3] = "Z:";
	for( nDrives = 26; nDrives >= 1; nDrives-- )
	{
		if( !_chdrive( nDrives ) )
		{
			tvItem.pszText = DriNam;
			tvItem.cchTextMax = 2;
			tvItem.iImage = 2;
			tvItem.iSelectedImage = 2;
			tvInsert.hParent = hRoot;
			tvInsert.item = tvItem;
			m_TreeDir.InsertItem(&tvInsert);
		}
		DriNam[0]--;
	}
	strcpy(CurDir, "c:\\");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHomework3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHomework3Dlg::OnPaint() 
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
HCURSOR CHomework3Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHomework3Dlg::OnSelchangedTreeDir(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
	TV_ITEM item;
	TVITEM tvItem;
	item.mask = TVIF_HANDLE | TVIF_TEXT;
	item.hItem = hSelected;
	item.pszText = m_Show.GetBuffer(31);
	item.cchTextMax = 30;
	VERIFY(m_TreeDir.GetItem(&item));
	UpdateData(FALSE);

	*pResult = 0;

	char temp[261];
	long cur_n;
	HTREEITEM hCurItem;
	int testImage, testImageSel;
	hCurItem = hSelected;
	m_TreeDir.GetItemImage(hCurItem, testImage, testImageSel);
	if(testImage == 6)//is file
	{
//		MessageBox("It is a file, can not open");
		return;
	}
	if(hCurItem == hRoot)//is root
		return;

	//delete child tree
	HTREEITEM p;
	p = m_TreeDir.GetChildItem(hCurItem);
	while(p != NULL)
	{
		m_TreeDir.DeleteItem(p);
		p = m_TreeDir.GetChildItem(hCurItem);
	}
	

	//find all path
	if(m_TreeDir.GetParentItem(hCurItem) == hRoot)
	{
		strcpy(CurDir, m_TreeDir.GetItemText(hCurItem));
		strcat(CurDir, "\\");
	}
	else
	{
		p = hCurItem;
		strcpy(CurDir, "");
		int n = 0;
		while(p != hRoot)
		{
			strcpy(temp, m_TreeDir.GetItemText(p));
			if(n == 0)
			{
				n = 1;
			}
			else
			strcat(temp, "\\");
			strcat(temp, CurDir);
			strcpy(CurDir, temp);
			p = m_TreeDir.GetParentItem(p);
		}
	}
	m_Show = CurDir;
	UpdateData(FALSE);
	if (hSelected != NULL
		&& hCurItem != m_TreeDir.GetRootItem()
		)
	{
		// Create the first child item.
		if(-1==_chdir(CurDir))
			MessageBox("chdir error");
		_finddata_t FileInfo, FileInfo_temp;
		cur_n = _findfirst("*.*", &FileInfo);
		if(cur_n == -1)
			MessageBox("error first");
	
		TV_INSERTSTRUCT tvInsert;
		tvItem.mask =
			TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		while(0==_findnext(cur_n, &FileInfo))
		{
			strcpy(temp, FileInfo.name);
			if(strcmp(temp, "..") == 0)
				continue;
			tvItem.pszText = temp;
			tvItem.cchTextMax = strlen(temp);
			if(FileInfo.attrib == FILE_ATTRIBUTE_DIRECTORY)
			{
				tvItem.iImage = 4;
				tvItem.iSelectedImage = 5;
				tvInsert.hParent = hCurItem;
				tvInsert.hInsertAfter = TVI_FIRST;
				tvInsert.item = tvItem;
				HTREEITEM temp_Item =  m_TreeDir.InsertItem(&tvInsert);
				//find child's children
				char temp_child[261];
				strcpy(temp_child, CurDir);
				if(m_TreeDir.GetParentItem(hCurItem) != hRoot)
					strcat(temp_child, "\\");
				strcat(temp_child, temp);
				if(-1==_chdir(temp_child))
					MessageBox("2chdir error");
				int cur_n_temp = _findfirst("*.*", &FileInfo_temp);
				if(cur_n_temp == -1)
					MessageBox("error first");
				int temp_z_n = 0;
				while(0 == _findnext(cur_n_temp, &FileInfo_temp))
				{
					temp_z_n++;
					strcpy(temp, FileInfo.name);
					if(strcmp(temp, "..") != 0 && temp_z_n >1)
					{
						tvItem.pszText = temp;
						tvItem.cchTextMax = strlen(temp);
						tvInsert.hParent = temp_Item;
						tvInsert.hInsertAfter = TVI_FIRST;
						tvInsert.item = tvItem;
						m_TreeDir.InsertItem(&tvInsert);
					}
				}
				if(strcmp(temp, "..") == 0)
					continue;
			}
			else
			{
				tvItem.iImage = 6;
				tvItem.iSelectedImage = 6;
				tvInsert.hParent = hCurItem;
				tvInsert.hInsertAfter = TVI_FIRST;
				tvInsert.item = tvItem;
				m_TreeDir.InsertItem(&tvInsert);
			}
		}
	}
	return;
	UpdateData(FALSE);

	*pResult = 0;
}

void CHomework3Dlg::OnItemexpandedTreeDir(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	OnSelchangedTreeDir(pNMHDR, pResult);
	*pResult = 0;
}
