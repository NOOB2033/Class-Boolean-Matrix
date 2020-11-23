#pragma once
#include<iostream>


#include"BoolVectorComponent.h"


class BoolVector
{
private:
	int len_, mem_;
	unsigned char* bv_;
	const int BYTE = 8;
public:
	BoolVector();
	BoolVector(int, bool);
	BoolVector(const char*);
	BoolVector(const BoolVector&);
	~BoolVector();
	friend std::istream& operator>>(std::istream&, const BoolVector&);
	friend std::ostream& operator<<(std::ostream&, const BoolVector&);
	void set0(int);
	void set1(int);
	void fullSet0();
	void fullSet1();
	void set0(int index, int value);
	void set1(int index, int value);
	void fullInversion();
	void componentInversion(int);
	int weight();
	BoolVector operator~();
	BoolVector operator=(const BoolVector&);
	BoolVector operator>>=(int);
	BoolVector operator>>(int);
	BoolVector operator<<=(int);
	BoolVector operator<<(int);
	BoolVector operator|=(const BoolVector&);
	BoolVector operator|(const BoolVector&);
	BoolVector operator&=(const BoolVector&);
	BoolVector operator&(const BoolVector&);
	BoolVector operator^=(const BoolVector&);
	BoolVector operator^(const BoolVector&);
	BoolVectorComponent operator[](int);
};