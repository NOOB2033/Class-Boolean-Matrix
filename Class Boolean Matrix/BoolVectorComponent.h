#pragma once
#include<iostream>


#include"BoolVector.h"


class BoolVectorComponent
{
private:
	BoolVector* bv_;
	int index_, value_;
	bool flag_ = false; // Для очистки памяти
public:
	BoolVectorComponent(BoolVector*, int, int);
	BoolVectorComponent(const BoolVectorComponent&);
	~BoolVectorComponent();
	friend std::ostream& operator<<(std::ostream&, const BoolVectorComponent&);
	BoolVectorComponent operator=(int);
	BoolVectorComponent operator=(const BoolVectorComponent&);
	BoolVectorComponent operator|=(int);
	BoolVectorComponent operator|(int);
	BoolVectorComponent operator&=(int);
	BoolVectorComponent operator&(int);
	BoolVectorComponent operator^=(int);
	BoolVectorComponent operator^(int);
	BoolVectorComponent operator|=(const BoolVectorComponent&);
	BoolVectorComponent operator|(const BoolVectorComponent&);
	BoolVectorComponent operator&=(const BoolVectorComponent&);
	BoolVectorComponent operator&(const BoolVectorComponent&);
	BoolVectorComponent operator^=(const BoolVectorComponent&);
	BoolVectorComponent operator^(const BoolVectorComponent&);
	BoolVectorComponent operator~();
};