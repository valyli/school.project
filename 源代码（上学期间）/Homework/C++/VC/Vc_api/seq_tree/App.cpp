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
////����ΪbitreeתΪsequen(2)////
	cout<<endl<<"����ΪbitreeתΪsequen(2)"<<endl;
	s1=new sequen;
	b1->treetoseq(s1);
	s1->print();
	cout<<endl;
	delete s1;
////����Ϊɾ��bitree(1)////
	b1->deltree();
////����Ϊ�ü������������(3)////
////����0����//////
	cout<<endl<<"����Ϊ�ü������������(3)"<<endl;
	cout<<"����0����"<<endl;
	int val;
	b1=new bitree;
	s1=new sequen;
	while(1)
	{
		cin>>val;
		if(val == 0) break;
		b1->insert(val);
	}
////����Ϊ�����������ʾ������(3)////
	cout<<endl<<"����Ϊ�����������ʾ������(3)"<<endl;
	b1->Preprint();
	b1->treetoseq(s1);
	cout<<endl<<"����������ʾΪ:"<<endl;
	s1->print();
	delete s1;
	b1->deltree();
	return 0;
}
