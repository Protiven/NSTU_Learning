#include "slae.h"

namespace slae
{
	//Сборка локальных матриц жёсткости
	void SLAE::CalculateG(int elementNumber)
	{
		double hx, hy, hx2, hy2, g1, g2;
		K_El element = grid.elements[elementNumber];

		double x1 = grid.nodes[element.nodes[0]].x, x3 = grid.nodes[element.nodes[1]].x;
		double y1 = grid.nodes[element.nodes[0]].y, y3 = grid.nodes[element.nodes[2]].y;

		hx = x3 - x1;
		hy = y3 - y1;
		hx2 = hx * hx;
		hy2 = hy * hy;

		double jacobian = hx * hy / 4.0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = i; j < 4; j++)
			{
				g1 = 0;
				g2 = 0;

				for (int k = 0; k < 9; k++)
				{
					double ksi = 0.5 + 0.5 * gaussPoints[0][k],
						etta = 0.5 + 0.5 * gaussPoints[1][k];
					double x_ = x1 + ksi * hx,
						y_ = y1 + etta * hy;
					double lambda = tests.Lambda(element.numberOfArea, x_, y_);
					g1 += gaussWeights[k] * dphiksi[i](ksi, etta) * dphiksi[j](ksi, etta) * lambda;
					g2 += gaussWeights[k] * dphietta[i](ksi, etta) * dphietta[j](ksi, etta) * lambda;
				}

				G[i][j] = g1 * jacobian / hx2 + g2 * jacobian / hy2;
			}
		}

		//матрица симметричная, заполняем нижний треугольник
		for (int i = 1; i < 4; i++)
			for (int j = 0; j < i; j++)
				G[i][j] = G[j][i];
	}

	//Сборка локальных матриц масс
	void SLAE::CalculateM(int elementNumber)
	{
		double hx, hy, g;
		K_El element = grid.elements[elementNumber];

		hx = grid.nodes[element.nodes[1]].x - grid.nodes[element.nodes[0]].x;
		hy = grid.nodes[element.nodes[2]].y - grid.nodes[element.nodes[0]].y;

		double jacobian = hx * hy / 4.0;

		for (int i = 0; i < 4; i++)
		{
			for (int j = i; j < 4; j++)
			{
				g = 0;

				for (int k = 0; k < 9; k++)
				{
					double ksi = 0.5 + 0.5 * gaussPoints[0][k],
						etta = 0.5 + 0.5 * gaussPoints[1][k];
					double x_ = grid.nodes[element.nodes[0]].x + ksi * hx,
						y_ = grid.nodes[element.nodes[0]].y + etta * hy;

					double gamma = tests.Gamma(element.numberOfArea, x_, y_);
					g += gaussWeights[k] * gamma * phi[i](ksi, etta) * phi[j](ksi, etta);
				}

				M[i][j] = g * jacobian;
			}
		}

		//матрица симметричная, заполняем нижний треугольник
		for (int i = 1; i < 4; i++)
			for (int j = 0; j < i; j++)
				M[i][j] = M[j][i];
	}

	//Сборка локальных правых частей
	void SLAE::CalculateLocalF(int elementNumber)
	{
		double fi;
		K_El element = grid.elements[elementNumber];
		int numberOfArea = element.numberOfArea;
		double x1 = grid.nodes[element.nodes[0]].x, x3 = grid.nodes[element.nodes[1]].x;
		double y1 = grid.nodes[element.nodes[0]].y, y3 = grid.nodes[element.nodes[2]].y;

		double hx = x3 - x1;
		double hy = y3 - y1;

		double jacobian = hx * hy / 4.0;

		for (int i = 0; i < 4; i++)
		{
			locF[i] = 0;
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 9; k++)
				{
					double ksi = 0.5 + 0.5 * gaussPoints[0][k],
						etta = 0.5 + 0.5 * gaussPoints[1][k];
					double x_ = x1 + ksi * hx,
						y_ = y1 + etta * hy;

					fi = tests.Fi(x_, y_);
					locF[i] += fi * gaussWeights[k] * phi[i](ksi, etta);
				}
			}
			locF[i] *= jacobian;
		}
	}

	//Добавка локального элемента в глобальный
	void SLAE::AddElementToGlobalMatrix(int i, int j, double element)
	{
		int id;
		bool flag;

		if (i == j)
			A.di[i] += element;
		else
		{
			if (i < j)
			{
				flag = false;
				for (id = A.ig[j]; !flag && id < A.ig[j + 1]; id++)
					if (A.jg[id] == i) flag = true;

				if (flag) A.ggu[id - 1] += element;
			}
			else
			{
				flag = false;
				for (id = A.ig[i]; !flag && id < A.ig[i + 1]; id++)
					if (A.jg[id] == j) flag = true;

				if (flag) A.ggl[id - 1] += element;
			}
		}
	}

	//Сборка локальных матриц(векторов) и добавление в глобальные
	void SLAE::CalculateLocals(int elementNumber)
	{
		K_El element = grid.elements[elementNumber];
		int ki, kj;

		CalculateG(elementNumber);
		CalculateM(elementNumber);
		CalculateLocalF(elementNumber);

		for (int i = 0; i < 4; i++)
		{
			ki = element.dof[i];
			for (int j = 0; j < 4; j++)
			{
				kj = element.dof[j];
				AddElementToGlobalMatrix(ki, kj, G[i][j] + M[i][j]);
			}
			F[ki] += locF[i];
		}
	}

	//Нахождение правой части для 1ого краевого условия
	void SLAE::Calculate_g(int formNumber, int orientation, int elNumber)
	{
		K_El element = grid.elements[elNumber];

		switch (orientation)
		{
			//левое ребро
		case 0:
		{
			double x = grid.nodes[element.nodes[0]].x;
			double y1 = grid.nodes[element.nodes[0]].y;
			double y2 = grid.nodes[element.nodes[2]].y;

			g[0] = tests.Ug(formNumber, x, y1);
			g[1] = tests.Ug(formNumber, x, y2);
		}
		break;
		//правое ребро
		case 1:
		{
			double x = grid.nodes[element.nodes[1]].x;
			double y1 = grid.nodes[element.nodes[1]].y;
			double y2 = grid.nodes[element.nodes[3]].y;

			g[0] = tests.Ug(formNumber, x, y1);
			g[1] = tests.Ug(formNumber, x, y2);
		}
		break;
		//нижнее ребро
		case 2:
		{
			double y = grid.nodes[element.nodes[0]].y;
			double x1 = grid.nodes[element.nodes[0]].x;
			double x2 = grid.nodes[element.nodes[1]].x;

			g[0] = tests.Ug(formNumber, x1, y);
			g[1] = tests.Ug(formNumber, x2, y);
		}
		break;
		//верхнее ребро
		case 3:
		{
			double y = grid.nodes[element.nodes[2]].y;
			double x1 = grid.nodes[element.nodes[2]].x;
			double x2 = grid.nodes[element.nodes[3]].x;

			g[0] = tests.Ug(formNumber, x1, y);
			g[1] = tests.Ug(formNumber, x2, y);
		}
		break;
		default:; break;
		}
	}

	//Вычисление 1ого краевого условия для одного узла
	void SLAE::CalculateBoundaries1ForNode(int node, double gi, double weight)
	{
		int id;
		F[node] = gi;
		A.di[node] = weight;

		for (int j = 0; j < n; j++)
			if (node < j)
			{
				bool flag = false;
				for (id = A.ig[j]; !flag && id <= A.ig[j + 1] - 1; id++)
					if (A.jg[id] == node) flag = true;
				if (flag) A.ggu[id - 1] = 0.0;
			}
			else
			{
				bool flag = false;
				for (id = A.ig[node]; !flag && id <= A.ig[node + 1] - 1; id++)
					if (A.jg[id] == j) flag = true;
				if (flag) A.ggl[id - 1] = 0.0;
			}
	}

	//Учёт первого краевого условия
	void SLAE::CalculateBoundaries1(int number)
	{
		K_El element = grid.elements[grid.ku[0][number].elem];

		if (grid.ku[0][number].edges[0] == 1)
		{
			int indexes[2] = { element.dof[0], element.dof[2] };
			Calculate_g(grid.ku[0][number].formNumber[0], 0, grid.ku[0][number].elem);
			for (int i = 0; i < 2; i++)
				CalculateBoundaries1ForNode(indexes[i], g[i], 1);

		}
		if (grid.ku[0][number].edges[1] == 1)
		{
			int indexes[2] = { element.dof[1], element.dof[3] };
			Calculate_g(grid.ku[0][number].formNumber[1], 1, grid.ku[0][number].elem);
			for (int i = 0; i < 2; i++)
				CalculateBoundaries1ForNode(indexes[i], g[i], 1);
		}
		if (grid.ku[0][number].edges[2] == 1)
		{
			int indexes[2] = { element.dof[0], element.dof[1] };
			Calculate_g(grid.ku[0][number].formNumber[2], 2, grid.ku[0][number].elem);
			for (int i = 0; i < 2; i++)
				CalculateBoundaries1ForNode(indexes[i], g[i], 1);
		}
		if (grid.ku[0][number].edges[3] == 1)
		{
			int indexes[2] = { element.dof[2], element.dof[3] };
			Calculate_g(grid.ku[0][number].formNumber[3], 3, grid.ku[0][number].elem);
			for (int i = 0; i < 2; i++)
				CalculateBoundaries1ForNode(indexes[i], g[i], 1);
		}
	}
	//умножение матрицы на вектор
	int SLAE::Multiply(vector <double>& a, vector <double>& res)
	{
		int i, j, k;
		int iend;
		for (i = 0; i < n; i++)
		{
			//kol = ig[i + 1] - ig[i];//количество ненулевых элементов строки (столбца) от первого
			//ненулевого элемента до диагонального элемента (не включая его)
			iend = A.ig[i + 1];
			k = A.ig[i]; // адрес первого занятого элемента строки (столбца) 

			res[i] = A.di[i] * a[i];//от главной диагонали

			for (; k < iend; k++)//проходим по всем элементам i строки (столбца)
			{
				j = A.jg[k];
				res[i] += A.ggl[k] * a[j];//от нижнего треугольника
				res[j] += A.ggu[k] * a[i];//от верхнего треугольника
			}
		}return 0;
	}

	//скалярное произведение
	double SLAE::Scalyar(vector <double>& a, vector <double>& b)
	{
		double Res = 0.0;
		int o = a.size();
		for (int i = 0; i < o; i++)
			Res += a[i] * b[i];
		return Res;
	}

	void SLAE::LU()
	{
		int i, i0, j0, iend, num, ki, kj;
		double suml, sumu, sumdg;
		L.resize(A.ggl.size());
		U.resize(A.ggu.size());
		Di.resize(A.di.size());
		for (i = 0; i < A.N_array; i++)
		{
			U[i] = A.ggu[i];
			L[i] = A.ggl[i];
			if (i < n)
				Di[i] = A.di[i];
		}
		for (i = 0; i < n; i++)
		{
			i0 = A.ig[i];
			iend = A.ig[i + 1];
			for (num = i0, sumdg = 0; num < iend; num++)
			{
				j0 = A.ig[A.jg[num]]; //в зависимости от номера фиксируем столбец,какой столбец l,такого столбца  ищем начальный эл у u 
				int jend = A.ig[A.jg[num] + 1];
				ki = i0; kj = j0;
				for (suml = 0, sumu = 0, ki = i0; ki < num; ki++) //для num учитываются все предыдущие элементы
					for (int m = kj; m < jend; m++)
						if (A.jg[ki] == A.jg[m]) //ищем соответствующие ненулевые элементы для умножения
						{
							suml += L[ki] * U[m];
							sumu += L[m] * U[ki];//для симметричного элемента из U
						}
				L[num] -= suml;
				U[num] = (U[num] - sumu) / Di[A.jg[num]];
				sumdg += L[num] * U[num];//умножаются симметричные элементы	
			}
			Di[i] -= sumdg;
		}
	}

	void SLAE::LYF(const vector <double>& C, vector <double>& yl)
	{
		int i, i0, iend; //i0-адрес начала строки, iend-адрес конца строки
		double sum;
		for (i = 0; i < n; i++)
		{
			i0 = A.ig[i]; iend = A.ig[i + 1];

			yl[i] = C[i];

			for (i0, sum = 0; i0 < iend; i0++)
				yl[i] -= yl[A.jg[i0]] * L[i0];
			yl[i] /= Di[i];
		}
	}

	void SLAE::UXY(const vector <double>& C, vector <double>& yu)
	{
		int i, i0, iend;

		for (i = 0; i < n; i++)
			yu[i] = 0.0;

		for (i = n - 1; i >= 0; i--)//проход по столбцам с конца
		{
			yu[i] += C[i];

			i0 = A.ig[i]; iend = A.ig[i + 1]; iend--;

			for (; iend >= i0; iend--)//идём по столбцу с конца
				yu[A.jg[iend]] -= yu[i] * U[iend];
		}
	}

	void SLAE::LULOS(FILE* out)
	{
		double a, b, pp, dis;
		int i;
		vector <double> Ax;
		vector <double> C;
		Ax.resize(n);
		C.resize(n);

		LU();
		Multiply(x, Ax);					//Ax0
		for (i = 0; i < n; i++)				//f-Ax0
			r[i] = F[i] - Ax[i];
		LYF(r, r);							//r0=L^(-1)(f-Ax0)
		UXY(r, z);							//z0=U^(-1)r0->r0=Uz0
											//p0=L^(-1)Az0
		Multiply(z, Ax);					//Az0
		LYF(Ax, p);

		rr = Scalyar(r, r);
		dis = Scalyar(r, r) / rr;
		dis = sqrt(dis);
		k = 0;

		for (k = 1; dis > eps&& k <= maxiter; k++)
		{
			pp = Scalyar(p, p);				//Аk
			a = Scalyar(p, r) / pp;

			for (i = 0; i < n; i++)
			{
				x[i] = x[i] + a * z[i];		//Xk, Rk
				r[i] = r[i] - a * p[i];
			}
			UXY(r, C);						//UY=rk->Y=U^(-1)rk
			Multiply(C, Ax);				//AU^(-1)rk=Ax
			LYF(Ax, Ax);					//L^(-1)AU^(-1)rk=Y2->L^(-1)B=Y2->LY2=B->Y2=L^(-1)AU^(-1)rk
			b = -Scalyar(p, Ax) / pp;		//bk
			for (i = 0; i < n; i++)
			{
				z[i] = C[i] + b * z[i];		//zk=U^(-1)rk+bkz[k-1]				
				p[i] = Ax[i] + b * p[i];	//pk
			}
			dis = Scalyar(r, r) / rr;
			dis = sqrt(dis);
		}
		for (int i = 0; i < n; i++)
			fprintf(out, "%.14lf\n", x[i]);
		fprintf(out, "dis = %E\t", dis);
		fprintf(out, "\nk = %d\t", k);
	}


	SLAE::SLAE()
	{

		grid.DoPartition();//Построение сетки

		n = grid.nx * grid.ny;//Размерность задачи соответствует общему числу базисных функций
		F.resize(n);
		x.resize(n);
		r.resize(n);
		z.resize(n);
		p.resize(n);


		A.CreatePortret(n, grid);//Генерация портрета матрицы и её инициализация


		for (int i = 0; i < grid.elements.size(); i++)//Высчитывание локальных матриц(векторов) и добавление в глобальные
			CalculateLocals(i);


		for (int i = 0; i < grid.ku[0].size(); i++)//Учёт краевых условий
			CalculateBoundaries1(i);

#pragma region 2 и 3 краевые
		/*for (int i = 0; i < grid.ku[1].size(); i++)
			CalculateBoundaries2(i);

		for (int i = 0; i < grid.ku[2].size(); i++)
			CalculateBoundaries3(i);*/
#pragma endregion опять же на потом

		normF = sqrt(Scalyar(F, F));
	}
}

