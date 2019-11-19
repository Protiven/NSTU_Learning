// LAB_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

extern "C" void FUNC(char* str1, char* res, int length, int position);

void main()
{
   char* str1;
   str1 = new char[200];
   char* res;
   res = new char[200];
   int length, position;
   printf("Enter the string: ");
   scanf("%s", str1);
   printf("Enter the length and the position of string: \n");
   scanf("%d %d", &length, &position);
   if (position >= 1 && length > 0)
   {
      FUNC(str1, res, length, position);
      printf("%s", res);
   }
   else
      printf("Error!");
}
