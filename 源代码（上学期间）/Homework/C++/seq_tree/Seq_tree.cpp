#include <iostream.h>
#include "seq_tree.h"

sequen::sequen(int sz)
{
	if(sz < 16) sz = 16;
	items = new int[sz];
	size = sz;
	used = 0;
}

errcode sequen::insert(int elem)
{
	if(used == 0)
	{
		items[used++]=elem;
		return noerr;
	}
	if(used == size)
	{
		return overflow;
	}
	for(int i = 0; i < used; i++)
		if(items[i] > elem)
		{
			for(int j = used; j > i; j--)
				items[j] = items[j-1];
			items[i] = elem;
			used++;
			return noerr;
		}
		else if(items[i] == elem)
			return noerr;
	items[used++]= elem;
	return noerr;
}

void sequen::print()
{
	if(used == 0)
	{
		cout<<"Sequence is empty !!\n";
		return;
	}
	cout<<"{";
	for(int i = 0; i < used-1; i++)
		cout<<items[i]<<";";
	cout<<items[used-1]<<"}\n";
}

node *bitree::insertnode(node *binode, node *tree)
{
	if(tree == 0)
		return binode;
	if(binode->item < tree->item)
		tree->left = insertnode(binode, tree->left);
	else if(binode->item > tree->item)
		tree->right = insertnode(binode, tree->right);
	else delete binode;
	return tree;
}

bool bitree::insert(int val)
{
	node *binode = new node;
	bool ok = false;
	if(binode != 0)
	{
		binode->item = val;
		binode->left = binode->right=0;
		root = insertnode(binode, root);
		ok = true;
	}
	return ok;
}

void bitree::printnode(node *binode)
{
	if(binode != 0)
	{
		printnode(binode->left);
		cout<<binode->item<<" ";
		printnode(binode->right);
	}
}

void bitree::print()
{
	printnode(root);
	cout<<"\n";
}

bool Preprintnode(node *binode)
{
	if(binode)
	{
		cout<<binode->item<<" ";
		if(Preprintnode(binode->left))
			if(Preprintnode(binode->right)) return true;
		return false;
	}
	else return true;
}

void bitree::Preprint()
{
	if(root==0) cout<<"Bitree is empty!";
	else Preprintnode(root);
}

node *maketree(sequen *seq, int low, int high)
{
	int mid = (low + high)/2;
	node *binode = new node;
	if(binode != 0)
	{
		binode->item = seq->items[mid];
		binode->left = (mid <= low ? 0: maketree(seq, low, mid-1));
		binode->right = (mid >= high ? 0: maketree(seq, mid+1, high));
	}
	return binode;
}

void bitree::seqtotree(sequen *seq, int low, int high)
{
	if(low == 0 && high == 0)
		high = seq->used;
	root = (low < 0 || high < 0 || low > seq->used || high > seq->used)
		? 0: maketree(seq, low, high);
}

bool makeseq(sequen *seq, node *binode)
{
	if(binode)
	{
		makeseq(seq,binode->left);
		seq->insert(binode->item);
		makeseq(seq,binode->right);
	}
	return true;
}

void bitree::treetoseq(sequen *seq)
{
	seq->used=0;
	makeseq(seq, root);
}

bool bitree::deltree()
{
	if(root == 0) return false;
	else deltreenode(root);
	root=0;
	return true;
}

bool bitree::deltreenode(node *binode)
{
	if(binode)
	{
		if(deltreenode(binode->left))
			if(deltreenode(binode->right))
			{
				delete binode;
				return true;
			}
		return false;
	}else return true;
}