#include "matrix.h"

namespace matrix
{
	//Генерация портрета матрицы
	void Matrix::CreatePortret(int slaeSize, Grid grid)
	{
		vector <int> elList, unzeroNumbersList;
		vector<vector <int>> list;
		list.reserve(slaeSize);
		for (int i = 0; i < slaeSize; i++)
		{
			//нашли,в каких элементах присутствует данная i-я степень свободы
			grid.SearchElements(i, elList);
			//собрать список узлов этих элементов, меньших по номеру
			for (unsigned int j = 0; j < elList.size(); j++)
			{
				for (int k = 0; k < 4; k++)
				{
					//если такого номера ещё нет и он меньше по номеру,то добавляем
					if (find(unzeroNumbersList.begin(), unzeroNumbersList.end(), grid.elements[elList[j]].dof[k])
						== unzeroNumbersList.end() && grid.elements[elList[j]].dof[k] < i)
						unzeroNumbersList.push_back(grid.elements[elList[j]].dof[k]);
				}
			}
			sort(unzeroNumbersList.begin(), unzeroNumbersList.end());
			list.push_back(unzeroNumbersList);
			unzeroNumbersList.clear();
			elList.clear();
		}
		//вычисляем размерность ggl,ggu
		int gg_size = 0;
		for (int i = 0; i < slaeSize; i++)
		{
			if (!list[i].empty())
				gg_size += list[i].size();
		}
		//инициализируем матрицу и собираем портрет
		Initialize(slaeSize, gg_size);
		ig[0] = 0;
		for (int i = 0; i < n; i++)
		{
			if (!list[i].empty())
				ig[i + 1] = ig[i] + list[i].size();
			else
				ig[i + 1] = ig[i];
		}
		int k = 0;
		for (int i = 0; i < n; i++)
		{
			if (!list[i].empty())
			{
				for (unsigned int j = 0; j < list[i].size(); j++)
				{
					jg[k] = list[i][j];
					k++;
				}
				list[i].clear();
			}
		}
		list.clear();
	}

	//Инициализация матрицы после генерации портрета
	void Matrix::Initialize(int size1, int size2)
	{
		n = size1; N_array = size2;
		ggl.resize(N_array);
		ggu.resize(N_array);
		di.resize(n);
		ig.resize(n + 1);
		jg.resize(N_array);
	}
}
