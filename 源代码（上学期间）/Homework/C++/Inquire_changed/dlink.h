// dlink.h

#if !defined(AFX_DATA_H__A1B09821_34F3_11D5_88D8_9E17A6A3E7AE__INCLUDED_)
#define AFX_DATA_H__A1B09821_34F3_11D5_88D8_9E17A6A3E7AE__INCLUDED_

#include "resclass.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <fstream.h>

// ö��State���ڶ���CStudent::m_Sort��CStudent::m_Retrieve��ͨ���ı����ǵ�ö��ֵ��
// ȷ����ͬ������ͼ���������none��ʾ������򣨺�)��������
enum State
{
	id,				// ʶ����
	name,			// ����
	sex,			// �Ա�
	age,			// ����
	birthplace,		// ������
	birthdate,		// ��������
	registdate,		// ע������
	major,			// ����
	speciality,		// רҵ
	none = -1		// ������򲻼���
};

// �ṹģ������ϵͳ����������˫�����ϵĽ��ṹ��
template<class T>
struct node
{
	// ������ݣ���ʵ����ʱ�����ͱ�����Ϊϵͳ�в�ͬ������࣬���磺CStudent��
	T items;
	node *prior, *next;
};

class CDataIODlg;

// ϵͳ��������Ա��Ļ��ࡣ
class CPerson  
{
protected:
	DWORD			m_ID;			// ��Ա��ʶ����
	CString			m_Name;			// ����
	CString			m_Sex;			// �Ա�
	int				m_Age;			// ����
	CString			m_Phone;		// ��ϵ�绰
	CString			m_BirthPlace;	// ������
	COleDateTime	m_BirthDate;	// ��������
	COleDateTime	m_RegistDate;	// ע������
	COleDateTime	m_UpdateDate;	// �޸�����

public:
	// �޸����ݳ�Աm_UpdateDate��
	void ModifyUpdateDate();
	// �����ݳ�Աm_BirthPlace���ִ����͵�sָ����ִ���
	void BirthPlace(char* s);
	// �����ݳ�Աm_Name���ִ���ǰ�����ַ������ϣ����͵�sָ����ִ���
	void Name(char* s);
	// �����ݽ����Ի���CDataIODlg�ĸ��������ж����ݵ�����Ӧ�����ݳ�Ա��
	// ������inΪָ��CDataIODlg��ָ�롣
	virtual void Read(CDataIODlg* in);
	// ���ļ���fstream��˳������ݵ�����Ӧ�����ݳ�Ա��
	// ������inΪfstream�����á�
	virtual void Read(fstream& in);
	// �������ݳ�Ա������д�����ݽ����Ի���CDataIODlg�е���Ӧ�������С�
	// ������outΪָ��CDataIODlg��ָ�롣
	virtual void Write(CDataIODlg* out);
	// �������ݳ�Ա������˳��д���ļ���fstream�С�
	// ������outΪfstream�����á�
	virtual void Write(fstream& out);
};

class CStudent : public CPerson  
{
protected:
	CString m_Speciality;	// רҵ
	CString m_Major;		// ����

public:
	static CString m_RetrieveKey;	// ���������ؼ��ִ�
	static State m_Retrieve;		// ����������ؼ��֣���
									// name,sex,birthplace,major,speciality
	static State m_Sort;			// ����ؼ��֣�
									// id,name,age,birthdate,registdate
	static m_FieldWidth[11];		// ��ʽ�������ʾ�ʹ�ӡ���и����ݵ����
	// �Ƚ������==���ء�
	// ������sΪ��CStudent�Ķ���
	// ����ֵ�����m_ID == s.m_ID����true���򷵻�false��
	bool operator==(CStudent s);
	// �Ƚ������==���ء�
	// ������keyΪ���бȽϵ��ִ���
	// ����ֵ�����ݼ������ؼ��֣������Ӧ�ļ��������ؼ��ִ� == key����true���򷵻�false��
	bool operator==(CString key);
	// �Ƚ������!=���ء�
	// ������sΪ��CStudent�Ķ���
	// ����ֵ�����ĳһ���ݳ�Ա != s����Ӧ���ݳ�Ա����true���򷵻�false��
	bool operator!=(CStudent s);
	// �Ƚ������<=���ء�
	// ������sΪ��CStudent�Ķ���
	// ����ֵ����������ؼ��������Ӧ�����ݳ�Ա <= s����Ӧ���ݳ�Ա����true���򷵻�false��
	bool operator<=(CStudent s);
	// �Ƚ������>���ء�
	// ������sΪ��CStudent�Ķ���
	// ����ֵ����������ؼ��������Ӧ�����ݳ�Ա > s����Ӧ���ݳ�Ա����true���򷵻�false��
	bool operator>(CStudent s);
	// �����ݽ����Ի���CDataIODlg�ĸ��������ж����ݵ�����Ӧ�����ݳ�Ա��
	// ������inΪָ��CDataIODlg��ָ�롣
	virtual void Read(CDataIODlg* in);
	// ���ļ���fstream��˳������ݵ�����Ӧ�����ݳ�Ա��
	// ������inΪfstream�����á�
	virtual void Read(fstream& in);
	// �������ݳ�Ա������д�����ݽ����Ի���CDataIODlg�е���Ӧ�������С�
	// ������outΪָ��CDataIODlg��ָ�롣
	virtual void Write(CDataIODlg* out);
	// �������ݳ�Ա������˳��д���ļ���fstream�С�
	// ������outΪfstream�����á�
	virtual void Write(fstream& out);
	// ���ݴ������Ĳ���ֵ��m_FieldWidth�е���������ݳ�Ա�������������ʾ���ӡ����
	// ������pDCΪָ���豸�����ĵ�ָ�룻posΪ��������ݳ�Ա����ʼλ�����ꣻ
	//		 sizeΪ�����������͵ĳߴ磻lheightΪ��ʽ�еĸ߶ȡ�
	void Show(CDC* pDC, CPoint pos, CSize size, int lheight);
};

template<class T>
class CD_Link
{
	node<T> *m_Head;	// ��ͷָ��
	int m_Size;			// ������
	int m_Index;		// ��ǰ�����ʵ�����������ֵ
public:
	// ���캯��
	CD_Link()
	{
		m_Head = new node<T>;
		m_Head->prior = m_Head;
		m_Head->next = m_Head;
		m_Size = 1;
		m_Index = -1;
	}
	// ��ȡ��ͷָ�롣
	// ����ֵ����ͷָ�롣
	node<T>* Head()
	{ return m_Head; }
	// ��ȡ�����еĵ�һ������㡣
	// ����ֵ��ָ���һ��������ָ�롣
	node<T>* First()
	{ return m_Head->next; }
	// ��ȡ�����е����һ������㡣
	// ����ֵ��ָ�����һ��������ָ�롣
	node<T>* Last()
	{ return m_Head->prior; }
	// ��ȡ��ǰ����ֵ��
	// ����ֵ����ǰ����������������ֵ��
	int Index()
	{ return m_Index; }
	// ��������ֵ��
	// ������iΪ�����õ�����ֵ��
	void Index(int i)
	{ m_Index = i; }
	// ��ȡ����ĳ��ȡ�
	// ����ֵ�������ʵ�ʳ��ȡ�
	int Size()
	{ return (m_Size - 1); }
	// ��ȡ�ڵ�ǰ����״̬�µĿɷ��ʵ������ĸ�����
	// ����ֵ�����ݼ������ؼ��ּ�����Ŀɷ��������ĸ�����
	int Count()
	{
		int count = m_Size - 1;
		// �ڴ˼������
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
	// �ж������Ƿ�Ϊ�գ�
	// ����ֵ���������Ϊ�շ���true���򷵻�false��
	bool Empty()
	{
		bool flag = false;
		// �ڴ˼������
		flag = (m_Head->next == m_Head) ? true: false;
		return flag;
	}
	// ��ȡ�ڵ�ǰ����״̬�������е�һ���ɷ�������������ֵ��
	// ����ֵ�����ݼ������ؼ����ҳ��ĵ�һ���ɷ�������������ֵ��
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
	// ��ȡ�ڵ�ǰ����״̬�����������һ���ɷ�������������ֵ��
	// ����ֵ�����ݼ������ؼ����ҳ������һ���ɷ�������������ֵ��
	int LastIndex()
	{
		int index = (m_Size - 2 >= 0) ? m_Size - 2 : 0;
		// �ڴ˼������
		if(CStudent::m_Retrieve != none)
		{
			while((index >= 0) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index--;
			index = (index >= 0) ? index : m_Index;
		}
		
		return index;
	}
	// ��ȡ�ڵ�ǰ����״̬��������ǰһ���ɷ�������������ֵ��
	// ����ֵ�����ݼ������ؼ����ҳ���ǰһ���ɷ�������������ֵ��
	int PrevIndex()
	{
		int index = (m_Index - 1 >= 0) ? m_Index - 1 : m_Index;
		// �ڴ˼������
		if(CStudent::m_Retrieve != none)
		{
			while((index >= 0) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index--;
			index = (index >= 0) ? index : m_Index;
		}

		return index;
	}
	// ��ȡ�ڵ�ǰ����״̬�������к�һ���ɷ�������������ֵ��
	// ����ֵ�����ݼ������ؼ����ҳ��ĺ�һ���ɷ�������������ֵ��
	int NextIndex()
	{
		int index = ((m_Index + 1) <= (m_Size - 2)) ? m_Index + 1 : m_Index;
		// �ڴ˼������
		if(CStudent::m_Retrieve != none)
		{
			while((index <= (m_Size - 2)) &&
				!(Get(index)->items == CStudent::m_RetrieveKey))
				index++;
			index = (index <= (m_Size - 2)) ? index : m_Index;
		}

		return index;
	}
	// ��һ����ΪT��������Ϊ��������������������½��ӵ�һ�������ǰ���������
	// ������xΪ�������½���������������ڵ���ʱ��ʵ����Ϊϵͳ����Ӧ�����ͣ�����CStudent��
	// ����ֵ�������������ɹ����򷵻�true�����򷵻�false��
	virtual bool InsertBefore(T x)
	{
		bool flag = false;
		// �ڴ˼������
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
	// ��p1ָ��Ľ���������ȡ�£�������嵽��pָ��Ľ��֮ǰ��
	// ������p��p1�ֱ�ָ�������е�������㡣
	void InsertBefore(node<T> *p, node<T> *p1)
	{
		// �ڴ˼������
		if(p == p1 || p == m_Head || p1 == m_Head)
			return;
		p1->prior->next = p1->next;
		p1->next->prior = p1->prior;
		p1->prior = p->prior;
		p->prior->next = p1;
		p1->next = p;
		p->prior = p1;

	}
	// ��һ����ΪT��������Ϊ��������������������½������һ�����������������
	// ������xΪ�������½���������������ڵ���ʱ��ʵ����Ϊϵͳ����Ӧ�����ͣ�����CStudent��
	// ����ֵ�������������ɹ����򷵻�true�����򷵻�false��
	virtual bool InsertAfter(T x)
	{
		bool flag = false;
		// �ڴ˼������
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
	// ��p1ָ��Ľ���������ȡ�£�������嵽��pָ��Ľ��֮��
	// ������p��p1�ֱ�ָ�������е�������㡣
	void InsertAfter(node<T> *p, node<T> *p1)
	{
		// �ڴ˼������
		if(p == p1 || p == m_Head || p1 == m_Head)
			return;
		p1->next->prior = p1->prior;
		p1->prior->next = p1->next;
		p1->next = p->next;
		p->next->prior = p1;
		p1->prior = p;
		p->next = p1;

	}
	// ��������Ѱ����������key��ͬ������㡣
	// ������keyΪ��Ѱ�ҵĽ�������е�������������ڵ���ʱ��ʵ����ϵͳ��ϵͳ����Ӧ�����ͣ�����CStudent��
	// ����ֵ������ҵ��˺���������key�Ľ�㣬�򷵻ظý���ָ�룬���򷵻�NULL��
	node<T>* Location(T key)
	{
		int index = 0;
		node<T> *p = m_Head->next;
		// �ڴ˼�����Σ�EndΪ�����Ψһ���ڣ���ˣ�����ڳ���ִ������Ҫ�ж�ִ�з���ʱ��
		// ��ִ�����goto End; ��
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
	// ��ȡ����ֵΪi������㡣
	// ������iΪ��Ѱ�ҵ�����������ֵ��
	// ����ֵ������ҵ�������ֵΪi������㣬�򷵻ظý���ָ�룬���򷵻�NULL��
	node<T>* Get(int i)
	{
		node<T> *p = m_Head->next;
		// �ڴ˼������
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
	// ��������ɾ����ָ��pָ�������㡣
	// ������pΪָ��ɾ��������ָ�롣
	void DeleteNode(node<T> *p)
	{
		// �ڴ˼������
		if(p == m_Head) return;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		p->next = NULL;
		p->prior = NULL;
		delete p;
		m_Size--;

	}
	// ��������ɾ��������Ϊx������㡣
	// ������xΪ��ɾ��������������������ڵ���ʱ��ʵ����ϵͳ��ϵͳ����Ӧ�����ͣ�����CStudent��
	// ����ֵ�����������Ϊx������㱻�ҵ����ұ�ȷ��ɾ�����򷵻�true�����򷵻�false��
	bool Delete(T x)
	{
		bool flag = false;
		node<T> *p = Location(x);
		if(p)
		{
			if(MessageBox(NULL,"ȷʵҪɾ����ǰ��ʾ�ļ�¼��",
						"ɾ����ʾ",MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				DeleteNode(p);
				m_Index = min(max(m_Index - 1, 0), m_Size - 2);
				flag = true;
			}
		}
		return flag;
	}
	// ��������ɾ������ֵΪi������㡣
	// ������iΪ��ɾ������������ֵ��
	// ����ֵ���������ֵΪi������㱻�ҵ�����ɾ�����򷵻�true�����򷵻�false��
	bool Delete(int i)
	{
		bool flag = false;
		// �ڴ˼������
		node<T>* p = Get(i);
		if(!p)
		{
			if(MessageBox(NULL,"ȷʵҪɾ����ǰ��ʾ�ļ�¼��",
						"ɾ����ʾ",MB_YESNO | MB_ICONQUESTION) == IDYES)
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
	// �б��������Ƿ��������������x��ͬ������㡣
	// ������xΪ���б�����������е�������������ڵ���ʱ��ʵ����ϵͳ��ϵͳ����Ӧ�����ͣ�����CStudent��
	// ����ֵ��������б���������ڣ��򷵻�true�����򷵻�false��
	bool contains(T x)
	{
		return Location(x) ? true : false;
	}
	// �������й鲢����һ�������ϵ�����㡣
	// ������low��mid��high�ֱ�Ϊ��������ʼ�㣬�е���յ������ֵ��
	void Merge(int low, int mid, int high)
	{
		// �ڴ˼������
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

	// �����������������һ��鲢����
	// ������lengthΪ�˱�鲢����������䳤�ȡ�
	void MergePass(int length)
	{
		// �ڴ˼������
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
	// ���ù鲢�����㷨�����������ϵĽ�㰴��ǰ������ؼ��ֽ�����ȫ����
	void MergeSort()
	{
		// �ڴ˼������
		int length;
		for(length = 1; length < m_Size - 1; length = length * 2)
			MergePass(length);
		m_Index = FirstIndex();
	}

	// ��������
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

// ����ģ��CD_Linkʵ����������ѧ��������
class CStudentSet : public CD_Link<CStudent>
{
public:
	// ���ݵ�ǰ������ؼ��ֺͼ����ؼ��ָ�ʽ�������ʾ���ӡ�������пɷ��ʽ��������
	// ������pDCΪָ���豸�����ĵ�ָ�룻posΪ��������ݳ�Ա����ʼλ�����ꣻ
	//		 sizeΪ�����������͵ĳߴ磻lheightΪ��ʽ�еĸ߶ȣ�
	//		 startΪ��ǰ���ҳ����ʼ�У�linesΪ��ǰ���ҳ��������
	void ShowItems(CDC *pDC, CPoint pos, CSize size, int lheight, int start, int lines);
	// ���ݵ�ǰ�ļ����ؼ��������Ϣ���ݱ�ı��⡣
	// ������pDCΪָ���豸�����ĵ�ָ�룻frameΪ������ݱ�Ŀ�ܵľ����������
	//		 fontΪ���ݱ����������ͣ�lheightΪ��ʽ�еĸ߶ȡ�
	void ShowTitle(CDC* pDC, CRect frame, CFont& font, int lheight);
	// ����������ݱ�Ŀ�ܡ�
	// ������pDCΪָ���豸�����ĵ�ָ�룻frameΪ������ݱ�Ŀ�ܵľ����������
	//		 sizeΪ�����������͵ĳߴ磻lheightΪ��ʽ�еĸ߶ȣ�linesΪ��ǰ���ҳ��������
	void DrawFrame(CDC* pDC, CRect frame, CSize size, int lheight, int lines);
	// ��һ��CStudent����������Ϊ��������������������½��ӵ�һ�������ǰ����뼯�ϡ�
	// ������itemsΪ�������½��������
	// ����ֵ�������������ɹ����򷵻�true�����򷵻�false��
	virtual bool InsertBefore(CStudent items);
	// ��һ��CStudent����������Ϊ��������������������½������һ������������뼯�ϡ�
	// ������itemsΪ�������½��������
	// ����ֵ�������������ɹ����򷵻�true�����򷵻�false��
	virtual bool InsertAfter(CStudent items);
};

#endif // !defined(AFX_DATA_H__A1B09821_34F3_11D5_88D8_9E17A6A3E7AE__INCLUDED_)
