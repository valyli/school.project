#include <string.h>
#include "p240_13.h"

void main()
{
	studentset student;
	student.print();
	Person item;
	item(1991002202,"����","Ů",19);
	student.insertafter(student.last(),item);
	item(1991002203,"��֮��","��",21);
	student.insertafter(student.last(),item);
	item(1991002204,"����","��",19);
	student.insertafter(student.last(),item);
	item(1991002205,"��ɼ�","Ů",20);
	student.insertafter(student.last(),item);
	item(1991002206,"�¾�","Ů",19);
	student.insertafter(student.last(),item);
	item(1991002207,"��ά��","Ů",20);
	student.insertafter(student.last(),item);
	item(1991002203,"��֮��","��",21);
	item(1991002201,"����","��",19);
	student.insertafter(student.last(),item);
	student.insertafter(student.last(),item);
	item(1991002208,"����","Ů",20);
	student.insertafter(student.last(),item);
	item(1991002205,"��ɼ�","Ů",20);
	student.insertafter(student.last(),item);
	student.print();
	item(1991002208,"����","Ů",20);
	if(student.location(item))
		cout<<"location"<<endl;
	else
		cout<<"not location"<<endl;
	student.in_order();
	student.print();
	item(1991002208,"����","Ů",20);
	student.deletes(item);
	student.search(19);
	student.save();
	student.open();
}