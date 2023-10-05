#include <iostream.h>
#include <fstream.h>

double in[10]={{0.0},{0.1},{0.2},{0.3},{0.4},{0.5},{0.6},{0.7},{0.8},{0.9}};
double out[10];

void main()
{
	ofstream storage("p240_12.dat");
	if (! storage)
	{
		cout<<"Cannot open the file p240_12.dat";
	}
    storage.write((unsigned char *)&in,sizeof(in));
	storage.close();
    int Index;
	ifstream obtain("p240_12.dat");
	obtain.read((unsigned char *)&out,sizeof(in));
	
	cout<<"Please input the No. of the number: ";
	cin>>Index;
	cout<<"The float is: "<<out[Index]<<endl;
    obtain.close();
}
