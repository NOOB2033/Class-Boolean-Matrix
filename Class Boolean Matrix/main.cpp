#include<iostream>
#include"Enum.h"
#include"BoolMatrix.h"
#include"BoolVector.h"


void sortMatrix(BoolMatrix bm, int* mass, int size)
{

}


int main()
{
	setlocale(LC_ALL, "Russian");
	BoolVector bv(8, 0);
	bv.set1(2, 8);
	std::cout << bv;
	/*int size;
	std::cin >> size;
	BoolMatrix bm(size, size, 0);
	int* mass = new int[size];
	for (int i = 0; i < size; i++)
		mass[i] = i;
	sortMatrix(bm, mass, size);*/
	try
	{
	}
	catch (Mistakes mistake)
	{
		switch (mistake)
		{
		case Invalid_size:
			std::cout << "�������� ������";
			exit(0);
		case Invalid_index:
			std::cout << "�������� ������";
			exit(1);
		case Invalid_column:
			std::cout << "�������� �������";
			exit(2);
		case Invalid_line:
			std::cout << "�������� ������";
			exit(3);
		case Invalid_value:
			std::cout << "�������� ��������";
			exit(4);
		default:
			std::cout << "���-�� ����� �� ���";
			exit(-1);
		}
	}
	return 0;
}