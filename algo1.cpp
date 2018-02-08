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
void first_step(int A, int B, int P, int M, vector <list <int>> &cur, vector <int> &data, int S);
void second_step(vector <list <int>> &cur, int M, vector <bucket> &buck, int P);
void printt(vector <bucket> &buck, int M);
void ssearch(vector <bucket> &buck, int M, int A, int B, int P);
int main()
{
	srand(time(0));
	vector <bucket> buck;  //финальная таблица хеширования
	vector <list <int>> cur; //текущий вектор списков куда записываем результат после первого этапа хеширования
	vector <int> data; //данные которые хешируем
	int A, B, P=101, M=40, S=10;// внешняя функция хеширования
	A = rand() % (P-1)+1;
	B = rand() % P;
	cout << "....First hash function.... " << endl;
	cout << "A=" << A << " B=" << B << " P=" << P << " M=" << M << endl;
	//задаем размер векторов
	cur.resize(M);
	buck.resize(M);
	data.resize(S);
	cout << "......Data....... " << endl;
	for (int i = 0; i < S; i++)// генерируем массив случайных чисел
	{
		data[i] =rand() % 98+1;
		cout << data[i] << " ";
	}	
	first_step(A, B, P, M, cur, data, S);
	second_step(cur, M, buck, P);
	printt(buck, M);
	ssearch(buck, M, A, B, P);
	data.clear();
	cur.clear();
	buck.clear();
	system("pause");
    return 0;
}

void first_step(int A, int B, int P, int M, vector <list <int>> &cur, vector <int> &data, int S)//записываем результат первой функции хеширования в списки (первый этап)
{
	int cur_hash;
	for (int i = 0; i < S; i++)
	{
		cur_hash = abs( ((A*data[i] + B) % P) % M);
		cur[cur_hash].push_back(data[i]);
	}
}
void second_step(vector <list <int>> &cur, int M, vector <bucket> &buck, int P)// хешируем каждый список (второй этап)
{
	for (int i = 0; i < M; i++)
	{
		if (!cur[i].empty())
		{
			cur[i].sort();
			cur[i].unique();
			//генеируем случайную функцию хеширования
			buck[i].a = rand() % (P-1)+1;
			buck[i].b = rand() % P;
			buck[i].p = P;
			int q = cur[i].size();
			buck[i].size = q*q;
			buck[i].v.resize(buck[i].size);//задаем размер вектора равным количеству лементов списка в квадрате
			for (int j = 0; j < buck[i].size; j++) buck[i].v[j] = 0;// обнуляем вектор
			int key, hash;
			while (!cur[i].empty())// находим хеш каждого элемента списка записывая его на нужное место в вектор
			{

				key = cur[i].front();
				cur[i].pop_front();
				hash =abs( ((buck[i].a*key + buck[i].b) % buck[i].p) % buck[i].size);
				//cout << key << " " << hash << endl;
				buck[i].v[hash] = key;// (одинаковые элементы запишутся в одно место, размер вектора слишком большой)
			}
		}
	}
}
void printt(vector <bucket> &buck, int M)
{
	//выводим результат
	cout << endl << ".....Hash Table......";
	for (int i = 0; i < M; i++)
	{
		cout << endl;
		cout << "a=" << buck[i].a << " b=" << buck[i].b << " size=" << buck[i].size << "|| ";
		for (int j = 0; j < buck[i].size; j++) cout << buck[i].v[j] << " ";
	}
}
void ssearch(vector <bucket> &buck, int M, int A, int B, int P)
{
	
	int f=1, f_hash1, f_hash2;
	cout << endl << "Write element that you want to find" << endl;
	cin >> f;
		f_hash1 = ((A*f + B) % P) % M;
		if (buck[f_hash1].size)
		{
			f_hash2 = ((buck[f_hash1].a*f + buck[f_hash1].b) % buck[f_hash1].p) % buck[f_hash1].size;
			if (buck[f_hash1].v[f_hash2] == f) cout << "yes" << endl;
			else cout << "no" << endl;
		}
		else cout << "no" << endl;
		
}