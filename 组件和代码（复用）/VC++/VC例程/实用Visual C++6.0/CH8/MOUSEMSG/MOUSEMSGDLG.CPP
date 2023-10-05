// MouseMsgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseMsg.h"
#include "MouseMsgDlg.h"

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
// CMouseMsgDlg dialog

CMouseMsgDlg::CMouseMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseMsgDlg::IDD, pParent),
	m_RectTracker(CRect(0,0,0,0),
 //** Initial rectangle
   CRectTracker::hatchedBorder +
//** Hatched border
   CRectTracker::resizeOutside)
  //** Outsize handles
{
	//{{AFX_DATA_INIT(CMouseMsgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMouseMsgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMouseMsgDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseMsgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseMsgDlg message handlers

BOOL CMouseMsgDlg::OnInitDialog()
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMouseMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMouseMsgDlg::OnPaint() 
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
		// ** Creat a device context for drawing
		CPaintDC dc(this);

		// ** Find the dialog dimensions
		CRect rcDlg;
		GetClientRect(&rcDlg);

		// ** Loop twice, once for each eye
		for (int i=0;i<2;i++)
		{
			// ** Find the center of the eye
			CPoint ptEye = rcDlg.CenterPoint();

			// ** Set the eye position for each eye
			ptEye.x += i==0 ? -80 : +80;

			// ** Make an eye rectangle
			CRect rcEye(ptEye,ptEye);
			rcEye.InflateRect(40,60);

			// ** Draw an eye white
			if (m_RectTracker.HitTest(rcEye.CenterPoint())!=CRectTracker::hitNothing)
				dc.SelectStockObject(GRAY_BRUSH);
			else
				dc.SelectStockObject(WHITE_BRUSH);
			dc.Ellipse(rcEye);
			rcEye.DeflateRect(20,40);

			// ** use the mouse position to update the pupil
			CPoint ptRel = m_ptMouse - rcEye.CenterPoint();
			double dX = (double)ptRel.x * (rcEye.Width() / (double)rcDlg.Width());
			double dY = (double)ptRel.y * (rcEye.Height() / (double)rcDlg.Height());

			// ** Move the pupil position and draw it
			rcEye.OffsetRect(CPoint((int)dX,(int)dY));
			dc.SelectStockObject(BLACK_BRUSH);
			dc.Ellipse(rcEye);
		}

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMouseMsgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMouseMsgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_ptButton = point;   // ** Store the passed point
   
	m_RectTracker.TrackRubberBand(this,point,TRUE);
	CDialog::OnLButtonDown(nFlags, point);
}

void CMouseMsgDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	   
	CDialog::OnLButtonUp(nFlags, point);
}

void CMouseMsgDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	AfxMessageBox("Left Button Double Clicked");
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CMouseMsgDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	// ** Display the mouse position
	CString strMessage;
	strMessage.Format("Mouse Position = (%d,%d)",point.x,point.y);
	SetWindowText(strMessage);

	// ** Store the point and reddraw the window
	m_ptMouse = point;
	Invalidate();
	
	CDialog::OnMouseMove(nFlags, point);
}
