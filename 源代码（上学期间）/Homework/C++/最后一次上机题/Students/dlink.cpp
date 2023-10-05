#include <string.h>
#include "dlink.h"

person::person()
{
	id = 0;
	strcpy(name, "");
	strcpy(sex, "");
	age = 0;
}

void person::operator ()(long i, char *n, char *s, unsigned int a)
{
	id = i;
	strcpy(name, n);
	strcpy(sex, s);
	age = a;
}

bool operator==(person s, person s1)
{
	bool flag = s.id == s1.id ? true : false;
	return flag;
}

bool operator>(person s, person s1)
{
	bool flag = s.id > s1.id ? true : false;
	return flag;
}

bool operator<(person s, person s1)
{
	bool flag = s.id < s1.id ? true : false;
	return flag;
}

ostream& operator<<(ostream &stream, person s)
{
	stream<<s.id<<" "<<s.name<<" "<<s.sex<<" "<<s.age<<endl;
	return stream;
}

istream& operator>>(istream &stream, person &s)
{
	stream>>s.id;
	stream.getline(s.name, 10);
	stream.getline(s.sex, 5);
	stream>>s.age;
	return stream;
}

bool studentset::insertbefore(node<person> *p, person x)
{
	if(!(dlink<person>::contains(x)) && (dlink<person>::insertbefore(p, x)))
	{
		return true;
	}
	return false;
}

bool studentset::insertafter(node<person> *p, person x)
{
	if(!(dlink<person>::contains(x)) && (dlink<person>::insertafter(p, x)))
	{
		return true;
	}
	return false;
}
