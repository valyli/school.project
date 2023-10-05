#include "human.h"

void main()
{
	human *p;
	teacher a("John", true, 23, 'A');
	student b("Jim", false, 15, 99213);
	staff c("Tom", true, 42, 1500.00);
	p = &a;
	p->print();
	p = &b;
	p->print();
	p = &c;
	p->print();
}
