#ifndef THREE_D
#define THREE_D
#include <iostream.h>

class three_d
{
	int x, y, z;
public:
	three_d(int i, int j, int k)
	{ x = i; y = j; z = k;}
	three_d()
	{ x = 0; y = 0; z = 0;}
	void get(int &i, int &j, int &k)
	{ i = x; j = y; k = z;}
	void show()
	{ cout<<"x = "<<x<<"; y = "<<y<<"; z = "<<z<<endl;}
	friend three_d operator+(three_d ob, int i);
	friend three_d operator+(int i, three_d ob);
	void operator=(three_d ob);
	three_d operator --();
	three_d operator ++();
};

#endif