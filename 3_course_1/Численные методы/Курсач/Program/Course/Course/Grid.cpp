#include "grid.h"

namespace grid
{
	void Area::Input(FILE* out)
	{
		fscanf_s(out, "%d", &leftX);
		fscanf_s(out, "%d", &rightX);
		fscanf_s(out, "%d", &lowY);
		fscanf_s(out, "%d", &upY);

		fscanf_s(out, "%d", &ku[0]);
		fscanf_s(out, "%d", &ku[1]);
		fscanf_s(out, "%d", &ku[2]);
		fscanf_s(out, "%d", &ku[3]);

		fscanf_s(out, "%d", &kuF[0]);
		fscanf_s(out, "%d", &kuF[1]);
		fscanf_s(out, "%d", &kuF[2]);
		fscanf_s(out, "%d", &kuF[3]);
	}

	LinesOfAreas::LinesOfAreas()
	{
		int n;
		double tmp;
		FILE* out;
		fopen_s(&out, "AreasLines.txt", "r");
		fscanf_s(out, "%d", &n);
		x.reserve(n);
		for (int i = 0; i < n; i++)
		{
			fscanf_s(out, "%lf", &tmp);
			x.push_back(tmp);
		}
		fscanf_s(out, "%d", &n);
		y.reserve(n);
		for (int j = 0; j < n; j++)
		{
			fscanf_s(out, "%lf", &tmp);
			y.push_back(tmp);
		}
		fclose(out);
	}

	//����� ����������� ������ �.�. dofsNumber � ��������
	bool K_El::SearchDof(int dofsNumber)
	{
		for (int i = 0; i < 4; i++)
			if (dofsNumber == dof[i]) return true;
		return false;
	}

	Grid::Grid()
	{
		int n;
		FILE* fo;
		fopen_s(&fo, "Areas.txt", "r");
		fscanf_s(fo, "%d", &n);
		areas.resize(n);
		for (int i = 0; i < n; i++)
			areas[i].Input(fo);
		fclose(fo);
	}

	//��������� ���������� � ������ ��������� �� ���� ����������
	void Grid::Partition�oordinate(vector <double>& x, vector <double> areasLines, vector <int> nIntervals)
	{
		int count;
		//����� ���������
		double l;
		//���
		double h;
		//����� ����������
		int nLines = areasLines.size();
		count = 0;
		for (int i = 0; i < nLines - 1; i++)
		{
			x.push_back(areasLines[i]);
			count++;
			//����� ���������
			l = abs(areasLines[i + 1] - areasLines[i]);
			//������������ ������ ���
			//�����������
			h = l / nIntervals[i];
			//�������� ����� ������ ���������
			for (int j = 1; j < nIntervals[i]; j++)
			{
				x.push_back(x[count - 1] + h);
				count++;
			}
		}
		x.push_back(areasLines[nLines - 1]);
	}

	//���������� ����
	void Grid::PushNode(double x, double y)
	{
		Point p;
		p.y = y;
		p.x = x;
		//����� ���� � ����� ������� �����
		nodes.push_back(p);
	}

	//���������� �����
	void Grid::BuildGrid()
	{
		//��� i��� ��������� � ������ ����������
		//����� �������������
		vector <int> xIntervals;
		vector <int> yIntervals;

		//���������� ������������ ����� �� x � y
		int xLines = areasLines.x.size();
		int yLines = areasLines.y.size();

		//�������������� ����� ��������� �� � � y
		vector <double> xi;
		vector <double> yj;

		//��������� ���������� ��� ����������
		int tmp1;

		//����� ����� � ����� ���������
		int nNodes, nElements;

		xIntervals.reserve(xLines - 1);
		yIntervals.reserve(yLines - 1);

		FILE* out;
		fopen_s(&out, "Intervals.txt", "r");
		//���� ���������� ���������� �� � � � � ������������� ��������
		for (int i = 0; i < xLines - 1; i++)
		{
			fscanf_s(out, "%d", &tmp1);
			xIntervals.push_back(tmp1);
		}

		for (int j = 0; j < yLines - 1; j++)
		{
			fscanf_s(out, "%d", &tmp1);
			yIntervals.push_back(tmp1);
		}
		fclose(out);
		nx = 0;
		for (int i = 0; i < xLines - 1; i++)
			//����� ���������� ���������� �� �
			nx += xIntervals[i];
		nx++;

		ny = 0;
		for (int j = 0; j < yLines - 1; j++)
			//����� ���������� ���������� �� �
			ny += yIntervals[j];
		ny++;

		xi.reserve(nx); yj.reserve(ny);

		//���������� ����� �� � � �
		Partition�oordinate(xi, areasLines.x, xIntervals);
		Partition�oordinate(yj, areasLines.y, yIntervals);

		xIntervals.clear();
		yIntervals.clear();

		nElements = (nx - 1) * (ny - 1);
		nNodes = xi.size() * yj.size();

		elements.reserve(nElements);
		nodes.reserve(nNodes);

		//��������� ������ �����
		for (int j = 0; j < yj.size(); j++)
			for (int i = 0; i < xi.size(); i++)
				PushNode(xi[i], yj[j]);
	}

	//��������� ����������� ������
	int Grid::GetGlobalNumber(int elementNumber, int localNumber)
	{
		//����� ���������� �� x
		int nxint = nx - 1;
		//����� �������������� �����, ������� �������� ������ ������ ��������
		int nGorLine = elementNumber / nxint;
		//��������� ����� ���� �� �����
		int nodeOnLine = nGorLine * (nxint + 1);
		//������ �� ���������� ����, ����� �������� ������� �����
		//������ ������� ���� ��������;
		int offsetX = elementNumber % nxint;
		//����� ������� ������ ����
		int nodeElem = nodeOnLine + offsetX;

		if (localNumber == 0)
			return nodeElem;
		if (localNumber == 1)
			return nodeElem + 1;
		if (localNumber == 2)
			return nodeElem + (nxint + 1);
		if (localNumber == 3)
			return nodeElem + (nxint + 1) + 1;
		return -1;
	}

	//���������� ������ �������, � ������� ����� �������� �����
	int Grid::FindArea(double x, double y)
	{
		bool xInterval, yInterval;
		int size = areas.size();
		for (int i = 0; i < size; i++)
		{
			xInterval = x > areasLines.x[areas[i].leftX] && x < areasLines.x[areas[i].rightX];
			yInterval = y > areasLines.y[areas[i].lowY] && y < areasLines.y[areas[i].upY];

			//���� ����� �������� � i�� �������, ���������� ����� ���� �������
			if (xInterval && yInterval) return i;
			else return -1;
		}
	}

	//���������� �������� �������� ���������
	void Grid::FindNeighbors(int elementNumber)
	{
		int count = 0;
		//���������� �������� ���������
		int nElements = elements.size();
		K_El element;
		element = elements[elementNumber];
		bool tmp[4] = { false, false, false, false };

		for (int i = 0; count < 4 && i < nElements; i++)
		{
			if (i == elementNumber) i++;
			else
			{
				//����� �� ������ �����
				if (nodes[element.nodes[0]] == nodes[elements[i].nodes[1]] && nodes[element.nodes[2]] == nodes[elements[i].nodes[3]])
				{
					element.neighbors[0] = i;
					tmp[0] = true;
					count++;
				}
				//����� �� ������� �����
				if (nodes[element.nodes[1]] == nodes[elements[i].nodes[0]] && nodes[element.nodes[3]] == nodes[elements[i].nodes[2]])
				{
					element.neighbors[1] = i;
					tmp[1] = true;
					count++;
				}
				//����� �� ������� �����
				if (nodes[element.nodes[0]] == nodes[elements[i].nodes[2]] && nodes[element.nodes[1]] == nodes[elements[i].nodes[3]])
				{
					element.neighbors[2] = i;
					tmp[2] = true;
					count++;
				}
				//����� �� �������� �����
				if (nodes[element.nodes[2]] == nodes[elements[i].nodes[0]] && nodes[element.nodes[3]] == nodes[elements[i].nodes[1]])
				{
					element.neighbors[3] = i;
					tmp[3] = true;
					count++;
				}
			}
		}
		for (int i = 0; i < 4; i++)
			//���������� ������ �� ��������������� �������
			if (tmp[i] == false) element.neighbors[i] = -1;
		elements[elementNumber] = element;
	}

	//���������� �������� ���������
	void Grid::ComputeElements()
	{
		K_El tmpEl;
		double x, y;
		//��������� ���������� ������ ����� � �������� �������
		//������� �� � ��������� ������ ��
		for (int i = 0; i < elements.capacity(); i++)
		{
			for (int j = 0; j < 4; j++)
			{
				tmpEl.nodes[j] = GetGlobalNumber(i, j);
				tmpEl.dof[j] = tmpEl.nodes[j];
			}
			elements.push_back(tmpEl);
		}
		//������� ����� ���������� ��� ������� ��
		for (int i = 0; i < elements.size(); i++)
		{
			//���� ����������� ����
			x = (nodes[elements[i].nodes[0]].x + nodes[elements[i].nodes[1]].x) / 2;
			y = (nodes[elements[i].nodes[0]].y + nodes[elements[i].nodes[2]].y) / 2;

			if (FindArea(x, y) == -1)
				printf("WAT");
			else
				elements[i].numberOfArea = FindArea(x, y);
		}
		//������� �������� ��
		for (int i = 0; i < elements.size(); i++)
			FindNeighbors(i);
	}

	//������������ �������� ������� �������
	void Grid::FormKU()
	{
		int size = elements.size();
		BoundaryCondition tmp;
		//��� ������� �������� �������,����� �� �� ��� ��������
		for (int i = 0; i < size; i++)
		{
			bool left[3] = { false, false, false }, right[3] = { false, false, false },
				low[3] = { false, false, false }, up[3] = { false, false, false };
			if (elements[i].neighbors[0] == -1)
			{
				if (areas[elements[i].numberOfArea].ku[0] == 1) left[0] = true;
				else
					if (areas[elements[i].numberOfArea].ku[0] == 2) left[1] = true;
					else
						if (areas[elements[i].numberOfArea].ku[0] == 3) left[2] = true;
			}
			if (elements[i].neighbors[1] == -1)
			{
				if (areas[elements[i].numberOfArea].ku[1] == 1) right[0] = true;
				else
					if (areas[elements[i].numberOfArea].ku[1] == 2) right[1] = true;
					else
						if (areas[elements[i].numberOfArea].ku[1] == 3) right[2] = true;
			}
			if (elements[i].neighbors[2] == -1)
			{
				if (areas[elements[i].numberOfArea].ku[2] == 1) low[0] = true;
				else
					if (areas[elements[i].numberOfArea].ku[2] == 2) low[1] = true;
					else
						if (areas[elements[i].numberOfArea].ku[2] == 3) low[2] = true;
			}
			if (elements[i].neighbors[3] == -1)
			{
				if (areas[elements[i].numberOfArea].ku[3] == 1) up[0] = true;
				else
					if (areas[elements[i].numberOfArea].ku[3] == 2) up[1] = true;
					else
						if (areas[elements[i].numberOfArea].ku[3] == 3) up[2] = true;
			}

			for (int j = 0; j < 3; j++)
				if (left[j] || right[j] || low[j] || up[j])
				{
					tmp.elem = i;
					if (left[j])
					{
						tmp.edges[0] = 1;
						tmp.formNumber[0] = areas[elements[i].numberOfArea].kuF[0];
					}
					else
					{
						tmp.edges[0] = 0;
						tmp.formNumber[0] = -1;
					}
					if (right[j])
					{
						tmp.edges[1] = 1;
						tmp.formNumber[1] = areas[elements[i].numberOfArea].kuF[1];
					}
					else
					{
						tmp.edges[1] = 0;
						tmp.formNumber[1] = -1;
					}
					if (low[j])
					{
						tmp.edges[2] = 1;
						tmp.formNumber[2] = areas[elements[i].numberOfArea].kuF[2];
					}
					else
					{
						tmp.edges[2] = 0;
						tmp.formNumber[2] = -1;
					}
					if (up[j])
					{
						tmp.edges[3] = 1;
						tmp.formNumber[3] = areas[elements[i].numberOfArea].kuF[3];
					}
					else
					{
						tmp.edges[3] = 0;
						tmp.formNumber[3] = -1;
					}

					ku[j].push_back(tmp);
				}
		}
	}

	//����������� ��������� ��
	void Grid::DoPart()
	{
		//���������� �����
		BuildGrid();
		//���������� �������� ���������
		ComputeElements();
		//������������ �������� ������� �������
		FormKU();
	}

	//������������ ������ ���������, ���������� ���������� ����� �.�.
	//������ dofsNumber
	void Grid::SearchElements(int dofsNumber, vector <int>& elList)
	{
		int count;
		int size = elements.size();
		elList.reserve(4);
		count = 0;
		for (int i = 0; i < size && count < 4; i++)
		{
			if (elements[i].SearchDof(dofsNumber))
			{
				count++;
				elList.push_back(i);
			}
		}
	}
}
