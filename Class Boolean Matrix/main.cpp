#include<iostream>
#include"Enum.h"
#include"BoolMatrix.h"
#include"BoolVector.h"


int main()
{
	setlocale(LC_ALL, "Russian");
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