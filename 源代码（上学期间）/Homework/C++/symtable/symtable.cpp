#include "symbol.h"
#include <iostream.h>

void main()
{
	SSymTable a;
///// Input Table      ////
	a.AddTable(9,"asdf");
	a.AddTable(6,"gji");
	a.AddTable(8,"qepiow");
	a.ShowTable();
///// Up Table by value //////	
	cout<<"Up Table by value"<<endl;
	a.UpTable_V();
	a.ShowTable();
///// Down Table by value ////
	cout<<"Down Table by value"<<endl;
	a.DownTable_V();
	a.ShowTable();
///// Up Table by name /////
	cout<<"Up Table by name"<<endl;
	a.UpTable_N();
	a.ShowTable();
///// Down Table by name ////
	cout<<"Down Table by name"<<endl;
	a.DownTable_N();
	a.ShowTable();
}
