
#include <iostream>
#include <fstream>
#include "locale.h"
#include <vector>

using namespace std;

// Здесь меняется точность
typedef double type_data;

int n_size; // размерность матрицы
int m_size; // полуширина


template <typename T>
void init_f(char* output)
{
	ofstream fout;
	char* in_au = new char[10]{ "au.txt" };
	char* in_di = new char[10]{ "di.txt" };
	char* in_al = new char[10]{ "al.txt" };


	// Ориентироваться в матрице никак (x, y), а как запись индексации в обычных матрицах
	vector< vector<T> > Up_m(n_size, vector<T>(m_size));
	vector< vector<T> > L_m(n_size, vector<T>(m_size));
	vector<T> di(n_size);
	
	// Генерация Гильбертовой матрицы
	for (int i = 0; i < n_size; i++)
		di[i] = T(1) / T(2 * (i + 1) - 1);

	for (int i = 0; i < n_size; i++)
		for (int j = 0; j < m_size; j++)
			L_m[i][j] = 0;

	for (int i = 0; i < n_size; i++)
		for (int j = 0; j < m_size; j++)
			Up_m[i][j] = 0;

	// Запись
	fout.open(in_di);
	for (int i = 0; i < n_size; i++)
		fout << di[i] << endl;		
	fout.close();
	delete(in_di);

	fout.open(in_au);
	for (int i = 0; i < n_size; i++)
	{
		for (int j = 0; j < m_size; j++)
			fout << Up_m[i][j] << "\t";
		fout << endl;
	}
	fout.close();
	delete(in_au);

	fout.open(in_al);
	for (int i = 0; i < n_size; i++)
	{
		for (int j = 0; j < m_size; j++)
			fout << L_m[i][j] << "\t";
		fout << endl;
	}
	fout.close();
	delete(in_al);
	//
}

int main()
{
	setlocale(LC_ALL, "rus");
	char* info_addr = new char[10]{ "info.txt" }; // Запись в виде: размерность матрицы, ширина ленты 
	char* output = new char[10]{ "out.txt" };

	ifstream fout_1(info_addr);
	fout_1 >> n_size >> m_size;
	fout_1.close();

	init_f<type_data>(output);
}

