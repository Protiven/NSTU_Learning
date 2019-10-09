/*
Программа для перевода целых чисел из одной системы счисления в другую
*/

#include "stdio.h"
#include "locale.h"
#include "string.h"
#include "math.h"

int to_10(char* str, int osnovanie, int counts_symbs) 
{
	int string_1[20];
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
	int ost_array[20], i = 0;
	do
	{
		ost_array[i] = chislo % osnovanie;
		chislo = chislo / osnovanie;
		i++;
	} while (chislo != 0);



	int supp_size = i - 1;
	char support[20];

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
	do
	{
		printf_s("%c", support[supp_size]);
		supp_size--;
	} while (supp_size != -1);
	printf_s("\n");
}

void translation(char* str, int sch1, int sch2, int counts_symb)
{
	int ch = 0;
	ch = to_10(str, sch1, counts_symb);
	if (sch2 != 10)
	{
		from_10_to(ch, sch2);
		printf_s("Обратный перевод: %d\n", ch); //
	}
	else
		printf_s("%d\n", ch);
}

bool check_func(char* str, int size, int sch)  
{
	int r = size-1;
	if (sch < 10 && r!=0)
		do
		{
			if (!(str[r] >= '0' && str[r] < sch + '0'))
				return false;
			r--;
		} while (r != 0);
	if (sch >= 10 && r!=0)
		do
		{
			if (!((str[r] >= '0' && str[r] <= '9') || (str[r] >= 'a' && str[r] < 'a' + sch) || (str[r] >= 'A' && str[r] < 'A' + sch)))
				return false;
			r--;
		} while (r != 0);
	if(r==0)
		if (!((str[r] >= '0' && str[r] <= '9') || (str[r] >= 'a' && str[r] < 'a' + sch) || (str[r] >= 'A' && str[r] < 'A' + sch)))
			return false;

	return true;
}

bool check_sch(int s)
{
	return s >= 2 && s <= 16 ? true : false;
}

int main()
{
	setlocale(LC_ALL, "rus");
	printf_s("Программа перевода из десятичной системы счисления в r-инчную и обратно.\n");
	for (;;)
	{
		int counts_symbs;
		int sch2, sch1 = 10;


//		printf_s("Исходная система счисления: ");
//		scanf_s("%d", &sch1);
		printf_s("Перевод в систему счисления: ");
		scanf_s("%d", &sch2);
		printf_s("Введите число (не более 20 символов): ");
		getchar();
		
		char str[20];
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

		if (str != '\0')
			counts_symbs = strlen(str);

		if (check_func(str, counts_symbs, sch1)/* && check_sch(sch1)*/ && check_sch(sch2))
		{
			translation(str, sch1, sch2, counts_symbs);
		}
		else
		{
			printf_s("Некорректный ввод! Повторите попытку!");
			break;
		}
	}

}

