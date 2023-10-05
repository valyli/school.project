#include<iostream.h>

int &f(int &i)
{
	i+=10;
	return i;
}

void main()
{
	int k=0;
	int &m=f(k);
	cout<<k<<endl;
	m=20;
	cout<<k<<endl;
}
