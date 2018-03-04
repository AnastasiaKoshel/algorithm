#pragma once
#ifndef BH_h
#define BH_h

struct node
{
	int data;
	int degree;
	struct node *child;
	struct node *sibling;
	struct node *parent;
};

class binheap
{
private:
	
	node *merge(node *root1, node *root2);
	node *fix(node *root);
	void join(node *root1, node *root2);
public:
	node *head;
	binheap()
	{
		head = NULL;
	}
	node *createnode(int  key);
	void insert(node *root);
	void display(node *h);
	int printmin();
	int printheadnode();
	node *extractmin();
	void getmin(node *&minimum);
	bool found(node *root, int key);
	bool search(node *root, int key, node *&temp);
};


#endif