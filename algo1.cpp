// algo1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <list>
#include <time.h>
#include <algorithm>

using namespace std;

struct bucket
{
	int a, b, p, size;
	vector <int> v;
};
int main()
{
	srand(time(0));
	vector <bucket> buck;  //финальная таблица хеширования
	vector <list <int>> cur; //текущий вектор списков куда записываем результат после первого этапа хеширования
	vector <int> data; //данные которые хешируем
	int A, B, P, M, S=20;// внешняя функция хеширования
	P = 101;
	A = rand() % P;
	B = 1 + rand() % (P-1);
	M = 9;
	cout << "....First hash function.... " << endl;
	cout << "A=" << A << " B=" << B << " P=" << P << " M=" << M << endl;
	//задаем размер векторов
	cur.resize(M);
	buck.resize(M);
	data.resize(S);
	cout << "......Data....... " << endl;
	for (int i = 0; i < S; i++)// генерируем массив случайных чисел. Убрать повторы???
	{
		data[i] =1+ rand() % 99;
		cout << data[i] << " ";
	}
	int cur_hash;
	for (int i = 0; i < S; i++)//записываем результат первой функции хеширования в списки (первый этап)
	{
		cur_hash = ((A*data[i] + B) % P) % M;
		cur[cur_hash].push_back(data[i]);
	}
	for (int i = 0; i < M; i++)// хешируем каждый список (второй этап)
	{
		//cout << endl;
		if (!cur[i].empty())
		{
			cur[i].sort();
			cur[i].unique();
			//генеируем случайную функцию хеширования
			buck[i].a = rand() % 18;
			buck[i].b= 1+rand() % 17;
			buck[i].p = 19;
			int q = cur[i].size();
			buck[i].size = q*q;
			buck[i].v.resize(buck[i].size);//задаем размер вектора равным количеству лементов списка в квадрате
			for (int j = 0; j < buck[i].size; j++) buck[i].v[j] = 0;// обнуляем вектор
			int key,hash;
			while (!cur[i].empty())// находим хеш каждого элемента списка записывая его на нужное место в вектор
			{
				
				key = cur[i].front();
				
			//cout << key << " ";
				cur[i].pop_front();
					hash = ((buck[i].a*key + buck[i].b) % 17) % buck[i].size;
					buck[i].v[hash] = key;// (одинаковые элементы запишутся в одно место, размер вектора слишком большой)
			}
		}
	}
	//выводим результат
	cout <<endl<< ".....Hash Table......";
	for (int i = 0; i < M; i++)
	{
		cout << endl;
		cout << "a=" << buck[i].a << " b=" << buck[i].b << " size=" << buck[i].size << "|| ";
		for (int j = 0; j < buck[i].size; j++) cout << buck[i].v[j] << " ";
	}
	cout <<endl<< "Write element that you want to find" << endl;
	int f, f_hash1, f_hash2;
	cin >> f;
	f_hash1 = ((A*f + B) % P) % M;
	f_hash2 = ((buck[f_hash1].a*f + buck[f_hash1].b) % buck[f_hash1].p) % buck[f_hash1].size;
	if (buck[f_hash1].v[f_hash2]) cout << "yes" << endl;
	else cout << "no" << endl;
	data.clear();
	cur.clear();
	buck.clear();
	system("pause");
    return 0;
}

