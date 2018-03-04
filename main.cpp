// BinHeap.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "BinHeap.h"
#include <iostream>
using namespace std;

int main()
{
	binheap bh;
	node *root=NULL;
	int n,x;
			cout << endl << "Write the number of elements"<<endl;
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				x = 1 + rand() % 100;
				cout << x << " ";
				root = bh.createnode(x);
				bh.insert(root);
			}
        cout << "Min =" << endl;
			x = bh.printmin();
			if (x == INT_MAX)
				cout << "None" << endl;
			else cout << endl << x << endl;
		
			cout << "HeadNode" << endl;
			x = bh.printheadnode();
			if (x == INT_MAX)
				cout << "Empty" << endl;
			else cout << endl << x << endl;
			cout << "Heap" << endl;
			bh.display(bh.head);
			cout << endl << "Write key to be deleted\t";
			cin >> x;
			if (!bh.found(bh.head, x))
				cout << endl << "Not found" << endl;
			else
				bh.extractmin();
			cout << "Heap" << endl;
			bh.display(bh.head);
			cout << "Extract min" << endl;
			bh.extractmin();
			cout << "Heap" << endl;
			bh.display(bh.head);
			cout << endl << "Enter key to be decreased\t";
			cin >> x;
			if (!bh.search(bh.head, x, root))
				cout << endl << "Not found" << endl;
			else
			{
				cout << "Enter data to replaced\t";
				cin >> x;
				cout << endl;
				root->data = x;
				while (root->parent && root->data<root->parent->data)
				{
					x = root->data;
					root->data = root->parent->data;
					root->parent->data = x;
					root = root->parent;
				}
				while (root->child && root->child->data<root->data)
				{
					x = root->data;
					root->data = root->child->data;
					root->child->data = x;
					root = root->child;
				}
			}
			
			
			system("pause");
    return 0;
}

