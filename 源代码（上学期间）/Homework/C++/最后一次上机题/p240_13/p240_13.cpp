#include <string.h>
#include "p240_13.h"

Person::Person()
{
	id=0;
	strcpy(name,"");
	strcpy(sex,"");
	age=0;
}

void Person::operator ()(long i,char *n,char *s,unsigned a)
{
	id=i;
	strcpy(name,n);
	strcpy(sex,s);
	age=a;
}

bool Person::distin(char *se)
{
	bool flag = strcmp(sex , se) == 0 ? 1:0;
	return flag;
}


bool Person::distin(unsigned a)
{
	bool flag = age == a ? 1:0;
	return flag;
}

bool operator ==(Person s, Person s1)
{
	bool flag = s.id == s1.id ? 1:0;
	return flag;
}

bool operator >(Person s,Person s1)
{
	bool flag =s.id>s1.id ? 1:0;
    return flag;
}

bool operator <(Person s,Person s1)
{
	bool flag=s.id<s1.id ? 1:0;
	return flag;
}

ostream& operator <<(ostream &stream, Person s)
{
	stream << s.id <<" "<< s.name<<" "<<s.sex<<" "<<s.age<<endl;
	return stream;
}

istream& operator >>(istream &stream,Person &s)
{
	stream>>s.id;
	stream.getline(s.name,10);
	stream.getline(s.sex,4);
	stream>>s.age;
	return stream;
}

bool studentset::insertbefore(Node<Person> *p,Person val)
{
	if(!(DLink<Person>::contains(val)) && (DLink<Person>::insertbefore(p,val)))
	{
		return 1;
	}
	return 0;
}

bool studentset::insertafter(Node<Person> *p,Person val)
{
	if(!(DLink<Person>::contains(val)) && (DLink<Person>::insertafter(p,val)))
	{
		return 1;
	}
	return 0;
}

void studentset::search(char *s)
{
	Node<Person> *p=head->prior;
	while (p!=head)
	{
		if(p->val.distin(s))
			cout<<p->val;
		p=p->prior;
	}
}

void studentset::search(unsigned a)
{
	Node<Person> *p=head->prior;
	while (p!=head)
	{
		if(p->val.distin(a))
			cout<<p->val;
		p=p->prior;
	}
}