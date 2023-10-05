// InquireView.h : interface of the CInquireView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INQUIREVIEW_H__12B2F58F_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
#define AFX_INQUIREVIEW_H__12B2F58F_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "InquireDoc.h"
#include "dlink.h"	// Added by ClassView

const WM_SUBMIT		= WM_USER + 10;	// �¼�¼�ύ������Ϣ
const WM_DELETE		= WM_USER + 11;	// ��¼ɾ��������Ϣ
const WM_FIRST_REC	= WM_USER + 12;	// Ѱ�Ҳ���ʾ�����е�һ����¼������Ϣ
const WM_LAST_REC	= WM_USER + 13;	// Ѱ�Ҳ���ʾ���������һ����¼������Ϣ
const WM_PREV_REC	= WM_USER + 14;	// Ѱ�Ҳ���ʾ������ǰһ����¼������Ϣ
const WM_NEXT_REC	= WM_USER + 15;	// Ѱ�Ҳ���ʾ��������һ����¼������Ϣ
const WM_SORTING	= WM_USER + 16;	// ���������Ϣ

class CInquireView : public CScrollView
{
protected: // create from serialization only
	CInquireView();
	DECLARE_DYNCREATE(CInquireView)

// Attributes
public:
	CInquireDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInquireView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_RetrieveKey;
	State m_Retrieve;
	State m_Sort;
	virtual ~CInquireView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInquireView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	// ��ʾ������������Ի���Լ��Ͻ��м����¼���޸ļ�¼��ɾ����¼�ͼ��ϵ����򼰼�����
	afx_msg void OnRegistration();
	//}}AFX_MSG
	// �ύ�¼�¼��������Ӧ������
	afx_msg LONG OnSubmit(WPARAM wParam, LPARAM lParam);
	// ɾ����¼��������Ӧ������
	afx_msg LONG OnDelete(WPARAM wParam, LPARAM lParam);
	// Ѱ�Ҳ���ʾ�����е�һ����¼��������Ӧ������
	afx_msg LONG OnFirstRec(WPARAM wParam, LPARAM lParam);
	// Ѱ�Ҳ���ʾ���������һ����¼��������Ӧ������
	afx_msg LONG OnLastRec(WPARAM wParam, LPARAM lParam);
	// Ѱ�Ҳ���ʾ������ǰһ����¼��������Ӧ������
	afx_msg LONG OnPrevRec(WPARAM wParam, LPARAM lParam);
	// Ѱ�Ҳ���ʾ��������һ����¼��������Ӧ������
	afx_msg LONG OnNextRec(WPARAM wParam, LPARAM lParam);
	// ��������ؼ��ֶԼ��Ͻ��������������Ӧ������
	afx_msg LONG OnSorting(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in InquireView.cpp
inline CInquireDoc* CInquireView::GetDocument()
   { return (CInquireDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INQUIREVIEW_H__12B2F58F_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
