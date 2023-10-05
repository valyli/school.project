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
	LOGFONT m_logFont;          // 用于文档的字体
	COLORREF m_crText;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInquireDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	// 打开一个学生数据文件。
	// 参数：lpszPathName为指向欲打开的学生数据文件名的指针。
	// 返回值：打开操作成功，则返回true，否则返回false。
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	// 保存一个学生数据文件。
	// 参数：lpszPathName为指向欲保存的学生数据文件名的指针。
	// 返回值：保存操作成功，则返回true，否则返回false。
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	// 根据排序关键字对学生集合进行排序并集合用排序后的集合数据刷新当前的显示。
	void Sorting();
	// 寻找集合中下一个记录，并在转换下一个记录之前，判断当前的记录是否被改变和确认是否要修改。
	bool NextRec();
	// 寻找集合中前一个记录，并在转换前一个记录之前，判断当前的记录是否被改变和确认是否要修改。
	bool PrevRec();
	// 寻找集合中最后一个记录，并在转换最后一个记录之前，判断当前的记录是否被改变和确认是否要修改。
	bool LastRec();
	// 寻找集合中第一个记录，并在转换第一个记录之前，判断当前的记录是否被改变和确认是否要修改。
	bool FirstRec();
	// 在学生集合中增加一个记录。
	void AddStudent();
	// 从学生集合中删除当前在数据输入输出对话框中显示的记录
	void DeleteStudent();
	CStudentSet m_StudentSet;	// 学生集合对象
	CDataIODlg* m_pDataIODlg;	// 指向数据输入输出对话框的指针
	virtual ~CInquireDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CInquireDoc)
	// 选择输出（显示或打印）字型。
	afx_msg void OnOptionFont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	// 依据数据输入输出对话框中显示的数据修改当前记录。
	// 返回值：如果修改了当前记录，则返回true，否则返回false。
	bool ModifyRec();
	// 从当前记录变到由集合的记录索引值指示的记录，并显示在数据输入输出对话框中。
	void ChangeRec();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INQUIREDOC_H__12B2F58D_29E7_11D5_88D8_AAF98AC2E0AE__INCLUDED_)
