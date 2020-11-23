#include<iostream>


#include"Enum.h"
#include"BoolVector.h"


int main()
{
	BoolVector bv1(10, 0);
	bv1[1] = 1;
	std::cout << bv1[1];
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
		default:
			std::cout << "Что-то пошло не так";
			exit(-1);
		}
	}
	return 0;
}