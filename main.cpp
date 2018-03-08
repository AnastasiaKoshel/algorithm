// fibheap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include"fibheap.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
/*
* Node Declaration
*/

/*
* Initialize Heap
*/

/*
* Main Contains Menu
*/
int main()
{
	int n, m, l;
	FibHeap fh;
	node* p;
	node* H;
	H = fh.InitializeHeap();
	cout << "Enter the number of element that you want to insert" << endl;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> m;
		//cout << m << " ";
		p = fh.Create_node(m);
		H = fh.Insert(H, p);
	}
	fh.Display(H);
	p = p = fh.Extract_Min(H);
	cout << "Minimum key node is "<< p->n << endl;
	cout << "Enter the key to be decreased: ";
	cin >> m;
	cout << "Enter new key value: ";
	cin >> l;
	fh.Decrease_key(H, m, l);
	cout << "Enter the key to be deleted: ";
	cin >> m;
	fh.Delete_key(H, m);
	cout << endl;
		
	system("pause");
	return 0;
}