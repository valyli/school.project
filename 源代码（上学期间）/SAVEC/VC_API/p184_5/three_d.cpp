#include "three_d.h"

three_d operator+(three_d ob, int i)
{
	ob.x += i;
	ob.y += i;
	ob.z += i;
	return ob;
}

three_d operator+(int i, three_d ob)
{
	ob.x += i;
	ob.y += i;
	ob.z += i;
	return ob;
}

three_d three_d::operator--()
{
	--x;
	--y;
	--z;
	return *this;
}

three_d three_d::operator ++()
{
	++x;
	++y;
	++z;
	return *this;
}

void three_d::operator =(three_d ob)
{
	x = ob.x;
	y = ob.y;
	z = ob.z;
}

