// Lab_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include "locale.h"
#include <vector>

using namespace std;

// Здесь меняется точность
typedef float type_data;
typedef float scal;

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

void LU_decomposition(vector< vector<type_data> >& Up_m, vector< vector<type_data> >& L_m, vector<type_data>& di)
{
   int add_j = 1, support = 0;
   int j = 0, l = 0;
   scal sup_scal = 0, sup_sc1 = 0, sup_sc2 = 0;

   for (int i = 0; i < n_size; i++)
   {

      for (j = m_size - 1; j >= 0; j--)
      {
         if (check(i, j))
         {
            for (int k = j + 1; k < m_size && i != j && i > j; k++)
            {
               sup_sc1 += L_m[i][k] * Up_m[i - j - 1][k - 1 - j];
               sup_sc2 += Up_m[i][k] * L_m[i - j - 1][k - 1 - j];
            }
            L_m[i][j] = (L_m[i][j] - sup_sc1);
            Up_m[i][j] = Up_m[i][j] - sup_sc2;
            sup_sc1 = 0;
            sup_sc2 = 0;

         }
         if (i != j && i > j)
            L_m[i][j] = L_m[i][j] / di[index_di(i, j)];

      }

      for (int k = 0; k < m_size; k++)
         sup_scal += L_m[i][k] * Up_m[i][k];
      di[i] = di[i] - sup_scal;
      sup_scal = 0;
   }
}

void forward_motion(vector< vector<type_data> > L_m, vector<type_data>& vec_y, vector<type_data> vec_b)
{
   // Решение y (L*y=b) "Прямой ход" 
   scal sup_scal = 0;
   for (int i = 0; i < n_size; i++)
      vec_y[i] = vec_b[i];

   int k = 0;

   for (int i = 1; i < n_size; i++) // Так как первый вектор уже найден
   {
      for (int j = i - 1; j >= 0 && k < m_size; j--)
      {
         sup_scal += L_m[i][k] * vec_y[j];         
         k++;
      }
      vec_y[i] += - sup_scal;
      sup_scal = 0;
      k = 0;
   }
}

void back_motion(vector< vector<type_data> > Up_m, vector<type_data>& vec_x, vector<type_data> vec_y, vector<type_data> di)
{
   // Решение x (U*x=y) "Обратный ход"
   scal sup_scal = 0;
   for (int i = 0; i < n_size; i++)
      vec_x[i] = vec_y[i];
   vec_x[n_size - 1] /= di[n_size - 1];

   int support = 0;

   for (int i = n_size - 2; i >= 0; i--)
   {
      support = 0;
      for (int j = i + 1; j < n_size && support < m_size; j++)
      {
         sup_scal += Up_m[j][support] * vec_x[j];         
         support++;
      }
      vec_x[i] = vec_x[i] - sup_scal;
      sup_scal = 0;
      vec_x[i] /= di[i];
   }

}

void output_func(vector<type_data> vec_x)
{
   char* output = new char[10]{ "out.txt" };
   ofstream fout;
   fout.precision(16);

   fout.open(output);
   for (int i = 0; i < n_size; i++)
      fout << vec_x[i] << endl;
   fout.close();
   delete(output);
}

void init_f()
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
   LU_decomposition(Up_m, L_m, di);
   forward_motion(L_m, vec_y, vec_b);
   back_motion(Up_m, vec_x, vec_y, di);
   output_func(vec_x);
}

int main()
{
	setlocale(LC_ALL, "rus");
	char* info_addr = new char[10]{ "info.txt" }; // Запись в виде: размерность матрицы, ширина ленты 
	ifstream fcin_1(info_addr);

	fcin_1 >> n_size >> m_size;
	fcin_1.close();

	init_f();
}

