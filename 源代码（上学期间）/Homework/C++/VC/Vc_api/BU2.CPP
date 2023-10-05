#include<iomanip.h>
#include<math.h>
void main(void)
{
	cout<<"                         **********SIN A**********"<<endl;
	cout<<setw(9)<<"A";
	for(int i=0;i<=60;i+=12)
		cout<<setw(8)<<i<<"\'";
	cout<<"\n";
	for(double du=0;du<30.0;du++)
	{
		if((int)du%22==21) cin.get();
		cout<<setw(9)<<(int)du;
		for(double fen=0;fen<=60;fen+=12)
			cout<<setw(9)<<setprecision(4)
			<<setiosflags(ios::showpoint|ios::fixed)
			<<sin(3.1415926/180*du+3.1415926/180*fen/60);
		cout<<setw(9)<<90-(int)du-1;
		cout<<"\n";
	}
	cout<<setw(9)<<" ";
	for(i=60;i>=0;i-=12)
		cout<<setw(8)<<i<<"\'";
	cout<<setw(9)<<"A";
	cout<<endl<<"                         **********COS A**********"<<endl;

}












