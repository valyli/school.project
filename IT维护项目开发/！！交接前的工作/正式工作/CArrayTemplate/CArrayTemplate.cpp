// CArrayTemplate.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "LIDP_CArrayTemplate.h"

struct tt
{
	int a;
	int b;
};

int main(int argc, char* argv[])
{
	LIDP_CArrayTemplate<int, int*> a;
	int b = 0;
	a.Add(b);
	b++;
	a.Add(b);
	b++;
	a.Add(b);

	printf("GetAt(1) = %d\n", a.GetAt(1));

	a.SetAt(1, 9);
	printf("GetAt(1) = %d\n", a.GetAt(1));

	a[1] = 5;
	printf("a[] = %d\n",a[1]);

	printf("return:%d\n", a.RemoveAt(2,1));

	LIDP_CArrayTemplate<int, int*> c;
	c.Add(100);
	c.Add(200);
	printf("append\n");
	a.Append(c);

	a.InsertAt(2, 600);
/*	a.RemoveAll();
*/

	int i;
	for(i = 0; i < a.GetCount(); i++)
		printf("a[%d] = %d\n" ,i ,a[i]);

	LIDP_CArrayTemplate<int, int*> d;
	d.Add(1000);
	d.Add(2000);
	a.InsertAt(3, d);

	for(i = 0; i < a.GetCount(); i++)
		printf("a[%d] = %d\n" ,i ,a[i]);

	LIDP_CArrayTemplate<tt, tt*> f;
	tt z;
	z.a = 1;
	z.b = 11;
	f.Add(z);
	z.a = 2;
	z.b = 22;
	f.Add(z);
	for(i = 0; i < f.GetCount(); i++)
	{
		printf("z[%d].a = %d   .b = %d\n" ,i ,f[i].a, f[i].b);
	}
	return 0;
}

