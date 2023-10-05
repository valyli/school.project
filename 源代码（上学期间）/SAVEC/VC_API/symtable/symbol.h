#ifndef SYMBOL
#define SYMBOL
#define MIN -32767
struct symbol
{
	char *name;
	int value;
	symbol *next;
};

class SymTable
{
protected:
	symbol head;
public:
	SymTable()
	{
		head.next = 0;
		head.value = 0;
		head.name = "0";
	}
	void AddTable(int value, char *name);
	void ShowTable();
};

class SSymTable: public SymTable
{
public:
	void UpTable_V();
	void DownTable_V();
	void UpTable_N();
	void DownTable_N();
};

#endif
