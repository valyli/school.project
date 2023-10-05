// linktext.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLinkTextDlg dialog

class CLinkTextDlg : public CDialog
{
// Construction
public:
	CLinkTextDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLinkTextDlg)
	enum { IDD = IDD_DIALOG1 };
	CString	m_linkText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinkTextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinkTextDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
