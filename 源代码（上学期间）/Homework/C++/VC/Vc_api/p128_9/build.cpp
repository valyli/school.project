#include <iostream.h>
#include "build.h"

building::building(int a, int b, int c)
{
	floor=a;
	room=b;
	area=c;
}

void building::setbuilding(int a, int b, int c)
{
	floor=a;
	room=b;
	area=c;
}

void building::showbuilding()
{
	cout<<endl;
	cout<<"floor: "<<floor<<"  room: "<<room<<"  area: "<<area<<" ";
}

house::house(int a, int b, int c, int d, int e): building(a,b,c)
{
	bedroom=d;
	bathroom=e;
}

void house::sethouse(int a, int b, int c, int d, int e)
{
	setbuilding(a, b, c);
	bedroom=d;
	bathroom=e;
}

void house::showhouse()
{
	cout<<endl;
	showbuilding();
	cout<<"bedroom: "<<bedroom<<"  bathroom"<<bathroom<<" ";
}

office::office(int a, int b, int c, int d, int e, int f, int g) :house(a,b,c,d,e)
{
	fire=f;
	phone=g;
}

void office::setoffice(int a, int b, int c, int d, int e, int f, int g)
{
	sethouse(a, b, c, d, e);
	fire=f;
	phone=g;
}

void office::showoffice()
{
	showhouse();
	cout<<"fire: "<<fire<<"  phone: "<<phone<<" ";
}
