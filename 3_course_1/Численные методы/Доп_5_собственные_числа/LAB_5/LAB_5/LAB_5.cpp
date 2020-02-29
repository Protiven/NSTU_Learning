
#include <string> 
#include <fstream>
#include <locale>
#include <iostream>
#include <iomanip>



using namespace std;

#define N 10

typedef double T;

int n, max_iter;
T eps = 1e-14, max, min;
T* x1, *x;
T** A;

void Hylbert_m(const int size)
{
   A = new T* [size];
   for (int i = 0; i < size; i++)
      A[i] = new T[size];

   for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++)
         A[i][j] = 1. / T(i + j + 1);

   ofstream fout("hylb.txt");
   for (int i = 0; i < size; i++)
   {
      for (int j = 0; j < size; j++)
         fout << setprecision(15) << A[i][j] << " ";
      fout << endl;
   }


}

void input()
{
   ifstream fcin("matrix_info.txt");
   A = new T* [n];
   x = new T[n];
   x1 = new T[n];
   fcin >> n >> max_iter;
   for (int i = 0; i < n; i++)
   {
      A[i] = new T[n];
      for (int j = 0; j < n; j++)
         fcin >> A[i][j];
   }
   fcin.close();
}


void output()
{
   ofstream fout("result.txt");
   fout << setprecision(15) << "MAX_VALUE: " << to_string(max) << endl<< "MIN_VALUE: "<< to_string(min);
   fout.close();
}


T norm_vec(T* vec)
{
   T sum = 0;
   for (int i = 0; i < n; i++)
      sum += vec[i] * vec[i];
   return sqrt(sum);
}


void LU_dec()
{
   for (int i = 0; i < n; i++)
   {
      for (int j = i; j < n; j++)
      {
         T sum = 0;
         for (int k = 0; k < i; k++)
            sum += A[j][k] * A[k][i];
         A[j][i] -= sum;
      }
    
      for (int j = i + 1; j < n; j++)
      {
         T sum = 0;
         for (int k = 0; k < i; k++)
            sum += A[i][k] * A[k][j];
         A[i][j] = (A[i][j] - sum) / A[i][i];
      }
   }
}

void solve_LU(T* res)
{
   for (int i = 0; i < n; i++)
   {
      T sum = 0;
      for (int j = 0; j < i; j++)
         sum += A[i][j] * res[j];
      res[i] = (x[i] - sum) / A[i][i];
   }
   for (int i = n - 1; i >= 0; i--)
   {
      T sum = 0;
      for (int j = i + 1; j < n; j++)
         sum += A[i][j] * res[j];
      res[i] -= sum;
   }
}


void MAX_eingenvalue()
{
   int iter;
   T norm_1, norm_2, supp_val;
   T lambda_1, lambda = 0;
   bool end = false;

   for (int i = 0; i < n; i++)
      x[i] = i;
   
   
   norm_1 = norm_vec(x);

   for (iter = 0; iter < max_iter && !end; iter++)
   {
      for (int i = 0; i < n; i++)
      {
         x1[i] = 0;

         for (int j = 0; j < n; j++)
            x1[i] += A[i][j] * x[j];
      }
      norm_2 = norm_vec(x1);
      lambda_1 = norm_2 / norm_1;

      supp_val = fabs((lambda_1 - lambda) / lambda_1);

      if (supp_val < eps)
         end = true;

      for (int i = 0; i < n; i++)
         x[i] = x1[i];
      lambda = lambda_1;
      norm_1 = norm_2;

      if (iter % 5 == 0)
      {
         for (int i = 0; i < n; i++)
            x[i] /= norm_1;
         norm_1 = 1;
      }
   }

   cout << "iter_max = " << to_string(iter) << endl;
   max = lambda;
}


void MIN_eingenvalue()
{
   int iter;
   T norm_1, norm_2, supp_val;
   T lambda_1, lambda = 0;
   bool end = false;

   for (int i = 0; i < n; i++)
      x[i] = i;

   norm_1 = norm_vec(x);

   LU_dec();

   for (iter = 0; iter < max_iter && !end; iter++)
   {
      solve_LU(x1);
      norm_2 = norm_vec(x1);
      lambda_1 = norm_2 / norm_1;

      supp_val = fabs((lambda_1 - lambda) / lambda_1);

      if (supp_val < eps)
         end = true;

      x = x1;
      lambda = lambda_1;
      norm_1 = norm_2;


      if (iter % 5 == 0)
      {
         for (int i = 0; i < n; i++)
            x[i] /= norm_1;
         norm_1 = 1;
      }
   }
   cout << "iter_min = " << to_string(iter);
   min = 1. / lambda;
}

void main()
{
   int choice;
   setlocale(LC_ALL, "rus");
   cout << "Сгенерировать матрицу Гильберта? n - размерность матрицы, * <= 0 - нет.\n";
   cin >> choice;
   if (choice > 0)
      Hylbert_m(choice);
   input();
   MAX_eingenvalue();
   MIN_eingenvalue();
   output();

}

