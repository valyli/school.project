#include<iomanip.h>
#include<math.h>
#include<conio.h>

void main(void)
{
	int i;
	cout<<setw(10)<<"Num"<<setw(10)<<"lnNum"<<setw(10)<<"logNum"<<endl;
	for(i=2;i<=100;i++)
	{	
		cout<<setw(10)<<setprecision(5)
			<<i<<setiosflags(ios::right|ios::showpoint|ios::fixed)
			<<setw(10)<<log(i)<<setw(10)<<log10(i)<<"\n";
		if(i%23==1)
		{
			cin.get();
			cout<<setw(10)<<"Num"<<setw(10)<<"lnNum"<<setw(10)<<"logNum"<<endl;
		}
	}
}
