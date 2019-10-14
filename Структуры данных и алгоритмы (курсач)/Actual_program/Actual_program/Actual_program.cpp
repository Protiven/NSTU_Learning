
#include <stdio.h>
#include <iostream>

/*
0 - пустая клетка
1 - стена
2 - начало
3 - конечная точка
*/

const int W = 8;  // ширина рабочего поля
const int H = 8;  // высота рабочего поля
const int WALL = -1;   // непроходимая ячейка
const int BLANK = -2;   // свободная непомеченная ячейка

int object_matrix[H][W];
int xs, ys, xf, yf;  // начальные и конечные координаты
// s - start, f - final

int px[W * H], py[W * H]; // координаты ячеек, входящих в путь
int len; // длина пути


int read_objects() 
{
	FILE* in = fopen("in.txt", "r");
	int i, j;
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
			fscanf(in, "%d", &object_matrix[i][j]);
		j = 0;
	}
	fclose(in);
	
	return 1;
}

int correct_matrix()
{
   xf = -3, yf = -3, xs = -3, ys = -3; // присваиваем недопустимые значения 
   for (int i = 0; i < 8; i++)
      for (int j = 0; j < 8; j++)
      {
         if (object_matrix[i][j] == 0)
            object_matrix[i][j] = BLANK;
         else
         {
            if (object_matrix[i][j] == 1)
               object_matrix[i][j] = WALL;
            else
            {
               if (object_matrix[i][j] == 2)
               {
                  xs = i;
                  ys = j;
               }
               else
               {
                  xf = i;
                  yf = j;
               }
               object_matrix[i][j] = -2;
            }
         }
      }
   if (xf == -3 && xs == -3)
   {
      printf_s("Отсутствую данные о начальной и конечной точках.\n");
      return 0;
   }
   else if (xf == -3)
   {
      printf_s("Отсутствую данные о конечной точке.\n");
      return 0;
   }
   else if (xs == -3)
   {
      printf_s("Отсутствую данные о начальной точке.\n");
      return 0;
   }
	return 1;
}

void out_func()
{
	FILE* out = fopen("out.txt", "w");
	
	for (size_t i = 0; i < len + 1; i++)
		fprintf(out, "(%d, %d) ", px[i], py[i]);
}

bool lee_upgrade(int ax, int ay, int bx, int by)  // поиск пути из ячейки (ax, ay) в ячейку (bx, by)
{
	int dx[4] = { 1, 0, -1, 0 };   // смещения, соответствующие соседям ячейки
	int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
	int d, x, y, k;
	bool stop;

	if (object_matrix[ax][ay] == WALL || object_matrix[bx][by] == WALL) return false;  // ячейка (ax, ay) или (bx, by) - стена
   if (ax == bx && ay == by)
   {
      len = 0;
      px[0] = ay;
      py[0] = ax;
      out_func();
      return true;
   }
	// распространение волны
	d = 0;
	object_matrix[ax][ay] = 0; // стартовая ячейка помечена 0
	do
	{
		stop = true;	// предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < H; ++y)	 // Ищем клетку с меткой d
			for (x = 0; x < W; ++x)
				if (object_matrix[x][y] == d)	// ячейка (x, y) помечена числом d
				{
					for (k = 0; k < 4; ++k)  // проходим по всем непомеченным соседям
					{  
						int iy = y + dy[k], ix = x + dx[k];
						while (object_matrix[ix][iy] != WALL && iy >= 0 && iy < H && ix >= 0 && ix < W) // ... Пока не упремся в стену
						{
							if (iy >= 0 && iy < H && ix >= 0 && ix < W && object_matrix[ix][iy] == BLANK && object_matrix[ix][iy] != WALL) // Ищем непомеченные клетки
							{
								stop = false;    // найдены непомеченные клетки
								object_matrix[ix][iy] = d + 1;   // распространяем волну
							}
							iy += dy[k];
							ix += dx[k];
						}
					}
				}
		d++;
	} while (!stop && object_matrix[bx][by] == BLANK);

	if (object_matrix[bx][by] == BLANK) return false;  // путь не найден

	// восстановление пути
	len = object_matrix[bx][by];  // количество ходов кратчайшего пути из (ax, ay) в (bx, by)
	x = bx;
	y = by;
	d = len;


	while (d > 0) // Пока не дойдем до начальной точки
	{
		// записываем ячейку (x, y) в путь
		px[d] = y;
		py[d] = x;
		d--;
		for (k = 0; k < 4 && !stop; ++k) // Проверяем всевозможные направления
		{
			int iy = y, ix = x;
			while (iy >= 0 && iy < H && ix >= 0 && ix < W && object_matrix[ix][iy] > 0) // двигаемся до того момента, пока упремся в стену
			{
				iy = iy + dy[k], ix = ix + dx[k];
				if (ix < 8 && iy < 8 && object_matrix[ix][iy] == d) // если нашли клетку с меньшим ходом на 1
				{
					stop = true;
					x = ix;  // переходим в ячейку, которая на 1 ближе к старту
					y = iy;
					break;
				}
			}

		}
		stop = false;
	}
	// теперь px[0..len] и py[0..len] - координаты ячеек пути
	px[0] = ay;
	py[0] = ax;                    

	out_func();
	return true;
}

int main()
{
	setlocale(LC_ALL, "rus");
	if (read_objects())
	{
		if (correct_matrix())
		{
			if (lee_upgrade(xs, ys, xf, yf))
				printf_s("Решение найдено!\n");                 
			else
				printf_s("Решение не найдено!\n");
		}
		else
			printf_s("Ошибка в данных.\n");
	}
	else
		printf_s("Ошибка при считывании из файла.\n");
	printf_s("Нажмите любую клавишу для выхода из программы.\n");
	getchar();
}