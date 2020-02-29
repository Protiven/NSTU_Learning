// Lab_1_up.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "stdio.h"
#include "locale.h"
#include "math.h"
#include <stdlib.h>

#define buff 30 

using namespace std;

int to_10(char* str, int osnovanie, int counts_symbs)
{
	int string_1[buff];
	int result;
	int i = 0;
	int f = 0;

	do
	{
	   if (str[i] >= '0' && str[i] <= '9')
			string_1[i] = str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'F')
			string_1[i] = str[i] - 'A' + 10;
		else if (str[i] >= 'a' && str[i] <= 'f')
			string_1[i] = str[i] - 'a' + 10;
        i++;
	} while (i != counts_symbs);

	i = 0;
	int k = counts_symbs - 1;
	do
	{
		f = f + string_1[i] * pow(osnovanie, k);
		k--;
	   i++;
	} while (i != counts_symbs);

	return f;
}

void from_10_to(int chislo, int osnovanie)
{
	int ost_array[buff], i = 0;
	do
	{
		ost_array[i] = chislo % osnovanie;
		chislo = chislo / osnovanie;
		i++;
	} while (chislo != 0);



	int supp_size = i - 1;
	char support[buff], * s1 = new char[buff];

	int k = supp_size;

	do
	{
		if (ost_array[k] >= 0 && ost_array[k] <= 9)
			support[k] = ost_array[k] + '0';
		else
			support[k] = ost_array[k] + 'A' - 10;
		k--;
	} while (k != -1);

	printf_s("В r-ичной системе счисления: ");

	int count = 0;
	i = 0;
	do
	{
		s1[i] = support[supp_size];
		i++;
		supp_size--;
	} while (supp_size != -1);

	count = i;
	i = 0;
	do
	{
		printf_s("%c", s1[i]);
		i++;
	} while (i != count);

	printf_s("\nПеревод в обратную сторону: %d\n", to_10(s1, osnovanie, count));
}

bool check_sch(int s)
{
	return s >= 2 && s <= 16 && s != 10 ? true : false;
}

bool check_func(char* str, int size)
{
   if (size >= 10)
      return false;
   else 
   {
   int r = size - 1;
   if (r != 0)
      do
      {
         if (!(str[r] >= '0' && str[r] < 10 + '0'))
            return false;
         r--;
      } while (r != 0);
   else
      if (!(str[r] >= '0' && str[r] < 10 + '0'))
         return false;
   return true;
   }
}

int main()
{
	setlocale(LC_ALL, "rus");
	printf_s("Программа перевода из десятичной системы счисления в r-инчную и обратно.\n");
	for (;;)
	{
		int sch2;

		printf_s("Перевод в систему счисления: ");
		scanf_s("%d", &sch2);
		printf_s("Введите число (не более 9 символов): ");
		getchar();

		int ch;
      char str[buff]; 
      char supp; 
      scanf_s("%c", &supp); 
      int i = 0;
      
      while (supp != '\n') 
      {
         str[i] = supp; 
         i++; 
         scanf_s("%c", &supp);
      }
      
      str[i] = '\0';

      if (check_sch(sch2) && check_func(str, i))
      {
         ch =  atoi(str);
         from_10_to(ch, sch2);
      }
      else
		{
			printf_s("Некорректный ввод! Повторите попытку!");
			break;
		}
	}
}

