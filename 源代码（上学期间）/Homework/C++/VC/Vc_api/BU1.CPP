#include<iomanip.h>

void main(void)
{
	float total=0.0,price;
	cout<<"Please input three prices:";
	for(int i=1;i<=3;i++)
	{
		cin>>price;
		cout<<endl;
		total+=price;
	}
	cout<<"Total is:"<<endl<<setw(20)
		<<setiosflags(ios::right|ios::showpoint|ios::fixed)
		<<setprecision(2)<<setfill('*')<<total<<endl;
}



