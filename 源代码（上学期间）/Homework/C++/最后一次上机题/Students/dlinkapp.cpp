#include <string.h>
#include "dlink.h"

main()
{
	char *key = new char[10];
	studentset student;
	student.print();
	person item;
	item(1991002203, "��֮��", "��", 22);
	student.insertafter(student.last(), item);
//	item(1991002202, "����", "Ů", 10);
//	student.insertafter(student.last(), item);
//	item(1991002204, "����", "��", 19);
//	student.insertafter(student.last(), item);
	item(1991002205, "��ɼ�", "Ů", 3);
	student.insertafter(student.last(), item);
//	item(1991002206, "�¾�", "Ů", 8);
//	student.insertafter(student.last(), item);
	item(1991002201, "����", "��", 19);
	student.insertafter(student.last(), item);
//	item(1991002208, "����", "Ů", 3);
//	student.insertafter(student.last(), item);
//	item(1991002207, "��ά��", "Ů", 8);
//	student.insertafter(student.last(), item);
	item(1991002203, "��֮��", "��", 22);
	student.insertafter(student.last(), item);
	item(1991002205, "��ɼ�", "Ů", 3);
	student.insertafter(student.last(), item);
	student.print();
	student.save();
	student.in_order();
	student.print();
	student.open();
	student.find_sex("��");
	student.find_age(3);
/*	item(1991002208, "����");
	if(student.location(item))
		cout<<"location"<<endl;
	else
		cout<<"not location"<<endl;
	student.rev_order();
	student.print();
	item(1991002208, "����");
	student.deletes(item);
	student.print();
*/
	return 1;
}