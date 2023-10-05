#include <iostream.h>
#include "build.h"

void main()
{
	building mybuild(5,50,5000);
	mybuild.showbuilding();
	mybuild.setbuilding(6,60,6000);
	mybuild.showbuilding();
	house myhouse(5,50,5000,3,2);
	myhouse.showhouse();
	office myoffice(6,60,6000,3,2,2,5);
	myoffice.showoffice();
	cout<<endl;
}