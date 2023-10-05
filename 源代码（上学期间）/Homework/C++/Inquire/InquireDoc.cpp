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
State CStudent::m_Sort = none;			// ��ʼ������ؼ���
State CStudent::m_Retrieve = none;		// ��ʼ���������ؼ���
CString CStudent::m_RetrieveKey = "";	// ��ʼ�����������ؼ���
int CStudent::m_FieldWidth[] = {14,18,/*14,*/6,6,14,24,/*14,*/10,10,12,14,14};	//��ʼ����ʽ���

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

// ѡ���������ʾ���ӡ�����͡�
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

// ��ѧ������������һ����¼��
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

// ��ѧ��������ɾ����ǰ��������������Ի�������ʾ�ļ�¼
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

// Ѱ�Ҽ����е�һ����¼������ת����һ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
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

// Ѱ�Ҽ��������һ����¼������ת�����һ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
bool CInquireDoc::LastRec()
{
	bool flag = false;
	// �ڴ˼������
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.LastIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// Ѱ�Ҽ�����ǰһ����¼������ת��ǰһ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
bool CInquireDoc::PrevRec()
{
	bool flag = false;
	// �ڴ˼������
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.PrevIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// Ѱ�Ҽ�������һ����¼������ת����һ����¼֮ǰ���жϵ�ǰ�ļ�¼�Ƿ񱻸ı��ȷ���Ƿ�Ҫ�޸ġ�
bool CInquireDoc::NextRec()
{
	bool flag = false;
	// �ڴ˼������
	if(ModifyRec())
	{
		m_StudentSet.Index(m_StudentSet.NextIndex());
		ChangeRec();
		flag = true;
	}
	return flag;
}

// �ӵ�ǰ��¼�䵽�ɼ��ϵļ�¼����ֵָʾ�ļ�¼������ʾ��������������Ի����С�
void CInquireDoc::ChangeRec()
{
	node<CStudent> *p = m_StudentSet.Get(m_StudentSet.Index());
	if(p)
		p->items.Write(m_pDataIODlg);
}

// ����������������Ի�������ʾ�������޸ĵ�ǰ��¼��
// ����ֵ������޸��˵�ǰ��¼���򷵻�true�����򷵻�false��
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
			int result = MessageBox(NULL, "��ǰ��¼�ѱ��޸ģ��Ƿ񱣴棿",
						"�޸���ʾ" , MB_YESNOCANCEL | MB_ICONQUESTION);
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
			MessageBox(NULL, "���ύ��¼��ѧ���Ѵ��ڣ��������޸�ѧ�š�",
						"�ύ����", MB_OK | MB_ICONERROR);
			flag = false;
		}
		else
			flag = true;
	}
	m_StudentSet.Index(index);
	return flag;
}

// ��������ؼ��ֶ�ѧ�����Ͻ������򲢼����������ļ�������ˢ�µ�ǰ����ʾ��
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

// ��һ��ѧ�������ļ���
// ������lpszPathNameΪָ�����򿪵�ѧ�������ļ�����ָ�롣
// ����ֵ���򿪲����ɹ����򷵻�true�����򷵻�false��
BOOL CInquireDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	BOOL flag = FALSE;
//	int length;
//	char buffer[21];
	fstream in(lpszPathName, ios::in | ios::binary);
	if(!in)
	{
		MessageBox(NULL, "���ܴ�ѧ�����ݿ�����ļ���",
					"�򿪴���", MB_OK | MB_ICONERROR);
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
						MessageBox(NULL, "��������ѧ����������",
								"�򿪴���", MB_OK | MB_ICONERROR);
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
			MessageBox(NULL, "���򿪵��ļ�����ѧ�����ݿ��ļ���",
						"�򿪴���", MB_OK | MB_ICONERROR);
		}
	}
End:return flag;
}

// ����һ��ѧ�������ļ���
// ������lpszPathNameΪָ���������ѧ�������ļ�����ָ�롣
// ����ֵ����������ɹ����򷵻�true�����򷵻�false��
BOOL CInquireDoc::OnSaveDocument(LPCTSTR lpszPathName) 
{
	BOOL flag = FALSE;
	// �ڴ˼�����Σ�������Ϣ��ӵ��ʵ���λ�á�
	fstream out(lpszPathName, ios::out | ios::binary);
	if(!out)
	{
		MessageBox(NULL, "���ܴ򿪻򴴽�����ļ���",
					"�������", MB_OK | MB_ICONERROR);
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
//						MessageBox(NULL, "��������ѧ����������",
//								"�򿪴���", MB_OK | MB_ICONERROR);
			out.close();
			flag = TRUE;
		}
//		else
//		{
//			MessageBox(NULL, "���򿪵��ļ�����ѧ�����ݿ��ļ���",
//						"�򿪴���", MB_OK | MB_ICONERROR);
//		}
	}
//		MessageBox(NULL, "���ܴ򿪻򴴽�����ļ���",
//					"�������", MB_OK | MB_ICONERROR);
	return flag;
}
