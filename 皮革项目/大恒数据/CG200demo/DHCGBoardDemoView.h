// DHCGBoardDemoView.h : interface of the CDHCGBoardDemoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DHCGBOARDDEMOVIEW_H__591A7391_C6AB_11D4_8E81_5254AB30C250__INCLUDED_)
#define AFX_DHCGBOARDDEMOVIEW_H__591A7391_C6AB_11D4_8E81_5254AB30C250__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "dhcgboard.h"

class CDHCGBoardDemoView : public CScrollView
{
protected: // create from serialization only
	CDHCGBoardDemoView();
	DECLARE_DYNCREATE(CDHCGBoardDemoView)

// Attributes
public:
	CDHCGBoardDemoDoc* GetDocument();
	BOOL m_bFreeze;	//ͼ���Ƿ�  0��� 1������
	CDhcgBoard cgBoard;//ͼ�󿨲�����
	BOOL m_bDDraw;	//�Ƿ�ʹ��DirectX��ʽ��ʾͼ��
	CRect InputVideoRect;	//ͼ����Ƶ���봰�ڣ�Ϊ�û���ʼ�趨
	bool m_bMask;//�Ƿ�����

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHCGBoardDemoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrintPreview(CDC* pDC, CPrintInfo* pInfo, POINT point, CPreviewView* pView);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL m_bInitCGboard;
	//	bool m_bPrePrint;
	BOOL m_bAutoFormat;
	
	void SetMask(CRect rect,bool bMask);//����Ļ��ʽ������������
	void InitVisualVideoRect(bool bToScreen);//��ʼ����ʾ���ڣ�bToScreen���Ƿ�ת��Ϊ��Ļ����
											//��Ҫ����Ϊд����ʽʹ����Ļָ�꣬DirectX��ʽʹ�ô�������
											//0����Ļ���꣬1����������
	void InitInputVideoRect();//ΪInputVideoRect��ֵ��������ScaollView��Size
	//	CRect DispVideoRect;
	HANDLE ReadDispWindowToHandle();//��ȡ��ʾ����ͼ��HANDLE
	void OnChangeViewSize();		//������ʾ���ں����봰��
	virtual ~CDHCGBoardDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDHCGBoardDemoView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCgcardAtuoformat();
	afx_msg void OnCgcardCg210para();
	afx_msg void OnCgcardMem();
	afx_msg void OnCgcardModeDirectx();
	afx_msg void OnCgcardModeScreen();
	afx_msg void OnCgcardParam();
	afx_msg void OnCgcardSnap();
	afx_msg void OnCgboardplay();
	afx_msg void OnUpdateCgcardCg210para(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgcardModeDirectx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgcardModeScreen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgboardplay(CCmdUI* pCmdUI);
	afx_msg void OnCgboardstop();
	afx_msg void OnUpdateCgboardstop(CCmdUI* pCmdUI);
	afx_msg void OnCgboardMask();
	afx_msg void OnUpdateCgboardMask(CCmdUI* pCmdUI);
	afx_msg void OnCgboardCapturemem();
	afx_msg void OnUpdateCgboardCapturemem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgcardAtuoformat(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgcardMem(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgcardParam(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCgcardSnap(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DHCGBoardDemoView.cpp
inline CDHCGBoardDemoDoc* CDHCGBoardDemoView::GetDocument()
   { return (CDHCGBoardDemoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DHCGBOARDDEMOVIEW_H__591A7391_C6AB_11D4_8E81_5254AB30C250__INCLUDED_)
