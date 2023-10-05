// dlink.cpp

#include "stdafx.h"
#include "Inquire.h"
#include "resclass.h"
#include "dlink.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CPerson Class
//////////////////////////////////////////////////////////////////////

// 从数据交互对话框CDataIODlg的各数据项中读数据到各相应的数据成员。
// 参数：in为指向CDataIODlg的指针。
void CPerson::Read(CDataIODlg *in)
{
}

// 将各数据成员的数据写到数据交互对话框CDataIODlg中的相应数据项中。
// 参数：out为指向CDataIODlg的指针。
void CPerson::Write(CDataIODlg *out)
{
}

// 从文件流fstream中顺序读数据到各相应的数据成员。
// 参数：in为fstream的引用。
void CPerson::Read(fstream &in)
{
}

// 将各数据成员的数据顺序写到文件流fstream中。
// 参数：out为fstream的引用。
void CPerson::Write(fstream &out)
{
}

// 将数据成员m_Name的字串的前两个字符（姓氏）传送到s指向的字串。
void CPerson::Name(char* s)
{
}

// 将数据成员m_BirthPlace的字串传送到s指向的字串。
void CPerson::BirthPlace(char *s)
{
}

// 将数据成员m_UpdateDate修改为当前日期。
void CPerson::ModifyUpdateDate()
{
}

//////////////////////////////////////////////////////////////////////
// CStudent Class
//////////////////////////////////////////////////////////////////////

// 比较运算符==重载。
// 参数：s为类CStudent的对象。
// 返回值：如果m_ID == s.m_ID返回true否则返回false。
bool CStudent::operator==(CStudent s)
{
	return (m_ID == s.m_ID);
}

// 比较运算符==重载。
// 参数：key为进行比较的字串。
// 返回值：根据检索主关键字，如果相应的检索辅助关键字串 == key返回true否则返回false。
bool CStudent::operator ==(CString key)
{
	bool flag = false;
	// 在此加入码段，根据m_Retrieve分情况判断m_Name的前两个字符，m_Sex，m_BirthPlace，
	// m_Major和m_Speciality。
	return flag;
}

// 比较运算符!=重载。
// 参数：s为类CStudent的对象。
// 返回值：如果除m_ID以外的某一数据成员 != s的相应数据成员返回true否则返回false。
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

// 比较运算符<=重载。
// 参数：s为类CStudent的对象。
// 返回值：根据排序关键字如果相应的数据成员 <= s的相应数据成员返回true否则返回false。
bool CStudent::operator<=(CStudent s)
{
	bool flag = false;
	// 在此加入码段，根据m_Sort分情况判断m_ID，m_Name的前两个字符，m_Age，
	// m_BirthDate和m_RegistDate。
	return flag;
}

// 比较运算符>重载。
// 参数：s为类CStudent的对象。
// 返回值：根据排序关键字如果相应的数据成员 > s的相应数据成员返回true否则返回false。
bool CStudent::operator>(CStudent s)
{
	bool flag = false;
	// 在此加入码段，根据m_Sort分情况判断m_ID，m_Name的前两个字符，m_Age，
	// m_BirthDate和m_RegistDate。
	return flag;
}

// 从数据交互对话框CDataIODlg的各数据项中读数据到各相应的数据成员。
// 参数：in为指向CDataIODlg的指针。
void CStudent::Read(CDataIODlg *in)
{
}

// 从文件流fstream中顺序读数据到各相应的数据成员。
// 参数：in为fstream的引用。
void CStudent::Read(fstream &in)
{
}

// 将各数据成员的数据写到数据交互对话框CDataIODlg中的相应数据项中。
// 参数：out为指向CDataIODlg的指针。
void CStudent::Write(CDataIODlg *out)
{
}

// 将各数据成员的数据顺序写到文件流fstream中。
// 参数：out为fstream的引用。
void CStudent::Write(fstream &out)
{
}

// 依据传递来的参数值和m_FieldWidth中的域宽将各数据成员的内容输出（显示或打印）。
// 参数：pDC为指向设备上下文的指针；pos为输出各数据成员的起始位置坐标；
//		 size为单个汉字字型的尺寸；lheight为格式行的高度。
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

// 将一个CStudent类型数据作为新链结点的数据项，并将此新结点从第一个链结点前面插入集合。
// 参数：items为被插入新结点的数据项。
// 返回值：如果插入操作成功，则返回true，否则返回false。
bool CStudentSet::InsertBefore(CStudent x)
{
	bool flag = false;
	// 在此加入码段，并将下面的两个信息框放在码段的适当位置
			MessageBox(NULL, "提交记录失败！",
						"提交警告", MB_OK | MB_ICONERROR);
		MessageBox(NULL, "欲提交记录的学号已存在！修改学号后再提交。",
					"提交警告", MB_OK | MB_ICONERROR);
	return flag;
}

// 将一个CStudent类型数据作为新链结点的数据项，并将此新结点从最后一个链结点后面插入集合。
// 参数：items为被插入新结点的数据项。
// 返回值：如果插入操作成功，则返回true，否则返回false。
bool CStudentSet::InsertAfter(CStudent x)
{
	bool flag = false;
	// 在此加入码段，并将下面的两个信息框放在码段的适当位置
			MessageBox(NULL, "提交记录失败！",
						"提交警告", MB_OK | MB_ICONERROR);
		MessageBox(NULL, "欲提交记录的学号已存在！修改学号后再提交。",
					"提交警告", MB_OK | MB_ICONERROR);
	return flag;
}

// 绘制输出数据表的框架。
// 参数：pDC为指向设备上下文的指针；frame为输出数据表的框架的矩形类参数；
//		 size为单个汉字字型的尺寸；lheight为格式行的高度；lines为当前输出页的行数。
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

// 根据当前的检索关键字输出信息数据表的标题。
// 参数：pDC为指向设备上下文的指针；frame为输出数据表的框架的矩形类参数；
//		 font为数据表项的输出字型；lheight为格式行的高度。
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
	CString title = CStudent::m_Retrieve > 0 ? "部分学生信息一览表" : "全体学生信息一览表";
	switch(CStudent::m_Retrieve)
	{
	case name:
		title += "(姓=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case sex:
		title += "(性别=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case birthplace:
		title += "(出生地=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case major:
		title += "(主修=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	case speciality:
		title += "(专业=\"" + CStudent::m_RetrieveKey + "\")";
		break;
	}
	CSize titleSize = pDC->GetTextExtent(title);
	int x = frame.left + (frame.Width() - titleSize.cx) / 2, y = frame.top + lheight * 3 / 2;
	pDC->TextOut(x, y, title);
	pDC->SelectObject(oldFont);
}

// 根据当前的排序关键字和检索关键字格式输出（显示或打印）链表中可访问结点的数据项。
// 参数：pDC为指向设备上下文的指针；pos为输出各数据成员的起始位置坐标；
//		 size为单个汉字字型的尺寸；lheight为格式行的高度；
//		 start为当前输出页的起始行；lines为当前输出页的行数。
void CStudentSet::ShowItems(CDC *pDC, CPoint pos, CSize size, int lheight, int start, int lines)
{
	int x, y, i; // x, y用于输出各项目名的坐标位置，i为循环变量。
	CPoint pos1(pos); // 用于存放每个项目名的边框位置
	CString str[11];
	str[0] = "学 号"; str[1] = "姓 名"; str[2] = "性别"; str[3] = "年龄";
	str[4] = "出生日期"; str[5] = "出生地"; str[6] = "主 修"; str[7] = "专 业";
	str[8] = "联系电话"; str[9] = "注册日期"; str[10] = "修改日期";
	// 在此加入码段，先输出项目名行，然后逐行输出信息记录。
}
