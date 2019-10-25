// Lab_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


#include <iostream>
#include <fstream>
#include "locale.h"
#include <vector>
#include <stdlib.h>
#include <ctime>

using namespace std;

int n_size; // размерность матрицы
int m_size; // полуширина
int k = 0;

void init_f()
{
   ofstream fout;
   char* in_au = new char[10]{ "au.txt" };
   char* in_di = new char[10]{ "di.txt" };
   char* in_al = new char[10]{ "al.txt" };
   char* in_vector = new char[15]{ "b_vector.txt" };


   // Объявление и выделение памяти векторов и матрицы 
   vector<int> vec_b(n_size);
   vector<int> vec_x_star(n_size);

   for (int i = 0; i < n_size; i++)
      vec_x_star[i] = i + 1;

   //
   // Ориентироваться в матрице никак (x, y), а как запись индексации в обычных матрицах
   vector< vector<int> > Up_m(n_size, vector<int>(m_size));
   vector< vector<int> > L_m(n_size, vector<int>(m_size));
   vector<float> di(n_size);
   //   
   int sup = 1;
   srand(time(NULL));
   // Генерация матрицы обусловленности (Работоспособность: Норм)
   for (int i = 1; i < n_size; i++)
   {
      for (int j = 0; j < sup; j++)
      {
         L_m[i][j] = -1 * rand() % 5;
         Up_m[i][j] = -1 * rand() % 5;
      }
      if (sup < m_size)
         sup++;
   }

   // (Работоспособность: Норм)
   for (int j = 0; j < m_size; j++)
      di[0] += - Up_m[1 + j][j];
   di[0] += pow(10, -k);

   sup = 1;
   for (int i = 1; i < n_size; i++)
   {
      for (int j = 0; i + 1 + j < n_size && j < m_size; j++)
         di[i] += - Up_m[i + 1 + j][j];
      for (int j = 0; j < sup; j++)
         di[i] += - L_m[i][j];
      if (sup < m_size)
         sup++;
   }

   // Генерация правой части обусловленности (Работоспособность: ???)

   sup = 0;
   int sup1 = 1;
   for (int i = 0; i < n_size; i++)
   {
      vec_b[i] += di[i] * vec_x_star[i];

      for (int j = 0; i + 1 + j < n_size && j < m_size; j++)
         vec_b[i] += Up_m[i + 1 + j][j] * vec_x_star[i + j + 1];

      for (int j = 0; j < sup && i - sup1 > -1; j++)
      {
         vec_b[i] += L_m[i][j] * vec_x_star[i - sup1];
         sup1++;
      }

      sup1 = 1;

      if (sup < m_size)
         sup++;
   }


   fout.open(in_di);
   for (int i = 0; i < n_size; i++)
      fout << di[i] << endl;
   fout.close();
   delete(in_di);

   fout.open(in_vector);
   for (int i = 0; i < n_size; i++)
      fout << vec_b[i] << endl;
   fout.close();
   delete(in_vector);

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
}

int main()
{
   setlocale(LC_ALL, "rus");
   char* info_addr = new char[10]{ "info.txt" }; // Запись в виде: размерность матрицы, ширина ленты 

   ifstream fcin(info_addr);

   fcin >> n_size >> m_size;
   fcin.close();

   // Изменение точности и не только 
   init_f();
}

