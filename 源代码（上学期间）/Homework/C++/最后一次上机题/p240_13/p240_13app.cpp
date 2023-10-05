#include <string.h>
#include "p240_13.h"

void main()
{
	studentset student;
	student.print();
	Person item;
	item(1991002202,"王炎","女",19);
	student.insertafter(student.last(),item);
	item(1991002203,"李之研","男",21);
	student.insertafter(student.last(),item);
	item(1991002204,"苗润","男",19);
	student.insertafter(student.last(),item);
	item(1991002205,"许可佳","女",20);
	student.insertafter(student.last(),item);
	item(1991002206,"章静","女",19);
	student.insertafter(student.last(),item);
	item(1991002207,"陈维闻","女",20);
	student.insertafter(student.last(),item);
	item(1991002203,"李之研","男",21);
	item(1991002201,"刘栋","男",19);
	student.insertafter(student.last(),item);
	student.insertafter(student.last(),item);
	item(1991002208,"王更","女",20);
	student.insertafter(student.last(),item);
	item(1991002205,"许可佳","女",20);
	student.insertafter(student.last(),item);
	student.print();
	item(1991002208,"王更","女",20);
	if(student.location(item))
		cout<<"location"<<endl;
	else
		cout<<"not location"<<endl;
	student.in_order();
	student.print();
	item(1991002208,"王更","女",20);
	student.deletes(item);
	student.search(19);
	student.save();
	student.open();
}