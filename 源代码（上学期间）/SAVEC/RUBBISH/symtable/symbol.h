#ifndef SYMBOL
#define SYMBOL

struct symbol
{
	char *name;
	int value;
	symbol *next;
};

class SymTable
{
private:
	symbol head;
public:
	SymTable()
	{
		head.next=NULL;
		head.value=0;
		head.name="0";
	}
	void AddTable(char *name);
	