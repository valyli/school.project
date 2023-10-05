// ListsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lists.h"
#include "ListsDlg.h"

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
// CListsDlg dialog

CListsDlg::CListsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CListsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CListsDlg)
	DDX_Control(pDX, IDC_MAIN_DIR, m_cbMainDir);
	DDX_Control(pDX, IDC_SELECTED_DIRS, m_lcDirDetails);
	DDX_Control(pDX, IDC_SUB_DIRS, m_lbSubDirs);
	DDX_Control(pDX, IDC_FILES_TREE, m_treeFiles);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CListsDlg, CDialog)
	//{{AFX_MSG_MAP(CListsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_MAIN_DIR, OnSelchangeMainDir)
	ON_LBN_SELCHANGE(IDC_SUB_DIRS, OnSelchangeSubDirs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CListsDlg message handlers

BOOL CListsDlg::OnInitDialog()
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
	// ** Initialize the main diretory combo box
	PopulateCombo();
	//** Initialize the list control columns
	m_lcDirDetails.InsertColumn(0,"Directory",LVCFMT_LEFT,70);
	m_lcDirDetails.InsertColumn(1,"Files",LVCFMT_RIGHT,50);
	m_lcDirDetails.InsertColumn(2,"Size KB",LVCFMT_RIGHT,60);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CListsDlg::PopulateCombo()
{
	TCHAR szBuffer[MAX_PATH];

	// ** Get the Windows directory, usually C:\Windows
	// ** and add to the combo box
	GetWindowsDirectory(szBuffer,MAX_PATH);
	m_cbMainDir.AddString(szBuffer);

	// ** Chop off the directory to leave the drive letter C:
	// ** and add to the combo box
	szBuffer[2]=0;
	m_cbMainDir.AddString(szBuffer);

	// ** Get the System directory, usually C:\Windows\System
	// ** and add to the combo box
	GetSystemDirectory(szBuffer,MAX_PATH);
	m_cbMainDir.AddString(szBuffer);

	// ** Get the present directory and add to the combo box
	GetCurrentDirectory(MAX_PATH,szBuffer);
	m_cbMainDir.AddString(szBuffer);
}

void CListsDlg::PopulateTree()
{
	// ** Remove all existing tree items
	m_treeFiles.DeleteAllItems();
	// ** Allocate an array of HTREEITEMS
	HTREEITEM hLetter[27];
	// ** Insert items 'A' through 'Z' as root items
	for (int nChar = 'A'; nChar<='Z'; nChar++)
		hLetter[nChar-'A'] = m_treeFiles.InsertItem((TCHAR*)&nChar);

	// ** Insert 'Other' item as a root items
	hLetter[26] = m_treeFiles.InsertItem("Other");

	HANDLE hFind;
	WIN32_FIND_DATA dataFind;
	BOOL bMoreFiles = TRUE;
	CString strFile;

	// ** Continue to first file in tht main directory
	hFind = FindFirstFile(m_strMainDir + "\\*.*",&dataFind);

	// ** Continue to loop until all files have been found
	while(hFind!=INVALID_HANDLE_VALUE && bMoreFiles ==TRUE)
	{
		// ** Check a file has been found and not a directory
		if(dataFind.dwFileAttributes==FILE_ATTRIBUTE_ARCHIVE)
		{
			// ** Get the first letter of the file name
			int nChar = dataFind.cFileName[0];
			// ** Convert lower case letter to upper casr 
			if (islower(nChar))
				nChar-=32;
			// ** If the file name starts with letter then
			// ** subtract 'A' to find the index in to 
			// ** the hLetter array, for others use index 26
			if (isalpha(nChar))
				nChar-='A';
			else
				nChar=26;
			 
			// ** Insert the file name in to the tree
			m_treeFiles.InsertItem(dataFind.cFileName,hLetter[nChar]);
		}
		// ** Find the next file in the main directory
		bMoreFiles = FindNextFile(hFind,&dataFind);
	}
	// ** clse the file handle
	FindClose(hFind);
}

void CListsDlg::PopulateListBox()
{
	// ** Remove all existing list box items
	m_lbSubDirs.ResetContent();

	HANDLE hFind;
	WIN32_FIND_DATA dataFind;
	BOOL bMoreFiles = TRUE;

	// ** Find the first file in the main directory
	hFind = FindFirstFile(m_strMainDir + "\\*.*",&dataFind);

	// ** Continue to loop until all files have been found
	while(hFind!=INVALID_HANDLE_VALUE && bMoreFiles ==TRUE)
	{
		// ** Check if a directory has been found
		if(dataFind.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
			// ** Add the directory name to the list box
			// ** ignored the "." and ".." directory entries
			if(strcmp(dataFind.cFileName,"."))
				if(strcmp(dataFind.cFileName,".."))
					m_lbSubDirs.AddString(dataFind.cFileName);
		}
		// ** Find the next file in the main directory
		bMoreFiles = FindNextFile(hFind,&dataFind);
	}
	// ** clse the file handle
	FindClose(hFind);
}

void CListsDlg::PopulateListControl()
{
	// ** Remove All existing list control items
	m_lcDirDetails.DeleteAllItems();

	POSITION pos;
	// ** Iterate round the list of directories selected
	// ** from the list box
	for(pos = m_strList.GetHeadPosition();pos !=NULL;)
	{
		int nItem;
		HANDLE hFind;
		WIN32_FIND_DATA dataFind;
		BOOL bMoreFiles = TRUE;
		CString str;
		CString strFind;

		str = m_strList.GetAt(pos);
		// ** Add a row to the list control (column 0)
		nItem = m_lcDirDetails.InsertItem(0,str);

		strFind = m_strMainDir+"\\"+str+"\\*.*";
		hFind = FindFirstFile(strFind,&dataFind);

		int nFileCount=0;
		double nFileSize=0;

		// ** loop finding each file in the directory and
		// ** total up the files count and size variable
		while(hFind!=INVALID_HANDLE_VALUE && bMoreFiles ==TRUE)
		{
			if(dataFind.dwFileAttributes==FILE_ATTRIBUTE_ARCHIVE)
			{
				nFileCount++;
				nFileSize += (dataFind.nFileSizeHigh * MAXDWORD)
					+ dataFind.nFileSizeLow;
			}
			bMoreFiles = FindNextFile(hFind,&dataFind);
		}
		// ** close the file handle
		FindClose(hFind);

		// ** format the text of the file count and
		// ** insert it as column 1
		str.Format("%ld",nFileCount);
		m_lcDirDetails.SetItemText(nItem,1,str);

		// ** format the text of the file size and
		// ** insert it as column 2
		str.Format("%-1.2f",nFileSize/ 1024.0);
		m_lcDirDetails.SetItemText(nItem,2,str);

		m_strList.GetNext(pos);
	}
}



void CListsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListsDlg::OnPaint() 
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
HCURSOR CListsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CListsDlg::OnSelchangeMainDir() 
{
	// TODO: Add your control notification handler code here
	// ** Retrieve the index of the selected item
	int nIndex = m_cbMainDir.GetCurSel();

	// ** Check the index is valid
	if (nIndex != CB_ERR)
	{
		// ** Get the text of the selected item and store in a
		// ** member variable and call function to populate
		// ** the other controls
		m_cbMainDir.GetLBText(nIndex,m_strMainDir);
		PopulateTree();
		PopulateListBox();
	}
}

void CListsDlg::OnSelchangeSubDirs() 
{
	// TODO: Add your control notification handler code here
	// ** Get the number of selection items
	int nSelCount = m_lbSubDirs.GetSelCount();

	// ** Clear the string list
	m_strList.RemoveAll();
	if (nSelCount)
	{
		CString str;
		// ** Creat an int array to store the indexes and
		// ** initialize with the indexes of selected items
		LPINT pItems = new int[nSelCount];
		m_lbSubDirs.GetSelItems(nSelCount,pItems);

		for( int i=0; i<nSelCount; i++)
		{
			// ** Retrieve selected item text and
			// ** store it in a string list
			m_lbSubDirs.GetText(pItems[i],str);
			m_strList.AddTail(str);
		}
		// ** tidy up the int array
		delete [] pItems;
	}
	// ** Now populate the list control
	PopulateListControl();
}
	

