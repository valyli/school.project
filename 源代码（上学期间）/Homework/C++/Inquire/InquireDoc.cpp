// InquireDoc.cpp : implementation of the CInquireDoc class
//

#include "stdafx.h"
#include "Inquire.h"

#include "InquireDoc.h"
#include "InquireView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
State CStudent::m_Sort = none;			// 初始化排序关键字
State CStudent::m_Retrieve = none;		// 初始化检索主关键字
CString CStudent::m_RetrieveKey = "";	// 初始化检索辅助关键字
int CStudent::m_FieldWidth[] = {14,18,/*14,*/6,6,14,24,/*14,*/10,10,12,14,14};	//初始化格式域宽

/////////////////////////////////////////////////////////////////////////////
// CInquireDoc

IMPLEMENT_DYNCREATE(CInquireDoc, CDocument)

BEGIN_MESSAGE_MAP(CInquireDoc, CDocument)
	//{{AFX_MSG_MAP(CInquireDoc)
	ON_COMMAND(ID_OPTION_FONT, OnOptionFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInquireDoc construction/destruction

CInquireDoc::CInquireDoc()
{
	// determine default font for document
	m_logFont = ((CInquireApp*)AfxGetApp())->m_logFont;

	// use default window text color
	m_crText = COLOR_WINDOWTEXT+1;
	m_pDataIODlg = NULL;
}

CInquireDoc::~CInquireDoc()
{
	if(m_pDataIODlg)
		delete m_pDataIODlg;
}

BOOL CInquireDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CInquireDoc serialization

void CInquireDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CInquireDoc diagnostics

#ifdef _DEBUG
void CInquireDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CInquireDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInquireDoc commands

// 选择输出（显示或打印）字型。
void CInquireDoc::OnOptionFont() 
{
	CClientDC dc(NULL);
	LOGFONT lf = m_logFont;
	lf.lfHeight = -::MulDiv(-lf.lfHeight, dc.GetDeviceCaps(LOGPIXELSY), 72);
	CFontDialog dlg(&lf);
	dlg.m_cf.rgbColors = m_crText;
	if (dlg.DoModal() == IDOK)
	{
		lf.lfHeight = -::MulDiv(-lf.lfHeight, 72, dc.GetDeviceCaps(LOGPIXELSY));
		m_crText = dlg.GetColor();
		m_logFont = ((CInquireApp*)AfxGetApp())->m_logFont = lf;
		SetModifiedFlag();
		UpdateAllViews(NULL);
	}
}

// 在学生集合中增加一个记录。
void CInquireDoc::AddStudent()
{
	CStudent student;
	m_pDataIODlg->m_RegistDate = m_pDataIODlg->m_RegistDate.GetCurrentTime();
	m_pDataIODlg->m_UpdateDate = m_pDataIODlg->m_UpdateDate.GetCurrentTime();
	student.Read(m_pDataIODlg);
	int index = m_StudentSet.Index();
	if(!m_StudentSet.InsertAfter(student))
		m_StudentSet.Index(index);
	else
	{
		SetModifiedFlag();
		m_pDataIODlg->NoSort();
		m_pDataIODlg->NoRetrieve();
		UpdateAllViews(NULL);
	}
}

// 从学生集合中删除当前在数据输入输出对话框中显示的记录
void CInquireDoc::DeleteStudent()
{
	CStudent student;
	node<CStudent> *p;
	student.Read(m_pDataIODlg);
	if(m_StudentSet.Delete(student))
	{
		SetModifiedFlag();
		p = m_StudentSet.Get(m_StudentSet.Index());
		if(p)
			p->items.Write(m_pDataIODlg);
		UpdateAllViews(NULL);
	}
}

// 寻找集合中第一个记录，并在转换第一个记录之前，判断当前的记录是否被改变和确认是否要修改。
bool CInquireDoc::FirstRec()
{
	bool flag = false;
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.FirstIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// 寻找集合中最后一个记录，并在转换最后一个记录之前，判断当前的记录是否被改变和确认是否要修改。
bool CInquireDoc::LastRec()
{
	bool flag = false;
	// 在此加入码段
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.LastIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// 寻找集合中前一个记录，并在转换前一个记录之前，判断当前的记录是否被改变和确认是否要修改。
bool CInquireDoc::PrevRec()
{
	bool flag = false;
	// 在此加入码段
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.PrevIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// 寻找集合中下一个记录，并在转换下一个记录之前，判断当前的记录是否被改变和确认是否要修改。
bool CInquireDoc::NextRec()
{
	bool flag = false;
	// 在此加入码段
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.NextIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// 从当前记录变到由集合的记录索引值指示的记录，并显示在数据输入输出对话框中。
void CInquireDoc::ChangeRec()
{
	node<CStudent> *p = m_StudentSet.Get(m_StudentSet.Index());
	if(p)
		p->items.Write(m_pDataIODlg);
}

// 依据数据输入输出对话框中显示的数据修改当前记录。
// 返回值：如果修改了当前记录，则返回true，否则返回false。
bool CInquireDoc::ModifyRec()
{
	bool flag = false;
	CStudent modified;
	int index = m_StudentSet.Index();
	modified.Read(m_pDataIODlg);
	node<CStudent> *p = m_StudentSet.Get(m_StudentSet.Index());
	if(p)
	{
		if(((p->items != modified) && (p->items == modified)) ||
			(!(p->items == modified) && (!m_StudentSet.contains(modified))))
		{
			int result = MessageBox(NULL, "当前记录已被修改，是否保存？",
						"修改提示" , MB_YESNOCANCEL | MB_ICONQUESTION);
			if(result == IDYES)
			{
				p->items = modified;
				p->items.ModifyUpdateDate();
				UpdateAllViews(NULL);
				SetModifiedFlag();
				flag = true;
			}
			else if(result == IDNO)
				flag = true;
			else
				flag = false;
		}
		else if(!(p->items == modified) && (m_StudentSet.contains(modified)))
		{
			MessageBox(NULL, "欲提交记录的学号已存在！请重新修改学号。",
						"提交警告", MB_OK | MB_ICONERROR);
			flag = false;
		}
		else
			flag = true;
	}
	m_StudentSet.Index(index);
	return flag;
}

// 根据排序关键字对学生集合进行排序并集合用排序后的集合数据刷新当前的显示。
void CInquireDoc::Sorting()
{
	if((m_StudentSet.Size() > 1) && (CStudent::m_Sort != none))
	{
		m_StudentSet.MergeSort();
		UpdateAllViews(NULL);
		SetModifiedFlag();
		ChangeRec();
	}
}

// 打开一个学生数据文件。
// 参数：lpszPathName为指向欲打开的学生数据文件名的指针。
// 返回值：打开操作成功，则返回true，否则返回false。
BOOL CInquireDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL flag = FALSE;
//	int length;
//	char buffer[21];
	fstream in(lpszPathName, ios::in | ios::binary);
	if(!in)
	{
		MessageBox(NULL, "不能打开学生数据库输出文件！",
					"打开错误", MB_OK | MB_ICONERROR);
	}
	else
	{
		CString idCard;
		in.read(idCard.GetBuffer(3), 3);
//		idCard = buffer;
		if(idCard == "SDB")
		{
			int recNum;
			in.read((char*)&recNum, sizeof(int));
			in.read((char*)&m_logFont, sizeof(m_logFont));
			if(recNum)
			{
				for(int i = 0; i < recNum; i++)
				{
					CStudent student;
					student.Read(in);
					int index = m_StudentSet.Index();
					if(!m_StudentSet.InsertAfter(student))
					{
						m_StudentSet.Index(index);
						MessageBox(NULL, "不能生成学生数据链表！",
								"打开错误", MB_OK | MB_ICONERROR);
						in.close();
						goto End;
					}
				}
			}
			m_StudentSet.Index(0);
			in.close();
			CStudent::m_Sort = none;
			CStudent::m_Retrieve = none;
			flag = TRUE;
		}
		else
		{
			MessageBox(NULL, "欲打开的文件不是学生数据库文件！",
						"打开错误", MB_OK | MB_ICONERROR);
		}
	}
End:return flag;
}

// 保存一个学生数据文件。
// 参数：lpszPathName为指向欲保存的学生数据文件名的指针。
// 返回值：保存操作成功，则返回true，否则返回false。
BOOL CInquireDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	BOOL flag = FALSE;
	// 在此加入码段，并将信息框加到适当的位置。
	fstream out(lpszPathName, ios::out | ios::binary);
	if(!out)
	{
		MessageBox(NULL, "不能打开或创建输出文件！",
					"保存错误", MB_OK | MB_ICONERROR);
	}
	else
	{
		CString idCard = "SDB";
		out.write(idCard.GetBuffer(3), 3);
		int recNum = m_StudentSet.Size();
		out.write((char*)&recNum, sizeof(int));
		out.write((char*)&m_logFont, sizeof(m_logFont));
		if(recNum)
		{
			for(int i = 0; i < recNum; i++)
				m_StudentSet.Get(i)->items.Write(out);
//						MessageBox(NULL, "不能生成学生数据链表！",
//								"打开错误", MB_OK | MB_ICONERROR);
			out.close();
			flag = TRUE;
		}
//		else
//		{
//			MessageBox(NULL, "欲打开的文件不是学生数据库文件！",
//						"打开错误", MB_OK | MB_ICONERROR);
//		}
	}
//		MessageBox(NULL, "不能打开或创建输出文件！",
//					"保存错误", MB_OK | MB_ICONERROR);
	return flag;
}
