#include<iostream>
#include"Enum.h"
#include"BoolMatrix.h"
#include"BoolVector.h"


int* sortMatrix(BoolMatrix bm, BoolVector bv, int size)
{
	int flag = 0;
	int index = 0;
	int* a = new int[size];
	for (; bv.weight();) {                                         // until the array is empty
		if (flag == size) {
			std::cout << "There is a cycle in the graph" << std::endl;
			for (int i = 0; i < size; i++)
				a[i] = -1;
			return a;
		}
		for (int column = 0; column < size; column++)
			if (bv.getBit(column)) {                             // if the column is not removed from the set
				int count = 0;
				for (int line = 0; line < size & !count; line++) // !count(no 1 in column)
					if (bm[line].getBit(column))
						count++;
				if (!count) {                                    // if column has no 1
					bm.set0(0, size, column);                    // set0 line (column == line)
					for (int i = 0; i < size; i++)               // set0 column
						bm[i].set0(column);
					bv.set0(column);                             // set0 element of the set
					a[index++] = column;
				}
			}
		flag++;
	}
	return a;
}


int main()
{
	try
	{
		int size;
		std::cin >> size;
		BoolMatrix bm(size, size, 0);
		std::cin >> bm;
		BoolVector bv(size, 1);
		int* a = sortMatrix(bm, bv, size);
		for (int i = 0; i < size; i++)
			std::cout << a[i] << " ";
	}
	catch (Mistakes mistake)
	{
		switch (mistake)
		{
		case Invalid_size:
			std::cout << "Invalid_size";
			exit(0);
		case Invalid_index:
			std::cout << "Invalid_index";
			exit(1);
		case Invalid_column:
			std::cout << "Invalid_column";
			exit(2);
		case Invalid_line:
			std::cout << "Invalid_line";
			exit(3);
		case Invalid_value:
			std::cout << "Invalid_value";
			exit(4);
		default:
			std::cout << "Something went wrong";
			exit(-1);
		}
	}
	return 0;
}