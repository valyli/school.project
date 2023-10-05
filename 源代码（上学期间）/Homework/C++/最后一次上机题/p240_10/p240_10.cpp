//²âÊÔÓÃÎÄ¼ş£ºtest.txt
#include <iostream.h>
#include <fstream.h>

void main()
{
	int length = 0;
	char buff;
	ifstream in("test.txt");
	
	if (!in)
	{
		cout<<"Cannot open input file.\n";
	}
	while(!in.eof())
	{
		in.get();
		length++;
	}
	in.clear();
	length = -1 * length;
	for(int i = -1; i >= length - 1; --i)
	{
		in.seekg(i,ios::end);
		in.get(buff);
		cout<<buff;
	}
	in.close();
	cout<<endl;
}