#include <iostream.h>

template <class T>
struct node
{
	T val;
	node *prior, *next;
}

class person
{
	long id;
	char name[15];
public:
	person();
	void operator()(long i, char *n);
	friend bool operator==(person s, person s1);
	friend bool operator>(person s, person s1);
	friend bool operator<(person s, person s1);
	friend ostream& operator<<(ostream &stream, person s);
	friend istream& operator>>(istream &stream, person &s);
};

template <class T>
class dlink
{
	node<T> *head;
	int size;
public:
	dlink();
	node<T> *gethead();
	{return head;}
	node<T> *first();
	{return head->next;}
	node<T> *last();
	{return head->prior;}
	virtual bool insertbefore(node<T> *p, T val);
	virtual bool insertafter(node<T> *p, T val);
	node<T>* location(T key);
	node<T>* get(int i);
	void deletenode(node<T> *p);
	bool deletes(T val);
	bool contains(T val);
	void rev_order();
	void print();
	~dlink();
};

class studentset: public dlink<person>
{
public:
	bool insertbefore(node<person> *p, person val);
	bool insertafter(node<person> *p, person val);
};

template <class T>
dlink<T>::dlink()
{
	head = new node<T>;
	head->prior = head;
	head->next = head;
	size = 1;
}

template <class T>
dlink<T>::~dlink()
{
	node<T> *temp, *p = head;
	for(int i = 0; i<size; i++)
	{
		temp = p;
		p = p->next;
		delete temp;
	}
}

template <class T>
bool dlink<T>::insertbefore(node<T> *p, T x)
{
	node<T> *nodes = new node<T>;
	if(nodes)
	{
		nodes->val = x;
		nodes->next = p;
		nodes->prior = p->prior;
		p->prior->next = nodes;
		p->prior = nodes;
		size++;
		return true;
	}
	return false;
}

template <class T>
bool dlink<T>::insertafter(node<T> *p, T x)
{
	node<T> *nodes = new node<T>;
	if(nodes)
	{
		nodes->val = x;
		nodes->next = p->next;
		nodes->prior = p;
		p->next->prior = nodes;
		p->next = nodes;
		size++;
		return true;
	}
	return false;
}

template <class T>
node<T>* dlink<T>::location(T x)
{
	node<T> *p = head->next;
	while(p != head)
	{
		if(p->val == x)
			return p;
		p = p->next;
	}
	return NULL;
}

template <class T>
node<T>* dlink<T>::get(int i)
{
	node<T> *p = head->next;
	int j = 0;
	while((p != head)&&(j<i))
	{
		p = p->next;
		j++;
	}
	if(i == j)
		return p;
	else 
		return NULL;
}

template <class T>
void dlink<T>::deletenode(node<T> *p)
{
	p->prior->next = p->next;
	p->next->prior = p->prior;
	delete p;
	size--;
}

template <class T>
bool dlink<T>::deletes(T x)
{
	node<T> *p = location(x);
	if(p)
	{
		deletenode(p);
		return true;
	}
	else
		return false;
}

template <class T>
bool dlink<T>::contains(T x)
{
	bool flag = location(x)?true: false;
	return flag;
}

template <class T>
void dlink<T>::rev_order()
{
	node<T> *p = head->prior, *rev_head, *p1, *temp;
	if(p == head)
		return;
	rev_head = new node<T>;
	rev_head->prior = rev_head->next = rev_head;
	p1 = rev_head;
	while(p != head)
	{
		p->prior->next = p->next;
		p->next->prior = p->prior;
		temp = p;
		p = head->prior;
		temp->next = p1->next;
		temp->prior = p1;
		p1->next->prior = temp;
		p1->next = temp;
		p1 = p1->next;
	}
	delete head;
	head = rev_head;
}

template<class T>
void dlink<T>::print()
{
	node<T> *p = head->next;
	if(p == head)
	{
		cout<<"The double link list is empty!"<<endl;
		return;
	}
	while(p != head)
	{
		cout<<" "<<p->val;
		p = p->next;
	}
	cout<<endl;
}
