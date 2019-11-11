// Method_gauss.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include "locale.h"
#include <vector>

using namespace std;

// Здесь меняется точность
typedef float type_data;

int n_size; // размерность матрицы

void output_func(vector<type_data> vec_x)
{
   char* address = new char[10]{ "out.txt" };
   ofstream fout;

   fout.open(address);
   for (int i = 0; i < n_size; i++)
      fout << vec_x[i] << endl;
}

void method_gauss(vector< vector<type_data> >& Matr)
{
   vector<type_data> vec_x(n_size);
   double e = 0.0000000000000001;
   int flag = 1;

   for (int k = 0; k < n_size; k++)  
   {
      
      type_data max = abs(Matr[k][k]);
      int imax = k;
      for (int j = k; j < n_size; j++) 
      {
         if (abs(Matr[j][k]) > max)
         {
            max = (abs(Matr[j][k]));
            imax = j;
         }
      }
      if (max < e)
      {
         cout << "Система не имеет решения";
         flag = 0;
      }
      else
         if (imax != k)
         {
            type_data g;
            g = Matr[k][n_size];
            Matr[k][n_size] = Matr[imax][n_size];
            Matr[imax][n_size] = g;

            for (int r = k; r < n_size; r++)
            {
               g = Matr[k][r];
               Matr[k][r] = Matr[imax][r];
               Matr[imax][r] = g;
            }
         }
      
      for (int i = k + 1; i < n_size; i++)
      {
         type_data t = Matr[i][k] / Matr[k][k];
         Matr[i][n_size] -= t * Matr[k][n_size];

         for (int j = k + 1; j < n_size; j++)
         {
            Matr[i][j] -= t * Matr[k][j];
         }
      }
   }
   
   int n_sup = n_size - 1;
   vec_x[n_sup] = Matr[n_sup][n_size] / Matr[n_sup][n_sup];
   for (int k = n_size - 2; k >= 0; k--)
   {
      type_data sum = 0;
      for (int i = k + 1; i < n_size; i++)
         sum += Matr[k][i] * vec_x[i];
      vec_x[k] = (Matr[k][n_size] - sum) / Matr[k][k];
   }

   if (flag)
      output_func(vec_x);
}

void read_func(vector< vector<type_data> >& Matr)
{
   // Чтение
   ifstream fcin;
   char* vector_addr = new char[15]{ "b_vector.txt" };
   char* in_m = new char[15]{ "Matrix.txt" };

   fcin.open(vector_addr);
   for (int i = 0; i < n_size; i++)
      fcin >> Matr[i][n_size];
   fcin.close();
   delete(vector_addr);

   fcin.open(in_m);
   for (int i = 0; i < n_size; i++)
      for (int j = 0; j < n_size; j++)
         fcin >> Matr[i][j];
   fcin.close();
   delete(in_m);
   //

}

int main()
{
   setlocale(LC_ALL, "rus");
   char* info_addr = new char[10]{ "info.txt" }; // Запись в виде: размерность матрицы, ширина ленты 
   ifstream fcin_1(info_addr);

   fcin_1 >> n_size;
   fcin_1.close();
   delete(info_addr);

   vector< vector<type_data> > Matr(n_size, vector<type_data>(n_size + 1));

   read_func(Matr);
   method_gauss(Matr);
}

