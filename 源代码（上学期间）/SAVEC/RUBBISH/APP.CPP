#include <iostream.h>
#include "seq_tree.h"

int main(void)
{
	sequen *s1;
	bitree *b1;
	s1 = new sequen;
	b1 = new bitree;
	s1->insert(34);
	s1->insert(657);
	s1->insert(345);
	s1->insert(213);
	s1->insert(562);
	s1->insert(43);
	s1->insert(234);
	s1->insert(84);
	s1->print();
	b1->seqtotree(s1, 0, s1->getused() - 1);
	b1->print();
	b1->insert(23);
	b1->print();
	b1->insert(400);
	b1->print();
	b1->insert(900);
	b1->print();
	delete s1;
	delete b1;
	return 0;
}
