// 媒体播放器Dlg.h : header file
//
//developer xiadong (CNU)
//{{AFX_INCLUDES()
#include "msmask.h"
//}}AFX_INCLUDES

#if !defined(AFX_DLG_H__66BB7ED1_3A0F_4F5E_98EB_75E7A940537E__INCLUDED_)
#define AFX_DLG_H__66BB7ED1_3A0F_4F5E_98EB_75E7A940537E__INCLUDED_


#if _MSC_VER > 1000 
#pragma once
#endif // _MSC_VER > 1000
#include "IVolume.h"
#include "VolumeInXXX.h"
#include "VolumeOutWave.h"
#include "VolumeOutMaster.h"

/////////////////////////////////////////////////////////////////////////////
// CMyDlg dialog

class CMyDlg : public CDialog
{
// Construction
public:
	
	CMyDlg(CWnd* pParent = NULL);	// standard constructor
    int track,t;
	BOOL tip;
	int m,s,f,ml,sl,state,trackl;
    int door;
	// Dialog Data
	//{{AFX_DATA(CMyDlg)
	enum { IDD = IDD_MY_DIALOG };
	CBitmapButton	m_min;
	CBitmapButton	m_about;
	CBitmapButton	m_close;
	CBitmapButton	m_door;
	CSliderCtrl	m_vol;
	CSliderCtrl	m_time;
    CBitmapButton	m_open;
	CBitmapButton	m_next;
	CBitmapButton	m_last;
	CBitmapButton	m_back;
	CBitmapButton	m_before;
	CBitmapButton	m_stop;
	CBitmapButton	m_pause;
	CBitmapButton m_play;
	CMSMask	m_show;
	CMSMask	m_count;
	CMSMask	m_current;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL
private:
		void ShowError(DWORD dwError);
// Implementation
protected:
	HICON m_hIcon;
    BOOL m_bPlay;//是否在播放文件
	BOOL m_bPause;//是否已暂停播放文件
	int  Iscda;  //判断是否为播放CD文件
	MCIDEVICEID m_MCIDeviceID;
    HWND m_hMainWnd;
	// Generated message map functions
	//{{AFX_MSG(CMyDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onplay();
	afx_msg void Onstop();
	afx_msg void Onpause();
	afx_msg void Onopen();
	afx_msg void Onclose();
	afx_msg void OnDestroy();
	afx_msg void Onnext();
	afx_msg void Onlast();
	afx_msg void Onbefore();
	afx_msg void Onback();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void Ondoor();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void Onabout();
	afx_msg void Onmin();
	//}}AFX_MSG
    afx_msg LRESULT OnMciNotify(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLG_H__66BB7ED1_3A0F_4F5E_98EB_75E7A940537E__INCLUDED_)
