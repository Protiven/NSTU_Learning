// Lab_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "locale.h"
#include <vector>

using namespace std;

// Здесь меняется точность
typedef double type_data;

int n_size; // размерность матрицы
int m_size; // полуширина

bool check(int i, int j)
{
	int sup1 = 1, sup2 = 0;
	while (sup2 < m_size || sup1 < n_size)
	{
		if (i == sup1 && j == sup2)
			return false;
		sup2++;
		sup1++;
	}
	return true;
}

int index_di(int i, int j)
{
	int key = 0;
	int sup1 = 1, sup2 = 0;
	int str1 = 1, str2 = 0;
	for (;;)
	{
		if (sup2 >= m_size || sup1 >= n_size)
			break;
		while (sup2 < m_size || sup1 < n_size)
		{
			if (i == sup1 && j == sup2)
				return key;
			sup1++;
			sup2++;
		}
		key++;
		sup1 = str1 + key;
		sup2 = str2;
	}
}

void read_func(vector<type_data> &vec_b, vector< vector<type_data> > &Up_m, vector< vector<type_data> > &L_m, vector<type_data> &di)
{
   // Чтение
   ifstream fcin;
   char* vector_addr = new char[15]{ "b_vector.txt" };
   char* in_au = new char[10]{ "au.txt" };
   char* in_di = new char[10]{ "di.txt" };
   char* in_al = new char[10]{ "al.txt" };

   fcin.open(vector_addr);
   for (int i = 0; i < n_size; i++)
      fcin >> vec_b[i];
   fcin.close();
   delete(vector_addr);

   fcin.open(in_di);
   for (int i = 0; i < n_size; i++)
      fcin >> di[i];
   fcin.close();
   delete(in_di);


   fcin.open(in_au);
   for (int i = 0; i < n_size; i++)
      for (int j = 0; j < m_size; j++)
         fcin >> Up_m[i][j];
   fcin.close();
   delete(in_au);

   fcin.open(in_al);
   for (int i = 0; i < n_size; i++)
      for (int j = 0; j < m_size; j++)
         fcin >> L_m[i][j];
   fcin.close();
   delete(in_al);
   //

}



void init_f(char* output)
{
	// Объявление и выделение памяти векторов и матрицы 
	vector<type_data> vec_b(n_size);
	vector<type_data> vec_y(n_size);
	vector<type_data> vec_x(n_size);

	//
	// Ориентироваться в матрице никак (x, y), а как запись индексации в обычных матрицах
	vector< vector<type_data> > Up_m(n_size, vector<type_data>(m_size));
	vector< vector<type_data> > L_m(n_size, vector<type_data>(m_size));
	vector<type_data> di(n_size);
	//   

   read_func(vec_b, Up_m, L_m, di);

	// LU - разложение
	int add_j = 1, support = 0;
	int j = 0, l = 0;

	for (int i = 0; i < n_size; i++)
	{

		for (j = m_size - 1; j >= 0; j--)
		{
			if (check(i, j))
			{
				for (int k = j + 1; k < m_size && i != j && i > j; k++)
				{

					L_m[i][j] = (L_m[i][j] - L_m[i][k] * Up_m[i - j - 1][k - 1 - j]);
					Up_m[i][j] = Up_m[i][j] - Up_m[i][k] * L_m[i - j - 1][k - 1 - j];
				}

			}
			if (i != j && i > j)
				L_m[i][j] = L_m[i][j] / di[index_di(i, j)];

		}

		for (int k = 0; k < m_size; k++)
		{
			di[i] = di[i] - L_m[i][k] * Up_m[i][k];
		}
	}

	// Разложение закончено




	// Решение y (L*y=b) "Прямой ход" (Делается правильно)
	for (int i = 0; i < n_size; i++)
		vec_y[i] = vec_b[i];

	support = 0;
	int k = 0;

	for (int i = 1; i < n_size; i++) // Так как первый вектор уже найден
	{
		for (int j = i - 1; j >= 0 && k < m_size; j--)
		{
			vec_y[i] = vec_y[i] - L_m[i][k] * vec_y[j];
			k++;
		}
		k = 0;
	}

	/*
	vec_y[1] = vec_y[1] - L_m[1][0] * vec_y[0];

	vec_y[2] = vec_y[2] - L_m[2][1] * vec_y[0] - L_m[2][0] * vec_y[1];
	
	vec_y[3] = vec_y[3] - L_m[3][2] * vec_y[0] - L_m[3][1] * vec_y[1] - L_m[3][0] * vec_y[2];
	
	vec_y[4] = vec_y[4] - L_m[4][2] * vec_y[1] - L_m[4][1] * vec_y[2] - L_m[4][0] * vec_y[3];
	*/

	// Решение x (U*x=y) "Обратный ход"

	for (int i = 0; i < n_size; i++)
		vec_x[i] = vec_y[i];
	vec_x[n_size - 1] /= di[n_size - 1];
	
	support = 0;

	for (int i = n_size - 2; i >= 0; i--)
	{
		support = 0;
		for (int j = i + 1; j < n_size && support < m_size; j++)
		{
			vec_x[i] = vec_x[i] - Up_m[j][support] * vec_x[j];
			support++;
		}
		vec_x[i] /= di[i];
	}

	for (int i = 0; i < n_size; i++)
		std::cout << vec_x[i] << endl;


	/*
	vec_x[n-2] = vec_x[n-2] - Up_m[n-1][0] * vec_x[n-1];
	vec_x[n-3] = vec_x[n-3] - Up_m[n-2][0] * vec_x[n-2] - Up_m[n-1][1] * vec_x[n-1];
	vec_x[n-4] = vec_x[n-4] - Up_m[n-3][0] * vec_x[n-3] - Up_m[n-2][1] * vec_x[n-2] - Up_m[n-1][2] * vec_x[n-1];
	vec_x[n-5] = vec_x[n-5] - Up_m[n-4][0] * vec_x[n-4] - Up_m[n-3][1] * vec_x[n-3] - Up_m[n-2][2] * vec_x[n-2];
	*/

}



int main()
{
	setlocale(LC_ALL, "rus");
	char* info_addr = new char[10]{ "info.txt" }; // Запись в виде: размерность матрицы, ширина ленты 
	char* output = new char[10]{ "out.txt" };

	ifstream fcin_1(info_addr);

	fcin_1 >> n_size >> m_size;
	fcin_1.close();

	// Изменение точности и не только 
	init_f(output);
}

