#include "stdafx.h"
#include "BinHeap.h"
#include <iostream>
using namespace std;

   node * binheap::createnode(int  key)
	{
		node *root;
		root = new node;
		root->child = root->sibling = root->parent = NULL;
		root->degree = 0;
		root->data = key;
		return root;
	}

	void binheap:: insert(node *root)
	{
		head = merge(head, root);
		head = fix(head);
	}

	void binheap::display(node *h)
	{
		if (h == NULL)
		{
			//cout << "The Heap is empty" << endl;
			return;
		}
		//cout << "The root nodes are: " << endl;
		node* p;
		p = h;
		while (p)
		{
			//cout << "root ";
			cout << p->data << " ";
			display(p->child);
			p = p->sibling;
			cout << endl;
		}
	}
	int binheap:: printmin()
	{
		int min;
		node *temp;
		temp = head;
		if (!head)
			return INT_MAX;
		min = head->data;
		head = head->sibling;
		while (head)
		{
			if (head->data<min)
				min = head->data;
			head = head->sibling;
		}
		head = temp;
		return min;
	}

	int binheap:: printheadnode()
	{
		node *temp;
		temp = head;
		if (!head)
			return INT_MAX;
		head = temp;
		return head->data;
	}

	node * binheap::merge(node *root1, node *root2)
	{
		node *head1;
		node *temp;
		if (!root1)
			return root2;
		if (!root2)
			return root1;
		if (root1->degree <= root2->degree)
		{
			head1 = root1;
			root1 = root1->sibling;
		}
		else
		{
			head1 = root2;
			root2 = root2->sibling;
		}
		temp = head1;
		while (root1 && root2)
		{
			if (root1->degree <= root2->degree)
			{
				temp->sibling = root1;
				root1 = root1->sibling;
			}
			else
			{
				temp->sibling = root2;
				root2 = root2->sibling;
			}
			temp = temp->sibling;
		}
		if (root1)
			temp->sibling = root1;
		else temp->sibling = root2;
		return head1;
	}

	node * binheap::fix(node *root)
	{
		node *temp;
		node *prev;
		node *current;
		node *next;
		node *head1=NULL;
		prev = NULL;
		current = root;
		next = current->sibling;
		if (!root->sibling)
			return root;
		while (next)
		{
			if (current->degree != next->degree)
			{
				if (!prev)
					head1 = current;
				prev = current;
				current = next;
				next = next->sibling;
			}
			else
			{
				if (next->sibling && next->sibling->degree == current->degree)
				{
					if (!prev)
						head1 = current;
					prev = current;
					current = next;
					next = next->sibling;
				}
				else
				{
					if (current->data>next->data)
					{
						if (prev)
							prev->sibling = next;
						current->sibling = NULL;
						join(next, current);
						current = next;
						next = next->sibling;
					}
					else
					{
						current->sibling = next->sibling;
						next->sibling = NULL;
						join(current, next);
						next = current->sibling;
					}
				}
			}
		}
		if (!prev)
			head1 = current;
		return head1;
	}

	void binheap:: join(node *root1, node *root2)
	{
		root1->degree++;
		root2->parent = root1;
		if (!root1->child)
		{
			root1->child = root2;
			return;
		}
		root1 = root1->child;
		while (root1->sibling)
			root1 = root1->sibling;
		root1->sibling = root2;
	}

	node * binheap::extractmin()
	{
		node *temp;
		node *x;
		if (!head)
			return NULL;
		getmin(temp);
		if (temp == head)
		{
			head = head->sibling;
			if (!head && temp->degree == 0)
				return temp;
		}
		else
		{
			x = head;
			while (x->sibling != temp)
				x = x->sibling;
			x->sibling = x->sibling->sibling;
		}
		temp->sibling = NULL;
		x = temp->child;
		while (x)
		{
			x->parent = NULL;
			x = x->sibling;
		}
		x = temp->child;
		temp->child = NULL;
		head = merge(head, x);
		head = fix(head);
		temp->degree = 0;
		return temp;
	}

	void binheap::getmin(node *&minimum)
	{
		int min;
		node *temp;
		temp = head;
		min = head->data;
		minimum = head;
		head = head->sibling;
		while (head)
		{
			if (head->data<min)
			{
				min = head->data;
				minimum = head;
			}
			head = head->sibling;
		}
		head = temp;
	}

	bool binheap:: found(node *root, int key)
	{
		if (!root)
			return false;
		while (root)
		{
			if (root->data == key)
			{
				root->data = INT_MIN;
				while (root->parent)
				{
					root->data = root->parent->data;
					root->parent->data = INT_MIN;
					root = root->parent;
				}
				return true;
			}
			else if (root->data<key)
				if (found(root->child, key))
					return true;
			root = root->sibling;
		}
		return false;
	}

	bool binheap:: search(node *root, int key, node *&temp)
	{
		if (!root)
			return false;
		while (root)
		{
			if (root->data == key)
			{
				temp = root;
				root->data = INT_MIN;
				while (root->parent)
				{
					root->data = root->parent->data;
					root->parent->data = INT_MIN;
					root = root->parent;
				}
				return true;
			}
			else if (root->data<key)
				if (found(root->child, key))
					return true;
			root = root->sibling;
		}
		return false;
	}
