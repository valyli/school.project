#include <iostream.h>
#include <string.h>
#include "symbol.h"

void SymTable::AddTable(int value, char *name)
{
	symbol *p, *q;
	p = &head;
	while(p->next != 0)
		p = p->next;
	q = new(symbol);
	q->value = value;
	q->name = name;
	p->next = q;
	q->next = 0;
}

void SymTable::ShowTable()
{
	symbol *p;
	p = head.next;
	while(p != 0)
	{
		cout<<"Name: "<<p->name<<"  Value: "<<p->value<<endl;
		p = p->next;
	}
	cout<<endl;
}

void SSymTable::UpTable_V()
{
	symbol *p, *q, *t, *e;
	e = 0;
	while(e != head.next->next)
	{
		p = &head;
		while(p->next->next != e)
		{
			q = p->next;
			t = q->next;
			if(q->value > t->value)
			{
				p->next = t;
				q->next = t->next;
				t->next = q;
			}
			p = p->next;
		}
		e = p->next;
	}
}

void SSymTable::DownTable_V()
{
	symbol *p, *q, *t, *e;
	e = 0;
	while(e != head.next->next)
	{
		p = &head;
		while(p->next->next != e)
		{
			q = p->next;
			t = q->next;
			if(q->value < t->value)
			{
				p->next = t;
				q->next = t->next;
				t->next = q;
			}
			p = p->next;
		}
		e = p->next;
	}
}


void SSymTable::UpTable_N()
{
	symbol *p, *q, *t, *e;
	e = 0;
	while(e != head.next->next)
	{
		p = &head;
		while(p->next->next != e)
		{
			q = p->next;
			t = q->next;
			if(strcmp(q->name, t->name) == 1)
			{
				p->next = t;
				q->next = t->next;
				t->next = q;
			}
			p = p->next;
		}
		e = p->next;
	}
}

void SSymTable::DownTable_N()
{
	symbol *p, *q, *t, *e;
	e = 0;
	while(e != head.next->next)
	{
		p = &head;
		while(p->next->next != e)
		{
			q = p->next;
			t = q->next;
			if(strcmp(q->name, t->name) == -1)
			{
				p->next = t;
				q->next = t->next;
				t->next = q;
			}
			p = p->next;
		}
		e = p->next;
	}
}

