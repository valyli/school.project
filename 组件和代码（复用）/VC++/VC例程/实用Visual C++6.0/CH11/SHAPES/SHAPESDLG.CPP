// ShapesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Shapes.h"
#include "ShapesDlg.h"

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
// CShapesDlg dialog

CShapesDlg::CShapesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShapesDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShapesDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShapesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShapesDlg)
	DDX_Control(pDX, IDC_COMBOBOXEX1, m_combo);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShapesDlg, CDialog)
	//{{AFX_MSG_MAP(CShapesDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShapesDlg message handlers

BOOL CShapesDlg::OnInitDialog()
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
	// ** Creat some text names for the shape images
	static char* shape[] = {
		"Square","Rectangle","Parallelogram",
		"Trapezoid","Triangle","Octagon"};
	int nShapes = 6;

	// ** Load the bitmap resource
	CBitmap bitmap;
	VERIFY(bitmap.LoadBitmap(IDB_SHAPES));
	
	// ** Creat the image list and add the bitmap
	m_imagelist.Create(IDB_SHAPES,16,1,0);
	m_imagelist.Add(&bitmap, (COLORREF)0xFFFFF);

	// ** Set the list control to use the image list
	m_list.SetImageList(&m_imagelist, LVSIL_SMALL);

	// ** Insert 6 items into the list control
	// ** setting the iamge index
	for (int i = 0; i < nShapes; i++)
		m_list.InsertItem(i,shape[i],i);

	// ** set the tree control to use the image list
	m_tree.SetImageList(&m_imagelist,TVSIL_NORMAL);

	// ** Insert 2 top level items into the tree
	// ** set normal/seleted images to close/open folder
	HTREEITEM hTetrangons, hOther;
	hTetrangons = m_tree.InsertItem("Tetrangons",6,7);
	hOther = m_tree.InsertItem("Other",6,7);

	// ** insert first 3 shapes as subitems of 'Tetrangons'
	// ** and last 3 as subitems of 'Other'
	for(i = 0; i < nShapes; i++)
		m_tree.InsertItem(shape[i],i,i,i<3 ? hTetrangons : hOther);

	// ** Set the Combo box to use the image list
	m_combo.SetImageList(&m_imagelist);

	// ** Allocate a combo item structure and set the mask
	COMBOBOXEXITEM cbItem;
	cbItem.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE;

	// ** Insert 6 items into the combo box
	// ** set normal/seleted to the same image
	for(i = 0; i < nShapes; i++)
	{
		cbItem.pszText = shape[i];
		cbItem.iItem = i;
		cbItem.iImage = cbItem.iSelectedImage =i;
		m_combo.InsertItem(&cbItem);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShapesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CShapesDlg::OnPaint() 
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
HCURSOR CShapesDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
