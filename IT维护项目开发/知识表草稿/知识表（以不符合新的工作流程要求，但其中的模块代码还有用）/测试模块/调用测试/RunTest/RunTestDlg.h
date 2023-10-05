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
//����ϵͳ���ͱ�����ö������
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
//���ڼ�¼������Ľṹ�嶨��
struct InfoOfHardDiskDevice
{
	//��¼�Ƿ����Ӳ��1���ڡ�0������
	int IsExist;
	//��¼Ӳ�����(1��2��3��4)
	int NoOfController;
	char strNoOfController[1024];
	//��¼Ӳ������0����1��
	int LevelOfController;
	char strLevelOfController[1024];
	//Ӳ�����к�
	char DriveSerialNumber[1024];
	//Ӳ���ͺ�
	char DriveModelNumber[1024];
	//Ӳ�̿������汾��
	char DriveControllerRevisionNumber[1024];
	//�����������С
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
