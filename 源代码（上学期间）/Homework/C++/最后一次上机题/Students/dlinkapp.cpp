#include <string.h>
#include "dlink.h"

main()
{
	char *key = new char[10];
	studentset student;
	student.print();
	person item;
	item(1991002203, "李之研", "男", 22);
	student.insertafter(student.last(), item);
//	item(1991002202, "王炎", "女", 10);
//	student.insertafter(student.last(), item);
//	item(1991002204, "苗润", "男", 19);
//	student.insertafter(student.last(), item);
	item(1991002205, "许可佳", "女", 3);
	student.insertafter(student.last(), item);
//	item(1991002206, "章静", "女", 8);
//	student.insertafter(student.last(), item);
	item(1991002201, "刘栋", "男", 19);
	student.insertafter(student.last(), item);
//	item(1991002208, "王更", "女", 3);
//	student.insertafter(student.last(), item);
//	item(1991002207, "陈维闻", "女", 8);
//	student.insertafter(student.last(), item);
	item(1991002203, "李之研", "男", 22);
	student.insertafter(student.last(), item);
	item(1991002205, "许可佳", "女", 3);
	student.insertafter(student.last(), item);
	student.print();
	student.save();
	student.in_order();
	student.print();
	student.open();
	student.find_sex("男");
	student.find_age(3);
/*	item(1991002208, "王更");
	if(student.location(item))
		cout<<"location"<<endl;
	else
		cout<<"not location"<<endl;
	student.rev_order();
	student.print();
	item(1991002208, "王更");
	student.deletes(item);
	student.print();
*/
	return 1;
}