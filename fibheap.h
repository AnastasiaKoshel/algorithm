#pragma once
struct node
{
	int n;
	int degree;
	node* parent;
	node* child;
	node* left;
	node* right;
	char mark;
	char C;
};
/*
* Class Declaration
*/
class FibHeap
{
private:
	int nH;
	node *H;
public:
	node* InitializeHeap();
	void Fibonnaci_link(node*, node*, node*);
	node *Create_node(int);
	node *Insert(node *, node *);
	node *Union(node *, node *);
	node *Extract_Min(node *);
	void Consolidate(node *);
	void Display(node *);
	node *Find(node *, int);
	int Decrease_key(node *, int, int);
	int Delete_key(node *, int);
	void Cut(node *, node *, node *);
	void Cascade_cut(node *, node *);
	FibHeap()
	{
		H = InitializeHeap();
	}
};