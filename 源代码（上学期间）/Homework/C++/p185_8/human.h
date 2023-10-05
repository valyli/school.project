#ifndef HUMAN
#define HUMAN

class human
{
protected:
	char *name;
	bool sex;
	int age;
public:
	human(char *a, bool b, int c)
	{
		name = new(char[20]);
		name = a;
		sex = b;
		age = c;
	}
//	human operator()(char *a, bool b, int c);
	virtual void print() = 0;
};

class teacher: public human
{
protected:
	char level;
public:
	teacher(char *a, bool b, int c, char d):human(a, b, c)
	{
		level = d;
	}
	virtual void print();
};

class student: public human
{
protected:
	long number;
public:
	student(char *a, bool b, int c, long d):human(a, b, c)
	{
		number = d;
	}
	virtual void print();
};

class staff: public human
{
protected:
	int paid;
public:
	staff(char *a, bool b, int c, int d):human(a, b, c)
	{
		paid = d;
	}
	virtual void print();
};

#endif
