#include <iomanip.h>
#include <math.h>

int sroot(int num)
{
	return (int)sqrt((double)num);
}

long sroot(long num)
{
	return (long)sqrt((double)num);
}

double sroot(double num)
{
	return sqrt(num);
}

void main(void)
{
	int num_int=4;
	long num_long=4;
	double num_double=4.0;
	cout<<"INT    "<<sroot(num_int)<<endl;
	cout<<"LONG   "<<sroot(num_long)<<endl;
	cout<<"DOUBLE "<<setiosflags(ios::showpoint)<<sroot(num_double)<<endl;
}
