// RunTestDlg.h : header file
//

#if !defined(AFX_RUNTESTDLG_H__7965BAEB_98C5_43D7_B13B_ADB5EDA1A8D5__INCLUDED_)
#define AFX_RUNTESTDLG_H__7965BAEB_98C5_43D7_B13B_ADB5EDA1A8D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CRunTestDlg dialog

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//声明系统类型变量的枚举类型
typedef enum tagWin32SysType
{
	Windows32s,
	WindowsNT3,
	Windows95,
	Windows98,
	WindowsME,
	WindowsNT4,
	Windows2000,
	WindowsXP
}Win32SysType;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//用于记录检测结果的结构体定义
struct InfoOfHardDiskDevice
{
	//记录是否存在硬盘1存在、0不存在
	int IsExist;
	//记录硬盘序号(1、2、3、4)
	int NoOfController;
	char strNoOfController[1024];
	//记录硬盘主从0主、1从
	int LevelOfController;
	char strLevelOfController[1024];
	//硬盘序列号
	char DriveSerialNumber[1024];
	//硬盘型号
	char DriveModelNumber[1024];
	//硬盘控制器版本号
	char DriveControllerRevisionNumber[1024];
	//控制器缓存大小
	unsigned long ControllerBufferSizeonDrive;
	//Drive Type
	//0,Removable
	//1,Fixed
	//2,Unknown
	int DriveType;
	char strDriveType[1024];
	//Physical Geometry
	int Cylinders;
	int Heads;
	int SectorsPerTrack;
};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


class CRunTestDlg : public CDialog
{
// Construction
public:
	CRunTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRunTestDlg)
	enum { IDD = IDD_RUNTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRunTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRunTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonChecksystemversion();
	afx_msg void OnButtonCheckdllversion();
	afx_msg void OnButtonCheckBios();
	afx_msg void OnButtonCheckHarddisk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RUNTESTDLG_H__7965BAEB_98C5_43D7_B13B_ADB5EDA1A8D5__INCLUDED_)
