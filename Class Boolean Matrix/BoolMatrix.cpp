#include "BoolMatrix.h"
#include "Enum.h"


BoolMatrix::BoolMatrix()
{
    bm_ = new BoolVector[line_ = 1];
    bm_[0] = BoolVector(column_ = 1, 0);
}


BoolMatrix::BoolMatrix(int line, int column, bool valueForAllDigits)
{
    if (line < 1 || column < 1)
        throw Invalid_size;
    bm_ = new BoolVector[line_ = line];
    for (int i = 0; i < line_; i++)
        bm_[i] = BoolVector(column_ = column, valueForAllDigits);
}


BoolMatrix::BoolMatrix(char** str, int line, int column)
{
    if (line < 1 || column < 1)
        throw Invalid_size;
    column_ = column;
    bm_ = new BoolVector[line_ = line];
    for (int i = 0; i < line_; i++)
        bm_[i] = BoolVector(str[i]);
}


BoolMatrix::BoolMatrix(const BoolMatrix& copyBM)
{
    bm_ = new BoolVector[line_ = copyBM.line_];
    column_ = copyBM.column_;
    for (int i = 0; i < line_; i++)
        bm_[i] = BoolVector(copyBM.bm_[i]);
}


BoolMatrix::~BoolMatrix()
{
    delete[] bm_;
}


std::istream& operator>>(std::istream& in, const BoolMatrix& bm)
{
    for (int i = 0; i < bm.line_; i++)
        in >> bm.bm_[i];
    return in;
}


std::ostream& operator<<(std::ostream& out, const BoolMatrix& bm)
{
    for (int i = 0; i < bm.line_; i++)
        out << bm.bm_[i] << std::endl;
    return out;
}


void BoolMatrix::inversion(int index, int line)
{
    if (index < 0 || index >= column_)
        throw Invalid_column;
    if (line < 0 || line >= line_)
        throw Invalid_line;
    ~bm_[line][index];
}


void BoolMatrix::inversion(int index, int value, int line)
{
    if (index < 0 || index >= column_)
        throw Invalid_column;
    if (line < 0 || line >= line_)
        throw Invalid_line;
    if (value < 0 || value >= column_)
        throw Invalid_value;
    if (column_ - index <= value)
        value = column_ - index - 1;
    for (int i = index; i < value + index; i++)
        bm_[line].componentInversion(i);
}


void BoolMatrix::set0(int index, int line)
{
    if (index < 0 || index >= column_)
        throw Invalid_column;
    if (line < 0 || line >= line_)
        throw Invalid_line;
    bm_[line].set0(index);
}


void BoolMatrix::set1(int index, int line)
{
    if (index < 0 || index >= column_)
        throw Invalid_column;
    if (line < 0 || line >= line_)
        throw Invalid_line;
    bm_[line].set1(index);
}


void BoolMatrix::set0(int index, int value, int line)
{
    if (index < 0 || index >= column_)
        throw Invalid_column;
    if (line < 0 || line >= line_)
        throw Invalid_line;
    if (value < 0 || value >= column_)
        throw Invalid_value;
    if (column_ - index <= value)
        value = column_ - index - 1;
    for (int i = index; i < value + index; i++)
        bm_[line].set0(i);
}


void BoolMatrix::set1(int index, int value, int line)
{
    if (index < 0 || index >= column_)
        throw Invalid_column;
    if (line < 0 || line >= line_)
        throw Invalid_line;
    if (value < 0 || value >= column_)
        throw Invalid_value;
    if (column_ - index <= value)
        value = column_ - index - 1;
    for (int i = index; i < value + index; i++)
        bm_[line].set1(i);
}


int BoolMatrix::weight()
{
    int weight = 0;
    for (int i = 0; i < line_; i++)
        weight += bm_[i].weight();
    return weight;
}


int BoolMatrix::weightLine(int index)
{
    if (index < 0 || index >= line_)
        throw Invalid_line;
    return bm_[index].weight();
}


BoolVector BoolMatrix::fullConjunction()
{
    BoolVector result(column_, 1);
    for (int i = 0; i < line_; i++)
        result &= bm_[i];
    return result;
}


BoolVector BoolMatrix::fullDisjunction()
{
    BoolVector result(column_, 0);
    for (int i = 0; i < line_; i++)
        result |= bm_[i];
    return result;
}


BoolMatrix BoolMatrix::operator~()
{
    for (int i = 0; i < line_; i++)
        bm_[i].fullInversion();
    return *this;
}


BoolMatrix BoolMatrix::operator=(const BoolMatrix& other)
{
    if (this != &other) {
        delete[] bm_;
        bm_ = new BoolVector[line_ = other.line_];
        column_ = other.column_;
        for (int i = 0; i < line_; i++)
            bm_[i] = BoolVector(other.bm_[i]);
    }
    return *this;
}


BoolMatrix BoolMatrix:: operator|=(const BoolMatrix& other)
{
    if (line_ != other.line_)
        throw Invalid_size;
    for (int i = 0; i < line_; i++)
        bm_[i] |= other.bm_[i];
    return *this;
}


BoolMatrix BoolMatrix:: operator|(const BoolMatrix& other)
{
    return BoolMatrix(*this) |= other;
}


BoolMatrix BoolMatrix:: operator&=(const BoolMatrix& other)
{
    if (line_ != other.line_)
        throw Invalid_size;
    for (int i = 0; i < line_; i++)
        bm_[i] &= other.bm_[i];
    return *this;
}


BoolMatrix BoolMatrix:: operator&(const BoolMatrix& other)
{
    return BoolMatrix(*this) &= other;
}


BoolMatrix BoolMatrix:: operator^=(const BoolMatrix& other)
{
    if (line_ != other.line_)
        throw Invalid_size;
    for (int i = 0; i < line_; i++)
        bm_[i] ^= other.bm_[i];
    return *this;
}


BoolMatrix BoolMatrix:: operator^(const BoolMatrix& other)
{
    return BoolMatrix(*this) ^= other;
}


BoolVector& BoolMatrix::operator[](int line)
{
    if (line < 0 || line >= line_)
        throw Invalid_line;
    return bm_[line];
}