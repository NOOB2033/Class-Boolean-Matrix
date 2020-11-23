#include"BoolVector.h"
#include"Enum.h"


BoolVector::BoolVector()
{
	len_ = 0;
	bv_ = new unsigned char[mem_ = 1];
	bv_[0] = 0;
}


BoolVector::BoolVector(int len, bool valueForAllDigits)
{
	if (len < 0)
		throw Invalid_size;
	len_ = len;
	bv_ = new unsigned char[mem_ = (len + BYTE - 1) / BYTE];
	if (valueForAllDigits) {
		for (int i = 0; i < mem_; i++)
			bv_[i] = 255; // 11111111
		if (len_ % BYTE) {
			unsigned char mask = 128; // 10000000
			for (int i = 0; i < BYTE - len_ % BYTE; i++) // ��������� ������ ��� � ������� �����
				bv_[0] &= ~mask >> i;
		}
	}
	else
		for (int i = 0; i < mem_; i++)
			bv_[i] = 0;
}


BoolVector::BoolVector(const char* str)
{
	len_ = strlen(str);
	bv_ = new unsigned char[mem_ = (len_ + BYTE - 1) / BYTE];
	for (int i = 0; i < mem_; i++)
		bv_[i] = 0;
	for (int i = 0; i < len_; i++)
		if (str[i] == '1')
			set1(i);
}


BoolVector::BoolVector(const BoolVector& copyBV)
{
	bv_ = new unsigned char[mem_ = copyBV.mem_];
	len_ = copyBV.len_;
	for (int i = 0; i < mem_; i++)
		bv_[i] = copyBV.bv_[i];
}


BoolVector::~BoolVector()
{
	delete[] bv_;
}


std::istream& operator>>(std::istream& in, const BoolVector& bv)
{
	unsigned char c;
	int i = 0;
	for (i; i < bv.len_ % bv.BYTE; i++) { // ��� �������� �����, ���� �� �� ������(������������ �� ��� 8 ���)
		in >> c;
		if (c != '0' && c != '1')
			c = '0';
		bv.bv_[0] <<= 1;
		bv.bv_[0] |= c - '0';
	}
	if (i != 0) // ���� ��������� i, �� �� ���������� ������� ���� => ���� � ���������
		i = 1;
	for (i; i < bv.mem_; i++)
		for (int j = 0; j < bv.BYTE; j++) {
			in >> c;
			if (c != '0' && c != '1')
				c = '0';
			bv.bv_[i] <<= 1;
			bv.bv_[i] |= c - '0';
		}
	return in;
}


std::ostream& operator<<(std::ostream& out, const BoolVector& bv)
{
	unsigned char mask;
	for (int i = 0; i < bv.mem_; i++) {
		mask = 128; // 10000000
		for (int j = 0; j < bv.BYTE; j++, mask >>= 1)
			if (bv.bv_[i] & mask)
				std::cout << 1;
			else
				std::cout << 0;
		std::cout << " ";
	}
	return out;
}


void BoolVector::set0(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte == 0) // �������� ��� �������� �����, ���� �� �� ������
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	else
		mask >>= (index - len_ % BYTE) % BYTE;
	bv_[byte] &= ~mask;
}


void BoolVector::set1(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte == 0)
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	else
		mask >>= (index - len_ % BYTE) % BYTE;
	bv_[byte] |= mask;
}


void BoolVector::fullSet0()
{
	for (int i = 0; i < mem_; i++)
		bv_[i] = 0;
}


void BoolVector::fullSet1()
{
	unsigned char mask = 128; // 10000000
	mask >>= BYTE - abs(len_ - (mem_ - 1) * BYTE);
	int i = 0;
	for (i; i < len_ % BYTE; i++)
		bv_[0] |= mask >> i;
	if (i != 0)
		i = 1;
	for (i; i < mem_; i++)
		bv_[i] = 255; // 11111111
}


void BoolVector::set0(int index, int value)
{
	if (index < 0 || index >= len_ || value < 0 || value >= len_)
		throw Invalid_index;
	if (index > value)
		index ^= value ^= index ^= value;
	if (index != value) {
		unsigned char mask;
		for (int i = index; i <= value; i++) {
			mask = 128; // 10000000
			int byte = mem_ - 1 - (len_ - i - 1) / BYTE;
			if (byte == 0)
				mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + i;
			else
				mask >>= (i - len_ % BYTE) % BYTE;
			bv_[byte] &= ~mask;
		}
	}
	else
		componentInversion(index);
}


void BoolVector::set1(int index, int value)
{
	if (index < 0 || index >= len_ || value < 0 || value >= len_)
		throw Invalid_index;
	if (index > value)
		index ^= value ^= index ^= value;
	if (index != value) {
		unsigned char mask;
		for (int i = index; i <= value; i++) {
			mask = 128; // 10000000
			int byte = mem_ - 1 - (len_ - i - 1) / BYTE;
			if (byte == 0)
				mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + i;
			else
				mask >>= (i - len_ % BYTE) % BYTE;
			bv_[byte] |= mask;
		}
	}
	else
		componentInversion(index);
}


void BoolVector::fullInversion()
{
	unsigned char mask;
	int i = 0;
	for (i; i < len_ % BYTE; i++) {
		mask = 128; // 10000000
		mask >>= BYTE - len_ % BYTE + i;
		bv_[0] ^= mask;
	}
	if (i != 0)
		i = 1;
	for (i; i < mem_; i++) {
		mask = 128; // 10000000
		for (int j = 0; j < BYTE; j++, mask >>= 1)
			bv_[i] ^= mask;
	}
}


void BoolVector::componentInversion(int index)
{
	if (index < 0 || index >= len_)
		throw Invalid_index;
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte == 0)
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	else
		mask >>= (index - len_ % BYTE) % BYTE;
	bv_[byte] ^= mask;
}


int BoolVector::weight()
{
	int weight = 0, i = 0;
	unsigned char mask;
	for (i; i < len_ % BYTE; i++) {
		mask = 128; // 10000000
		mask >>= BYTE - len_ % BYTE + i;
		if (bv_[0] & mask)
			weight++;
	}
	if (i != 0)
		i = 1;
	for (i; i < mem_; i++) {
		mask = 128; // 10000000
		for (int j = 0; j < BYTE; j++, mask >>= 1)
			if (bv_[i] & mask)
				weight++;
	}
	return weight;
}


BoolVector BoolVector::operator~()
{
	fullInversion();
	return *this;
}


BoolVector BoolVector::operator=(const BoolVector& bv)
{
	if (this != &bv) {
		delete[] bv_;
		bv_ = new unsigned char[mem_ = bv.mem_];
		len_ = bv.len_;
		for (int i = 0; i < mem_; i++)
			bv_[i] = bv.bv_[i];
	}
	return *this;
}


BoolVector BoolVector::operator>>=(int value)
{
	if (value <= 0)
		return *this;
	if (value >= len_)
		for (int i = 0; i < mem_; i++)
			bv_[i] = 0;
	unsigned char mask = 128; // 10000000
	for (int i = 0; i < value; i++) {
		for (int j = mem_ - 1; j > 0; j--) {
			bv_[j] >>= 1;
			if (bv_[j - 1] & 1)
				bv_[j] |= mask;
		}
		bv_[0] >>= 1;
	}
	return *this;
}


BoolVector BoolVector::operator>>(int value)
{
	return BoolVector(*this) >>= value;
}


BoolVector BoolVector::operator<<=(int value)
{

	if (value <= 0)
		return *this;
	if (value >= len_)
		for (int i = 0; i < mem_; i++)
			bv_[i] = 0;
	unsigned char mask = 128; //10000000
	for (int i = 0; i < value; i++) {
		for (int j = 0; j < mem_ - 1; j++) {
			bv_[j] <<= 1;
			if (bv_[j + 1] & mask)
				bv_[j] |= 1;
		}
		bv_[mem_ - 1] <<= 1;
	}
	if (len_ % BYTE)
		for (int i = 0; i < BYTE - len_ % BYTE; i++) // ��������� ������ ��� � ������� �����
			bv_[0] &= ~mask >> i;
	return *this;
}


BoolVector BoolVector::operator<<(int value)
{
	return BoolVector(*this) <<= value;
}


BoolVector BoolVector::operator|=(const BoolVector& other)
{
	int min = mem_;
	if (mem_ > other.mem_)
		min = other.mem_;
	for (int i = 0; i < min; i++)
		bv_[mem_ - i - 1] |= other.bv_[other.mem_ - i - 1];
	return *this;
}


BoolVector BoolVector::operator|(const BoolVector& other)
{
	return BoolVector(*this) |= other;
}


BoolVector BoolVector::operator&=(const BoolVector& other)
{
	int min = mem_;
	if (mem_ > other.mem_)
		min = other.mem_;
	for (int i = 0; i < min; i++)
		bv_[mem_ - i - 1] &= other.bv_[other.mem_ - i - 1];
	return *this;
}


BoolVector BoolVector::operator&(const BoolVector& other)
{
	return BoolVector(*this) &= other;
}


BoolVector BoolVector::operator^=(const BoolVector& other)
{
	int min = mem_;
	if (mem_ > other.mem_)
		min = other.mem_;
	for (int i = 0; i < min; i++)
		bv_[mem_ - i - 1] ^= other.bv_[other.mem_ - i - 1];
	return *this;
}


BoolVector BoolVector::operator^(const BoolVector& other)
{
	return BoolVector(*this) ^= other;
}


BoolVectorComponent BoolVector::operator[](int index)
{
	unsigned char mask = 128; // 10000000
	int byte = mem_ - 1 - (len_ - index - 1) / BYTE;
	if (byte == 0)
		mask >>= BYTE - (len_ - (mem_ - 1) * BYTE) + index;
	else
		mask >>= (index - len_ % BYTE) % BYTE;
	return BoolVectorComponent(this, index, (bv_[byte] & mask));
}