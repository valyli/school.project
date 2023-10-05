// dlink.h

#if !defined(AFX_DATA_H__A1B09821_34F3_11D5_88D8_9E17A6A3E7AE__INCLUDED_)
#define AFX_DATA_H__A1B09821_34F3_11D5_88D8_9E17A6A3E7AE__INCLUDED_

#include "resclass.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream.h>

// 枚举State用于定义CStudent::m_Sort和CStudent::m_Retrieve，通过改变它们的枚举值以
// 确定不同的排序和检索操作。none表示不排序或（和)不检索。
enum State
{
	id,				// 识别编号
	name,			// 姓名
	sex,			// 性别
	age,			// 年龄
	birthplace,		// 出生地
	birthdate,		// 出生日期
	registdate,		// 注册日期
	major,			// 主修
	speciality,		// 专业
	none = -1		// 不排序或不检索
};

// 结构模板用于系统中所有类型双链集合的结点结构。
template<class T>
struct node
{
	// 结点数据，在实例化时其类型被具体为系统中不同的相关类，例如：CStudent。
	T items;
	node *prior, *next;
};

class CDataIODlg;

// 系统中所有人员类的基类。
class CPerson  
{
protected:
	DWORD			m_ID;			// 人员的识别编号
	CString			m_Name;			// 姓名
	CString			m_Sex;			// 性别
	int				m_Age;			// 年龄
	CString			m_Phone;		// 联系电话
	CString			m_BirthPlace;	// 出生地
	COleDateTime	m_BirthDate;	// 出生日期
	COleDateTime	m_RegistDate;	// 注册日期
	COleDateTime	m_UpdateDate;	// 修改日期

public:
	// 修改数据成员m_UpdateDate。
	void ModifyUpdateDate();
	// 将数据成员m_BirthPlace的字串传送到s指向的字串。
	void BirthPlace(char* s);
	// 将数据成员m_Name的字串的前两个字符（姓氏）传送到s指向的字串。
	void Name(char* s);
	// 从数据交互对话框CDataIODlg的各数据项中读数据到各相应的数据成员。
	// 参数：in为指向CDataIODlg的指针。
	virtual void Read(CDataIODlg* in);
	// 从文件流fstream中顺序读数据到各相应的数据成员。
	// 参数：in为fstream的引用。
	virtual void Read(fstream& in);
	// 将各数据成员的数据写到数据交互对话框CDataIODlg中的相应数据项中。
	// 参数：out为指向CDataIODlg的指针。
	virtual void Write(CDataIODlg* out);
	// 将各数据成员的数据顺序写到文件流fstream中。
	// 参数：out为fstream的引用。
	virtual void Write(fstream& out);
};

class CStudent : public CPerson  
{
protected:
	CString m_Speciality;	// 专业
	CString m_Major;		// 主修

public:
	static CString m_RetrieveKey;	// 检索辅助关键字串
	static State m_Retrieve;		// 检索类别（主关键字）：
									// name,sex,birthplace,major,speciality
	static State m_Sort;			// 排序关键字：
									// id,name,age,birthdate,registdate
	static m_FieldWidth[11];		// 格式输出（显示和打印）中各数据的域宽
	// 比较运算符==重载。
	// 参数：s为类CStudent的对象。
	// 返回值：如果m_ID == s.m_ID返回true否则返回false。
	bool operator==(CStudent s);
	// 比较运算符==重载。
	// 参数：key为进行比较的字串。
	// 返回值：根据检索主关键字，如果相应的检索辅助关键字串 == key返回true否则返回false。
	bool operator==(CString key);
	// 比较运算符!=重载。
	// 参数：s为类CStudent的对象。
	// 返回值：如果某一数据成员 != s的相应数据成员返回true否则返回false。
	bool operator!=(CStudent s);
	// 比较运算符<=重载。
	// 参数：s为类CStudent的对象。
	// 返回值：根据排序关键字如果相应的数据成员 <= s的相应数据成员返回true否则返回false。
	bool operator<=(CStudent s);
	// 比较运算符>重载。
	// 参数：s为类CStudent的对象。
	// 返回值：根据排序关键字如果相应的数据成员 > s的相应数据成员返回true否则返回false。
	bool operator>(CStudent s);
	// 从数据交互对话框CDataIODlg的各数据项中读数据到各相应的数据成员。
	// 参数：in为指向CDataIODlg的指针。
	virtual void Read(CDataIODlg* in);
	// 从文件流fstream中顺序读数据到各相应的数据成员。
	// 参数：in为fstream的引用。
	virtual void Read(fstream& in);
	// 将各数据成员的数据写到数据交互对话框CDataIODlg中的相应数据项中。
	// 参数：out为指向CDataIODlg的指针。
	virtual void Write(CDataIODlg* out);
	// 将各数据成员的数据顺序写到文件流fstream中。
	// 参数：out为fstream的引用。
	virtual void Write(fstream& out);
	// 依据传递来的参数值和m_FieldWidth中的域宽将各数据成员的内容输出（显示或打印）。
	// 参数：pDC为指向设备上下文的指针；pos为输出各数据成员的起始位置坐标；
	//		 size为单个汉字字型的尺寸；lheight为格式行的高度。
	void Show(CDC* pDC, CPoint pos, CSize size, int lheight);
};

template<class T>
class CD_Link
{
	node<T> *m_Head;	// 链头指针
	int m_Size;			// 链表长度
	int m_Index;		// 当前被访问的链结点的索引值
public:
	// 构造函数
	CD_Link()
	{
		m_Head = new node<T>;
		m_Head->prior = m_Head;
		m_Head->next = m_Head;
		m_Size = 1;
		m_Index = -1;
	}
	// 获取链头指针。
	// 返回值：链头指针。
	node<T>* Head()
	{ return m_Head; }
	// 获取链表中的第一个链结点。
	// 返回值：指向第一个链结点的指针。
	node<T>* First()
	{ return m_Head->next; }
	// 获取链表中的最后一个链结点。
	// 返回值：指向最后一个链结点的指针。
	node<T>* Last()
	{ return m_Head->prior; }
	// 获取当前索引值。
	// 返回值：当前被访问链结点的索引值。
	int Index()
	{ return m_Index; }
	// 设置索引值。
	// 参数：i为欲设置的索引值。
	void Index(int i)
	{ m_Index = i; }
	// 获取链表的长度。
	// 返回值：链表的实际长度。
	int Size()
	{ return (m_Size - 1); }
	// 获取在当前检索状态下的可访问的链结点的个数。
	// 返回值：根据检索主关键字计算出的可访问链结点的个数。
	int Count()
	{
		int count = m_Size - 1;
		// 在此加入码段
		int index = 0;
		if(CStudent::m_Retrieve == none)
			return count;
		count = 0;
		while(index <= (m_Size - 2))
		{
			if(Get(index)->items == CStudent::m_RetrieveKey)
				count++;
			index++;
		}
		return count;
	}
	// 判定链表是否为空？
	// 返回值：如果链表为空返回true否则返回false。
	bool Empty()
	{
		bool flag = false;
		// 在此加入码段
		flag = (m_Head->next == m_Head) ? true: false;
		return flag;
	}
	// 获取在当前检索状态下链表中第一个可访问链结点的索引值。
	// 返回值：根据检索主关键字找出的第一个可访问链结点的索引值。
	int FirstIndex()
	{
		int index = 0;
		if(CStudent::m_Retrieve != none)
		{
			while((index <= (m_Size - 2)) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index++;
			index = (index <= (m_Size - 2)) ? index : m_Index;
		}
		return index;
	}
	// 获取在当前检索状态下链表中最后一个可访问链结点的索引值。
	// 返回值：根据检索主关键字找出的最后一个可访问链结点的索引值。
	int LastIndex()
	{
		int index = (m_Size - 2 >= 0) ? m_Size - 2 : 0;
		// 在此加入码段
		if(CStudent::m_Retrieve != none)
		{
			while((index >= 0) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index--;
			index = (index >= 0) ? index : m_Index;
		}
		
		return index;
	}
	// 获取在当前检索状态下链表中前一个可访问链结点的索引值。
	// 返回值：根据检索主关键字找出的前一个可访问链结点的索引值。
	int PrevIndex()
	{
		int index = (m_Index - 1 >= 0) ? m_Index - 1 : m_Index;
		// 在此加入码段
		if(CStudent::m_Retrieve != none)
		{
			while((index >= 0) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index--;
			index = (index >= 0) ? index : m_Index;
		}

		return index;
	}
	// 获取在当前检索状态下链表中后一个可访问链结点的索引值。
	// 返回值：根据检索主关键字找出的后一个可访问链结点的索引值。
	int NextIndex()
	{
		int index = ((m_Index + 1) <= (m_Size - 2)) ? m_Index + 1 : m_Index;
		// 在此加入码段
		if(CStudent::m_Retrieve != none)
		{
			while((index <= (m_Size - 2)) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index++;
			index = (index <= (m_Size - 2)) ? index : m_Index;
		}

		return index;
	}
	// 将一类型为T的数据作为新链结点的数据项，并将此新结点从第一个链结点前面插入链表。
	// 参数：x为被插入新结点的数据项，其类型在调用时被实例化为系统中相应的类型，例如CStudent。
	// 返回值：如果插入操作成功，则返回true，否则返回false。
	virtual bool InsertBefore(T x)
	{
		bool flag = false;
		// 在此加入码段
		node<T> *p = new node<T>;
		if(p)
		{
			p->items = x;
			p->next = m_Head->next;
			m_Head->next->prior = p;
			m_Head->next = p;
			p->prior = m_Head;
			m_Index = 0;
			m_Size++;
			flag = true;
		}

		return flag;
	}
	// 将p1指向的结点从链表中取下，并将其插到由p指向的结点之前。
	// 参数：p和p1分别指向链表中的两个结点。
	void InsertBefore(node<T> *p, node<T> *p1)
	{
		// 在此加入码段
		if(p == p1 || p == m_Head || p1 == m_Head)
			return;
		p1->prior->next = p1->next;
		p1->next->prior = p1->prior;
		p1->prior = p->prior;
		p->prior->next = p1;
		p1->next = p;
		p->prior = p1;

	}
	// 将一类型为T的数据作为新链结点的数据项，并将此新结点从最后一个链结点后面插入链表。
	// 参数：x为被插入新结点的数据项，其类型在调用时被实例化为系统中相应的类型，例如CStudent。
	// 返回值：如果插入操作成功，则返回true，否则返回false。
	virtual bool InsertAfter(T x)
	{
		bool flag = false;
		// 在此加入码段
		node<T> *p = new node<T>;
		if(p)
		{
			p->items = x;
			p->prior = m_Head->prior;
			m_Head->prior->next = p;
			m_Head->prior = p;
			p->next = m_Head;
			m_Size++;
			m_Index = m_Size - 2;
			flag = true;
		}

		return flag;
	}
	// 将p1指向的结点从链表中取下，并将其插到由p指向的结点之后。
	// 参数：p和p1分别指向链表中的两个结点。
	void InsertAfter(node<T> *p, node<T> *p1)
	{
		// 在此加入码段
		if(p == p1 || p == m_Head || p1 == m_Head)
			return;
		p1->next->prior = p1->prior;
		p1->prior->next = p1->next;
		p1->next = p->next;
		p->next->prior = p1;
		p1->prior = p;
		p->next = p1;

	}
	// 在链表中寻找数据项与key相同的链结点。
	// 参数：key为被寻找的结点所含有的数据项，其类型在调用时被实例化系统中系统中相应的类型，例如CStudent。
	// 返回值：如果找到了含有数据项key的结点，则返回该结点的指针，否则返回NULL。
	node<T>* Location(T key)
	{
		int index = 0;
		node<T> *p = m_Head->next;
		// 在此加入码段，End为程序的唯一出口，因此，如果在程序执行中需要中断执行返回时，
		// 则执行语句goto End; 。
		if(Empty())
		{
			p = 0;
			goto End;
		}
		while((index <= (m_Size - 2)) &&
			!(Get(index)->items == key))
			index++;
		if(index <= (m_Size - 2))
		{
			p = Get(index);
			m_Index = index;
		}
		else p = 0;
End:	return p; 
	}
	// 获取索引值为i的链结点。
	// 参数：i为欲寻找的链结点的索引值。
	// 返回值：如果找到了索引值为i的链结点，则返回该结点的指针，否则返回NULL。
	node<T>* Get(int i)
	{
		node<T> *p = m_Head->next;
		// 在此加入码段
		int index = 0;
		if(m_Head->next == m_Head || i < 0 || i > (m_Size - 2))
		{
			p = 0;
			return p;
		}
		while(index != i)
		{
			index++;
			p = p->next;
		}
		return p;
	}
	// 从链表中删除有指针p指向的链结点。
	// 参数：p为指向被删除链结点的指针。
	void DeleteNode(node<T> *p)
	{
		// 在此加入码段
		if(p == m_Head) return;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		p->next = NULL;
		p->prior = NULL;
		delete p;
		m_Size--;

	}
	// 从链表中删除数据项为x的链结点。
	// 参数：x为欲删除链结点的数据项，其类型在调用时被实例化系统中系统中相应的类型，例如CStudent。
	// 返回值：如果数据项为x的链结点被找到并且被确认删除，则返回true，否则返回false。
	bool Delete(T x)
	{
		bool flag = false;
		node<T> *p = Location(x);
		if(p)
		{
			if(MessageBox(NULL,"确实要删除当前显示的记录吗？",
						"删除提示",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DeleteNode(p);
				m_Index = min(max(m_Index - 1, 0), m_Size - 2);
				flag = true;
			}
		}
		return flag;
	}
	// 从链表中删除索引值为i的链结点。
	// 参数：i为欲删除链结点的索引值。
	// 返回值：如果索引值为i的链结点被找到并被删除，则返回true，否则返回false。
	bool Delete(int i)
	{
		bool flag = false;
		// 在此加入码段
		node<T>* p = Get(i);
		if(!p)
		{
			if(MessageBox(NULL,"确实要删除当前显示的记录吗？",
						"删除提示",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				p->next->prior = p->prior;
				p->prior->next = p->next;
				delete p;
				m_Index = min(FirstIndex(), m_Size - 2);
				flag = true;
			}
		}
		return flag;
	}
	// 判别链表中是否包含有数据项与x相同的链结点。
	// 参数：x为欲判别链结点所含有的数据项，其类型在调用时被实例化系统中系统中相应的类型，例如CStudent。
	// 返回值：如果欲判别的链结点存在，则返回true，否则返回false。
	bool contains(T x)
	{
		return Location(x) ? true : false;
	}
	// 在链表中归并排序一段区间上的链结点。
	// 参数：low，mid和high分别为这段区间的始点，中点和终点的索引值。
	void Merge(int low, int mid, int high)
	{
		// 在此加入码段
		int i = low ,j = mid + 1;
		while (i <= mid && j<=high)
		{
			if(Get(i)->items > Get(j)->items)
			{
				InsertBefore(Get(i),Get(j));
				j++;
			}
			else
				i++;
		}
		if(j > mid+1 && j<=high)
			Merge(mid+1, j-1, high);
	}

	// 对整个链表区间进行一遍归并排序。
	// 参数：length为此遍归并排序的子区间长度。
	void MergePass(int length)
	{
		// 在此加入码段
		int low, mid, high;
		for(low = 0; (low + length) <= (m_Size - 2); low = low + 2 * length)
		{
			mid = ((low + length - 1) <= (m_Size - 2))
				? (low + length - 1) : (m_Size - 2);
			high = ((mid + length) <= (m_Size - 2))
				? (mid + length) : (m_Size - 2);
			Merge(low, mid, high);
		}
	}
	// 采用归并排序算法对整个链表上的结点按当前的排序关键字进行完全排序
	void MergeSort()
	{
		// 在此加入码段
		int length;
		for(length = 1; length < m_Size - 1; length = length * 2)
			MergePass(length);
		m_Index = FirstIndex();
	}

	// 析构函数
	~CD_Link()
	{
		node<T> *temp, *p = m_Head;
		for(int i = 0; i < m_Size; i++)
		{
			temp = p;
			p = p->next;
			delete temp;
		}
	}
};

// 由类模板CD_Link实例化派生的学生集合类
class CStudentSet : public CD_Link<CStudent>
{
public:
	// 根据当前的排序关键字和检索关键字格式输出（显示或打印）链表中可访问结点的数据项。
	// 参数：pDC为指向设备上下文的指针；pos为输出各数据成员的起始位置坐标；
	//		 size为单个汉字字型的尺寸；lheight为格式行的高度；
	//		 start为当前输出页的起始行；lines为当前输出页的行数。
	void ShowItems(CDC *pDC, CPoint pos, CSize size, int lheight, int start, int lines);
	// 根据当前的检索关键字输出信息数据表的标题。
	// 参数：pDC为指向设备上下文的指针；frame为输出数据表的框架的矩形类参数；
	//		 font为数据表项的输出字型；lheight为格式行的高度。
	void ShowTitle(CDC* pDC, CRect frame, CFont& font, int lheight);
	// 绘制输出数据表的框架。
	// 参数：pDC为指向设备上下文的指针；frame为输出数据表的框架的矩形类参数；
	//		 size为单个汉字字型的尺寸；lheight为格式行的高度；lines为当前输出页的行数。
	void DrawFrame(CDC* pDC, CRect frame, CSize size, int lheight, int lines);
	// 将一个CStudent类型数据作为新链结点的数据项，并将此新结点从第一个链结点前面插入集合。
	// 参数：items为被插入新结点的数据项。
	// 返回值：如果插入操作成功，则返回true，否则返回false。
	virtual bool InsertBefore(CStudent items);
	// 将一个CStudent类型数据作为新链结点的数据项，并将此新结点从最后一个链结点后面插入集合。
	// 参数：items为被插入新结点的数据项。
	// 返回值：如果插入操作成功，则返回true，否则返回false。
	virtual bool InsertAfter(CStudent items);
};

#endif // !defined(AFX_DATA_H__A1B09821_34F3_11D5_88D8_9E17A6A3E7AE__INCLUDED_)
