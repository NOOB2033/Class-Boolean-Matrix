#pragma once
#include"BoolVector.h"

class BoolMatrix
{
private:
	int line_, column_;
	BoolVector* bm_;
public:
	BoolMatrix();
	BoolMatrix(int, int, bool);
	BoolMatrix(char**, int, int);
	BoolMatrix(const BoolMatrix&);
	~BoolMatrix();
	friend std::istream& operator>>(std::istream&, const BoolMatrix&);
	friend std::ostream& operator<<(std::ostream&, const BoolMatrix&);
	void inversion(int index, int line);
	void inversion(int index, int value, int line);
	void set0(int index, int line);
	void set1(int index, int line);
	void set0(int index, int value, int line);
	void set1(int index, int value, int line);
	int weight();
	int weightLine(int);
	BoolVector fullConjunction();
	BoolVector fullDisjunction();
	BoolMatrix operator~();
	BoolMatrix& operator=(const BoolMatrix&);
	BoolMatrix& operator|=(const BoolMatrix&);
	BoolMatrix operator|(const BoolMatrix&);
	BoolMatrix& operator&=(const BoolMatrix&);
	BoolMatrix operator&(const BoolMatrix&);
	BoolMatrix& operator^=(const BoolMatrix&);
	BoolMatrix operator^(const BoolMatrix&);
	BoolVector& operator[](int);
};