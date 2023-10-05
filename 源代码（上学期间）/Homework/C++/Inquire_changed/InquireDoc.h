// InquireDoc.h : interface of the CInquireDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_INQUIREDOC_H__12B2F58D_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
#define AFX_INQUIREDOC_H__12B2F58D_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_

#include "resclass.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "resclass.h"
#include "dlink.h"


class CInquireDoc : public CDocument
{
protected: // create from serialization only
	CInquireDoc();
	DECLARE_DYNCREATE(CInquireDoc)

// Attributes
public:
	LOGFONT m_logFont;          // �����ĵ�������
	COLORREF m_crText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInquireDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	// ��һ��ѧ�������ļ���
	// ������lpszPathNameΪָ�����򿪵�ѧ�������ļ�����ָ�롣
	// ����ֵ���򿪲����ɹ����򷵻�true�����򷵻�false��
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	// ����һ��ѧ�������ļ���
	// ������lpszPathNameΪָ���������ѧ�������ļ�����ָ�롣
	// ����ֵ����������ɹ����򷵻�true�����򷵻�false��
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	// ��������ؼ��ֶ�ѧ�����Ͻ������򲢼����������ļ�������ˢ�µ�ǰ����ʾ��
	void Sorting();
	// Ѱ�Ҽ�������һ����¼������ת����һ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
	bool NextRec();
	// Ѱ�Ҽ�����ǰһ����¼������ת��ǰһ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
	bool PrevRec();
	// Ѱ�Ҽ��������һ����¼������ת�����һ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
	bool LastRec();
	// Ѱ�Ҽ����е�һ����¼������ת����һ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
	bool FirstRec();
	// ��ѧ������������һ����¼��
	void AddStudent();
	// ��ѧ��������ɾ����ǰ��������������Ի�������ʾ�ļ�¼
	void DeleteStudent();
	CStudentSet m_StudentSet;	// ѧ�����϶���
	CDataIODlg* m_pDataIODlg;	// ָ��������������Ի����ָ��
	virtual ~CInquireDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInquireDoc)
	// ѡ���������ʾ���ӡ�����͡�
	afx_msg void OnOptionFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// ����������������Ի�������ʾ�������޸ĵ�ǰ��¼��
	// ����ֵ������޸��˵�ǰ��¼���򷵻�true�����򷵻�false��
	bool ModifyRec();
	// �ӵ�ǰ��¼�䵽�ɼ��ϵļ�¼����ֵָʾ�ļ�¼������ʾ��������������Ի����С�
	void ChangeRec();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INQUIREDOC_H__12B2F58D_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
