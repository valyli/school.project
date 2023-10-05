#include <iostream.h>
#include <fstream.h>

template <class T>
struct Node
{
	T val;
	Node *prior, *next;
};

class Person
{
	long id;
	char name[15];
	char sex[5];
	unsigned age;
public:
	Person();
	void operator()(long i,char *n,char *s,unsigned a);
    bool distin(unsigned a);
	bool distin(char *se);
	friend bool operator ==(Person s, Person s1);
    friend bool operator >(Person s, Person s1);
    friend bool operator <(Person s, Person s1);
    friend ostream& operator <<(ostream &stream, Person s);
	friend istream& operator >>(istream &stream, Person& s);
};

template <class T>
class DLink
{
protected:
	Node<T> *head;
	int size;
public:
	DLink();
	Node<T>* gethead()
	{ return head; }

	Node<T>* first()
	{ return head->next; }

	Node<T>* last()
	{ return head->prior; }

	virtual bool insertbefore(Node<T> *p,T x);
	virtual bool insertafter(Node<T> *p,T x);
	Node<T>* location(T key);
	Node<T>* get(int i);
	void deletenode(Node<T> *p);
	bool deletes(T val);
	bool contains(T val);
	void rev_order();
	void in_order();
	void print();
	void save();
	void open();
	~DLink();
};

class studentset : public DLink<Person>
{
public:
	bool insertbefore(Node<Person> *p, Person val);
	bool insertafter(Node<Person> *p, Person val);
	void search(char *s);
	void search(unsigned a);
};

template <class T>
DLink<T>::DLink()
{
	head=new Node<T>;
	head->prior=head;
	head->next=head;
	size=1;
}

template <class T>
DLink<T>::~DLink()
{
	Node<T> *temp, *p=head;
	for (int i=0; i<size; i++)
	{
		temp=p;
		p=p->next;
		delete temp;
	}
}

template <class T>
bool DLink<T>::insertbefore(Node<T> *p, T x)
{
	Node<T> *nodes=new Node<T>;
	if(nodes)
	{
		nodes->val=x;
		nodes->next=p;
		nodes->prior=p->prior;
		p->prior->next=nodes;
		p->prior=nodes;
		size++;
		return 1;
	}
	return 0;
}

template <class T>
bool DLink<T>::insertafter(Node<T> *p, T x)
{
	Node<T> *nodes=new Node<T>;
	if(nodes)
	{
		nodes->val=x;
		nodes->next=p->next;
		nodes->prior=p;
		p->next->prior=nodes;
		p->next=nodes;
		size++;
		return 1;
	}
	return 0;
}

template <class T>
Node<T>* DLink<T>::location(T key)
{
	Node<T> *p=head->next;
	while (p!=head)
	{
		if(p->val==key)
			return p;
		p=p->next;
	}
	return 0;
}

template <class T>
Node<T>* DLink<T>::get(int i)
{
	Node<T> *p=head->next;
	int j=0;
	while((p!=head) && (j<i))
	{
		p=p->next;
		j++;
	}
	if(i==j)
		return p;
	else
		return 0;
}

template <class T>
void DLink<T>::deletenode(Node<T> *p)
{
	p->prior->next=p->next;
	p->next->prior=p->prior;
    delete p;
	size--;
}

template <class T>
bool DLink<T>::deletes(T val)
{
	Node<T> *p=location(val);
	if(p)
	{
		deletenode(p);
		return 1;
	}
	else 
		return 0;
}

template <class T>
bool DLink<T>::contains(T val)
{
	bool flag=location(val) ? 1:0;
	return flag;
}

template <class T>
void DLink<T>::rev_order()
{
	Node<T> *p=head->prior,*rev_head,*p1,*temp;
	if(p==head)
		return;
	rev_head=new Node<T>;
	rev_head->prior=rev_head->next=rev_head;
	p1=rev_head;
	while(p!=head)
	{
		p->prior->next=p->next;
		p->next->prior=p->prior;
		temp=p;
		p=head->prior;
		temp->next=p1->next;
		temp->prior=p1;
		p1->next->prior=temp;
		p1->next=temp;
		p1=p1->next;
	}
	delete head;
	head=rev_head;
}

template <class T>
void DLink<T>::in_order()
{
    Node<T> *p = head->next, *q, *r = head;
	if(p == head)
		return;
	while(head->next != r)
	{
		p = head->next;
		q = p->next;
		while(p->next != r)
		{
			if(p->val > q->val)
			{
				p->prior->next = q;
				q->next->prior = p;
				q->prior = p->prior;
				p->next = q->next;
				q->next = p;
				p->prior = q;
				p = p->prior;
			}
			p = p->next;
			q = p->next;
		}
		r = r->prior;
	}
}

template <class T>
void DLink<T>::print()
{
	Node<T> *p=head->next;
	if(p==head)
	{
		cout<<"The double link list is empty!"<<endl;
		return;
	}
	while(p!=head)
	{
		cout<<" "<<p->val;
		p=p->next;
	}
	cout<<endl;
}

template <class T>\
void DLink<T>::save()
{
	Node<T> *p=head->next;
	ofstream out_student("STUD.REC");
	if (!out_student)
	{
		cout<<"Cannot open the file!";
	}

	if(p == head)
	{
		cout<<"The double link list is empty!"<<endl;
		return;
	}
	while(p != head)
	{
		out_student.write((unsigned char*)&(p->val),sizeof(p->val));
		p = p -> next;
	}
	out_student.close();
}

template <class T>
void DLink<T>::open()
{
	Node<T> *p;
	ifstream in_student("STUD.REC");
	if(!in_student)
	{
		cout<<"Cannot open the file!";
	}
    p = new Node<T>;
	while(!in_student.eof())
	{
		in_student.read((unsigned char*)&(p->val),sizeof(p->val));
	    cout<<p->val<<endl;
	}
	in_student.close();
}