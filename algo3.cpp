// algo3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
struct node {
	node *left;
	node *right;
	node *parent;
	int data;
};
node *root=NULL;


void left_rotate(node *p);
void right_rotate(node *p);
void splay(node *t);
void insert(int key);
void print(node *p);
node* find(int key);
bool erase(int key);
int main()
{
	cout << "Write the number of elements" << endl;
		int n, cur,key;
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cur = 1 + rand() % 100;
			cout << cur << " ";
			insert(cur);
		}
		cout <<endl<<"Write key " << endl;
		cin >> key;
			if (!find(key))
				cout << "There is no such element" << endl;
			else
				cout << "Ok" << endl;
		cout << "Write element that should be erased"<<endl;
		cin >> key;
			if (erase(key))
				cout << "Ok" << endl;
			else
				cout << "There is no such element" << endl;
		print(root);
	system("pause");
	return 0;
}
void left_rotate(node *p)
{
	node *q = p->right;
	if (q) {
		p->right = q->left;
		if (q->left) q->left->parent = p;
		q->parent = p->parent;
	}

	if (!p->parent) root = q;
	else if (p == p->parent->left) p->parent->left = q;
	else p->parent->right = q;
	if (q) q->left = p;
	p->parent = q;
}

void right_rotate(node *p) {
	node *q = p->left;
	if (q) {
		p->left = q->right;
		if (q->right) q->right->parent = p;
		q->parent = p->parent;
	}
	if (!p->parent) root = q;
	else if (p == p->parent->left) p->parent->left = q;
	else p->parent->right = q;
	if (q) q->right = p;
	p->parent = q;
}
void splay(node *t)//zigzig если путь идет только по правым/только по левым детям, zigzag иначе
{
	while (true)
	{
		node *p = t->parent;
		if (!p) break;
		node *q = p->parent;
		if (!q)
		{
			if (p->left == t)
				right_rotate(p);
			else
				left_rotate(p);
			break;
		}
		if (q->left == p)
		{
			if (p->left == t)//zigzig
			{
				right_rotate(q);
				right_rotate(p);
			}
			else//zigzag
			{
				left_rotate(p);
				right_rotate(q);
			}
		}
		else
		{
			if (p->left == t)//zigzag
			{
				right_rotate(p);
				left_rotate(q);
			}
			else//zigzig
			{
				left_rotate(q);
				left_rotate(p);
			}
		}
	}
	root = t;
}
void insert(int key)//вставка ключа
{
	if (!root)
	{
		root = new node; 
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		root->data = key;
		return;
	}
	node *p = root;
	while (true)
	{
		if (p->data == key) break;
		if (key < (p->data))
		{
			if (p->left) p = p->left;
			else
			{
				p->left = new node;
				p->left->parent = p;
				p->left->right = NULL;
				p->left->left = NULL;
				p->left->data = key;
				p = p->left;
			}
		}
		else
		{
			if (p->right) p = p->right;
			else
			{
				p->right = new node;
				p->right->parent = p;
				p->right->right = NULL;
				p->right->left = NULL;
				p->right->data = key;
				p = p->right;
			}
		}
	}
	splay(p);
}
void print(node *p)//вывод дерева
{
	if (!p) return;
	print(p->left);
	cout <<"data "<< p->data << " ";
	if (p->left) cout << " left " << p->left->data << " ";
	if (p->right) cout << " right " << p->right->data << " ";
	cout << endl;
	print(p->right);
}
node* find(int key)//поиск ключа
{
	if (!root) return NULL;
	node *p = root;
	while (p)
	{
		if (p->data == key) break;
		if (key < (p->data))
			if (p->left)
				p = p->left;
			else break;
		else
			if (p->right)
				p = p->right;
			else break;
	}
	splay(p);
	if (p->data == key) return p;
	else return NULL;
}
bool erase(int key)//удаление ключа
{
	node *q = find(key);
	if (!q) return false;
	splay(q); 
	node *p = q->left;
	if (!p)
	{
		root = q->right;
		root->parent = NULL;
		free(q);
		return true;
	}
	while (p->right) p = p->right;
	if (q->right)
	{
		p->right = q->right;
		q->right->parent = p;
	}
	root = q->left;
	root->parent = NULL;
	free(q);
	return true;
}

