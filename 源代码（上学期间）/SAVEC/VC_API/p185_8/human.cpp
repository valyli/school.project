#include <iostream.h>
#include "human.h"

void teacher::print()
{
	cout<<" Name:  "<<name<<endl;
	cout<<" Work:  Teacher"<<endl;
	cout<<" Sex:   "<<(sex?"Male":"Female")<<endl;
	cout<<" Age:   "<<age<<endl;
	cout<<" Level: "<<level<<endl;
	cout<<endl;
}

void student::print()
{
	cout<<" Name:  "<<name<<endl;
	cout<<" Work:  Student"<<endl;
	cout<<" Sex:   "<<(sex?"Male":"Female")<<endl;
	cout<<" Age:   "<<age<<endl;
	cout<<" Number:"<<number<<endl;
	cout<<endl;
}

void staff::print()
{
	cout<<" Name:  "<<name<<endl;
	cout<<" Work:  Teacher"<<endl;
	cout<<" Sex:   "<<(sex?"Male":"Female")<<endl;
	cout<<" Age:   "<<age<<endl;
	cout<<" Paid:  "<<paid<<endl;
	cout<<endl;
}