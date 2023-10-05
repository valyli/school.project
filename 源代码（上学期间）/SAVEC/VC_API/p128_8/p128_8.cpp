#include <iostream.h>

class A
{
protected:
	int m,n;
public:
	void set(int a, int b)
	{m=a; n=b;}
	void show()
	{cout<<m<<" "<<n<<"\n";}
};

class B:public A
{
	int s;
public:
	void sets()
	{s=m*n;}
	void shows()
	{cout<<s<<"\n";}
};

int main()
{
	B obj;
	obj.set(2,3);
	obj.show();
	obj.sets();
	obj.shows();
	return 0;
}