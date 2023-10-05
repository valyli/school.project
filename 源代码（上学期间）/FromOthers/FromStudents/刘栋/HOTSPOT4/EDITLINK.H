// editlink.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CEditLinkDlg dialog

class CEditLinkDlg : public CDialog
{
// Construction
public:
	CEditLinkDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEditLinkDlg)
	enum { IDD = IDD_DIALOG2 };
	int		m_selectedLink;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditLinkDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEditLinkDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDelete();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
