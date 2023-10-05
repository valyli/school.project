#include "three_d.h"

void main()
{
	int x, y, z;
	three_d a(5, 6, 7);
	a.show();
	a.get(x, y, z);
	cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<endl;
	three_d b;
	b.show();
	cout<<endl<<"b=a+5"<<endl;
	b=a+5;
	b.show();
	cout<<endl<<"a=5+b"<<endl;
	a=5+b;
	a.show();
	cout<<endl<<"a++"<<endl;
	++a;
	a.show();
	cout<<endl<<"b--"<<endl;
	--b;
	b.show();
}
