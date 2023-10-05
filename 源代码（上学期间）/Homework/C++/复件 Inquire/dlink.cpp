// dlink.cpp

#include "stdafx.h"
#include "Inquire.h"
#include "resclass.h"
#include "dlink.h"
#include "string.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CPerson Class
//////////////////////////////////////////////////////////////////////

// �����ݽ����Ի���CDataIODlg�ĸ��������ж����ݵ�����Ӧ�����ݳ�Ա��
// ������inΪָ��CDataIODlg��ָ�롣
void CPerson::Read(CDataIODlg *in)
{
	m_ID = in->m_StudentID;
	m_Name = in->m_Name;
	m_Sex = in->m_Sex;
	m_BirthPlace = in->m_BirthPlace;
	m_Phone = in->m_Phone;
	m_Age = in->m_Age;
	m_BirthDate = in->m_BirthDate;
	m_RegistDate = in->m_RegistDate;
	m_UpdateDate = in->m_UpdateDate;
}

// �������ݳ�Ա������д�����ݽ����Ի���CDataIODlg�е���Ӧ�������С�
// ������outΪָ��CDataIODlg��ָ�롣
void CPerson::Write(CDataIODlg *out)
{
	out->m_StudentID = m_ID;
	out->m_Name = m_Name;
	out->m_Sex = m_Sex;
	out->m_BirthPlace = m_BirthPlace;
	out->m_Phone = m_Phone;
	out->m_Age = m_Age;
	out->m_BirthDate = m_BirthDate;
	out->m_RegistDate = m_RegistDate;
	out->m_UpdateDate = m_UpdateDate;
}

// ���ļ���fstream��˳������ݵ�����Ӧ�����ݳ�Ա��
// ������inΪfstream�����á�
void CPerson::Read(fstream &in)
{
	int length;
	char buffer[21];
	in.read((char *)&m_ID, sizeof(DWORD));

	in.read((char *)&length, sizeof(int));
	in.read(buffer, length);
	m_Name = buffer;
	
	in.read((char *)&length, sizeof(int));
	in.read(buffer, length);
	m_Sex = buffer;
	
	in.read((char *)&length, sizeof(int));
	in.read(buffer, length);
	m_BirthPlace = buffer;
	
	in.read((char *)&length, sizeof(int));
	in.read(buffer, length);
	m_Phone = buffer;
	
	in.read((char *)&m_Age, sizeof(int));
	in.read((char *)&m_BirthDate, sizeof(m_BirthDate));
	in.read((char *)&m_RegistDate, sizeof(m_RegistDate));
	in.read((char *)&m_UpdateDate, sizeof(m_UpdateDate));
}

// �������ݳ�Ա������˳��д���ļ���fstream�С�
// ������outΪfstream�����á�
void CPerson::Write(fstream &out)
{
	int length;
	out.write((char *)&m_ID, sizeof(DWORD));
	
	length = m_Name.GetLength() + 1;
	out.write((char *)&length, sizeof(int));
	out.write(m_Name.GetBuffer(length), length);
	
	length = m_Sex.GetLength() + 1;
	out.write((char *)&length, sizeof(int));
	out.write(m_Sex.GetBuffer(length), length);
	
	length = m_BirthPlace.GetLength() + 1;
	out.write((char *)&length, sizeof(int));
	out.write(m_BirthPlace.GetBuffer(length), length);
	
	length = m_Phone.GetLength() + 1;
	out.write((char *)&length, sizeof(int));
	out.write(m_Phone.GetBuffer(length), length);
	
	out.write((char *)&m_Age, sizeof(int));
	out.write((char *)&m_BirthDate, sizeof(m_BirthDate));
	out.write((char *)&m_RegistDate, sizeof(m_RegistDate));
	out.write((char *)&m_UpdateDate, sizeof(m_UpdateDate));
}

// �����ݳ�Աm_Name���ִ���ǰ�����ַ������ϣ����͵�sָ����ִ���
void CPerson::Name(char* s)
{
//	s = new char(3);////////////////////////////try
	strncpy(s, m_Name, 2);
}

// �����ݳ�Աm_BirthPlace���ִ����͵�sָ����ִ���
void CPerson::BirthPlace(char *s)
{
	int length = m_BirthPlace.GetLength() + 1;
//	s = new char(length);
	strcpy(s, m_BirthPlace);
}

// �����ݳ�Աm_UpdateDate�޸�Ϊ��ǰ���ڡ�
void CPerson::ModifyUpdateDate()
{
	m_UpdateDate = m_UpdateDate.GetCurrentTime();
}

//////////////////////////////////////////////////////////////////////
// CStudent Class
//////////////////////////////////////////////////////////////////////

// �Ƚ������==���ء�
// ������sΪ��CStudent�Ķ���
// ����ֵ�����m_ID == s.m_ID����true���򷵻�false��
bool CStudent::operator==(CStudent s)
{
	return (m_ID == s.m_ID);
}

// �Ƚ������==���ء�
// ������keyΪ���бȽϵ��ִ���
// ����ֵ�����ݼ������ؼ��֣������Ӧ�ļ��������ؼ��ִ� == key����true���򷵻�false��
bool CStudent::operator ==(CString key)
{
	bool flag = false;
	// �ڴ˼�����Σ�����m_Retrieve������ж�m_Name��ǰ�����ַ���m_Sex��m_BirthPlace��
	// m_Major��m_Speciality��
	switch(m_Retrieve)
	{
	case name:
		flag = strncmp(m_Name, key, key.GetLength())? false: true;
		break;
	case sex:
		flag = (m_Sex == key);
		break;
	case birthplace:
		flag = (m_BirthPlace == key);
		break;
	case major:
		flag = (m_Major == key);
		break;
	case speciality:
		flag = (m_Speciality == key);
		break;
	}
	return flag;
}

// �Ƚ������!=���ء�
// ������sΪ��CStudent�Ķ���
// ����ֵ�������m_ID�����ĳһ���ݳ�Ա != s����Ӧ���ݳ�Ա����true���򷵻�false��
bool CStudent::operator !=(CStudent s)
{
	bool flag = ((m_Name != s.m_Name) ||
				 (m_Sex != s.m_Sex) || 
				 (m_BirthPlace != s.m_BirthPlace) ||
				 (m_Phone != s.m_Phone) || 
				 (m_Age != s.m_Age) ||
				 (m_BirthDate != s.m_BirthDate) ||
				 (m_RegistDate != s.m_RegistDate) ||
				 (m_Major != s.m_Major) || 
				 (m_Speciality != s.m_Speciality)) ? true : false;
	return flag;
}

// �Ƚ������<=���ء�
// ������sΪ��CStudent�Ķ���
// ����ֵ����������ؼ��������Ӧ�����ݳ�Ա <= s����Ӧ���ݳ�Ա����true���򷵻�false��
bool CStudent::operator<=(CStudent s)
{
	bool flag = false;
	// �ڴ˼�����Σ�����m_Sort������ж�m_ID��m_Name��ǰ�����ַ���m_Age��
	// m_BirthDate��m_RegistDate��
	switch(m_Sort)
	{
	case id:
		flag = (m_ID <= s.m_ID) ? true: false;
		break;
	case name:
		flag = (strncmp(m_Name, s.m_Name, s.m_Name.GetLength()) != 1) ? true: false;
		break;
	case age:
		flag = (m_Age <= s.m_Age) ? true: false;
	case birthdate:
		flag = (m_BirthDate <= s.m_BirthDate) ? true: false;
		break;
	case registdate:
		flag = (m_RegistDate <= s.m_RegistDate) ? true: false;
	}
	return flag;
}

// �Ƚ������>���ء�
// ������sΪ��CStudent�Ķ���
// ����ֵ����������ؼ��������Ӧ�����ݳ�Ա > s����Ӧ���ݳ�Ա����true���򷵻�false��
bool CStudent::operator>(CStudent s)
{
	bool flag = false;
	// �ڴ˼�����Σ�����m_Sort������ж�m_ID��m_Name��ǰ�����ַ���m_Age��
	// m_BirthDate��m_RegistDate��
	switch(m_Sort)
	{
	case id:
		flag = (m_ID > s.m_ID) ? true: false;
		break;
	case name:
		flag = (strncmp(m_Name, s.m_Name, s.m_Name.GetLength()) == 1) ? true: false;
		break;
	case age:
		flag = (m_Age > s.m_Age) ? true: false;
		break;
	case birthdate:
		flag = (m_BirthDate > s.m_BirthDate) ? true: false;
		break;
	case registdate:
		flag = (m_RegistDate > s.m_RegistDate) ? true: false;
	}
	return flag;
}

// �����ݽ����Ի���CDataIODlg�ĸ��������ж����ݵ�����Ӧ�����ݳ�Ա��
// ������inΪָ��CDataIODlg��ָ�롣
void CStudent::Read(CDataIODlg *in)
{
	CPerson::Read(in);
	m_Major = in->m_Major;
	m_Speciality = in->m_Speciality;
}

// ���ļ���fstream��˳������ݵ�����Ӧ�����ݳ�Ա��
// ������inΪfstream�����á�
void CStudent::Read(fstream &in)
{
	CPerson::Read(in);
	int length;
	char buffer[21];
	in.read((char *)&length, sizeof(int));
	in.read(buffer, length);
	m_Major = buffer;
	in.read((char *)&length, sizeof(int));
	in.read(buffer, length);
	m_Speciality = buffer;
}

// �������ݳ�Ա������д�����ݽ����Ի���CDataIODlg�е���Ӧ�������С�
// ������outΪָ��CDataIODlg��ָ�롣
void CStudent::Write(CDataIODlg *out)
{
	CPerson::Write(out);
	out->m_Major = m_Major;
	out->m_Speciality = m_Speciality;
}

// �������ݳ�Ա������˳��д���ļ���fstream�С�
// ������outΪfstream�����á�
void CStudent::Write(fstream &out)
{
	CPerson::Write(out);
	int length = m_Major.GetLength() + 1;
	out.write((char *)&length, sizeof(int));
	out.write(m_Major.GetBuffer(length), length);
	length = m_Speciality.GetLength() + 1;
	out.write((char *)&length, sizeof(int));
	out.write(m_Speciality.GetBuffer(length), length);
}

// ���ݴ������Ĳ���ֵ��m_FieldWidth�е���������ݳ�Ա�������������ʾ���ӡ����
// ������pDCΪָ���豸�����ĵ�ָ�룻posΪ��������ݳ�Ա����ʼλ�����ꣻ
//		 sizeΪ�����������͵ĳߴ磻lheightΪ��ʽ�еĸ߶ȡ�
void CStudent::Show(CDC *pDC, CPoint pos, CSize size, int lheight)
{
	int x, y;
	char id[12], age[5];
	CString str[11];
	str[0] = _ltoa(m_ID, id, 10); str[1] = m_Name; str[2] = m_Sex;
	str[3] = itoa(m_Age, age, 10);
	str[4] = m_BirthDate.Format("%Y-%m-%d");
	str[5] = m_BirthPlace;
	str[6] = m_Major; str[7] = m_Speciality; str[8] = m_Phone;
	str[9] = m_RegistDate.Format("%Y-%m-%d");
	str[10] = m_UpdateDate.Format("%Y-%m-%d");
	for(int i = 0; i < 11; i++)
	{
		CSize tSize = pDC->GetTextExtent(str[i]);
		CSize bSize = CSize(size.cx * m_FieldWidth[i] / 2, lheight);
		x = pos.x + (bSize.cx - tSize.cx) / 2;
		y = pos.y - (bSize.cy - tSize.cy) / 2;
		pDC->TextOut(x, y, str[i]);
		pos.x += bSize.cx;
	}
}

//////////////////////////////////////////////////////////////////////
// CStudentSet Class
//////////////////////////////////////////////////////////////////////

// ��һ��CStudent����������Ϊ��������������������½��ӵ�һ�������ǰ����뼯�ϡ�
// ������itemsΪ�������½��������
// ����ֵ�������������ɹ����򷵻�true�����򷵻�false��
bool CStudentSet::InsertBefore(CStudent x)
{
	bool flag = false;
	// �ڴ˼�����Σ����������������Ϣ�������ε��ʵ�λ��
	if(contains(x))
		MessageBox(NULL, "���ύ��¼��ѧ���Ѵ��ڣ��޸�ѧ�ź����ύ��",
					"�ύ����", MB_OK | MB_ICONERROR);
	else if(!CD_Link<CStudent>::InsertBefore(x))
		MessageBox(NULL, "�ύ��¼ʧ�ܣ�",
					"�ύ����", MB_OK | MB_ICONERROR);
	else flag = true;
	return flag;
}

// ��һ��CStudent����������Ϊ��������������������½������һ������������뼯�ϡ�
// ������itemsΪ�������½��������
// ����ֵ�������������ɹ����򷵻�true�����򷵻�false��
bool CStudentSet::InsertAfter(CStudent x)
{
	bool flag = false;
	// �ڴ˼�����Σ����������������Ϣ�������ε��ʵ�λ��
	if(contains(x))
		MessageBox(NULL, "���ύ��¼��ѧ���Ѵ��ڣ��޸�ѧ�ź����ύ��",
					"�ύ����", MB_OK | MB_ICONERROR);
	else if(!CD_Link<CStudent>::InsertAfter(x))
		MessageBox(NULL, "�ύ��¼ʧ�ܣ�",
					"�ύ����", MB_OK | MB_ICONERROR);
	else flag = true;
	return flag;
}

// ����������ݱ�Ŀ�ܡ�
// ������pDCΪָ���豸�����ĵ�ָ�룻frameΪ������ݱ�Ŀ�ܵľ����������
//		 sizeΪ�����������͵ĳߴ磻lheightΪ��ʽ�еĸ߶ȣ�linesΪ��ǰ���ҳ��������
void CStudentSet::DrawFrame(CDC *pDC, CRect frame, CSize size, int lheight, int lines)
{
	CPen tabPen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen itvPen(PS_SOLID, 2, RGB(0, 0, 0));
	// draw form border
	CPen* pOldPen = pDC->SelectObject(&tabPen);
	CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(WHITE_BRUSH);
	pDC->MoveTo(frame.TopLeft());
	pDC->LineTo(frame.right, frame.top);
	pDC->LineTo(frame.BottomRight());
	pDC->LineTo(frame.left, frame.bottom);
	pDC->LineTo(frame.TopLeft());
	// draw vertical interval lines
	pDC->SelectObject(&itvPen);
	int interval = 0;
	for(int i = 0; i < 11; i++)
	{
		interval += CStudent::m_FieldWidth[i] / 2;
		pDC->MoveTo(frame.TopLeft() + CSize(size.cx * interval, 0));
		pDC->LineTo(frame.TopLeft() + CSize(size.cx * interval, frame.Height()));
	}
	// draw horizontal interval lines
	for(i = 0; i < lines; i++)
	{
		pDC->MoveTo(frame.left, frame.top - i * lheight);
		pDC->LineTo(frame.right, frame.top - i * lheight);
	}
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

// ���ݵ�ǰ�ļ����ؼ��������Ϣ���ݱ�ı��⡣
// ������pDCΪָ���豸�����ĵ�ָ�룻frameΪ������ݱ�Ŀ�ܵľ����������
//		 fontΪ���ݱ����������ͣ�lheightΪ��ʽ�еĸ߶ȡ�
void CStudentSet::ShowTitle(CDC *pDC, CRect frame, CFont& font, int lheight)
{
	LOGFONT logFont;
	font.GetLogFont(&logFont);
	logFont.lfHeight *= 2;
	logFont.lfWeight *= 2;
	CFont titleFont, *oldFont;
	BOOL changeFont = titleFont.CreateFontIndirect(&logFont);
	if(changeFont)
		oldFont = pDC->SelectObject(&titleFont);
	CString title = CStudent::m_Retrieve > 0 ? "����ѧ����Ϣһ����" : "ȫ��ѧ����Ϣһ����";
	switch(CStudent::m_Retrieve)
	{
	case name:
		title += "(��=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case sex:
		title += "(�Ա�=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case birthplace:
		title += "(������=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case major:
		title += "(����=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case speciality:
		title += "(רҵ=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	}
	CSize titleSize = pDC->GetTextExtent(title);
	int x = frame.left + (frame.Width() - titleSize.cx) / 2, y = frame.top + lheight * 3 / 2;
	pDC->TextOut(x, y, title);
	pDC->SelectObject(oldFont);
}

// ���ݵ�ǰ������ؼ��ֺͼ����ؼ��ָ�ʽ�������ʾ���ӡ�������пɷ��ʽ��������
// ������pDCΪָ���豸�����ĵ�ָ�룻posΪ��������ݳ�Ա����ʼλ�����ꣻ
//		 sizeΪ�����������͵ĳߴ磻lheightΪ��ʽ�еĸ߶ȣ�
//		 startΪ��ǰ���ҳ����ʼ�У�linesΪ��ǰ���ҳ��������
void CStudentSet::ShowItems(CDC *pDC, CPoint pos, CSize size, int lheight, int start, int lines)
{
	int x, y, i; // x, y�����������Ŀ��������λ�ã�iΪѭ��������
	CPoint pos1(pos); // ���ڴ��ÿ����Ŀ���ı߿�λ��
	CString str[11];
	str[0] = "ѧ ��"; str[1] = "�� ��"; str[2] = "�Ա�"; str[3] = "����";
	str[4] = "��������"; str[5] = "������"; str[6] = "�� ��"; str[7] = "ר ҵ";
	str[8] = "��ϵ�绰"; str[9] = "ע������"; str[10] = "�޸�����";
	// �ڴ˼�����Σ��������Ŀ���У�Ȼ�����������Ϣ��¼��
	for(i = 0; i < 11; i++)
	{
		CSize tSize = pDC->GetTextExtent(str[i]);
		CSize bSize = CSize(size.cx * CStudent::m_FieldWidth[i] / 2, lheight);
		x = pos1.x + (bSize.cx - tSize.cx) / 2;
		y = pos1.y - (bSize.cy - tSize.cy) / 2;
		pDC->TextOut(x, y, str[i]);
		pos1.x += bSize.cx;
	}
    pos.y -= lheight;

	Get(FirstIndex())->items.Show(pDC,pos,size,lheight);
    pos.y -= lheight;

	for (i = 1; i < Count(); i++)
	{
		Index(NextIndex());
		Get(Index())->items.Show(pDC,pos,size,lheight);
		pos.y -= lheight;
	}
	

}
