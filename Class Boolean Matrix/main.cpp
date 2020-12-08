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
			std::cout << "Неверный размер";
			exit(0);
		case Invalid_index:
			std::cout << "Неверный индекс";
			exit(1);
		case Invalid_column:
			std::cout << "Неверный столбец";
			exit(2);
		case Invalid_line:
			std::cout << "Неверная строка";
			exit(3);
		case Invalid_value:
			std::cout << "Неверное значение";
			exit(4);
		default:
			std::cout << "Что-то пошло не так";
			exit(-1);
		}
	}
	return 0;
}