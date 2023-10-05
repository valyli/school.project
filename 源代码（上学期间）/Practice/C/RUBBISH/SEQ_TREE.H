#ifndef SEQ_TREE
#define SEQ_TREE

enum errcode {noerr, overflow};
enum bool{FALSE, TRUE};

struct node
{
	int item;
	node *left;
	node *right;
};

class sequen;
class bitree
{
	node *root;
	node *insertnode(node*, node*);
	void printnode(node *binode);
public:
	bitree(){root=0;}
	bool insert(int val);
	void print();
	void seqtotree(sequen*, int, int);
};

class sequen
{
	int *items;
	int size, used;
public:
	sequen(int sz=16);
	int getused(){return used;}
	errcode insert(int);
	void print();
	friend node *maketree(sequen*, int, int);
	friend void bitree::seqtotree(sequen*, int, int);
};

#endif